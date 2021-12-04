//
//  trocaregioes.cpp
//  OpenCV
//
//  Created by Juan Collin on 20/09/21.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Struct para simbolizar uma coordenada
struct POINT {
    float x;
    float y;
};

// Struct para representar um quadrante
struct QUADRANT {
    POINT firstPoint;
    POINT secondPoint;
};

// Função que modifica a imagem, desenhando o quadrante Q1 na posição do quadrante Q2.
// Recebe a imagem de referencia, a imagem modificada e dois quadrantes.
// Retorna a imagem modificada.
cv::Mat modifyImage(cv::Mat refImage, cv::Mat modifiedImage,
                     QUADRANT firstQ, QUADRANT secondQ) {
    
    // Referencia dos pontos do segundo quadrante
    float firstX = secondQ.firstPoint.x;
    float firstY = secondQ.firstPoint.y;
    
    // Percorre todas as coordenadas de Q1 e preenche nas respectivas coordenadas de Q2
    for(int i= firstQ.firstPoint.x; i < firstQ.secondPoint.x; i++) {
        for(int j= firstQ.firstPoint.y; j < firstQ.secondPoint.y; j++) {
            // Modifica o Q2 com o respectivo pixel de Q1.
            modifiedImage.at<uchar>(firstX,firstY) = refImage.at<uchar>(i,j);
            // Incrementa o Y do segundo quadrante para acompanhar o primeiro.
            firstY++;
        }
        // Incrementa o X e zera o Y do segundo quadrante para acompanhar o primeiro.
        firstX++;
        firstY = secondQ.firstPoint.y;
    }
    
    return modifiedImage;
}

int main(int, char**) {
    cv::Mat image;
    cv::Mat modifiedImage;
    cv::Vec3b val;
    
    string imgPath = "Growlithe.png";
    
    // Cria duas imagens e duas janelas
    image= cv::imread(imgPath,cv::IMREAD_GRAYSCALE);
    modifiedImage= cv::imread(imgPath,cv::IMREAD_GRAYSCALE);
    
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Modificada", cv::WINDOW_AUTOSIZE);
    
    // Recebe as dimensões da imagens
    float imgHeight = image.size().height;
    float imgWidth = image.size().width;

    // Cria os quatros quadrantes com base nas dimensões da imagem
    // q1 - q2
    // q3 - q4
    struct QUADRANT q1 = { POINT{0.0, 0.0}, POINT{imgHeight/2, imgWidth/2} };
    struct QUADRANT q2 = { POINT{0.0, imgWidth/2}, POINT{imgHeight/2, imgWidth} };
    struct QUADRANT q3 = { POINT{imgHeight/2, 0.0}, POINT{imgHeight, imgWidth/2} };
    struct QUADRANT q4 = { POINT{imgHeight/2, imgWidth/2}, POINT{imgHeight, imgWidth} };

    // Chama 4 vezes a função de modificar a imagem, invertendo assim os 4 quadrantes em diagonal
    modifiedImage = modifyImage(image, modifiedImage, q1, q4);
    modifiedImage = modifyImage(image, modifiedImage, q4, q1);
    modifiedImage = modifyImage(image, modifiedImage, q2, q3);
    modifiedImage = modifyImage(image, modifiedImage, q3, q2);
    
    // Mostra a imagem original e a modificada
    cv::imshow("Original", image);
    cv::imshow("Modificada", modifiedImage);
    cv::waitKey();
    
    return 0;
}
