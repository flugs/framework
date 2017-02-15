project(flugs_controller VERSION 0.0.1)
set(COMPONENT Controller)

set(SOURCES
    controller.cpp
    mux.cpp

    params/param.cpp
    params/bodyparam.cpp
    params/formparam.cpp
    params/headerparam.cpp
    params/pathparam.cpp
    params/queryparam.cpp

    result/result.cpp
    result/contentresult.cpp
)

set(GEN_INCLUDE_HEADERS
    Controller
    Mux

    params/Param
    params/BodyParam
    params/FormParam
    params/HeaderParam
    params/PathParam
    params/QueryParam

    result/Result
    result/ContentResult
)

set(INSTALL_DIRS result params)

set(PUBLIC_LINK_LIBRARIES Flugs::Foundation Flugs::Router Qt5::Core Qt5::Network)
qc_add_library(TARGET ${COMPONENT} NS Flugs ${SOURCES})
target_link_libraries(${COMPONENT} PUBLIC ${PUBLIC_LINK_LIBRARIES})
qc_generate_headers(TARGET ${COMPONENT} NS Flugs ${GEN_INCLUDE_HEADERS})
qc_install_library(TARGET ${COMPONENT} NS Flugs DIRECTORIES ${INSTALL_DIRS})
