import os
import sys
import json
import time
from sklearn.datasets import load_svmlight_file
from classifier_svm import SVMTrainer
from classifier_xgboost import TMXGBTrainer
if os.name != 'nt':
    from classifier_keras import TMSAKerasTrainer
    from classifier_pylibsvm import LIBSVMTrainer


class TrainerFactory:
    """"""
    def __init__(self, config):
        self.config_ = config

    def produce(self, model_name):
        if 'svm' == model_name:
            return SVMTrainer(self.config_)
        elif 'xgboost' == model_name:
            return TMXGBTrainer(self.config_)
        elif 'libsvm' == model_name:
            if os.name != 'nt':
                return LIBSVMTrainer(self.config_)
            else:
                return None
        elif 'keras' == model_name:
            if os.name != 'nt':
                return TMSAKerasTrainer(self.config_)
            return None
        else:
            print '[ERROR] Unsupported Model Name'

class TrainerHelper:
    def __init__(self, config):
        self.config_ = config
        self.trainer_factory_ = TrainerFactory(config)

    def train(self, training_file, model_file = None):
        model_name_list = self.config_['train']['model'].split('|')
        print '[Training Process] prepare to build model: {}'.format(model_name_list)
        print '> load training file: {}'.format(training_file)
        X, y = load_svmlight_file(training_file)
        mal_num = 0
        nor_num = 0
        for item in y:
            if item == 1:
                mal_num += 1
            else:
                nor_num += 1
        print '- load complete'
        print('In training set, malicious count: {}, normal count: {}'.format(mal_num, nor_num))
        for model_name in model_name_list:
            print '> build [{}] model'.format(model_name)
            trainer = self.trainer_factory_.produce(model_name)
            trainer.set_data(X, y)
            start = time.time()
            trainer.train()
            msg = "Training Time Delta: {}".format(time.time() - start)            
            print(msg)
            model_file = trainer.save_model(model_file)
            print('Model Size: {}(bytes)'.format(os.path.getsize(model_file)))
            print('[TrainerHelper.train] Done!')


help_msg = """
Usage:
    > python train.py training-set
"""

if __name__ == '__main__':
    with open('config.json', 'rb') as fh:
        config = json.load(fh)
    helper = TrainerHelper(config)
    helper.train(sys.argv[1])
