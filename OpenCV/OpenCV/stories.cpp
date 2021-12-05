#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void printmask(cv::Mat &m) {
    for (int i = 0; i < m.size().height; i++) {
        for (int j = 0; j < m.size().width; j++) {
            std::cout << m.at<float>(i, j) << ",";
        }
        std::cout << "\n";
    }
}

int getUpdatedFilterIndex(int maxValue, int currentValue, bool isIncrementing) {
    
    int newValue = currentValue;
    
    if(isIncrementing) {
        newValue = newValue + 1;
        if(newValue >= maxValue) {
            newValue = -1;
        }
    } else {
        newValue = newValue - 1;
        if(newValue < -1) {
            newValue = maxValue-1;
        }
    }
    
    return newValue;
}

string getTitle(char currentMode) {
    
    switch(currentMode) {
        case 'f':
            return "Aplicando filtros";
        case 't':
            return "Aplicando texto";
        default:
            return "";
    }
}

int main(int, char **) {
    cv::VideoCapture cap;  // open the default camera
    
    cv::Mat sepia = (cv::Mat_<float>(3, 3) <<
                      0.272, 0.534, 0.131,
                      0.349, 0.686, 0.168,
                      0.393, 0.769, 0.189);
    cv::Mat media = (cv::Mat_<float>(3, 3) <<
                     0.1111, 0.1111, 0.1111,
                     0.1111, 0.1111, 0.1111,
                     0.1111, 0.1111, 0.1111);
    cv::Mat gauss = (cv::Mat_<float>(3, 3) <<
                     0.0625, 0.125, 0.0625,
                     0.125, 0.25, 0.125,
                     0.0625, 0.125,  0.0625);
    cv::Mat horizontal = (cv::Mat_<float>(3, 3) <<
                            -1, 0, 1,
                            -2, 0, 2,
                            -1, 0, 1);
    cv::Mat laplacian = (cv::Mat_<float>(3, 3) <<
                         0, -1, 0,
                         -1, 4, -1,
                         0, -1, 0);
    
    int maxFilters = 5;
    int filtersIndex = -1;
    Mat filters[5] = {sepia, media, gauss, horizontal, laplacian};
    
    char currentMode = 'f';
    string userText = "";
    
    cv::Mat frame, framegray;
    cv::Mat result;
    double width, height;
    char key;
    
    string imgPath = "Growlithe.png";
    cout << "Por favor, digite o nome do arquivo: ";
    cin >> imgPath;
    
    Mat img = imread(imgPath, cv::IMREAD_COLOR);
    
    cv::namedWindow("filtroespacial", cv::WINDOW_NORMAL);
    cv::namedWindow("original", cv::WINDOW_NORMAL);
    
    for (;;) {
        cv::cvtColor(img, framegray, cv::IMREAD_COLOR);
//        cv::flip(framegray, framegray, 1);
        cv::imshow("original", framegray);
        
        framegray.convertTo(result, CV_8U);
        
        Mat currentFilter;
        
        string title = getTitle(currentMode);
        
        if(filtersIndex >= 0) {
            currentFilter = filters[filtersIndex];
            
            cv::transform(img, result, currentFilter);
//            cv::flip(result, result, 1);
//            cv::putText(result, title, cv::Point(10, 30), cv::QT_FONT_NORMAL, 1, Scalar(255, 255, 255), 2);
            cv::putText(result, userText, cv::Point(10, 460), cv::QT_FONT_NORMAL, 1, Scalar(255, 255, 255), 2);
            cv::imshow("filtroespacial", result);
        } else {
//            cv::putText(framegray, title, cv::Point(10, 30), cv::QT_FONT_NORMAL, 1, Scalar(255, 255, 255), 2);
            cv::putText(framegray, userText, cv::Point(10, 460), cv::QT_FONT_NORMAL, 1, Scalar(255, 255, 255), 2);
            cv::imshow("filtroespacial", framegray);
        }
        
        key = (char)cv::waitKey(10);
        if (key == 27) break;
        
        switch (key) {
            case 'f':
                if(currentMode != 't') {
                    currentMode = 'f';
                }
                break;
            case 't':
                currentMode = 't';
                cout << "Por favor, digite o texto desejado: ";
                cin >> userText;
                currentMode = 'f';
                break;
            case 's':
                if(currentMode != 't') {
                    currentMode = 's';
                }
                break;
            default:
                break;
        }
        
        switch(currentMode) {
            case 'f':
                switch (key) {
                    case 'a':
                        filtersIndex = getUpdatedFilterIndex(maxFilters, filtersIndex, false);
                        break;
                    case 'd':
                        filtersIndex = getUpdatedFilterIndex(maxFilters, filtersIndex, true);
                        break;
                    default:
                        break;
                }
                break;
            case 't':
                break;
            case 's':
                string name = "";
                cout << "Por favor, digite o nome do arquivo: ";
                cin >> name;
                imwrite(name + ".jpg", result);
                return 0;
        }
    }
    return 0;
}
