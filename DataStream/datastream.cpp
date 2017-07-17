/*****************************************************************************
 * datastream.cpp -- DataStream C++ code
 *
 * Copyright (C) 2017 Jeroen Lodder
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *****************************************************************************/
#include "datastream.h"

DataStream::DataStream(void *b, size_t n, DataStream::Endian e)
{
    // Assert when not little endian
    assert(hostBigEndian() == false);

    // Convert pointer
    start = (uint8_t*)b;
    data = start;

    // Set maximum size
    if(n == 0)
        size = SIZE_MAX;
    else
        size = n;

    // Set endian
    endian = e;

    // Middle endian is not supported
    assert(endian != Middle);

}

DataStream::~DataStream()
{

}

size_t DataStream::read(void *dst, size_t n)
{
    // If size requested isn't available
    assert(remaining() >= n);
    // Cast pointer
    uint8_t *d = (uint8_t*)dst;
    // Little endian read
    if(endian == Little){
        for(size_t i=0; i<n; i++)
            *d++ = *data++;
    }
    // Big endian read
    if(endian == Big){
        d += n;
        for(size_t i=0; i<n; i++)
            *--d = *data++;
    }
    return n;
}

void DataStream::operator>>(int8_t &i)
{
    assert(remaining() >= 1);
    i = *data++;
}

void DataStream::operator>>(int16_t &i)
{
    assert(remaining() >= 2);
    uint16_t d;
    d = *data++;
    d <<= 8;
    d |= *data++;
    if(endian == Little)
        d = swap_uint16(d);
    i = d;
}

void DataStream::operator>>(int32_t &i)
{
    assert(remaining() >= 4);
    uint32_t d;
    d = *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    if(endian == Little)
        d = swap_uint32(d);
    i = d;
}

void DataStream::operator>>(int64_t &i)
{
    assert(remaining() >= 8);
    uint64_t d;
    d = *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    if(endian == Little)
        d = swap_uint64(d);
    i = d;
}

void DataStream::operator>>(uint8_t &i)
{
    assert(remaining() >= 1);
    i = *data++;
}

void DataStream::operator>>(uint16_t &i)
{
    assert(remaining() >= 2);
    uint16_t d;
    d = *data++;
    d <<= 8;
    d |= *data++;
    if(endian == Little)
        d = swap_uint16(d);
    i = d;
}

void DataStream::operator>>(uint32_t &i)
{
    assert(remaining() >= 4);
    uint32_t d;
    d = *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    if(endian == Little)
        d = swap_uint32(d);
    i = d;
}

void DataStream::operator>>(uint64_t &i)
{
    assert(remaining() >= 8);
    uint64_t d;
    d = *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    d <<= 8;
    d |= *data++;
    if(endian == Little)
        d = swap_uint64(d);
    i = d;
}

void DataStream::operator>>(float &i)
{
    assert(remaining() >= 4);
    union {
      uint32_t u;
      float f;
    } d;
    this->operator >>(d.u);
    i = d.f;
}

void DataStream::operator>>(double &i)
{
    assert(remaining() >= 8);
    union {
      uint64_t u;
      double f;
    } d;
    this->operator >>(d.u);
    i = d.f;
}

size_t DataStream::write(const void *src, size_t n)
{
    // If size requested isn't available
    assert(remaining() >= n);
    // Cast pointer
    uint8_t *d = (uint8_t*)src;
    // Little endian read
    if(endian == Little){
        for(size_t i=0; i<n; i++)
            *data++ = *d++;
    }
    // Big endian read
    if(endian == Big){
        d += n;
        for(size_t i=0; i<n; i++)
            *data++ = *--d;
    }
    return n;
}

void DataStream::operator<<(int8_t i)
{
    assert(remaining() >= 1);
    *data++ = (uint8_t)i;
}

void DataStream::operator<<(int16_t i)
{
    assert(remaining() >= 2);
    uint16_t d = (uint16_t)i;
    if(endian == Big){
        d = swap_uint16(d);
    }
    *data++ = d;
    d >>= 8;
    *data++ = d;
}

void DataStream::operator<<(int32_t i)
{
    assert(remaining() >= 4);
    uint32_t d = (uint32_t)i;
    if(endian == Big){
        d = swap_uint32(d);
    }
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
}

void DataStream::operator<<(int64_t i)
{
    assert(remaining() >= 8);
    uint64_t d = (uint64_t)i;
    if(endian == Big){
        d = swap_uint64(d);
    }
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
}

void DataStream::operator<<(uint8_t i)
{
    assert(remaining() >= 1);
    *data++ = (uint8_t)i;
}

void DataStream::operator<<(uint16_t i)
{
    assert(remaining() >= 4);
    uint16_t d = (uint16_t)i;
    if(endian == Big){
        d = swap_uint16(d);
    }
    *data++ = d;
    d >>= 8;
    *data++ = d;
}

void DataStream::operator<<(uint32_t i)
{
    assert(remaining() >= 4);
    uint32_t d = (uint32_t)i;
    if(endian == Big){
        d = swap_uint32(d);
    }
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
}

void DataStream::operator<<(uint64_t i)
{
    assert(remaining() >= 8);
    uint64_t d = (uint64_t)i;
    if(endian == Big){
        d = swap_uint64(d);
    }
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
    d >>= 8;
    *data++ = d;
}

void DataStream::operator<<(float i)
{
    assert(remaining() >= 4);
    union {
      uint32_t u;
      float f;
    } d;
    d.f = i;
    this->operator <<(d.u);
}

void DataStream::operator<<(double i)
{
    assert(remaining() >= 8);
    union {
      uint64_t u;
      double f;
    } d;
    d.f = i;
    this->operator <<(d.u);
}

void DataStream::reset()
{
    data = start;
}

bool DataStream::hostBigEndian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};
    return bint.c[0] == 1;
}
