cmake_minimum_required(VERSION 3.2)
project(AlgorithmTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/usr/local/include/")
link_directories("/usr/local/lib")

set(SOURCE_FILES main.cpp
        source/fusion/wisefuseRpc.h
        source/fusion/wisefuseRpc.cpp
        source/quality/qualityjudgeRpc.h
        source/quality/qualityjudgeRpc.cpp
        source/retrieve/ImageRetrieveRpc.h
        source/retrieve/ImageRetrieveRpc.cpp
        source/utils/utiltest.cpp
        source/utils/utiltest.h)
add_executable(AlgorithmTest ${SOURCE_FILES})
target_link_libraries(AlgorithmTest Ice IceUtil pthread)