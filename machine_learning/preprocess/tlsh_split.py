import os, sys, shutil
import subprocess
import random
from optparse import OptionParser
import tlsh_tool


class TLSHSplitHelper(object):
    def __init__(self):
        self.label_group_ = {}
        self.group_a_ = {}
        self.group_b_ = {}

    def exec_cmd(self, cmd):
        print "[Command] " + cmd
        p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.wait()
        if p.returncode != 0:  
            print "[Execute Command Error] " + p.stderr.read()  
            raise Exception("Execute Command Error")


    def build_tlsh_forest(self, src_file):
        our_dir = os.path.dirname(src_file)
        filename, fileext = os.path.splitext(src_file)
        tlsh_file = filename+'.tlsh'
        dt_file = filename+'.dt'
        try:
            cmd_extract_tlsh_values = "cut -f 2 {} > {}".format(src_file, tlsh_file)
            self.exec_cmd(cmd_extract_tlsh_values)
            
            cmd_build_forest = "lsh_tree -i {} -o {}".format(tlsh_file, dt_file)
            self.exec_cmd(cmd_build_forest)
        except Exception as e:
            print e

    def cluster(self, src_file, tlsh_distance):
        filename, fileext = os.path.splitext(src_file)
        tlsh_file = filename+'.tlsh'
        dt_file = filename+'.dt'
        clout_file = filename+'.clout'
        txtg_file = filename+'.txtg'
        
        try:
            cmd_cluster_tlsh_value = "search_lsh_tree -dt {} -cluster {} -T {} > {}".format(dt_file, tlsh_file, tlsh_distance, clout_file)
            self.exec_cmd(cmd_cluster_tlsh_value)

            cmd_label_data_file = "perl tlsh_cluster_label.pl -c {} -f {} > {}".format(clout_file, src_file, txtg_file)
            self.exec_cmd(cmd_label_data_file)
        except Exception as e:
            print e

    def get_cluster_result(self, filepath):
        with open(filepath, 'rb') as fh:
            for line in fh.readlines():
                temp_list = line.strip().split('\t')
                if len(temp_list) < 4 or temp_list[0] == 'Sing':
                    print "[Warning] " + line
                else:
                    label = temp_list[0] + temp_list[1]
                    filepath = temp_list[2]
                    if label in self.label_group_:
                        self.label_group_[label].append(filepath)
                    else:
                        self.label_group_[label] = [filepath]
                
    def split_by_random(self, percentage):
        for item in self.label_group_:
            length = len(self.label_group_[item])
            length_a = int(length * percentage)
            if percentage >= 1:
                self.group_a_[item] = self.label_group_[item]
                self.group_b_[item] = []
            else:
                rand_list = sorted(random.sample(set(self.label_group_[item]), length_a))
                self.group_a_[item] = rand_list
                self.group_b_[item] = list(set(self.label_group_[item]) - set(rand_list))
    def save_to_file(self, label_group, output_file_name):
        try:
            with open(output_file_name, 'wb') as fh:
                for label in label_group:
                    for filepath in label_group[label]:
                        fh.write("{}\t{}\n".format(filepath, label))
        except Exception,e:
            print "[Exception][TLSHSplitHelper.save_to_file] "+str(e)

    def generate_two_files(self, file_path, percentage):
        path_wo_ext, ext = os.path.splitext(file_path)
        dest_file_path = '{}_{}'.format(path_wo_ext, percentage)
        file_a = dest_file_path+"_group_a.txt"
        file_b = dest_file_path+"_group_b.txt"
        self.save_to_file(self.group_a_, file_a)
        self.save_to_file(self.group_b_, file_b)
        return file_a, file_b

    def move_samples(self, label_group, dst_dir):
        if not os.path.exists(dst_dir):
            os.makedirs(dst_dir)
        for label in label_group:
            for filepath in label_group[label]:
                dst_path = os.path.join(dst_dir, os.path.basename(filepath))
                if not os.path.exists(dst_path):
                    shutil.move(filepath, dst_path)

    def split(self, src_file, percentage, dst_dir=None):
        src_file_name = os.path.splitext(src_file)[0]
        txtg_file = src_file_name +'.txtg'
        percentage = float(percentage)
        self.get_cluster_result(txtg_file)
        self.split_by_random(percentage)
        self.generate_two_files(txtg_file, percentage)
        
        if dst_dir:
            self.move_samples(self.group_a_, os.path.join(dst_dir, src_file_name+"_group_a"))
            self.move_samples(self.group_b_, os.path.join(dst_dir, src_file_name+"_group_b"))
            
        





help_msg = """
Usage:
For example:
    1. build forest
       python tlsh_split.py build_forest --tlsh_data xxx_input.txt
    2. cluster
        python tlsh_split.py cluster --tlsh_data xxx_input.txt --distance 300 (max distance is 300, default is 300)
    3. split
        python tlsh_split.py split --tlsh_data xxx_input.txt --move dst_dir --percentage 0.5 (default is 0.5)
        python tlsh_split.py split --tlsh_data xxx_input.txt --percentage 0.5 (default is 0.5)
    4. do all process
        python tlsh_split.py all --tlsh_data xxx_input.txt --percentage 0.5 --distance 300
        python tlsh_split.py all --tlsh_data xxx_input.txt --percentage 0.5 --distance 300 --move dst_dir
    

"""

if __name__ == '__main__':
    try:
        parser = OptionParser(usage=help_msg)
        parser.add_option("--tlsh_data", dest="data_file", help="specify tlsh data file")
        parser.add_option("--percentage", dest="percentage", help="specify percentage", default="0.5")
        parser.add_option("--distance", dest="tlsh_distance", help="specify tlsh distance", default="300")
        parser.add_option("--move", dest="sample_dst_dir", help="specify sample dest dir")
        (options, args) = parser.parse_args()
        print options
        split_helper = TLSHSplitHelper()
        if len(sys.argv) == 1:
            print help_msg
        elif "all" in args:
            split_helper.build_tlsh_forest(options.data_file)
            split_helper.cluster(options.data_file, options.tlsh_distance)
            split_helper.split(options.data_file, options.percentage, options.sample_dst_dir)
        else:
            if "build_forest" in args:
                split_helper.build_tlsh_forest(options.data_file)
            if "cluster" in args:
                split_helper.cluster(options.data_file, options.tlsh_distance)
            if "split" in args:
                print options.sample_dst_dir
                split_helper.split(options.data_file, options.percentage, options.sample_dst_dir)
    except Exception as e:
        print e 
        print help_msg