project(flugs_router VERSION 0.0.1)
set(COMPONENT Router)

set(SOURCES
    router.cpp
    router_p.h
    route.cpp
    route_p.h
    scope.cpp
    scope_p.h
)

set(GEN_INCLUDE_HEADERS
    Router
    Route
    Scope
)

set(PUBLIC_LINK_LIBRARIES Flugs::Foundation Qt5::Core Qt5::Network)
qc_add_library(TARGET ${COMPONENT} NS Flugs ${SOURCES})
target_link_libraries(${COMPONENT} PUBLIC ${PUBLIC_LINK_LIBRARIES})
qc_generate_headers(TARGET ${COMPONENT} NS Flugs ${GEN_INCLUDE_HEADERS})
qc_install_library(TARGET ${COMPONENT} NS Flugs)

add_subdirectory(tests)
