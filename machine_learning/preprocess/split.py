import os
import sys
import random
from sklearn.cluster import KMeans
from sklearn.datasets import load_svmlight_file

class SplitHelper:
    ''''''
    def __init__(self):
        self.label_group_ = {}
        self.group_a_ = {}
        self.group_b_ = {}
        self.kmeans_num_ = 10
        self.groups = {}

    def set_kmeans_num(self, num):
        self.kmeans_num_ = num

    def cluster(self):
        kmeans = KMeans(n_clusters=self.kmeans_num_, random_state=0).fit(self.data_)
        # print kmeans.labels_
        # index starts from 1, for reading
        i = 1
        for label in kmeans.labels_:
            if label in self.label_group_:
                self.label_group_[label].append(i)
            else:
                self.label_group_[label] = [i]
            i += 1
        self.label_group_

    def split_by_top(self, percentage):
        for item in self.label_group_:
            length = len(self.label_group_[item])
            length_a = int(length * percentage)
            self.group_a_[item] = self.label_group_[item][0:length_a]
            self.group_b_[item] = self.label_group_[item][length_a:]

    def split_by_step(self, percentage):
        # for item in self.label_group_:
        #     length = len(self.label_group_[item])
        #     length_a = int(length * percentage)
        #     self.group_a_[item] = self.label_group_[item][0:length_a]
        #     self.group_b_[item] = self.label_group_[item][length_a:]
        pass

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

    def split_into_nfolder_by_random(self, file_path, folder_count):
        for item in self.label_group_:
            length = len(self.label_group_[item])
            piece_length = int(length / folder_count)
            rand_list = self.label_group_[item]
            random.shuffle(rand_list)
            slice_begin = 0
            slice_end = 0
            for i in range(0, folder_count):
                if i not in self.groups:
                    self.groups[i] = {item: []}
                if item not in self.groups[i]:
                    self.groups[i][item] = []

                if piece_length > 0:
                    slice_end = piece_length + slice_begin
                    self.groups[i][item].extend(sorted(rand_list[slice_begin: slice_end]))
                    slice_begin = slice_end
            for i in range(slice_end, length):
                self.groups[i - slice_end][item].append(rand_list[i])

        with open(file_path, 'rb') as fh:
            lines = fh.readlines()
        path_wo_ext, ext = os.path.splitext(file_path)

        for i in range(0, folder_count):
            dest_file_path = '{}_{}'.format(path_wo_ext, folder_count)
            print(self.groups[i])
            self.save_to_file(self.groups[i], lines, dest_file_path + "_group_{}.txt".format(i))

    def split(self, percentage, method='random'):
        if method == 'step':
            self.split_by_step(percentage)
        elif method == 'top':
            self.split_by_top(percentage)
        elif method == 'random':
            self.split_by_random(percentage)
        else:
            self.split_by_random(percentage)

    def save_to_file(self, label_group, lines, output_file_name):
        try:
            with open(output_file_name, 'wb') as fh:
                for item in label_group:
                    for index in label_group[item]:
                        fh.write("{} @@group_{},index_{}\n".format(lines[index-1].strip(), item, index))
        except Exception,e:
            print "[Exception][SplitHelper.save_to_file] "+str(e)

    def generate_two_files(self, file_path, split_method, percentage):
        with open(file_path, 'rb') as fh:
            lines = fh.readlines()
        path_wo_ext, ext = os.path.splitext(file_path)
        dest_file_path = '{}_{}_{}'.format(path_wo_ext, split_method, percentage)
        file_a = dest_file_path+"_group_a.txt"
        file_b = dest_file_path+"_group_b.txt"
        self.save_to_file(self.group_a_, lines, file_a)
        self.save_to_file(self.group_b_, lines, file_b)
        return file_a, file_b

    def analyze(self, file_path, percentage=0.7):
        # step 1: load data from file
        self.data_, y = load_svmlight_file(file_path)
        # step 2: cluster
        self.cluster()

        if int(percentage) >= 2:
            # split into n folder
            self.split_into_nfolder_by_random(file_path, int(percentage))
        else:
            # step 3: split based on cluster group
            split_method = 'random'
            self.split(percentage, split_method)
            # step 4: generate new files
            self.generate_two_files(file_path, split_method, percentage)



help_msg = '''
Usage:
    > python split.py feature-file percentage
For example:
    1. split sample set by 7:3
        python split.py xxx.txt 0.7
        it will generate two files: group_a.txt and group_b.txt, and group_a is a bigger one
    2. split into n folder
        python split.py xxx.txt 5
        it will generate 5 file: n_group_0.txt n_group_1.txt ...
'''

if __name__ == '__main__':
    try:
        s = SplitHelper()
        s.set_kmeans_num(20)
        s.analyze(sys.argv[1], float(sys.argv[2]))
    except Exception,e:
        print help_msg
        print 'Exception: {}'.format(str(e))