#include "uds_user.h"
#include "SID10_DiagnosticSessionControlCfg.h"

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
Struct_Uds_SID_DSC_Info Uds_SID_DSC_Info;

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void ChangeSession_Init(void)

Description:

Parameters: 	void

Return:       	void
*/
void ChangeSession_Init(void)
{
	Uds_SID_ER_Info.HardResetFlag = false;
	Uds_SID_SA_Info.Security_Locked = true;
	Uds_SID_SA_Info.RequestSeedFlag = false;
}

/*************************************************************************/
/*
Function:		void SID_DSC_Analysis(uint8 *pInd, uint16 indLen)

Description:

Parameters: 	pInd
				indLen

Return:       	void
*/
void SID_DSC_Analysis(uint8_t *pInd, uint16_t indLen)
{
	uint8_t loop;
	uint8_t subID;

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < UDS_SID_DSC_SUBFUNC_NUMBER; loop++)
	{
		if ((subID & 0x7FU) == Uds_SID_DSC[loop].SubID)
		{
			break;
		}
	}

	if (loop < UDS_SID_DSC_SUBFUNC_NUMBER)
	{
		Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_DSC;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_SFNS;
	}
}

/*************************************************************************/
/*
Function:		boolean SID_DSC_Appl_Deal
				(uint8 *pInd, uint8 *pRes, uint32 *pResLen)

Description:

Parameters: 	pInd SubID
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_DSC_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop;
	uint8_t subID;
	boolean ret;

	if ((pInd[0U] & 0x80U) != 0U)
	{
		Uds_Response.SuppressPosRspBit = true;
	}

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < UDS_SID_DSC_SUBFUNC_NUMBER; loop++)
	{
		if (subID == Uds_SID_DSC[loop].SubID)
		{
			break;
		}
	}

	if (loop < UDS_SID_DSC_SUBFUNC_NUMBER)
	{
		ret = Uds_SID_DSC[loop].pFunc(&pRes[1U], &pResLen[0U]);

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
