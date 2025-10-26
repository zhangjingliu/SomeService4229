#include "SID28_CommunicationControlCfg.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_CC_SUBID_ERXTX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

boolean SID_CC_SUBID_ERXDTX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

boolean SID_CC_SUBID_DRXETX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

boolean SID_CC_SUBID_DRXTX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_CC Uds_SID_CC[UDS_SID_CC_SUBFUNC_NUMBER] =
	{
		{0x00U,
		 SID_CC_SUBID_ERXTX_Callback},

		{0x80U,
		 SID_CC_SUBID_ERXTX_Callback},

		{0x01U,
		 SID_CC_SUBID_ERXDTX_Callback},

		{0x81U,
		 SID_CC_SUBID_ERXDTX_Callback},

		{0x02U,
		 SID_CC_SUBID_DRXETX_Callback},

		{0x82U,
		 SID_CC_SUBID_DRXETX_Callback},

		{0x03U,
		 SID_CC_SUBID_DRXTX_Callback},

		{0x83U,
		 SID_CC_SUBID_DRXTX_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/

/*************************************************************************/
/*
Function:		void SID_CC_SUBID_ERXTX_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_CC_SUBID_ERXTX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t commuType; /*01:应用报文，02:网络报文，03:应用报文+网络报文*/

	commuType = pInd[0U];

	switch (commuType)
	{
	case 1:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_EN_RX_TX_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 2:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_EN_RX_TX_NWMCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 3:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_EN_RX_TX_NWMCM_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}

	default:
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR; /*requestOutOfRange*/
		break;
	}
	}

	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_CC_SUBID_ERXDTX_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_CC_SUBID_ERXDTX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t commuType;

	commuType = pInd[0U];

	switch (commuType)
	{
	case 1:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_EN_RX_DIS_TX_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 2:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_EN_RX_DIS_TX_NWMCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 3:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_EN_RX_DIS_TX_NWMCM_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}

	default:
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR; /*requestOutOfRange*/
		break;
	}
	}

	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_CC_SUBID_DRXETX_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_CC_SUBID_DRXETX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t commuType;

	commuType = pInd[0U];

	switch (commuType)
	{
	case 1:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_DIS_RX_EN_TX_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 2:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_DIS_RX_EN_TX_NWMCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 3:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_DIS_RX_EN_TX_NWMCM_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}

	default:
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR; /*requestOutOfRange*/
		break;
	}
	}

	ret = E_OK;

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_CC_SUBID_DRXTX_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_CC_SUBID_DRXTX_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t commuType;

	commuType = pInd[0U];

	switch (commuType)
	{
	case 1:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_DIS_RX_TX_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 2:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_DIS_RX_TX_NWMCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}
	case 3:
	{
		Uds_SID_CC_Info.CommuCtrlFlag = UDS_DIS_RX_TX_NWMCM_NCM;
		pResLen[0U] = 0U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		break;
	}

	default:
	{
		Uds_Response.ResCode = UDS_RES_CODE_ROOR; /*requestOutOfRange*/
		break;
	}
	}

	ret = E_OK;
	return ret;
}
