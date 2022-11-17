#include "dlt664data.h"
#include <iomanip>
using namespace  dlt664;



DLT664Data::DLT664Data(const std::string& dltFilePath):m_dltFilePath(dltFilePath)
{
    IRImage=cv::imread(dltFilePath);

    std::ifstream ifs(m_dltFilePath,std::ios::in|std::ios_base::binary|std::ios::ate);
    ifs.seekg(-20,std::ios::end);
    readFromIfs(ifs,&IRDataOffset);
    readFromIfs(ifs,&fileEndType,16);

    ifs.seekg(IRDataOffset,std::ios::beg);
    readFromIfs(ifs,&fileVersion);
    readFromIfs(ifs,&width);
    readFromIfs(ifs,&height);
    readFromIfs(ifs,&dateTime,14);

    float* IRData_p=new float[width*height];
    ifs.read(reinterpret_cast<char*>(IRData_p),width*height*4);
    IRData=cv::Mat(height,width,CV_32FC1,IRData_p).clone();
    delete  [] IRData_p;

    readFromIfs(ifs,&emiss);
    readFromIfs(ifs,&ambientTemperature);
    readFromIfs(ifs,&len);
    readFromIfs(ifs,&distance);
    readFromIfs(ifs,&relativeHumidity);
    readFromIfs(ifs,&reflectiveTemperature);
    readFromIfs(ifs,&productor,32);
    readFromIfs(ifs,&type,32);
    readFromIfs(ifs,&serialNO,32);
    readFromIfs(ifs,&longitude);
    readFromIfs(ifs,&latitude);
    readFromIfs(ifs,&altitude);
    readFromIfs(ifs,&desLength);
    readFromIfs(ifs,&desData,desLength);
}

cv::Mat DLT664Data::getNormIRData()
{
    cv::Mat normIRData;
    cv::normalize(IRData,normIRData,1.0,0,cv::NORM_MINMAX);
    normIRData=normIRData*255;
    normIRData.convertTo(normIRData,CV_8UC1);
    return normIRData;
}

DLT664Data::~DLT664Data()
{

}

std::ostream& dlt664::operator<<(std::ostream& os,const DLT664Data& dlt664)
{
    os<< std::left<<"IRImage Size: "<<dlt664.IRImage.size<<std::endl
      <<"File Version: "<<std::hex<<std::setiosflags(std::ios::showbase|std::ios::internal)<<dlt664.fileVersion<<std::endl
      <<"Width: "<<std::resetiosflags(std::ios::showbase|std::ios::internal)<<std::dec<<dlt664.width<<std::endl
     <<"Height: "<<dlt664.height<<std::endl
    <<"DateTime: "<<dlt664.dateTime<<std::endl
    <<"IRData Size: "<<dlt664.IRData.size<<std::endl
    <<"Emiss: "<<dlt664.emiss<<std::endl
    <<"Ambient Temperature: "<<dlt664.ambientTemperature<<"C"<<std::endl
    <<"Len: "<<static_cast<ushort>(dlt664.len)<<std::endl
    <<"Distance: "<<dlt664.distance<<"m"<<std::endl
    <<"Relative Humidity: "<<static_cast<ushort>(dlt664.relativeHumidity)<<"%"<<std::endl
    <<"Productor: "<<StringToHex(dlt664.productor)<<std::endl
    <<"Type: "<<StringToHex(dlt664.type)<<std::endl
    <<"Serial NO: "<<StringToHex(dlt664.serialNO)<<std::endl
    <<"Longitude: "<<dlt664.longitude<<std::endl
    <<"Latitude: "<<dlt664.latitude<<std::endl
    <<"Altitude: "<<dlt664.altitude<<"m"<<std::endl
    <<"Description Length: "<<dlt664.desLength<<std::endl
    <<"Description Data: "<<dlt664.desData<<std::endl
    <<"IRData Offset: "<<std::oct<<dlt664.IRDataOffset<<std::endl
    <<"File End Type: "<<StringToHex(dlt664.fileEndType.data())<<std::endl;
    return os;
}
