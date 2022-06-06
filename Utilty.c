/*
 * Utilty.c
 *
 *  Created on: Aug 29, 2021
 *      Author: kavaipatti
 */


#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ti/sysbios/BIOS.h>
#include "RSTaWRE_Mailbox.h"
#include "Utility.h"

char calculateCheckSum(char *pDataPtr, uint16_t size){
    uint16_t i;
    char chksum = 0;

        for(i=0;i<size;++i){
            chksum+= *(pDataPtr+i);
        }
        return(chksum & 0xFF);
}




void Delay_us(uint16_t delay_value){

    uint16_t i;

        for(i=0;i<delay_value;++i){
          ;
        }
}

void Delay_1ms(void){

    uint16_t i,spin;

        for(i=0;i<1200;++i){        // for  flash wait state of 8
           for(spin=0;spin<1;++spin){
               ;
           }
        }
}
void Convert2Float(char* pbyte_data, char* pfloat_data){
      *(pfloat_data+1) = (*(pbyte_data) << 8) | *(pbyte_data+1);
      *(pfloat_data) = (*(pbyte_data+2) << 8) | *(pbyte_data+3);

}
void ConvertFloat2Bytes(float value, char *pByteArray){

    uint16_t *pDataPtr;
// Make it default big endian
         pDataPtr = (uint16_t*) &value;

        *(pByteArray+3) = *(pDataPtr) & 0xFF;
        *(pByteArray+2) = ((*pDataPtr) >> 8) & 0xFF;
        *(pByteArray+1) = (*(pDataPtr+1))& 0xFF;
        *(pByteArray) = (*(pDataPtr+1) >> 8) & 0xFF;
}
char ConvertFloatArray2ByteArray(float* pFltDataptr, char *pByteArrayptr, char float_array_size){

    char i, byte_array_index;
    float flt_value;

        byte_array_index = 0;
        for(i=0;i<float_array_size;++i){
            flt_value = *(pFltDataptr+i);
            ConvertFloat2Bytes(flt_value, pByteArrayptr+byte_array_index);
            byte_array_index+=4;
        }

        return(byte_array_index);

}
void ConvertFloat2Bytes2(float value, char *pByteArray, char endian){

    uint16_t *pDataPtr;
// Make it default big endian
         pDataPtr = (uint16_t*) &value;
         if(endian == BIG_ENDIAN){
            *(pByteArray+3) = *(pDataPtr) & 0xFF;
            *(pByteArray+2) = ((*pDataPtr) >> 8) & 0xFF;
            *(pByteArray+1) = (*(pDataPtr+1))& 0xFF;
            *(pByteArray) = (*(pDataPtr+1) >> 8) & 0xFF;
         }
         else{
             *(pByteArray) = *(pDataPtr) & 0xFF;
             *(pByteArray+1) = ((*pDataPtr) >> 8) & 0xFF;
             *(pByteArray+2) = (*(pDataPtr+1))& 0xFF;
             *(pByteArray+3) = (*(pDataPtr+1) >> 8) & 0xFF;
         }
}

void Pack_b2w(char *bArrayPtr, uint16_t *wArrayPtr,uint16_t byte_count){

    uint16_t i,k;

        k = 0;
        for(i=0;i<byte_count;i=i+2){
            wArrayPtr[k] = bArrayPtr[i+1];
            wArrayPtr[k] = (wArrayPtr[k] << 8) | bArrayPtr[i];
            k++;
        }

}
// consolidate into 1
uint16_t Convert_w2b(uint16_t *pWarray, char *pBarray, uint16_t word_count){
    uint16_t i,k;

        k = 0;
        for(i=0;i<word_count;++i){
            *(pBarray+k) = (*(pWarray+i) >> 8) & 0x00FF;
            *(pBarray+k+1) = *(pWarray+i) & 0x00FF;
            k+=2;
        }
        return(word_count*2);
}

void Unpack_w2b(uint16_t *wArrayPtr, char *bArrayPtr,uint16_t word_count){

    uint16_t i,k;

        k = 0;
        for(i=0;i<word_count;++i){
            bArrayPtr[k+1] = wArrayPtr[i] & 0xFF;
            bArrayPtr[k] = (wArrayPtr[i] >> 8) & 0xFF;
            k=k+2;
        }
}

void Unpack_32bw2b(uint32_t *wArrayPtr, char *bArrayPtr,uint16_t word_count){

    uint16_t i,k;

        k = 0;
        for(i=0;i<word_count;++i){
            bArrayPtr[k+3] = wArrayPtr[i] & 0xFF;
            bArrayPtr[k+2] = (wArrayPtr[i] >> 8) & 0xFF;
            bArrayPtr[k+1] = (wArrayPtr[i] >> 16) & 0xFF;
            bArrayPtr[k] = (wArrayPtr[i] >> 24) & 0xFF;
            k=k+4;
        }
}

void Pack_b2w2(char *bArrayPtr, uint32_t *w2ArrayPtr,uint16_t byte_count){

    uint16_t i,k;
        k = 0;
        for(i=0;i<byte_count;i=i+4){
            w2ArrayPtr[k] = bArrayPtr[i];
            w2ArrayPtr[k] = (w2ArrayPtr[k] << 8) | bArrayPtr[i+1];
            w2ArrayPtr[k] = (w2ArrayPtr[k] << 8) | bArrayPtr[i+2];
            w2ArrayPtr[k] = (w2ArrayPtr[k] << 8) | bArrayPtr[i+3];
            k++;
        }

}
