import sys
import os
import shutil
out_folder=os.path.join(os.getcwd(),"feature_sample")
if not os.path.exists(out_folder):
  os.mkdir(out_folder)
feature="0"

with open(sys.argv[1], 'rb') as fh:
    lines = fh.readlines()
    for line in lines:
      #line=line.strip('\r')
      #line=line.strip('\t')
      #line=line.strip('\r\n')
      if  feature in line:
        
        path=line.split('#')[1]
        path=path.strip('\t')
        path=path.strip('\r\n')
        if '@' in path:
          print path
          path=path.split(' ')[0]
          #print path
        if os.path.exists(path):
          shutil.copy(path,out_folder)
          os.remove(path)