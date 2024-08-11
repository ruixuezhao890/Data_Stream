/**
*********************************************************************
*********
* @project_name :write_demo
* @file : softwareSerial.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/8/11 
*********************************************************************
*********
*/


#ifndef WRITE_DEMO_SOFTWARESERIAL_HPP
#define WRITE_DEMO_SOFTWARESERIAL_HPP
#include "stream_lib/OutputStream.h"
#include "stream_lib/InputStream.h"
namespace data_device{
    class SoftwareSerial: public OutputStream,public InputStream{


    };
};



#endif //WRITE_DEMO_SOFTWARESERIAL_HPP
