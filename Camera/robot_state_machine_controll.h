#include <memory>
#include "camera.h"
#include "robot.h"
#include <unistd.h>


enum EState {EWait, EMove ,EMoveToTarget, ERotateLeft, ERotateRight, EForward};

class Robot_control{

    std::shared_ptr<Camera_detect> det;

    EState state;

    void processEvents();

public:

    Robot_control(std::shared_ptr<Camera_detect> d);
    void run();

};

Robot_control::Robot_control(std::shared_ptr<Camera_detect> d) {
    det = d;
}


void Robot_control::run() {
    int iter = 0;
    while (1){
        this->det->refurbish_all();

        cout << iter<< '\n' << int(det->get_angle_to_target());
        iter++;

        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
}


void Robot_control::processEvents() {

    }
