 # Author: Feihao Chen
 # Date: 2016/12/15

import os,sys
import re
import xml.etree.cElementTree as ET

class BehaviourReportHelper(object):
    """

    """
    def __init__(self,xml_file = ''):
        self.xml_file = xml_file
        self.root = None
        self.file_path = ''
        self.sha1 = ''
        self.decision = ''
        self.rules = ''
        self.behaviour = ''

    def clear(self):
        self.xml_file = ''
        self.root = None
        self.file_path = ''
        self.sha1 = ''
        self.decision = ''
        self.rules = ''
        self.behaviour = ''

    def set_xml_file(self, xml_file):
        self.xml_file = xml_file

    def parse_XML(self):
        self.root = ET.parse(self.xml_file).getroot()
        self.parse_base_info()
        self.extract_behavior()

    def parse_base_info(self):
        for e in self.root:
            if e.tag == 'file_path':
                self.file_path = e.text
            elif e.tag == 'sha1':
                self.sha1 = e.text
            elif e.tag == 'decision':
                self.decision = e.text
            elif e.tag == 'matched_rules':
                self.rules = ';'.join(x.text for x in e)

    def extract_behavior(self):
        label=0
        for e in self.root:
            if e.tag == 'evidence':
                if e.attrib['type']=='javascript' and '// This is JS Runtime file' in e[2].text:
                    label=1
                    continue
                if e.attrib['type']=='javascript_behaviour' and label==1:
                    label=0
                    continue
                self.behaviour = self.behaviour + e[-1].text

    def get_file_path(self):
        return self.file_path

    def get_sha1(self):
        return self.sha1

    def get_decision(self):
        return self.decision

    def get_rules(self):
        return self.rules

    def get_behaviour(self):
        return self.behaviour




class ExtractBehaviourFeature(object):
    """

    """
    def __init__(self,xml_file = ''):
        self.xml_file = xml_file
        self.BRH = BehaviourReportHelper()
        self.behaviour = None
        self.feature_dict = {}
        self.url_list = []

    def clear(self):
        self.xml_file = ''
        self.BRH = BehaviourReportHelper()
        self.behaviour = None
        self.feature_dict = {}
        self.url_list = []

    def set_xml_file(self, xml_file):
        self.xml_file = xml_file
        self.BRH.set_xml_file(xml_file)

    def load_behaviour(self):
    	self.BRH.parse_XML()
    	self.behaviour = self.BRH.get_behaviour().lower()

    def add_feature_exists(self,feature):
        self.feature_dict[feature] = 1 if re.search(feature,self.behaviour)!=None else 0

    def add_feature_matched(self,feature):
        self.feature_dict[feature] = ';'.join(set(re.findall(feature,self.behaviour)))

    def append_local_script_feature(self):
        self.add_feature_exists(r'/*@cc_on')
        self.add_feature_exists('wscript.shell')
        self.add_feature_exists('shell.application')
        self.add_feature_exists('scripting.filesystemobject')

    def append_browser_script_feature(self):
        self.add_feature_matched('\\bwindow\.[a-z0-9]+')
        if self.feature_dict['\\bwindow\.[a-z0-9]+'] == 'window.open':
            self.feature_dict['\\bwindow\.[a-z0-9]+'] = ''
        elif self.feature_dict['\\bwindow\.[a-z0-9]+'].startswith('window.open;'):
            self.feature_dict['\\bwindow\.[a-z0-9]+'] = self.feature_dict['\\bwindow\.[a-z0-9]+'][12:]
        else:
            pass
        self.add_feature_matched('\\bdocument\.[a-z0-9]+')
        self.add_feature_matched('\\bwindow\[[a-z0-9]+\]')
        self.add_feature_matched('\\bdocument\[[a-z0-9]+\]')
        self.add_feature_exists('getElementsByTagName')
        self.add_feature_exists('getElementById')
        self.add_feature_exists('<div')
        self.add_feature_exists('\\bconsole\.')
        self.add_feature_exists('parentNode')
        self.add_feature_exists('\s\$\.')

    # If you need to append other features, use this function.
    def append_other_features(self):
        self.add_feature_exists('xmlhttp')
        self.add_feature_exists('adodb.stream')

    def extract_url_list(self):
        line_list=self.behaviour.split('\n')
        for line in line_list[2:]:
            if line.find(' URL =')!=-1:
                start=line.find(' URL =')+7
                if line[start:start+4]=='http':
                    start=start+7              #pass http://
                    end=line.find('/',start)     
                    if end ==-1:
                        end=line.find('\"',start)
                else:           #other url
                    end=line.find('\"',start)
                self.url_list.append(line[start:end])

    def get_file_path(self):
        return self.BRH.get_file_path()

    def get_sha1(self):
        return self.BRH.get_sha1()

    def get_decision(self):
        return self.BRH.get_decision()

    def get_rules(self):
        return self.BRH.get_rules()

    def get_origin_behaviour(self):
        return self.BRH.get_behaviour()

    def get_lower_behaviour(self):
        return self.behaviour

    def get_feature_dict(self):
        return self.feature_dict

    def get_is_local(self):
        return self.is_local

    def get_url_list(self):
        return self.url_list