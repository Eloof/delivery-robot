#include <iostream>
#include "camera.h"
#include "robot_message_mqtt.h"
#include "robot_state_machine_controll.h"

char *mqtt_host = (char*)"broker.hivemq.com";
int mqtt_port = 1883;


int main() {
    color_HSV BOT_BLUE_PART = color_HSV(110, 185, 100);
    color_HSV BOT_PURPLE_PART = color_HSV(159, 119, 100);
    color_HSV COLOR_TARGET = color_HSV(74, 150, 100);



    // std::shared_ptr<RobotControll> robot(new RobotControll(mqtt_host, mqtt_port));

    std::shared_ptr <Camera_detect> det(new Camera_detect(0, BOT_BLUE_PART, BOT_PURPLE_PART, COLOR_TARGET));
    std::shared_ptr <StateMachine> rob_c(new StateMachine(det));
    rob_c->run();


}
