#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <vector>
#include "dlt664data.h"

using namespace  dlt664;

int main(int argc, char *argv[])
{
    std::string filePath {"D:/workspace/personalCode/cpp/dlt664.jpg"};
    std::string txtPath {"D:/workspace/personalCode/cpp/123.txt"};



    DLT664Data dataContent(filePath);
    std::cout<<dataContent<<std::endl;

    cv::imshow("hot",dataContent.getNormIRData());
    cv::imshow("src",dataContent.IRImage);
    cv::waitKey();






}
