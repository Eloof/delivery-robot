#include "iostream"


class Robot {
public:
    void moveForward();
    void setAngle();
    void moveBack();
    void stop();
};

void Robot::moveForward() {
    std::cout << "Forward";
}

void Robot::setAngle() {
    std::cout << "Angle";
}

void Robot::moveBack() {
    std::cout << "Back";
}

void Robot::stop() {
    std::cout << "Stopped";
}



