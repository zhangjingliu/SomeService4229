#include "uds_user.h"
#include "SID37_RequestTransferExit.h"
#include "SID37_RequestTransferExitCfg.h"

/*************************************************************************/
/*
Function:		void SID_RTE_Analysis(uint8 *ui8_pInd, uint16 ui16_IndLen)

Description:

Parameters: 	ui8_pInd
				ui16_IndLen

Return:       	void

Return Values:
*/
void SID_RTE_Analysis(uint8_t *ui8_pInd, uint16_t ui16_IndLen)
{
	Uds_Dcm_Info.Cur_Task = UDS_TASK_SID_RTE;
}

/*************************************************************************/
/*
Function:		boolean SID_RTE_Appl_Deal(uint8_t *ui8_pInd,
				uint8_t *ui8_pRes, uint16_t *ui16_pResLen)

Description:

Parameters: 	ui8_pInd
				ui8_pRes
				ui16_pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RTE_Appl_Deal(uint8_t *ui8_pInd, uint8_t *ui8_pRes, uint32_t *ui16_pResLen)
{
	boolean	b_Return;

	b_Return = SID_RTE_Callback(&ui8_pInd[0U], &ui8_pRes[0U], &ui16_pResLen[0U]);

	return b_Return;
}
