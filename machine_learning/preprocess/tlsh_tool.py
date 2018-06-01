import os
import sys
import tlsh
from optparse import OptionParser

# https://github.trendmicro.com/CoreTech-ERS/Library-tlsh
#

def get_tlsh(file_path):
    try:
        with open(file_path, 'rb') as fh:
            return tlsh.hash(fh.read())
    except Exception as e:
        print('ERROR: cannot get TLSH of file: {}'.format(file_path))
        print(e)
        return None

def gen_csv_for_file(file_path, output_dir):
    tlsh_hash = get_tlsh(file_path)
    dir_path, file_name = os.path.split(file_path)
    csv_file = os.path.join(output_dir, 'file_tlsh_{}_{}.csv'.format(file_name, tlsh_hash))
    with open(csv_file, 'w') as fh:
        fh.write('{},{}\n'.format(file_path, tlsh_hash))
    return csv_file

def gen_csv_for_dir(input_dir, output_dir):
    if input_dir[-1] == '/':
        input_dir = input_dir[0:-1]
    parent_dir_path, dir_name = os.path.split(input_dir)
    csv_file = os.path.join(output_dir, 'dir_tlsh_{}.csv'.format(dir_name))
    
    with open(csv_file, 'w') as fh:
        for root, dirs, files in os.walk(input_dir):
            for name in files:
                file_path = os.path.join(root, name)
                tlsh_hash = get_tlsh(file_path)
                fh.write('{},{}\n'.format(file_path, tlsh_hash))
    return csv_file

def gen_csv(target_path, output_dir):
    if not os.path.exists(target_path):
        print('ERROR: cannot find {}'.format(target_path))
        return None
    if os.path.isfile(target_path):
        return gen_csv_for_file(target_path, output_dir)
    elif os.path.isdir(target_path):
        return gen_csv_for_dir(target_path, output_dir)
    else:
        return None

# def scan_csv(csv_file):
#     output = os.popen('./tlsh_pattern -pat coinminer-experiment.tpat -l "{}" -lcsv -l2 -showmiss 10000'.format(csv_file))
#     buf = output.read()
#     output.close()
#     return buf

def dump_file_tlsh(file_path):
    tlsh_value = get_tlsh(file_path)
    print('File:{}, TLSH:{}'.format(file_path, tlsh_value))

def dump_dir_tlsh(dir_path):
    for root, dirs, files in os.walk(dir_path):
        for name in files:
            dump_file_tlsh(os.path.join(root, name))

def dump_tlsh(target_path):
    if os.path.isfile(target_path):
        dump_file_tlsh(target_path)
    elif os.path.isdir(target_path):
        dump_dir_tlsh(target_path)
    else:
        pass

# def scan_csv_dir(dir_file):
#     for root, dirs, files in os.walk(input_dir):
#         for name in files:
#             name_wo_ext, ext = os.path.splitext(name)
#             if ext == '.csv':
#                 pass

help_msg = """
    1. get TLSH value from file
        >> python tlsh_tool.py --tlsh file_path
    2. generate CSV file
        >> python tlsh_tool.py --gen target_path --outdir output_dir
    3. dump TLSH value in terminal
        >> python tlsh_tool.py --dump target_path
"""

if __name__ == '__main__':
    try:
        parser = OptionParser(usage=help_msg)
        parser.add_option("--tlsh", dest="tlsh_source", help="specify file path, and print TLSH value")
        parser.add_option("--gen", dest="csv_source", help="specify file path, and generate CSV file")
        parser.add_option("--outdir", dest="output_dir", help="specify output dir")
        parser.add_option("--dump", dest="dump_target", help="specify file path or dir path")
        (options, args) = parser.parse_args()

        # set config in logging
        # basicConfig(filename='adversary_ml_{}.log'.format(os.getpid()), format='[%(asctime)s][%(levelname)s] - %(message)s', level=INFO)

        if options.tlsh_source:
            tlsh_hash = get_tlsh(options.tlsh_source)
            print(tlsh_hash)
        elif options.csv_source:
            print('CSV: {}'.format(gen_csv(options.csv_source, options.output_dir)))
        # elif options.scan_target:
        #     tlsh_output = scan_csv(options.scan_target)
        #     # print(tlsh_output)
        #     for line in tlsh_output.split('\n'):
        #         print(line.split('\t'))
        elif options.dump_target:
            dump_tlsh(options.dump_target)
        else:
            print(help_msg)
    except Exception as e:
        print(e)
        print(help_msg)