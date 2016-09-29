cmake_minimum_required(VERSION 3.3)
project(sw_matrixsource)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

FILE(GLOB_RECURSE source_files src/*.c*)
FILE(GLOB_RECURSE header_files src/*.h*)

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

add_executable(sw_matrixsource ${source_files} ${header_files})

qt5_use_modules( sw_matrixsource Core Widgets Gui )

include_directories( ../mueb/ ../common/ ./fmod/lowlevel/inc/ )
