import os
import sys
import getopt
import pdb
def generate(key_word_file,feature_number):
  f=open(key_word_file)
  number_count=11
  string_count=501
  all_count=0
  out_file="flash_features_"+str(feature_number)+".txt"
  f_out=open(out_file,'w+')
  for line in f.readlines():
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
    if type=="number":
      f_out.write(str(number_count)+':'+keyword+'\n')
      number_count+=1
      all_count+=1
    elif type=="string":
      #if string_count==629:
        #print ord(keyword)
      f_out.write(str(string_count)+':'+keyword+'\n')
      string_count+=1
      all_count+=1
    if all_count==feature_number:
      break
      

if __name__=="__main__":
    optlist, args = getopt.getopt(sys.argv[1:], 'f:n:')
    opt_dict = {}
    print optlist
   # global config_path
    #pdb.set_trace()
    for option,value in optlist:
        opt_dict[option] = value
    if '-f' not in opt_dict or '-n' not in opt_dict:
      print"-f key_word_file;-n feature number"
    key_word_file=opt_dict['-f']
    feature_number=int(opt_dict['-n'])
    generate(key_word_file,feature_number)