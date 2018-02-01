#
import sys
import traceback
import json
from string_feature_extractor import *
from yara_feature_analyzer import *
# from slimit.parser import Parser
# from slimit.visitors.nodevisitor import ASTVisitor
# from antlr4 import *
from pyjsparser import *
from histogram import *

BIG_STRING_THRESHOLD = 100

# class BigStringVisitor(ASTVisitor):
class BigStringVisitor:
    def __init__(self):
        self.big_strings_ = []

    # def visit(self, node):
    #     """visit big strings in current script code"""
    #     for child in node:
    #         if 'String' == type(child).__name__ and len(child.value) > BIG_STRING_THRESHOLD:
    #             self.big_strings_.append(child.value)
    #         self.visit(child)

    def visit(self, node):
        node_type = type(node).__name__
        if 'dict' in node_type:
            if 'type' in node and node['type'] == 'Literal' and 'value' in node and 'unicode' in type(node['value']).__name__:
                if len(node['value']) > BIG_STRING_THRESHOLD:
                    self.big_strings_.append(node['value'])
                return
            for item in node:
                self.visit(node[item])
        elif 'list' in node_type:
            for item in node:
                self.visit(item)
        # elif 'unicode' in node_type:
        #     print node
        else:
            pass

    def get_big_strings(self):
        return self.big_strings_


class JSFeatureExtractor:
    """
    extract all of features in JavaScript code, which includes:
    (a) big string features
    (b) keywords features in JavaScript code
    """
    def __init__(self, js_feature_rules, config_map):
        self.config_ = config_map
        self.yara_feature_analyzer = YaraFeatureAnalyzer(js_feature_rules)
        self.string_feature_extractor = StringFeatureExtractor(config_map['js_engine_feature_index'])
        self.base_index_ = config_map['js_base_index']
        self.js_hist_base_index_ = config_map['js_hist_base_index']

    def extract_big_string(self, content):
        try:
            # parser = Parser()
            # tree = parser.parse(content)
            # visitor = BigStringVisitor()
            # visitor.visit(tree)
            # return visitor.get_big_strings()
            parser = PyJsParser()
            tree = parser.parse(content)
            visitor = BigStringVisitor()
            visitor.visit(tree)
            return visitor.get_big_strings()
        except:
            print '[Exception] extract big string failed'
            print sys.exc_info()
            print traceback.print_stack(file=sys.stdout)
            return []


    def extract_js_features(self, file_path, content):
        try:
            if isinstance(content, unicode):
                converted_content = content.encode('utf-8', errors='replace')
            else:  # isinstance(s, str):
                converted_content = unicode(content, encoding='utf-8', errors='replace')

            # analyze all of big string from JavaScript code, and extract string features
            # big_strings = self.extract_big_string(converted_content)
            # big_string_features = self.string_feature_extractor.extract_string_features(big_strings)
            # use YARA engine to match keywords

            js_features = {}
            if self.config_['enable_js_yara_keyword']:
                js_yara_features = {}
                try:
                    self.yara_feature_analyzer.analyze_content(converted_content, self.base_index_)
                    js_yara_features = self.yara_feature_analyzer.get_features()
                except Exception,e:
                    print '[Exception][extract_js_features.yara_feature_analyzer] File: {}, Exception: {}'.format(file_path, str(e))

                # js_features = dict(big_string_features)
                js_features.update(js_yara_features)
	    else:
		print 'diable js yara keyword extract'
            # update histogram features
            hist = Histogram()
            for ch in content:
                hist.update(ch)
            hist_features = hist.get_features(self.js_hist_base_index_)
            js_features.update(hist_features)

            # js_length/10000
            if len(converted_content) > 10000:
                js_features[self.config_['js_engine_feature_index']['len_div_10000']] = 1.0
            else:
                js_features[self.config_['js_engine_feature_index']['len_div_10000']] = float(len(converted_content)) / 10000

            return js_features
        except Exception,e:
            print 'Exception in extract_js_features, '+str(e)
            return {}

def print_help():
    pass

if __name__ == '__main__':
    cfg_file = r'pysie.cfg'
    with open(cfg_file, 'rb') as fh:
        config_map = json.load(fh)
    js_feature_yara_rule = config_map['feature_extraction']['js_feature_yara_rule']
    with open(js_feature_yara_rule, 'rb') as fh:
        feature_rules = fh.read()
    feature_index = config_map['feature_extraction']['js_engine_feature_index']
    js_feature_extractor = JSFeatureExtractor(feature_rules, feature_index)
    content = """
var a = "this is a big string !@#$%^&*(*&^%$%$##$%%^&&**&^%$$#$%^&$%^#^$%@^#!@#$%@&^%$*&^%*^&^$%&^%$#%^@$%#@$%&^%*&^%*&^%&^$#^$%&";
var malware_keywords = "payload and shellcode";
var Ehs16J="\123\125\350\020\000\000\000\135\133\213\143\014\213\105\014\203\010\001\061\366\302\024\000\220";
"""
    print js_feature_extractor.extract_js_features('abcdefg', content)