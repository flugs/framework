project(flugs_httpserver VERSION 0.0.1)
set(COMPONENT HttpServer)

set(SOURCES
    httpserver.cpp
    httpserverplugin.cpp
    httpserverconnection.cpp
    httpserverconnection_p.h
    httpserverresponse.cpp
)

set(GEN_INCLUDE_HEADERS
    HttpServer
    HttpServerConnection
    HttpServerResponse
)

set(PUBLIC_LINK_LIBRARIES Flugs::Foundation Qt5::Core Qt5::Network)

find_package(Qt5Qml ${REQUIRED_QT_VERSION} NO_MODULE)
if(Qt5Qml_FOUND)
    set(SOURCES ${SOURCES} httpserverplugin.cpp qmldir)
    set(GEN_INCLUDE_HEADERS ${GEN_INCLUDE_HEADERS} HttpServerPlugin)
    set(PUBLIC_LINK_LIBRARIES ${PUBLIC_LINK_LIBRARIES} Qt5::Qml)
endif()

qc_add_library(TARGET ${COMPONENT} NS Flugs ${SOURCES})
target_link_libraries(${COMPONENT} PUBLIC ${PUBLIC_LINK_LIBRARIES})
qc_generate_headers(TARGET ${COMPONENT} NS Flugs ${GEN_INCLUDE_HEADERS})
qc_install_library(TARGET ${COMPONENT} NS Flugs)

add_subdirectory(tests)
