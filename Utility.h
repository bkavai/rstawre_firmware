/*
 * Utility.h
 *
 *  Created on: Aug 29, 2021
 *      Author: kavaipatti
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdbool.h>

#define     BIG_ENDIAN                  1
#define     LITTLE_ENDIAN               0
#define     MAX_STD_DEV_DATA_SIZE       32


char calculateCheckSum(char *pDataPtr, uint16_t size);
float CalulateStdDev(float *pDataPtr, char array_offset, char array_step, uint16_t size);
uint16_t Convert_w2b(uint16_t *pWarray, char *pBarray, uint16_t word_count);
float Scale_nbits(char res, float value, float max);
float Scale_by_factor(float value, float max, float mult);
void dec_to_octal(uint16_t value, char* pOctalData);
void Delay_us(uint16_t delay_value);
bool IsGoodCRC8(char   *p2block,uint16_t  length);
char GetCrc8(char  *p2block,   uint16_t length);
void Delay_1ms(void);
void Convert2Float(char* pbyte_data, char* pfloat_data);
void ConvertFloat2Bytes(float value, char *pByteArray);
void Pack_b2w(char *bArrayPtr, uint16_t *wArrayPtr,uint16_t byte_count);
void Unpack_w2b(uint16_t *wArrayPtr, char *bArrayPtr,uint16_t word_count);
void Unpack_32bw2b(uint32_t *wArrayPtr, char *bArrayPtr,uint16_t word_count);
void Pack_b2w2(char *bArrayPtr, uint32_t *w2ArrayPtr,uint16_t byte_count);      // bytes to UINT32
uint16_t Prepare_memory_header(char *pDataPtr, char data_type);
uint16_t Prepare_memory_footer(char *pDataPtr);
void Utility_debug_display(char dbg_char);
void ConvertFloat2Bytes2(float value, char *pByteArray, char endian);
void dec_to_octal_generic(int32_t value, char* pOctalData, char nbits);
char Check_header_status(char *pDataptr, char data_type);
char Check_footer_status(char *pDataptr);
char Verify_CRC_Status(char *pDataptr, uint16_t size);
char ConvertFloatArray2ByteArray(float* pFltDataptr, char *pByteArrayptr, char float_array_size);

#endif /* UTILITY_H_ */
