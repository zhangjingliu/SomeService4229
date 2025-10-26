#include "SID11_ECUResetCfg.h"
#include "bsp_debug_uart.h"
#include "bsp_canfd1.h"


/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_ER_SUBID_HR_Callback(uint8_t *pRes, uint32_t *pResLen);

boolean SID_ER_SUBID_KeyR_Callback(uint8_t *pRes, uint32_t *pResLen);

boolean SID_ER_SUBID_SR_Callback(uint8_t *pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_ER Uds_SID_ER[UDS_SID_ER_SUBFUNC_NUMBER] =
	{
		{0x01U,
		 SID_ER_SUBID_HR_Callback},
		{0x02U,
		 SID_ER_SUBID_KeyR_Callback},
		{0x03U,
		 SID_ER_SUBID_SR_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		boolean USID_ER_SUBID_HR_Callback
				(uint8_t *u8_pRes, uint32_t *pResLen)

Description:

Parameters: 	u8_pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_ER_SUBID_HR_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	/*Reset type 看门狗复位方式*/
	Uds_SID_ER_Info.HardResetFlag = true;
	Uds_Response.ResCode = UDS_RES_CODE_PR;
	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		boolean SID_ER_SUBID_KeyR_Callback
				(uint8_t *u8_pRes, uint16_t *pResLen)

Description:

Parameters: 	u8_pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_ER_SUBID_KeyR_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	/*Reset type 芯片复位管脚*/
//	HLI_Dio_WritePin(DIO_CHANNEL_D_0, 1);
	Uds_Response.ResCode = UDS_RES_CODE_PR;
	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		boolean SID_ER_SUBID_SR_Callback
				(uint8_t *u8_pRes, uint32_t *pResLen)

Description:

Parameters: 	u8_pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_ER_SUBID_SR_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	/*Reset type*/
	Uds_SID_ER_Info.HardResetFlag = true;

	//	HLI_Mcu_Reset();
	Uds_Response.ResCode = UDS_RES_CODE_PR;
	ret = E_OK;

	return ret;
}
