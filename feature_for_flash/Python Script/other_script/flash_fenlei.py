import sys
import os
import subprocess
for root, dirs, files in os.walk(sys.argv[1]):
    for file in files:
        file_path=os.path.join(root,file)
        cmd="FlashML_fenlei.exe -p {0}".format(file_path)          
        subprocess.call(cmd,shell=True)