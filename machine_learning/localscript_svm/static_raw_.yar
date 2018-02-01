//word
rule WORD_CONST_JQUERY {
strings:
  $r = /\bjquery\b/ nocase
condition:
  $r
}

rule WORD_CONST_COPYRIGHT {
strings:
  $r = /\bcopyright\b/ nocase
condition:
  $r
}

rule WORD_CONST_PLUGIN {
strings:
  $r = /\bplugin\b/ nocase
condition:
  $r
}

rule WORD_CONST_LICENSE {
strings:
  $r = /\bLicense\b/ nocase
condition:
  $r
}

rule WORD_CONST_MICROSOFT {
strings:
  $r = /\bMicrosoft\b[^\.]/ nocase
condition:
  $r
}

rule WORD_CONST_APACHE {
strings:
  $s = "www.apache.org"  nocase
condition:
  $s
}

rule WORD_CONST_TYPEOF {
strings:
  $r = /\btypeof\b/ nocase
condition:
  $r
}

rule WORD_CONST_CCON {
strings:
  $s = "/*@cc_on"
condition:
  $s
}

rule WORD_API_PUBLIC_ISNAN {
strings:
  $r = /\bisNaN\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_SHOW {
strings:
  $r = /\bshow\s*\(/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_ENCODEURICOMPONENT {
strings:
  $s = "encodeURIComponent"  nocase
condition:
  $s
}

rule WORD_API_PUBLIC_UNESCAPE {
strings:
  $r = /\bunescape\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_PARSEFLOAT {
strings:
  $r = /\bparsefloat\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_ALERT {
strings:
  $r = /\balert\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_REGEXP {
strings:
  $r = /\bregexp\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_BROWSER_OBJECT {
strings:
  $r1 = /\bwindow\./ nocase
  $r2 = /\bdocument\./ nocase
condition:
  $r1 or $r2
}

rule WORD_API_PUBLIC_BROWSER_NODE {
strings:
  $s1 = "createelement"  nocase
  $s2 = "getelementsbytagname"  nocase
  $s3 = "getattribute"  nocase
  $s4 = "addeventlistener"  nocase
  $r5 = /\baddclass\b/  nocase
  $r6 = /\bremovechild\b/  nocase
  $r7 = /\bparentnode\b/  nocase
condition:
  $s1 or $s2 or $s3 or $s4 or $r5 or $r6 or $r7
}

rule WORD_API_PUBLIC_ISFINITE {
strings:
  $r = /\bisFinite\b/ nocase
condition:
  $r
}

rule WORD_API_MSUTILSYSINFO_GETSERVICE {
meta:
  description = "normal"
strings:
  $r = /\bgetservice\b/  nocase
condition:
  $r
}

rule WORD_API_WSCRIPT_CREATEOBJECT {
strings:
  $s = "wscript.createobject"  nocase
condition:
  $s
}

rule WORD_API_WSCRIPT_QUIT {
strings:
  $r = /\bquit\s*\(/  nocase
condition:
  $r
}

rule WORD_API_WSCRIPT_SLEEP {
strings:
  $r = /\bsleep\s*\(/  nocase
condition:
  $r
}

rule WORD_API_WSCRIPT_RUN {
strings:
  $r = /\brun\s*\(/  nocase
condition:
  $r
}

rule WORD_API_PUBLIC_XMLHTTPREQUEST {
strings:
  $s = "XMLHttpRequest"  nocase
condition:
  $s
}

rule WORD_API_PUBLIC_ACTIVEXOBJECT {
strings:
  $s = "ActiveXObject"  nocase
condition:
  $s
}

rule WORD_API_PUBLIC_DATE {
strings:
  $r = /\bdate\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_EVAL {
strings:
  $r = /\beval\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_BIND {
strings:
  $r = /\bbind\s*\(/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_EXEC {
strings:
  $r = /\bexec\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_CALL {
strings:
  $r = /\bcall\s*\(/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_DECODEURI {
strings:
  $r = /\bdecodeURI\b/ nocase
condition:
  $r
}

rule WORD_API_ARRAY_SLICE {
strings:
  $r = /\bslice\s*\(/  nocase
condition:
  $r
}

rule WORD_API_ARRAY_UNSHIFT {
strings:
  $r = /\bunshift\s*\(/  nocase
condition:
  $r
}

rule WORD_API_ARRAY_ISARRAY {
strings:
  $r = /\isArray\b/  nocase
condition:
  $r
}

rule WORD_API_STR_TOCASE {
strings:
  $s1 = "tolowercase"  nocase
  $s2 = "touppercase"  nocase
condition:
  $s1 or $s2
}

rule WORD_API_STR_CHARAT {
strings:
  $r = /\bcharAt\b/  nocase
condition:
  $r
}

rule WORD_API_STR_FROMCHARCODE {
strings:
  $s = "String.fromCharCode"  nocase
condition:
  $s
}

rule WORD_API_DATE_NOW {
strings:
  $s = "date.now"  nocase
condition:
  $s
}

rule WORD_API_DATE_GETOVERDAY {
strings:
  $s1 = "getYear()"  nocase
  $s2 = "getMonth()"  nocase
  $s3 = "getDay()"  nocase
condition:
  $s1 or $s2 or $s3
}

rule WORD_API_DATE_GETINDAY {
strings:
  $s1 = "getMilliseconds()"  nocase
  $s2 = "getSeconds()"  nocase
  $s3 = "getMinutes()"  nocase
  $s4 = "getHours()"  nocase
  $s5 = "getTime()"  nocase
condition:
  $s1 or $s2 or $s3 or $s4 or $s5
}

rule WORD_API_SCRIPT_FILESYSTEM_EXISTS {
strings:
  $r1 = /\bFileExists\b/ nocase
  $r2 = /\bFolderExists\b/ nocase
condition:
  $r1 or $r2
}

rule WORD_API_SCRIPT_FILESYSTEM_GET {
strings:
  $r1 = /\bGetFile\b/ nocase
  $r2 = /\bGetFolder\b/ nocase
condition:
  $r1 or $r2
}

rule WORD_API_SCRIPT_FILESYSTEM_CREATETEXTFILE {
strings:
  $s = "CreateTextFile"  nocase
condition:
  $s
}

rule WORD_API_SCRIPT_FILESYSTEM_OPENTEXTFILE {
strings:
  $s = "OpenTextFile"  nocase
condition:
  $s
}

rule WORD_API_XMLHTTP_ONREADYSTATECHANGE {
strings:
  $s = "onreadystatechange"  nocase
condition:
  $s
}

rule WORD_API_XMLHTTP_READYSTATE {
strings:
  $r = /\breadyState\b/  nocase
condition:
  $r
}

rule WORD_API_XMLHTTP_RESPONSE {
strings:
  $r1 = /\bresponse\b/  nocase
  $r2 = /\bresponseBody\b/  nocase
  $r3 = /\bresponseText\b/  nocase
  $r4 = /\bresponseType\b/  nocase
  $r5 = /\bresponseXML\b/  nocase
condition:
  $r1 or $r2 or $r3 or $r4 or $r5
}

rule WORD_API_XMLHTTP_STATUS {
strings:
  $r1 = /\bstatus\b/  nocase
  $r2 = /\bstatusText\b/  nocase
condition:
  $r1 or $r2
}

rule WORD_API_ADO_LOADFROMFILE {
strings:
  $r = /\bLoadFromFile\b/  nocase
condition:
  $r
}

rule WORD_API_ADO_OPEN {
strings:
  $r = /\bOpen\s*\(b/  nocase
condition:
  $r
}

rule WORD_API_ADO_READ {
strings:
  $r1 = /\bRead\s*\(\b/  nocase
  $r2 = /\bReadText\b/  nocase
condition:
  $r1 or $r2
}

rule WORD_API_ADO_SAVE {
strings:
  $r1 = /\bSave\s*\(\b/  nocase
  $r2 = /\bSaveToFile\b/  nocase
condition:
  $r1 or $r2
}

rule WORD_API_ADO_WRITE {
strings:
  $r1 = /\bWrite\s*\(\b/  nocase
  $r2 = /\bWriteText\b/  nocase
condition:
  $r1 or $r2
}

rule WORD_API_OBJECT_TOSTRING {
strings:
  $r = /\btoString\(\b/  nocase
condition:
  $r  
}

rule WORD_API_MATH_OP {
strings:
  $s1 = "math.floor"  nocase
  $s2 = "math.round"  nocase
  $s3 = "math.ceil"  nocase
  $s4 = "math.max"  nocase
  $s5 = "math.min"  nocase
  $s6 = "math.abs"  nocase
condition:
  $s1 or $s2 or $s3 or $s4 or $s5 or $s6
}

rule WORD_API_MATH_RANDOM {
strings:
  $s = "math.random"  nocase
condition:
  $s
}

rule WORD_API_MATH_TRIGONOMETRIC_FUNC {
strings:
  $s1 = "math.atan2"  nocase
  $s2 = "math.cos"  nocase
condition:
  $s1 or $s2
}


rule WORD_ARG_ACTIVEXOBJECT_SCRIPT_FILESYSTEM {
strings:
  $s = "scripting.filesystemobject"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_WSCRIPT_SHELL {
strings:
  $s = "WScript.Shell"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_VBS_REGEXP {
strings:
  $s = "VBScript.RegExp"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_ADODB_STREAM {
strings:
  $s = "ADODB.Stream"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_MSUTIL_SCRIPTUTIL {
strings:
  $s = "MSUtil.ScriptUtil"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_MSUTIL_SYSINFO {
strings:
  $s = "MSUtil.Sysinfo"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_XSI_COLLECTION {
strings:
  $s = "Shell.Application"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_MSUTIL_LOG {
strings:
  $s = "MSUtil.Log"  nocase
condition:
  $s
}

rule WORD_ARG_ACTIVEXOBJECT_XMLHTTP {
strings:
  $s1 = "Microsoft.XMLHTTP"  nocase
  $s2 = "Msxml2.XMLHTTP"  nocase
condition:
  $s1 or $s2
}

rule WORD_ARG_ACTIVEXOBJECT_MS_DOMDOCUMENT {
strings:
  $s = "MSXML2.DOMDocument"  nocase
condition:
  $s
}

//structure
rule STRUCTURE_TRY_CATCH {
strings:
  $r1 = /\btry\b/
  $r2 = /\bcatch\b/
condition:
  $r1 and $r2
}

rule STRUCTURE_SWITCH_CASE{
strings:
  $r1 = /\bswitch\b/  nocase
  $r2 = /\bcase\b/
condition:
  $r1 and $r2
}

rule STRUCTURE_ARRAY_STR{
strings:
  $r = /\[(\".*\",?)*\]/
condition:
  $r
}
rule STRUCTURE_ANONYMOUS_FUNC{
strings:
  $r = /\(\s*function\s*\(/
condition:
  $r
}

//new
rule WORD_CONST_DOJO {
strings:
  $r = /\bdojo\.\b/ nocase
condition:
  $r
}

rule WORD_API_PUBLIC_WSCRIPT {
strings:
  $r = /\bWScript\b[^\.]/  nocase
condition:
  $r
}


rule STRUCTURE_HEXADECIMAL1 {
strings:
  $r = /\b0x\w/  nocase
condition:
  $r
}

rule STRUCTURE_HEXADECIMAL2 {
strings:
  $r = /\\x\w/  nocase
condition:
  #r > 1
}

rule STRUCTURE_VAR_COUNT{
strings:
  $r = /\bvar\b/  nocase
condition:
  #r < 20
}