#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argvc, char** argv) {
    cv::Mat image1, image2, result, image32f, imageFiltered;

    // Abrindo o vídeo original
    VideoCapture inputVideo("SunsetTimelapse.mp4");
    if (!inputVideo.isOpened()) {
        cout  << "Não conseguiu abrir o vídeo";
        return -1;
    }
    
    Size videoSize = Size((int) inputVideo.get(CAP_PROP_FRAME_WIDTH),
                          (int) inputVideo.get(CAP_PROP_FRAME_HEIGHT));
    
    double alfa;

    // Região escolhida foi 25% da altura do vídeo
    double tamanhoRegiao = 0.25 * videoSize.height;
    // Decaimento escolhido foi de valor 5
    double decaimento = 5;
    // Centro escolhido foi realmente o centro do vídeo
    double centro = 0.5 * videoSize.height;
    
    // Para calcular as linhas, pegamos a metade da altura da imagem, ou seja o centro da imagem,
    // e subtraimos do centro para pegar a linha de cima, e adicionamos o centro para pegar a linha de baixo.
    double linha1 = centro - tamanhoRegiao/2;
    double linha2 = centro + tamanhoRegiao/2;
    
    // Criando o arquivo de saída
    VideoWriter outputVideo;
    int ex = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));
    outputVideo.open("SunsetTimelapseSaida.mp4", ex, inputVideo.get(CAP_PROP_FPS), videoSize, true);
    
    if (!outputVideo.isOpened()) {
        cout  << "Não foi possível criar o arquivo de saída";
        return -1;
    }
    
    while(true) {
        inputVideo >> image1;
        
        // Verifica se é o final do vídeo
        if (image1.empty()) break;

        image2 = image1.clone();

        // Modificando a imagem para ficar visível o efeito
        float media[] = {1,1,1,
                        1,1,1,
                        1,1,1};
        
        cv::Mat mask = cv::Mat(3, 3, CV_32F, media);
        
        image1.convertTo(image32f, CV_32F);
        
        filter2D(image32f, imageFiltered, image32f.depth(), mask, cv::Point(2,2), 0);

        // Guarda imagem modificada na var result
        imageFiltered.convertTo(result, CV_8U);

        for(int i = 0; i < result.size().height; i++) {
            alfa = 0.5 * (tanh((i - linha1) / decaimento) - tanh((i - linha2) / decaimento));
            addWeighted(image1.row(i), alfa, result.row(i), 1.0 - alfa, 0.0, image2.row(i));
        }

        outputVideo << image2;
    }
    
    return 0;
}
