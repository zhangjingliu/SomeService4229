#include "SID2E_WriteDataByldentifierCfg.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_WDBI_DID_F198_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_WDBI Uds_SID_WDBI[UDS_SID_WDBI_DID_NUMBER] =
	{
		{0xF198U,
		 (2U + 10U),
		 SID_WDBI_DID_F198_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void SID_WDBI_DID_F198_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_WDBI_DID_F198_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	/*ToDo*/
	pResLen[0U] = 0U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	ret = E_OK;

	return ret;
}
