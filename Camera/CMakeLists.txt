set(CAMERA_EXE_NAME "Camera")

set(CMAKE_PREFIX_PATH "/home/anatoly/build")

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${CAMERA_EXE_NAME} main.cpp camera.h color.h)
target_link_libraries(${CAMERA_EXE_NAME} ${OpenCV_LIBS})
