#
# from xml.dom.minidom import parseString
from bs4 import BeautifulSoup
import json
import collections
from histogram import *
from yara_feature_analyzer import *
from logging import *

class DOMParser:
    """

    """
    def __init__(self, config):
        self.config_ = config
        self.dom_tag_list_ = config['dom_tag_list'].split(',')
        self.soup_ = None
        self.js_content_list = []
        self.vbs_content_list =[]
        self.tag_num_map_ = {}
        for item in self.dom_tag_list_:
            self.tag_num_map_[item] = 0
        self.tag_num_map_['unknown'] = 0
        self.dom_tag_list_and_normalization_base = config['dom_tag_list_and_nomalization_base']
        for item in self.dom_tag_list_and_normalization_base:
            pass
        self.all_of_big_leaf_content = ""
        self.num_external_link_script_ = 0
        self.num_internal_script_ = 0
        # tag_relationship map
        self.tag_relation_map_ = {}
        self.dom_tag_relation_base_ = config['dom_tag_relation_base']
        for key in self.dom_tag_relation_base_.keys():
            self.tag_relation_map_[key] = 0
        self.dom_features = {}

    def parse_content(self, content):
        # initialize dom_features
        self.dom_features.clear()

        # why use 'html.parser' here?
        # lxml and html5lib does't support multi-html in single file
        self.soup_ = BeautifulSoup(content, "html.parser")
        # self.soup_ = BeautifulSoup(content, "lxml")
        # self.soup_ = BeautifulSoup(content, "html5lib")

        # count tag name
        if self.config_['enable_tag_uni_gram']:
            info('Enable Tag Uni-gram, count all of tags')
            for tag in self.soup_.find_all():
                if tag.name in self.tag_num_map_.keys():
                    self.tag_num_map_[tag.name] += 1
                else:
                    self.tag_num_map_['unknown'] += 1

        # save all of scripts
        info('Save all of scripts')
        scripts = self.soup_.find_all('script')
        for script in scripts:
            if 'src' in script:
                self.num_external_link_script_ += 1
            else:
                self.num_internal_script_ += 1
                if not 'type' in script.attrs:
                    self.js_content_list.extend(script.contents)
                else:
                    script_type = script.attrs['type'].lower()
                    if 'vbscript' in script_type:
                        self.vbs_content_list.extend(script.contents)
                    else:
                        self.js_content_list.extend(script.contents)

        # save all of big leaf content, except script
        for child in self.soup_.recursiveChildGenerator():
            name = getattr(child, "name", None)
            if name is not None:
                # count tag-relationship
                if self.config_['enable_tag_bi_gram']:
                    parent = child.parent
                    parent_name = getattr(parent, "name", None)
                    tag_relationship = '{}-{}'.format(parent_name, name)

                    if tag_relationship in self.tag_relation_map_.keys():
                        self.tag_relation_map_[tag_relationship] += 1
                    # else:
                    #     self.tag_relation_map_[tag_relationship] = 1

            elif not child.isspace():
                if self.config_['enable_big_leaf_uni_gram']     \
                    and child not in self.js_content_list       \
                    and child not in self.vbs_content_list      \
                    and len(child) > self.config_['big_leaf_content_threshold']:
                    self.all_of_big_leaf_content += child
            else:
                pass
        
        # check manual keywords in HTML content
        if self.config_['enable_manual_keywords']:
            manual_feature_yara_rule = self.config_['manual_keywords_yara_rule']
            with open(manual_feature_yara_rule, 'rb') as fh:
                manual_feature_rules = fh.read()
            manual_yara_fea_analyzer = YaraFeatureAnalyzer(manual_feature_rules)
            index = self.config_['manual_keywords_base_index']
            manual_yara_fea_analyzer.analyze_content(content, index)
            self.dom_features.update(manual_yara_fea_analyzer.get_features())

    def get_tag_relationship_statistic(self):
        return self.tag_relation_map_

    def get_dom_features(self):
        # tag name statistic
        if self.config_['enable_tag_uni_gram']:
            ordered_map_tag_num = collections.OrderedDict(sorted(self.tag_num_map_.items()))
            index = 0
            dom_tag_base_index = self.config_['dom_tag_base_index']
            for tag_name in ordered_map_tag_num:
                # print '{}:{}:{} '.format(base_index+index, i, ordered_map_tag_num[i])
                base = self.dom_tag_list_and_normalization_base[tag_name]
                value = ordered_map_tag_num[tag_name]
                if value >= base:
                    self.dom_features[dom_tag_base_index + index] = 1
                else:
                    self.dom_features[dom_tag_base_index + index] = float(value) / base
                index += 1

        # tag relation statistic
        if self.config_['enable_tag_bi_gram']:
            ordered_map_tag_rel = collections.OrderedDict(sorted(self.tag_relation_map_.items()))
            index = 0
            dom_tag_rel_base_index = self.config_['dom_tag_relation_base_index']
            dom_tag_rel_feature = {}
            for tag_rel_name in ordered_map_tag_rel:
                if tag_rel_name in self.dom_tag_relation_base_.keys():
                    base = self.dom_tag_relation_base_[tag_rel_name]
                    value = ordered_map_tag_rel[tag_rel_name]
                    if value >= base:
                        dom_tag_rel_feature[dom_tag_rel_base_index + index] = 1
                    else:
                        if self.config_['use_dom_tag_relation_div_base']:
                            dom_tag_rel_feature[dom_tag_rel_base_index + index] = float(value) / base
                        else:
                            dom_tag_rel_feature[dom_tag_rel_base_index + index] = value
                else:
                    pass
                index += 1
            self.dom_features.update(dom_tag_rel_feature)

        # update histogram features of big leaf content
        if self.config_['enable_big_leaf_uni_gram']:
            hist = Histogram()
            for ch in self.all_of_big_leaf_content:
                hist.update(ch)
            hist_features = hist.get_features(self.config_['big_leaf_content_hist_base_index'])
            self.dom_features.update(hist_features)

        # update other features
        self.dom_features[self.config_['dom_feature_index']['external_link_script_div_50']] = float(self.num_external_link_script_) / 50
        self.dom_features[self.config_['dom_feature_index']['internal_script_div_20']] = float(self.num_internal_script_) / 20
        return self.dom_features

    def get_javascripts(self):
        return self.js_content_list

    def get_vbscripts(self):
        return self.vbs_content_list

def print_help():
    print """
DOMParser Usage:

"""

if __name__ == '__main__':
    html_content = """
<!DOCTYPE>
<html>
<head>
<TITLE>
</title>
</head>
<body>
<div id='123'><div id='abc'>190823748912758901243758902347189034789162347861289034712389461278934612783461789236478912364782364781236478123641789023461023789412890347123890471380141347128931704612378946123789461908237489127589012437589023471890347891623478612890347123894612789346127834617892364789123647823647812364781236417890234610237894128903471238904713801413471289317046123789461237894619082374891275890124375890234718903478916234786128903471238946127893461278346178923647891236478236478123647812364178902346102378941289034712389047138014134712893170461237894612378946190823748912758901243758902347189034789162347861289034712389461278934612783461789236478912364782364781236478123641789023461023789412890347123890471380141347128931704612378946123789461908237489127589012437589023471890347891623478612890347123894612789346127834617892364789123647823647812364781236417890234610237894128903471238904713801413471289317046123789461237894619082374891275890124375890234718903478916234786128903471238946127893461278346178923647891236478236478123647812364178902346102378941289034712389047138014134712893170461237894612378946916234786128903471238946127893461278346178923647891236478236</div></div>
<!--comments-->
<script type="text/javascript">
var a = "Hello";
</script>
<script type="text/vbscript">
DIM a = 1;
</script>
</body>
<unknown>aaa</unknown>
</html>
<html>
</html>
<script>
var a = 1;
</script>

"""
    with open('pysie.cfg', 'rb') as fh:
        config = json.load(fh)
    dom_parser = DOMParser(config['feature_extraction'])
    dom_parser.parse_content(html_content)
    print dom_parser.get_javascripts()
    print dom_parser.get_dom_features()
