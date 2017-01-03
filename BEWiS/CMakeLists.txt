cmake_minimum_required(VERSION 3.2)
# change paths to your C++ compiler

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-stack-protector" )

project( bewis )

include_directories("/usr/local/opt/opencv3/include")
LINK_DIRECTORIES("/usr/local/opt/opencv3/lib")

set(BGWIZSRC_NAME wisardlib/bgwis.cpp)
set(MAINSRC_NAME bewis.cpp)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY .)

set(LIB_NAME wisard)
set(BIN_NAME bewis)

set(OPENCV_LIBS opencv_core opencv_calib3d
        opencv_flann opencv_imgcodecs opencv_ml
        opencv_highgui opencv_video opencv_videoio
        opencv_imgproc opencv_photo opencv_shape)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
add_library(${LIB_NAME} SHARED ${BGWIZSRC_NAME} wisardlib/wisard.cpp wisardlib/wnet_lib.cpp)
target_link_libraries( ${LIB_NAME} ${OPENCV_LIBS})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
add_executable(${BIN_NAME} ${MAINSRC_NAME})
target_link_libraries(${BIN_NAME} ${LIB_NAME} ${OPENCV_LIBS})
