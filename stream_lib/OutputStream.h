#ifndef __OUTPUT_STREAM_H
#define __OUTPUT_STREAM_H

#include <cstdio>
#include <cstdint>
#include "res_lib/WString.h"


#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
#undef BIN
#endif
#define BIN 2


#define endl "\r\n"
namespace data_device {
    class OutputStream {
    private:
        size_t printNumber(unsigned long, uint8_t);

        size_t printFloat(double, uint8_t);
    protected:
        char tx_Buff[256]={0};
    public:
        virtual size_t write(uint8_t) = 0;

        size_t write(const char *str) {
            if (str == nullptr)
                return 0;
            return write((const uint8_t *) str, strlen(str));
        }

        virtual size_t write(const uint8_t *, size_t) = 0;

        size_t write(const char *buffer, size_t size) {
            return write((const uint8_t *) buffer, size);
        }

        // size_t print(const __FlashStringHelper *);
        size_t print(const String &);

        size_t print(const char[], ...);

        size_t print(char);

        size_t print(unsigned char, int = DEC);

        size_t print(int, int = DEC);

        size_t print(unsigned int, int = DEC);

        size_t print(long long, int = DEC);

        size_t print(unsigned long long, int = DEC);

        size_t print(double, int = 2);


        // size_t println(const __FlashStringHelper *);
        size_t println(const String &s);

        size_t println(const char[], ...);

        size_t println(char);

        size_t println(unsigned char, int = DEC);

        size_t println(int, int = DEC);

        size_t println(unsigned int, int = DEC);

        size_t println(long long, int = DEC);

        size_t println(unsigned long long, int = DEC);

        size_t println(double, int = 2);

        size_t println() { return print(endl); };

        template<typename T>
        OutputStream &operator<<(T &out) {
            print(out);
            return *this;
        }
    };
}
#endif
