import os
import sys

def extract_sha1_from_line(line):
    features, sample_path = line.split('#')
    sample_path = sample_path.strip()
    sample_dir, sample_name = os.path.split(sample_path)
    sha1 = sample_name.split(' ')[0]
    return sha1

def extract_sha1_from_feature_file(feature_file, output_file):
    with open(output_file, 'wb') as fh_output:
        with open(feature_file, 'rb') as fh_input:
            for line in fh_input.readlines():
                fh_output.write('{}\n'.format(extract_sha1_from_line(line)))

def generate_features_file_by_sha1(ori_feature_file, sha1_list_file, new_feature_file):
    sha1_list = []
    with open(sha1_list_file, 'rb') as fh:
        for line in fh.readlines():
            sha1_list.append(line.strip())
    with open(new_feature_file, 'wb') as fh_output:
        with open(ori_feature_file, 'rb') as fh_input:
            for line in fh_input.readlines():
                sha1 = extract_sha1_from_line(line)
                if sha1 in sha1_list:
                    fh_output.write(line)

def remove_dimension_by_index(ori_feature_file, index_m, index_n, new_feature_file):
    with open(new_feature_file, 'wb') as fh_output:
        with open(ori_feature_file, 'rb') as fh_input:
            for line in fh_input.readlines():
                features, sample_path = line.split('#')
                features = features.strip()
                # sample_path = sample_path.strip()
                label_feature_list = features.split(' ')
                label = label_feature_list[0]
                feature_list = label_feature_list[1:]
                new_line = '{} '.format(label)
                for feature in feature_list:
                    if feature == '':
                        continue
                    index, value = feature.split(':')
                    if index_m <= int(index) <= index_n:
                        pass
                    else:
                        new_line += feature
                        new_line += ' '
                new_line += '#'
                new_line += sample_path
                fh_output.write(new_line)

help_msg = """
Usage:
    (1) extract all of sha1 list from feature file
    >> python tool.py -s feature_file extracted_sha1_list
    (2) generate new feature file according to sha1 list
    >> python tool.py -n ori_feature_file sha1_list new_feature_file
    (3) remove feature dimension from m to n
    >> python tool.py -r ori_feature_file m n new_feature_file

"""

if __name__ == '__main__':
    try:
        if sys.argv[1] != '-s' and sys.argv[1] != '-n' and sys.argv[1] != '-r':
            print(help_msg)
            exit(-1)
    except Exception, e:
        print(help_msg)
        exit(-1)
    if sys.argv[1] == '-s':
        extract_sha1_from_feature_file(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == '-n':
        generate_features_file_by_sha1(sys.argv[2], sys.argv[3], sys.argv[4])
    elif sys.argv[1] == '-r':
        remove_dimension_by_index(sys.argv[2], int(sys.argv[3]), int(sys.argv[4]), sys.argv[5])
    else:
        print(help_msg)

