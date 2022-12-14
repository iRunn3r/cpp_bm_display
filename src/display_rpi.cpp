//
// Created by vaidas on 17/11/2022.
//

#if defined __ARM_ARCH && !defined TARGET_OS_MAC

#include "../include/display.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace rgb_matrix;

void PixelDisplay::DisplayImage(const Mat &image)
{
    for (size_t y = 0; y < image.rows; ++y)
    {
        for (size_t x = 0; x < image.cols; ++x)
        {
            Vec3b color = image.at<Vec3b>(Point(x, y));
            _matrix->SetPixel(x, y, color[2], color[1], color[0]);
        }
    }

    usleep(20000);
}

PixelDisplay::PixelDisplay(int argc, char **argv)
{
    RGBMatrix::Options matrixDefaults;
    matrixDefaults.hardware_mapping = "adafruit-hat-pwm";
    matrixDefaults.chain_length = 1;
    matrixDefaults.rows = 32;
    matrixDefaults.cols = 32;
    matrixDefaults.show_refresh_rate = true;
    rgb_matrix::RuntimeOptions runtime_defaults;
    runtime_defaults.drop_privileges = 1;
    _matrix = RGBMatrix::CreateFromFlags(&argc, &argv, &matrixDefaults, &runtime_defaults);
    // if (_matrix == nullptr) {
    //     rgb_matrix::PrintMatrixFlags(stderr, matrixDefaults, runtime_defaults);
    // }
}

PixelDisplay::~PixelDisplay()
{
    delete _matrix;
}
#endif
