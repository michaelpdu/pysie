import bs4

class DOMSeqFeatureAnalyzer:
    def __init__(self, soup):
        self.soup_=soup
#        print(self.soup_.prettify())
        self.tag2tag_relation_map_={}
        pass


    def analyze(self):
        for child in self.soup_.children:
            if isinstance(child, bs4.element.Tag):
                for child2 in child.children:
                    if child2.name is not None:
                        tag2tag_relationship = '{}-{}@{}-{}'.format(self.soup_.name, child.name, child.name,
                                                                    child2.name)
                        if tag2tag_relationship in self.tag2tag_relation_map_.keys():
                            self.tag2tag_relation_map_[tag2tag_relationship] += 1
                        else:
                            self.tag2tag_relation_map_[tag2tag_relationship] = 1
                for sibling in child.next_siblings:
                    if sibling is None:
                        pass
                    elif isinstance(sibling, bs4.element.Tag):
                        tag2tag_relationship = '{}-{}#{}-{}'.format(self.soup_.name, child.name, child.name,
                                                                    sibling.name)
                        if tag2tag_relationship in self.tag2tag_relation_map_.keys():
                            self.tag2tag_relation_map_[tag2tag_relationship] += 1
                        else:
                            self.tag2tag_relation_map_[tag2tag_relationship] = 1
                    else:
                        pass
                for child2 in child.descendants:
                    if child2.name is not None:
                        for child3 in child2.children:
                            if child3.name is not None:
                                tag2tag_relationship = '{}-{}@{}-{}'.format(child2.parent.name, child2.name,child2.name, child3.name)
                                if tag2tag_relationship in self.tag2tag_relation_map_.keys():
                                    self.tag2tag_relation_map_[tag2tag_relationship] += 1
                                else:
                                    self.tag2tag_relation_map_[tag2tag_relationship] = 1
                            else:
                                pass
                        for sibling in child2.next_siblings:
                            if sibling is None:
                                pass
                            elif isinstance(sibling, bs4.element.Tag):
                                tag2tag_relationship = '{}-{}#{}-{}'.format(child2.parent.name, child2.name, child2.parent.name,
                                                                            sibling.name)
                                if tag2tag_relationship in self.tag2tag_relation_map_.keys():
                                    self.tag2tag_relation_map_[tag2tag_relationship] += 1
                                else:
                                    self.tag2tag_relation_map_[tag2tag_relationship] = 1
                            else:
                                pass
                    else:
                        pass

    def get_result(self):
        return self.tag2tag_relation_map_;

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
<script>
var a = 1;
</script>

"""
    domseq_feature_analyzer=DOMSeqFeatureAnalyzer(bs4.BeautifulSoup(html_content, "html5lib"))
    domseq_feature_analyzer.analyze()
    print(domseq_feature_analyzer.get_result())