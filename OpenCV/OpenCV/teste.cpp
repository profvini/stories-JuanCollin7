//
//  teste.cpp
//  OpenCV
//
//  Created by Poatek on 08/12/21.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    Mat bigImage = imread("MarioGalaxy.jpg", cv::IMREAD_ANYCOLOR);
    Mat lilImage = imread("Growlithe.png", cv::IMREAD_ANYCOLOR);

    cv::resize(lilImage, lilImage, cv::Size(lilImage.cols * 0.5, lilImage.rows * 0.5), 0, 0, cv::INTER_LINEAR);
    
    lilImage.copyTo(bigImage(cv::Rect(0, 0, lilImage.cols, lilImage.rows)));
    
    imshow("Overlay Image", bigImage);

    cv::waitKey();
    
    return 0;
}
