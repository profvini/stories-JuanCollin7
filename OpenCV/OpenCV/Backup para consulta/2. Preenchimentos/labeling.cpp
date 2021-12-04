#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
    cv::Mat image, realce;
    int width, height;
    int nobjects, nobjectsBuraco;
    
    std::map<std::string, std::string> usedColors;
    
    Vec3b whiteColor(255,255,255);
    Vec3b redColor(0,0,255);
    Vec3b greenColor(0,255,0);
    Vec3b bgColor(100,100,100);
    Vec3b black(0,0,0);
    
    cv::Point p;
    
    string imgPath = "bolhas2.png";
    
    // Cria duas imagens e duas janelas
    image = cv::imread(imgPath,cv::IMREAD_COLOR);
    
    if(!image.data){
        std::cout << "imagem nao carregou corretamente\n";
        return(-1);
    }
    
    width=image.cols;
    height=image.rows;
    
    // Remove bolhas que tocam a borda superior
    for(int j=0; j<width; j++){
        if(image.at<Vec3b>(0,j) == whiteColor) {
            p.x=j;
            p.y=0;
            floodFill(image,p,Scalar(0,0,0));
        }
    }
    
    // Remove bolhas que tocam a borda lateral direita
    for(int i=0; i<height; i++){
        if(image.at<Vec3b>(i,width-1) == whiteColor){
            p.x=width-1;
            p.y=i;
            floodFill(image,p,Scalar(0,0,0));
        }
    }
    
    // Remove bolhas que tocam a borda inferior
    for(int j=0; j<width; j++){
        if(image.at<Vec3b>(height-1,j) == whiteColor){
            p.x=j;
            p.y=height-1;
            floodFill(image,p,Scalar(0,0,0));
        }
    }
    
    // Remove bolhas que tocam a borda lateral esquerda
    for(int i=0; i<height; i++){
        if(image.at<Vec3b>(i,0) == whiteColor){
            p.x=0;
            p.y=i;
            floodFill(image,p,Scalar(0,0,0));
        }
    }

    // Troca cor do fundo para diferenciar da cor interna das bolhas
    p.x=0; p.y=0;
    floodFill(image,p,bgColor);
    
    p.x=0;
    p.y=0;
    
    nobjects = 0 ;
    nobjectsBuraco = 0;
    
    // identificando bolhas e pintando com cores diferentes
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            // Cor do ponto atual
            Vec3b pointColor = image.at<Vec3b>(i,j);
            // Cor do ponto anterior
            Vec3b previousColor = image.at<Vec3b>(i,j-1);
            
            p.x=j;
            p.y=i;
            
            // Achou uma bolha
            if(pointColor == whiteColor) {
                // Incrementa objeto
                nobjects++;
                
                // Pinta a borda da bolha com a cor verde
                cv::floodFill(image,p,greenColor);
                
            } else if(pointColor == black && previousColor == greenColor) { // Achou um buraco
                // Diminui o numero de objetos
                nobjects--;
                // Incrementa numero de objetos com buraco
                nobjectsBuraco++;

                // Pinta o buraco com a cor do bg
                floodFill(image,p,bgColor);
                
                p.x = j-1;
                p.y = i;
                
                // Pinta a borda com a cor vermelha
                floodFill(image,p,redColor);
            } else if(pointColor == black) {
                // Segundo ou outro buraco de uma bolha que já foi computada com buraco,
                // ou seja, só pinta este buraco com a cor do background
                floodFill(image,p,bgColor);
            }
            
            // Ps.: Para os casos com dois buracos, o algoritmo só irá ignorar, pois para definir como uma bolha com buraco,
            // ela checa se no pixel anterior ao buraco temos uma borda verde, porém ao passar pelo primeiro buraco, ela será pintada de vermelha
            // Sendo assim, este buraco será ignorado.
        }
    }
    
    std::cout << "a figura tem " << nobjects << " bolhas sem buraco\n";
    std::cout << "a figura tem " << nobjectsBuraco << " bolhas com buraco\n";
    
    cv::imshow("image", image);
    cv::imwrite("labeling.png", image);
    
    cv::waitKey();
    
    return 0;
}
