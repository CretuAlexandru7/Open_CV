#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
using namespace cv;

/* Function used to invert te colors of the frame */
/* Iterates over the entire matrix and changes the values of the BGR color channels */
void vDoInvertColors(cv::Mat frame, int rows, int cols)
{
    /* Iterate and manipulate each pixel */
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            /* Vec3b -> represents a vector with three elements (three color channels BGR ORDER) */
            cv::Vec3b pixel = frame.at<cv::Vec3b>(i, j);

            /* Access individual color channels(BGR order) */
            unsigned char blue = pixel[0];
            unsigned char green = pixel[1];
            unsigned char red = pixel[2];

            /* Modify pixel values */
            pixel[0] = 255 - blue;
            pixel[1] = 255 - green;
            pixel[2] = 255 - red;

            /* Update the pixel value */
            frame.at<cv::Vec3b>(i, j) = pixel;
        }
    }    
}

/* Function used to transform the image into a binary image. */
/* During the binarization process, each pixel in the image is compared to the threshold value.
 * If the pixel intensity is higher than the threshold, it is assigned the white value 
 * otherwise the black value. */
void vDoBinarizeImage(cv::Mat frame, int img_threshold, int rows, int cols)
{
    /* Iterate over each pixel of the frame */ 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Vec3b pixel = frame.at<cv::Vec3b>(i, j);

            /* Calculate the grayscale intensity as the average of the color channels */ 
            int intensity = (pixel[0] + pixel[1] + pixel[2]) / 3;
            /* Binarize the pixel based on the threshold */ 
            if (intensity >= img_threshold) {
                /* Update the pixel value to white */
                frame.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);  // Set white pixel
            }
            else {
                /* Update the pixel value to black */
                frame.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);  // Set black pixel
            }
        }
    }

    /* Display the threshold number on the frame */
    std::string text = "Threshold: " + std::to_string(img_threshold);
    cv::putText(frame, text, cv::Point(10, rows-20), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 165, 255), 2);
}


/* Function used to flip the image horizontally -> mirrored / symmetrical effect */
void vMirrorImage(cv::Mat frame, int rows, int cols)
{
    /* Iterate and manipulate each pixel */
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            /* Vec3b -> represents a vector with three elements (three color channels BGR ORDER) */
            cv::Vec3b pixel1 = frame.at<cv::Vec3b>(i, j);
            cv::Vec3b pixel2 = frame.at<cv::Vec3b>(i, cols - j - 1);

            /* Swap the pixel values to mirror the image horizontally */
            frame.at<cv::Vec3b>(i, j) = pixel2;
            frame.at<cv::Vec3b>(i, cols - j - 1) = pixel1;
        }
    }
}


/* Function used to flip the image vertically -> flipped / symmetrical effect */
void vFlipImage(cv::Mat frame, int rows, int cols)
{
    /* Iterate and manipulate each pixel */
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols; j++) {
            /* Vec3b -> represents a vector with three elements (three color channels BGR ORDER) */
            cv::Vec3b pixel1 = frame.at<cv::Vec3b>(i, j);
            cv::Vec3b pixel2 = frame.at<cv::Vec3b>(rows - i - 1, j);

            /* Swap pixel values */
            frame.at<cv::Vec3b>(i, j) = pixel2;
            frame.at<cv::Vec3b>(rows - i - 1, j) = pixel1;
        }
    }
}

/* Function used to convert the received (parameter) frame into a grayscale one. */
/* For each pixel, it retrieves the BGR pixel values and applies the grayscale conversion formula:
 * 0.299 * R + 0.587 * G + 0.114 * B.*/
cv::Mat convertToGrayscale(const cv::Mat& frame) {
    /*  Create an empty grayscale frame with the same dimensions as the input frame */
    cv::Mat temp_frame(frame.size(), frame.type());

    /*  Iterate over each pixel of the input frame and apply the formula to it */
    for (int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++) {
            // Get the BGR pixel values
            cv::Vec3b bgrPixel = frame.at<cv::Vec3b>(i, j);
            // Convert to grayscale using formula: 0.299*R + 0.587*G + 0.114*B
            unsigned char grayscaleValue = static_cast<unsigned char>(0.299 * bgrPixel[2] +
                                                                      0.587 * bgrPixel[1] +
                                                                      0.114 * bgrPixel[0]);
            // Set the grayscale value in the corresponding pixel of the grayscale frame
            temp_frame.at<cv::Vec3b>(i, j) = cv::Vec3b(grayscaleValue, grayscaleValue, grayscaleValue);
        }
    }

    return temp_frame;
}


/* Function used to calculate the absolute difference between two consecutive frames, on a pixel-wise basis */
cv::Mat calculateAbsoluteDifference(const cv::Mat& frame1, const cv::Mat& frame2) {
    /*  Ensure that the input frames have the same sizeand type */
    CV_Assert(frame1.size() == frame2.size() && frame1.type() == frame2.type());

    /*  Create an empty frame to store the absolute difference between two consecutive ones */
    cv::Mat diff(frame1.size(), frame1.type());

    /* Iterate over each pixel of the frames and make the difference */
    for (int i = 0; i < frame1.rows; i++) {
        for (int j = 0; j < frame1.cols; j++) {
            // Get the pixel values of both frames
            cv::Vec3b pixel1 = frame1.at<cv::Vec3b>(i, j);
            cv::Vec3b pixel2 = frame2.at<cv::Vec3b>(i, j);

            int diffBlue = std::abs(pixel1[0] - pixel2[0]);
            int diffGreen = std::abs(pixel1[1] - pixel2[1]);
            int diffRed = std::abs(pixel1[2] - pixel2[2]);

            /* Set the absolute difference in the corresponding pixel of the output frame */
            diff.at<cv::Vec3b>(i, j) = cv::Vec3b(diffBlue, diffGreen, diffRed);
        }
    }

    return diff;
}

