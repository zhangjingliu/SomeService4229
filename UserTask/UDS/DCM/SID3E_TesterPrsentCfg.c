#include "SID3E_TesterPrsentCfg.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_TP_SUBID_ZSUBF_Callback(uint8_t *pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_TP Uds_SID_TP[UDS_SID_TP_SUBFUNC_NUMBER] =
	{
		{0x00U,
		 SID_TP_SUBID_ZSUBF_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		boolean SID_TP_SUBID_ZSUBF_Callback
				(uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_TP_SUBID_ZSUBF_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	pResLen[0U] = 0U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	ret = E_OK;

	return ret;
}
