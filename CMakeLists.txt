CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Protobuf
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})

FIND_PACKAGE(Threads REQUIRED)

INCLUDE_DIRECTORIES(${FMITCP_INCLUDE_DIR} ${LACEWING_INCLUDE_DIR})
LINK_DIRECTORIES(${FMITCP_LIBS_DIR} ${LACEWING_LIBS_DIR})

SET(MASTER_SRCS
    src/master/Connection.cpp
    src/master/main.cpp
    src/master/Master.cpp
    src/master/Logger.cpp
    src/master/FMIClient.cpp
    src/master/StrongConnection.cpp
    src/master/WeakConnection.cpp
    src/common/url_parser.c
    src/common/common.cpp
)
SET(MASTER_HEADERS
    include/master/Connection.h
    include/master/Master.h
    include/master/Logger.h
    include/master/FMIClient.h
    include/master/StrongConnection.h
    include/master/WeakConnection.h
    include/common/common.h
    include/common/url_parser.h
)

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/bin")

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(master ${MASTER_HEADERS} ${MASTER_SRCS})

IF(WIN32)
    TARGET_LINK_LIBRARIES(master
        fmitcp
        shlwapi
        lacewing
        ws2_32
        mswsock
        crypt32
        secur32
        mpr
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${PROTOBUF_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
    )
ELSE(WIN32)
    TARGET_LINK_LIBRARIES(master
        fmitcp
        lacewing
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${PROTOBUF_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
    )
ENDIF(WIN32)

