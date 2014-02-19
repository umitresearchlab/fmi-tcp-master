CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Protobuf
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})

FIND_PACKAGE(Threads REQUIRED)

INCLUDE_DIRECTORIES(${FMITCP_INCLUDE_DIR} ${LACEWING_INCLUDE_DIR})
LINK_DIRECTORIES(${FMITCP_LIBS_DIR} ${LACEWING_LIBS_DIR})

SET(SRCS
    src/Connection.cpp
    src/main.cpp
    src/Master.cpp
    src/Slave.cpp
    src/StrongConnection.cpp
    src/url_parser.c
    src/WeakConnection.cpp
)
SET(HEADERS
    include/Connection.h
    include/Master.h
    include/Slave.h
    include/StrongConnection.h
    include/url_parser.h
    include/WeakConnection.h
)

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/bin")

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(master ${HEADERS} ${SRCS})

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

