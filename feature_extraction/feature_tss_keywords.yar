/*
common TSS keywords
*/

rule tss_keyword_windows
{
    meta:
        index = 0
    strings:
        $a = "Windows" nocase
    condition:
        $a
}

rule tss_keyword_official
{
    meta:
        index = 1
    strings:
        $a = "Official" nocase
    condition:
        $a
}

rule tss_keyword_support
{
    meta:
        index = 2
    strings:
        $a = "support" nocase
    condition:
        $a
}

rule tss_keyword_defender
{
    meta:
        index = 3
    strings:
        $a = "defender" nocase
    condition:
        $a
}

rule tss_keyword_alert
{
    meta:
        index = 4
    strings:
        $a = "alert" nocase
    condition:
        $a
}

rule tss_keyword_virus
{
    meta:
        index = 5
    strings:
        $a = "virus" nocase
    condition:
        $a
}

rule tss_keyword_detect
{
    meta:
        index = 6
    strings:
        $a = "Detect" nocase
    condition:
        $a
}

rule tss_keyword_computer
{
    meta:
        index = 7
    strings:
        $a = "Computer" nocase
    condition:
        $a
}

rule tss_keyword_phone
{
    meta:
        index = 8
    strings:
        $a = "phone" nocase
    condition:
        $a
}

rule tss_keyword_number
{
    meta:
        index = 9
    strings:
        $a = "number" nocase
    condition:
        $a
}

rule tss_keyword_security
{
    meta:
        index = 10
    strings:
        $a = "security" nocase
    condition:
        $a
}

rule tss_keyword_warning
{
    meta:
        index = 11
    strings:
        $a = "warning" nocase
    condition:
        $a
}

rule tss_keyword_spyware
{
    meta:
        index = 12
    strings:
        $a = "spyware" nocase
    condition:
        $a
}

rule tss_keyword_login
{
    meta:
        index = 13
    strings:
        $a = "login" nocase
    condition:
        $a
}

rule tss_keyword_call
{
    meta:
        index = 14
    strings:
        $a = "call" nocase
    condition:
        $a
}

rule tss_keyword_system
{
    meta:
        index = 15
    strings:
        $a = "system" nocase
    condition:
        $a
}

rule tss_keyword_trojan
{
    meta:
        index = 16
    strings:
        $a = "Trojan" nocase
    condition:
        $a
}

rule tss_keyword_dangerous
{
    meta:
        index = 17
    strings:
        $a = "dangerous" nocase
    condition:
        $a
}

rule tss_keyword_backdoor
{
    meta:
        index = 18
    strings:
        $a = "backdoor" nocase
    condition:
        $a
}

rule tss_keyword_worm
{
    meta:
        index = 19
    strings:
        $a = "worm" nocase
    condition:
        $a
}

