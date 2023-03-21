#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H

#include "iostream"
#include "opencv2/opencv.hpp"
#include "color.h"

using namespace std;
using namespace cv;


class Camera_detect {

private:
    string FILE_NAME;

    color_HSV *BOT_BLUE_PART{};
    color_HSV *BOT_PURPLE_PART{};
    color_HSV *COLOR_TARGET{};

    Mat frame;
    VideoCapture cap;

public:

    Camera_detect(string &filename, color_HSV &bot_blue_part, color_HSV &bot_purple_part, color_HSV &color_target) {
        this->FILE_NAME = filename;

        BOT_BLUE_PART->h = bot_blue_part.h;
        BOT_BLUE_PART->s = bot_blue_part.s;
        BOT_BLUE_PART->v = bot_blue_part.v;

        BOT_PURPLE_PART->h = bot_purple_part.h;
        BOT_PURPLE_PART->s = bot_purple_part.s;
        BOT_PURPLE_PART->v = bot_purple_part.v;

        COLOR_TARGET->h = color_target.h;
        COLOR_TARGET->s = color_target.s;
        COLOR_TARGET->v = color_target.v;

        this->cap.open(FILE_NAME);
        if (!cap.isOpened())
            cout << "Error opening video stream or file" << endl;
    }

    // Поиск контуров объекта(доделать)
    bool search_rect() {
        vector<cv::Mat> objects;
        Mat image_hsv;
        vector<vector<Point>> contours;

        cv::cvtColor(frame, image_hsv, COLOR_BGR2HSV);
        Mat tmp_img(frame.size(), CV_8U);

        findContours(tmp_img, contours, 0, 1);
        return 1;

        /////////////////////////?????????????
    }

    // Центр масс
    Point rect_centre(Rect r) {
        int x = r.x + (r.width / 2);
        int y = r.y + (r.height / 2);

        return Point(x, y);
    }

    // Центр между точками(для робота)
    Point centre_beetwen_point(Point p1, Point p2) {
        int x = (p1.x + p2.x) / 2;
        int y = (p1.y + p2.y) / 2;

        return Point(x, y);
    }

    // Необходимый угол поворота
    int calc_angle_beetwen_point(Point p_a, Point p_b) {
        double hyp = pow((p_b.x - p_a.x) * (p_b.x - p_a.x) + (p_b.y - p_a.y) * (p_b.y - p_a.y), 2);
        asin(hyp / (p_b.x - p_a.x));

        double a = atan2((p_b.x - p_a.x), (p_b.y - p_a.y)) / M_PI * 180;

        if (a >= 0)
            return a;
        else
            return 360 + a;
    }

    // Дистанция до точки
    int distance_beetwen_point(Point p_a, Point p_b){
        return sqrt((p_b.x - p_a.x)*(p_b.x - p_a.x) + (p_b.y - p_a.y)*(p_b.y - p_a.y));
    }

    ~Camera_detect(){
        cap.release();
        destroyAllWindows();
    }
};
#endif //CAMERA_CAMERA_H