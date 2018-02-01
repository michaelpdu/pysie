# -*- coding=utf-8 -*-
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

MAL_SAMPLE_DIR = '/home/GT/sample/unzip/mal_set/'
NOR_SAMPLE_DIR = '/home/GT/sample/unzip/nor_set/'

# MAL_SAMPLE_DIR = '/home/GT/test/mal'
# NOR_SAMPLE_DIR = '/home/GT/test/nor/'


if test_status:
    MAL_SAMPLE_DIR = '/sa/sample/html/mal_test'
    NOR_SAMPLE_DIR = '/sa/sample/html/nor_test'

# DATE_DIR = time.strftime('%Y%m%d%H%M%S', time.gmtime())
# if test_status:
#    DATE_DIR += '_test'

# DATE_DIR = 'aaa'

# CUR_DIR = os.path.abspath(os.path.join(MIDDLE_DIR, DATE_DIR))

# if not os.path.exists(CUR_DIR):
#    os.makedirs(CUR_DIR)

# os.chmod(CUR_DIR, 0o777)

# MAL_FEATURE_FILE = os.path.join(CUR_DIR, 'mal_unique.txt')
# NOR_FEATURE_FILE = os.path.join(CUR_DIR, 'nor_unique.txt')

no_need_split_every_time = False
split_time = 0
for topn in range(100, 5000, 200):
    # 3. extract feature
    DATE_DIR = time.strftime('%Y%m%d%H%M%S', time.gmtime())
    CUR_DIR = os.path.abspath(os.path.join(MIDDLE_DIR, DATE_DIR))

    if not os.path.exists(CUR_DIR):
        os.makedirs(CUR_DIR)

    current_dir = os.getcwd()
    os.chmod(CUR_DIR, 0o777)
    if not no_need_split_every_time:
        MAL_FEATURE_FILE = os.path.join(CUR_DIR, 'mal_unique.txt')
        NOR_FEATURE_FILE = os.path.join(CUR_DIR, 'nor_unique.txt')

        current_dir = os.getcwd()
        working_dir = os.path.join(os.getcwd(), '../tm_pysie', 'build', 'x64')
        DLL_PATH = os.path.join(working_dir, 'libtmsie.so')
        print
        '[Change Working Dir] ' + working_dir
        sie_config_path = os.path.join(os.getcwd(), '../pysie', 'pysie.cfg')
        os.chdir(working_dir)
        cmd = 'python ../../py_talos.py --dllpath="{}" --label=1 --samplepath="{}" --out="{}" --configpath="{}" --topn="{}"'.format(
            DLL_PATH, MAL_SAMPLE_DIR, MAL_FEATURE_FILE, sie_config_path, topn)
        print
        '[Extract Feature] ' + cmd
        os.system(cmd)
        cmd = 'python ../../py_talos.py --dllpath="{}" --label=0 --samplepath="{}" --out="{}" --configpath="{}" --topn="{}" '.format(
            DLL_PATH, NOR_SAMPLE_DIR, NOR_FEATURE_FILE, sie_config_path, topn)
        print
        '[Extract Feature] ' + cmd
        os.system(cmd)
        os.chdir(current_dir)

    # 4. split training/testing set
    if not no_need_split_every_time:
        print
        'now split feature file'
        working_dir = os.path.join(os.getcwd(), 'preprocess')
        print
        '[Change Working Dir] ' + working_dir
        os.chdir(working_dir)
        mal_split_rate = 0.7
        nor_split_rate = 0.7
        cmd = 'python split.py {} {}'.format(MAL_FEATURE_FILE, mal_split_rate)
        print
        '[Split Set] ' + cmd
        os.system(cmd)
        cmd = 'python split.py {} {}'.format(NOR_FEATURE_FILE, nor_split_rate)
        print
        '[Split Set] ' + cmd
        os.system(cmd)
        os.chdir(current_dir)
        # 5. build training set
        parent_dir, filename = os.path.split(MAL_FEATURE_FILE)
        filename_wo_ext, ext = os.path.splitext(filename)
        mal_part_a = os.path.join(parent_dir, filename_wo_ext + '_random_{}_group_a{}'.format(mal_split_rate, ext))
        mal_part_b = os.path.join(parent_dir, filename_wo_ext + '_random_{}_group_b{}'.format(mal_split_rate, ext))

        parent_dir, filename = os.path.split(NOR_FEATURE_FILE)
        filename_wo_ext, ext = os.path.splitext(filename)
        nor_part_a = os.path.join(parent_dir, filename_wo_ext + '_random_{}_group_a{}'.format(nor_split_rate, ext))
        nor_part_b = os.path.join(parent_dir, filename_wo_ext + '_random_{}_group_b{}'.format(nor_split_rate, ext))

        training_set_file = os.path.join(CUR_DIR, 'training_set.txt')
        testing_set_file = os.path.join(CUR_DIR, 'testing_set.txt')

        os.system('cat {} > {}'.format(mal_part_a, training_set_file))
        os.system('cat {} >> {}'.format(nor_part_a, training_set_file))
        os.system('cat {} >> {}'.format(nor_part_b, testing_set_file))
        os.system('cat {} > {}'.format(mal_part_b, testing_set_file))

    training_set_file = os.path.join(current_dir, 'middle_dir', 'split_feature', 'training.txt')
    testing_set_file = os.path.join(current_dir, 'middle_dir', 'split_feature', 'testing.txt')
    # 6. training and scoring
    print
    'training set:', training_set_file
    print
    'testing set:', testing_set_file

    working_dir = os.path.join(current_dir, 'training_process')
    train_score_in_multi_process(CUR_DIR, training_set_file, testing_set_file)
    os.chdir(current_dir)
