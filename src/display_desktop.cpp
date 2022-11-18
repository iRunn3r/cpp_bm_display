////
//// Created by vaidas on 17/11/2022.
////
#if !defined __ARM_ARCH || defined TARGET_OS_MAC

#include "../include/display.h"

void PixelDisplay::DisplayImage(const Mat &material)
{
    Mat enlarged;
    resize(material, enlarged, Size(_displayDimension, _displayDimension), 0, 0, INTER_AREA);
    imshow(_windowName, enlarged);
    waitKey(25);
}

PixelDisplay::~PixelDisplay()
{
    destroyWindow(_windowName);
}

PixelDisplay::PixelDisplay(int argc, char** argv)
{
    namedWindow(_windowName);
}
#endif
