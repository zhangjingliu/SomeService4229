#include "SID85_ControlDTCSettingCfg.h"
/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_CDTCS_SUBID_ON_Callback(uint8_t *u8_pRes, uint32_t *pResLen);

boolean SID_CDTCS_SUBID_OFF_Callback(uint8_t *u8_pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_CDTCS Uds_SID_CDTCS[UDS_SID_CDTCS_SUBFUNC_NUMBER] =
	{
		{0x01U,
		 SID_CDTCS_SUBID_ON_Callback},

		{0x02U,
		 SID_CDTCS_SUBID_OFF_Callback},
		{0x81U,
		 SID_CDTCS_SUBID_ON_Callback},

		{0x82U,
		 SID_CDTCS_SUBID_OFF_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void UdsFunc_SID_CDTCS_SUBID_ON_Callback
				(uint8_t *u8_pRes, uint32_t *pResLen)

Description:

Parameters: 	u8_pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_CDTCS_SUBID_ON_Callback(uint8_t *u8_pRes, uint32_t *pResLen)
{
	boolean ret;

	Uds_SID_CDTCS_Info.DTCSettingType = UDS_CDTCS_ON;

	pResLen[0U] = 0U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_CDTCS_SUBID_OFF_Callback
				(uint8_t *u8_pRes, uint32_t *pResLen)

Description:

Parameters: 	u8_pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_CDTCS_SUBID_OFF_Callback(uint8_t *u8_pRes, uint32_t *pResLen)
{
	boolean ret;

	Uds_SID_CDTCS_Info.DTCSettingType = UDS_CDTCS_OFF;

	pResLen[0U] = 0U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	ret = E_OK;

	return ret;
}
