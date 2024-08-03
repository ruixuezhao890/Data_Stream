#ifndef __INPUT_STREAM_H
#define __INPUT_STREAM_H


#include <cstdint>
#include "res_lib/WString.h"

namespace data_device {
    typedef struct {
        volatile uint8_t buf[256];      //接收缓冲区
        volatile uint8_t write_index;   //写指针
        volatile uint8_t read_index;    //读指针
        volatile uint16_t data_size;    //缓冲区接收到的数据长度
        /* data */
    } _rec_buf;

    class InputStream {
    protected:
        long scanNumber();

        double scanFloat();

    public:
        virtual int available();

        virtual int read();

        virtual int peek();

        String readString();

        /***阻滞读取**********************/

        int getc();

        int scan(char *); //扫描字符串
        int scan(String &);

        int scan(char &);

        int scan(unsigned char &);      //扫描字符
        int scan(int &);                //扫描数字
        int scan(unsigned int &);       //扫描数字
        int scan(long long &);          //扫描数字
        int scan(unsigned long long &); //扫描数字
        int scan(double &);             //扫描浮点数
        int scan(float &);              //扫描浮点数

        template<typename T>
        InputStream &operator>>(T &out) {
            scan(out);
            return *this;
        }
    };

}
extern data_device::_rec_buf buf;
#endif
