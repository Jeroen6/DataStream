/*****************************************************************************
 * main.cpp -- DataStream test code
 *
 * Copyright (C) 2017 Jeroen Lodder
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *****************************************************************************/
#include <iostream>
#include <string.h>
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "datastream.h"

using namespace std;

int main()
{
    uint8_t test[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
    uint8_t zata[8];
    uint8_t result[8];
    memset(zata,0x00,sizeof(zata));
    DataStream lt(zata, sizeof(zata), DataStream::Little);
    DataStream bt(zata, sizeof(zata), DataStream::Big);

    //uint8_t  ztest[16] = {0};
    int8_t   ti8 , ri8 ;
    int16_t  ti16, ri16;
    int32_t  ti32, ri32;
    int64_t  ti64, ri64;
    uint8_t  tu8 , ru8 ;
    uint16_t tu16, ru16;
    uint32_t tu32, ru32;
    uint64_t tu64, ru64;
    float    tf, rf;
    double   td, rd;

    lt.write(test, 8);    lt.reset();
    lt.read(result,8);    lt.reset();
    assert(!memcmp(result,test,8));

    bt.write(test, 8);    bt.reset();
    bt.read(result,8);    bt.reset();
    assert(!memcmp(result,test,8));

    // Write and Read test
    // Test / Result
    ti8  = ri8  = -0x11;
    ti16 = ri16 = -0x2211;
    ti32 = ri32 = -0x44332211;
    ti64 = ri64 = -0x4877665544332211;
    tu8  = ru8  = 0x81;
    tu16 = ru16 = 0x8211;
    tu32 = ru32 = 0x84332211;
    tu64 = ru64 = 0x8877665544332211;
    tf = rf = M_PI;
    td = rd = M_PI;

    lt << ti8;          lt.reset();
    lt >> ti8;          lt.reset();
    assert(ti8 == ri8);
    lt << ti16;         lt.reset();
    lt >> ti16;         lt.reset();
    assert(ti16 == ti16);
    lt << ti32;         lt.reset();
    lt >> ti32;         lt.reset();
    assert(ti32 == ti32);
    lt << ti64;         lt.reset();
    lt >> ti64;         lt.reset();
    assert(ti64 == ti64);
    lt << tu8;          lt.reset();
    lt >> tu8;          lt.reset();
    assert(tu8 == ru8);
    lt << tu16;         lt.reset();
    lt >> tu16;         lt.reset();
    assert(tu16 == tu16);
    lt << tu32;         lt.reset();
    lt >> tu32;         lt.reset();
    assert(tu32 == tu32);
    lt << tu64;         lt.reset();
    lt >> tu64;         lt.reset();
    assert(tu64 == tu64);
    lt << tf;           lt.reset();
    lt >> tf;           lt.reset();
    assert(tf == tf);
    lt << td;           lt.reset();
    lt >> td;           lt.reset();
    assert(td == td);

    bt << ti8;          bt.reset();
    bt >> ti8;          bt.reset();
    assert(ti8 == ri8);
    bt << ti16;         bt.reset();
    bt >> ti16;         bt.reset();
    assert(ti16 == ti16);
    bt << ti32;         bt.reset();
    bt >> ti32;         bt.reset();
    assert(ti32 == ti32);
    bt << ti64;         bt.reset();
    bt >> ti64;         bt.reset();
    assert(ti64 == ti64);
    bt << tu8;          bt.reset();
    bt >> tu8;          bt.reset();
    assert(tu8 == ru8);
    bt << tu16;         bt.reset();
    bt >> tu16;         bt.reset();
    assert(tu16 == tu16);
    bt << tu32;         bt.reset();
    bt >> tu32;         bt.reset();
    assert(tu32 == tu32);
    bt << tu64;         bt.reset();
    bt >> tu64;         bt.reset();
    assert(tu64 == tu64);
    bt << tf;           bt.reset();
    bt >> tf;           bt.reset();
    assert(tf == tf);
    bt << td;           bt.reset();
    bt >> td;           bt.reset();
    assert(td == td);

    // Sequential test
    memset(zata,0x00,sizeof(zata));
    lt << (uint8_t)0x00u;
    lt << (uint8_t)0x11u;
    lt << (uint8_t)0x22u;
    lt << (uint8_t)0x33u;
    lt << (uint8_t)0x44u;
    lt << (uint8_t)0x55u;
    lt << (uint8_t)0x66u;
    lt << (uint8_t)0x77u;
    lt.reset();
    lt.read(result,8);
    assert(!memcmp(result,test,8));

    // Sequential test
    memset(zata,0x00,sizeof(zata));
    bt << (uint8_t)0x77u;
    bt << (uint8_t)0x66u;
    bt << (uint8_t)0x55u;
    bt << (uint8_t)0x44u;
    bt << (uint8_t)0x33u;
    bt << (uint8_t)0x22u;
    bt << (uint8_t)0x11u;
    bt << (uint8_t)0x00u;
    bt.reset();
    bt.read(result,8);
    assert(!memcmp(result,test,8));

    cout << "Pass" << endl;
    return 0;
}
