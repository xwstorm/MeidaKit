
#-------------------------------------------------------------------------------
# macos.cmake
# cmake settings file for macOS target platform.
#-------------------------------------------------------------------------------

set(MSK_PLATFORM MACOS)
set(MSK_PLATFORM_NAME "macos")
set(MSK_MACOS 1)

set (CMAKE_OSX_DEPLOYMENT_TARGET "10.11")


set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fvisibility-inlines-hidden -fmerge-all-constants -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility-inlines-hidden -fmerge-all-constants -fvisibility=hidden")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fobjc-arc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc '-std=c++14'")


