import os
import sys
import tlsh
from optparse import OptionParser

def get_tlsh(file_path):
    try:
        with open(file_path, 'rb') as fh:
            return tlsh.hash(fh.read())
    except Exception as e:
        print('ERROR: cannot get TLSH of file: {}'.format(file_path))
        print(e)
        return None

def search_similar_file(base_file_path, dest_dir_path, dist):
    base_tlsh = get_tlsh(base_file_path)
    for root, dirs, files in os.walk(dest_dir_path):
        for name in files:
            file_path = os.path.join(root, name)
            value = get_tlsh(file_path)
            if value:
                dist_value = tlsh.diff(base_tlsh, value)
                if dist_value <= dist:
                    print('File: {}, Distance: {}'.format(file_path, dist_value))

help_msg = """
Usage:
    python tool.py question_file target_dir
"""

if __name__ == "__main__":
    search_similar_file(sys.argv[1], sys.argv[2], 200)




