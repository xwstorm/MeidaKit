cmake_minimum_required(VERSION 3.10.0)

FILE(GLOB BASE_SOURCES
    ${MK_ROOT_DIR}/src/base/*.h
    ${MK_ROOT_DIR}/src/base/*.cpp
    )

set(COMMON_SOURCES ${COMMON_SOURCES} ${BASE_SOURCES})

message(STATUS "COMMON_SOURCES=${COMMON_SOURCES}")
set(SOURCES ${COMMON_SOURCES} )
