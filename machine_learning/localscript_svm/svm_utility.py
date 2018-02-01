# auther = Cheng Chang(SA)
# Date = 2017/1/18
import os
import sys

def str2yararule(file_path, new_file_path):
    rule_tmp = r'''
rule JSB_%s{
strings:
  $s = %s
condition:
  $s
}
'''
    count = 1
    with open(file_path, 'r') as file, open(new_file_path, 'w') as new_file:
        for line in file:
            rule = rule_tmp % (count, line.strip())
            new_file.write(rule)
            count += 1


if __name__ == '__main__':
    eval(sys.argv[1])