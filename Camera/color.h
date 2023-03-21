#ifndef CAMERA_COLOR_H
#define CAMERA_COLOR_H

struct color_HSV{
    int h;
    int s;
    int v;

    color_HSV(int hue, int saturation, int value):h(hue), s(saturation), v(value) {}
};
#endif //CAMERA_COLOR_H
