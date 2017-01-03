cmake_minimum_required(VERSION 2.8)

project(bgs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
include_directories(/usr/local/Cellar/opencv3/HEAD-a85b4b5/include /Users/liuguiyang/Library/Caches/Homebrew/opencv3--contrib--git/modules/bgsegm/include)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

file(GLOB sources FrameProcessor.cpp PreProcessor.cpp VideoAnalysis.cpp  VideoCapture.cpp)
file(GLOB main Main.cpp)
file(GLOB demo Demo.cpp)
file(GLOB demo2 Demo2.cpp)

list(REMOVE_ITEM sources ${demo} ${demo2})

file(GLOB_RECURSE analysis package_analysis/*.cpp)
file(GLOB_RECURSE bgs package_bgs/*.cpp package_bgs/*.c)
file(GLOB_RECURSE bgs_include package_bgs/*.h)

include_directories(${CMAKE_SOURCE_DIR})

add_library(bgs SHARED ${sources} ${bgs} ${analysis})
target_link_libraries(bgs ${OpenCV_LIBS})
set_property(TARGET bgs PROPERTY PUBLIC_HEADER ${bgs_include})

add_executable(bgs_bin ${main})
target_link_libraries(bgs_bin ${OpenCV_LIBS} bgs)
set_target_properties(bgs_bin
  PROPERTIES OUTPUT_NAME bgs)

add_executable(bgs_demo ${demo})
target_link_libraries(bgs_demo ${OpenCV_LIBS} bgs)

add_executable(bgs_demo2 ${demo2})
target_link_libraries(bgs_demo2 ${OpenCV_LIBS} bgs)

INSTALL(TARGETS bgs
	bgs_bin
  RUNTIME DESTINATION bin COMPONENT app
  LIBRARY DESTINATION lib COMPONENT runtime
  ARCHIVE DESTINATION lib COMPONENT runtime
  PUBLIC_HEADER DESTINATION include/package_bgs COMPONENT dev
  FRAMEWORK DESTINATION "/Library/Frameworks"
)
