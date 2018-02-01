import os
import sys
import time
import json
from file_helper import *
from sklearn.datasets import load_svmlight_file
from classifier_svm import SVMClassifier
from classifier_xgboost import TMXGBClassifier
from sklearn.metrics import roc_auc_score
if os.name != 'nt':
    from classifier_keras import TMSAKerasClassifier
    from classifier_pylibsvm import LIBSVMClassifier


class ClassifierFactory:
    """"""
    def __init__(self, config):
        self.config_ = config

    def produce(self, model_name):
        if 'svm' == model_name:
            classifier = SVMClassifier(self.config_)
            classifier.load_model()
            return classifier
        elif 'xgboost' == model_name:
            classifier = TMXGBClassifier(self.config_)
            classifier.load_model()
            return classifier
        elif 'libsvm' == model_name:
            if os.name != 'nt':
                classifier = LIBSVMClassifier(self.config_)
                classifier.load_model()
                return classifier
            else:
                return None
        elif 'keras' == model_name:
            if os.name != 'nt':
                classifier = TMSAKerasClassifier(self.config_)
                classifier.load_model()
                return classifier
            else:
                return None
        else:
            print '[ERROR] Unsupported Model Name'

class ClassifierHelper:
    def __init__(self, config):
        self.config_ = config
        self.classifier_factory_ = ClassifierFactory(config)

    def score(self, testing_file):
        try:
            file_helper = FileHelper()
            model_name_list = self.config_['train']['model'].split('|')
            print '[Prediction Process] model list: {}'.format(model_name_list)
            print '> load testing file: {}'.format(testing_file)
            X, y = load_svmlight_file(testing_file)
            print '- load complete'
            for model_name in model_name_list:
                test_filename = os.path.splitext(os.path.split(testing_file)[1])[0]
                print '> calculate scores using [{}] model'.format(model_name)
                tpl = tnl = fpl = fnl = []
                classifier = self.classifier_factory_.produce(model_name)
                start = time.time()
                (tpl, tnl, fpl, fnl, y_pred) = classifier.score(X,y)
                msg = "Scoring Time Delta: {}".format(time.time() - start)
                print(msg)
                #
                tp = len(tpl)
                tn = len(tnl)
                fp = len(fpl)
                fn = len(fnl)
                msg = "TP:{}, TN:{}, FP:{}, FN:{}".format(tp, tn, fp, fn)
                print(msg)
                #
                accuracy = float(tp+tn)/(tp+tn+fp+fn)
                if 0 == tp+fp:
                    precision = 0
                else:
                    precision = float(tp)/(tp+fp)
                if 0 == tp+fn:
                    recall = 0
                else:
                    recall = float(tp)/(tp+fn)
                if 0 == fp+tn:
                    fpr = 0
                else:
                    fpr = float(fp)/(fp+tn)
                fdr = 1-precision
                f1 = None
                try:
                    f1 = float(2*tp)/(2*tp+fp+fn)
                except Exception,e:
                    print('[ClassifierHelper.score] Exception in f1: {}'.format(str(e)))
                f2 = None
                try:
                    f2 = 5*precision*recall/(4*precision+recall)
                except Exception,e:
                    print('[ClassifierHelper.score] Exception in f2: {}'.format(str(e)))
                auc = None
                try:
                    auc = roc_auc_score(y, y_pred)
                except Exception,e:
                    print('[ClassifierHelper.score] Exception in roc_auc_score: {}'.format(str(e)))
                msg = "Accuracy:{}, Precision(PPV):{}, Recall:{}, FPR(FP1):{}, FDR(FP2|1-PPV):{}, F1-Measure:{}, F2-Measure:{}, AUC:{}".format(\
                    accuracy, precision, recall, fpr, fdr, f1, f2, auc)
                print(msg)
                print '> save false prediction result'
                path_wo_ext, ext = os.path.splitext(testing_file)
                file_dir, file_name = os.path.split(path_wo_ext)
                if model_name == 'svm':
                    model_name += '_{}'.format(self.config_['model']['svm']['kernel'])
                fpl_file = os.path.join(self.config_['filesystem']['mid_folder'], '{}_{}_fpl{}'.format(file_name, model_name, ext))
                file_helper.backup_lines_by_index(testing_file, fpl, fpl_file)
                print(fpl_file)
                fnl_file = os.path.join(self.config_['filesystem']['mid_folder'], '{}_{}_fnl{}'.format(file_name, model_name, ext))
                file_helper.backup_lines_by_index(testing_file, fnl, fnl_file)
                print(fnl_file)
        except Exception, e:
            print '[ClassifierHelper.score] Exception: {}'.format(str(e))
        print 'Done!'


help_msg = """
Usage:
    > python predict.py testing-file
"""

if __name__ == '__main__':
    with open('config.json', 'rb') as fh:
        config = json.load(fh)
    helper = ClassifierHelper(config)
    helper.score(sys.argv[1])
