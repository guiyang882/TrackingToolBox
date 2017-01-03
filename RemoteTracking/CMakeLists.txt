cmake_minimum_required(VERSION 3.6)
project(RemoteTracking)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

set(SOURCE_FILES
#        source/main.cpp
#        source/kalman_opencv.cpp
#        source/camshift.cpp
        source/vibe/vibe-background-sequential.h
        source/vibe/vibe-background-sequential.c
        source/main-opencv.cpp
        #source/tracking/lkflow.cpp
        )

add_executable(RemoteTracking ${SOURCE_FILES})
target_link_libraries(RemoteTracking ${OpenCV_LIBS})