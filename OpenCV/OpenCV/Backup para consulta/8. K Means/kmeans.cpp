#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
    int nClusters = 6;
    Mat rotulos;
    int nRodadas = 1;
    Mat centros;
    
    if(argc!=3){
        exit(0);
    }
    
    string imgPath = "sushi.jpg";
    
    Mat img = imread(imgPath, cv::IMREAD_COLOR);
    
    Mat samples(img.rows * img.cols, 3, CV_32F);
    
    for( int y = 0; y < img.rows; y++ ){
        for( int x = 0; x < img.cols; x++ ){
            for( int z = 0; z < 3; z++){
                samples.at<float>(y + x*img.rows, z) = img.at<Vec3b>(y,x)[z];
            }
        }
    }
    
    srand(time(NULL));
    cv::setRNGSeed(rand());
    
    kmeans(samples,
           nClusters,
           rotulos,
           TermCriteria(cv::TermCriteria::MAX_ITER|cv::TermCriteria::EPS, 10000, 0.0001),
           nRodadas,
           cv::KMEANS_RANDOM_CENTERS,
           centros );
    
    cout << "Centros: " << centros;
    
    Mat rotulada( img.size(), img.type() );
    for( int y = 0; y < img.rows; y++ ){
        for( int x = 0; x < img.cols; x++ ){
            int indice = rotulos.at<int>(y + x*img.rows,0);
            rotulada.at<Vec3b>(y,x)[0] = (uchar) centros.at<float>(indice, 0);
            rotulada.at<Vec3b>(y,x)[1] = (uchar) centros.at<float>(indice, 1);
            rotulada.at<Vec3b>(y,x)[2] = (uchar) centros.at<float>(indice, 2);
        }
    }
    imshow( "clustered image", rotulada );
    imwrite(argv[2], rotulada);
    waitKey( 0 );
}
