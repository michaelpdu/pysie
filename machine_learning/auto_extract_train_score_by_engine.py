import os, time
import sys
sys.path.append('../../third_party/wrappers/pylibsvm/')
from svmutil import *
from training_process.auto_train_score import *

# 1. rename log
log_file = 'auto.log'
if os.path.exists(log_file):
    os.rename(log_file, 'auto_{}.log'.format(time.strftime('%Y%m%d', time.gmtime())))


# 2. prepare environment
test_status = False

MIDDLE_DIR = 'middle_dir'

MAL_SAMPLE_DIR = '/sa/sample/html/unique/malicious'
NOR_SAMPLE_DIR = '/sa/sample/html/unique/normal'

if test_status:
    MAL_SAMPLE_DIR = '/sa/sample/html/mal_test'
    NOR_SAMPLE_DIR = '/sa/sample/html/nor_test'


DATE_DIR = time.strftime('%Y%m%d%H%M%S', time.gmtime())
if test_status:
    DATE_DIR += '_test'

# DATE_DIR = 'aaa'

CUR_DIR = os.path.abspath(os.path.join(MIDDLE_DIR, DATE_DIR))

if not os.path.exists(CUR_DIR):
    os.makedirs(CUR_DIR)

os.chmod(CUR_DIR, 0o777)

MAL_FEATURE_FILE = os.path.join(CUR_DIR, 'mal_unique.txt')
NOR_FEATURE_FILE = os.path.join(CUR_DIR, 'nor_unique.txt')

# 3. extract feature
working_dir = os.path.join(os.getcwd(),'tm_pysie','build','x64')
DLL_PATH = os.path.join(working_dir, 'libtmsie.so')

print '[Change Working Dir] '+working_dir
os.chdir(working_dir)
cmd = 'python ../../py_talos.py --dllpath="{}" --label=1 --samplepath="{}" --out="{}"'.format(DLL_PATH, MAL_SAMPLE_DIR, MAL_FEATURE_FILE)
print '[Extract Feature] '+cmd
os.system(cmd)
cmd = 'python ../../py_talos.py --dllpath="{}" --label=0 --samplepath="{}" --out="{}"'.format(DLL_PATH, NOR_SAMPLE_DIR, NOR_FEATURE_FILE)
print '[Extract Feature] '+cmd
os.system(cmd)

# 4. split training/testing set
working_dir = os.path.join(os.getcwd(), 'machine_learning','preprocess')
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

# 5. build training set
parent_dir, filename = os.path.split(MAL_FEATURE_FILE)
filename_wo_ext, ext = os.path.splitext(filename)
mal_part_a = os.path.join(parent_dir, filename_wo_ext+'_random_{}_group_a{}'.format(mal_split_rate,ext))
mal_part_b = os.path.join(parent_dir, filename_wo_ext+'_random_{}_group_b{}'.format(mal_split_rate,ext))

parent_dir, filename = os.path.split(NOR_FEATURE_FILE)
filename_wo_ext, ext = os.path.splitext(filename)
nor_part_a = os.path.join(parent_dir, filename_wo_ext+'_random_{}_group_a{}'.format(nor_split_rate,ext))
nor_part_b = os.path.join(parent_dir, filename_wo_ext+'_random_{}_group_b{}'.format(nor_split_rate,ext))

training_set_file = os.path.join(CUR_DIR, 'training_set.txt')

os.system('cat {} > {}'.format(mal_part_a, training_set_file))
os.system('cat {} >> {}'.format(nor_part_a, training_set_file))

# 6. training and scoring
working_dir = os.path.join('..','training_process')
print '[Change Working Dir] '+working_dir
os.chdir(working_dir)

config_file = 'config.json'
auto = TrainScoreHelper(config_file)
auto.update_middle_folder(CUR_DIR)
auto.update_training_file(training_set_file)
auto.update_testing_file(nor_part_b, mal_part_b)
auto.start()

