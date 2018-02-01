import pickle
from sklearn.datasets import load_svmlight_file

class ModelLoader:
    """Common loader for all types of model file"""
    def __init__(self):
        pass

    def check_model_file_type(self):
        pass

    def load(self, file_path):
        pass

    def get_model(self):
        pass

help_msg = """

"""

if __name__ == '__main__':
    loader = ModelLoader()
    loader.load('../test_samples/model/')
    model = loader.get_model()