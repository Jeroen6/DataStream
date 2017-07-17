/*****************************************************************************
 * datastream.h -- DataStream C++ class definition
 *
 * Copyright (C) 2017 Jeroen Lodder
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *****************************************************************************/
#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <stdint.h>
#include <stddef.h>
#include <cstdint>
#include <assert.h>

/**
 * @brief The DataStream class provides a way to encode and decode streams
 * from and to standard C types.
 *
 * @details
 * Supported types:
 *  int8_t
 *  int16_t
 *  int32_t
 *  int64_t
 *  uint8_t
 *  uint16_t
 *  uint32_t
 *  uint64_t
 *  float
 *  double
 */
class DataStream
{
public:
    /** @brief Endian selection */
    enum Endian
    {
        Little = 0,
        Big = 1,
        Middle = 2
    };

    /** @brief Create a DataStream.
     * @param[in] data.
     * @param[in] Size of data buffer.
     * @param[in] Endianness of encoding/decoding.
     */
    DataStream(void *b, size_t n = 0, Endian e = Little);
    ~DataStream();

    /** @group Read functions
     * @{
     */
    size_t read(void *dst, size_t n);
    void operator>>(int8_t   &i);
    void operator>>(int16_t  &i);
    void operator>>(int32_t  &i);
    void operator>>(int64_t  &i);
    void operator>>(uint8_t  &i);
    void operator>>(uint16_t &i);
    void operator>>(uint32_t &i);
    void operator>>(uint64_t &i);
    void operator>>(float &i);
    void operator>>(double &i);
    /** @} */

    /** @group Write functions
     * @{
     */
    size_t write(const void *src, size_t n);
    void operator<<(int8_t   i);
    void operator<<(int16_t  i);
    void operator<<(int32_t  i);
    void operator<<(int64_t  i);
    void operator<<(uint8_t  i);
    void operator<<(uint16_t i);
    void operator<<(uint32_t i);
    void operator<<(uint64_t i);
    void operator<<(float i);
    void operator<<(double i);
    /** @} */

    /**
     * @brief Reset stream.
     */
    void reset(void);

    /**
     * @brief Set position in stream.
     */
    void seek(size_t pos){
        assert(pos < size);
        data = start + pos;
    }

    /**
     * @brief Calculate remaining bytes in assigned data buffer.
     */
    size_t remaining(void){
        size_t n = size - (((char *)data) - ((char *)start));
        return n;
    }

private:
    /** Start of data */
    uint8_t *start;
    /** Current data pointers */
    uint8_t *data;
    /** Size of data */
    size_t size;
    /** Data endian */
    Endian endian;

    /**
     * @brief Test if host system is big endian.
     */
    bool hostBigEndian(void);

    /**
     * @brief Byte swap unsigned short
     */
    uint16_t swap_uint16( uint16_t val )
    {
        return (val << 8) | (val >> 8 );
    }

    /**
     * @brief Byte swap unsigned int
     */
    uint32_t swap_uint32( uint32_t val )
    {
        val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
        return (val << 16) | (val >> 16);
    }

    /**
     * @brief Byte swap unsigned long int
     */
    uint64_t swap_uint64( uint64_t val )
    {
        val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
        val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
        return (val << 32) | (val >> 32);
    }
};

#endif // DATASTREAM_H
