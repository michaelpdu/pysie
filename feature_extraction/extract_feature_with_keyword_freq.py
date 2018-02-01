import os
import sys
import json
from dom_parser import *
from js_feature_extractor import *
from vbs_feature_extractor import *
from keyword_feature_analyzer import *

sys.path.append(os.path.join('..','..'))
from utility.file_type_detector import *
from utility.encoding_checker import *
file_type_yara_file = os.path.join('..','..','utility','file_type.yar')

class FeatureExtractor:
    def __init__(self, auto_config_path, feature_config_path, top_keyword=0):
        with open(auto_config_path, 'r+') as fd:
            self.auto_cfg = json.load(fd)
        with open(feature_config_path, 'r+') as fd:
            self.feature_cfg = json.load(fd)
        with open(self.auto_cfg['auto_by_engine']['max_tf_cfg_path'], 'r+') as fd:
            self.tf_cfg = json.load(fd)
        self.feature_cfg_map = self.feature_cfg['feature_extraction']
        self.max_dim_index = self.feature_cfg['feature_extraction']['max_dim_index']
        with open(self.feature_cfg_map['js_feature_yara_rule'], 'rb') as fh:
            feature_rules = fh.read()
        self.js_feature_e = JSFeatureExtractor(feature_rules, self.feature_cfg_map)
        with open(self.feature_cfg_map['vbs_feature_yara_rule'], 'rb') as fh:
            feature_rules = fh.read()
        self.vbs_feature_e = VBSFeatureExtractor(feature_rules, self.feature_cfg_map)
        if self.auto_cfg['auto_by_python']['word_freq_function'] == 'MAXTF':
            self.keyword_feature_extractor =  KeywordFeatureAnalyzer(self.feature_cfg, self.tf_cfg, True)
        else:
            self.keyword_feature_extractor =  KeywordFeatureAnalyzer(self.feature_cfg, self.tf_cfg, False)
        self.topn = int(top_keyword)
        self.file_type_detector_ = FileTypeDetector(file_type_yara_file)
        self.encoding_modifier_ = EncodingModifier()
        
	self.dom_parser_ = DOMParser(self.feature_cfg_map)
        self.features = {}

    def extract_feature(self, label, src_path, dest_path):
    	print 'extract feature,src path',src_path
	with open(dest_path, 'w+') as output:
            for root, dirs, fs in os.walk(src_path):
                for name in fs:
                    file_path = os.path.join(root, name)
                    print 'process file:', file_path
		    try:
                        with open(file_path, 'r+') as fd:
                            content = fd.read()
                        self.features.clear()
                        self.extract(file_path, content)
                        feature_line = self.convert_to_libsvm_format(label, file_path)
                        print (feature_line)
                        output.write(feature_line)
		    except Exception, e:
                        print '[ERROR] cannot extract feature on {}, exception is {}'.format(file_path, str(e))

    def convert_to_libsvm_format(self, label, comments):
        feature_msg = ''
        if isinstance(self.features, dict):
            ordered_features = collections.OrderedDict(sorted(self.features.items()))
            for i in ordered_features:
                value = ordered_features[i]
                if float(value) > 0:
                    feature_msg += '{}:{} '.format(i, value)
        else:
            feature_msg = self.features
        return '{} {} # {}\n'.format(label, feature_msg, comments)

    def extract_html_features(self, file_path, content):
        self.dom_parser_.parse_content(content)
        if self.feature_cfg_map['enable_dom_feature'] > 0:
            dom_features = self.dom_parser_.get_dom_features()
            self.features.update(dom_features)
        if self.feature_cfg_map['enable_js_feature'] > 0:
            js_list = self.dom_parser_.get_javascripts()
            js_features = self.extract_js_features(file_path, '\n'.join(js_list))
            self.features.update(js_features)
        if self.feature_cfg_map['enable_vbs_feature'] > 0:
            vbs_list = self.dom_parser_.get_vbscripts()
            vbs_features = self.extract_vbs_features(file_path, '\n'.join(vbs_list))
            self.features.update(vbs_features)
        return self.features

    def extract_js_features(self, file_path, content):
        if self.topn > 0:
            self.keyword_feature_extractor.analyze_content(content, self.topn)
            self.features.update(self.keyword_feature_extractor.get_features_index_frequency())
        return self.js_feature_e.extract_js_features(file_path, content)

    def extract_vbs_features(self, file_path, content):
        if self.topn > 0:
            self.keyword_feature_extractor.analyze_content(content, self.topn)
            self.features.update(self.keyword_feature_extractor.get_features_index_frequency())
        return self.vbs_feature_e.extract_vbs_features(file_path, content)

    def extract(self, file_path, content):
        file_type, encoding_type = self.file_type_detector_.check_type(content)
        if FileType.FILETYPE_HTML == file_type:
            if EncodingType.ENCODE_UNKNOWN != encoding_type:
                content = self.encoding_modifier_.modify(content, encoding_type)
            return self.extract_html_features(file_path, content)
        elif FileType.FILETYPE_JS == file_type:
            return self.extract_js_features(file_path, content)
        elif FileType.FILETYPE_VBS == file_type:
            return self.extract_vbs_features(file_path, content)
        else:
            return None


def print_help():
    print ('''
        python tool.py auto.json_path pysie.cfg_path topn src_path dest_path label
    ''')

if __name__ == '__main__':
    print_help()
    auto_path = sys.argv[1]
    feature_cfg_path = sys .argv[2]
    topn = int(sys.argv[3])
    src_path = sys.argv[4]
    dest_path = sys.argv[5]
    label = sys.argv[6]

    et = FeatureExtractor(auto_path, feature_cfg_path, topn)
    et.extract_feature(label, src_path, dest_path)
