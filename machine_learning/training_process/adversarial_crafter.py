from __future__ import division
import os, sys, json, time
from argparse import ArgumentParser
from keras.models import load_model
from sklearn.datasets import load_svmlight_file
import numpy as np

sys.path.append('/sa/github/adversarial-robustness-toolbox/')
from art.classifiers import KerasClassifier
from art.attacks.deepfool import DeepFool
from art.attacks.fast_gradient import FastGradientMethod
from art.attacks.carlini import CarliniL2Method

# os.environ["CUDA_VISIBLE_DEVICES"]="0"

class AdversarialCrafter:
    """"""

    def __init__(self, config):
        self.config_ = config
    
    def generate(self, data_file):
        # load data set
        x, y = load_svmlight_file(data_file)
        X = x.toarray()
        # load model from file
        model = load_model(self.config_['common']['model_file'])
        classifier = KerasClassifier((np.amin(X), np.amax(X)), model=model)

        # 
        preds = np.argmax(classifier.predict(X), axis=1)
        acc = np.sum(preds == y) / y.shape[0]
        print('Accuracy on raw samples: %.2f%%' % (acc * 100))

        crafter_type = self.config_['crafter']['type']
        if crafter_type == 'deepfool':
            # Craft adversarial samples with DeepFool
            print("Build DeepFool crafter ...")
            adv_crafter = DeepFool(classifier)
            # x_train_adv = adv_crafter.generate(x_train)
            begin = time.time()
            print("Begin to generate adversarial samples")
            print("Shape of test sample set: {}".format(X.shape))
            x_adv = adv_crafter.generate(X)
            delta = time.time() - begin
            print("Time delta of adv. generation: {}".format(delta))

            # save adversary samples to file
            np.savetxt('adv_deepfool.out', x_adv, delimiter=',')

            # Evaluate the classifier on the adversarial samples
            preds = np.argmax(classifier.predict(x_adv), axis=1)
            acc = np.sum(preds == y) / y.shape[0]
            print('Classifier before adversarial training')
            print('Accuracy on adversarial samples: %.2f%%' % (acc * 100))
        elif crafter_type == 'fgsm':
            # Craft adversarial samples with FGSM
            epsilon = .1  # Maximum perturbation
            adv_crafter = FastGradientMethod(classifier)
            x_adv = adv_crafter.generate(x=X, eps=epsilon)
            # save adversary samples to file
            np.savetxt('adv_fgsm.out', x_adv, delimiter=',')
            # Evaluate the classifier on the adversarial samples
            preds = np.argmax(classifier.predict(x_adv), axis=1)
            acc = np.sum(preds == y) / y.shape[0]
            print('Classifier before adversarial training')
            print('Accuracy on adversarial samples: %.2f%%' % (acc * 100))
        elif crafter_type == 'carlini':
            print("Build Carlini crafter ...")
            adv_crafter = CarliniL2Method(classifier)
            x_adv = adv_crafter.generate(x=X, y=y)
            # save adversary samples to file
            np.savetxt('adv_carlini.out', x_adv, delimiter=',')
            # Evaluate the classifier on the adversarial samples
            preds = np.argmax(classifier.predict(x_adv), axis=1)
            acc = np.sum(preds == y) / y.shape[0]
            print('Classifier before adversarial training')
            print('Accuracy on adversarial samples: %.2f%%' % (acc * 100))
        else:
            print('ERROR: Unsupported crafter type')


help_msg = """
Usage:
    > python adversarial_crafter.py [-c|--config] config-file [-d|--data] data-set
"""

if __name__ == '__main__':
    arg_parser = ArgumentParser()
    arg_parser.add_argument("-c", "--config", dest='config_file', help="specify config file")
    arg_parser.add_argument("-d", "--data", dest='data_file', help="specify data set")
    args = arg_parser.parse_args()
    if args.config_file:
        with open(args.config_file, 'rb') as fh:
            config = json.load(fh)
            crafter = AdversarialCrafter(config)
            crafter.generate(args.data_file)