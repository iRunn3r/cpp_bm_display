//
// Created by vaidas on 17/11/2022.
//

#ifndef DISPLAYIMAGE_DISPLAY_H
#define DISPLAYIMAGE_DISPLAY_H

#include <opencv2/opencv.hpp>
#if defined __ARM_ARCH && !defined TARGET_OS_MAC
#include "led-matrix.h"
#endif

using namespace cv;

class PixelDisplay
{
public:
    PixelDisplay(int argc, char **argv);
    PixelDisplay() : PixelDisplay(-1, nullptr) {}
    void DisplayImage(const Mat& image);
private:
    const char* _windowName = "Pixel Camera";
    const int _displayDimension = 320;
    ~PixelDisplay();
#if defined __ARM_ARCH && !defined TARGET_OS_MAC
    rgb_matrix::RGBMatrix *_matrix;
#endif
};

#endif //DISPLAYIMAGE_DISPLAY_H
