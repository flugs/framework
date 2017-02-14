project(http-parser VERSION 2.7.1)

set( SOURCES
    http_parser.c
)

set( HEADERS
    http_parser
)

qc_add_library(TARGET HttpParser STATIC NS Flugs ${SOURCES})
set_property(TARGET HttpParser PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(HttpParser PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# disable some warnings
if(WIN32 AND MSVC)
    add_definitions(-wd4244)
endif()

qc_generate_headers(TARGET HttpParser NS Flugs ${HEADERS})
