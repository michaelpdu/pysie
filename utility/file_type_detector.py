import os
import sys
import yara
from encoding_checker import *

class FileType:
    FILETYPE_UNKNOWN    = 0
    FILETYPE_HTML       = 1
    FILETYPE_JS         = 2
    FILETYPE_VBS        = 3

class FileTypeDetector:
    """
    """
    def __init__(self, yara_rule_file):
        self.encoding_checker_ = EncodingChecker()
        self.encoding_modifier_ = EncodingModifier()
        with open(yara_rule_file, 'rb') as fh:
            file_type_rules = fh.read()
            self.yara_rules_ = yara.compile(source=file_type_rules)

    def check_type(self, content):
        encoding_type = self.encoding_checker_.check(content)
        if EncodingType.ENCODE_UNKNOWN != encoding_type:
            content = self.encoding_modifier_.modify(content, encoding_type)
        matched_rules = self.yara_rules_.match(data=content)
        for matched in matched_rules:
            if 'html_type' in matched.rule:
                return (FileType.FILETYPE_HTML, encoding_type)
            elif 'js_type' in matched.rule:
                return (FileType.FILETYPE_JS, encoding_type)
            elif 'vbs_type' in matched.rule:
                return (FileType.FILETYPE_VBS, encoding_type)
            else:
                return (FileType.FILETYPE_UNKNOWN, encoding_type)
        return (FileType.FILETYPE_UNKNOWN, encoding_type)

    def check_file(self, file_path):
        try:
            with open(file_path, 'rb') as fh:
                file_type, encoding_type = file_type_d.check_type(fh.read())
                if file_type == FileType.FILETYPE_HTML:
                    print '{}, file type: HTML, encoding type: {}'.format(file_path, EncodingType.toString(encoding_type))
                elif file_type == FileType.FILETYPE_JS:
                    print '{}, file type: JS, encoding type: {}'.format(file_path, EncodingType.toString(encoding_type))
                elif file_type == FileType.FILETYPE_VBS:
                    print '{}, file type: VBS, encoding type: {}'.format(file_path, EncodingType.toString(encoding_type))
                else:  # type == FileType.FILETYPE_UNKNOWN:
                    print '{}, file type: Unknown, encoding type: {}'.format(file_path, EncodingType.toString(encoding_type))
        except Exception,e:
            print '{}, file type: Exception, encoding type: --'.format(file_path)

    def check_dir(self, dir_path):
        for root, dirs, files in os.walk(dir_path):
            for name in files:
                file_path = os.path.join(root, name)
                self.check_file(file_path)

help_msg = """
Usage:
    python file_type_detector.py target
"""

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print help_msg
        exit(-1)

    file_type_d = FileTypeDetector('file_type.yar')
    if os.path.isdir(sys.argv[1]):
        file_type_d.check_dir(sys.argv[1])
    else:
        file_type_d.check_file(sys.argv[1])
