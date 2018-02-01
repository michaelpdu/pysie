from __future__ import print_function
import os, json
from classifier_base import *
import keras
from keras.models import *
from keras.layers import Dense, Dropout
from keras.optimizers import RMSprop
from sklearn.preprocessing import OneHotEncoder
from keras.wrappers.scikit_learn import *
from sklearn.datasets import load_svmlight_file
import numpy as np
from scipy.sparse import csr_matrix


def csr_matrix_to_ndarray(m):
    return csr_matrix(m, dtype=np.float32).toarray()

class TMSAKerasTrainer(TrainerInterface):
    def __init__(self, config):
        print('TMSAKerasTrainer init')
        super(self.__class__, self).__init__()
        self.config_ = config
        self.input_dim_ = config['model']['keras']['input_dim']
        self.num_classes_ = config['model']['keras']['num_classes']
        self.batch_size_ = config['model']['keras']['batch_size']
        self.epochs_ = config['model']['keras']['epochs']

    def train(self):
        # convert class vectors to binary class matrices
        y_train = keras.utils.to_categorical(self.y_, 2)
        # enc = OneHotEncoder(sparse=False)  # Key here is sparse=False!
        # y_train = enc.fit_transform(self.y_.reshape((self.y_.shape[0]), 1))
        # y = np.array(self.y_)

        self.model_ = Sequential()
        #self.model_.add(Dense(10240, activation='relu', input_dim=self.input_dim_))
        #self.model_.add(Dropout(0.2))
        #self.model_.add(Dense(1024, activation='relu'))
        #self.model_.add(Dropout(0.2))
        #self.model_.add(Dense(512, activation='relu'))
        self.model_.add(Dense(512, activation='relu', input_dim=self.input_dim_))
        self.model_.add(Dropout(0.2))
        self.model_.add(Dense(64, activation='relu'))
        self.model_.add(Dropout(0.2))
        self.model_.add(Dense(2, activation='softmax'))
        #self.model_.add(Dense(2, activation='sigmoid'))

        self.model_.summary()

        self.model_.compile(loss='categorical_crossentropy',
                      optimizer=RMSprop(),
                      metrics=['accuracy'])

        X_array = csr_matrix_to_ndarray(self.X_)       

        history = self.model_.fit(X_array, y_train,
                            batch_size=self.batch_size_,
                            epochs=self.epochs_,
                            verbose=1,
                            validation_data=(X_array, y_train))
        #print history

    def save_model(self, model_path = None):
        if model_path:
            print('get model path from parameter')
        else:
            model_path = os.path.join(self.config_['filesystem']['mid_folder'], \
                                      self.config_['model']['keras']['model_name'])
            print('get model path from config')
        dir_path, file_name = os.path.split(model_path)
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)
        self.model_.save(model_path)
        return model_path



class TMSAKerasClassifier(ClassifierInterface):
    def __init__(self, config):
        super(self.__class__, self).__init__(config)
        self.config_ = config
        self.model_path_ = ''
        self.model_ = None
        self.num_classes_ = config['model']['keras']['num_classes']

    def load_model(self, model_path = None):
        if model_path and os.path.exists(model_path):
            print('Load model from parameter: {}'.format(model_path))
            self.model_path_ = model_path
        else:
            self.model_path_ = os.path.join(self.config_['filesystem']['mid_folder'], \
                                            self.config_['model']['keras']['model_name'])
            print('Load model from config: {}'.format(self.model_path_))
        self.model_ = load_model(self.model_path_)

    def score(self, X, y):
        self.clear_score()
        X_array = csr_matrix_to_ndarray(X)
        y_test = keras.utils.to_categorical(y, self.num_classes_)
        score = self.model_.evaluate(X_array, y_test, verbose=0)

        probabilities = self.model_.predict(X_array)
        nor_prob_list = probabilities[:,0]

        index = 0
        for prob in nor_prob_list:
            if prob >= 0.5 and y[index] == 1:
                self.fn_ += 1
                self.fnl_.append(index)
            elif prob < 0.5 and y[index] == 1:
                self.tp_ += 1
                self.tpl_.append(index)
            elif prob >= 0.5 and y[index] == 0:
                self.tn_ += 1
                self.tnl_.append(index)
            else:
                self.fp_ += 1
                self.fpl_.append(index)
            index += 1 
        return self.tpl_, self.tnl_, self.fpl_, self.fnl_, probabilities[:,1]


