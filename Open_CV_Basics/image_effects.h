#ifndef IMAGE_EFFECTS_H
#define IMAGE_EFFECTS_H

#include <opencv2/core.hpp>

void vDoInvertColors(cv::Mat frame, int rows, int cols);
void vDoBinarizeImage(cv::Mat frame, int img_threshold, int rows, int cols);
void vMirrorImage(cv::Mat frame, int rows, int cols);
void vFlipImage(cv::Mat frame, int rows, int cols);

#endif
