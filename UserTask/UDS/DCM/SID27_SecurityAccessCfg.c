#include "SID27_SecurityAccessCfg.h"
#include "Dcm_DrvCfg.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_SA_SUBID_RSD_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

boolean SID_SA_SUBID_SK_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_SA Uds_SID_SA[SID_SA_SUBFUNC_NUMBER] =
{
	{0x01U,SID_SA_SUBID_RSD_Callback},

	{0x02U,SID_SA_SUBID_SK_Callback},
		 
	{0x03U,SID_SA_SUBID_RSD_Callback},
	
	{0x04U,SID_SA_SUBID_SK_Callback},
	
	{0x05U,SID_SA_SUBID_RSD_Callback},
	
	{0x06U,SID_SA_SUBID_SK_Callback},

};

#define SEED_LEN (16)

uint8_t Uds_Seed[SEED_LEN]; /*Seed Buf*/
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/


/*************************************************************************/
/*
Function:		boolean SID_SA_SUBID_RSD_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_SA_SUBID_RSD_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t i;
	//uint32_t cur_STM_TIM0 = (uint32_t)0xAAAA5555U;

	if (Uds_SID_SA_Info.AccessDelay == 0U)
	{
		if (Uds_SID_SA_Info.Security_Locked == false)
		{
			for(i=0;i<SEED_LEN;i++)
			{
				Uds_Seed[i] = 0x00U;
			}
		}
		else
		{
			AES_CBC_CMAC_GetRandom(SEED_LEN, Uds_Seed);
		}

		if (Uds_SID_SA_Info.RequestSeedFlag != true)
		{
			Uds_SID_SA_Info.RequestSeedFlag = true;
		}
		else
		{
		}

		pResLen[0U] = SEED_LEN;
		for(i=0;i<SEED_LEN;i++)
		{
			pRes[i] = Uds_Seed[i];
		}
		Uds_Response.ResCode = UDS_RES_CODE_PR;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_RTDNE;
	}
	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		boolean SID_SA_SUBID_SK_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_SA_SUBID_SK_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t loop;
	uint32_t seed;
	//uint32_t key;
	uint8_t key[SEED_LEN];

	if (Uds_SID_SA_Info.RequestSeedFlag == true)
	{
		AES_CBC_CMAC_EncryptData(Uds_Seed, SEED_LEN, key);

		for (loop = 0U; loop < SEED_LEN; loop++)
		{
			if (pInd[loop] != key[loop])
			{
				break;
			}
		}

		if (loop < SEED_LEN)
		//if (0)
		{
			Uds_SID_SA_Info.RequestSeedFlag = false;
			Uds_SID_SA_Info.FailCount++;
			/*3 次非法密钥后，服务器需要锁定 10 秒后才允许再次进行安全访问*/
			if (Uds_SID_SA_Info.FailCount > 2U)
			{
				Uds_SID_SA_Info.AccessDelay = 10000 * UDS_MS_MULTI_FACTOR;
				Uds_Response.ResCode = UDS_RES_CODE_ENOA;
			}
			else
			{
				Uds_Response.ResCode = UDS_RES_CODE_IK;
			}
			/*ToDo*/

		}
		else
		{
			Uds_SID_SA_Info.RequestSeedFlag = false;
			Uds_SID_SA_Info.Security_Locked = false;

			Uds_SID_SA_Info.FailCount = 0;
			Uds_SID_SA_Info.AccessDelay = 0;
			pResLen[0U] = 0U;
			Uds_Response.ResCode = UDS_RES_CODE_PR;
			/*Todo*/

		}
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_RSE;
	}

	ret = E_OK;

	return ret;
}

