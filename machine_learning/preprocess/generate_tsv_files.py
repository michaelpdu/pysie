import os, sys
from sklearn.datasets import load_svmlight_file

def load_svm_file(svm_file_path):
    path_list = []
    with open(svm_file_path, 'r') as fh:
        for line in fh.readlines():
            comments = line.split('# ')[1]
            file_path = comments.split(' @@')[0]
            path_list.append(file_path)
    return path_list

svm_file_path = sys.argv[1]
print('Load file from: %s' % svm_file_path)
X, y = load_svmlight_file(svm_file_path)
path_list = load_svm_file(svm_file_path)
print('Count of path list: %d' % len(path_list))

dir_path, file_name = os.path.split(svm_file_path)
name_wo_ext, ext = os.path.splitext(file_name)

X = X.toarray()
with open(os.path.join(dir_path, name_wo_ext+'_features.tsv'), 'w') as fh:
    for line in X:
        fh.write('\t'.join(str(e) for e in line))
        fh.write('\n')

with open(os.path.join(dir_path, name_wo_ext+'_label.tsv'), 'w') as fh:
    count = y.shape[0]
    print('Count of sample label: %d' % count)
    for index in range(0, count):
        fh.write('{}\t{}\n'.format(y[index], path_list[index]))
