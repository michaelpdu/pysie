import json
from train import *
from predict import *
import multiprocessing

class TrainScoreHelper(object):
    """"""
    def __init__(self, config_file):
        with open(config_file, 'rb') as fh:
            self.config_ = json.load(fh)
        self.current_mid_folder_ = self.config_['filesystem']['mid_folder']
        # if get_testing_file_from_config_ is True, it will score testing files from config
        # otherwise, it will score testing files in testing_file_list
        self.get_testing_file_from_config_ = True
        self.testing_file_list = []

    def update_middle_folder(self, new_mid_dir):
        self.config_['filesystem']['mid_folder']=new_mid_dir

    def update_training_file(self, new_training_file):
        self.config_['filesystem']['training_set'] = new_training_file

    def update_testing_file(self, new_normal_file, new_malicious_file):
        self.config_['filesystem']['testing_set_normal'] = new_normal_file
        self.config_['filesystem']['testing_set_malicious'] = new_malicious_file

    def set_testing_file_from_config(self, bool):
        self.get_testing_file_from_config_ = bool

    def append_testing_file(self, testing_file):
        self.testing_file_list.append(testing_file)

    def set_options(self, key, value):
        key_list = key.split('.')
        key_num = len(key_list)
        if key_num == 1:
            self.config_[key_list[0]] = value
        elif key_num == 2:
            self.config_[key_list[0]][key_list[1]] = value
        elif key_num == 3:
            self.config_[key_list[0]][key_list[1]][key_list[2]] = value
        else:
            print '[ERROR] Unsupported key_num in set_options'

    def prepare_env(self):
        if not os.path.exists(self.current_mid_folder_):
            os.makedirs(self.current_mid_folder_)

    def start(self):
        self.prepare_env()

        # step 1: load training set and train model by config
        training_file = self.config_['filesystem']['training_set']
        trainer_helper = TrainerHelper(self.config_)
        trainer_helper.train(training_file)
        # step 2: load model file and testing set, calculate scores
        testing_file_normal = self.config_['filesystem']['testing_set_normal']
        testing_file_malicious = self.config_['filesystem']['testing_set_malicious']
        cls_helper = ClassifierHelper(self.config_)
        if self.get_testing_file_from_config_:
            cls_helper.score(testing_file_normal)
            cls_helper.score(testing_file_malicious)
        else:
            for item in self.testing_file_list:
                cls_helper.score(item)
        # step 3: process fp/fn samples

def train_score_handler(mid_dir, training_file, testing_file, config):
    # redirect stdout and stderr to local file
    stdout_file = ''
    stderr_file = ''
    model_name = config['train.model']
    if model_name == 'svm':
        kernel = config['model.svm.kernel']
        stdout_file = os.path.join(mid_dir, '{}_{}_stdout.txt'.format(model_name, kernel))
        stderr_file = os.path.join(mid_dir, '{}_{}_stderr.txt'.format(model_name, kernel))
    else:
        stdout_file = os.path.join(mid_dir, '{}_stdout.txt'.format(model_name))
        stderr_file = os.path.join(mid_dir, '{}_stderr.txt'.format(model_name))        
    stdout_fh = open(stdout_file, 'w')
    stderr_fh = open(stderr_file, 'w')
    sys.stdout = stdout_fh
    sys.stderr = stderr_fh
    config_file = 'config.json'
    auto = TrainScoreHelper(config_file)
    auto.update_middle_folder(mid_dir)
    auto.update_training_file(training_file)
    auto.set_testing_file_from_config(False)
    auto.append_testing_file(testing_file)
    for (key, value) in config.items():
        auto.set_options(key, value)
    auto.start()
    stdout_fh.close()
    stderr_fh.close()


def train_score_in_single_process(mid_dir, training_file, testing_file):
    train_score_handler(mid_dir, training_file, testing_file, {'train.model':'svm', 
                                                               'model.svm.model_name':'svm_linear.model',
                                                               'model.svm.kernel':'linear'})
    train_score_handler(mid_dir, training_file, testing_file, {'train.model':'svm', 
                                                               'model.svm.model_name':'svm_rbf.model',
                                                               'model.svm.kernel':'rbf'})
    train_score_handler(mid_dir, training_file, testing_file, {'train.model':'xgboost'})
    train_score_handler(mid_dir, training_file, testing_file, {'train.model':'keras'})


def train_score_in_multi_process(cur_dir, training_file, testing_file):
    proc_list = []
    ## linear kernel based svm
    #proc = multiprocessing.Process(target=train_score_handler, args=(cur_dir, training_file, testing_file, \
    #                               {'train.model':'svm', 'model.svm.model_name':'svm_linear.model', 'model.svm.kernel':'linear'}))
    #proc_list.append(proc)
    ## rbf kernel based svm
    #proc = multiprocessing.Process(target=train_score_handler, args=(cur_dir, training_file, testing_file, \
    #                               {'train.model':'svm', 'model.svm.model_name':'svm_rbf.model', 'model.svm.kernel':'rbf'}))
    #proc_list.append(proc)
    ## xgboost
    #proc = multiprocessing.Process(target=train_score_handler, args=(cur_dir, training_file, testing_file, \
    #                               {'train.model':'xgboost'}))
    #proc_list.append(proc)
    # keras
    proc = multiprocessing.Process(target=train_score_handler, args=(cur_dir, training_file, testing_file, \
                                   {'train.model':'keras'}))
    proc_list.append(proc)

    for proc in proc_list:
        proc.start()
    for proc in proc_list:
        proc.join()
    print 'Train and Scorc Completely'


help_msg = """
Usage:
    python auto_train_score.py middle_dir training_file testing_file

In this script, it supports two type of mode:
(1) train_score_in_single_process
(2) train_score_in_multi_process

There are following machine learning algorithms:
(1) svm-linear
(2) svm-rbf
(3) xgboost
(4) keras

"""

if __name__ == '__main__':
    middle_dir = '/sa/middle_dir/test_auto'
    training_file = '/sa/middle_dir/20170729150002_test/training_set.txt'
    testing_file = '/sa/middle_dir/20170729150002_test/testing_set.txt'

    train_score_in_multi_process(middle_dir, training_file, testing_file)
    # train_score_in_multi_process(sys.argv[0], sys.argv[1], sys.argv[2])
