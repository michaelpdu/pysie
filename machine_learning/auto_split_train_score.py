import os
import sys
import time
from preprocess.split import *
from training_process.auto_train_score import *

# set parameters here
MAL_FEATURE_FILE = os.path.join('training_process', 'samples', 'mal.txt')
NOR_FEATURE_FILE = os.path.join('training_process', 'samples', 'nor.txt')
TESTING_FEATURE_FILE = os.path.join('training_process', 'samples', 'all.txt')
MIDDLE_DIR = 'middle_dir'

# make directory by date-time
DATE_DIR = time.strftime('%Y%m%d%H%M%S', time.gmtime())
CUR_DIR = os.path.abspath(os.path.join(MIDDLE_DIR, DATE_DIR))
if not os.path.exists(CUR_DIR):
    os.makedirs(CUR_DIR)
os.chmod(CUR_DIR, 0o777)

# split training/testing set, split from 0.1 to 1.0, step is 0.1
for p in range(1,11,1):
    p = float(p)/10

    # make sub directory by split rate
    CUR_SUB_DIR = os.path.join(CUR_DIR, 'split_rate_{}'.format(p))
    if not os.path.exists(CUR_SUB_DIR):
        os.makedirs(CUR_SUB_DIR)
    os.chmod(CUR_SUB_DIR, 0o777)

    # split to two parts of samples
    sample_selector = SplitHelper()
    sample_selector.set_kmeans_num(20)
    mal_part_a, mal_part_b = sample_selector.analyze(MAL_FEATURE_FILE, p)
    nor_part_a, nor_part_b = sample_selector.analyze(NOR_FEATURE_FILE, p)

    # merge two first parts into training set
    training_set_file = os.path.join(CUR_SUB_DIR, 'training_set.txt')
    if os.name != 'nt':
        os.system('cat {} > {}'.format(mal_part_a, training_set_file))
        os.system('cat {} >> {}'.format(nor_part_a, training_set_file))
    else:
        with open(training_set_file, "wb") as fh:
            with open(mal_part_a, "rb") as fhr:
                fh.write(fhr.read())
            with open(nor_part_a, "rb") as fhr:
                fh.write(fhr.read())

    # training and scoring
    config_file = os.path.join('training_process', 'config.json')
    auto = TrainScoreHelper(config_file)
    auto.update_middle_folder(CUR_SUB_DIR)
    auto.update_training_file(training_set_file)
    auto.append_testing_file(TESTING_FEATURE_FILE)
    #auto.append_testing_file(testing_file_2)
    auto.set_testing_file_from_config(False)
    auto.start()

