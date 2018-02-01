import os
import sys
import time

test_status = True
# set parameters here
MAL_SAMPLE_DIR = '/sa/sample/html/unique/malicious'
NOR_SAMPLE_DIR = '/sa/sample/html/unique/normal'
if test_status:
    MAL_SAMPLE_DIR = '/sa/sample/html/mal_test'
    NOR_SAMPLE_DIR = '/sa/sample/html/nor_test'
MIDDLE_DIR = '/data2/middle_dir'

# make directory by date-time
DATE_DIR = time.strftime('%Y%m%d%H%M%S', time.gmtime())
if test_status:
    DATE_DIR += '_test'

CUR_DIR = os.path.abspath(os.path.join(MIDDLE_DIR, DATE_DIR))
if not os.path.exists(CUR_DIR):
    os.makedirs(CUR_DIR)
os.chmod(CUR_DIR, 0o777)

CUR_DIR = os.path.abspath(os.path.join(MIDDLE_DIR, DATE_DIR))
if not os.path.exists(CUR_DIR):
    os.makedirs(CUR_DIR)
os.chmod(CUR_DIR, 0o777)

MAL_FEATURE_FILE = os.path.join(CUR_DIR, 'mal_unique.txt')
NOR_FEATURE_FILE = os.path.join(CUR_DIR, 'nor_unique.txt')

# extract feature
working_dir = os.path.join('..','pysie')
print '[Change Working Dir] '+working_dir
os.chdir(working_dir)

cmd = 'python pysie.py --dump-feature="{}" --label=1 --dest-file="{}"'.format(MAL_SAMPLE_DIR, MAL_FEATURE_FILE)
print '[Extract Feature] '+cmd
os.system(cmd)
cmd = 'python pysie.py --dump-feature="{}" --label=0 --dest-file="{}"'.format(NOR_SAMPLE_DIR, NOR_FEATURE_FILE)
print '[Extract Feature] '+cmd
os.system(cmd)

# split training/testing set
working_dir = os.path.join('..','machine_learning','preprocess')
print '[Change Working Dir] '+working_dir
os.chdir(working_dir)

mal_split_rate = 0.7
nor_split_rate = 0.7
cmd = 'python split.py {} {}'.format(MAL_FEATURE_FILE, mal_split_rate)
print '[Split Set] '+ cmd
os.system(cmd)
cmd = 'python split.py {} {}'.format(NOR_FEATURE_FILE, nor_split_rate)
print '[Split Set] '+ cmd
os.system(cmd)