import os
import sys
import shutil
import json
import re

sys.path.append(os.path.join("..",".."))
from utility.file_type_detector import *
from utility.encoding_checker import *

file_type_yara_file = os.path.join('..','..','utility','file_type.yar')

from dom_parser import *
import multiprocessing

# PROC_NUM = 1
PROC_NUM = multiprocessing.cpu_count()

# 
# remove illegal tagrel, such as, multiple '-' and ':' in one line, find \W in tagrel key
#
def analyze_tagrel_file(input_file, output_file):
    with open(output_file, 'wb') as ofh:
        with open(input_file, 'rb') as ifh:
            for line in ifh.readlines():
                if line.count('-') > 1 or line.count(':') > 1:
                    continue
                else:
                    tag_rel, count = line.strip().split(':')
                    # remove line whose count is 0
                    if int(count) == 0:
                        print line
                        continue

                    # check illegal key
                    parent_tag_name, tag_name = tag_rel.split('-')
                    if parent_tag_name != '[document]':
                        matched = re.search(r'\W', parent_tag_name)
                        if matched:
                            print(line)
                            continue
                    matched = re.search(r'\W', tag_name)
                    if matched:
                        print(line)
                        continue

                    # only write lines whose tagrel contains \w
                    ofh.write('"{}-{}":{},\n'.format(parent_tag_name,tag_name,count))



class TagRelStatisticHelper:
    """"""
    def __init__(self, config):
        self.config_ = config
        self.max_tagrel_count_dict_ = {}
        self.total_tagrel_count_dict_ = {}
        self.type_detector_ = FileTypeDetector(file_type_yara_file)
        self.encoding_modifier_ = EncodingModifier()
        self.tag_name_list_ = self.config_['feature_extraction']['dom_tag_list'].split(',')

    def save_dict_to_file(self, dict_info, dest_file, sort_by_value = False, reverse=False):
        if sort_by_value:
            tag_rel_list = sorted(dict_info.iteritems(), key=lambda d: d[1], reverse=reverse)
        else:
            tag_rel_list = sorted(dict_info.iteritems(), key=lambda d: d[0], reverse=reverse)
        with open(dest_file, 'wb') as fh:
            for item in tag_rel_list:
                fh.write('{}:{}\n'.format(item[0], item[1]))

    def extract_tagrel_to_file(self, src_file, dest_file):
        try:
            with open(src_file, 'rb') as fh:
                content = fh.read()
                file_type, encoding_type = self.type_detector_.check_type(content)
                if file_type == FileType.FILETYPE_HTML:
                    if EncodingType.ENCODE_UNKNOWN != encoding_type:
                        content = self.encoding_modifier_.modify(content, encoding_type)
                    dom_parser = DOMParser(self.config_['feature_extraction'])
                    dom_parser.parse_content(content)
                    self.save_dict_to_file(dom_parser.get_tag_relationship_statistic(), dest_file)
                else:
                    print '[INFO] {} is not HTML file'.format(src_file)
        except Exception, e:
            print '[ERROR] Cannot process: {}, exception is: {}'.format(src_file, str(e))

    def extract_tagrel_in_dir(self, src_dir, dest_dir):
        if not os.path.exists(dest_dir):
            os.makedirs(dest_dir)
        for root, dirs, files in os.walk(src_dir):
            for name in files:
                name_wo_ext, ext = os.path.splitext(name)
                new_name = name_wo_ext + '_tagrel' + ext
                self.extract_tagrel_to_file(os.path.join(root, name), os.path.join(dest_dir, new_name))

    def extract_tagrel_in_list(self, file_list, dest_dir):
        if not os.path.exists(dest_dir):
            os.makedirs(dest_dir)
        for file_path in file_list:
            # file_path = line.strip()
            dir_path, file_name = os.path.split(file_path)
            name_wo_ext, ext = os.path.splitext(file_name)
            new_name = name_wo_ext + '_tagrel' + ext
            self.extract_tagrel_to_file(file_path, os.path.join(dest_dir, new_name))

    def update_tagrel_map(self, input_file):
        with open(input_file, 'rb') as fh:
            for line in fh.readlines():
                if line.count('-') > 1 or line.count(':') > 1:
                    continue
                else:
                    tagrel, count = line.strip().split(':')
                    parent_tag_name, tag_name = tagrel.split('-')
                    if len(parent_tag_name) > 10 or len(tag_name) > 10:
                        continue
                    count = int(count)
                    # build max_tagrel_count_dict_
                    if self.max_tagrel_count_dict_.get(tagrel) != None:
                        pre_value = self.max_tagrel_count_dict_[tagrel]
                        if count > pre_value:
                            self.max_tagrel_count_dict_[tagrel] = count
                        else:
                            pass
                    else:
                        self.max_tagrel_count_dict_[tagrel] = count
                    # build total_tagrel_count_dict_
                    if self.total_tagrel_count_dict_.get(tagrel) != None:
                        self.total_tagrel_count_dict_[tagrel] += count
                    else:
                        self.total_tagrel_count_dict_[tagrel] = count

    def merge_tagrel_files(self, src_dir, max_tagrel_count_file, total_tagrel_count_file):
        self.max_tagrel_count_dict_.clear()
        self.total_tagrel_count_dict_.clear()
        for root, dirs, files in os.walk(src_dir):
            for name in files:
                file_path = os.path.join(root, name)
                self.update_tagrel_map(file_path)
        self.save_dict_to_file(self.max_tagrel_count_dict_, max_tagrel_count_file)
        self.save_dict_to_file(self.total_tagrel_count_dict_, total_tagrel_count_file)

    def merge_tagrel_in_list(self, file_list, max_tagrel_count_file, total_tagrel_count_file):
        self.max_tagrel_count_dict_.clear()
        for file_path in file_list:
            self.update_tagrel_map(file_path)
        if max_tagrel_count_file != None and max_tagrel_count_file != '':
            self.save_dict_to_file(self.max_tagrel_count_dict_, max_tagrel_count_file)
        if total_tagrel_count_file != None and total_tagrel_count_file != '':
            self.save_dict_to_file(self.total_tagrel_count_dict_, total_tagrel_count_file, True, True)

def extract_reltag_proc(config, id, file_list, dest_dir):
    print 'Run process: {}, size of file_list: {}'.format(id, len(file_list))
    helper = TagRelStatisticHelper(config)
    helper.extract_tagrel_in_list(file_list, dest_dir)

def extract_reltag_in_multi_process(config, src_dir, dest_dir):
    proc_num = PROC_NUM
    file_list_map = {}
    for i in range(0,proc_num):
        file_list_map[i] = []

    if os.path.isdir(src_dir):
        i = 0
        for root, dirs, files in os.walk(src_dir):
            for name in files:
                file_path = os.path.join(root, name)
                file_list_map[i%proc_num].append(file_path)
                i += 1
    else:
        print '[ERROR] multi-thread only process folder'
        exit(-1)
    #
    proc_list = []
    for i in range(0,proc_num):
        proc = multiprocessing.Process(target=extract_reltag_proc, \
                                       args=(config, i, file_list_map[i], dest_dir))
        proc_list.append(proc)

    for proc in proc_list:
        proc.start()

    # Wait for all threads to complete
    for proc in proc_list:
        proc.join()

    print "[Extract RelTag] Exiting Main Process"


def merge_reltag_proc(config, id, file_list, max_tagrel_count_file, total_tagrel_count_file):
    print 'Run process: {}, size of file_list: {}'.format(id, len(file_list))
    helper = TagRelStatisticHelper(config)
    helper.merge_tagrel_in_list(file_list, max_tagrel_count_file, total_tagrel_count_file)

def merg_reltag_in_multi_process(config, src_dir, dest_file):
    proc_num = PROC_NUM

    file_list_map = {}
    temp_max_tagrel_count_file_list = []
    temp_total_tagrel_count_file_list = []

    dest_dir, filename = os.path.split(dest_file)
    if dest_dir == '':
        dest_dir = '.'
    filename_wo_ext, ext = os.path.splitext(filename)
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    # make tmp directory in dest_dir
    temp_dir = os.path.join(dest_dir, 'temp_merge_tagrel')
    if os.path.exists(temp_dir):
        shutil.rmtree(temp_dir)
    os.makedirs(temp_dir)

    for i in range(0,proc_num):
        temp_max_tagrel_count_file_list.append(os.path.join(temp_dir,\
                                        '{}_tmp_max_{}{}'.format(filename_wo_ext, i, ext)))
        temp_total_tagrel_count_file_list.append(os.path.join(temp_dir,\
                                        '{}_tmp_total_{}{}'.format(filename_wo_ext, i, ext)))
        file_list_map[i] = []

    max_tagrel_count_file = os.path.join(dest_dir,'{}_max{}'.format(filename_wo_ext, ext))
    total_tagrel_count_file = os.path.join(dest_dir, '{}_total{}'.format(filename_wo_ext, ext))

    if os.path.isdir(src_dir):
        i = 0
        for root, dirs, files in os.walk(src_dir):
            for name in files:
                file_path = os.path.join(root, name)
                file_list_map[i%proc_num].append(file_path)
                i += 1
    else:
        print '[ERROR] multi-thread only process folder'
        exit(-1)
    #
    proc_list = []
    for i in range(0,proc_num):
        proc = multiprocessing.Process(target=merge_reltag_proc, args=(config, i, file_list_map[i], \
                                      temp_max_tagrel_count_file_list[i], temp_total_tagrel_count_file_list[i]))
        proc_list.append(proc)

    for proc in proc_list:
        proc.start()

    # Wait for all threads to complete
    for proc in proc_list:
        proc.join()

    # merge reltag files in temp dir
    merge_reltag_proc(config, 0, temp_max_tagrel_count_file_list, max_tagrel_count_file, None)
    merge_reltag_proc(config, 0, temp_total_tagrel_count_file_list, None, total_tagrel_count_file)

    # remove temp dir
    shutil.rmtree(temp_dir)

    print "[Extract RelTag] Exiting Main Process"


def select_top_n_item(top_n, total_tagrel_file, max_tagrel_file, top_max_tagrel_file):
    top_n_tagrel_list = []
    with open(total_tagrel_file, 'rb') as total_tagrel_fh:
        top_n_lines = total_tagrel_fh.readlines()[0:top_n]
        for line in top_n_lines:
            top_n_tagrel_list.append(line.split(':')[0])
    with open(top_max_tagrel_file, 'wb') as top_max_tagrel_fh:
        with open(max_tagrel_file, 'rb') as max_tagrel_fh:
            for line in max_tagrel_fh.readlines():
                key, value = line.strip().split(':')
                if key in top_n_tagrel_list:
                    top_max_tagrel_fh.write('"{}":{},\n'.format(key, value))

help_msg = """
Usage:
    (1) analyze file and dump tag_rel to file_name-tag_rel.txt
    >> python tool.py -f src-dir dest-dir

    (2) merge tag_rel files
    >> python tool.py -m src-dir dest-file

    (3) remove illegal tagrel line
    >> python tool.py -a src-tagrel-file dest-file > illegal-lines

    (4) select top-n max-tagrel-list according total-list sequence
    >> python tool.py -t 1000 total-list-file max-list-file top-n-max-list-file
"""


if __name__ == '__main__':
    try:
        if sys.argv[1] != '-f' and sys.argv[1] != '-m' and sys.argv[1] != '-a' and sys.argv[1] != '-t':
            print help_msg
            exit(-1)
    except Exception,e:
        print(help_msg)
        exit(-1)
    with open('pysie.cfg', 'rb') as fh:
        config = json.load(fh)

    if sys.argv[1] == '-f':
        extract_reltag_in_multi_process(config, sys.argv[2], sys.argv[3])
    elif sys.argv[1] == '-m':
        merg_reltag_in_multi_process(config, sys.argv[2], sys.argv[3])
    elif sys.argv[1] == '-a':
        analyze_tagrel_file(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == '-t':
        select_top_n_item(int(sys.argv[2]), sys.argv[3], sys.argv[4], sys.argv[5])
    else:
        print('Unsupported parameters')
