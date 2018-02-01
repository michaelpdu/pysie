include "feature_malicious_keywords.yar"

/*
special malicious keywords in VBScript, from 2100-2199
*/

rule keyword_runmuma
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2100
    strings:
        $a = "runmuma" nocase
    condition:
        $a
}

/*
keywords in VBScript, from 2200-2499
*/

rule keyword_redim
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2200
    strings:
        $a = "redim" nocase
    condition:
        $a
}

rule keyword_preserve
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2201
    strings:
        $a = "preserve" nocase
    condition:
        $a
}

rule keyword_on_error
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2202
    strings:
        $a = "on error resume next" nocase
    condition:
        $a
}

rule keyword_lcase
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2203
    strings:
        $a = "lcase" nocase
    condition:
        $a
}

rule keyword_isobject
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2204
    strings:
        $a = "IsObject" nocase
    condition:
        $a
}

rule keyword_ubound
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2205
    strings:
        $a = "UBound" nocase
    condition:
        $a
}

rule keyword_next
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2206
    strings:
        $a = "next" nocase
    condition:
        $a
}

rule keyword_execute
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2207
    strings:
        $a = "Execute" nocase
    condition:
        $a
}

rule keyword_chr
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 2208
    strings:
        $a = "chr" nocase
    condition:
        $a
}