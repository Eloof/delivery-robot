#include <iostream>
#include "camera.h"
#include "robot.h"
#include "robot_state_machine_controll.h"


int main() {
    color_HSV BOT_BLUE_PART = color_HSV(110, 185, 100);
    color_HSV BOT_PURPLE_PART = color_HSV(159, 119, 100);
    color_HSV COLOR_TARGET = color_HSV(74, 150, 100);

    shared_ptr<Camera_detect> det(new Camera_detect(0, BOT_BLUE_PART, BOT_PURPLE_PART, COLOR_TARGET));

    shared_ptr<Robot_control> rob_c(new Robot_control(det));
    rob_c->run();


}
