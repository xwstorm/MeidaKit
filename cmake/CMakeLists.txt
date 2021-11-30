
cmake_minimum_required(VERSION 3.4)

project(MediaKit)


set(LIBRARY_TYPE STATIC)

message("begin cmake")

include(sources.cmake)
set(CMAKE_CONFIGURATION_TYPES Debug Release)



if(MST_WINDOWS)
    message("MST_WINDOWS")
elseif(MSK_MACOS OR MSK_IOS)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fvisibility-inlines-hidden -fmerge-all-constants -fvisibility=hidden")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility-inlines-hidden -fmerge-all-constants -fvisibility=hidden")
    
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fobjc-arc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc '-std=c++14'")
    message("MSK_MACOS")
endif()


add_library(MStreamKit ${LIBRARY_TYPE} ${SOURCES})
target_include_directories(MStreamKit PUBLIC ./)

