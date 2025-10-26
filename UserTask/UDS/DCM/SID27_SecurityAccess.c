#include "SID27_SecurityAccess.h"
#include "SID27_SecurityAccessCfg.h"

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
Struct_Uds_SID_SA_Info Uds_SID_SA_Info;
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/

/*************************************************************************/
/*
Function:		void SID_SA_Analysis(uint8_t *pInd, uint16_t indLen)

Description:

Parameters: 	pInd
				indLen

Return:       	void
*/
void SID_SA_Analysis(uint8_t *pInd, uint16_t indLen)
{
	uint8_t loop;
	uint8_t subID;

	subID = pInd[0U] & 0x7FU;
	for (loop = 0U; loop < SID_SA_SUBFUNC_NUMBER; loop++)
	{
		if ((subID & 0x7FU) == Uds_SID_SA[loop].SubID)
		{
			break;
		}
	}
	if (loop < SID_SA_SUBFUNC_NUMBER)
	{
		Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_SA;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_SFNS;
	}
}

/*************************************************************************/
/*
Function:		boolean SID_SA_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_SA_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop;
	uint8_t subID;
	boolean ret;

	if ((pInd[0U] & 0x80U) != 0U)
	{
		Uds_Response.SuppressPosRspBit = true;
	}

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < SID_SA_SUBFUNC_NUMBER; loop++)
	{
		if (subID == Uds_SID_SA[loop].SubID)
		{
			break;
		}
	}

	if (loop < SID_SA_SUBFUNC_NUMBER)
	{
		ret = Uds_SID_SA[loop].pFunc(&pInd[1U], &pRes[1U], &pResLen[0U]);

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
