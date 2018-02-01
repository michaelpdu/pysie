
import json
from keras.preprocessing import text

class KeywordFeatureAnalyzer:
    """extract keyword feature"""
    def __init__(self, config, tf_config, usemaxtf):
        self.config_ = config
        self.usemaxtf = usemaxtf
        self.keyword_features_ = {}
        self.keyword_features_frequency = {}
        self.tf_config = {}
        if usemaxtf:
            self.tf_config = tf_config["max_word_freq_per_script"]
        self.keyword_start_index = int(self.config_["feature_extraction"]["keyword_start_index"])
        self.keyword_features_index_value_ = {}
        self.config_validate_keyword_ = self.config_["feature_extraction"]["keywords"]

    def analyze_content(self, content, top_n):
        keywords = text.text_to_word_sequence(content,
                                               filters='!"#$%&()*+,-./:;<=>?@[\\]^_`{|}~\t\n',
                                               lower=True,
                                               split=" ")

        self.keyword_features_.clear()
        self.keyword_features_frequency.clear()
        self.keyword_features_index_value_.clear()
        # format config feature to keyword:index
        start_index = self.keyword_start_index
        config_keyword_index = {}
        ordered_keywords_list = sorted(self.config_validate_keyword_.items(), key=lambda item: item[1], reverse=True)
        ordered_keywords_list = ordered_keywords_list[:int(top_n)]
        keylist = []
        for item in ordered_keywords_list:
            config_keyword_index[item[0]] = start_index
            start_index += 1
            keylist.append(str(item[0]))

        total_word = 0.0
        for word in keywords:
            if word in keylist:
                if self.keyword_features_.get(word) != None:
                    self.keyword_features_[word] += 1
                else:
                    self.keyword_features_[word] = 1
                total_word += 1

        if self.usemaxtf:
            print 'use max tf mode...'
            for k in self.keyword_features_.keys():
                if self.tf_config.get(k) != None:
                    self.keyword_features_frequency[k] = 1.0*self.keyword_features_[k]/self.tf_config[k]
                else:
                   self.keyword_features_frequency[k] = 1
        else:
            # normalize
            print 'use max total mode...'
            for k in self.keyword_features_.keys():
                if total_word != 0:
                    self.keyword_features_frequency[k] = self.keyword_features_[k]/total_word

        # format feature to index:value
        for word in self.keyword_features_frequency.keys():
            self.keyword_features_index_value_[config_keyword_index[word]] = self.keyword_features_frequency[word]

    def get_features_index_frequency(self):
        return self.keyword_features_index_value_

    def get_features_keywords_count(self):
        return self.keyword_features_
