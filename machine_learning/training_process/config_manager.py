import xml.etree.ElementTree as et


class ConfigMgr:
    """

    """

    def __init__(self, config_file):
        try:
            self.et_ = et.parse(config_file)
        except:
            print 'Parse config file failed'

    def get(self, key):
        return ''

help_msg = """

"""

if __name__ == '__main__':
    config = ConfigMgr('config.xml')
    config.get('abc')
