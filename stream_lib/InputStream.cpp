#include "InputStream.h"
using namespace data_device;
data_device::_rec_buf buf{
    0,0,0,0
};

int InputStream::available()
{
    return buf.data_size;
}

int InputStream::read()
{
    if (buf.data_size == 0)
    {
        buf.read_index=0;
        memset((void *)buf.buf,0,256);
        return -1;
    }
    buf.data_size--;
    return buf.buf[buf.read_index++];
}
String InputStream::readString()
{
    String ret;
    while (available()){
        ret+=(char)read();
    }
    return ret;
}
int InputStream::peek()
{
    if (buf.data_size == 0)
    {
        return -1;
    }
    return buf.buf[buf.read_index];
}

int InputStream::getc()
{
    while (!available())
        ;
    return read();
}

long InputStream::scanNumber()
{
    char ch;
    do
    {
        ch = getc();
    } while (ch != '-' && (ch <= '0' || ch >= '9'));

    long res;
    int fu_flag = 0;

    if (ch == '-')
    {
        res = 0;
        fu_flag = 1;
    }
    else
    {
        res = ch - '0';
    }

    ch = getc();
    while (ch >= '0' && ch <= '9')
    {
        res *= 10;
        res += (ch - '0');
        ch = getc();
    }

    if (fu_flag)
        res = -res;
    return res;
}

double InputStream::scanFloat()
{
    char ch;
    do
    {
        ch = getc();
    } while (ch != '-' && (ch <= '0' || ch >= '9'));

    double res;
    int fu_flag = 0;

    if (ch == '-')
    {
        res = 0;
        fu_flag = 1;
    }
    else
    {
        res = (double)(ch - '0');
    }

    ch = getc();
    while (ch >= '0' && ch <= '9')
    {
        res *= 10.0;
        res += (double)(ch - '0');
        ch = getc();
    }

    if (ch != '.')
    {
        if (fu_flag)
            res = -res;
        return res;
    }

    double d = 0.1;

    while (1)
    {
        ch = getc();
        if (ch < '0' || ch > '9')
            break;
        res += d * (double)(ch - '0');
        d /= 10.0;
    }
    if (fu_flag)
        res = -res;
    return res;
}

int InputStream::scan(char &in)
{
    in = getc();
    return in;
}

int InputStream::scan(unsigned char &in)
{
    in = scanNumber();
    return in;
}

int InputStream::scan(int &in)
{
    in = scanNumber();
    return in;
}

int InputStream::scan(unsigned int &in)
{
    in = scanNumber();
    return in;
}

int InputStream::scan(long long &in)
{
    in = scanNumber();
    return in;
}

int InputStream::scan(unsigned long long &in)
{
    in = scanNumber();
    return in;
}

int InputStream::scan(double &in)
{
    in = scanFloat();
    return (int)in;
}

int InputStream::scan(float &in)
{
    in = scanFloat();
    return (int)in;
}

int InputStream::scan(char *in)
{
    char ch;
    do
    {
        ch = getc();
    } while (ch <= ' ' || ch > '~');

    int pos = 0;
    in[pos++] = ch;
    while (1)
    {
        ch = getc();
        if (ch <= ' ' || ch > '~')
        {
            break;
        }
        in[pos++] = ch;
    }
    in[pos] = '\0';
    return pos;
}

int InputStream::scan(String &in)
{
    in = "";
    char ch;
    do
    {
        ch = getc();
    } while (ch <= ' ' || ch > '~');
    in += ch;
    while (1)
    {
        ch = getc();
        if (ch <= ' ' || ch > '~')
        {
            break;
        }
        in += ch;
    }
    return in.length();
}
