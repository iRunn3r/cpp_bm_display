#include <cstdio>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include "include/display.h"

using namespace cv;
using namespace std;

const int windowDimension = 32;

void ReduceColors(Mat &image, int factor=32)
{
    int rowCount = image.rows;
    int columnCount = image.cols * image.channels();
    for (int j = 0; j < rowCount; j++)
    {
        auto* data = image.ptr<uchar>(j);
        for (int i = 0; i < columnCount; i++)
        {
            data[i] = data[i] / factor * factor + factor / 2;
        }
    }
}

int main(int argc, char **argv)
{
    Mat image;
    VideoCapture capture(0);

    if (!capture.isOpened()) {
        printf("ERROR: Cannot open camera!");
        exit(1);
    }

    Mat cropped;        // stores image cropped to the largest square allowed by camera
    Mat minimized;      // stores image reduced to the LED Matrix dimension
    Mat final;          // stores image at the final LED matrix resolution
    Mat colorCorrected;

    auto *display = new PixelDisplay(argc, argv);
    while (true)
    {
        capture.read(image);

        if (image.cols < 1 || image.rows < 1)
        {
            continue;
        }

        int smallDimension = min(image.rows, image.cols);
        getRectSubPix(image, Size(smallDimension, smallDimension), Point(image.cols / 2, image.rows / 2),
                      cropped);

        resize(cropped, minimized, Size(windowDimension, windowDimension));
        ReduceColors(minimized);
        flip(minimized, final, 1);
        display->DisplayImage(final);
    }
}
