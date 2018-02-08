SET (YARA_3_0_HOME ${PROJECT_SOURCE_DIR}/third_party/yara-3.0.0/yara)

SET(CMAKE_C_FLAGS_RELEASE "-O3")

INCLUDE_DIRECTORIES (
	${YARA_3_0_HOME}
	${YARA_3_0_HOME}/libyara
	${YARA_3_0_HOME}/libyara/include
	${YARA_3_0_HOME}/windows/include
)

ADD_DEFINITIONS (
)

ADD_LIBRARY (yara_3_0 STATIC
    libyara/modules/cuckoo.c
    #libyara/modules/demo.c
    libyara/modules/pe.c
    libyara/modules/tests.c
    libyara/ahocorasick.c
    libyara/arena.c
    libyara/atoms.c
    libyara/compiler.c
    libyara/exec.c
    libyara/exefiles.c
    libyara/filemap.c
    libyara/grammar.c
    libyara/hash.c
    libyara/hex_grammar.c
    libyara/hex_lexer.c
    libyara/lexer.c
    libyara/libyara.c
    libyara/mem.c
    libyara/modules.c
    libyara/object.c
    libyara/parser.c
    libyara/proc.c
    libyara/re.c
    libyara/re_grammar.c
    libyara/re_lexer.c
    libyara/rules.c
    libyara/scan.c
    libyara/utils.c
)

