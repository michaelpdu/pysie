

class TrainerInterface(object):
    def __init__(self):
        self.X_ = None
        self.y_ = None
        self.model_ = None

    def set_data(self, X, y):
        self.X_ = X
        self.y_ = y

    def train(self):
        pass

    def get_model(self):
        return self.model_

    def save_model(self, model_path = None):
        """
        if model_path is None, please use model_file in config
        :param model_path:
        :return:
        """
        pass



class ClassifierInterface(object):
    def __init__(self, config):
        self.model_ = None
        self.model_file_ = ''
        # list for 4 different groups, they are index list, and starts from 0
        self.tpl_ = []
        self.tnl_ = []
        self.fpl_ = []
        self.fnl_ = []
        self.tp_ = 0
        self.tn_ = 0
        self.fp_ = 0
        self.fn_ = 0

    def clear_score(self):
        self.tpl_ = []
        self.tnl_ = []
        self.fpl_ = []
        self.fnl_ = []
        self.tp_ = 0
        self.tn_ = 0
        self.fp_ = 0
        self.fn_ = 0

    def set_model(self, model):
        self.model_ = model

    def load_model(self, model_path):
        pass

    def score(self, X, y):
        self.clear_score()

    def predict(self, X):
        pass