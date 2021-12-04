//
//  regions.cpp
//  OpenCV
//
//  Created by Juan Collin on 20/09/21.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
    cv::Mat image;
    cv::Vec3b val;
    
    string imgPath = "Growlithe.png";
    
    // Bons valores 100 | 200 | 250 | 350
    int p1x, p1y, p2x, p2y;
    cout << "Por favor, digite o x do primeiro ponto: ";
    cin >> p1x;
    cout << "Por favor, digite o y do primeiro ponto: ";
    cin >> p1y;
    cout << "Por favor, digite o x do segundo ponto: ";
    cin >> p2x;
    cout << "Por favor, digite o y do segundo ponto: ";
    cin >> p2y;
    
    // Lê a imagem
    image= cv::imread(imgPath,cv::IMREAD_GRAYSCALE);
    
    if(!image.data)
        std::cout << "nao abriu growlithe.png" << std::endl;
    
    cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);
    
    // Percorre os pontos passados pelo usuário
    for(int i=p1x;i<p2x;i++){
        for(int j=p1y;j<p2y;j++){
            // Subtrai 255 pela cor da posição para obter o seu tom negativo
            image.at<uchar>(i,j)= 255 - image.at<uchar>(i,j);
        }
    }
    
    cv::imshow("janela", image);
    cv::waitKey();
    
    return 0;
}
