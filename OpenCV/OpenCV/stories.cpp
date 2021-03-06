#include <iostream>
#include <opencv2/opencv.hpp>

// Redimensionar sticker

using namespace cv;
using namespace std;

int filterSliderMax = 5;
int filterSlider = 0;

int textXSliderMax = 430;
int textYSliderMax = 460;

int textXSlider = 10;
int textYSlider = 460;

int stickerXSliderMax = 430;
int stickerYSliderMax = 460;
int stickerSliderMax = 2;

int stickerXSlider = 0;
int stickerYSlider = 0;
int stickerSlider = 0;

int stickerSize = 200;

char TrackbarName[50];

double fontSize = 455;
string userText = "";

cv::Mat applySticker(cv::Mat refImage) {
    if(stickerSlider == 0) { return refImage; }
    string stickers[2] = { "sticker1.png", "sticker2.png" };
    Mat stickerImage = imread("stickers/" + stickers[stickerSlider-1], cv::IMREAD_ANYCOLOR);
    
    cv::resize(stickerImage, stickerImage, cv::Size(stickerSize, stickerSize), 0, 0, cv::INTER_LINEAR);
    
    stickerImage.copyTo(refImage(cv::Rect(stickerXSlider, stickerYSlider, stickerImage.cols, stickerImage.rows)));
    
    return refImage;
}

cv::Mat applyFilter(cv::Mat refImage) {
    if(filterSlider == 0) { return refImage; }
    
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
    
    Mat filters[5] = {sepia, media, gauss, horizontal, laplacian};
    
    cv::Mat currentFilter = filters[filterSlider-1];
    
    cv::transform(refImage, refImage, currentFilter);
    
    return refImage;
}

void createTrackbars() {
    sprintf(TrackbarName, "Text X %d", textXSliderMax);
    createTrackbar(TrackbarName, "stories",
                   &textXSlider,
                   textXSliderMax);
    
    sprintf(TrackbarName, "Text Y %d", textYSliderMax);
    createTrackbar(TrackbarName, "stories",
                   &textYSlider,
                   textYSliderMax);
    
    sprintf(TrackbarName, "Sticker X %d", stickerXSliderMax);
    createTrackbar(TrackbarName, "stories",
                   &stickerXSlider,
                   stickerXSliderMax);
    
    sprintf(TrackbarName, "Sticker Y %d", stickerYSliderMax);
    createTrackbar(TrackbarName, "stories",
                   &stickerYSlider,
                   stickerYSliderMax);
    
    sprintf(TrackbarName, "Sticker %d", stickerSliderMax);
    createTrackbar(TrackbarName, "stories",
                   &stickerSlider,
                   stickerSliderMax);
    
    sprintf(TrackbarName, "Filter %d", filterSliderMax);
    createTrackbar(TrackbarName, "stories",
                   &filterSlider,
                   filterSliderMax);
}

int saveVideo(VideoCapture video, string name) {
    
    cv::Mat img, result;

    video.set(CAP_PROP_POS_FRAMES, 0);
    
    VideoWriter outputVideo;
    
    Size videoSize = Size((int) video.get(CAP_PROP_FRAME_WIDTH),
                          (int) video.get(CAP_PROP_FRAME_HEIGHT));
    
    int ex = static_cast<int>(video.get(CAP_PROP_FOURCC));
    outputVideo.open(name + ".mp4", ex, video.get(CAP_PROP_FPS), videoSize);

    int frame_counter = 0;
    int videoFrames = video.get(CAP_PROP_FRAME_COUNT);
    
    while(frame_counter < videoFrames) {
        video >> img;

        img.convertTo(result, CV_8U);
        
        // Aplica filtro
        result = applyFilter(result);
        // Aplica texto
        cv::putText(result, userText, cv::Point(textXSlider, textYSlider), cv::QT_FONT_NORMAL, fontSize, Scalar(255, 255, 255), 2);
        // Aplica sticker
        result = applySticker(result);
        
        outputVideo.write(result);
        
        frame_counter += 1;
        video.set(CAP_PROP_POS_FRAMES, frame_counter);
        cout << "Saving: " << (double)frame_counter/(double)videoFrames*100.0 << "%\n";
    }
    
    return 0;
}

int main(int, char **) {

    string fileType = "f";
    string filePath = "Growlithe.png";
    
    char currentMode = 'n';
    
    
    cv::Mat img;
    VideoCapture inputVideo("SunsetTimelapse.mp4");
    
    cv::Mat framegray, result;
    char key;
    
    cout << "Gostaria de abrir uma foto ou v??deo? [f/v] ";
    cin >> fileType;
    
    
    cout << "Por favor, digite o nome do arquivo: ";
    cin >> filePath;
    
    if(fileType == "f") {
        img = imread(filePath, cv::IMREAD_COLOR);
        
        textXSliderMax = img.size().width - 30;
        textYSliderMax = img.size().height - 20;
        textYSlider = textYSliderMax;
        fontSize = textYSliderMax / fontSize;
        
        stickerXSliderMax = img.size().width - stickerSize;
        stickerYSliderMax = img.size().height - stickerSize;
    } else {
        VideoCapture inputVideo(filePath);
        
        Size videoSize = Size((int) inputVideo.get(CAP_PROP_FRAME_WIDTH),
                              (int) inputVideo.get(CAP_PROP_FRAME_HEIGHT));
        
        textXSliderMax = videoSize.width - 30;
        textYSliderMax = videoSize.height - 20;
        textYSlider = textYSliderMax;
        fontSize = textYSliderMax / fontSize;
        
        stickerXSliderMax = videoSize.width - stickerSize;
        stickerYSliderMax = videoSize.height - stickerSize;
    }
    
    cv::namedWindow("stories", cv::WINDOW_NORMAL);
    
    createTrackbars();
    
    int frame_counter = 0;
    
    for (;;) {
        if(fileType == "v") {
            frame_counter += 1;
            if(frame_counter == inputVideo.get(CAP_PROP_FRAME_COUNT)) {
                frame_counter = 0;
                inputVideo.set(CAP_PROP_POS_FRAMES, frame_counter);
            }
            inputVideo >> img;
        }

        img.convertTo(result, CV_8U);
        
        // Aplica filtro
        result = applyFilter(result);
        // Aplica texto
        cv::putText(result, userText, cv::Point(textXSlider, textYSlider), cv::QT_FONT_NORMAL, fontSize, Scalar(255, 255, 255), 2);
        // Aplica sticker
        result = applySticker(result);
        
        cv::imshow("stories", result);
        
        key = (char)cv::waitKey(10);
        if (key == 27) break;
        
        switch (key) {
            case 't':
                currentMode = 't';
                cout << "Por favor, digite o texto desejado: ";
                cin >> userText;
                currentMode = 'n';
                break;
            case 's':
                if(currentMode != 't') {
                    string name = "";
                    cout << "Por favor, digite o nome do arquivo: ";
                    cin >> name;
                    
                    if(fileType == "f") {
                        imwrite(name + ".jpg", result);
                    } else {
                        saveVideo(inputVideo, name);
                    }
                    
                    return 0;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}
