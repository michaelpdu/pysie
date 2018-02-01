include "feature_malicious_keywords.yar"

/*
special malicious keywords in JavaScript, from 1100-1199
*/

rule keyword_eval
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1100
    strings:
        $a = "eval" nocase
    condition:
        $a
}

rule keyword_unescape
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1101
    strings:
        $a = "unescape" nocase
    condition:
        $a
}

rule keyword_escape
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1102
    strings:
        $a = "escape" nocase
    condition:
        $a
}

rule keyword_res
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1110
    strings:
        $a = "res://" nocase
    condition:
        $a
}

rule keyword_sys_ext
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1111
    strings:
        $a = /\.sys\b/ nocase
    condition:
        $a
}

rule keyword_product_360se
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1120
    strings:
        $a = "360se.exe" nocase
    condition:
        $a
}

rule keyword_product_360safe
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1121
    strings:
        $a = "360safe.exe" nocase
    condition:
        $a
}

rule keyword_product_kingsoft
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1122
    strings:
        $a = "kingsoft" nocase
    condition:
        $a
}

rule keyword_product_qq
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1123
    strings:
        $a = "QQPCMgr" nocase
    condition:
        $a
}

rule keyword_product_kislive
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1124
    strings:
        $a = "kislive.exe" nocase
    condition:
        $a
}

rule keyword_product_bugreport
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1125
    strings:
        $a = "bugreport_xf.exe" nocase
    condition:
        $a
}


/*
keywords in JavaScript, from 1200-1499
*/

rule keyword_setInterval
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1200
    strings:
        $a = "setInterval" nocase
    condition:
        $a 
}

rule keyword_setTimeout
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1201
    strings:
        $a = "setTimeout" nocase
    condition:
        $a 
}

rule keyword_addEventListener
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1202
    strings:
        $a = "addEventListener" nocase
    condition:
        $a 
}

rule keyword_appendChild
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1203
    strings:
        $a = "appendChild" nocase
    condition:
        $a
}

rule keyword_insertBefore
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1204
    strings:
        $a = "insertBefore" nocase
    condition:
        $a
}

rule keyword_createTextNode
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1205
    strings:
        $a = "createTextNode" nocase
    condition:
        $a
}

rule keyword_getElementById
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1206
    strings:
        $a = "getElementById" nocase
    condition:
        $a
}

rule keyword_getElementByTagName
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1207
    strings:
        $a = "getElementByTagName" nocase
    condition:
        $a
}

rule keyword_fromCharCode
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1208
    strings:
        $a = "fromCharCode" nocase
    condition:
        $a
}

rule keyword_indexOf
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1209
    strings:
        $a = "indexOf" nocase
    condition:
        $a
}

rule keyword_concat
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1210
    strings:
        $a = "concat" nocase
    condition:
        $a
}

rule keyword_charCodeAt
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1211
    strings:
        $a = "charCodeAt" nocase
    condition:
        $a
}

rule keyword_charAt
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1212
    strings:
        $a = "charAt" nocase
    condition:
        $a
}

rule keyword_decodeURI
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1213
    strings:
        $a = "decodeURI" nocase
    condition:
        $a
}

rule keyword_clearInterval
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1214
    strings:
        $a = "clearInterval" nocase
    condition:
        $a
}

rule keyword_valueOf
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1215
    strings:
        $a = "valueOf" nocase
    condition:
        $a
}

rule keyword_substr
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1216
    strings:
        $a = "substr" nocase
    condition:
        $a
}

rule keyword_split
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1217
    strings:
        $a = "split" nocase
    condition:
        $a
}

rule keyword_slice
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1218
    strings:
        $a = "slice" nocase
    condition:
        $a
}

rule keyword_shift
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1219
    strings:
        $a = "shift" nocase
    condition:
        $a
}

rule keyword_unshift
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1220
    strings:
        $a = "unshift" nocase
    condition:
        $a
}

rule keyword_replace
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1221
    strings:
        $a = "replace" nocase
    condition:
        $a
}

rule keyword_reverse
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1222
    strings:
        $a = "reverse" nocase
    condition:
        $a
}

rule keyword_search
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1223
    strings:
        $a = "search" nocase
    condition:
        $a
}

rule keyword_lastIndexOf
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1224
    strings:
        $a = "lastIndexOf" nocase
    condition:
        $a
}

rule keyword_parseInt
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1225
    strings:
        $a = "parseInt" nocase
    condition:
        $a
}

rule keyword_innerHTML
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1226
    strings:
        $a = "innerHTML" nocase
    condition:
        $a
}

rule keyword_createElement
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1227
    strings:
        $a = "createElement" nocase
    condition:
        $a
}

rule keyword_toLowerCase
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1228
    strings:
        $a = "toLowerCase" nocase
    condition:
        $a
}

rule keyword_toUpperCase
{
    meta:
        description = ""
        date = "2017-06-13"
        index = 1229
    strings:
        $a = "toUpperCase" nocase
    condition:
        $a
}

/*

*/
rule keyword_twitter
{
    meta:
        description = ""
        date = "2017-07-18"
        index = 1497
    strings:
        $a = "twitter" nocase
    condition:
        $a
}

rule keyword_yahoo
{
    meta:
        description = ""
        date = "2017-07-18"
        index = 1498
    strings:
        $a = "yahoo" nocase
    condition:
        $a
}

rule keyword_google_swiffy
{
    meta:
        description = ""
        date = "2017-07-18"
        index = 1499
    strings:
        $a = "swiffy.Stage" nocase
    condition:
        $a
}

rule keyword_google_analytics
{
    meta:
        description = ""
        date = "2017-07-18"
        index = 1499
    strings:
        $a = "google-analytics.com" nocase
    condition:
        $a
}
