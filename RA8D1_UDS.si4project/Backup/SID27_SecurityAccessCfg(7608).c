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
		{0x03U,
		 1U,
		 SID_SA_SUBID_RSD_Callback},

		{0x04U,
		 5U,
		 SID_SA_SUBID_SK_Callback},
		 
	{0x01U,
	 1U,
	 SID_SA_SUBID_RSD_Callback},
	
	{0x02U,
	 5U,
	 SID_SA_SUBID_SK_Callback},

};

uint8_t Uds_Seed[4U]; /*Seed Buf*/
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
static uint32_t saGetKey(uint32_t wSeed, uint32_t wConst)
{
	uint32_t wTop31Bits;

	wTop31Bits = wSeed;
	wTop31Bits = wTop31Bits ^ wConst;
	return (wTop31Bits);
}

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
			for(i=0;i<AES_SEED_LEN;i++)
			{
				Uds_Seed[i] = 0x00U;
			}
		}
		else
		{
			UDS_ALG_HAL_GetRandom(AES_SEED_LEN, Uds_Seed);
		}

		if (Uds_SID_SA_Info.RequestSeedFlag != true)
		{
			Uds_SID_SA_Info.RequestSeedFlag = true;
		}
		else
		{
		}

		pResLen[0U] = 4U;
		pRes[0U] = Uds_Seed[0U];
		pRes[1U] = Uds_Seed[1U];
		pRes[2U] = Uds_Seed[2U];
		pRes[3U] = Uds_Seed[3U];

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
	uint32_t key;

	if (Uds_SID_SA_Info.RequestSeedFlag == true)
	{
		seed = (Uds_Seed[0U] << 24U) | (Uds_Seed[1U] << 16U) | (Uds_Seed[2U] << 8U) | Uds_Seed[3U];

		key = saGetKey(seed, MASK_VALUE); /*车企安全算法*/

		Uds_Seed[0U] = (uint8_t)((key & 0xFF000000) >> 24U);
		Uds_Seed[1U] = (uint8_t)((key & 0x00FF0000) >> 16U);
		Uds_Seed[2U] = (uint8_t)((key & 0x0000FF00) >> 8U);
		Uds_Seed[3U] = (uint8_t)(key & 0x000000FF);
		for (loop = 0U; loop < 4U; loop++)
		{
			if (pInd[loop] != Uds_Seed[loop])
			{
				break;
			}
		}

//		if (loop < 4U)
		if (0)
		{
			Uds_SID_SA_Info.RequestSeedFlag = false;
			Uds_SID_SA_Info.FailCount++;
			/*3 次非法密钥后，服务器需要锁定 10 秒后才允许再次进行安全访问*/
			if (Uds_SID_SA_Info.FailCount > 2U)
			{
				Uds_SID_SA_Info.AccessDelay = 60000 * UDS_MS_MULTI_FACTOR;
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
