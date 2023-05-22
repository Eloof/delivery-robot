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


    Mat frame;
    Mat frame_result;
    VideoCapture cap;

    Rect rect_bot_blue_part;
    Rect rect_bot_purple_part;
    Rect rect_target;

    Point centre_of_bot;

    int angle_bot;
    int angle_target;
    int distance_target;

    color_HSV BOT_BLUE_PART = color_HSV(0, 0, 0);
    color_HSV BOT_PURPLE_PART = color_HSV(0, 0, 0);
    color_HSV COLOR_TARGET = color_HSV(0, 0, 0);

public:

    Camera_detect(int id, color_HSV &bot_blue_part, color_HSV &bot_purple_part, color_HSV &color_target) {

        BOT_BLUE_PART.h = bot_blue_part.h;
        BOT_BLUE_PART.s = bot_blue_part.s;
        BOT_BLUE_PART.v = bot_blue_part.v;

        BOT_PURPLE_PART.h = bot_purple_part.h;
        BOT_PURPLE_PART.s = bot_purple_part.s;
        BOT_PURPLE_PART.v = bot_purple_part.v;

        COLOR_TARGET.h = color_target.h;
        COLOR_TARGET.s = color_target.s;
        COLOR_TARGET.v = color_target.v;

        this->cap.open(id);

        if (!cap.isOpened())
            cout << "Error opening video stream or file" << endl;


        this->refurbish_all();


    }


    // Поиск контуров объекта
    Rect detect_rect(color_HSV color) {

        vector<cv::Mat> stickers;
        cv::Mat image_hsv;
        std::vector<std::vector<cv::Point>> contours;
        cv::cvtColor(this->frame_result, image_hsv, cv::COLOR_BGR2HSV);
        cv::Mat tmp_img(frame.size(), CV_8U);
        cv::inRange(image_hsv, cv::Scalar(color.h - 20, color.s - 50, 0),
                    cv::Scalar(color.h + 20, color.s + 50, 255),
                    tmp_img);
        //Выделение непрерывных областей
        cv::findContours(tmp_img, contours, 0, 1);

        cv::Rect max_rect(0, 0, 0, 0);
        for (uint i = 0; i < contours.size(); i++) {
            cv::Mat sticker;
            //Для каждой области определяем ограничивающий прямоугольник
            cv::Rect rect = cv::boundingRect(contours[i]);

            //Ищем из всех самый большой прямоугольник
            if (rect.height * rect.width > max_rect.height * max_rect.width) {
                max_rect = rect;
            }
        }

        return max_rect;
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
    int distance_beetwen_point(Point p_a, Point p_b) {
        return sqrt((p_b.x - p_a.x) * (p_b.x - p_a.x) + (p_b.y - p_a.y) * (p_b.y - p_a.y));
    }


    void refurbish_angle_bot() {
        Point p_a = rect_centre(rect_bot_purple_part);
        Point p_b = rect_centre(rect_bot_blue_part);

        this->centre_of_bot = centre_beetwen_point(p_a, p_b);
        this->angle_bot = calc_angle_beetwen_point(p_b, p_a);

    }

    void refurbish_angle_to_target() {
        Point point_target = rect_centre(rect_target);
        int angle_bot_centre_to_target = calc_angle_beetwen_point(this->centre_of_bot, point_target);
        this->angle_target = angle_bot_centre_to_target - this->angle_bot;

    }

    void refurbish_distance_to_target() {
        Point point_target = rect_centre(rect_target);
        this->distance_target = distance_beetwen_point(this->centre_of_bot, point_target);

    }

    int get_angle_to_target() {
        return this->angle_target;
    }

    int get_angle_bot() {
        return this->angle_bot;
    }

    int get_distance_to_target() {
        return this->distance_target;
    }

    bool has_delta_angle_to_target(int delta) {
        if (abs(this->angle_target) > delta)
            return true;
        else
            return false;
    }

    bool has_distance_to_target(int distance) const {
        if (this->distance_target < distance)
            return false;
        else
            return true;

    }

    void refurbish_all() {
        cap >> frame;
        frame_result = frame;

        this->rect_bot_blue_part = this->detect_rect(this->BOT_BLUE_PART);
        this->rect_bot_purple_part = this->detect_rect(this->BOT_PURPLE_PART);
        this->rect_target = this->detect_rect(this->COLOR_TARGET);

        this->refurbish_angle_bot();
        this->refurbish_angle_to_target();
        this->refurbish_distance_to_target();

        cout << this->get_distance_to_target() << '\n';

    }



    ~Camera_detect(){
        cap.release();
        destroyAllWindows();
    }
};
#endif //CAMERA_CAMERA_H