CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Protobuf
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

INCLUDE_DIRECTORIES(${FMIL_INCLUDE_DIR} ${STRONG_COUPLING_INCLUDE_DIR} ${FMITCP_INCLUDE_DIR} ${LACEWING_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} include)
LINK_DIRECTORIES   (${FMIL_LIBS_DIR}    ${STRONG_COUPLING_LIBS_DIR}    ${FMITCP_LIBS_DIR}    ${LACEWING_LIBS_DIR}    ${PROTOBUF_LIBRARY})

SET(MASTER_SRCS
    src/master/Connection.cpp
    src/master/main.cpp
    src/master/Master.cpp
    src/master/FMIClient.cpp
    src/master/StrongConnection.cpp
    src/master/WeakConnection.cpp
    src/common/url_parser.c
    src/common/common.cpp
)
SET(MASTER_HEADERS
    include/master/Connection.h
    include/master/Master.h
    include/master/FMIClient.h
    include/master/StrongConnection.h
    include/master/WeakConnection.h
    include/common/common.h
    include/common/url_parser.h
)

SET(TEST_SRCS
    test/main.cpp
    src/master/Connection.cpp
    src/master/Master.cpp
    src/master/FMIClient.cpp
    src/master/StrongConnection.cpp
    src/master/WeakConnection.cpp
    src/common/url_parser.c
    src/common/common.cpp
)
SET(TEST_HEADERS
    include/master/Connection.h
    include/master/Master.h
    include/master/FMIClient.h
    include/master/StrongConnection.h
    include/master/WeakConnection.h
    include/common/common.h
    include/common/url_parser.h
)

SET(SLAVE_SRCS
  src/slave/main.cpp
)
SET(SLAVE_HEADERS
)

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/bin")

ADD_EXECUTABLE(master ${MASTER_HEADERS} ${MASTER_SRCS})
ADD_EXECUTABLE(slave  ${SLAVE_HEADERS}  ${SLAVE_SRCS})
ADD_EXECUTABLE(test   ${TEST_HEADERS}   ${TEST_SRCS})

IF(WIN32)
    SET(WINLIBS
        fmitcp
        fmilib
        shlwapi
        lacewing
        ws2_32
        mswsock
        crypt32
        secur32
        mpr
        sc m umfpack amd cblas suitesparseconfig # For strong coupling
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        protobuf
        ${CMAKE_THREAD_LIBS_INIT})
    TARGET_LINK_LIBRARIES(master ${WINLIBS})
    TARGET_LINK_LIBRARIES(slave  ${WINLIBS})
    TARGET_LINK_LIBRARIES(test   ${WINLIBS})
ELSE(WIN32)
    SET(LINUXLIBS
        fmitcp
        fmilib
        lacewing
        dl
        sc m umfpack amd cblas atlas # For strong coupling
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${PROTOBUF_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT})
    TARGET_LINK_LIBRARIES(master ${LINUXLIBS})
    TARGET_LINK_LIBRARIES(slave  ${LINUXLIBS})
    TARGET_LINK_LIBRARIES(test   ${LINUXLIBS})
ENDIF(WIN32)
