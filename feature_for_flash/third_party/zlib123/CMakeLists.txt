ADD_DEFINITIONS (
	#-DASMV
	#-DASMINF
)

ADD_LIBRARY (zlib123 STATIC
	adler32.c
	compress.c
	crc32.c
	deflate.c
	#contrib/masmx86/gvmat32c.c  #used in 32bit system
	gzio.c
	infback.c
	inffast.c
	inflate.c
	inftrees.c
	ioapi.c    #used in javaengine and class2js
	trees.c
	uncompr.c
	unzip.c    #used in javaengine and class2js
	zutil.c
)
