#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace cv;
using namespace std;

HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD dwBytesWritten = 0;

int main()
{
    VideoCapture cap(0);

    int dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get camera width

    int PixelWidth = dWidth / 3;
    int PixelHeight = PixelWidth / 2.1818;


    std::cout << "\033[8;" << PixelHeight * 3 << ";" << PixelWidth << "t"; // set console size

    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video camera" << endl;
        cin.get();
        return -1;
    }

    //Different gradients
    char gradient[] = " .:!/r(l1Z4H9W8$@";
    //char gradient[] = " .`:I!>~_&[{)|/frxnuvczXYUJCLQ0Zmwqpdbkhao#MW8B@$";
    int x;
    int y;

    char* arr = { 0 };
    wchar_t* mass = new wchar_t[PixelWidth * PixelHeight + 1];

    Mat frame;
    Mat Gray;
    Mat Pixel;

    while (true)
    { 
        //resize and grayscale image
        bool bSuccess = cap.read(frame);

        if(bSuccess == false)
        {
            cout << "video camera is disconnected" << endl;
            cin.get();
            break;
        }

        cvtColor(frame, Gray, COLOR_RGB2GRAY);
        resize(Gray, Pixel, Size(PixelWidth, PixelHeight), INTER_LINEAR);
        //imshow("image", Pixel);

        for (y = 0; y < PixelHeight; y++)
        {
            for (x = 0; x < PixelWidth; x++)
            {
                int pixelGrayValue = Pixel.at<uchar>(y, x);
                mass[x + y * PixelWidth] = gradient[pixelGrayValue / (sizeof(gradient) - 1)];
            }
        }

        mass[PixelWidth * PixelHeight] = '\0';
        WriteConsoleOutputCharacter(Handle, mass, PixelWidth * PixelHeight, { 0, 0 }, &dwBytesWritten); //Buffering image and output

        waitKey();
    }
    return 0;
}
