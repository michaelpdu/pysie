rule JSB_1{
strings:
  $s = "TmsaObject ExecQuery:"
condition:
  $s
}

rule JSB_2{
strings:
  $s = "[GetObject] "
condition:
  $s
}

rule JSB_3{
strings:
  $s = "[Window Global] Call ScriptEngine()"
condition:
  $s
}

rule JSB_4{
strings:
  $s = "[Text.Stream] get Column property"
condition:
  $s
}

rule JSB_5{
strings:
  $s = "[Text.Stream] write line, value = "
condition:
  $s
}

rule JSB_6{
strings:
  $s = "[Text.Stream] write, value = "
condition:
  $s
}

rule JSB_7{
strings:
  $s = "[Text.Stream] close"
condition:
  $s
}

rule JSB_8{
strings:
  $s = "[Text.Stream] ReadAll, content = "
condition:
  $s
}

rule JSB_9{
strings:
  $s = "[Text.Stream] ReadLine, content = "
condition:
  $s
}

rule JSB_10{
strings:
  $s = "[Text.Stream] GetName, name = "
condition:
  $s
}

rule JSB_11{
strings:
  $s = "stop accessing fake response body in loop"
condition:
  $s
}

rule JSB_12{
strings:
  $s = "[TMSAString] call charCodeAt, return fake value (A), index = "
condition:
  $s
}

rule JSB_13{
strings:
  $s = "[File] get Path property"
condition:
  $s
}

rule JSB_14{
strings:
  $s = "[File] get Name property"
condition:
  $s
}

rule JSB_15{
strings:
  $s = "[File] OpenAsTextStream"
condition:
  $s
}

rule JSB_16{
strings:
  $s = "[File] Delete "
condition:
  $s
}

rule JSB_17{
strings:
  $s = "[Folder] get Path property"
condition:
  $s
}

rule JSB_18{
strings:
  $s = "[Folder] get Files property"
condition:
  $s
}

rule JSB_19{
strings:
  $s = "[Folder] call CopyHere"
condition:
  $s
}

rule JSB_20{
strings:
  $s = "[Folder] call Items"
condition:
  $s
}

rule JSB_21{
strings:
  $s = "[Folder] CreateTextFile, filename = "
condition:
  $s
}

rule JSB_22{
strings:
  $s = "[Folder] Get DateLastAccessed"
condition:
  $s
}

rule JSB_23{
strings:
  $s = "[Folder] Get DateLastModified"
condition:
  $s
}

rule JSB_24{
strings:
  $s = "tmsaNewAddedFiles add file:"
condition:
  $s
}

rule JSB_25{
strings:
  $s = "tmsaNewAddedFiles find no file named:"
condition:
  $s
}

rule JSB_26{
strings:
  $s = "[WScript.Shell] Run! no argus"
condition:
  $s
}

rule JSB_27{
strings:
  $s = "[WScript.Shell] Run! CMD: "
condition:
  $s
}

rule JSB_28{
strings:
  $s = "[WScript.Shell] ExpandEnvironmentStrings, path = "
condition:
  $s
}

rule JSB_29{
strings:
  $s = "[WScript.Shell] RegRead, key = "
condition:
  $s
}

rule JSB_30{
strings:
  $s = "[WScript.Shell] Exec! CMD: "
condition:
  $s
}

rule JSB_31{
strings:
  $s = "[WScript.Shell] CreateShortcut, path = "
condition:
  $s
}

rule JSB_32{
strings:
  $s = "[WScript.Shell] Popup window, text = "
condition:
  $s
}

rule JSB_33{
strings:
  $s = "[Shell.Application] call NameSpace, dir = "
condition:
  $s
}

rule JSB_34{
strings:
  $s = "[Shell.Application] ShellExecute, file = "
condition:
  $s
}

rule JSB_35{
strings:
  $s = "[XMLHttpRequest] trigger onreadystatechange callback."
condition:
  $s
}

rule JSB_36{
strings:
  $s = "[XMLHttpRequest] open HTTP request, method = "
condition:
  $s
}

rule JSB_37{
strings:
  $s = "[XMLHttpRequest] send HTTP request"
condition:
  $s
}

rule JSB_38{
strings:
  $s = "[XMLHttpRequest] set request header, header = "
condition:
  $s
}

rule JSB_39{
strings:
  $s = "[XMLHttpRequest] set proxy, proxy ="
condition:
  $s
}

rule JSB_40{
strings:
  $s = "[XMLHttpRequest] get HTTP status, return 200"
condition:
  $s
}

rule JSB_41{
strings:
  $s = "[XMLHttpRequest] get HTTP Response Body"
condition:
  $s
}

rule JSB_42{
strings:
  $s = "[XMLHttpRequest] get HTTP Response Body"
condition:
  $s
}

rule JSB_43{
strings:
  $s = "[XMLHttpRequest] set callback of onreadystatechange"
condition:
  $s
}

rule JSB_44{
strings:
  $s = "[ServerXMLHTTP] open HTTP request, method = "
condition:
  $s
}

rule JSB_45{
strings:
  $s = "[ServerXMLHTTP] send HTTP request"
condition:
  $s
}

rule JSB_46{
strings:
  $s = "[ServerXMLHTTP] get HTTP status, return 200"
condition:
  $s
}

rule JSB_47{
strings:
  $s = "[ADODB.Stream] open stream"
condition:
  $s
}

rule JSB_48{
strings:
  $s = "[ADODB.Stream] write content, "
condition:
  $s
}

rule JSB_49{
strings:
  $s = "[ADODB.Stream] writeText content, "
condition:
  $s
}

rule JSB_50{
strings:
  $s = "[ADODB.Stream] get content size, fake size = 2000"
condition:
  $s
}

rule JSB_51{
strings:
  $s = "[ADODB.Stream] save to file, path = "
condition:
  $s
}

rule JSB_52{
strings:
  $s = "[ADODB.Stream] close stream"
condition:
  $s
}

rule JSB_53{
strings:
  $s = "[ADODB.Stream] set type, value = "
condition:
  $s
}

rule JSB_54{
strings:
  $s = "[ADODB.Stream] set position, value = "
condition:
  $s
}

rule JSB_55{
strings:
  $s = "[ADODB.Stream] Load contents of existing file, filename: "
condition:
  $s
}

rule JSB_56{
strings:
  $s = "[ADODB.Stream] Read content, number of bytes: "
condition:
  $s
}

rule JSB_57{
strings:
  $s = "[FileSystemObject] Add folder, "
condition:
  $s
}

rule JSB_58{
strings:
  $s = "[FileSystemObject] Folder exists, "
condition:
  $s
}

rule JSB_59{
strings:
  $s = "[FileSystemObject] Create folder, "
condition:
  $s
}

rule JSB_60{
strings:
  $s = "[FileSystemObject] File exists: "
condition:
  $s
}

rule JSB_61{
strings:
  $s = "[FileSystemObject] Create text file, filename: "
condition:
  $s
}

rule JSB_62{
strings:
  $s = "[FileSystemObject] Open text file, filename: "
condition:
  $s
}

rule JSB_63{
strings:
  $s = "[FileSystemObject] Copy file. source: "
condition:
  $s
}

rule JSB_64{
strings:
  $s = "[FileSystemObject] Move file. source: "
condition:
  $s
}

rule JSB_65{
strings:
  $s = "[FileSystemObject] Return special folder object specified: "
condition:
  $s
}

rule JSB_66{
strings:
  $s = "[FileSystemObject] Return parent folder name for: "
condition:
  $s
}

rule JSB_67{
strings:
  $s = "[FileSystemObject] Returns a randomly generated temporary file or folder name"
condition:
  $s
}

rule JSB_68{
strings:
  $s = "[FileSystemObject] GetFolder, folderspec = "
condition:
  $s
}

rule JSB_69{
strings:
  $s = "[FileSystemObject] GetFile, filespec = "
condition:
  $s
}

rule JSB_70{
strings:
  $s = "[FileSystemObject] Deletes a specified file, "
condition:
  $s
}

rule JSB_71{
strings:
  $s = "[Enumerator] Create a enumerator"
condition:
  $s
}

rule JSB_72{
strings:
  $s = "[Enumerator] call item function, return: defined"
condition:
  $s
}

rule JSB_73{
strings:
  $s = "[Enumerator] call item function, return: undefined"
condition:
  $s
}

rule JSB_74{
strings:
  $s = "[Msxml2.DOMDocument] createElement "
condition:
  $s
}

rule JSB_75{
strings:
  $s = "Create ActiveXObject: "
condition:
  $s
}

rule JSB_76{
strings:
  $s = "[ActiveXObject] create WScript.Shell"
condition:
  $s
}

rule JSB_77{
strings:
  $s = "[ActiveXObject] create Shell.Application"
condition:
  $s
}

rule JSB_78{
strings:
  $s = "[ActiveXObject] create ADODB.Stream"
condition:
  $s
}

rule JSB_79{
strings:
  $s = "[ActiveXObject] create MSXML2.XMLHTTP"
condition:
  $s
}

rule JSB_80{
strings:
  $s = "[ActiveXObject] create WinHttp.WinHttpRequest"
condition:
  $s
}

rule JSB_81{
strings:
  $s = "[ActiveXObject] create MSXML2.ServerXMLHTTP"
condition:
  $s
}

rule JSB_82{
strings:
  $s = "[ActiveXObject] create Msxml2.DOMDocument"
condition:
  $s
}

rule JSB_83{
strings:
  $s = "[ActiveXObject] create ADODB.Recordset"
condition:
  $s
}

rule JSB_84{
strings:
  $s = "[ActiveXObject] create unknown "
condition:
  $s
}

rule JSB_85{
strings:
  $s = "[WScript] sleep, milliseconds = "
condition:
  $s
}

rule JSB_86{
strings:
  $s = "[WScript] Sleep count > 50"
condition:
  $s
}

rule JSB_87{
strings:
  $s = "[WScript] quit! errorcode = "
condition:
  $s
}

rule JSB_88{
strings:
  $s = "[WScript.Echo] "
condition:
  $s
}

rule JSB_89{
strings:
  $s = "[WScript] get StdErr property"
condition:
  $s
}

rule JSB_90{
strings:
  $s = "[WScript] get StdIn property"
condition:
  $s
}

rule JSB_91{
strings:
  $s = "[WScript] get StdOut property"
condition:
  $s
}

rule JSB_92{
strings:
  $s = "[WScript] get Path property"
condition:
  $s
}

rule JSB_93{
strings:
  $s = "_global.Exception"
condition:
  $s
}

rule ATTR_FILESIZE_SMALL{
condition:
  filesize < 1KB
}

rule JSB_WINDOW_EVAL{
strings:
  $s = "window.eval"
condition:
  $s  
}

rule JSB_TYPEERROR{
strings:
  $s = "TypeError"
condition:
  $s  
}