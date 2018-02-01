import sys
from dist_matrix import *
from sklearn.metrics.pairwise import euclidean_distances
from sklearn.datasets import load_svmlight_file

class SimilarityChecker:
    ''''''
    def __init__(self):
        pass

    def analyze(self, file_path_a, file_path_b, d):
        ax, ay = load_svmlight_file(file_path_a)
        bx, by = load_svmlight_file(file_path_b)
        self.calculate(ax, bx, d)

    def calculate(self, matrix_a, matrix_b, d):
        matrix = euclidean_distances(matrix_a, matrix_b)
        dim_x, dim_y = matrix.shape
        for i in range(0, dim_x):
            for j in range(0, dim_y):
                v = matrix.item((i, j))
                if v <= d:
                    print "A[{}] is similar with B[{}], distance is {}".format(i+1, j+1, v)

help_msg = """
Usage:
    > python check_file_similarity.py feature_list_a feature_list_b

    Note:
        1. parameter
            feature_list_a: feature for all of samples
            feature_list_b: feature for new sample
        2. Output format looks like:
            A[2] is similar with B[3], distance is 0.0
            Here all of index starts from 1

"""

if __name__ == '__main__':
    checker = SimilarityChecker()
    checker.analyze(sys.argv[1], sys.argv[2], 0)
    # ax = [[1,0],[1,1],[2,1]]
    # bx = [[0,0],[3,4],[1,1]]
    # print euclidean_distances(ax,bx)
    # checker.calculate(ax, bx, 1)