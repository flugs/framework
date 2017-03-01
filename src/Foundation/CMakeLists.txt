project(flugs_foundation VERSION 0.0.1)

set(COMPONENT Foundation)

set(SOURCES
    global.cpp
    abstracthttpparser.cpp
    connection.cpp
    header.cpp
    headers.cpp
    method.cpp
    request.cpp
    response.cpp
    server.cpp
    status.cpp
    stringutils.cpp
    middleware.cpp
)

set(GEN_INCLUDE_HEADERS
    Global
    AbstractHttpParser
    Connection
    Header
    Headers
    Method
    Request
    Response
    Server
    Status
    StringUtils
    Middleware
)

set(PUBLIC_LINK_LIBRARIES Qt5::Core Qt5::Network)
qc_add_library(TARGET ${COMPONENT} NS Flugs ${SOURCES})
target_link_libraries(${COMPONENT} PUBLIC ${PUBLIC_LINK_LIBRARIES} PRIVATE Flugs::HttpParser)
qc_generate_headers(TARGET ${COMPONENT} NS Flugs ${GEN_INCLUDE_HEADERS})
qc_install_library(TARGET ${COMPONENT} NS Flugs)

add_subdirectory(tests)
