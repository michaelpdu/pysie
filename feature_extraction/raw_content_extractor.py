#
import os
import sys
import json

sys.path.append('..')
from utility.file_type_detector import *
from utility.encoding_checker import *
from logging import *

file_type_yara_file = os.path.join('..','utility','file_type.yar')

class RawContentExtractor:
    """
    """
    def __init__(self, config_map):
        self.config_ = config_map
        # self.content_ = ''
        self.file_type_detector_ = FileTypeDetector(file_type_yara_file)
        self.encoding_modifier_ = EncodingModifier()

    def extract(self, file_path, content):
        features = {}
        file_type, encoding_type = self.file_type_detector_.check_type(content)
        info('File path: {}, file type: {}, encoding type: {}'.format(file_path, file_type, encoding_type))
        if len(content) < self.config_['dim']:
            content += (self.config_['dim']-len(content))*'0'
        for i in range(0, self.config_['dim']):
            features[i] = ord(content[i])
        return features