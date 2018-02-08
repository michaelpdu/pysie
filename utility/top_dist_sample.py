import sys
import pickle

from sklearn.metrics.pairwise import euclidean_distances


class TopDistCalculater:
    """
    """
    def __init__(self):
        self.top_n_list_ = []
        self.max_v_in_top_n_list_ = 1000

    def load_sample(self):
        self.sample_list_ = pickle.load(open(self.sample_file_, 'rb'))
        #print self.sample_list_.tolist()

    def update_item(self, item):
        if self.max_v_in_top_n_list_ > item[0]:
            self.max_v_in_top_n_list_ = item[0]

        if len(self.top_n_list_) <= self.top_n_:
            self.top_n_list_.append(item)
        else:    
            # find max v in list and remove it
            for i in self.max_v_in_top_n_list_:
                if i[0] == item[0]:
                    self.max_v_in_top_n_list_.remove(i)
            self.top_n_list_.append(item)

    def calc_euclidean_dist(self):
        print '>>> calculate distances'
        dist_matrix = euclidean_distances(self.sample_list_, self.sample_list_)
        # select top-n index and distances
        print '>>> select unique and valuable distances'
        dim_x,dim_y = dist_matrix.shape
        mean_value = dist_matrix.mean()
        for i in range(0,dim_x):
            sum_x_less_than_mean = 0
            count_x_less_than_mean = 0
            dic_conj = {}
            for j in range(0,dim_y):
                dist = dist_matrix.item((i,j))
                if dist < mean_value:
                   sum_x_less_than_mean = sum_x_less_than_mean + dist
                   count_x_less_than_mean += 1
                   dic_conj[j] = dist
            if count_x_less_than_mean == 0:
                continue
            mean_value = sum_x_less_than_mean/count_x_less_than_mean
            self.update_item((mean_value,i,dic_conj))       


    def process(self, sample_file, n):
        self.sample_file_ = sample_file
        self.top_n_ = n
        # load sample from file
        print '>>> load sample features from file'
        self.load_sample()
        # standardization
        print '>>> standardization'
        # calculate distances
        self.calc_euclidean_dist()                
        print '>> sort index_value_dict'
        # index_value_sorted_dict = sorted(index_value_dict.iteritems(), key=lambda d:d[1], reverse = False)
        print '>> dump sorted_dict'
        self.dump_top_index()

    def dump_top_index(self):
        for item in self.top_n_list_:
            print "mean distance: {}, node id: {}".format(item[0], item[1])
            sorted_dict_conj = sorted(item[2].iteritems(), key=lambda d:d[1], reverse = False)
            print sorted_dict_conj

def print_help():
    print 'Usage:'
    print '  python tool.py sample_feature_file top-n'

if __name__ == '__main__':
    top_dist = TopDistCalculater()
    top_dist.process(sys.argv[1], sys.argv[2])
    top_dist.dump_top_index()




