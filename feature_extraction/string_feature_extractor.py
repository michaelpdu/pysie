#
from __future__ import division
import json

class StringFeatureExtractor:
    """

    """
    def __init__(self, config):
        self.big_string_features_ = {}
        self.feature_index_map_ = config
        self.index_non_word_percentage_in_big_string_ = self.feature_index_map_['non_word_percentage_in_big_string']
        self.big_string_features_[self.index_non_word_percentage_in_big_string_] = 0
        self.index_find_big_hex_string_ = self.feature_index_map_['find_big_hex_string']
        self.big_string_features_[self.index_find_big_hex_string_] = 0

    def is_non_word(self, ch):
        if ch == ' ' or ('0' <= ch <= '9') or ('a' <= ch <= 'z') or ('A' <= ch <= 'Z'):
            return False
        else:
            return True

    def is_hex_char(self, ch):
        if ('0' <= ch <= '9') or ('a' <= ch <= 'f') or ('A' <= ch <= 'F'):
            return True
        else:
            return False

    def extract_feature_non_word_percentage(self, big_string):
        num_non_word = 0
        for ch in big_string:
            if self.is_non_word(ch):
                num_non_word += 1

        percentage = num_non_word/len(big_string)

        if self.big_string_features_[self.index_non_word_percentage_in_big_string_] < percentage:
            self.big_string_features_[self.index_non_word_percentage_in_big_string_] = percentage

    def extract_feature_is_hex_string(self, big_string):
        if self.big_string_features_[self.index_find_big_hex_string_] == 1:
            return

        is_hex_string = True
        for ch in big_string:
            if not self.is_hex_char(ch):
                is_hex_string = False
                break

        if is_hex_string == True:
            self.big_string_features_[self.index_find_big_hex_string_] = 1
        else:
            pass

    def extract_string_features(self, big_strings):
        for big_str in big_strings:
            self.extract_feature_non_word_percentage(big_str)
            self.extract_feature_is_hex_string(big_str)
        return self.big_string_features_

def print_help():
    pass

if __name__ == '__main__':
    big_strings = ["this is a big string !@#$%^&*(*&^%$%$##$%%^&&**&^%$$#$%^&$%^#^$%@^#!@#$%@&^%$*&^%*^&^$%&^%$#%^@$%#@$%&^%*&^%*&^%&^$#^$%&",
                   "1234567898765432123456789098765432345678916234713264871263471326431287461278345612834632178462317461273412341234623974612"]
    config = {'non_word_percentage_in_big_string':600,'find_big_hex_string':601}
    string_feature_extractor = StringFeatureExtractor(config)
    print string_feature_extractor.extract_string_features(big_strings)