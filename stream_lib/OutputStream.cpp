#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <math.h>
#include <stdarg.h>

#include "OutputStream.h"

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
using namespace data_device;
size_t OutputStream::print(const String &s)
{
  return write(s.c_str(), s.length());
}

size_t OutputStream::print(const char str[],...)
{
    va_list ap;
    uint16_t len;
    va_start(ap, str);
    vsprintf((char *)tx_Buff, str, ap);
    va_end(ap);
    return write(tx_Buff);
}

size_t OutputStream::print(char c)
{
  return write(c);
}

size_t OutputStream::print(unsigned char b, int base)
{
  return print((unsigned long long)b, base);
}

size_t OutputStream::print(int n, int base)
{
  return print((long long)n, base);
}

size_t OutputStream::print(unsigned int n, int base)
{
  return print((unsigned long long)n, base);
}

size_t OutputStream::print(long long n, int base)
{
  if (base == 0)
  {
    return write(n);
  }
  else if (base == 10)
  {
    if (n < 0)
    {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  }
  else
  {
    return printNumber(n, base);
  }
}

size_t OutputStream::print(unsigned long long n, int base)
{
  if (base == 0)
    return write(n);
  else
    return printNumber(n, base);
}

size_t OutputStream::print(double n, int digits)
{
  return printFloat(n, digits);
}

size_t OutputStream::println(const String &s)
{
  size_t n = print(s);
  n += println();
  return n;
}

size_t OutputStream::println(const char c[],...)
{
    va_list ap;
    uint16_t len;
    va_start(ap, c);
    vsprintf((char *)tx_Buff, c, ap);
    va_end(ap);
  size_t n = print(tx_Buff);
  n += println();
  return n;
}

size_t OutputStream::println(char c)
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t OutputStream::println(unsigned char b, int base)
{
  size_t n = print(b, base);
  n += println();
  return n;
}

size_t OutputStream::println(int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t OutputStream::println(unsigned int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t OutputStream::println(long long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t OutputStream::println(unsigned long long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t OutputStream::println(double num, int digits)
{
  size_t n = print(num, digits);
  n += println();
  return n;
}

// Private Methods /////////////////////////////////////////////////////////////

size_t OutputStream::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2)
    base = 10;

  do
  {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (n);

  return write(str);
}

size_t OutputStream::printFloat(double number, uint8_t digits)
{
  size_t n = 0;

  if (isnan(number))
    return print("nan");
  if (isinf(number))
    return print("inf");
  if (number > 4294967040.0)
    return print("ovf"); // constant determined empirically
  if (number < -4294967040.0)
    return print("ovf"); // constant determined empirically

  // Handle negative numbers
  if (number < 0.0)
  {
    n += print('-');
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long long int_part = (unsigned long long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
  {
    n += print('.');
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint;
  }

  return n;
}







