project(flugs_middleware VERSION 0.0.1)
set(COMPONENT Middleware)

set(SOURCES
    auth.cpp
    cors.cpp
    csrf.cpp
    gzip.cpp
    xhttpmethodoverride.cpp
    panic.cpp
    prefixstrip.cpp
    static.cpp
    throttle.cpp
    delay.cpp
    secure.cpp
)

set(GEN_INCLUDE_HEADERS
    Auth
    Cors
    Csrf
    Gzip
    XHttpMethodOverride
    Panic
    PrefixStrip
    Static
    Throttle
    Delay
    Secure
)

set(PUBLIC_LINK_LIBRARIES Flugs::Foundation Qt5::Core Qt5::Network)

qc_add_library(TARGET ${COMPONENT} NS Flugs ${SOURCES})
target_link_libraries(${COMPONENT} PUBLIC ${PUBLIC_LINK_LIBRARIES})
qc_generate_headers(TARGET ${COMPONENT} NS Flugs ${GEN_INCLUDE_HEADERS})
qc_install_library(TARGET ${COMPONENT} NS Flugs)

add_subdirectory(tests)
