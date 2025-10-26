#include "SID10_DiagnosticSessionControlCfg.h"
#include "SID11_ECUReset.h"
#include "Dcm_DrvCfg.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_DSC_SUBID_DS_Callback(uint8_t *pRes, uint32_t *pResLen);

boolean SID_DSC_SUBID_PRGS_Callback(uint8_t *pRes, uint32_t *pResLen);

boolean SID_DSC_SUBID_EXTDS_Callback(uint8_t *pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_DSC Uds_SID_DSC[UDS_SID_DSC_SUBFUNC_NUMBER] =
	{
		{0x01U,
		 SID_DSC_SUBID_DS_Callback},
		{0x81U,
		 SID_DSC_SUBID_DS_Callback},
		{0x02U,
		 SID_DSC_SUBID_PRGS_Callback},
		{0x03U,
		 SID_DSC_SUBID_EXTDS_Callback},
		{0x83U,
		 SID_DSC_SUBID_EXTDS_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void SID_DSC_SUBID_DS_Callback
				(uint8 *pRes, uint32_t *pResLen)

Description:

Parameters: 	pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_DSC_SUBID_DS_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	if (Uds_SID_DSC_Info.Active_Session == UDS_PROGRAMMING_SESSION_ACTIVE)
	{
		Uds_SID_DSC_Info.Active_Session = UDS_DEFAULT_SESSION_ACTIVE;
		pResLen[0U] = 4U;
		pRes[0U] = (uint8_t)(UDS_P2_SERVER_MAX / 0x100U);
		pRes[1U] = (uint8_t)(UDS_P2_SERVER_MAX);
		pRes[2U] = (uint8_t)(UDS_P2EX_SERVER_MAX / 0x100U);
		pRes[3U] = (uint8_t)(UDS_P2EX_SERVER_MAX);
		Uds_Response.ResCode = UDS_RES_CODE_PR;
	}
	else
	{
		ChangeSession_Init();
		Uds_SID_DSC_Info.Active_Session = UDS_DEFAULT_SESSION_ACTIVE;
		pResLen[0U] = 4U;
		pRes[0U] = (uint8_t)(UDS_P2_SERVER_MAX / 0x100U);
		pRes[1U] = (uint8_t)(UDS_P2_SERVER_MAX);
		pRes[2U] = (uint8_t)(UDS_P2EX_SERVER_MAX / 0x100U);
		pRes[3U] = (uint8_t)(UDS_P2EX_SERVER_MAX);
		Uds_Response.ResCode = UDS_RES_CODE_PR;
	}
	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_DSC_SUBID_PRGS_Callback
				(uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_DSC_SUBID_PRGS_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	/*编程会话02，功能地址下不响应,不执行*/
	if ((Uds_Indication.TA_Type[0U] & 0x55) != 0U)//0x55
	{
		if (Uds_SID_DSC_Info.Active_Session == UDS_DEFAULT_SESSION_ACTIVE)
		{
			Uds_Response.ResCode = UDS_RES_CODE_SFNSIAS;
		}
		else
		{
			ChangeSession_Init();
			Uds_SID_DSC_Info.Active_Session = UDS_PROGRAMMING_SESSION_ACTIVE;
			pResLen[0U] = 4U;
			pRes[0U] = (uint8_t)(UDS_P2_SERVER_MAX / 0x100U);
			pRes[1U] = (uint8_t)(UDS_P2_SERVER_MAX);
			pRes[2U] = (uint8_t)(UDS_P2EX_SERVER_MAX / 0x100U);
			pRes[3U] = (uint8_t)(UDS_P2EX_SERVER_MAX);
			Uds_Response.ResCode = UDS_RES_CODE_PR;
		}
	}
	else
	{
		NOP();
	}

	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_DSC_SUBID_EXTDS_Callback
				(uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_DSC_SUBID_EXTDS_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	if (Uds_SID_DSC_Info.Active_Session == UDS_PROGRAMMING_SESSION_ACTIVE)
	{
		Uds_Response.ResCode = UDS_RES_CODE_SFNSIAS;
	}
	else
	{
		ChangeSession_Init();
		Uds_SID_DSC_Info.Active_Session = UDS_EXTENDED_SESSION_ACTIVE;
		pResLen[0U] = 4U;
		pRes[0U] = (uint8_t)(UDS_P2_SERVER_MAX / 0x100U);
		pRes[1U] = (uint8_t)(UDS_P2_SERVER_MAX);
		pRes[2U] = (uint8_t)(UDS_P2EX_SERVER_MAX / 0x100U);
		pRes[3U] = (uint8_t)(UDS_P2EX_SERVER_MAX);
		Uds_Response.ResCode = UDS_RES_CODE_PR;
	}

	ret = E_OK;

	return ret;
}
