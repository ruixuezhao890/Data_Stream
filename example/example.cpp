/**
*********************************************************************
*********
* @project_name :write_demo
* @file : Bridge.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/8/2 
*********************************************************************
*********
*/
//

#include "bridge.h"
#include "Serial/hardware_serial/SerialPort.h"
data_device::SerialPort * Serial;
//uint8_t flag=0;
void test_uart(){
    Serial=new data_device::SerialPort(&huart1);
//    Serial->println("hello world");
    *Serial<<"hello world wow"<<endl;
    Serial->print("beautiful a day");
    Serial->println();
    Serial->println(3.1415,3);
    Serial->println(322,HEX);
    Serial->println(322,OCT);
    Serial->println(322,BIN);
    Serial->println("this is c style %d",22);
    //show String
    String s1 = "application";
    String s2 = "is my";

    Serial->println(s1+s2);

    Serial->println(s1+" hello world");
    //If you want to print a command
    Serial->print("AT + OK");
    //It is the fastest because the write function is called directly,
    // blocking sending it is completed first
}
void setup(){
    test_uart();
}
void loop(){
    String inString="";
    while (Serial->available()>0){
        inString=Serial->readString();
        if (Serial->available()==0){
            //If you display the return to use it like I do,
            // there will be errors.
            Serial->print(inString);
        }

    }
    // 检查是否接收到数据，如果接收到数据，则输出该数据


}