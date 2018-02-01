# auther = Cheng Chang(SA)
# Date = 2016/12/29
import os
import sys
import re
import yara
import pickle
import numpy as np
import time
import csv
import xml.etree.cElementTree as ET
from sklearn import svm
from sklearn.externals import joblib
from sklearn import random_projection
from numpy import array,zeros
# from lxml import etree
# fix utf-8 decode problem
reload(sys)
sys.setdefaultencoding('utf-8')


class FeatureExtractor:
    """
    """
    def __init__(self):
        self.root_path_ = os.path.split(os.path.realpath(__file__))[0]
        self.sr_path_ = os.path.join(self.root_path_, 'static_raw_.yar')
        self.em_path_ = os.path.join(self.root_path_, 'emulation_.yar')
        self.sr_ = None
        self.em_ = None
        self.raw_rules_names_ = []
        self.emulation_rules_names_ = []
        self.data = []
        self.target = []
        self.npd = None
        self.npt = None
        self.preprocess()

    def preprocess(self):
        # compile yara
        self.sr_ = yara.compile(self.sr_path_)
        self.em_ = yara.compile(self.em_path_)        
        # extract rule names
        with open(self.sr_path_, 'r') as static_file:
            s = static_file.read()
            self.raw_rules_names_ = re.findall(r'rule\s*([\w\_]*)', s)
        with open(self.em_path_, 'r') as emulation_file:
            s = emulation_file.read()
            self.emulation_rules_names_ = re.findall(r'rule\s*([\w\_]*)', s)

    def get_root(self, xml_path):
        try:
            return ET.parse(xml_path).getroot()
            # ERROR!not well-formed (invalid token)
            # parser = ET.XMLParser(encoding="utf-8")
            # return ET.parse(xml_path, parser).getroot()
            # fix decode problem
            # parser = etree.XMLParser(recover=True)
            # xml_str = open(xml_path).read()
            # etree.fromstring(xml_str, parser=parser)
            # root_ = etree.Element("root")
        except Exception as e:
            raise e

    def learning(self, m_path_list, n_path_list):
        for path in m_path_list:
            for f in os.listdir(path):
                file = os.path.join(path, f)
                try:
                    self.process_sample(file, 1)
                except Exception as e:
                    print file
                    print e
        for path in n_path_list:
            for f in os.listdir(path):
                file = os.path.join(path, f)
                try:
                    self.process_sample(file, 0)
                except Exception as e:
                    print file
                    print e
        self.dump_npdata()
        self.dump_model(kernel='linear')

    def process_sample(self, xml_path, flag=-1):
        root_ = self.get_root(xml_path)
        self.extract_feature(root_)
        self.extract_decision(root_, flag)

    def extract_feature(self, root_):
        d = self.get_data(root_=root_)
        self.data.append(d)

    def match2str(self, matches):
        m = []
        for x in matches:
            m.append(str(x))
        return m

    def extract_decision(self, root_, flag = -1):
        if flag == -1:
            for e in root_:
                if e.tag == 'decision':
                    if e.text == 'Malicious':
                        self.target.append(1)
                    else:
                        self.target.append(0)
        else:
            self.target.append(flag)

    def collect_other_feature(self, d, static_raw_, static_obfuscate_, emulation_):
        # other feature
        # have obfuscate
        if len(static_obfuscate_) != 0:
            d.append(1.)
        else:
            d.append(0.)
        # obfuscate num > 1
        if js_tag_flag > 2:
            d.append(1.)
        else:
            d.append(0.)
        # have emlulation
        if len(emulation_) != 0:
            d.append(1.)
        else:
            d.append(0.)
        return d

    def get_data(self, root_=None, xml_path='',debug=False):
        if root_ is None:
            root_ = self.get_root(xml_path)
        static_raw_ = ''
        static_obfuscate_ = ''
        emulation_ = ''
        js_tag_flag = 0
        jsb_tag_flag = 0
        for e in root_:
            if e.tag == 'evidence':
                if e.attrib['type']=='javascript':
                    if js_tag_flag == 0:
                        static_raw_ = e[-1].text
                    elif js_tag_flag > 0:
                        static_obfuscate_ += e[-1].text
                    js_tag_flag += 1
                if e.attrib['type']=='javascript_behavior':
                    if jsb_tag_flag >= 0:
                        emulation_ += e[-1].text
                    jsb_tag_flag += 1
        d = []
        matches = self.match2str(self.sr_.match(data=static_raw_ + static_obfuscate_))
        if debug is True:
            print matches
        for f in self.raw_rules_names_:
            if f in matches:
                d.append(1.)
            else:
                d.append(0.)
        if len(emulation_) != 0:
            matches = self.match2str(self.em_.match(data=emulation_))
            if debug is True:
                print matches
            for f in self.emulation_rules_names_:
                if f in matches:
                    d.append(1.)
                else:
                    d.append(0.)
        else:
            d += [0.] * len(self.emulation_rules_names_)
        d = self.collect_other_feature(d, static_raw_, static_obfuscate_, emulation_)
        return d

    def get_sha1(self, xml_path):
        root_ = self.get_root(xml_path)
        for e in root_:
            if e.tag == 'file_path':
                self.file_path = e.text
                return os.path.splitext(os.path.split(self.file_path)[1])[0]

    def get_decision(self, xml_path):
        root_ = self.get_root(xml_path)
        for e in root_:
            if e.tag == 'decision':
                if e.text == 'Malicious':
                    return 'Malicious'
                else:
                    return 'Normal'

    def dump_npdata(self):
        X_digits = np.array(self.data, dtype=np.float64, order='C') ###
        y_digits = np.array(self.target, dtype=np.float64, order='C')
        self.npd = X_digits
        self.npt = y_digits
        t = time.strftime("%m%d")
        if os.path.exists(r'npdata_%s.pkl' % t):
            t += 'x'
        pickle.dump(X_digits, open(r'npdata_%s.pkl' % t, 'wb'), -1)
        pickle.dump(y_digits, open(r'nptarget_%s.pkl' % t, 'wb'), -1)

    def dump_model(self, kernel='linear'):
        clf = svm.SVC(kernel='linear', C=5, class_weight='balanced', cache_size=1000)
        clf.fit(self.npd, self.npt)
        print clf.get_params()
        t = time.strftime("%m%d")
        with open(r'svc_model_params_%s.cfg' % t, 'w') as p:
            p.write(time.ctime() + '\n')
            p.write('static_raw_rules_num = %s\n' % len(self.raw_rules_names_))
            p.write('emulation_rules_num = %s\n' % len(self.emulation_rules_names_))
            p.write('data size = %s\n' % len(self.target))
            p.write(str(clf.get_params()))
        if os.path.exists(r'balanced_linear_svc_model_%s.pkl' % t):
            t +='x'
        joblib.dump(clf, r'balanced_linear_svc_model_%s.pkl' % t)

    def dev(self, xml_path='', boo='M'):
        root_ = self.get_root(xml_path)
        static_raw_ = ''
        static_obfuscate_ = ''
        emulation_ = ''
        js_tag_flag = 0
        jsb_tag_flag = 0
        for e in root_:
            if e.tag == 'evidence':
                if e.attrib['type']=='javascript':
                    if js_tag_flag == 0:
                        static_raw_ = e[-1].text
                    elif js_tag_flag > 0:
                        static_obfuscate_ += e[-1].text
                    js_tag_flag += 1
                if e.attrib['type']=='javascript_behavior':
                    if jsb_tag_flag >= 0:
                        emulation_ += e[-1].text
                    jsb_tag_flag += 1

        if js_tag_flag != 1:
            print xml_path
        # d = []
        # matches1 = self.match2str(self.sr_.match(data=static_raw_ + static_obfuscate_))
        # for f in self.raw_rules_names_:
        #     if f in matches1:
        #         d.append(1)
        #     else:
        #         d.append(0)
        # if len(emulation_) != 0:
        #     matches2 = self.match2str(self.em_.match(data=emulation_))
        #     for f in self.emulation_rules_names_:
        #         if f in matches2:
        #             d.append(1)
        #         else:
        #             d.append(0)
        # else:
        #     d += [0] * len(self.emulation_rules_names_)
        # return d

    def find_pattern(self):
        pass

def get_data(xml_path):
    feaExtractor = FeatureExtractor()
    print feaExtractor.get_data(xml_path=xml_path, debug=True)

def get_dev(xml_path):
    feaExtractor = FeatureExtractor()
    print feaExtractor.dev(xml_path=xml_path)

def rule_evaluation(rule_num=150):
    m1 = r'D:\BaseSampleSet\malicious_result\amresult'
    m2 = r'D:\BaseSampleSet\malicious_result\atseresult'
    m3 = r'D:\BaseSampleSet\malicious_result\ccresult'
    m4 = r'D:\BaseSampleSet\malicious_result\ersresult'
    m5 = r'D:\BaseSampleSet\malicious_result\vt2result'
    n1 = r'D:\BaseSampleSet\normal_result\atseresult'
    n2 = r'D:\BaseSampleSet\normal_result\ccresult'
    n3 = r'D:\BaseSampleSet\normal_result\houxresult'
    # m_path_list = [m1,m2,m3,m4,m5]
    # n_path_list = [n1,n2,n3]
    m_path_list = [r'D:\sal_1\result']
    feaExtractor = FeatureExtractor()
    # csv
    # writer = csv.writer(open('mal.csv', 'wb'))
    for dir in m_path_list:
        for behavior in os.listdir(dir):
            p = os.path.join(dir, behavior)
            try:
                feaExtractor.dev(xml_path=p, boo='M')
                # writer.writerow(d)
            except Exception as e:
                print behavior
                print e
    # writer = csv.writer(open('nor.csv', 'wb'))
    for dir in n_path_list:
        for behavior in os.listdir(dir):
            p = os.path.join(dir, behavior)
            try:
                feaExtractor.dev(xml_path=p, boo='N')
                # writer.writerow(d)
            except Exception as e:
                print behavior
                print e

def train_model():
    X_digits = pickle.load(open('npdata_0104.pkl', 'rb'))
    y_digits = pickle.load(open('nptarget_0104.pkl', 'rb'))
    clf = svm.SVC(kernel='linear', C=8, class_weight='balanced', cache_size=1000)
    clf.fit(X_digits, y_digits)
    print clf.get_params()
    joblib.dump(clf, 'test.pkl')


def test():
    feaExtractor = FeatureExtractor()
    print len(feaExtractor.raw_rules_names_)
    print len(feaExtractor.emulation_rules_names_)


def main():
    m1 = r'E:\BaseSampleSet\malicious_result\amresult'
    m2 = r'E:\BaseSampleSet\malicious_result\atseresult'
    m3 = r'D:\BaseSampleSet\malicious_result\ccresult'
    m4 = r'D:\BaseSampleSet\malicious_result\ersresult'
    m5 = r'D:\BaseSampleSet\malicious_result\vt2result'
    n1 = r'D:\BaseSampleSet\normal_result\atseresult'
    n2 = r'D:\BaseSampleSet\normal_result\ccresult'
    n3 = r'D:\BaseSampleSet\normal_result\houxresult'
    m_path_list = [m1,m2,m3,m4,m5]
    n_path_list = [n1,n2,n3]
    feaExtractor = FeatureExtractor()
    feaExtractor.learning(m_path_list, n_path_list)


if __name__ == '__main__':
    eval(sys.argv[1])
