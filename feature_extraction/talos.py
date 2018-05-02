# -*- coding=utf-8 -*-
import os
import sys
import json
import platform
import multiprocessing
from ctypes import *
from logging import *
from optparse import OptionParser
from collections import OrderedDict

from tmsie_wrapper import TmsieWrapper
from keyword_feature_analyzer import KeywordFeatureAnalyzer

def GetSampleData(sample_path):
    if not os.path.exists(sample_path):
        warning("[GetSampleData] Cannot find sample, " + sample_path)
        return ""
    with open(sample_path, 'rb') as f:
        return f.read()


class Talos:
    """"""
    def __init__(self, config):
        self.tmsie_ = TmsieWrapper(self.get_dll_path(config))
        log_path = b"tmsie.log"
        # self.tmsie_.TMSIE_SetOption(self.tmsie_.TMSIE_OPT_LOG_PATH, log_path, len(log_path))
        # self.tmsie_.TMSIE_SetOption(self.tmsie_.TMSIE_OPT_LOG_LEVEL, self.tmsie_.TMSIE_LOG_INFO, 4)

    def get_dll_path(self, config):
        sie_build_root = config['tmsie']['build_path']
        dll_path = ''
        if platform.system() == 'Windows':
            if platform.architecture()[0] == '64bit':
                dll_path = os.path.join(sie_build_root, 'Windows', 'x64', 'tmsie64.dll')
            else:
                dll_path = os.path.join(sie_build_root, 'Windows', 'x86', 'tmsie32.dll')
        elif platform.system() == 'Linux':
            if platform.architecture()[0] == '64bit':
                dll_path = os.path.join(sie_build_root, 'Linux', 'x64', 'libtmsie.so')
            else:
                dll_path = os.path.join(sie_build_root, 'Linux', 'x86', 'libtmsie.so')
        else:
            print('[ERROR] Unknown platform')
        return dll_path

    def get_features(self, sample_path):
        try:
            debug('Get features from: ' + sample_path);
            context_id = c_uint(0)
            self.tmsie_.TMSIE_CreateContext(byref(context_id))
            ret = -1
            reserve = c_void_p()
            client_ip = b"127.0.0.1"
            ret = self.tmsie_.TMSIE_AddContent(context_id, self.tmsie_.TMSIE_HTTP_REQ_CLIENT_IP, client_ip, len(client_ip), reserve)
            if ret != 0:
                error("TMSIE_AddContent failed : TMSIE_HTTP_REQ_CLIENT_IP")
            server_ip = b"127.0.0.1"
            ret = self.tmsie_.TMSIE_AddContent(context_id, self.tmsie_.TMSIE_HTTP_REQ_SERVER_IP, server_ip, len(server_ip), reserve)
            if ret != 0:
                error("TMSIE_AddContent failed : TMSIE_HTTP_REQ_SERVER_IP")
            url = b"http://www.abcd1234sa.com.cn/index"
            ret = self.tmsie_.TMSIE_AddContent(context_id, self.tmsie_.TMSIE_HTTP_REQ_URL, url, len(url), reserve)
            if ret != 0:
                error("TMSIE_AddContent failed : TMSIE_HTTP_REQ_URL")
            req_hdr   = b"GET /abc.html HTTP/1.1\r\nConnection: Keep-Alive\r\n"
            ret = self.tmsie_.TMSIE_AddContent(context_id, self.tmsie_.TMSIE_HTTP_REQ_HDR, req_hdr, len(req_hdr), reserve)
            if ret != 0:
                error("TMSIE_AddContent failed : TMSIE_HTTP_REQ_HDR")
            req_body  = b""
            ret = self.tmsie_.TMSIE_AddContent(context_id, self.tmsie_.TMSIE_HTTP_REQ_BODY, req_body, len(req_body), reserve)
            if ret != 0:
                error("TMSIE_AddContent failed : TMSIE_HTTP_REQ_BODY")
            resp_hdr  = b"HTTP/1.0 200 OK\r\nContent-Length: 1024"
            ret = self.tmsie_.TMSIE_AddContent(context_id, self.tmsie_.TMSIE_HTTP_RESP_HDR, resp_hdr, len(resp_hdr), reserve)
            if ret != 0:
                error("TMSIE_AddContent failed : TMSIE_HTTP_RESP_HDR")
            resp_body = GetSampleData(sample_path)
            ret = self.tmsie_.TMSIE_AddContent(context_id, self.tmsie_.TMSIE_HTTP_RESP_BODY, resp_body, len(resp_body), reserve)
            if ret != 0:
                error("TMSIE_AddContent failed : TMSIE_HTTP_RESP_BODY")
            decision = c_int(100)
            ret = self.tmsie_.TMSIE_Scan(context_id, byref(decision), reserve)
            debug('Get scan result: {}'.format(ret))
            try:
                reserve = c_void_p()
                result_len = c_ulong(0)
                c_result = c_char_p()
                self.tmsie_.TMSIE_GetScanResult(context_id, self.tmsie_.TMSIE_HEU_FEATURES_DESC, c_result, byref(result_len))

                if result_len != 0:
                    result = create_string_buffer(result_len.value)
                    self.tmsie_.TMSIE_GetScanResult(context_id, self.tmsie_.TMSIE_HEU_FEATURES_DESC, result, byref(result_len))
                    feature_buf = str(result.value)
                    if not feature_buf:
                        warning('Cannot extract feature from: ' + sample_path)
                        return None
                    else:
                        return feature_buf
                else:
                    warning('Feature buffer length is 0, sample: ' + sample_path)
                    return None
            except Exception,e:
                warning("Exception in getting feature: " + e)
                return None
        except Exception,e:
            warning("Exception in fake SIE scan: " + e)
            return None

    def get_libsvm_format(self, label, features, comments):
        return '{} {} # {}\n'.format(label, features, comments)

    def dump_features(self, target_path, dest_path, label):
        with open(dest_path, 'w') as fh:
            for root, dir, samples in os.walk(target_path):
                for sample in samples:
                    sample_path = os.path.join(root, sample)
                    features = self.get_features(sample_path)
                    if features != None:
                        fh.write(self.get_libsvm_format(label, features, sample_path))

    def dump_features_from_list(self, sample_path_list, dest_path, label):
        with open(dest_path, 'w') as fh:
            for sample_path in sample_path_list:
                features = self.get_features(sample_path)
                if features != None:
                    fh.write(self.get_libsvm_format(label, features, sample_path))

def process_file_list_by_talos(config, id, label, file_list, dest_file):
    msg = 'Run process: {}, size of file_list: {}'.format(id, len(file_list))
    info(msg)
    print(msg)
    talos = Talos(config)
    talos.dump_features_from_list(file_list, dest_file, label)

def dump_features_multi_process(config, label, target_path, dest_path):
    process_num = config['common']['process_num']
    if config['common']['use_system_cpu_num']:
        process_num = multiprocessing.cpu_count()
        info('Use CPU number, thread number is {}'.format(process_num))
    else:
        info('Use default config, thread number is {}'.format(process_num))

    file_list_map = {}
    for i in range(0,process_num):
        file_list_map[i] = []
    with open(dest_path, 'w') as output:
        if os.path.isdir(target_path):
            i = 0
            for root, dirs, files in os.walk(target_path):
                for name in files:
                    file_path = os.path.join(root, name)
                    file_list_map[i%process_num].append(file_path)
                    i += 1
        else:
            print '[ERROR] multi-process only process folder'
            exit(-1)
    #
    proc_list = []
    file_path_wo_filename, filename = os.path.split(dest_path)
    filename_wo_ext, ext = os.path.splitext(filename)
    output_list = []
    for i in range(0,process_num):
        new_target_path = os.path.join(file_path_wo_filename, '{}_proc_{}{}'.format(filename_wo_ext, i, ext))
        output_list.append(new_target_path)
        proc = multiprocessing.Process(target=process_file_list_by_talos, args=(config, i, label, file_list_map[i], new_target_path))
        proc_list.append(proc)

    for proc in proc_list:
        proc.start()

    # Wait for all threads to complete
    for proc in proc_list:
        proc.join()

    # merge all of outputs
    if os.path.exists(dest_path):
        os.remove(dest_path)
    dest_fh = open(dest_path, 'wb')
    for file_path in output_list:
        with open(file_path, 'rb') as fh:
            dest_fh.write(fh.read())
        os.remove(file_path)
    dest_fh.close()
    print "Exiting Main Process"

if __name__ == "__main__":
    option_parser = OptionParser()
    option_parser.add_option("--dump-feature", dest='target_path', help="target path", type="string")
    option_parser.add_option("--label", dest='label', help="malicious:1 , normal:0", type="string")
    option_parser.add_option("--dest-file", dest='dest_file', help="destination file", type="string")

    try:
        basicConfig(filename='talos.log', format='[%(asctime)s][%(levelname)s] - %(message)s', level=DEBUG)

        (options, args) = option_parser.parse_args()
        with open('talos.cfg', 'rb') as fh:
            config = json.load(fh)
        info('Load config from talos.cfg')

        if config['common']['use_multiple_process'] == True:
            info('Multiple thread mode')
            dump_features_multi_process(config, int(options.label), options.target_path, options.dest_file)
        else:
            talos = Talos(config)
            talos.dump_features(options.target_path, options.dest_file, int(options.label))
    except Exception,e:
        print(e)
        option_parser.print_help()