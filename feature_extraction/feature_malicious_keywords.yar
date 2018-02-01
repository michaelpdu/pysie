/*
common malicious keywords, from 0-49
*/

rule malicious_keyword_payload
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 0
    strings:
        $a = "payload" nocase
    condition:
        $a
}

rule malicious_keyword_shellcode
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1
    strings:
        $a = "shellcode" nocase
    condition:
        $a
}

rule malicious_keyword_trigger
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2
    strings:
        $a = "trigger" nocase
    condition:
        $a
}

rule malicious_keyword_exploit
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 3
    strings:
        $a = "exploit" nocase
    condition:
        $a
}

rule malicious_keyword_antivirus
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 4
    strings:
        $a = "antivirus" nocase
    condition:
        $a
}

rule malicious_keyword_safemode
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 5
    strings:
        $a = "safemode" nocase
    condition:
        $a
}

rule malicious_keyword_shellexecute
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 6
    strings:
        $a = "ShellExecute" nocase
    condition:
        $a
}

rule malicious_keyword_7FFE
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 43
    strings:
        $a = "7FFE" nocase
    condition:
        $a
}
rule malicious_keyword_FFFF
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 44
    strings:
        $a = "FFFF" nocase
    condition:
        $a
}

rule malicious_keyword_4141
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 45
    strings:
        $a = "4141" nocase
    condition:
        $a
}

rule malicious_keyword_4142
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 46
    strings:
        $a = "4142" nocase
    condition:
        $a
}

rule malicious_keyword_9090
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 47
    strings:
        $a = "9090" nocase
    condition:
        $a
}

rule malicious_keyword_0C0C
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 48
    strings:
        $a = "0C0C" nocase
    condition:
        $a
}

rule malicious_keyword_5A4D
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 49
    strings:
        $a = "5A4D" nocase
    condition:
        $a
}

/*
powershell keywords, from 50-59
*/

rule malicious_keyword_powershell
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 50
    strings:
        $a = "powershell" nocase
    condition:
        $a
}

rule malicious_keyword_powershell_iex
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 51
    strings:
        $a = /\biex\b/ nocase
    condition:
        $a
}

rule malicious_keyword_FromBase64String
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 52
    strings:
        $a = "FromBase64String" nocase
    condition:
        $a
}

/*
ActiveX keywords, from 60-79
*/

rule malicious_keyword_activexobject
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 60
    strings:
        $a = "ActiveXObject" nocase
    condition:
        $a
}

rule malicious_keyword_createobject
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 61
    strings:
        $a = "CreateObject" nocase
    condition:
        $a
}

rule malicious_keyword_wscript
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 62
    strings:
        $a = "wscript" nocase
    condition:
        $a
}

rule malicious_keyword_open
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 63
    strings:
        $a = "open" nocase
    condition:
        $a
}

rule malicious_keyword_get
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 64
    strings:
        $a = "get" nocase
    condition:
        $a
}

rule malicious_keyword_run
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 65
    strings:
        $a = "run" nocase
    condition:
        $a
}

rule malicious_keyword_SaveToFile
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 66
    strings:
        $a = "SaveToFile" nocase
    condition:
        $a
}

rule malicious_keyword_ADODB
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 67
    strings:
        $a = "ADODB.Stream" nocase
    condition:
        $a
}

rule malicious_keyword_XMLHTTP
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 68
    strings:
        $a = "Microsoft.XMLHTTP" nocase
    condition:
        $a
}

rule malicious_keyword_cscript
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 69
    strings:
        $a = "cscript" nocase
    condition:
        $a
}

rule malicious_keyword_onreadystatechange
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 70
    strings:
        $a = "onreadystatechange" nocase
    condition:
        $a
}

rule malicious_keyword_wshshell
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 71
    strings:
        $a = "wshshell" nocase
    condition:
        $a
}

rule malicious_keyword_send
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 72
    strings:
        $a = "send" nocase
    condition:
        $a
}

/*
Other keywords, from n to 99
*/

rule malicious_keyword_svchost
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 90
    strings:
        $a = "svchost.exe" nocase
    condition:
        $a
}

rule malicious_keyword_cmd
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 91
    strings:
        $a = "cmd.exe" nocase
    condition:
        $a
}

rule malicious_keyword_MSIE
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 97
    strings:
        $a = "MSIE" nocase
    condition:
        $a
}

rule malicious_keyword_Win32
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 98
    strings:
        $a = "Win32" nocase
    condition:
        $a
}

rule malicious_keyword_Win64
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 99
    strings:
        $a = "Win64" nocase
    condition:
        $a
}