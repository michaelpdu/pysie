import os
import shutil
from epc2saz import dealwithPro
import hashlib
import sys
def get_url(file_name,result_file):
    #print 'geturl'
    url=""
    fp=open(result_file,"r")

    for line in fp.readlines():

        if file_name in line:

            url=line.split(",")[7]
    #print url
    return url
def process(sample_folder,result_file=None):
    for file in os.listdir(sample_folder):
        file_name=os.path.basename(file)
        file_path=os.path.join(sample_folder,file_name)
        if file_name.endswith(".txt"):
            continue
        if os.path.isfile(file_path):
            print file_name
            fp=open(file_path,"r")
            line = fp.readline()
            if line.startswith("========== Plugin Info Begin =========="):
                saz_folder=os.path.join(sample_folder,"saz")
                bk_folder=os.path.join(saz_folder,"saz_bk")
                if not os.path.exists(saz_folder):
                    os.makedirs(saz_folder)
                if not os.path.exists(bk_folder):
                    os.makedirs(bk_folder)
                fp.close()
                dealwithPro(file_path, saz_folder)
                if result_file==None:
                    print 'not found result_file'
                else:
                    url=get_url(file_name,result_file)
                    extract_file(file_path,url,saz_folder)
                    shutil.move(file_path,bk_folder)
            # else:
            #     fp.close()
            #     sha1=file_name
            #     #url=get_url(file_name,result_file)
            #     result=get_sha1_result(sha1)
            #     if result=="normal":
            #         shutil.move(file_path, normal_sample_folder)
            #     elif result=="malicious" :
            #         shutil.move(file_path, malicious_sample_folder)
            #     elif result == "suspicious" :
            #         shutil.move(file_path, suspicious_sample_folder)
            #     else:
            #         print "Error query result in virustotal or Not Found"



# def get_sha1_result(sha1):
#     result="suspicious"
#     vs=VirusTotal()
#     search_result=vs.searchSha1(sha1)
#     time.sleep(2)
#     if ("/") in search_result:
#         detected=int(search_result.split("/")[0])
#
#         if detected<2:
#             result="normal"
#         elif detected>10:
#             result="malicious"
#     else:
#         result="error"
#     print search_result
#     print result
#     return result
# def get_url_result(url):
#     result="suspicious"
#     vs=VirusTotal()
#     search_result=vs.analyseUrl(url)
#     time.sleep(5)
#     if ("/") in result:
#         detected=result.split("/")[0]
#         if detected<2:
#             result="normal"
#         elif detected>10:
#             result="malicious"
#     else:
#         result="error"

def extract_folder(sazfolder,result_file):
    print 'extract_folder'
    for file in os.listdir(sazfolder):
        file_name=os.path.basename(file)
        file_path=os.path.join(sazfolder,file_name)
        if os.path.isfile(file_path) and file_name.endswith('saz'):
            url=get_url(file_name[:-4],result_file)
            outdir=os.path.join(sazfolder,file_name[:-4])
            if not os.path.exists(outdir):
                os.makedirs(outdir)
            extract_file(file_path, url,outdir)


def extract_file(sazfile,url,outdir):
    #saz_folder=  os.path.dirname(os.path.abspath(outdir))
    #print 'sazfolder',saz_folder
    if not os.path.exists(outdir):
        os.makedirs(outdir)
    content="Content: \n"
    print url
    recordFile=open(os.path.join(outdir,"extractResult.txt"),'a')
    epc_file_data = open(sazfile, 'rb').read()
    urlIndex=epc_file_data.find(url)
    epc_file_data=epc_file_data[urlIndex:]
    contentIndex=epc_file_data.find(content)
    endFlag="========== PageInfo End =========="
    epc_file_data=epc_file_data[contentIndex+len(content):]
    body_endIndex=epc_file_data.find("URL: ")
    if body_endIndex < 0:
        body_endIndex=epc_file_data.find(endFlag)
    epc_file_data=epc_file_data[:body_endIndex]
    #epc_file_data=epc_file_data.lstrip('\r\n')
    sha1obj = hashlib.sha1()
    sha1obj.update(epc_file_data)
    hash = sha1obj.hexdigest()
    resultFile = open(os.path.join(outdir, hash), "wb")
    resultFile.write(epc_file_data)

    resultFile.close()
    resultFile = open(os.path.join(outdir, hash), "rb")
    recordFile.write(hash+','+sazfile)
    recordFile.write("\n")
    recordFile.close()
if __name__=="__main__":
    #extract_file(r'E:\sample\201705_SWF%__62614\saz\saz_bk\000f1091c849efb77edd194e28b7861a1eedbb07','http://app3-cdn2.sbx-cdn.com/content/compliance/uid.swf',r'E:\sample\201705_SWF%__62614\saz')

    if len(sys.argv)<3:
        print "process.py sampledir [resultfile]"
        exit(0)
    else:
        sample_dir=sys.argv[1]
        result_file=sys.argv[2]
        process(sample_dir,result_file)
        




