cmake_minimum_required(VERSION 3.24)
project(Camera)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_PREFIX_PATH "/home/anatoly/build")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Camera main.cpp camera.h)
target_link_libraries( Camera ${OpenCV_LIBS} )
