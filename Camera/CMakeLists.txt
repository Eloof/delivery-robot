set(CAMERA_EXE_NAME "Camera")

set(CMAKE_PREFIX_PATH "/home/anatoly/build")

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(Mosquitto REQUIRED IMPORTED_TARGET libmosquitto)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${CAMERA_EXE_NAME} main.cpp
        color.h
        robot_message_mqtt.h)
target_link_libraries(${CAMERA_EXE_NAME} ${OpenCV_LIBS}
        PkgConfig::Mosquitto)


