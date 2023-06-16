
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
    std::cout << "     5. GREYSCALE;" << std::endl;
    std::cout << "     6. ABSOLUTE DIFference between two frames;" << std::endl;
    std::cout << "     7. Sobel edge detection;" << std::endl;
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
            break;
        case 6:
            frame = convertToGrayscale(frame);
            cap.read(frame2);
            frame2 = convertToGrayscale(frame2);
            frame = calculateAbsoluteDifference(frame, frame2);
            break;
        case 7:
            sobelEdgeDetection(frame);
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






















//const int NUMBER = 100;
//const int DELAY = 5;
//const int window_width = 900;
//const int window_height = 600;
//int x_1 = -window_width / 2;
//int x_2 = window_width * 3 / 2;
//int y_1 = -window_width / 2;
//int y_2 = window_width * 3 / 2;
//static Scalar randomColor(RNG& rng);
//int Drawing_Random_Lines(Mat image, char* window_name, RNG rng);
//int Drawing_Random_Rectangles(Mat image, char* window_name, RNG rng);
//int Drawing_Random_Ellipses(Mat image, char* window_name, RNG rng);
//int Drawing_Random_Polylines(Mat image, char* window_name, RNG rng);
//int Drawing_Random_Filled_Polygons(Mat image, char* window_name, RNG rng);
//int Drawing_Random_Circles(Mat image, char* window_name, RNG rng);
//int Displaying_Random_Text(Mat image, char* window_name, RNG rng);
//int Displaying_Big_End(Mat image, char* window_name, RNG rng);
//int main(void)
//{
//    int c;
//    char window_name[] = "Drawing_2 Tutorial";
//    RNG rng(0xFFFFFFFF);
//    Mat image = Mat::zeros(window_height, window_width, CV_8UC3);
//    imshow(window_name, image);
//    waitKey(DELAY);
//    c = Drawing_Random_Lines(image, window_name, rng);
//    if (c != 0) return 0;
//    c = Drawing_Random_Rectangles(image, window_name, rng);
//    if (c != 0) return 0;
//    c = Drawing_Random_Ellipses(image, window_name, rng);
//    if (c != 0) return 0;
//    c = Drawing_Random_Polylines(image, window_name, rng);
//    if (c != 0) return 0;
//    c = Drawing_Random_Filled_Polygons(image, window_name, rng);
//    if (c != 0) return 0;
//    c = Drawing_Random_Circles(image, window_name, rng);
//    if (c != 0) return 0;
//    c = Displaying_Random_Text(image, window_name, rng);
//    if (c != 0) return 0;
//    c = Displaying_Big_End(image, window_name, rng);
//    if (c != 0) return 0;
//    waitKey(0);
//    return 0;
//}
//static Scalar randomColor(RNG& rng)
//{
//    int icolor = (unsigned)rng;
//    return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
//}
//int Drawing_Random_Lines(Mat image, char* window_name, RNG rng)
//{
//    Point pt1, pt2;
//    for (int i = 0; i < NUMBER; i++)
//    {
//        pt1.x = rng.uniform(x_1, x_2);
//        pt1.y = rng.uniform(y_1, y_2);
//        pt2.x = rng.uniform(x_1, x_2);
//        pt2.y = rng.uniform(y_1, y_2);
//        line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
//        imshow(window_name, image);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//int Drawing_Random_Rectangles(Mat image, char* window_name, RNG rng)
//{
//    Point pt1, pt2;
//    int lineType = 8;
//    int thickness = rng.uniform(-3, 10);
//    for (int i = 0; i < NUMBER; i++)
//    {
//        pt1.x = rng.uniform(x_1, x_2);
//        pt1.y = rng.uniform(y_1, y_2);
//        pt2.x = rng.uniform(x_1, x_2);
//        pt2.y = rng.uniform(y_1, y_2);
//        rectangle(image, pt1, pt2, randomColor(rng), MAX(thickness, -1), lineType);
//        imshow(window_name, image);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//int Drawing_Random_Ellipses(Mat image, char* window_name, RNG rng)
//{
//    int lineType = 8;
//    for (int i = 0; i < NUMBER; i++)
//    {
//        Point center;
//        center.x = rng.uniform(x_1, x_2);
//        center.y = rng.uniform(y_1, y_2);
//        Size axes;
//        axes.width = rng.uniform(0, 200);
//        axes.height = rng.uniform(0, 200);
//        double angle = rng.uniform(0, 180);
//        ellipse(image, center, axes, angle, angle - 100, angle + 200,
//            randomColor(rng), rng.uniform(-1, 9), lineType);
//        imshow(window_name, image);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//int Drawing_Random_Polylines(Mat image, char* window_name, RNG rng)
//{
//    int lineType = 8;
//    for (int i = 0; i < NUMBER; i++)
//    {
//        Point pt[2][3];
//        pt[0][0].x = rng.uniform(x_1, x_2);
//        pt[0][0].y = rng.uniform(y_1, y_2);
//        pt[0][1].x = rng.uniform(x_1, x_2);
//        pt[0][1].y = rng.uniform(y_1, y_2);
//        pt[0][2].x = rng.uniform(x_1, x_2);
//        pt[0][2].y = rng.uniform(y_1, y_2);
//        pt[1][0].x = rng.uniform(x_1, x_2);
//        pt[1][0].y = rng.uniform(y_1, y_2);
//        pt[1][1].x = rng.uniform(x_1, x_2);
//        pt[1][1].y = rng.uniform(y_1, y_2);
//        pt[1][2].x = rng.uniform(x_1, x_2);
//        pt[1][2].y = rng.uniform(y_1, y_2);
//        const Point* ppt[2] = { pt[0], pt[1] };
//        int npt[] = { 3, 3 };
//        polylines(image, ppt, npt, 2, true, randomColor(rng), rng.uniform(1, 10), lineType);
//        imshow(window_name, image);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//int Drawing_Random_Filled_Polygons(Mat image, char* window_name, RNG rng)
//{
//    int lineType = 8;
//    for (int i = 0; i < NUMBER; i++)
//    {
//        Point pt[2][3];
//        pt[0][0].x = rng.uniform(x_1, x_2);
//        pt[0][0].y = rng.uniform(y_1, y_2);
//        pt[0][1].x = rng.uniform(x_1, x_2);
//        pt[0][1].y = rng.uniform(y_1, y_2);
//        pt[0][2].x = rng.uniform(x_1, x_2);
//        pt[0][2].y = rng.uniform(y_1, y_2);
//        pt[1][0].x = rng.uniform(x_1, x_2);
//        pt[1][0].y = rng.uniform(y_1, y_2);
//        pt[1][1].x = rng.uniform(x_1, x_2);
//        pt[1][1].y = rng.uniform(y_1, y_2);
//        pt[1][2].x = rng.uniform(x_1, x_2);
//        pt[1][2].y = rng.uniform(y_1, y_2);
//        const Point* ppt[2] = { pt[0], pt[1] };
//        int npt[] = { 3, 3 };
//        fillPoly(image, ppt, npt, 2, randomColor(rng), lineType);
//        imshow(window_name, image);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//int Drawing_Random_Circles(Mat image, char* window_name, RNG rng)
//{
//    int lineType = 8;
//    for (int i = 0; i < NUMBER; i++)
//    {
//        Point center;
//        center.x = rng.uniform(x_1, x_2);
//        center.y = rng.uniform(y_1, y_2);
//        circle(image, center, rng.uniform(0, 300), randomColor(rng),
//            rng.uniform(-1, 9), lineType);
//        imshow(window_name, image);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//int Displaying_Random_Text(Mat image, char* window_name, RNG rng)
//{
//    int lineType = 8;
//    for (int i = 1; i < NUMBER; i++)
//    {
//        Point org;
//        org.x = rng.uniform(x_1, x_2);
//        org.y = rng.uniform(y_1, y_2);
//        putText(image, "Testing text rendering", org, rng.uniform(0, 8),
//            rng.uniform(0, 100) * 0.05 + 0.1, randomColor(rng), rng.uniform(1, 10), lineType);
//        imshow(window_name, image);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//int Displaying_Big_End(Mat image, char* window_name, RNG)
//{
//    Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
//    Point org((window_width - textsize.width) / 2, (window_height - textsize.height) / 2);
//    int lineType = 8;
//    Mat image2;
//    for (int i = 0; i < 255; i += 2)
//    {
//        image2 = image - Scalar::all(i);
//        putText(image2, "OpenCV forever!", org, FONT_HERSHEY_COMPLEX, 3,
//            Scalar(i, i, 255), 5, lineType);
//        imshow(window_name, image2);
//        if (waitKey(DELAY) >= 0)
//        {
//            return -1;
//        }
//    }
//    return 0;
//}
//
#include <opencv2/opencv.hpp>
#define HALF_LINE(x) x/2
#define THIRDS_LINE(x) x/1.5
#define EIGHTH_LINE(x) x/8

//int main()
//{
//    // Create a blank image to draw the half-arch
//    cv::Mat image(400, 400, CV_8UC3, cv::Scalar(0, 0, 0));
//
//    int frame_width = image.cols;
//    int frame_height = image.rows;
//
//    /* Create an anchor center line for reference */
//    int center_line_x = HALF_LINE(frame_width);
//    /* Trajectory line offset used to plot the 2 trajectory lines*/
//    int trajectory_line_x_offset = EIGHTH_LINE(frame_width);
//    //int line_thickness = static_cast<int>((1 - static_cast<double>(frame_height - line_lenght) / frame_height) * max_line_thickness);
//    
//    // Parameters of the ellipse
//    cv::Point center(center_line_x + 2*trajectory_line_x_offset, frame_height-20);
//    double angle = 90; // in degrees
//    
//    cv::Size axes(frame_height / 3, 50);
//    int startAngle = 0;                   // use this with 180 for the other one
//    int endAngle = 140; // in degrees (only draw the right side)
//    int thickness = 2;    
//    cv::Scalar color(0, 255, 0); // green color
//    
//                                 /* Center line (white) */
//    cv::line(image, cv::Point(center_line_x, 0), cv::Point(center_line_x, frame_height), cv::Scalar(255, 255, 255), 1);
//    /* Green lines for the trajectory displayed info: */
//    /* To plot the lines from the bottom start from the frame_height -> the picture pixel patrix starts from the top left corner P(0,0) */
//    cv::line(image, cv::Point(center_line_x - trajectory_line_x_offset, frame_height), cv::Point(center_line_x - trajectory_line_x_offset, THIRDS_LINE(frame_height)), cv::Scalar(0, 255, 0), 2);
//    cv::line(image, cv::Point(center_line_x + trajectory_line_x_offset, frame_height), cv::Point(center_line_x + trajectory_line_x_offset, THIRDS_LINE(frame_height)), cv::Scalar(0, 255, 0), 2);
//    
//    
//    std::vector<cv::Point> contour;
//    cv::ellipse2Poly(center, axes, static_cast<int>(angle), startAngle, endAngle, 10, contour);
//
//    // Draw the half-arch on the image
//    cv::polylines(image, contour, false, color, thickness);
//
//    // Display the image
//    cv::imshow("Half-Arch", image);
//    cv::waitKey(0);
//
//    return 0;
//}


//#include <opencv2/opencv.hpp>
//
//int main()
//{
//    // Create a blank image to draw the curve
//    cv::Mat image(400, 400, CV_8UC3, cv::Scalar(0, 0, 0));
//
//    // Parameters
//    int width = image.cols;
//    int height = image.rows;
//    int angleDegrees = 80; // Specify the angle of the line in degrees
//
//    // Calculate the endpoint of the curve
//    cv::Point startPoint(width/2, height); // Start from the middle bottom of the screen
//    cv::Point endPoint;
//    double angleRadians = angleDegrees * CV_PI / 180.0;
//    endPoint.x = startPoint.x + height * std::tan(angleRadians);
//    endPoint.y = 0;
//
//    // Calculate the radius and center of the curve
//    int radius = (endPoint.x - startPoint.x) / 2;
//    cv::Point center(startPoint.x + radius, startPoint.y - radius);
//
//    // Draw the curve on the image
//    cv::Scalar color(0, 255, 0); // Green color
//    int thickness = 2;
//    cv::ellipse(image, center, cv::Size(radius, radius), 0, 0, 180, color, thickness);
//
//    // Display the image
//    cv::imshow("Curve", image);
//    cv::waitKey(0);
//
//    return 0;
//}


//#include <opencv2/opencv.hpp>
//
//int main()
//{
//    // Create a blank image to draw the curve
//    cv::Mat image(400, 400, CV_8UC3, cv::Scalar(0, 0, 0));
//
//    // Parameters
//    int width = image.cols;
//    int height = image.rows;
//    int angleDegrees = 80; // Specify the angle of the line in degrees
//
//    // Generate 20 random points
//    std::vector<cv::Point> points;
//    for (int i = 0; i < height/3; i++)
//    {
//        cv::Point point(width / 2 + i, 2*height/3 + i);
//        points.push_back(point);
//    }
//
//    // Draw the polyline on the image
//    cv::Scalar color(0, 255, 0); // Green color
//    int thickness = 2;
//    cv::polylines(image, points, false, color, thickness);
//
//    // Display the image
//    cv::imshow("Polyline", image);
//    cv::waitKey(0);
//
//    return 0;
//}



//int main()
//{
//    // Create a blank image to draw the curve
//    cv::Mat image(400, 400, CV_8UC3, cv::Scalar(0, 0, 0));
//
//    // Parameters
//    int width = image.cols;
//    int height = image.rows;
//
//    int offset = 100;
//
//    // Parameters of the circle
//    cv::Point fixedPoint(width/2 + 30 + offset, height); // Fixed point at (100, 200)
//    int radius = 30 + offset;
//    cv::Scalar color(0, 0, 255); // Red color
//    int thickness = 2;
//
//    cv::line(image, cv::Point(width/2, 0), cv::Point(width / 2, height), cv::Scalar(255, 255, 255), 1);
//
//    // Draw the circle on the image
//    cv::circle(image, fixedPoint, radius, color, thickness);
//
//    // Display the image
//    cv::imshow("Circle", image);
//    cv::waitKey(0);
//
//    return 0;
//}



//
//#include <cmath>
//
//int main()
//{
//    // Create a blank image
//    cv::Mat image(400, 400, CV_8UC3, cv::Scalar(0, 0, 0));
//
//    // Parameters of the circle
//    cv::Point center(200, 200);
//    int radius = 100;
//
//    // Point on the circle
//    double angle_deg = 200;
//    double angle_rad = angle_deg * CV_PI / 180.0;
//    int x = static_cast<int>(center.x + radius * std::cos(angle_rad));
//    int y = static_cast<int>(center.y + radius * std::sin(angle_rad));
//    cv::Point point_on_circle(x, y);
//
//    // Calculate the slope of the tangent line
//    double slope = -std::cos(angle_rad) / std::sin(angle_rad);
//
//    double angle_rad_ = std::atan2(-std::cos(angle_rad), std::sin(angle_rad));
//    double angle_deg_ = angle_rad * 180.0 / CV_PI;
//
//    std::cout << "Slope0: angle rad: " << angle_rad_ << " Slope angle deg: " << angle_deg_ << "\n";
//
//    // Calculate the intercept of the tangent line
//    double intercept = point_on_circle.y - slope * point_on_circle.x;
//
//    // Calculate the start and end points of the tangent line
//    int start_x = 0;
//    int start_y = static_cast<int>(slope * start_x + intercept);
//    int end_x = image.cols - 1;
//    int end_y = static_cast<int>(slope * end_x + intercept);
//
//    // Draw the circle on the image
//    cv::circle(image, center, radius, cv::Scalar(255, 255, 255), 2);
//
//    // Draw the point on the circle
//    cv::circle(image, point_on_circle, 3, cv::Scalar(0, 0, 255), cv::FILLED);
//
//    // Draw the tangent line on the image
//    cv::line(image, cv::Point(start_x, start_y), cv::Point(end_x, end_y), cv::Scalar(0, 255, 0), 2);
//
//    // Display the image
//    cv::imshow("Tangent Line", image);
//    std::cout << "Angle of the point for radius " << radius << ": " << angle_deg << " degrees" << std::endl;
//    cv::waitKey(500);
//
//    // Clean the canvas by setting it to black
//    image.setTo(cv::Scalar(0, 0, 0));
//
//    // Print the slope of the tangent line
//    std::cout << "Slope of the tangent line: " << slope << std::endl;
//
//    // Calculate the angle of the point with the same tangent slope for a different radius
//    int new_radius = 150;  // New radius value
//    double new_angle_rad = std::atan(-1.0 / slope);
//    double new_angle_deg = new_angle_rad * 180.0 / CV_PI;
//
//    std::cout << "Angle of the point for radius " << new_radius << ": " << new_angle_deg << " degrees" << std::endl;
//
//    // Calculate the updated point on the circle using the new radius but same angle
//    x = static_cast<int>(center.x + new_radius * std::cos(angle_rad));
//    y = static_cast<int>(center.y + new_radius * std::sin(angle_rad));
//    cv::Point point_on_circle1(x, y);
//
//    // Calculate the slope of the tangent line
//    slope = -std::cos(new_angle_rad) / std::sin(new_angle_rad);
//
//    angle_rad_ = std::atan2(-std::cos(angle_rad), std::sin(angle_rad));
//    angle_deg_ = angle_rad * 180.0 / CV_PI;
//
//    std::cout << "Slope1: angle rad: " << angle_rad_ << " Slope angle deg: " << angle_deg_ << "\n";
//
//    // Calculate the intercept of the tangent line
//    intercept = point_on_circle1.y - slope * point_on_circle1.x;
//
//    // Calculate the start and end points of the tangent line
//    start_x = 0;
//    start_y = static_cast<int>(slope * start_x + intercept);
//    end_x = image.cols - 1;
//    end_y = static_cast<int>(slope * end_x + intercept);
//
//    // Draw the circle on the image
//    cv::circle(image, center, new_radius, cv::Scalar(255, 255, 255), 2);
//
//    // Draw the point on the circle
//    cv::circle(image, point_on_circle1, 3, cv::Scalar(0, 0, 255), cv::FILLED);
//
//    // Draw the tangent line on the image
//    cv::line(image, cv::Point(start_x, start_y), cv::Point(end_x, end_y), cv::Scalar(0, 255, 0), 2);
//
//    // Display the image
//    cv::imshow("Tangent Line", image);
//    std::cout << "Slope of the tangent line: " << slope << std::endl;
//
//    cv::waitKey(5000);
//
//    return 0;
//}


    

    