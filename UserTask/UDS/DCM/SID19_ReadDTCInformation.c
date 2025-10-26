#include "SID19_ReadDTCInformation.h"
#include "SID19_ReadDTCInformationCfg.h"

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
void SID_RDTCI_Analysis(uint8_t *pInd, uint16_t indLen)
{
	uint8_t loop;
	uint8_t subID;

	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < UDS_SID_RDTCI_SUBFUNC_NUMBER; loop++)
	{
		if ((subID & 0x7FU) == Uds_SID_RDTCI[loop].SubID)
		{
			break;
		}
	}

	if (loop < UDS_SID_RDTCI_SUBFUNC_NUMBER)
	{
		Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_RDTCI;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR;
	}
}

/*************************************************************************/
/*
Function:		boolean SID_RDTCI_Appl_Deal
				(uint8_t *pInd, uint8_t *pRes, uint16_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RDTCI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	uint8_t loop;
	uint8_t subID;
	boolean ret;

	if ((pInd[0U] & 0x80U) != 0U)
	{
		Uds_Response.SuppressPosRspBit = true;
	}
	subID = pInd[0U] & 0x7FU;

	for (loop = 0U; loop < UDS_SID_RDTCI_SUBFUNC_NUMBER; loop++)
	{
		if (subID == Uds_SID_RDTCI[loop].SubID)
		{
			break;
		}
	}

	if (loop < UDS_SID_RDTCI_SUBFUNC_NUMBER)
	{
		ret = Uds_SID_RDTCI[loop].pFunc(&pInd[1U], &pRes[1U], &pResLen[0U]);

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
//
//	goDTC = (uint32_t)pInd[0U] * 0x100U * 0x100U + (uint32_t)pInd[1U] * 0x100U + (uint32_t)pInd[2U];
//
//	for (loop = 0U; loop < 6; loop++)
//	{
//		if (goDTC == 0xFFFFFF)
//		{
//			break;
//		}
//	}
//
//	if (loop < 6)
//	{
//		ret = Uds_SID_CDTCI[loop].pFunc(&pRes[3U], &pResLen[0U]);
//	}
//	else
//	{
//		Uds_Response.ResCode = UDS_RES_CODE_ROOR;
//		ret = E_OK;
//	}
	return ret;
}
