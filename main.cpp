#include <cstdio>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include "led-matrix.h"

using namespace cv;
using namespace std;
using rgb_matrix::RGBMatrix;

const char *windowName = "Pixel Camera";
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

    namedWindow(windowName);
    VideoCapture capture(0);

    if (!capture.isOpened()) {
        printf("ERROR: Cannot open camera!");
        exit(1);
    }

    Mat cropped;        // stores image cropped to the largest square allowed by camera
    Mat minimized;      // stores image reduced to the LED Matrix dimension
    Mat final;          // stores image at the final LED matrix resolution
    Mat colorCorrected;
    Mat enlarged;       // stores image enlarged to be viewed on a computer screen


//    RGBMatrix::Options my_defaults;
//    my_defaults.hardware_mapping = "adafruit-hat";
//    my_defaults.chain_length = 1;
//    my_defaults.show_refresh_rate = true;
//    rgb_matrix::RuntimeOptions runtime_defaults;
//    // If you drop privileges, the root user you start the program with
//    // to be able to initialize the hardware will be switched to an unprivileged
//    // user to minimize a potential security attack surface.
//    runtime_defaults.drop_privileges = 1;
//    RGBMatrix *matrix = RGBMatrix::CreateFromFlags(&argc, &argv,
//                                                   &my_defaults,
//                                                   &runtime_defaults);
//    if (matrix == nullptr) {
//        PrintMatrixFlags(stderr, my_defaults, runtime_defaults);
//    }

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

        resize(final, enlarged, Size(320, 320), 0, 0, INTER_AREA);
        imshow(windowName, enlarged);
        waitKey(25);
    }
}
