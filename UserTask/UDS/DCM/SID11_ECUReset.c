#include "SID11_ECUReset.h"
#include "SID11_ECUResetCfg.h"

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
Struct_Uds_SID_ER_Info Uds_SID_ER_Info;

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void SID_ER_Analysis(uint8_t *pInd, uint32_t indLen)

Description:

Parameters: 	pInd
				indLen

Return:       	void
*/
void SID_ER_Analysis(uint8_t *pInd, uint16_t indLen)
{
	uint8_t loop;
	uint8_t subID;

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < UDS_SID_ER_SUBFUNC_NUMBER; loop++)
	{
		if ((subID & 0x7FU) == Uds_SID_ER[loop].SubID)
		{
			break;
		}
	}

	if (loop < UDS_SID_ER_SUBFUNC_NUMBER)
	{
		Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_ER;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_SFNS;
	}
}

/*************************************************************************/
/*
Function:		boolean SID_ER_Appl_Deal
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean
*/
boolean SID_ER_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop;
	uint8_t subID;
	boolean ret;

	if ((pInd[0U] & 0x80U) != 0U)
	{
		Uds_Response.SuppressPosRspBit = true;
	}

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < UDS_SID_ER_SUBFUNC_NUMBER; loop++)
	{
		if (subID == Uds_SID_ER[loop].SubID)
		{
			break;
		}
	}

	if (loop < UDS_SID_ER_SUBFUNC_NUMBER)
	{
		ret = Uds_SID_ER[loop].pFunc(&pRes[1U], &pResLen[0U]);

		if (Uds_Response.ResCode == UDS_RES_CODE_PR)
		{
			pRes[0U] = subID;
			pResLen[0U] += 1U;
		}
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_SFNS;
		ret = E_OK;
	}

	return ret;
}
