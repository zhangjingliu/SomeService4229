#include "UDS_alg_hal.h"


uint8_t input1[16] = {0x66,0xB0,0xCF,0x31,0xF5,0x6A,0xC1,0x6A,0xBF,0x46,0x10,0xDF,0x87,0xA1,0xAE,0x20};
uint8_t input2[16] = {0xF0,0xB6,0xE5,0x3E,0xA9,0x01,0xFD,0x31,0xE6,0x64,0x81,0xD4,0x23,0x98,0x7C,0xC7};



 boolean UDS_ALG_HAL_EncryptData(const uint8_t *i_pPlainText, const uint32_t i_dataLen, uint8_t *o_pCipherText)
{
	boolean ret = 0;

	aes((signed char *)i_pPlainText, i_dataLen, (signed char *)&input1[0], (signed char *)o_pCipherText);

	return ret;
}


 boolean UDS_ALG_HAL_DecryptData(const uint8_t *i_pCipherText, const uint32_t i_dataLen, uint8_t *o_pPlainText)
{
	boolean ret = 0;


	deAes((signed char *)i_pCipherText, i_dataLen, (signed char *)&input1[0], (signed char *)o_pPlainText);	



	return ret;
}


boolean UDS_ALG_HAL_GetRandom(const uint32_t i_needRandomDataLen, uint8_t *o_pRandomDataBuf)
{
	boolean ret = TRUE;
	uint8_t index = 0u;
	uint32_t random = 0;

	if((0u == i_needRandomDataLen) || (NULL_PTR == o_pRandomDataBuf))
	{
		ret = FALSE;
	}

	for(index = 0; index < i_needRandomDataLen; index++)
	{
		o_pRandomDataBuf[index] = 0x11;

		//random += 0x11u;
	}


	return ret;

}






/*check random is right?*/
uint8_t UDS_IsReceivedKeyRight(const uint8_t *i_pReceivedKey,const uint8_t *i_pTxSeed,const uint8_t KeyLen)
{
    uint8_t index = 0u;
    uint8_t aPlainText[AES_SEED_LEN] = {0u};


    UDS_ALG_HAL_DecryptData(i_pReceivedKey, KeyLen, aPlainText);

    index = 0u;
    while(index < AES_SEED_LEN)
    {
        if(aPlainText[index] != i_pTxSeed[index])
        {
            return 0;
        }

        index++;
    }

    return 1;
}






