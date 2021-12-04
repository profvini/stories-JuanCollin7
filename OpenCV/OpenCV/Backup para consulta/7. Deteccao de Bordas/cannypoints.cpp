#include <iostream>
#include <opencv2/opencv.hpp>

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

int top_slider = 10;
int top_slider_max = 200;

int step_slider = 5;
int step_max = 10;

int jitter_slider = 3;
int jitter_max = 10;

int raio_slider = 3;
int raio_max = 6;


char TrackbarName[50];
Mat points;
Mat image, border;

void applyPontilhismo() {
    int width, height, gray;
    int x, y;
    
    width = image.size().width;
    height = image.size().height;
    
    vector<int> yrange;
    vector<int> xrange;
    
    // Valor de mínimo 1 para raio, step e jitter
    if(raio_slider < 1) { raio_slider = 1; }
    if(step_slider < 1) { step_slider = 1; }
    if(jitter_slider < 1) { jitter_slider = 1; }
    
    xrange.resize(height/step_slider);
    yrange.resize(width/step_slider);
    
    iota(xrange.begin(), xrange.end(), 0);
    iota(yrange.begin(), yrange.end(), 0);
    
    for(uint i=0; i<xrange.size(); i++){
        xrange[i]= xrange[i]*step_slider+step_slider/2;
    }
    
    for(uint i=0; i<yrange.size(); i++){
        yrange[i]= yrange[i]*step_slider+step_slider/2;
    }
    
    points = Mat(height, width, CV_8U, Scalar(255));
    
    random_shuffle(xrange.begin(), xrange.end());
    
    for(auto i : xrange){
        random_shuffle(yrange.begin(), yrange.end());
        for(auto j : yrange){
            
            x = i+rand()%(2*jitter_slider)-jitter_slider+1;
            y = j+rand()%(2*jitter_slider)-jitter_slider+1;
            gray = image.at<uchar>(x,y);
            
            circle(points,
                   cv::Point(y,x),
                   raio_slider,
                   CV_RGB(gray,gray,gray),
                   -1,
                   cv::LINE_AA);
        }
    }
    
    imshow("cannyPoints", points);
}

void on_trackbar_canny(int, void*){
    Canny(image, border, top_slider, 3 * top_slider);
    applyPontilhismo();
}

int main(int argc, char**argv) {
    int width, height;
    
    string imgPath = "Growlithe.png";
    
    image = imread(imgPath, cv::IMREAD_GRAYSCALE);
    
    width = image.size().width;
    height = image.size().height;
    
    namedWindow("cannyPoints", 1);
    
    sprintf(TrackbarName, "Threshold %d", top_slider_max);
    createTrackbar(TrackbarName, "cannyPoints",
                   &top_slider,
                   top_slider_max,
                   on_trackbar_canny);
    
    sprintf(TrackbarName, "STEP %d", step_max);
    createTrackbar(TrackbarName, "cannyPoints",
                   &step_slider,
                   step_max,
                   on_trackbar_canny);
    
    sprintf(TrackbarName, "JITTER %d", jitter_max);
    createTrackbar(TrackbarName, "cannyPoints",
                   &jitter_slider,
                   jitter_max,
                   on_trackbar_canny);
    
    sprintf(TrackbarName, "RAIO %d", raio_max);
    createTrackbar(TrackbarName, "cannyPoints",
                   &raio_slider,
                   raio_max,
                   on_trackbar_canny);
    
    
    on_trackbar_canny(top_slider, 0);
    
    imwrite("cannyPoints.jpg", points);
    
    waitKey();
    return 0;
}
