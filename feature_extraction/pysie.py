#
import os
import sys
import json
import collections
import time
import types
from optparse import OptionParser
from sie_feature_extractor import *
from raw_content_extractor import *
import multiprocessing
from logging import *

class PySIE:
    """
    SIE Python Version for Experiment
    """
    def __init__(self, config):
        self.config_ = config
        self.max_dim_index_ = config['feature_extraction']['max_dim_index']

    def extract_feature(self, file_path):
        info('Extract feature: '+file_path)
        with open(file_path, 'rb') as fh:
            content = fh.read()
            if self.config_['common']['use_raw_content']:
                feature_extractor = RawContentExtractor(self.config_['raw_content_extraction'])
                features = feature_extractor.extract(file_path, content)
                return features
            else:
                feature_extractor = SIEFeatureExtractor(self.config_['feature_extraction'])
                features = feature_extractor.extract(file_path, content)
                if features == None:
                    warning('[WARNING][PySIE.extract_feature] Unknown File Type, file path: ' + file_path)
                    return {}
                return features
                            
    def dump_feature_basecount_for_normalization(self, file_path):
        info('Extract feature: '+file_path)
        with open(file_path, 'rb') as fh:
            content = fh.read()
            feature_extractor = SIEFeatureExtractor(self.config_['feature_extraction'])
            features = feature_extractor.dump_feature_basecount_for_normalization(file_path, content)
            if features == None:
                warning('[WARNING][PySIE.extract_feature] Unknown File Type, file path: ' + file_path)
                return {}
            return features
    
    def convert_to_libsvm_format(self, label, features, comments):
        feature_msg = ''
        if isinstance(features, dict):
            ordered_features = collections.OrderedDict(sorted(features.items()))
            for i in ordered_features:
                value = ordered_features[i]
                if float(value) > 0:
                    feature_msg += '{}:{} '.format(i, value)
        else:
            feature_msg = features
        if self.config_['common']['use_raw_content']:
            return '{} {} # {}\n'.format(label, feature_msg, comments)
        else:
            return '{} {} {}:0 # {}\n'.format(label, feature_msg, self.max_dim_index_, comments)

    def dump_feature(self, label, target_path, dest_path):
        with open(dest_path, 'w') as output:
            if os.path.isdir(target_path):
                for root, dirs, files in os.walk(target_path):
                    for name in files:
                        file_path = os.path.join(root, name)
                        try:
                            features = self.extract_feature(file_path)
                            feature_line = self.convert_to_libsvm_format(label, features, file_path)
                            output.write(feature_line)
                        except Exception,e:
                            print '[ERROR] cannot extract feature on {}, exception is {}'.format(file_path, str(e))

            elif os.path.isfile(target_path):
                feature_msg = self.extract_feature(target_path)
                output.write(self.convert_to_libsvm_format(label, feature_msg, target_path))
            else:
                pass

    def dump_feature_from_file_list(self, label, file_list, dest_path):
        msg = 'Dump feature to: ' + dest_path
        info(msg)
        print(msg)
        with open(dest_path, 'w') as output:
            for file_path in file_list:
                try:
                    features = self.extract_feature(file_path)
                    feature_line = self.convert_to_libsvm_format(label, features, file_path)
                    output.write(feature_line)
                except Exception,e:
                    print( '[ERROR] cannot extract feature on {}, exception is {}'.format(file_path, str(e)) )
    
    def dump_feature_basecount_from_file_list(self, file_list):
        feature_base_dict = {}
        for filepath in file_list:
            try:
                feature_dict = self.dump_feature_basecount_for_normalization(filepath)
                feature_base_dict = update_feature_base(feature_base_dict, feature_dict)
            except Exception,e:
                    print( '[ERROR] cannot extract feature on {}, exception is {}'.format(filepath, str(e)) )
        return feature_base_dict

    def load_model(self, model_path):
        pass

    def predict(self, target_path):
        pass

def update_feature_base(feature_base_dict, feature_dict):
    for key in feature_dict:
        value = feature_dict[key]
        if type(value) == types.IntType:
            # js_length, vbs_length, num_external_link_script, num_internal_script
            if key not in feature_base_dict:
                feature_base_dict[key] = 0
            if feature_base_dict[key] < value:
                feature_base_dict[key] = value
        elif type(value) == types.DictionaryType:
            if key not in feature_base_dict:
                feature_base_dict[key] = {}
            for subkey in value:
                subvalue = value[subkey]
                if subkey not in feature_base_dict[key]:
                    feature_base_dict[key][subkey] = 0
                if feature_base_dict[key][subkey] < subvalue:
                    feature_base_dict[key][subkey] = subvalue
        else:
            print "[Eroor] Unsupport feature basecount type"
    return feature_base_dict

def get_thread_num(config):
    thread_num = config['common']['thread_num']
    if config['common']['use_system_cpu_num']:
        thread_num = multiprocessing.cpu_count()
        info('Use CPU number, thread number is {}'.format(thread_num))
    else:
        info('Use default config, thread number is {}'.format(thread_num))
    return thread_num

def generate_file_list_map(thread_num, target_path):
    file_list_map = {}
    for i in range(0,thread_num):
        file_list_map[i] = []
    if config['common']['target_is_filelist']:
        if not os.path.isfile(target_path):
            print('[ERROR] config `target_is_filelist` enable, target must be a file list!')
            exit(-1)
        with open(target_path, 'r') as fh:
            i = 0
            for line in fh.readlines():
                file_list_map[i%thread_num].append(line.strip())
                i += 1
    else:
        # with open(dest_path, 'w') as output:
        if os.path.isdir(target_path):
            i = 0
            for root, dirs, files in os.walk(target_path):
                for name in files:
                    file_path = os.path.join(root, name)
                    file_list_map[i%thread_num].append(file_path)
                    i += 1
        else:
            print '[ERROR] multi-thread only process folder'
            exit(-1)
    return  file_list_map

def process_file_list_by_pysie(config, id, label, file_list, dest_file):
    msg = 'Run process: {}, size of file_list: {}'.format(id, len(file_list))
    info(msg)
    print(msg)
    pysie = PySIE(config)
    pysie.dump_feature_from_file_list(label, file_list, dest_file)

def dump_feature_basecount_from_file_list(config, file_list):
    msg = 'Run process: {}, size of file_list: {}'.format(id, len(file_list))
    info(msg)
    print(msg)
    pysie = PySIE(config)
    return pysie.dump_feature_basecount_from_file_list(file_list)

def dump_feature_basecount_multi_thread(config, target_path, dest_path, src_path=None):
    thread_num = get_thread_num(config)
    file_list_map = generate_file_list_map(thread_num, target_path)

    # dump feature basecount 
    pool = multiprocessing.Pool(processes=thread_num)
    result_feature_basecount = []
    for i in range(0,thread_num):
        result_feature_basecount.append(pool.apply_async(dump_feature_basecount_from_file_list, (config, file_list_map[i])))
    pool.close()
    pool.join()
    
    # merge output
    if src_path:
        with open(src_path, 'rb') as fh:
            result = json.load(fh)
    else:
        result = {}
    for feature_base_dict in result_feature_basecount:
        feature_base_dict = feature_base_dict.get()
        result = update_feature_base(result, feature_base_dict)
    

    # save result
    
        
    with open(dest_path, 'w') as fh:
        fh.write(json.dumps(result))

def dump_feature_multi_thread(config, label, target_path, dest_path):
    thread_num = get_thread_num(config)
    file_list_map = generate_file_list_map(thread_num, target_path)

    proc_list = []
    file_path_wo_filename, filename = os.path.split(dest_path)
    filename_wo_ext, ext = os.path.splitext(filename)
    output_list = []
    for i in range(0,thread_num):
        new_target_path = os.path.join(file_path_wo_filename, '{}_proc_{}{}'.format(filename_wo_ext, i, ext))
        output_list.append(new_target_path)
        # id = thread.start_new_thread(self.dump_feature_from_file_list, (label, file_list_map[i], new_target_path))
        proc = multiprocessing.Process(target=process_file_list_by_pysie, args=(config, i, label, file_list_map[i], new_target_path))
        proc_list.append(proc)

    for proc in proc_list:
        proc.start()

    # Wait for all threads to complete
    for proc in proc_list:
        proc.join()

    # merge all of outputs
    if os.path.exists(dest_path):
        os.remove(dest_path)
    dest_fh = open(dest_path, 'wb')
    for file_path in output_list:
        with open(file_path, 'rb') as fh:
            dest_fh.write(fh.read())
        os.remove(file_path)
    dest_fh.close()
    print "Exiting Main Process"


help_msg = """
PySIE Usage:
    1) extract features and dump libsvm data format
        >> python pysie.py --dump-feature target_path --label label --dest-file [dest_file_path]
        Note:
            a) if dest_file_path is not specified, feature list will be dumped into original_file_name.libsvm.fea
            b) label is 1 or 0, here 1 indicates malicious, 0 indicates normal
    2) [not implemented] load model and predict target 
        >> python pysie.py --model-type [svm|xgboost|...] --model model_path --predict target_path
        Note:
            a) after prediction, this command will dump statistical information into console.
    3) dump feature base count
        >> python pysie.py --dump-featurebase target_path --dest-file dest_file_path  [--src-fle src_file_path]

Feature Index:
    0-499    DOM features
        0-120   tag number statistic
        121-249 big leaf content histogram
        250-xxx others
    500-999   TSS keywords features
    1000-1999 JS features
        1000-1099 common malicious keywords in JS code
        1100-1199 special malicious keywords in JS code
        1200-1499 keywords in JS code
        1500-1599 statistical feature index in JS code, refer to pysie.cfg
        1600-1729 histogram feature in JS code
        1730-1999 AST features
    2000-2999 VBS features
        2000-2099 common malicious keywords in VBS code
        2100-2199 special malicious keywords in VBS code
        2200-2499 keywords in VBS code
        2500-2999 AST features
    3000-10841 DOM tag-rel

"""

if __name__ == '__main__':
    parser = OptionParser(usage=help_msg)
    parser.add_option("--dump-feature", dest="dump_feature_target_path",
                      help="specify target path", metavar="TARGET-PATH")
    parser.add_option("--dump-featurebase", dest="dump_featurebase_target_path",
                      help="specify target path", metavar="TARGET-PATH")                      
    parser.add_option("--label", dest="label",
                      help="specify label for target category", metavar="LABEL")
    parser.add_option("--dest-file", dest="dest_file",
                      help="specify destination file path", metavar="DEST-FILE")
    parser.add_option("--src-file", dest="src_file",
                      help="specify src feature basecount file path", metavar="SRC-FILE")

    (options, args) = parser.parse_args()
    # set config in logging
    basicConfig(filename='pysie.log', format='[%(asctime)s][%(levelname)s] - %(message)s', level=INFO)

    if options.dump_feature_target_path or options.dump_featurebase_target_path:
        with open('pysie.cfg', 'rb') as fh:
            config = json.load(fh)
        info('Load config from pysie.cfg')

        begin_time = time.time()
        if options.dump_feature_target_path:
            if config['common']['thread_num'] == 1:
                info('Single thread mode')
                pysie = PySIE(config)
                pysie.dump_feature(int(options.label), options.dump_feature_target_path, options.dest_file)
            else:
                info('Multiple thread mode')
                dump_feature_multi_thread(config, int(options.label),
                                        options.dump_feature_target_path, options.dest_file)
        else:
            dump_feature_basecount_multi_thread(config, options.dump_featurebase_target_path, options.dest_file, options.src_file)

        msg = 'Time: {}'.format(time.time() - begin_time)
        info(msg)
        print(msg)

    else:
        print help_msg
