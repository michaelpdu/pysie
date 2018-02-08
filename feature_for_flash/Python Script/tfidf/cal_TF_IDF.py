import os
import pdb
import math
import sys
from operator import itemgetter

f_totalcount=open(sys.argv[1])
total_sample_count=sys.argv[2]

TF_IDF={}
TF_IDF_list=[]
#calc the max keyword count
max_keyword=0
for line in f_totalcount.readlines():
  line=line.strip('\n')
  if len(line.split(',"'))<3:
      continue
  line=line.strip('\n')
  keyword=line.split(',"')[0].strip('"')
  if keyword=="" or keyword=="\t" or keyword=="\n":
    continue
  if len(keyword)==1 and (ord(keyword)==13 or ord(keyword)==32):
    continue
  count=line.split(',"')[1].rstrip('"')
  type=line.split(',"')[2].rstrip('"')
  max_keyword=count
  break
f_totalcount.close()
f_totalcount=open(sys.argv[1])
#calc TF_IDF
for line in f_totalcount.readlines():
  #pdb.set_trace()
  line=line.strip('\n')
  if len(line.split(',"'))<4:
      continue
  line=line.strip('\n')
  keyword=line.split(',"')[0].strip('"')
  if keyword=="" or keyword=="\t" or keyword=="\n":
    continue
  if len(keyword)==1 and (ord(keyword)==13 or ord(keyword)==32):
    continue
  count=line.split(',"')[1].rstrip('"')
  if count=="":
    continue
  if int(count)<10:
    continue
  type=line.split(',"')[2].rstrip('"')
  sample_count=line.split(',"')[3].rstrip('"')
  TF=float(count)/float(max_keyword)
  IDF=math.log(float(total_sample_count)/float(sample_count))
  value=TF*IDF
  TF_IDF["keyword"]=keyword
  TF_IDF["TF_IDF"]=value
  TF_IDF["type"]=type
  TF_IDF_list.append(TF_IDF.copy())
rows_by_count = sorted(TF_IDF_list, key=itemgetter('TF_IDF'),reverse=True)
f=open("key_word_by_TF_IDF.txt","w+")
for data in rows_by_count:
  f.write('"'+data["keyword"]+'","'+str(data["TF_IDF"])+'","'+data["type"]+'"\n')
f.close()
f_totalcount.close()
    