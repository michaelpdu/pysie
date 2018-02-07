rule html_type
{
    strings:
        $a1 = "<html" nocase
        $a2 = "<head" nocase
        $a3 = "<body" nocase
        $a4 = "<script" nocase
        $a5 = "<meta" nocase
        $a6 = "<title" nocase
    condition:
        any of them
}

rule js_type
{
    strings:
        $a1 = "var "
        $a2 = "function "
        $a3 = "function("
        $a4 = "eval"
        $a5 = "parseInt"
        $a6 = "return"
        $a7 = "document"
        $a8 = "window"
    condition:
        any of them
}

rule vbs_type
{
    strings:
        $a1 = "Dim " nocase
    condition:
        any of them
}

