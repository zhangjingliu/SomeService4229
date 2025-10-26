#ifndef UDS_ALG_HAL_H
#define UDS_ALG_HAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "AES.h"


#define AES_SEED_LEN (16u)

extern boolean UDS_ALG_HAL_EncryptData(const uint8_t *i_pPlainText, const uint32_t i_dataLen, uint8_t *o_pCipherText);


extern boolean UDS_ALG_HAL_DecryptData(const uint8_t *i_pCipherText, const uint32_t i_dataLen, uint8_t *o_pPlainText);


extern boolean UDS_ALG_HAL_GetRandom(const uint32_t i_needRandomDataLen, uint8_t *o_pRandomDataBuf);


uint8_t UDS_IsReceivedKeyRight(const uint8_t *i_pReceivedKey,const uint8_t *i_pTxSeed,const uint8_t KeyLen);

void test1(void);
void print_test(const unsigned char *ptr, int len);


#endif 
