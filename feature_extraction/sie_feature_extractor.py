#
import os
import sys
import json
from dom_parser import *
from js_feature_extractor import *
from vbs_feature_extractor import *

sys.path.append('..')
from utility.file_type_detector import *
from utility.encoding_checker import *
from logging import *

file_type_yara_file = os.path.join('..','utility','file_type.yar')

class SIEFeatureExtractor:
    """

    """
    def __init__(self, config_map):
        self.config_ = config_map
        # self.content_ = ''
        self.file_type_detector_ = FileTypeDetector(file_type_yara_file)
        self.encoding_modifier_ = EncodingModifier()
        self.dom_parser_ = DOMParser(config_map)
        with open(config_map['js_feature_yara_rule'], 'rb') as fh:
            feature_rules = fh.read()
        self.js_feature_e = JSFeatureExtractor(feature_rules, config_map)
        with open(config_map['vbs_feature_yara_rule'], 'rb') as fh:
            feature_rules = fh.read()
        self.vbs_feature_e = VBSFeatureExtractor(feature_rules, config_map)

    def extract_html_features(self, file_path, content):
        features = {}
        self.dom_parser_.parse_content(content)
        if self.config_['enable_dom_feature'] > 0:
            dom_features = self.dom_parser_.get_dom_features()
            features.update(dom_features)
        if self.config_['enable_js_feature'] > 0:
            js_list = self.dom_parser_.get_javascripts()
            js_features = self.extract_js_features(file_path, '\n'.join(js_list))
            features.update(js_features)
        if self.config_['enable_vbs_feature'] > 0:
            vbs_list = self.dom_parser_.get_vbscripts()
            vbs_features = self.extract_vbs_features(file_path, '\n'.join(vbs_list))
            features.update(vbs_features)
        return features

    def extract_js_features(self, file_path, content):
        return self.js_feature_e.extract_js_features(file_path, content)

    def extract_vbs_features(self, file_path, content):
        return self.vbs_feature_e.extract_vbs_features(file_path, content)

    def extract(self, file_path, content):
        file_type, encoding_type = self.file_type_detector_.check_type(content)
        info('File path: {}, file type: {}, encoding type: {}'.format(file_path, file_type, encoding_type))
        if FileType.FILETYPE_HTML == file_type:
            if EncodingType.ENCODE_UNKNOWN != encoding_type:
                content = self.encoding_modifier_.modify(content, encoding_type)
            return self.extract_html_features(file_path, content)
        elif FileType.FILETYPE_JS == file_type:
            return self.extract_js_features(file_path, content)
        elif FileType.FILETYPE_VBS == file_type:
            return self.extract_vbs_features(file_path, content)
        else:
            return None

    def get_keyword_freq_features(self):
        pass

def print_help():
    pass

if __name__ == '__main__':
    with open('pysie.cfg', 'rb') as fh:
        config_data = json.load(fh)
    sie_feature_extractor = SIEFeatureExtractor(config_data['feature_extraction'])
    html_content = """
<html>
<script type="text/javascript">
var a = "this is a big string !@#$%^&*(*&^%$%$##$%%^&&**&^%$$#$%^&$%^#^$%@^#!@#$%@&^%$*&^%*^&^$%&^%$#%^@$%#@$%&^%*&^%*&^%&^$#^$%&";
var malware_keywords = "payload and shellcode";
</script>
<script type="text/vbscript">
DIM a = "shellcode";
DIM e = "execute";
</script>
</html>
"""
    print sie_feature_extractor.extract_html_features(html_content)


