from __future__ import unicode_literals
import os
import time
import pdb
import subprocess
import json
import collections
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
import time
import datetime
from multiprocessing import Process, Queue
#from split import SplitHelper
import operator
import math
import types
from operator import itemgetter
import getopt
queue = Queue()

 

def produce_file(dir_path):

     all_files = []
     for root,dirs,files in os.walk(dir_path):
         for file in files:
             if file.endswith('.json') or file.endswith('.txt'):
                continue
             file_path = os.path.join(root,file)
             all_files.append(file_path)
     return all_files
 
def extract(file_path,out_folder):

    filename=os.path.basename(file_path)
    out_path=out_folder+"\\"+filename+".json"
    if not os.path.exists(out_path):
        
      cmd="FlashML_autofeature.exe -p {0} -o {1}".format(file_path,out_path)
      #print cmd
      print file_path
      subprocess.call(cmd,shell=True)
 
def worker(queue,out_folder):
     
     for file_path in iter(queue.get,"STOP"):
     
         extract(file_path,out_folder)
         #insert_mysql(file_path,file_md5)
     return True
 
def main(out_folder,flash_folder):    
     all_files = produce_file(flash_folder)
     for file_path in all_files:
         queue.put(file_path)     
     workers = 4
     processes = []
     for w in xrange(workers):
         p = Process(target=worker,args=(queue,out_folder))
         p.start()
         processes.append(p)
         queue.put("STOP")
     for p in processes:
         p.join()
         
def merge(out_folder):
    all_number_dict_by_word={}
    all_string_dict_by_word={}
    all_number_dict_by_sample={}
    all_string_dict_by_sample={}
    all_featuredict_list=[]
    for file in os.listdir(out_folder):
        if file.endswith(".json"):
            file_full_path=os.path.join(out_folder,file)
            #print file_full_path
            with open(file_full_path, 'r') as f:
                f_str=f.read()                
                try:
                  datadict = json.loads(f_str)
                except:
                  continue
                if len(datadict)!=2:
                  continue
                constant_number=datadict[0]
                constant_string=datadict[1]              
                if constant_string!=None:    
                  for key,value in constant_string.items():                   
                      if key in all_string_dict_by_word:                       
                        all_string_dict_by_word[key]=int(int(value)+all_string_dict_by_word[key])
                        all_string_dict_by_sample[key]=int(1+all_string_dict_by_sample[key])
                      else:
                        all_string_dict_by_word[key]=int(value)
                        all_string_dict_by_sample[key]=1
                if constant_number!=None:    
                  for key,value in constant_number.items():
                      if key in all_number_dict_by_word:                       
                        all_number_dict_by_word[key]=int(int(value)+all_number_dict_by_word[key])
                        all_number_dict_by_sample[key]=int(1+all_number_dict_by_sample[key])
                      else:
                        all_number_dict_by_word[key]=int(value)
                        all_number_dict_by_sample[key]=1
    for key in all_number_dict_by_word:
      feature_dict={}
      feature_dict["keyword"]=key
      feature_dict["count"]=all_number_dict_by_word[key]
      feature_dict["type"]="number"
      feature_dict["sample_count"]=all_number_dict_by_sample[key]
      all_featuredict_list.append(feature_dict.copy())
    for key in all_string_dict_by_word:
      feature_dict={}
      feature_dict["keyword"]=key
      feature_dict["count"]=all_string_dict_by_word[key]
      feature_dict["type"]="string"
      feature_dict["sample_count"]=all_string_dict_by_sample[key]
      all_featuredict_list.append(feature_dict.copy())
    rows_by_count = sorted(all_featuredict_list, key=itemgetter('count'),reverse=True)
    f=open("key_word.txt","w+")
    for data in rows_by_count:
      f.write('"'+data["keyword"]+'","'+str(data["count"])+'","'+data["type"]+'","'+str(data["sample_count"])+'"\n')
    

def sort_by_value(d):
  items=d.items()
  backitems=[[v[1],v[0]] for v in items]
  
  backitems.sort(reverse = True)
  return backitems


def splitfile(out_file):
    if os.path.exists(out_file):
      try:
          s = SplitHelper()
          s.analyze(out_file, 0.7)
      except Exception,e:
          print help_msg
          print 'Exception: {}'.format(str(e))

if __name__ == "__main__":

    optlist, args = getopt.getopt(sys.argv[1:], 'e:m:p:')
    opt_dict = {}
    print optlist
   # global config_path
    for option,value in optlist:
        opt_dict[option] = value
    
    global out_folder
    out_folder=os.path.join(os.getcwd(),"out_json")
    #out_file_number=os.path.join(flash_folder,"out_json")+"\\"+"out_file_number.txt"
    #out_file_string=os.path.join(flash_folder,"out_json")+"\\"+"out_file_string.txt"
    if not os.path.exists(out_folder):
      os.mkdir(out_folder)
    if '-e' in opt_dict:
        flash_folder=opt_dict['-e']
        main(out_folder,flash_folder)
    if '-m'in opt_dict:
      out_folder=opt_dict['-m']
      merge(out_folder)
 
    
   
    