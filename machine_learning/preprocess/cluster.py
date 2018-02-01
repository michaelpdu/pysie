import os, sys
from sklearn.cluster import KMeans
from sklearn.datasets import load_svmlight_file


class ClusterHelper:
    """"""
    def __init__(self):
        self.label_group_ = {}
        self.k_num_ = 10
        self.output_dir_ = 'output'

    def cluster(self):
        kmeans = KMeans(n_clusters=self.k_num_, random_state=0).fit(self.data_)
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

    def save_to_file(self, index_list, lines, output_file_name):
        with open(output_file_name, 'wb') as fh:
            for index in index_list:
                fh.write(lines[index-1])

    def generate_clustered_files(self):
        with open(self.input_file_, 'rb') as fh:
            lines = fh.readlines()
        path_wo_ext, ext = os.path.splitext(self.input_file_)
        dir_path, file_name = os.path.split(path_wo_ext)
        for label in self.label_group_:
            dest_file_path = os.path.join(self.output_dir_, '{}_cluster_{}{}'.format(file_name, label, ext))
            self.save_to_file(self.label_group_[label], lines, dest_file_path)

    def analyze(self, input_file, num, output_dir):
        self.input_file_ = input_file
        self.k_num_ = num
        self.output_dir_ = output_dir
        if not os.path.exists(self.output_dir_):
            os.makedirs(self.output_dir_)

        # step 1: load data from file
        self.data_, y = load_svmlight_file(input_file)
        # step 2: cluster
        self.cluster()
        # step 3: generate new files
        self.generate_clustered_files()


help_msg = '''
Usage:
    > python cluster.py feature-file num output-folder
    Note:
        1. feature-file is libsvm format file
        2. num is number of k-means
        3. output-folder is
For example:
    1. cluster
        python cluster.py xxx.txt 10
        it will generate two files: group_a.txt and group_b.txt, and group_a is a bigger one
'''

if __name__ == '__main__':
    # try:
    #     s = ClusterHelper()
    #     s.analyze(sys.argv[1], sys.argv[2], sys.argv[3])
    # except Exception,e:
    #     print help_msg
    #     print 'Exception: {}'.format(str(e))
    s = ClusterHelper()
    s.analyze(sys.argv[1], int(sys.argv[2]), sys.argv[3])