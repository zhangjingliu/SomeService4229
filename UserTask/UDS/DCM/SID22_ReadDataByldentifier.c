#include "SID22_ReadDataByldentifier.h"
#include "SID22_ReadDataByldentifierCfg.h"

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
uint16_t SID_RDBI_DID_Buf[SID_RDBI_DID_NUMBER]; /*DID Buffer*/
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void SID_RDBI_Analysis(uint8_t *pInd, uint32_t indLen)

Description:

Parameters: 	pInd
				indLen

Return:       	void
*/
void SID_RDBI_Analysis(uint8_t *pInd, uint16_t indLen)
{
	uint8_t loop_1;
	uint8_t loop_2;
	uint8_t loop_3;
	uint16_t did;
	boolean errflag;
	boolean neg_78_Flag;

	if ((indLen % 2U) == 0U)
	{
		errflag = false;
		loop_3 = 0U;
		for (loop_1 = 0U; loop_1 < SID_RDBI_DID_NUMBER; loop_1++)
		{
			SID_RDBI_DID_Buf[loop_1] = 0x00U;
		}

		for (loop_1 = 0U; loop_1 < Uds_Indication.Length[0U] - 1U; loop_1 += 2U)
		{
			did = (uint16_t)pInd[loop_1] * 0x100U + pInd[loop_1 + 1U];

			for (loop_2 = 0U; loop_2 < SID_RDBI_DID_NUMBER; loop_2++)
			{
				if (did == Uds_SID_RDBI[loop_2].DID)
				{
					SID_RDBI_DID_Buf[loop_3] = did;
					loop_3++;
					break;
				}
			}

			if (loop_2 >= SID_RDBI_DID_NUMBER)
			{
				errflag = true;
				Uds_Response.ResCode = UDS_RES_CODE_ROOR;
				break;
			}
		}

		if (errflag == false)
		{
			neg_78_Flag = false;

			if (neg_78_Flag == true)
			{
				Uds_Response.ResCode = UDS_RES_CODE_RCRRP;
			}
			Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_RDBI;
		}
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_IMLOIF;
	}
}

/*************************************************************************/
/*
Function:		boolean SID_RDBI_Appl_Deal
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RDBI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop_1;
	uint8_t loop_2;
	uint32_t temp_Length;
	boolean ret;

	ret = E_OK;
	pResLen[0U] = 0U;
	for (loop_1 = 0U; loop_1 < SID_RDBI_DID_NUMBER; loop_1++)
	{
		for (loop_2 = 0U; loop_2 < SID_RDBI_DID_NUMBER; loop_2++)
		{
			if (SID_RDBI_DID_Buf[loop_1] == Uds_SID_RDBI[loop_2].DID)
			{
				ret = Uds_SID_RDBI[loop_2].pFunc(&(pRes[pResLen[0U] + 2U]), &temp_Length);

				if (Uds_Response.ResCode == UDS_RES_CODE_PR)
				{
					pRes[pResLen[0U]] = (uint8_t)(SID_RDBI_DID_Buf[loop_1] / 0x100U);
					pRes[pResLen[0U] + 1U] = (uint8_t)SID_RDBI_DID_Buf[loop_1];
					pResLen[0U] += (2U + temp_Length);
				}
				break;
			}
		}

		if ((ret != E_OK) || (Uds_Response.ResCode != UDS_RES_CODE_PR))
		{
			break;
		}
	}

	return ret;
}
