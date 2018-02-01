import os,time
from classifier_base import *
from sklearn import svm
import pickle
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import fbeta_score, make_scorer
import multiprocessing
from svmutil import *
from scipy.sparse import csr_matrix
import numpy as np

class SVMTrainer(TrainerInterface):
    def __init__(self, config):
        super(self.__class__, self).__init__()
        self.config_ = config
        self.kernel_type_ = self.config_['model']['svm']['kernel']
        self.model_filename_ = ''

    def change_data_format(self, X, y):
        print('convert data for libsvm utility')
        start = time.time()
        X_tmp =[]
        for i in range(0,X.shape[0]):
            m=X.getrow(i)
            n=csr_matrix.todok(m)
            dict = {}
            for k, v in n.iteritems():
                dict[k[1]] = float(v)
            X_tmp.append(dict)
        y_tmp = np.ndarray.tolist(y)
        self.X_ = X_tmp
        self.y_ = y_tmp
        print('Convert Time: {}'.format(time.time()-start))

    def set_kernel_type(self, k_type):
        if k_type == 'rbf':
            self.kernel_type_ = 'rbf'
            self.model_filename_ = 'svm_rbf.model'
        else:
            self.kernel_type_ = 'linear'
            self.model_filename_ = 'svm_linear.model'

    def train(self):
        best_params = {'C': 4, 'gamma': 1}
        if self.config_['train']['search_best_params']:
            libsvm_model = svm.SVC(kernel=self.kernel_type_)
            test_params = {
                'C': [2**x for x in range(-5,5,2)]
            }
            if self.kernel_type_ == 'linear':
                pass
            elif self.kernel_type_ == 'rbf':
                test_params['gamma'] = [2**x for x in range(-8,8,2)]
            else:
                print '[ERROR] Unsupported kernel_type in SVMTrainer.train' 
                return

            # use f2_score as scoring
            f2_score = make_scorer(fbeta_score, beta=2)
            gs = GridSearchCV(estimator=libsvm_model, param_grid=test_params, cv=5, verbose=10,\
                                 scoring = f2_score, n_jobs=multiprocessing.cpu_count())
            # # use auc as scoring
            # gs = GridSearchCV(estimator=libsvm_model, param_grid=test_params, cv=5, verbose=10,\
            #                      scoring = 'roc_auc', n_jobs=multiprocessing.cpu_count())
            # # use f2_measure and auc as scoring
            # scoring = {'f2_measure': make_scorer(fbeta_score, beta=2), 'roc_auc': 'roc_auc'}
            # gs = GridSearchCV(estimator=libsvm_model, param_grid=test_params, cv=5, verbose=10,\
            #                      scoring = scoring, refit = 'f2_measure', n_jobs=multiprocessing.cpu_count())
            gs.fit(self.X_, self.y_)

            print('=============== Best Results ================')
            print('best params: {}, best score: {}'.format(gs.best_params_, gs.best_score_))
            print('=============== End ================')

            best_params = gs.best_params_
        
        self.change_data_format(self.X_,self.y_)
        if self.kernel_type_ == 'linear':
            cmd = ['-t',0,'-c',best_params['C']]
            self.model_ = svm_train(self.y_,self.X_,cmd)
        elif self.kernel_type_ == 'rbf':
            cmd = ['-t',2,'-c',best_params['C'],'-g',best_params['gamma']]
            self.model_ = svm_train(self.y_,self.X_,cmd)
        else:
            pass

    def save_model(self, model_path = None):
        if model_path:
            print('get model path from parameter')
        else:
            if self.model_filename_ == '':
                self.model_filename_ = self.config_['model']['svm']['model_name']
            model_path = os.path.join(self.config_['filesystem']['mid_folder'], self.model_filename_)
            print('get model path from config')
        dir_path, filename = os.path.split(model_path)
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)
        svm_save_model(model_path,self.model_)
#        pickle.dump(self.model_, open(model_path, 'wb'))
        print('> save model to file: {}'.format(model_path))
        return model_path




class SVMClassifier(ClassifierInterface):
    def __init__(self, config):
        super(self.__class__, self).__init__(config)
        self.config_ = config
        self.model_path_ = ''
        self.model_ = None
        self.target_filename_ = ''
        self.kernel_type_ = 'linear'
        self.model_filename_ = ''

    def set_kernel_type(self, k_type):
        if k_type == 'rbf':
            self.kernel_type_ = 'rbf'
            self.model_filename_ = 'svm_rbf.model'
        else:
            self.kernel_type_ = 'linear'
            self.model_filename_ = 'svm_linear.model'

    def load_model(self, model_path = None):
        if model_path and os.path.exists(model_path):
            print('Load model from parameter: {}'.format(model_path))
            self.model_path_ = model_path
        else:
            if self.model_filename_ == '':
                self.model_filename_ = self.config_['model']['svm']['model_name']
            self.model_path_ = os.path.join(self.config_['filesystem']['mid_folder'], self.model_filename_)
            print('Load model from config: {}'.format(self.model_path_))
        self.model_ = svm_load_model(self.model_path_)
#        self.model_ = pickle.load(open(self.model_path_, 'rb'))

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
            return self.tpl_, self.tnl_, self.fpl_, self.fnl_, y_pred
        except Exception, e:
            print('[SVMClassifier.score] Exception: {}'.format(str(e)))

