#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>

int tamanhoRegiao, decaimento, centro = 0;
int regiaoSlider = 0, decaimentoSlider = 0, centroSlider = 0;

double alfa, firstLine, secondLine;

int sliderMax = 100;
int yMax;

cv::Mat image1, image2, result, image32f, imageFiltered;

char TrackbarName[50];

void on_track_regiao(int, void*) {
    // Calculo do centro da imagem desejado
    tamanhoRegiao = (regiaoSlider * yMax) / sliderMax;
    
    // Para calcular as linhas, pegamos a metade da altura da imagem, ou seja o centro da image,
    // e subtraimos do centro para pegar a linha de cima, e adicionamos o centro para pegar a linha de baixo.
    firstLine = centro - tamanhoRegiao/2;
    secondLine = centro + tamanhoRegiao/2;
    
    for(int i = 0; i < result.size().height; i++) {
        // Utilizada a função do tutorial para definir o alfa
        alfa = 0.5 * (tanh((i - firstLine) / decaimento) - tanh((i - secondLine) / decaimento));
        cv::addWeighted(image1.row(i), alfa, result.row(i), 1.0 - alfa, 0.0, image2.row(i));
    }
    
    imshow("tiltshift", image2);
    imwrite("tiltshift.png", image2);
}

void on_track_decaimento(int, void*) {
    decaimento = decaimentoSlider;
    on_track_regiao(regiaoSlider, 0);
}


void on_track_centro(int, void*) {
    centro = (centroSlider * yMax) / sliderMax;
    on_track_regiao(regiaoSlider, 0);
}

int main(int argvc, char** argv) {
    image1 = cv::imread("Growlithe.png");
    image2 = image1.clone();
   
    cv::namedWindow("tiltshift", 1);
    
    yMax = image1.size().height;
    
    // Modificando a imagem para ficar visível o efeito
    float media[] = {1,1,1,
                    1,1,1,
                    1,1,1};
    
    cv::Mat mask = cv::Mat(3, 3, CV_32F, media);
    
    image1.convertTo(image32f, CV_32F);
    
    filter2D(image32f, imageFiltered, image32f.depth(), mask, cv::Point(2,2), 0);
    
    // Guarda imagem modificada na var result
    imageFiltered.convertTo(result, CV_8U);
    
    std::sprintf( TrackbarName, "Regiao %d", sliderMax);
    cv::createTrackbar( TrackbarName, "tiltshift",
                       &regiaoSlider,
                       sliderMax,
                       on_track_regiao);
    on_track_regiao(regiaoSlider, 0);
    
    std::sprintf( TrackbarName, "Decaimento %d", sliderMax);
    cv::createTrackbar( TrackbarName, "tiltshift",
                       &decaimentoSlider,
                       sliderMax,
                       on_track_decaimento);
    on_track_decaimento(decaimentoSlider, 0);
    
    std::sprintf( TrackbarName, "Centro %d", sliderMax);
    cv::createTrackbar( TrackbarName, "tiltshift",
                       &centroSlider,
                       sliderMax,
                       on_track_centro);
    on_track_centro(centroSlider, 0);
    
    cv::waitKey(0);
    return 0;
}
