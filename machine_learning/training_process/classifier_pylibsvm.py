import os
import sys
sys.path.append('/sa/githubee/md_auto_tools/third_party/wrappers/pylibsvm/')
from classifier_base import *
from svmutil import *
from scipy.sparse import csr_matrix
import numpy as np

class LIBSVMTrainer(TrainerInterface):
    def __init__(self, config):
        super(self.__class__, self).__init__()
        self.config_ = config

    def set_data(self, X, y):
        self.X_=[]
        for i in range(0,X.shape[0]):
            m=X.getrow(i)
            n=csr_matrix.todok(m)
            dict = {}
            for k, v in n.iteritems():
                dict[k[1]] = float(v)
            self.X_.append(dict)
        self.y_ = np.ndarray.tolist(y)

    def train(self):
        self.model_ = svm_train(self.y_, self.X_, '-t 0 -c 4 -h 0')

    def save_model(self, model_path = None):
        if model_path:
            print('get model path from parameter')
        else:
            model_path = os.path.join(self.config_['filesystem']['mid_folder'],self.config_['model']['libsvm']['model_name'])
            print('get model path from config')
        dir_path, filename = os.path.split(model_path)
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)
        svm_save_model(model_path, self.model_)
        print '> save model to file: {}'.format(model_path)




class LIBSVMClassifier(ClassifierInterface):
    def __init__(self, config):
        super(self.__class__, self).__init__(config)
        self.config_ = config
        self.model_path_ = ''
        self.model_ = None
        
    def load_model(self, model_path = None):
        if model_path and os.path.exists(model_path):
            print('Load model from parameter: {}'.format(model_path))
            self.model_path_ = model_path
        else:
            self.model_path_ = os.path.join(self.config_['filesystem']['mid_folder'], self.config_['model']['libsvm']['model_name'])
            print('Load model from config: {}'.format(self.model_path_))
        self.model_ = svm_load_model(self.model_path_)

    def score(self, X, y):
        X_=[]
        for i in range(0,X.shape[0]):
            m=X.getrow(i)
            n=csr_matrix.todok(m)
            dict = {}
            for k, v in n.iteritems():
                dict[k[1]] = float(v)
            X_.append(dict)
        y_ = np.ndarray.tolist(y)
        try:
            self.clear_score()
            y_pred,y_acc,y_vals = svm_predict(y_,X_,self.model_)
            for i in range(0, len(y_pred)):
                if y_pred[i] >= 0.5 and y[i] == 1:
                    self.tp_ += 1
                    self.tpl_.append(i)
                elif y_pred[i] < 0.5 and y[i] == 0:
                    self.tn_ += 1
                    self.tnl_.append(i)
                elif y_pred[i] >= 0.5 and y[i] == 0:
                    self.fp_ += 1
                    self.fpl_.append(i)
                else:
                    self.fn_ += 1
                    self.fnl_.append(i)
            return self.tpl_, self.tnl_, self.fpl_, self.fnl_
        except Exception, e:
            print 'Exception: {}'.format(str(e))
