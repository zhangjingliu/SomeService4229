#include "SID2E_WriteDataByldentifier.h"
#include "SID2E_WriteDataByldentifierCfg.h"

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void SID_WDBI_Analysis(uint8_t *pInd, uint16_t indLen)

Description:

Parameters: 	pInd
				indLen

Return:       	void
*/
void SID_WDBI_Analysis(uint8_t *pInd, uint16_t indLen)
{
	uint8_t loop;
	uint16_t did;

	did = (uint16_t)pInd[0U] * 0x100U + pInd[1U];

	for (loop = 0U; loop < UDS_SID_WDBI_DID_NUMBER; loop++)
	{
		if (did == Uds_SID_WDBI[loop].DID)
		{
			break;
		}
	}

	if (loop < UDS_SID_WDBI_DID_NUMBER)
	{
		if (indLen == Uds_SID_WDBI[loop].DataLen)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_WDBI;
		}
		else
		{
			Uds_Response.ResCode = UDS_RES_CODE_IMLOIF;
		}
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR;
	}
}

/*************************************************************************/
/*
Function:		boolean SID_WDBI_Appl_Deal
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_WDBI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop;
	uint16_t did;
	boolean ret;

	did = (uint16_t)pInd[0U] * 0x100U + pInd[1U];

	for (loop = 0U; loop < UDS_SID_WDBI_DID_NUMBER; loop++)
	{
		if (did == Uds_SID_WDBI[loop].DID)
		{
			break;
		}
	}

	if (loop < UDS_SID_WDBI_DID_NUMBER)
	{
		ret = Uds_SID_WDBI[loop].pFunc(&pInd[2U], &pRes[2U], &pResLen[0U]);

		if (Uds_Response.ResCode == UDS_RES_CODE_PR)
		{
			pRes[0U] = (uint8_t)(did / 0x100U);
			pRes[1U] = (uint8_t)(did);
			pResLen[0U] += 2U;
		}
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR;
		ret = E_OK;
	}

	return ret;
}
