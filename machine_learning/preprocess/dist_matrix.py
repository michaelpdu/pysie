import sys
import numpy
from sklearn.metrics.pairwise import euclidean_distances
from sklearn.datasets import load_svmlight_file

class DistMatrix:
    '''  '''
    def __init__(self, type):
        self.type_ = type

    def load_libsvm_sample(self, file_path):
        self.x_, self.y_ = load_svmlight_file(file_path)

    def calculate_dist_matrix(self):
        self.matrix_ = euclidean_distances(self.x_, self.x_)
        # print self.matrix_

    def calc_dense_value(self, n):
        dense_map = {}
        i = 0
        for dist_list in self.matrix_:
            sorted_dist_list = sorted(dist_list)[0:n]
            dense_map[i] = numpy.mean(sorted_dist_list)
            i+=1
        return dense_map

    def get_max_min_dist(self):
        print self.calc_dense_value(10)
        return 0,0

    def find_similarity(self, d):
        dim_x, dim_y = self.matrix_.shape
        for i in range(0, dim_x):
            for j in range(i+1, dim_y):
                v = self.matrix_.item((i, j))
                if v <= d:
                    print "{} is similar with {}, distance is {}".format(i+1, j+1, v)
                # print "{} ".format(v)
            # print "\n"

help_msg = '''
Usage:
    python dist_matrix.py
For example:
    1. split
'''

def print_help():
    print help_msg

if __name__ == '__main__':
    dist_matrix = DistMatrix(1)
    dist_matrix.load_libsvm_sample(sys.argv[1])
    dist_matrix.calculate_dist_matrix()
    # max_dist, min_dist = dist_matrix.get_max_min_dist()
    # print 'Max distance is {}, min distance is {}'.format(max_dist, min_dist)
    dist_matrix.find_similarity(1)