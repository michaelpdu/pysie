# coding=utf-8
import os
import sys
import struct
import re

def judge_file_type(filename):
    if suffix_func(filename) != 'unknown':
        return suffix_func(filename)
    elif file_header_func(filename) != 'unknown':
        return file_header_func(filename)
    elif text_func(filename) != 'unknown':
        return text_func(filename)
    return 'unknown'

def suffix_func(filename):
    ext = os.path.splitext(filename)[1]
    if ext != '':
        return ext[1:]
    return 'unknown'

def file_header_func(filename):
    binfile = open(filename, 'rb')
    tl = typeList()
    ftype = 'unknown'  
    for hcode in tl.keys():  
        numOfBytes = len(hcode) / 2
        binfile.seek(0)
        hbytes = struct.unpack_from("B"*numOfBytes, binfile.read(numOfBytes))
        f_hcode = bytes2hex(hbytes)
        if f_hcode == hcode:  
            ftype = tl[hcode]
            break  
    binfile.close()  
    return ftype

# 支持文件类型
# 用16进制字符串可以知道文件头是多少字节  
# 各种文件头的长度不一样，2字符~8字符  
def typeList():
    file_type_list_file = os.path.join(os.path.split(os.path.realpath(__file__))[0], 'Common file header.cfg')
    type_list = {}
    with open(file_type_list_file, 'r') as file_type:
        for line in file_type:
            matched, replaced = line.split('=')
            type_list[matched.strip()] = replaced.strip()
    return type_list

def bytes2hex(bytes):  
    num = len(bytes)  
    hexstr = u""  
    for i in range(num):  
        t = u"%x" % bytes[i]  
        if len(t) % 2:  
            hexstr += u"0"  
        hexstr += t  
    return hexstr.upper()  

def text_func(filename):
    with open(filename, 'r') as file:
        s = file.read().lower()
        dim_matched = re.search(r'\bdim\b', s)
        endif_matched = re.search(r'\bend if\b', s)
        if dim_matched is not None and endif_matched is not None:
            return 'vbs'
    return 'unknown'

if __name__ == '__main__':
    print judge_file_type(sys.argv[1])  