import os
import time
import pdb
import subprocess
import json
import collections
import sys
import time
import datetime
from multiprocessing import Process, Queue
import decimal  
from decimal import getcontext, Decimal
#from split import SplitHelper
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
 
def extract(file_path,out_folder,label,feature_file):

    filename=os.path.basename(file_path)
    out_path=out_folder+"\\"+filename+".json"
    if not os.path.exists(out_path):
        
      cmd="FlashML.exe -l {0} -p {1} -o {2} -f {3}".format(label,file_path,out_path,feature_file)
      #print cmd
      print file_path
      subprocess.call(cmd,shell=True)
 
def worker(queue,out_folder,label,feature_file):
     
     for file_path in iter(queue.get,"STOP"):
     
         extract(file_path,out_folder,label,feature_file)
         #insert_mysql(file_path,file_md5)
     return True
 
def main(label,out_folder,flash_folder,feature_file):
    
     all_files = produce_file(flash_folder)
     for file_path in all_files:
         queue.put(file_path)
     
     workers = 4
     processes = []
     for w in xrange(workers):
         p = Process(target=worker,args=(queue,out_folder,label,feature_file))
         p.start()
         processes.append(p)
         queue.put("STOP")
     for p in processes:
         p.join()

def splitfile(out_file):
    if os.path.exists(out_file):
      try:
          s = SplitHelper()
          s.analyze(out_file, 0.7)
      except Exception,e:
          print help_msg
          print 'Exception: {}'.format(str(e))
#def pre_process(label,out_folder):
   #for file in os.listdir(folder):
      #if file.endswith('.txt'):
if __name__ == "__main__":
    if len(sys.argv)<3:
        print_help()
        exit(0)
    label=sys.argv[1]
    flash_folder=sys.argv[2]
    feature_file=sys.argv[3]
    out=os.path.basename(feature_file)
    if '.txt' in out:
      out=out[0:-4]
    global out_folder
    out_folder=os.path.join(os.getcwd(),out)
    #out_file=os.path.join(flash_folder,"out_json")+"\\"+"out_file.txt"
    if not os.path.exists(out_folder):
      os.mkdir(out_folder)
    start_time = time.strftime('%c', time.localtime(time.time()))
    main(label,out_folder,flash_folder,feature_file)
    end_time = time.strftime('%c', time.localtime(time.time()))
    #merge(label,out_folder,flash_folder)
    print "start_time",start_time
    print "end_time",end_time 
    
    #splitfile(out_file)
    #pre_process(label,out_folder)
    