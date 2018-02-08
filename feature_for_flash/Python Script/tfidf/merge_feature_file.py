import os
import sys
import json
import decimal  
from decimal import getcontext, Decimal
def merge(out_folder):
    feature_file=sys.argv[2]
    normal_out_file=os.path.join(out_folder,"normal_feature.txt")
    malicious_out_file=os.path.join(out_folder,"malicious_feature.txt")
    f_out_normal=open(normal_out_file,"a+")
    f_out_malicious=open(malicious_out_file,"a+")
    feature=open(feature_file)
    all_key_dict={}
    for line in feature.readlines():
      line=line.strip('\n')
      index=line.split(':')[0]
      if int(index)>11:
        all_key_dict[index]=0
    
    for file in os.listdir(out_folder):       
        if file.endswith(".json"):
            filename=file[:-5]
            #flash_path=os.path.join(flash_folder,filename)                    
            file_full_path=os.path.join(out_folder,file)
            with open(file_full_path, 'r') as f:
                print file_full_path
                datadict = json.load(f)
                for data in datadict:
                    if "flash_file_path" in data:
                      data.pop("flash_file_path")
                    if "flash_label" in data:
                      data.pop("flash_label")
                for data in datadict:
                    for key in sorted(data.keys(),key=int):
                       value=data[key]
                       #if value!="0":
                       if key in all_key_dict:
                         if int(value)>all_key_dict[key]:
                           all_key_dict[key]=int(value)
    #pdb.set_trace()
    
    for file in os.listdir(out_folder):       
        if file.endswith(".json"):
            filename=file[:-5]
            flash_path=""
            stringline=""
            label=""
            file_full_path=os.path.join(out_folder,file)
            with open(file_full_path, 'r') as f:
                datadict = json.load(f)
                for data in datadict:
                    if "flash_file_path" in data:
                      flash_path=data["flash_file_path"]
                      data.pop("flash_file_path")
                    if "flash_label" in data:
                      label=data["flash_label"]
                      
                      if label=="malicious":
                        stringline="1"
                      else:
                        stringline="0"
                      data.pop("flash_label")
                for data in datadict:
                    for key in sorted(data.keys(),key=int):
                        value=data[key]
                        #if value!="0":
                        new_value=value
                        if key in all_key_dict:
                          max=all_key_dict[key]
                          if max==0:
                            print key,max
                            #pdb.set_trace()
                            new_value=0
                          else:
                            new_value=float(value)/max
                            new_value = Decimal(new_value).quantize(Decimal('0.000000'))
                        if new_value!=0:
                            stringline=stringline+"\t"+key+":"+str(new_value)
                stringline=stringline+"\t"+"#"+"\t"+flash_path
                #print stringline
                if label=="normal":
                  f_out_normal.write(stringline+"\n")
                if label=="malicious":
                  f_out_malicious.write(stringline+"\n")
    f_out_normal.close()
    f_out_malicious.close()
   # print "!!!!!!!!!!please check file in {0}".format(out_file) 
if __name__=="__main__":
  merge(sys.argv[1])