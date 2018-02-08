import os
import sys
from zipfile import * 
import zipfile 
import shutil



def zipDir(filename,destDir,index,resultDir): 
    currentPath = os.getcwd()
    #global resultDir
    if len(resultDir) == 0 :
        resultDir = currentPath
    if not os.path.exists(resultDir):
        os.makedirs(resultDir)
    f = zipfile.ZipFile(resultDir + "\\" + filename + '.saz','w',zipfile.ZIP_DEFLATED)
    index = destDir.rfind('\\')
    destDir = destDir[:index]
    os.chdir(destDir)
    length = len(str(index))
    for dirpath, dirnames, filenames in os.walk(destDir): 
        for filename in filenames: 
            try:
                if filename == "_index.htm":
                    f.write(filename)
                else:
                    digit = filename[:filename.find('_')]
                    if len(digit) != length:
                        newFilename = '0' * (length - len(digit)) + filename
                        os.rename(os.path.join(dirpath,filename),os.path.join(dirpath,newFilename))
                        filename = newFilename
                    #if "_s" in filename:
                    #    f2 = open(os.path.join(dirpath,filename), 'rb+')
                    #    f2.seek(-2, os.SEEK_END)
                    #    f2.truncate()
                    #    f2.close()
                    f.write("raw\\" + filename)
            except:
                print "error,zip files to saz missing,",filename
    f.close()
    os.chdir(currentPath)

def dealwithPro(filepath,resultDir): 
    print "filepath: " + filepath  
    request_str = "Request Header: "
    response_str = "Response Header: "
    url_start = "URL: http://"
    referer_start = "Referer:"    
    outer_js_url = "Outer JS url:"
    outer_js_content = "Outer JS content:"
    content = "Content:"
    
    rule_str_ignore = "Rule:"
    sha1_str_ignore = "Sha1:"
    file_type_str_ignore = "File type:"
    user_agent_str_ignore = "User agent:"
    
    content_length = "Content-Length: "
    encoding_gzip = "Content-Encoding: gzip"
    encoding_chunked = "Transfer-Encoding: chunked"
    filepath_split_array = filepath.split("\\")
    print "split size is: ",len(filepath_split_array)
    filename = filepath_split_array[len(filepath_split_array) - 1]
    print "filename : ", filename
    destDir = os.getcwd() + "\\temp_raw\\raw"
    if os.path.exists(destDir):
        shutil.rmtree(destDir)
    os.makedirs(destDir)
   
    index = 0
    flag = False
    changeLine = 0
    file = open(filepath,"rb")
    line = file.readline()
    buffer = ""
    gc_flag = False
    gc_response_flag = False
    firstLineFlag = False
    while line:                       
        if line.find(request_str) >= 0:
            #print "1 " + line
            tempLine = line[(line.find(request_str) + len(request_str)):]
            if len(tempLine.strip()) > 0 :
                flag = True
                changeLine = 0
                if index != 0:
                    if gc_flag == True:
                        ###
                        try:
                            if ord(buffer[len(buffer)-2]) == 0x0d and ord(buffer[len(buffer)-1]) == 0x0a:
                                buffer = buffer[:(len(buffer)-2)]
                            elif ord(buffer[len(buffer)-1]) == 0x0a:
                                buffer = buffer[:(len(buffer)-1)]
                            #if ord(buffer[len(buffer)-1]) == 0x0a:
                            #    buffer = buffer[:(len(buffer)-1)]
                            #if ord(buffer[0]) == 0x0a:
                            #    buffer = buffer[1:]
                        except:
                            pass
                        ###
                        resultFile.write(content_length + str(len(buffer)) + "\r\n\r\n")
                        resultFile.write(buffer)
                    resultFile.close()
                gc_flag = False
                gc_response_flag = False
                buffer = ""
                index = index + 1
                resultFile = open(os.path.join(destDir,str(index) + "_c.txt"),"wb")
                resultFile.write(line[(str(line).find(request_str) + len(request_str)):])
        elif line.find(response_str) >= 0: 
            if flag == True:
                #print "2 " + line
                #print index," ",line
                changeLine = 0
                gc_flag = False
                gc_response_flag = True
                firstLineFlag = True
                buffer = ""
                resultFile.close()
                resultFile = open(os.path.join(destDir,str(index) + "_s.txt"),"wb")
                resultFile.write(line[(line.find(response_str)+len(response_str)):])
        elif outer_js_url in line:
            #print "4 "
            pass
        elif outer_js_content in line:
            #print "5 "
            pass
        elif url_start in line:
            #print "3 " + line
            templine = line
            line = file.readline()
            if referer_start in line:
                flag = False
            elif flag == True:
                resultFile.write(templine)
                resultFile.write(line)
        elif (rule_str_ignore in line) or (sha1_str_ignore in line) or (file_type_str_ignore in line) or (user_agent_str_ignore in line):
            line = file.readline()
            continue
        elif flag == True:            
            if line.strip()!= content:               
                if changeLine == 1 and firstLineFlag == True:
                    #print "*********************FWS"
                    firstLineFlag = False                    
                    if (ord(line[0]) == 0x0d and ord(line[1]) == 0x0a) or ord(line[0]) == 0x0a:
                        changeLine = changeLine + 1
                        #print "*********************ZWS"
                        line = file.readline()
                        if (ord(line[0]) == 0x0d and ord(line[1]) == 0x0a) or ord(line[0]) == 0x0a:
                            changeLine = changeLine + 1
                            line = file.readline()
                            #print "*********************CWS"
                        continue                
                #if len(line.strip()) < 1 :
                #    changeLine = changeLine + 1
                if ord(line[0]) == 0x0d and ord(line[1]) == 0x0a :
                    changeLine = changeLine + 1
                    if changeLine == 1:
                        line = file.readline()
                        continue
                        
                #if gc_response_flag and (str(line).find(encoding_gzip) >= 0 or str(line).find(encoding_chunked) >= 0):
                if gc_response_flag :
                    gc_flag = True                
                
                if gc_flag == False:
                    resultFile.write(line)                    
                else:                    
                    if str(line).find(encoding_gzip) >= 0 or str(line).find(encoding_chunked) >= 0 or str(line).find(content_length) >= 0:
                        pass
                    elif changeLine == 0 :
                        resultFile.write(line)                    
                    elif changeLine < 2 : # 3                       
                        #if len(line.strip()) < 1 :
                        #    pass
                        #else:
                            buffer += line
                    else:
                        buffer += line
        line = file.readline()
    ###
    if gc_flag == True:
        try:
            if ord(buffer[len(buffer)-2]) == 0x0d and ord(buffer[len(buffer)-1]) == 0x0a:
                buffer = buffer[:(len(buffer)-2)]
            elif ord(buffer[len(buffer)-1]) == 0x0a:
                buffer = buffer[:(len(buffer)-1)]
            #if ord(buffer[len(buffer)-1]) == 0x0a:
            #    buffer = buffer[:(len(buffer)-1)]
            #if ord(buffer[0]) == 0x0a:
            #    buffer = buffer[1:]
        except:
            pass
        if len(buffer) > 0:
            resultFile.write(content_length + str(len(buffer)) + "\r\n\r\n")
            resultFile.write(buffer)
    ###
    try:
        resultFile.close()
        file.close()    
        generateIndexFile(index,destDir[:destDir.rfind('\\')])
        zipDir(filename,destDir,index,resultDir)
    except:
        pass

def emptyWorkspace():
    currentPath = os.getcwd()
    remove_dir = currentPath + "\\temp_raw"
    if os.path.exists(remove_dir):
        print "clear workspace:",remove_dir
        shutil.rmtree(remove_dir)
                
def generateIndexFile(index,destDir):
    head = r"<html><head><style>body,thead,td,a,p{font-family:verdana,sans-serif;font-size: 10px;}</style></head><body><table cols=12><thead><tr><th>&nbsp;</th><th>#</th><th>Result</th><th>Protocol</th><th>Host</th><th>URL</th><th>Body</th><th>Caching</th><th>Content-Type</th><th>Process</th><th>Comments</th><th>Custom</th></tr></thead><tbody>"
    body = r"<td>200</td><td>HTTP</td><td>www.tortasypostresmichelangelo.com</td><td>/wp-content/themes/shopsy/css/font-awesome.min.css?ver=4.1.1</td><td>3,974</td><td></td><td>text/css</td><td></td><td></td><td></td>"
    tail = r"</tbody></table></body></html>"
    begin = 1
    length = len(str(index))
    while True:
        if begin > index:
            break
        formatBegin = '0' * (length - len(str(begin))) + str(begin)
        head += "<tr><TD><a href='raw\\" + formatBegin+ "_c.txt'>C</a>&nbsp;<a href='raw\\" + formatBegin+ "_s.txt'>S</a>&nbsp;<a href='raw\\" + formatBegin+ "_m.xml'>M</a></TD><td>" + formatBegin+ "</td>"
        head += body
        begin += 1
    head += tail
    file = open(os.path.join(destDir,"_index.htm"),"wb")
    file.write(head)
    file.close()
                

if len(sys.argv) > 1:
    srcDir = sys.argv[1]
    if len(sys.argv) > 2:
        resultDir = sys.argv[2]
    if os.path.isfile(srcDir):
        print "input file is : " + srcDir
        dealwithPro(srcDir,resultDir)
    else:
        print "is folder"
    emptyWorkspace()
else:
    print "usage: epc2saz.py inputfile outdir"
  
