#ifndef IMAGE_EFFECTS_H
#define IMAGE_EFFECTS_H

#include <opencv2/core.hpp>

void vDoInvertColors(cv::Mat frame, int rows, int cols);
void vDoBinarizeImage(cv::Mat frame, int img_threshold, int rows, int cols);
void vDoMirrorImage(cv::Mat frame, int rows, int cols);
void vDoFlipImage(cv::Mat frame, int rows, int cols);
void vDoSobelEdgeDetection(const cv::Mat& frame);
cv::Mat matDoConvertToGrayscale(const cv::Mat& frame);
cv::Mat matDoCalculateAbsoluteDifference(const cv::Mat& frame1, const cv::Mat& frame2);
cv::Mat matDoGeneratePixelatedImage(const cv::Mat& inputImage, int pixelSize);



#endif
