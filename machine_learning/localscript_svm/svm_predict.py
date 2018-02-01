# auther = Cheng Chang(SA)
# Date = 2016/12/29
import os
import sys
import shutil
import csv
from sklearn.externals import joblib
from feature_extractor import FeatureExtractor
from third_party.wrappers.salineup_wrapper.salineup_wrapper import SALineupWrapper
from sklearn.metrics import classification_report


class SVMPrediction:
    """
    """
    def __init__(self):
        self.root_path_ = os.path.split(os.path.realpath(__file__))[0]
        self.model_path_ = os.path.join(self.root_path_, 'test.pkl')
        self.clf_ = joblib.load(self.model_path_)
        self.fte_ = FeatureExtractor()
        self.sal_ = SALineupWrapper()
        self.sal_opt_args_ = ' --productname=sc --script-malware=true --loglevel=all'
        self.sal_path_ = os.path.join(self.sal_.get_path(), 'salineup')
        self.behavior_path_ = os.path.join(self.root_path_, 'behavior')

    def check_env(self):
        return True

    def clear_env(self):
        self.sal_.clear_env()
        if os.path.exists(self.behavior_path_):
            shutil.rmtree(self.behavior_path_)
        csv_path = os.path.join(self.root_path_, 'summary.csv')
        if os.path.exists(csv_path):
            os.remove(csv_path)

    def process_file(self, file_path):
        self.scan(file_path)
        self.move_behavior()
        self.predict_single()

    def process_dir(self, dir_path):
        self.scan(dir_path)
        self.move_behavior()
        self.predict_dir()

    def scan(self, js_path):
        # sal
        self.sal_.scan_file(self.sal_opt_args_, js_path)

    def move_behavior(self):
        # move behavior to the current path
        behavior_path = os.path.join(self.sal_path_, 'result')
        try:
            shutil.move(behavior_path, self.behavior_path_)
        except Exception as e:
            raise e

    def predict_single(self):
        behavior = os.path.join(self.behavior_path_, os.listdir(self.behavior_path_)[0])
        data = self.fte_.get_data(xml_path=behavior)
        if int(self.clf_.predict([data])[0]) == 1:
            print 'Malicious'
        else:
            print 'Normal'

    def predict_dir(self, behavior_dir_path='', sum_name=''):
        if behavior_dir_path == '':
            behavior_dir_path = self.behavior_path_
        result_list = []
        mal_count = 0
        nor_count = 0
        for behavior in os.listdir(behavior_dir_path):
            behavior_path = os.path.join(behavior_dir_path, behavior)
            try:
                sha1 = self.fte_.get_sha1(behavior_path)
                data = self.fte_.get_data(xml_path=behavior_path)
            except Exception as e:
                print behavior
                print e
                continue
            if int(self.clf_.predict([data])[0]) == 1:
                result_list.append((sha1, 'M'))
                mal_count += 1
            else:
                result_list.append((sha1, 'N'))
                nor_count += 1

        print '''
------------------------------
Total = %s
Malicious = %s
Normal = %s''' % (mal_count + nor_count, mal_count, nor_count)

        self.dump_summary(result_list, sum_name)

    def classify_analysis(self, behavior_dir_path='', y_true=None):
        if behavior_dir_path == '':
            behavior_dir_path = self.behavior_path_
        y_pred = []
        for behavior in os.listdir(behavior_dir_path):
            behavior_path = os.path.join(behavior_dir_path, behavior)
            data = self.fte_.get_data(xml_path=behavior_path)
            y_pred.append(data)
        y_pred = self.clf_.predict(y_pred)
        # anaylsis
        if y_true is None:
            y_true = [0] * len(y_pred)
        target_names = ['Normal', 'Malicious']
        print classification_report(y_true, y_pred, target_names=target_names)

    def dump_summary(self, result_list, sum_name=''):
        if not sum_name:
            sum_name = 'summary.csv'
        csv_file_ = os.path.join(self.root_path_, sum_name)
        with open(csv_file_, 'wb') as csv_file:
            writer = csv.writer(csv_file)
            writer.writerow(['SHA1', 'DECISION'])
            for row in result_list:
                writer.writerow(row)


def print_help():
    print """
Usage:
    python svm_predict.py target

Predict sample by linear-svm
    """


def main():
    if len(sys.argv) < 2:
        print_help()
        exit(-1)
    svm_prediction = SVMPrediction()
    if not svm_prediction.check_env():
        exit(-1)
    svm_prediction.clear_env()
    target = sys.argv[1]
    if target.endswith('result'):
        svm_prediction.predict_dir(target, sys.argv[2])
        # svm_prediction.classify_analysis(target)
    elif os.path.isfile(target):
        svm_prediction.process_file(target)
    elif os.path.isdir(target):
        svm_prediction.process_dir(target)


if __name__ == '__main__':
    main()
