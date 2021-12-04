#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

// troca os quadrantes da imagem da DFT
void deslocaDFT(Mat& image ){
    Mat tmp, A, B, C, D;
    
    // se a imagem tiver tamanho impar, recorta a regiao para
    // evitar cópias de tamanho desigual
    image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
    int cx = image.cols/2;
    int cy = image.rows/2;
    
    // reorganiza os quadrantes da transformada
    // A B   ->  D C
    // C D       B A
    A = image(Rect(0, 0, cx, cy));
    B = image(Rect(cx, 0, cx, cy));
    C = image(Rect(0, cy, cx, cy));
    D = image(Rect(cx, cy, cx, cy));
    
    // A <-> D
    A.copyTo(tmp);
    D.copyTo(A);
    tmp.copyTo(D);
    
    // C <-> B
    C.copyTo(tmp);
    B.copyTo(C);
    tmp.copyTo(B);
}

int sliderMax = 100;
int ghSlider = 10, glSlider = 10, dSlider = 10, cSlider = 10;

int dft_M, dft_N;
cv::Mat filter, tmp;

char TrackbarName[50];

void on_trackbar_height(int, void*){
    
    for(int i=0; i<dft_M; i++) {
        for(int j=0; j<dft_N; j++) {
            double aux = cSlider * (pow(i - dft_M / 2, 2) + pow(j - dft_N / 2, 2));
            tmp.at<float> (i,j) = (ghSlider - glSlider) * (1 - exp(-aux / pow(dSlider, 2))) + glSlider;
        }
    }
    
    cv::Mat comps[] = { tmp, tmp };
    cv::merge(comps, 2, filter);
}

int main(int , char**) {
    cv::VideoCapture cap;
    cv::Mat complexImage, multsp;
    cv::Mat padded;
    cv::Mat image, imagegray;
    cv::Mat_<float> realInput, zeros;
    std::vector<Mat> planos;
    
    // guarda tecla capturada
    char key;
    
    // abre a câmera default
    cap.open(0);
    if(!cap.isOpened()) return -1;
    
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    
    // captura uma imagem para recuperar as
    // informacoes de gravação
    cap >> image;
    
    // identifica os tamanhos otimos para
    // calculo do FFT
    dft_M = getOptimalDFTSize(image.rows);
    dft_N = getOptimalDFTSize(image.cols);
    
    // realiza o padding da imagem
    copyMakeBorder(image, padded, 0,
                   dft_M - image.rows, 0,
                   dft_N - image.cols,
                   BORDER_CONSTANT, Scalar::all(0));
    
    // parte imaginaria da matriz complexa (preenchida com zeros)
    zeros = Mat_<float>::zeros(padded.size());
    
    // prepara a matriz complexa para ser preenchida
    complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));
    
    // a função de transferência (filtro frequencial) deve ter o
    // mesmo tamanho e tipo da matriz complexa
    filter = complexImage.clone();
    
    // cria uma matriz temporária para criar as componentes real
    // e imaginaria do filtro ideal
    tmp = Mat(dft_M, dft_N, CV_32F);
    
    namedWindow("filtrada", 1);
    
    sprintf(TrackbarName, "gh %d", sliderMax);
    createTrackbar(TrackbarName, "filtrada",
                   &ghSlider,
                   sliderMax,
                   on_trackbar_height);
    
    sprintf(TrackbarName, "gl %d", sliderMax);
    createTrackbar(TrackbarName, "filtrada",
                   &glSlider,
                   sliderMax,
                   on_trackbar_height);
    
    sprintf(TrackbarName, "d %d", sliderMax);
    createTrackbar(TrackbarName, "filtrada",
                   &dSlider,
                   sliderMax,
                   on_trackbar_height);
    
    sprintf(TrackbarName, "c %d", sliderMax);
    createTrackbar(TrackbarName, "filtrada",
                   &cSlider,
                   sliderMax,
                   on_trackbar_height);
    
    
    for(;;){
        cap >> image;
        cv::cvtColor(image, imagegray, cv::COLOR_BGR2GRAY);
        cv::imshow("original", imagegray);
        
        // realiza o padding da imagem
        cv::copyMakeBorder(imagegray, padded, 0,
                           dft_M - image.rows, 0,
                           dft_N - image.cols,
                           BORDER_CONSTANT, Scalar::all(0));
        
        // limpa o array de matrizes que vao compor a
        // imagem complexa
        planos.clear();
        // cria a compoente real
        realInput = Mat_<float>(padded);
        
        //Aplica logaritmo na imagem
        for(int i=0; i<dft_M; i++) {
            for(int j=0; j<dft_N; j++) {
                realInput.at<float> (i,j) = log(1 + realInput.at<float> (i,j));
            }
        }
        
        // insere as duas componentes no array de matrizes
        planos.push_back(realInput);
        planos.push_back(zeros);
        
        // combina o array de matrizes em uma unica componente complexa
        cv::merge(planos, complexImage);
        
        // calcula o dft
        cv::dft(complexImage, complexImage);
        
        // realiza a troca de quadrantes
        deslocaDFT(complexImage);
        
        // aplica o filtro frequencial
        cv::mulSpectrums(complexImage,filter,complexImage,0);
        
        // troca novamente os quadrantes
        deslocaDFT(complexImage);
        
        // calcula a DFT inversa
        cv::idft(complexImage, complexImage);
        
        // limpa o array de planos
        planos.clear();
        
        // separa as partes real e imaginaria da
        // imagem filtrada
        cv::split(complexImage, planos);
        
        // normaliza a parte real para exibicao
        cv::normalize(planos[0], planos[0], 0, 1, cv::NORM_MINMAX);
        
        //Aplica exponencial à imagem
        for(int i=0; i<dft_M; i++) {
            for(int j=0; j<dft_N; j++) {
                planos[0].at<float> (i,j) = exp(planos[0].at<float> (i,j));
            }
        }
        
        cv::normalize(planos[0], planos[0], 0, 1, cv::NORM_MINMAX);
        
        cv::imshow("filtrada", planos[0]);
        
        key = (char) waitKey(10);
        if( key == 27 ) break; // esc pressed!
    }
    return 0;
}
