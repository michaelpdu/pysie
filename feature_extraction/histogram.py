import sys, operator
import matplotlib.pyplot as plt

class Histogram:
    """"""
    def __init__(self):
        self.hist_ = dict()
        for i in range(0,129):
            self.hist_[i] = 0

    def update(self, ch):
        ord_ch = ord(ch)
        if ord_ch >= 128:
            self.hist_[128] += 1
        else:
            self.hist_[ord_ch] += 1

    def get_features(self, base_index = 0):
        max_value = max(self.hist_.iteritems(), key=operator.itemgetter(1))[1]
        # fix bug: divide 0 error
        if max_value == 0:
            max_value = 10000
        features = dict()
        for item in self.hist_:
            features[base_index + item] = float(self.hist_[item])/max_value
        return features

if __name__ == '__main__':
    with open(sys.argv[1], 'rb') as fh:
        content = fh.read()
    hist = Histogram()
    for ch in content:
        hist.update(ch)
    features = hist.get_features(1000)
    # show histogram
    plt.hist(features.values(), bins='auto')
    plt.title("Histogram with 'auto' bins")
    plt.show()