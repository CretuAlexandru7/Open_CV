
/*******************************************************************************************
* This program serves as a demonstration of fundamental image processing operations        *
* using the OpenCV library                                                                 *
* Frames are read from the webcam and the following techiniques are applied on every frame:*
* **** color inversion;                                                                    *
* **** image thresholding;                                                                 *
* **** image mirroring;                                                                    *
* **** flipping the image;                                                                 *
* **** grayscale;                                                                          *
* **** absolute difference between two frames;                                             *
* **** Sobel edge detection method;                                                        *
*******************************************************************************************/

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "image_effects.h"
using namespace cv;

#define ASCII_ZERO '0'
#define ASCII_NINE '9'
#define PLUS_KEY 'm'
#define MINUS_KEY 'n'

/* Function used to clear the console output */
void vDoclearConsole()
{
    std::system("cls");
}
/* Function used to prin console user menu */
void vDoShowUserMeniu()
{
    std::cout << "###################################################" << std::endl;
    std::cout << "     1. INVERT colors of the image;" << std::endl;
    std::cout << "     2. BINARIZE the image;" << std::endl;
    std::cout << "        ( use n & m keys to modify the threshold )" << std::endl;
    std::cout << "     3. MIRROR the image;" << std::endl;
    std::cout << "     4. FLIP the image;" << std::endl;
    std::cout << "     5. GREYSCALE;" << std::endl;
    std::cout << "     6. ABSOLUTE DIFference between two frames;" << std::endl;
    std::cout << "     7. Sobel edge detection;" << std::endl;
    std::cout << "     8. Pixelate the image;" << std::endl;
    std::cout << "     0. EXIT the program;" << std::endl;
    std::cout << "###################################################" << std::endl;
}

int main() 
{    
    /* Open the default webcam(0) */
    cv::VideoCapture vcVideo_Cap(0);
    /* Few info massage are shown by the openCV library -> the following line mutes those. */
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    /* Check if the webcam is opened successfully */
    if (!vcVideo_Cap.isOpened()) {
        std::cout << "Failed to open the webcam." << std::endl;
        return -1;
    }
    
    /* Variable used to store the user keyboard pressed key */
    int iUserKey;
    /* Variable used to switch beween image processing techniques */
    int iTechniqueNumber = 9;
    /* Variable used to exit the program when the ESCAPE key is detected */
    bool bExitProgram = false;
    /* Variable used to set the threshold value for the image binarization */
    int iImgThreshold = 128;
    int iPixelSize = 10;

    /* Clear the console  and show the meniu / user options */
    vDoclearConsole();
    vDoShowUserMeniu();

    /* Frame used when calcultaing the absolute .... */
    cv::Mat frame2;
    /* Readand process frames from the webcam */
    while (!bExitProgram) {
        /* cv::Mat -> class which represents a matrix (used to store/manipulate images)*/
        cv::Mat mFrame;

        /* Read a frame from the webcam */ 
        vcVideo_Cap.read(mFrame);

        /* Check if the frame is empty */ 
        if (mFrame.empty()) {
            std::cout << "Failed to capture a frame." << std::endl;
            break;
        }  

        /* Get the dimensions of the frame */
        int iFrameRows = mFrame.rows;
        int iFramesCols = mFrame.cols;

        /* User keyboard input */
        iUserKey = cv::waitKey(1);
        if (iUserKey >= ASCII_ZERO && iUserKey <= ASCII_NINE)
        {
            iTechniqueNumber = iUserKey - ASCII_ZERO;
        }
        else if (iTechniqueNumber == 2 && iUserKey == MINUS_KEY)
        {
            iImgThreshold -= 1;
        }
        else if (iTechniqueNumber == 2 && iUserKey == PLUS_KEY)
        {
            iImgThreshold += 1;
        }
     

        /* Process different states */ 
        switch (iTechniqueNumber) {
        case 1:                
            vDoInvertColors(mFrame, iFrameRows, iFramesCols);
            break;
        case 2:
            vDoBinarizeImage(mFrame, iImgThreshold, iFrameRows, iFramesCols);
            break;
        case 3:
            vDoMirrorImage(mFrame, iFrameRows, iFramesCols);
            break;
        case 4:
            vDoFlipImage(mFrame, iFrameRows, iFramesCols);
            break;
        case 5:
            mFrame = matDoConvertToGrayscale(mFrame);
            break;
        case 6:
            mFrame = matDoConvertToGrayscale(mFrame);
            vcVideo_Cap.read(frame2);
            frame2 = matDoConvertToGrayscale(frame2);
            mFrame = matDoCalculateAbsoluteDifference(mFrame, frame2);
            break;
        case 7:
            vDoSobelEdgeDetection(mFrame);
            break;
        case 8:
            mFrame = matDoGeneratePixelatedImage(mFrame, iPixelSize);
            break;
        
        case 0:
            bExitProgram = true;
            break;
        default:
            break;
        }

        /* Display the technique number on the frame */
        std::string text = "Number: " + std::to_string(iTechniqueNumber);
        cv::putText(mFrame, text, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 165, 255), 2);

        /*Display the frame */ 
        cv::imshow("Webcam", mFrame);
    }

    /*  Release the webcam */
    vcVideo_Cap.release();

    return 0;
}

