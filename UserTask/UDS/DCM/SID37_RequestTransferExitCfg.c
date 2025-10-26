#include "Dcm_DrvCfg.h"
#include "SID34_RequestDownloadCfg.h"
#include "SID36_TransferDataCfg.h"
#include "SID37_RequestTransferExitCfg.h"


/*************************************************************************/
/*
Function:		void SID_RTE_Callback
				(uint8_t *ui8_pInd, uint8_t *ui8_pRes, uint16_t *ui16_pResLen)

Description:

Parameters: 	ui8_pInd
				ui8_pRes
				ui16_pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RTE_Callback(uint8_t *ui8_pInd, uint8_t *ui8_pRes, uint32_t *ui16_pResLen)
{
	boolean	b_Return;

	if(st_Uds_SID_TD_Info.b_TransferDataFlag == true)
	{
		st_Uds_SID_RD_Info.b_ReqDownloadFlag = false;

		ui16_pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_RSE;
	}

	b_Return = E_OK;

	return	b_Return;
}
