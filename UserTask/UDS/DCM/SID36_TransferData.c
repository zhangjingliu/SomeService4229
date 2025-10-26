#include "uds_user.h"
#include "SID36_TransferData.h"
#include "SID36_TransferDataCfg.h"

/*************************************************************************/
/*
Function:		void SID_TD_Analysis(uint8 *ui8_pInd, uint16 ui16_IndLen)

Description:

Parameters: 	ui8_pInd
				ui16_IndLen

Return:       	void

Return Values:
*/
void SID_TD_Analysis(uint8_t *pInd, uint16_t indLen)
{
	Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_TD;
}

/*************************************************************************/
/*
Function:		boolean SID_TD_Appl_Deal(uint8_t *pInd, uint16_t indLen, uint8_t *pRes, uint16_t *pResLen)

Description:

Parameters: 	pInd
				IndLen
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK

Remarks:

Example:
*/
boolean SID_TD_Appl_Deal(uint8_t *pInd, uint16_t indLen, uint8_t *pRes, uint32_t *pResLen)
{
	boolean	b_Return;

	b_Return = SID_TD_Callback(&pInd[0U], indLen, &pRes[0U], &pResLen[0U]);

	return b_Return;
}
