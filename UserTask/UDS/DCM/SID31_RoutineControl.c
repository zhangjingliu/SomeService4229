#include "SID31_RoutineControl.h"
#include "SID31_RoutineControlCfg.h"

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void SID_RC_Analysis(uint8_t *pInd, uint16_t ui16_IndLen)

Description:

Parameters: 	pInd
				ui16_IndLen

Return:       	void
*/
void SID_RC_Analysis(uint8_t *pInd, uint16_t ui16_IndLen)
{
	uint8_t loop;
	uint8_t subID;

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < SID_RC_SUBFUNC_NUMBER; loop++)
	{
		if ((subID & 0x7FU) == Uds_SID_RC[loop].SubID)
		{
			break;
		}
	}
	if (loop < SID_RC_SUBFUNC_NUMBER)
	{
		Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_RC;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_SFNS;
	}
}

/*************************************************************************/
/*
Function:		boolean UdsFunc_SID_RC_Appl_Deal
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RC_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop;
	uint8_t subID;
	boolean ret;

	if ((pInd[0U] & 0x80U) != 0U)
	{
		Uds_Response.SuppressPosRspBit = true;
	}

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < SID_RC_SUBFUNC_NUMBER; loop++)
	{
		if (subID == Uds_SID_RC[loop].SubID)
		{
			break;
		}
	}

	if (loop < SID_RC_SUBFUNC_NUMBER)
	{
		ret = Uds_SID_RC[loop].pFunc(&pInd[1U], &pRes[1U], &pResLen[0U]);

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
