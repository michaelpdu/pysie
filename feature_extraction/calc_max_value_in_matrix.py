import sys
import json
from sklearn.datasets import load_svmlight_file

X, y = load_svmlight_file(sys.argv[1])
coo_max = X.max(axis=0)
print coo_max.data
data_list = coo_max.toarray()[0]
# print numpy.ndarray(coo_max)

with open('pysie.cfg', 'rb') as fh:
    config = json.load(fh)
tag_name_list = config['feature_extraction']['dom_tag_list'].split(',')

index = 0
for item in tag_name_list:
    print "{}:{}:{}".format(index, item, int(data_list[index]))
    index += 1

print "================ JSON Format ================="

index = 0
for item in tag_name_list:
    base = int(data_list[index])
    if base == 0:
        base = 1
    print '"{}":{},'.format(item, base)
    index += 1

