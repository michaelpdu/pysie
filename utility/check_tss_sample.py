import os, sys

count_all = 0
count_normal_file = 0
count_less_than_5 = 0
count_accumulated_issue = 0
count_imcomplete_sample = 0

def select_larger_line(lines):
    largest_index = 0
    largest_len = 0
    for i in range(0,len(lines)):
        length = len(lines[i])
        if length > largest_len:
            largest_index = i
            largest_len = length
    return lines[largest_index]

def check_file(file_path):
    global count_all
    global count_normal_file
    global count_less_than_5
    global count_accumulated_issue 
    global count_imcomplete_sample 

    count_all = count_all + 1
    with open(file_path, 'rb') as fh:
        lines = fh.readlines()
        if len(lines) > 5:
            find_end_tag = False
            largest_line = select_larger_line(lines[0:5])
            for line in lines[5:]:
                if largest_line in line:
                    count_accumulated_issue = count_accumulated_issue + 1
                    return 1
                if '</body>' in line or '</html>' in line:
                    find_end_tag = True
            if find_end_tag:
                count_normal_file = count_normal_file + 1
                return 0
            else:
                count_imcomplete_sample = count_imcomplete_sample+1
                return 2
        else:
            return -1

def check_folder(folder_path):
    for root, dirs, files in os.walk(folder_path):
        for name in files:
            target = os.path.join(root, name)
            status = check_file(target)
            if -1 == status:
                print('{}, count of lines less than 5'.format(target))
            elif 0 == status:
                print('{}, normal file'.format(target))
            elif 1 == status:
                os.remove(target)
                print('{}, accumulated issus'.format(target))
            elif 2 == status:
                print('{}, cannot find end tag'.format(target))
            else:
                print('{}, Unsupported status'.format(target))

def print_statistic_info():
    global count_all
    global count_normal_file
    global count_less_than_5
    global count_accumulated_issue 
    global count_imcomplete_sample 

    print('\n\n********************************************')
    print('All: {}\nNormal: {}\nAccumulated Issue: {}\nIncomplete Sample: {}\nLess than 5: {}\n'.format(count_all, count_normal_file, count_accumulated_issue, count_imcomplete_sample, count_less_than_5))
    print('********************************************\n\n')

help_msg = """
Usage:
    python check_tss_sample.py target_path
"""

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(help_msg)
        exit(-1)
    check_folder(sys.argv[1])
    print_statistic_info()