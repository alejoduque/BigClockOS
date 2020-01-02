/**
 * No warrantees or liability is assumed with this software. 
 * This software is the property of Charles M. Nowell, Jr. 
 * It is placed in the public domain for personal use only. 
 * All commercial rights are reserved. 
 * You may use this software to make a display(s) for yourself 
 * or for a model club. You may not use this software to make a 
 * product for sale, whether for profit or not. 
 * Charles M. Nowell, Jr 
 * 2-Jan-2020 
 * mickeysbigtimer@gmail.com 
 *  
 */
#include "type.h"
#include "ascii.h"
//#include "printf.h"
#include "crc.h"
#define FLIP_ON
//#undef FLIP_ON

#ifdef FLIP_ON
/* A little table to bit reverse bytes easily */
const Byte flip[] = 
{
    0x00,0x80,0x40,0xc0,0x20,0xa0,0x60,0xe0,
    0x10,0x90,0x50,0xd0,0x30,0xb0,0x70,0xf0,
    0x08,0x88,0x48,0xc8,0x28,0xa8,0x68,0xe8,
    0x18,0x98,0x58,0xd8,0x38,0xb8,0x78,0xf8,
    0x04,0x84,0x44,0xc4,0x24,0xa4,0x64,0xe4,
    0x14,0x94,0x54,0xd4,0x34,0xb4,0x74,0xf4,
    0x0c,0x8c,0x4c,0xcc,0x2c,0xac,0x6c,0xec,
    0x1c,0x9c,0x5c,0xdc,0x3c,0xbc,0x7c,0xfc,
    0x02,0x82,0x42,0xc2,0x22,0xa2,0x62,0xe2,
    0x12,0x92,0x52,0xd2,0x32,0xb2,0x72,0xf2,
    0x0a,0x8a,0x4a,0xca,0x2a,0xaa,0x6a,0xea,
    0x1a,0x9a,0x5a,0xda,0x3a,0xba,0x7a,0xfa,
    0x06,0x86,0x46,0xc6,0x26,0xa6,0x66,0xe6,
    0x16,0x96,0x56,0xd6,0x36,0xb6,0x76,0xf6,
    0x0e,0x8e,0x4e,0xce,0x2e,0xae,0x6e,0xee,
    0x1e,0x9e,0x5e,0xde,0x3e,0xbe,0x7e,0xfe,
    0x01,0x81,0x41,0xc1,0x21,0xa1,0x61,0xe1,
    0x11,0x91,0x51,0xd1,0x31,0xb1,0x71,0xf1,
    0x09,0x89,0x49,0xc9,0x29,0xa9,0x69,0xe9,
    0x19,0x99,0x59,0xd9,0x39,0xb9,0x79,0xf9,
    0x05,0x85,0x45,0xc5,0x25,0xa5,0x65,0xe5,
    0x15,0x95,0x55,0xd5,0x35,0xb5,0x75,0xf5,
    0x0d,0x8d,0x4d,0xcd,0x2d,0xad,0x6d,0xed,
    0x1d,0x9d,0x5d,0xdd,0x3d,0xbd,0x7d,0xfd,
    0x03,0x83,0x43,0xc3,0x23,0xa3,0x63,0xe3,
    0x13,0x93,0x53,0xd3,0x33,0xb3,0x73,0xf3,
    0x0b,0x8b,0x4b,0xcb,0x2b,0xab,0x6b,0xeb,
    0x1b,0x9b,0x5b,0xdb,0x3b,0xbb,0x7b,0xfb,
    0x07,0x87,0x47,0xc7,0x27,0xa7,0x67,0xe7,
    0x17,0x97,0x57,0xd7,0x37,0xb7,0x77,0xf7,
    0x0f,0x8f,0x4f,0xcf,0x2f,0xaf,0x6f,0xef,
    0x1f,0x9f,0x5f,0xdf,0x3f,0xbf,0x7f,0xff
};

#endif
const Byte remainderHigh[256] = 
  {
     0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,
     0x81,0x91,0xa1,0xb1,0xc1,0xd1,0xe1,0xf1,
     0x12,0x02,0x32,0x22,0x52,0x42,0x72,0x62,
     0x93,0x83,0xb3,0xa3,0xd3,0xc3,0xf3,0xe3,
     0x24,0x34,0x04,0x14,0x64,0x74,0x44,0x54,
     0xa5,0xb5,0x85,0x95,0xe5,0xf5,0xc5,0xd5,
     0x36,0x26,0x16,0x06,0x76,0x66,0x56,0x46,
     0xb7,0xa7,0x97,0x87,0xf7,0xe7,0xd7,0xc7,
     0x48,0x58,0x68,0x78,0x08,0x18,0x28,0x38,
     0xc9,0xd9,0xe9,0xf9,0x89,0x99,0xa9,0xb9,
     0x5a,0x4a,0x7a,0x6a,0x1a,0x0a,0x3a,0x2a,
     0xdb,0xcb,0xfb,0xeb,0x9b,0x8b,0xbb,0xab,
     0x6c,0x7c,0x4c,0x5c,0x2c,0x3c,0x0c,0x1c,
     0xed,0xfd,0xcd,0xdd,0xad,0xbd,0x8d,0x9d,
     0x7e,0x6e,0x5e,0x4e,0x3e,0x2e,0x1e,0x0e,
     0xff,0xef,0xdf,0xcf,0xbf,0xaf,0x9f,0x8f,
     0x91,0x81,0xb1,0xa1,0xd1,0xc1,0xf1,0xe1,
     0x10,0x00,0x30,0x20,0x50,0x40,0x70,0x60,
     0x83,0x93,0xa3,0xb3,0xc3,0xd3,0xe3,0xf3,
     0x02,0x12,0x22,0x32,0x42,0x52,0x62,0x72,
     0xb5,0xa5,0x95,0x85,0xf5,0xe5,0xd5,0xc5,
     0x34,0x24,0x14,0x04,0x74,0x64,0x54,0x44,
     0xa7,0xb7,0x87,0x97,0xe7,0xf7,0xc7,0xd7,
     0x26,0x36,0x06,0x16,0x66,0x76,0x46,0x56,
     0xd9,0xc9,0xf9,0xe9,0x99,0x89,0xb9,0xa9,
     0x58,0x48,0x78,0x68,0x18,0x08,0x38,0x28,
     0xcb,0xdb,0xeb,0xfb,0x8b,0x9b,0xab,0xbb,
     0x4a,0x5a,0x6a,0x7a,0x0a,0x1a,0x2a,0x3a,
     0xfd,0xed,0xdd,0xcd,0xbd,0xad,0x9d,0x8d,
     0x7c,0x6c,0x5c,0x4c,0x3c,0x2c,0x1c,0x0c,
     0xef,0xff,0xcf,0xdf,0xaf,0xbf,0x8f,0x9f,
     0x6e,0x7e,0x4e,0x5e,0x2e,0x3e,0x0e,0x1e,
  };


const Byte remainderLow[256] = 
  {
     0x00,0x21,0x42,0x63,0x84,0xa5,0xc6,0xe7,
     0x08,0x29,0x4a,0x6b,0x8c,0xad,0xce,0xef,
     0x31,0x10,0x73,0x52,0xb5,0x94,0xf7,0xd6,
     0x39,0x18,0x7b,0x5a,0xbd,0x9c,0xff,0xde,
     0x62,0x43,0x20,0x01,0xe6,0xc7,0xa4,0x85,
     0x6a,0x4b,0x28,0x09,0xee,0xcf,0xac,0x8d,
     0x53,0x72,0x11,0x30,0xd7,0xf6,0x95,0xb4,
     0x5b,0x7a,0x19,0x38,0xdf,0xfe,0x9d,0xbc,
     0xc4,0xe5,0x86,0xa7,0x40,0x61,0x02,0x23,
     0xcc,0xed,0x8e,0xaf,0x48,0x69,0x0a,0x2b,
     0xf5,0xd4,0xb7,0x96,0x71,0x50,0x33,0x12,
     0xfd,0xdc,0xbf,0x9e,0x79,0x58,0x3b,0x1a,
     0xa6,0x87,0xe4,0xc5,0x22,0x03,0x60,0x41,
     0xae,0x8f,0xec,0xcd,0x2a,0x0b,0x68,0x49,
     0x97,0xb6,0xd5,0xf4,0x13,0x32,0x51,0x70,
     0x9f,0xbe,0xdd,0xfc,0x1b,0x3a,0x59,0x78,
     0x88,0xa9,0xca,0xeb,0x0c,0x2d,0x4e,0x6f,
     0x80,0xa1,0xc2,0xe3,0x04,0x25,0x46,0x67,
     0xb9,0x98,0xfb,0xda,0x3d,0x1c,0x7f,0x5e,
     0xb1,0x90,0xf3,0xd2,0x35,0x14,0x77,0x56,
     0xea,0xcb,0xa8,0x89,0x6e,0x4f,0x2c,0x0d,
     0xe2,0xc3,0xa0,0x81,0x66,0x47,0x24,0x05,
     0xdb,0xfa,0x99,0xb8,0x5f,0x7e,0x1d,0x3c,
     0xd3,0xf2,0x91,0xb0,0x57,0x76,0x15,0x34,
     0x4c,0x6d,0x0e,0x2f,0xc8,0xe9,0x8a,0xab,
     0x44,0x65,0x06,0x27,0xc0,0xe1,0x82,0xa3,
     0x7d,0x5c,0x3f,0x1e,0xf9,0xd8,0xbb,0x9a,
     0x75,0x54,0x37,0x16,0xf1,0xd0,0xb3,0x92,
     0x2e,0x0f,0x6c,0x4d,0xaa,0x8b,0xe8,0xc9,
     0x26,0x07,0x64,0x45,0xa2,0x83,0xe0,0xc1,
     0x1f,0x3e,0x5d,0x7c,0x9b,0xba,0xd9,0xf8,
     0x17,0x36,0x55,0x74,0x93,0xb2,0xd1,0xf0
  };


Word16 computeCRC(Byte *buffer,int32_t length,Word16 startingValue,Byte doLSB)
{
    Byte   crcH,crcL;
    Byte index;
    crcH = startingValue >> 8;
    crcL = startingValue & 0xff;
    if(doLSB)
    {
        while(length--)
        {
            #ifdef FLIP_ON
            index = ((flip[*buffer++]) ^ (crcH));
            #else
            index = ((*buffer++) ^ (crcH));
            #endif
            crcH = (crcL) ^ remainderHigh[index];
            crcL = remainderLow[index];
        }//while
    }
    else
    {
        while(length--)
        {
            index = (*buffer++) ^ crcH;
            // crc = (crc<<8) ^ mt[index];
            crcH = (crcL) ^ remainderHigh[index];
            crcL = remainderLow[index];
        }//while
    }
    return((((Word16)crcH)<<8) | (Word16)crcL);
}
// use the MSB version so we don't have to bit flip the CRC value
// when sending, the other end will use the same source code
// to check the crc, so it does not have to match CCITT standards exactly.
/*-------------------------------------------------------------------------*/
Word16 calcCRC(Byte *buffer, int32_t length)
/*-------------------------------------------------------------------------*/
{
    if((length > 1000) || (length <= 0))
    {
        return(0xFFFF);
    }
  return(computeCRC(buffer,length,NOMINAL_CRC_SEED,0));
}//Word16 calcCRC(Byte *buffer, int32_t length)

Word16 calcCRCLSB(Byte *buffer, int32_t length)
/*-------------------------------------------------------------------------*/
{
    if((length > 1000) || (length <= 0))
    {
        return(0xFFFF);
    }
  return(computeCRC(buffer,length,NOMINAL_CRC_SEED,1));
}//Word16 calcCRC(Byte *buffer, int32_t length)

Word16 calcCRCUnlimited(Byte *buffer, int32_t length)
{
  return(computeCRC(buffer,length,NOMINAL_CRC_SEED,0));
}


Word16 runningCRC(Byte *buffer,int32_t length, Word16 partialCRC)
{
    if((length > 1000) || (length <= 0))
    {
        return(0xffff);
    }
    return(computeCRC(buffer,length,partialCRC,0));
}//Word16 runningCRC(Byte *buffer,int32_t length, Word16 partialCRC)


void addCRC16(Byte *buffer,int32_t length)
{
    Word16 crcValue;
    crcValue = calcCRC(buffer,length);
    buffer[length] = (crcValue >> 8);
    buffer[length+1] = (crcValue & 0xff);
}//addcrc16

