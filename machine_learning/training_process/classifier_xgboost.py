import os
from classifier_base import *
import xgboost as xgb
from xgboost.sklearn import XGBClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import fbeta_score, make_scorer
import multiprocessing

class TMXGBTrainer(TrainerInterface):
    def __init__(self, config):
        super(self.__class__, self).__init__()
        self.config_ = config

    def train(self):
        # best params for SIE
        # best_params = {'learning_rate':0.2, 'max_depth':4, 'n_estimators':100}
        # best params for TSS
        best_params = {'learning_rate':0.6, 'max_depth':4, 'n_estimators':50}
        
        if self.config_['train']['search_best_params']:
            # searching best parameters
            param_dist = {'objective':'binary:logistic', 'n_jobs':multiprocessing.cpu_count()}
            xgb_model = XGBClassifier(param_dist)
            test_params = {
                'max_depth':[4,8,12],
                'learning_rate':[0.1,0.3,0.6,1.0],
                'n_estimators':[50,100,200]
            }
            # use f2_score as scoring
            f2_score = make_scorer(fbeta_score, beta=2)
            gs = GridSearchCV(estimator=xgb_model, param_grid=test_params, cv=5, verbose=10,\
                                 scoring = f2_score, n_jobs=1)
            # # use auc as scoring
            # gs = GridSearchCV(estimator=xgb_model, param_grid=test_params, cv=5, verbose=10,\
            #                      scoring = 'roc_auc', n_jobs=1)
            # # use f2_measure and auc as scoring
            # scoring = {'f2_measure': make_scorer(fbeta_score, beta=2), 'roc_auc': 'roc_auc'}
            # gs = GridSearchCV(estimator=xgb_model, param_grid=test_params, cv=5, verbose=10,\
            #                      scoring = scoring, refit = 'f2_measure', n_jobs=1)
            gs.fit(self.X_.toarray(), self.y_)
            print('=============== Best Results ================')
            print('best params: {}, best score: {}'.format(gs.best_params_, gs.best_score_))
            print('=============== End ================')

            best_params = gs.best_params_

        training_set = xgb.DMatrix(self.X_, self.y_)
        # parameters
        param = {'bst:max_depth': best_params['max_depth'], \
                 'bst:eta': best_params['learning_rate'], \
                 'silent': 0, \
                 'objective': 'binary:logistic'}
        # set number of parallel threads used to run xgboost            
        nthread = self.config_['model']['xgboost']['nthread']
        if self.config_['model']['xgboost']['use_system_cpu_num']:
            nthread = multiprocessing.cpu_count()
        param['nthread'] = nthread

        plst = param.items()
        plst += [('eval_metric', 'auc')]
        evallist = [(training_set, 'eval'), (training_set, 'train')]
        #
        num_round = int(best_params['n_estimators'])
        self.model_ = xgb.train(plst, training_set, num_round, evallist)

    def save_model(self, model_path):
        if model_path:
            print('get model path from parameter')
        else:
            model_path = os.path.join(self.config_['filesystem']['mid_folder'], \
                                     self.config_['model']['xgboost']['model_name'])
            print('get model path from config')
        dir_path, filename = os.path.split(model_path)
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)
        self.model_.save_model(model_path)
        print('> save model to file: {}'.format(model_path))
        return model_path



class TMXGBClassifier(ClassifierInterface):
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
            self.model_path_ = os.path.join(self.config_['filesystem']['mid_folder'], \
                                            self.config_['model']['xgboost']['model_name'])
            print('Load model from config: {}'.format(self.model_path_))
        #
        thread_num = self.config_['model']['xgboost']['nthread']
        if self.config_['model']['xgboost']['use_system_cpu_num']:
            thread_num = multiprocessing.cpu_count()
        self.model_ = xgb.Booster({'nthread': thread_num})
        self.model_.load_model(self.model_path_)

    def score(self, X, y):
        try:
            self.clear_score()
            testing_set = xgb.DMatrix(X)
            y_pred = self.model_.predict(testing_set)
            for i in range(0,y_pred.size):
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
            print('[XGBClassifier.score] Exception: {}'.format(str(e)))
