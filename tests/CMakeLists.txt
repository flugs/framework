#if(BUILD_TESTING)
#    find_package(Qt5Test ${REQUIRED_QT_VERSION} NO_MODULE)
#    if(Qt5Test_FOUND)
#        set(TEST_SRCS
#            statustest.cpp
#            headertest.cpp
#            headerstest.cpp
#        )

#        qc_add_tests(${TEST_SRCS} NAME_PREFIX qhttpserver LINK_LIBRARIES PUBLIC QHttpServer Qt5::Core Qt5::Network Qt5::Test)
#    endif()
#endif()
