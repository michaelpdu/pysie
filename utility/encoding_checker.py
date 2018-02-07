import os
import sys

class EncodingType:
    ENCODE_UNKNOWN      = 0
    ENCODE_UTF_16_BE    = 1
    ENCODE_UTF_16_LE    = 2
    ENCODE_UTF_32_BE    = 3
    ENCODE_UTF_32_LE    = 4

    @staticmethod
    def toString(type):
        if type == EncodingType.ENCODE_UTF_16_BE:
            return 'ENCODE_UTF_16_BE'
        elif type == EncodingType.ENCODE_UTF_16_LE:
            return 'ENCODE_UTF_16_LE'
        elif type == EncodingType.ENCODE_UTF_32_BE:
            return 'ENCODE_UTF_32_BE'
        elif type == EncodingType.ENCODE_UTF_32_LE:
            return 'ENCODE_UTF_32_LE'
        else:
            return 'ENCODE_UNKNOWN'

class EncodingChecker:
    """"""

    def __init__(self):
        pass

    def check(self, content):
        content = content.lstrip('\s\t\r\n')
        if content[0] == '\0' and content[1] == '\0' and content[2] == '\0' \
            and content[4] == '\0' and content[5] == '\0' and content[6] == '\0' \
            and content[8] == '\0' and content[9] == '\0' and content[10] == '\0' \
            and content[12] == '\0' and content[13] == '\0' and content[14] == '\0':
            return EncodingType.ENCODE_UTF_32_BE
        elif content[1] == '\0' and content[2] == '\0' and content[3] == '\0' \
            and content[5] == '\0' and content[6] == '\0' and content[7] == '\0' \
            and content[9] == '\0' and content[10] == '\0' and content[11] == '\0' \
            and content[13] == '\0' and content[14] == '\0' and content[15] == '\0':
            return EncodingType.ENCODE_UTF_32_LE
        elif content[0] == '\0' and content[2] == '\0' and content[4] == '\0' and content[6] == '\0':
            return EncodingType.ENCODE_UTF_16_BE
        elif content[1] == '\0' and content[3] == '\0' and content[5] == '\0' and content[7] == '\0':
            return EncodingType.ENCODE_UTF_16_LE
        else:
            return EncodingType.ENCODE_UNKNOWN

    def check_file(self, file_path):
        with open(file_path, 'rb') as fh:
            type = self.check(fh.read(500))
            if type == EncodingType.ENCODE_UTF_16_BE:
                print '{}, encoding type: UTF_16_BE'.format(file_path)
            elif type == EncodingType.ENCODE_UTF_16_LE:
                print '{}, encoding type: UTF_16_LE'.format(file_path)
            elif type == EncodingType.ENCODE_UTF_32_BE:
                print '{}, encoding type: UTF_32_BE'.format(file_path)
            elif type == EncodingType.ENCODE_UTF_32_LE:
                print '{}, encoding type: UTF_32_LE'.format(file_path)
            else:
                print '{}, encoding type: Unknown'.format(file_path)

class EncodingModifier:
    def __init__(self):
        pass

    def modify(self, content, encoding_type):
        content = content.lstrip('\s\t\r\n')
        if encoding_type == EncodingType.ENCODE_UTF_32_BE:
            return content[3::4]
        elif encoding_type == EncodingType.ENCODE_UTF_32_LE:
            return content[0::4]
        elif encoding_type == EncodingType.ENCODE_UTF_16_BE:
            return content[1::2]
        elif encoding_type == EncodingType.ENCODE_UTF_16_LE:
            return content[0::2]
        else:
            content

    def modify_file(self, file_path):
        with open(file_path, 'rb') as fh:
            content = fh.read()
            checker = EncodingChecker()
            type = checker.check(content[0:500])
            print self.modify(content, type)

help_msg = """
Usage:
    python file_type_detector.py target
"""

if __name__ == '__main__':
    checker = EncodingChecker()
    checker.check_file(sys.argv[1])
    modifier = EncodingModifier()
    modifier.modify_file(sys.argv[1])