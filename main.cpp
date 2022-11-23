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

void ProcessImage(const Mat &input, Mat &output)
{
    Mat cropped;
    Mat minimized;
    Mat greyScale;

    int smallDimension = min(input.rows, input.cols);
    getRectSubPix(input, Size(smallDimension, smallDimension), Point(input.cols / 2, input.rows / 2), cropped);

    resize(cropped, minimized, Size(windowDimension, windowDimension));
//    cvtColor(minimized, greyScale, COLOR_BGR2GRAY);
    flip(minimized, output, 1);
}

int main(int argc, char **argv)
{
    VideoCapture capture(0);
    if (!capture.isOpened())
    {
        printf("ERROR: Cannot open camera!");
        exit(1);
    }

    Mat image;
    Mat final;

    auto *display = new PixelDisplay(argc, argv);
    while (true)
    {
        capture.read(image);
        ProcessImage(image, final);
        display->DisplayImage(final);
    }
}
