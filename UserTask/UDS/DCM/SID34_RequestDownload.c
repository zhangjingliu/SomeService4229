#include "uds_user.h"
#include "SID34_RequestDownload.h"
#include "SID34_RequestDownloadCfg.h"
/*************************************************************************/
/*
Function:		void SID_RD_Analysis(uint8 *ui8_pInd, uint16 ui16_IndLen)

Description:

Parameters: 	ui8_pInd
				ui16_IndLen

Return:       	void

Return Values:
*/
void SID_RD_Analysis(uint8_t *pInd, uint16_t indLen)
{
	Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_RD;
}

/*************************************************************************/
/*
Function:		boolean SID_RD_Appl_Deal
				(uint8 *ui8_pInd, uint8 *ui8_pRes, uint16 *ui16_pResLen)

Description:

Parameters: 	ui8_pInd
				ui8_pRes
				ui16_pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RD_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	ret = SID_RD_Callback(&pInd[0U], &pRes[0U], &pResLen[0U]);

	return ret;
}
