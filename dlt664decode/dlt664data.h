#ifndef DLT664DATA_H
#define DLT664DATA_H
#include "opencv2/opencv.hpp"
#include <iostream>

#include <fstream>


namespace dlt664 {

namespace  {
std::string StringToHex(const std::string& data)
{
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;

    for (std::string::size_type i = 0; i < data.size(); ++i)
        ss << hex[(unsigned char)data[i] >> 4] << hex[(unsigned char)data[i] & 0xf];
    return ss.str();
}

std::string HexToStr(const std::string& str)
{
    std::string result;
    for (size_t i = 0; i < str.length(); i += 2)
    {
        std::string byte = str.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
        result.push_back(chr);
    }
    return result;
}

template <typename T>
void readFromIfs(std::ifstream& ifs,T* data_p,int length=1)
{
    ifs.read(reinterpret_cast<char*>(data_p),sizeof(T)*length);
}

template <>
void readFromIfs<std::string>(std::ifstream& ifs,std::string* data_p,int length)
{
    char* tmpStr_c=new char[length];
    ifs.read(reinterpret_cast<char*>(tmpStr_c),sizeof(char)*length);
    data_p->assign(tmpStr_c,length);
    delete [] tmpStr_c;
}


}




class DLT664Data
{
public:
    explicit DLT664Data(const std::string& dltFilePath);
    ~DLT664Data();

    cv::Mat getNormIRData();

    cv::Mat IRImage;
    unsigned short fileVersion;
    unsigned short  width;
    unsigned short height;
    std::string dateTime;
    cv::Mat IRData;
    float emiss;
    float ambientTemperature;
    unsigned char len;
    unsigned int distance;
    unsigned char relativeHumidity;
    float reflectiveTemperature;
    std::string productor;
    std::string type;
    std::string serialNO;
    double longitude;
    double latitude;
    int altitude;
    unsigned int desLength;
    std::string desData;
    unsigned int IRDataOffset;
    std::string fileEndType;

    friend std::ostream& operator<<(std::ostream& stream,const DLT664Data& dlt664);

private:
    std::string m_dltFilePath;

};

std::ostream& operator<<(std::ostream& stream,const DLT664Data& dlt664);

}



#endif // DLT664DATA_H
