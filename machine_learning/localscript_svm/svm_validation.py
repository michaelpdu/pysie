# auther = Cheng Chang(SA)
# Date = 2016/12/29
import os
import sys
import re
import pickle
import numpy as np
from sklearn import random_projection
from sklearn import svm
from sklearn.externals import joblib
from sklearn.model_selection import StratifiedKFold, cross_val_score
from feature_extractor import FeatureExtractor
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import classification_report

# Stratified k-fold
def stratified_k_fold():
    clf = svm.SVC(kernel='linear', class_weight='balanced', cache_size=1000)
    skf = StratifiedKFold(n_splits=3)
    X_digits = pickle.load(open('npdata_0102.pkl', 'rb'))
    y_digits = pickle.load(open('nptarget_0102.pkl', 'rb'))
    print cross_val_score(clf, X_digits, y_digits, cv = skf)    


def grid_search():
    X_digits = pickle.load(open('npdata_0102.pkl', 'rb'))
    y_digits = pickle.load(open('nptarget_0102.pkl', 'rb'))
    tuned_parameters = [{'kernel': ['linear'], 'C': [5, 10, 20, 50]}]
    srv = svm.SVC(class_weight='balanced', cache_size=1000)
    skf = StratifiedKFold(n_splits=3)
    clf = GridSearchCV(srv, tuned_parameters, cv=skf)
    clf.fit(X_digits, y_digits)
    print "Best parameters set found on development set:"
    print clf.best_params_
    print clf.best_score_


def classify_report():
    clf = joblib.load('balanced_linear_svc_model_0102.pkl')
    # y_pred = clf.predict()
    # y_true = 
    # print classification_report()


def main():
    # clf = joblib.load('svc_model.pkl')

    # fsock = open('error.log', 'w')
    # sys.stderr = fsock

    stratified_k_fold()

if __name__ == '__main__':
    eval(sys.argv[1])
