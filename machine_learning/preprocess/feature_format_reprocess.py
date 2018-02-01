import os, sys

def format_feature(feature_file):
    if not os.path.exists(feature_file):
        print(" file not exist!")
    new_feature_file =feature_file + "_new"
    with open(new_feature_file, 'w+') as ffd:
        with open(feature_file, 'r+') as fd:
            lines = fd.readlines()
            for line in lines:
                line_words = line.split(' ')
                new_line = ""
                for word in line_words:
                    if word.endswith("0.0"):
                        continue
                    else:
                        new_line += ' '
                        new_line += word
                new_line = new_line.lstrip()
                ffd.write(new_line)


def format_feature_file(feature_file):
    feature_dict = {}
    new_feature_file = feature_file+"_new"
    with open(new_feature_file, 'w+') as fd:
        with open(feature_file, 'r+') as fd2:
            lines = fd2.readlines()
            for line in lines:
                key = line[line.rfind('/') + 1:]
                key = key.strip('\n')
                feature_dict[key] = line[:line.find('#')]
        for key in sorted(feature_dict.keys()):
            new_line = key + ':' + feature_dict[key]
            fd.write(new_line)
            fd.write('\n')


def get_matched_feature_index(feature_file): # sha1: index1 index2
    feature_dict = {}
    new_feature_file = feature_file + "_new_index"
    with open(new_feature_file, 'w+') as fd:
        with open(feature_file, 'r+') as fd2:
            lines = fd2.readlines()
            for line in lines:
                key = line[line.rfind('/') + 1:]
                key = key.strip('\n')
                new_line = line[:line.find('#')]
                temp_line = ""
                for word in new_line.split(' '):
                    temp_line += word[:word.find(':')]
                    temp_line += ' '
                feature_dict[key] = temp_line
        for key in sorted(feature_dict.keys()):
            new_line = key + ':' + feature_dict[key]
            fd.write(new_line)
            fd.write('\n')


def get_index_gap_between_feature_file(feature_file_1, feature_file_2):
    gap_dict = {}


def combine_feature_with_result_file(feature_file, result_file): # sha1: label
    result = []
    new_result_file = result_file + "_new"
    with open(result_file, 'r+') as fd:
        result = fd.readlines()
    index = 0
    with open(new_result_file, 'w+') as fd:
        with open(feature_file, 'r+') as fd2:
            lines = fd2.readlines()
            for line in lines:
                key = line[line.rfind('/') + 1:]
                key = key.strip('\n')
                new_line = key + ': ' + result[index]
                fd.write(new_line)
                index += 1


def get_new_result_from_engine_result(result_file):  # sha1: label
    new_result_file = result_file + "_new"
    with open(new_result_file, 'w+') as fd:
        with open(result_file, 'r+') as fd2:
            lines = fd2.readlines()
            for line in lines:
                if not line.startswith("file_path"):
                    continue
                label = '0'
                if line.find("decision=suspicious") != -1 or line.find("decision=malicious") != -1:
                    label = '1'
                index_1 = line.find(":0")
                index_2 = line.rfind('/', 0, index_1)
                key = line[index_2 + 1:index_1]
                new_line = key + ': ' + label
                fd.write(new_line)
                fd.write('\n')


if __name__ == "__main__":
    print(" python xxx.py -a feature_file_path")
    print(" python xxx.py -b feature_file_path")
    print(" python xxx.py -c feature_file_path")
    print(" python xxx.py -d feature_file_path, result_path")
    print(" python xxx.py -e engine_result_path")

    if sys.argv[1] == "-a":
        format_feature(sys.argv[2])
    elif sys.argv[1] == "-b":
        format_feature_file(sys.argv[2])
    elif sys.argv[1] == "-c":
        get_matched_feature_index(sys.argv[2])
    elif sys.argv[1] == "-d":
        combine_feature_with_result_file(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == "-e":
        get_new_result_from_engine_result(sys.argv[2])
