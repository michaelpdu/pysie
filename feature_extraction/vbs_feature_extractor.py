#
from string_feature_extractor import *
from yara_feature_analyzer import *
from histogram import *

class VBSFeatureExtractor:
    """

    """
    def __init__(self, vbs_feature_rules, config):
        self.config_ = config
        self.yara_feature_analyzer = YaraFeatureAnalyzer(vbs_feature_rules)
        self.base_index_ = config['vbs_base_index']
        self.vbs_hist_base_index_ = config['vbs_hist_base_index']

    def extract_vbs_features(self, file_path, content):
        if isinstance(content, unicode):
            converted_content = content.encode('utf-8', errors='replace')
        else:  # isinstance(s, str):
            converted_content = unicode(content, encoding='utf-8', errors='replace')

        vbs_features = {}
        if self.config_['enable_vbs_yara_keyword']:
            try:
                # use YARA engine to match keywords
                self.yara_feature_analyzer.analyze_content(converted_content, self.base_index_)
                vbs_yara_features = self.yara_feature_analyzer.get_features()
            except Exception,e:
                print '[Exception][extract_vbs_features.yara_feature_analyzer] File: {}, Exception: {}'.format(file_path, str(e))
            vbs_features.update(vbs_yara_features)
	else:
	    print 'disable vbs yara keyword feature extract'
        # update histogram features
        hist = Histogram()
        for ch in content:
            hist.update(ch)
        hist_features = hist.get_features(self.vbs_hist_base_index_)
        vbs_features.update(hist_features)

        # vbs_length / 10000
        if len(converted_content) > 10000:
            vbs_features[self.config_['vbs_engine_feature_index']['len_div_10000']] = 1.0
        else:
            vbs_features[self.config_['vbs_engine_feature_index']['len_div_10000']] = float(len(converted_content)) / 10000

        return vbs_features

def print_help():
    pass

if __name__ == '__main__':
    pass