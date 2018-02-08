INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/third_party/jsoncpp/include
                    ${PROJECT_SOURCE_DIR}/third_party/jsoncpp/src/lib_json
					)

SET(JSONCPP_INCLUDE_DIR  ${PROJECT_SOURCE_DIR}/third_party/jsoncpp/include )

SET(PUBLIC_HEADERS
    ${JSONCPP_INCLUDE_DIR}/json/config.h
    ${JSONCPP_INCLUDE_DIR}/json/forwards.h
    ${JSONCPP_INCLUDE_DIR}/json/features.h
	${JSONCPP_INCLUDE_DIR}/json/json.h
    ${JSONCPP_INCLUDE_DIR}/json/value.h
    ${JSONCPP_INCLUDE_DIR}/json/reader.h
    ${JSONCPP_INCLUDE_DIR}/json/writer.h
    ${JSONCPP_INCLUDE_DIR}/json/assertions.h
    ${JSONCPP_INCLUDE_DIR}/json/version.h
    )


ADD_LIBRARY(jsoncpp STATIC
            ${PROJECT_SOURCE_DIR}/third_party/jsoncpp/src/lib_json/json_reader.cpp
            ${PROJECT_SOURCE_DIR}/third_party/jsoncpp/src/lib_json/json_value.cpp
            ${PROJECT_SOURCE_DIR}/third_party/jsoncpp/src/lib_json/json_writer.cpp
            ${PROJECT_SOURCE_DIR}/third_party/jsoncpp/src/lib_json/version.h.in
            )