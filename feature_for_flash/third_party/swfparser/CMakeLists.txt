INCLUDE_DIRECTORIES (
	${PROJECT_SOURCE_DIR}/third_party/swfparser
	${PROJECT_SOURCE_DIR}/third_party/zlib123
	${PROJECT_SOURCE_DIR}/third_party/lzma-920
)

ADD_DEFINITIONS (
)

ADD_LIBRARY (swfparser STATIC
    base64.c
	DoABCContext.cpp
	SWFAction.cpp
	SWFFile.cpp
	SWFFilter.cpp
	SWFItem.cpp
	SWFOpCode.cpp
	SWFReader.cpp
	SWFTag.cpp
	SWFTrait.cpp
	gSWFBasics.cpp
	gSWFDumper.cpp
	gSWFParser.cpp
	gSWFSize.cpp
)

TARGET_LINK_LIBRARIES (swfparser lzma zlib123) 

