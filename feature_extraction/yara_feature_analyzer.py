#
import yara
import json
import platform

class YaraFeatureAnalyzer:
    """extract feature by YARA rules"""
    def __init__(self, feature_rules):
        system = platform.system()
        if system == 'Windows':
            def include_callback(requested_filename, filename, namespace):
                with open(requested_filename, 'rb') as fh:
                    feature_rules = fh.read()
                    return feature_rules
                return ""
            self.yara_rules_ = yara.compile(source=feature_rules, include_callback=include_callback)
        elif system == 'Linux':
            self.yara_rules_ = yara.compile(source=feature_rules)
        else:
            print('[ERROR] Unsupported System!!!')
        self.matched_feature_index_map_ = {}

    def analyze_content(self, content, base_index):
        matched_rules = self.yara_rules_.match(data=content)
        for matched in matched_rules:
            index_value = matched.meta['index']
            if matched.rule.startswith('malicious_') or matched.rule.startswith('tss_'):
                index_value = index_value + base_index
            self.matched_feature_index_map_[index_value] = 1

    def get_features(self):
        return self.matched_feature_index_map_

def print_help():
    pass

if __name__ == '__main__':
    cfg_file = r'pysie.cfg'
    with open(cfg_file, 'rb') as fh:
        config_map = json.load(fh)
    content = """
    payload and shellcode
    windows official support
    phone_number
    """
    # test js yara rules
    js_feature_yara_rule = config_map['feature_extraction']['js_feature_yara_rule']
    with open(js_feature_yara_rule, 'rb') as fh:
        feature_rules = fh.read()
    yara_fea_analyzer = YaraFeatureAnalyzer(feature_rules)
    yara_fea_analyzer.analyze_content(content, config_map['feature_extraction']['js_base_index'])
    print yara_fea_analyzer.get_features()

    # test vbs yara rules
    vbs_feature_yara_rule = config_map['feature_extraction']['vbs_feature_yara_rule']
    with open(vbs_feature_yara_rule, 'rb') as fh:
        vbs_feature_rules = fh.read()
    vbs_yara_fea_analyzer = YaraFeatureAnalyzer(vbs_feature_rules)
    vbs_yara_fea_analyzer.analyze_content(content, config_map['feature_extraction']['vbs_base_index'])
    print vbs_yara_fea_analyzer.get_features()

    tss_feature_yara_rule = config_map['feature_extraction']['tss_keywords_yara_rule']
    with open(tss_feature_yara_rule, 'rb') as fh:
        tss_feature_rules = fh.read()
    tss_yara_fea_analyzer = YaraFeatureAnalyzer(tss_feature_rules)
    index = config_map['feature_extraction']['tss_keywords_base_index']
    tss_yara_fea_analyzer.analyze_content(content, index)
    print tss_yara_fea_analyzer.get_features()