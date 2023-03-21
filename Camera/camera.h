#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H


#include "iostream"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


class Camera{

private:
    string FILE_NAME;

public:
    Camera(string const & file_name){
        this->FILE_NAME = file_name;
    }


    int get_video(){
        VideoCapture cap(FILE_NAME);
        Mat frame;
        cap >> frame;

        if ((!cap.isOpened()) or (frame.empty())){
            cout << "Error opening video stream or file\n";
            return -1;
        }

        while(1) {
            imshow("Frame", frame);
            char c=(char)waitKey(25);
            if(c==27)
                break;
        }

        cap.release();
        destroyAllWindows();
    }


};

#endif //CAMERA_CAMERA_H
