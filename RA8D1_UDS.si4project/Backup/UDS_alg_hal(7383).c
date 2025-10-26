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






uint8_t s_aSeedBuf1[AES_SEED_LEN] = {0u};


uint8_t s_aSeedBuf[AES_SEED_LEN] = {0u};


void main(void)
{
	uint8_t result = 0;
    uint8_t mac[16];


	UDS_ALG_HAL_GetRandom(AES_SEED_LEN, s_aSeedBuf);
	UDS_ALG_HAL_EncryptData(s_aSeedBuf, 16, mac);
    printf("\nSeed: \r\n");
	print_test(s_aSeedBuf, 16);
    printf("\nmac :\r\n");
    print_test(mac, 16);
  
	if(1 == UDS_IsReceivedKeyRight(mac, s_aSeedBuf, AES_SEED_LEN))
	{
		printf("\ncorrect passs :\r\n");
	}
	else
	{
		printf("\nwrong :\r\n");
	}
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





void print_test(const unsigned char *ptr, int len)
{
    int i;
    for(i = 0; i < len; i++)
        printf("%02x ", ptr[i]);
    printf("\n");
}

void test1(void)
{
    uint8_t input[16] = {0x66,0xB0,0xCF,0x31,0xF5,0x6A,0xC1,0x6A,0xBF,0x46,0x10,0xDF,0x87,0xA1,0xAE,0x20};
    uint8_t mac[16];
    //uint8_t key[16] = {0x3D,0x2E,0x6D,0xE2,0xA1,0x25,0x17,0xBA,0xC5,0xB3,0x1B,0xBD,0x0E,0x7E,0x3B,0x54};
	uint8_t seed[16];

    printf("\n*********AES-CMAC-128 test**********\r\n");
	printf("jiami\r\n");
    UDS_ALG_HAL_EncryptData(input, 16, mac);
    printf("\nSeed: \r\n");
	print_test(input, 16);
    //printf("\nkey: \r\n", key);
	//print_test(key, 16);
    printf("\nmac :\r\n");
    print_test(mac, 16);


    printf("jiemi\r\n");
	UDS_ALG_HAL_DecryptData(mac, 16, seed);
	printf("\nseed :\r\n");
    print_test(seed, 16);

}

