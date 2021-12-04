#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
    cv::Mat image, equalizedImage;
    int width, height;
    cv::VideoCapture cap;
    int key;
    
    cap.open(0);
    
    if(!cap.isOpened()){
        std::cout << "cameras indisponiveis";
        return -1;
    }
    
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    
    while(1){
        cap >> image;
        
        cvtColor(image, image, cv::COLOR_BGR2GRAY);
        equalizeHist(image, equalizedImage);

        cv::imshow("image", image);
        cv::imshow("equalized image", equalizedImage);
        
        key = cv::waitKey(30);
        if(key == 27) break;
    }
    return 0;
}
