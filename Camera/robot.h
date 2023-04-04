#include "iostream"


class robot {
public:
    void moveForward();
    void setAngle();
    void moveBack();
    void stop();
};

void robot::moveForward() {
    std::cout << "Forward";
}

void robot::setAngle() {
    std::cout << "Angle";
}

void robot::moveBack() {
    std::cout << "Back";
}

void robot::stop() {
    std::cout << "Stopped";
}



