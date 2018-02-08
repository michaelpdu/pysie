#get html/flash sample from caws
#copy to output folder and added in sample.txt
import sys
import os
import shutil
caws_sample_folder=r'Y:\\'
frs_sample_folder=r"Z:\\"
#import MySQLdb
#import MySQLdb.cursors
import argparse
import datetime
import pdb
import glob



db_info={'host':'10.64.24.44',
          'user':'root',
          'password':'111111',
          'database':'detectiontest'
          }

table_name='totaldetail_date'


def get_sample(type,begin_date,end_date):
    out_dir=os.path.join(os.getcwd(),"out_sample")
    if not os.path.exists(out_dir):
        os.mkdir(out_dir)
    for folder in os.listdir(frs_sample_folder):
        if folder>=begin_date and folder <=end_date:
            match=frs_sample_folder+"\\"+folder+"\\*\\"+"EKfile_"+type
            folderlist=glob.glob(match)
            if len(folderlist)>0:
              for flash_folder in folderlist:
                  #flash_folder=folderlist[0]
                  for file in os.listdir(flash_folder):
                      file_full_path=os.path.join(flash_folder,file)
                      print file_full_path
                      shutil.copy(file_full_path,out_dir)
    for folder in os.listdir(caws_sample_folder):
        if folder>=begin_date and folder <=end_date:
            match=caws_sample_folder+"\\"+folder+"\\*\\"+"EKfile_"+type
            folderlist=glob.glob(match)
            if len(folderlist)>0:
              for flash_folder in folderlist:
                  #flash_folder=folderlist[0]
                  for file in os.listdir(flash_folder):
                      file_full_path=os.path.join(flash_folder,file)
                      print file_full_path
                      shutil.copy(file_full_path,out_dir)
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('-t', '--type', help="choose a type", default = '')
    parser.add_argument('-r', '--rule', help="choose a rule", default = '.')
    parser.add_argument('-s', '--begin_date', help="choose a begin date", default = '')
    parser.add_argument('-e', '--end_date', help="choose a end-date", default = '')

    args = parser.parse_args()
    type = args.type
    rule = args.rule
    begin_date = args.begin_date
    end_date = args.end_date

    assert type != ''

    #pdb.set_trace()
    if '' == end_date:
        end_date = ( datetime.date.today()).strftime("%Y-%m-%d")
    if '' == begin_date:
        begin_date = (datetime.datetime.strptime(end_date, "%Y-%m-%d") - datetime.timedelta(days = 365) ).strftime("%Y-%m-%d") +" 00:00:00"
    end_date = end_date +" 00:00:00"
    get_sample(type,begin_date,end_date)
    #sha1_list=get_distinct_sha1_form_db(type, rule, begin_date, end_date )
    #filter_new_sha1_from_file(sha1_list,type, rule)
