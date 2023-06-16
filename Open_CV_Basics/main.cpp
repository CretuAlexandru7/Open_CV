
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

/* Function used to clear the console output */
void vDoclearConsole()
{
    std::system("cls");
}

int main() 
{    
    /* Open the default webcam(0) */
    cv::VideoCapture cap(0);
    /* Few info massage are shown by the openCV library -> the following line mutes those. */
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    /* Check if the webcam is opened successfully */
    if (!cap.isOpened()) {
        std::cout << "Failed to open the webcam." << std::endl;
        return -1;
    }
    
    /* Variable used to store the user keyboard pressed key */
    int user_key;
    /* Variable used to switch beween image processing techniques */
    int technique_number = 9;
    /* Variable used to exit the program when the ESCAPE key is detected */
    bool exitProgram = false;
    /* Variable used to set the threshold value for the image binarization */
    int img_threshold = 128;

    /* Clear the console  and show the meniu / user options */
    vDoclearConsole();
    std::cout << "###################################################" << std::endl;
    std::cout << "     1. INVERT colors of the image;" << std::endl;
    std::cout << "     2. BINARIZE the image;" << std::endl;
    std::cout << "        ( use n & m keys to modify the threshold )" << std::endl;
    std::cout << "     3. MIRROR the image;" << std::endl;
    std::cout << "     4. FLIP the image;" << std::endl;
    std::cout << "     0. EXIT the program;" << std::endl;
    std::cout << "###################################################" << std::endl;

    /* Frame used when calcultaing the absolute .... */
    cv::Mat frame2;
    /* Readand process frames from the webcam */
    while (!exitProgram) {
        /* cv::Mat -> class which represents a matrix (used to store/manipulate images)*/
        cv::Mat frame;

        /* Read a frame from the webcam */ 
        cap.read(frame);

        /* Check if the frame is empty */ 
        if (frame.empty()) {
            std::cout << "Failed to capture a frame." << std::endl;
            break;
        }  

        /* Get the dimensions of the frame */
        int frame_rows = frame.rows;
        int frames_cols = frame.cols;

        /* User keyboard input */
        user_key = cv::waitKey(1);
        if (user_key >= '0' && user_key <= '9')
        {
            technique_number = user_key - '0';
        }
        else if (technique_number == 2 && user_key == 'n')
        {
            img_threshold -= 1;
        }
        else if (technique_number == 2 && user_key == 'm')
        {
            img_threshold += 1;
        }
     

        /* Process different states */ 
        switch (technique_number) {
        case 1:                
            vDoInvertColors(frame, frame_rows, frames_cols);
            break;
        case 2:
            vDoBinarizeImage(frame, img_threshold, frame_rows, frames_cols);
            break;
        case 3:
            vMirrorImage(frame, frame_rows, frames_cols);
            break;
        case 4:
            vFlipImage(frame, frame_rows, frames_cols);
            break;
        case 5:
            frame = convertToGrayscale(frame);
            cap.read(frame2);
            frame2 = convertToGrayscale(frame2);
            frame = calculateAbsoluteDifference(frame, frame2);
            break;
        case 6:            
            frame = convertToGrayscale(frame);
            break;
        case 0:
            exitProgram = true;
            break;
        default:
            break;
        }

        /* Display the technique number on the frame */
        std::string text = "Number: " + std::to_string(technique_number);
        cv::putText(frame, text, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 165, 255), 2);

        /*Display the frame */ 
        cv::imshow("Webcam", frame);
    }

    /*  Release the webcam */
    cap.release();

    return 0;
}