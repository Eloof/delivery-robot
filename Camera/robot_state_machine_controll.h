#include <memory>
#include "camera.h"
#include <unistd.h>

bool order_exists = true;

enum State {Wait, Move ,MoveToTarget, RotateLeft, RotateRight, Forward, Finish};

class StateMachine{

    std::shared_ptr<Camera_detect> cam;
    std::shared_ptr<RobotControll> robot_moving;
    State state;
    int iter = 0;

    void processEvents();

public:

    StateMachine(std::shared_ptr<Camera_detect> d);

    void run();

};



StateMachine::StateMachine(std::shared_ptr<Camera_detect> camera){
    this->cam = camera;
    state = Wait;
}


void StateMachine::run() {
    while (1){
        this->cam->refurbish_all();

        iter++;
        this->processEvents();


        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
}


void StateMachine::processEvents() {
    switch (this->state) {
        case Wait:
            if (order_exists) {
                this->state = MoveToTarget;
            }
            break;

        case Move:
            this->state = MoveToTarget;
            break;

        case MoveToTarget:
            if(cam->has_delta_angle_to_target(5)){
                if (cam->get_angle_to_target() > 0)
                    this->state = RotateLeft;
                else
                    this->state = RotateRight;
            }

            if(cam->has_distance_to_target(160))
                this->state = Forward;
            else
                this->state = Finish;
            break;

        case RotateLeft:
            // robot_moving->move_left();
            this->state = Move;
            break;

        case RotateRight:
            // robot_moving->move_right();
            this->state = Move;
            break;

        case Forward:
            // robot_moving->move_forward();
            this->state = Move;
            break;

        case Finish:
            cout << "Finish!!!" << '\n';
            sleep(30);
            this->state = Wait;
            break;
    }
}

