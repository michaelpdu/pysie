import os
import sys
import shutil
import argparse

class FileHelper:
    """"""

    #
    def backup_lines_by_index(self, src_file_path, index_list, backup_file_path):
        with open(src_file_path, 'rb') as fh:
            lines = fh.readlines()
        with open(backup_file_path, 'wb') as fh:
            index = 0
            for line in lines:
                if index in index_list:
                    fh.write(line)
                index += 1

    #
    def remove_lines_by_index(self, src_file_path, index_list, dest_file_path):
        with open(src_file_path, 'rb') as fh:
            lines = fh.readlines()
        with open(dest_file_path, 'wb') as fh:
            index = 0
            for line in lines:
                if not index in index_list:
                    fh.write(line)
                index += 1

    #
    def remove_lines_by_file(self, src_file_path, src_file_path_removed, dest_file_path):
        with open(src_file_path, 'rb') as src_file:
            src_lines = src_file.readlines()
        with open(src_file_path_removed, 'rb') as src_file_removed:
            src_removed_lines = src_file_removed.readlines()
        with open(dest_file_path, 'wb') as dest_file:
            for src_line in src_lines:
                if not src_line in src_removed_lines:
                    dest_file.write(src_line)

    #
    def merge_two_file(self, src_file_path, src_file_path_append, dest_file_path):
        if os.path.exists(dest_file_path):
            os.remove(dest_file_path)
        shutil.copy2(src_file_path, dest_file_path)
        with open(dest_file_path, "a") as dest_file:
            with open(src_file_path_append, 'rb') as append_file:
                for line in append_file:
                    dest_file.write(line)

if __name__ == '__main__':
    # parser = argparse.ArgumentParser(description='File Operation')

    helper = FileHelper()
    helper.remove_lines_by_file(sys.argv[1],sys.argv[2],sys.argv[3])


