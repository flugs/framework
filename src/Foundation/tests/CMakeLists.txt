set(TEST_SRCS
    statustest.cpp
    headertest.cpp
    headerstest.cpp
)

qc_add_tests(${TEST_SRCS}
    NAME_PREFIX ${PROJECT_NAME}
    LINK_LIBRARIES PUBLIC Flugs::Foundation Qt5::Network
)
