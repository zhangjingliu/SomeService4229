#include "SID14_ClearDiagnosticInformation.h"
#include "SID14_ClearDiagnosticInformationCfg.h"


/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
void SID_CDTCI_Analysis(uint8_t *pInd, uint16_t indLen)
{
	uint8_t loop;
	uint32_t goDTC;

	goDTC = (uint32_t)pInd[0U] * 0x100U * 0x100U + (uint32_t)pInd[1U] * 0x100U + (uint32_t)pInd[2U];

	for (loop = 0U; loop < UDS_SID_CDTCI_GODTC_NUMBER; loop++)
	{
		if (goDTC == 0xFFFFFF)
		{
			break;
		}
	}

	if (loop < UDS_SID_CDTCI_GODTC_NUMBER)
	{
		Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_CDTCI;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR;
	}
}

/*************************************************************************/
/*
Function:		boolean SID_CDTCI_Appl_Deal
				(uint8_t *pInd, uint8_t *pRes, uint16_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_CDTCI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop;
	uint32_t goDTC;
	boolean ret;

	goDTC = (uint32_t)pInd[0U] * 0x100U * 0x100U + (uint32_t)pInd[1U] * 0x100U + (uint32_t)pInd[2U];

	for (loop = 0U; loop < UDS_SID_CDTCI_GODTC_NUMBER; loop++)
	{
		if (goDTC == 0xFFFFFF)
		{
			break;
		}
	}

	if (loop < UDS_SID_CDTCI_GODTC_NUMBER)
	{
		ret = Uds_SID_CDTCI[loop].pFunc(&pRes[3U], &pResLen[0U]);
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR;
		ret = E_OK;
	}
	return ret;
}

