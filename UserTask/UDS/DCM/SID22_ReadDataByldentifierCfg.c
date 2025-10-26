#include "SID22_ReadDataByldentifierCfg.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_RDBI_DID_F183_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F189_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F032_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F184_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F013_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F090_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F18A_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F18B_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F190_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F197_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F011_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F0F0_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F0F2_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F0F1_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F0F3_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F186_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F091_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F150_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F151_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F152_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F15b_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F0FE_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F160_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F161_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_D008_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F031_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F180_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F187_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F089_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F18C_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F162_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_RDBI_DID_F163_Callback(uint8_t *pRes, uint32_t *pResLen);


boolean SID_ECU_DID_4000_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_4100_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_5601_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_5602_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_560B_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_560C_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_5600_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_5604_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_560D_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_560E_Callback(uint8_t *pRes, uint32_t *pResLen);
boolean SID_ECU_DID_560F_Callback(uint8_t *pRes, uint32_t *pResLen);

/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_RDBI Uds_SID_RDBI[SID_RDBI_DID_NUMBER] =
	{
		{0xF032,SID_RDBI_DID_F032_Callback},{0xF183,SID_RDBI_DID_F183_Callback},
		{0xF031,SID_RDBI_DID_F031_Callback},{0xF180,SID_RDBI_DID_F180_Callback},
		{0xF184,SID_RDBI_DID_F184_Callback},{0xF187,SID_RDBI_DID_F187_Callback},
		{0xF189,SID_RDBI_DID_F189_Callback},{0xF089,SID_RDBI_DID_F089_Callback},
		{0xF013,SID_RDBI_DID_F013_Callback},{0xF090,SID_RDBI_DID_F090_Callback},
		{0xF18A,SID_RDBI_DID_F18A_Callback},{0xF18B,SID_RDBI_DID_F18B_Callback},
		{0xF18C,SID_RDBI_DID_F18C_Callback},{0xF190,SID_RDBI_DID_F190_Callback},
		{0xF197,SID_RDBI_DID_F197_Callback},{0xF011,SID_RDBI_DID_F011_Callback},
		{0xF0F0,SID_RDBI_DID_F0F0_Callback},{0xF0F2,SID_RDBI_DID_F0F2_Callback},
		{0xF0F1,SID_RDBI_DID_F0F1_Callback},{0xF0F3,SID_RDBI_DID_F0F3_Callback},
		{0xF186,SID_RDBI_DID_F186_Callback},{0xF091,SID_RDBI_DID_F091_Callback},
		{0xF150,SID_RDBI_DID_F150_Callback},{0xF151,SID_RDBI_DID_F151_Callback},
		{0xF152,SID_RDBI_DID_F152_Callback},{0xF15B,SID_RDBI_DID_F15b_Callback},
		{0xF0FE,SID_RDBI_DID_F0FE_Callback},{0xF160,SID_RDBI_DID_F160_Callback},
		{0xF161,SID_RDBI_DID_F161_Callback},{0xD008,SID_RDBI_DID_D008_Callback},
		{0xF162,SID_RDBI_DID_F162_Callback},{0xF163,SID_RDBI_DID_F163_Callback},
		{0x4000,SID_ECU_DID_4000_Callback},{0x4100,SID_ECU_DID_4100_Callback},
		{0x5600,SID_ECU_DID_5600_Callback},{0x5601,SID_ECU_DID_5601_Callback},
		{0x5602,SID_ECU_DID_5602_Callback},{0x5604,SID_ECU_DID_5604_Callback},
		{0x560B,SID_ECU_DID_560B_Callback},{0x560C,SID_ECU_DID_560C_Callback},
		{0x560D,SID_ECU_DID_560D_Callback},{0x560E,SID_ECU_DID_560E_Callback},
		{0x560F,SID_ECU_DID_560F_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
boolean SID_RDBI_DID_F183_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 12U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//标定零件号
//16 bytes
boolean SID_RDBI_DID_F031_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 16U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x16U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//标定版本号
//24 bytes
boolean SID_RDBI_DID_F032_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 24U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x01U;
	pRes[19U] = 0x01U;
	pRes[20U] = 0x01U;
	pRes[21U] = 0x01U;
	pRes[22U] = 0x01U;
	pRes[23U] = 0x24U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//BootLoader软件版本号
//24 bytes
boolean SID_RDBI_DID_F180_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 32U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x01U;
	pRes[19U] = 0x01U;
	pRes[20U] = 0x01U;
	pRes[21U] = 0x01U;
	pRes[22U] = 0x01U;
	pRes[23U] = 0x01U;
	pRes[24U] = 0x01U;
	pRes[25U] = 0x01U;
	pRes[26U] = 0x01U;
	pRes[27U] = 0x01U;
	pRes[28U] = 0x01U;
	pRes[29U] = 0x01U;
	pRes[30U] = 0x01U;
	pRes[31U] = 0x32U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//应用软件指纹信息
//19 bytes
boolean SID_RDBI_DID_F184_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 19U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x19U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//整车厂定义零件号
//16 bytes
boolean SID_RDBI_DID_F187_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 16U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x16U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//整车厂ECU软件版本号
//24 bytes
boolean SID_RDBI_DID_F189_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 24U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x01U;
	pRes[19U] = 0x01U;
	pRes[20U] = 0x01U;
	pRes[21U] = 0x01U;
	pRes[22U] = 0x01U;
	pRes[23U] = 0x24U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//整车厂ECU硬件版本号
//24 bytes
boolean SID_RDBI_DID_F089_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;
	uint16_t i;

	pResLen[0U] = 24U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x01U;
	pRes[19U] = 0x01U;
	pRes[20U] = 0x01U;
	pRes[21U] = 0x01U;
	pRes[22U] = 0x01U;
	pRes[23U] = 0x24U;
	for(i=0;i<900;i++)
	{
		pRes[i] = i;
	}
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//备份软件版本号
//24 bytes
boolean SID_RDBI_DID_F090_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 24U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x01U;
	pRes[19U] = 0x01U;
	pRes[20U] = 0x01U;
	pRes[21U] = 0x01U;
	pRes[22U] = 0x01U;
	pRes[23U] = 0x24U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//整车厂定义软件零件号
//16 bytes
boolean SID_RDBI_DID_F013_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 16U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x16U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//供应商代码
//3 bytes
boolean SID_RDBI_DID_F18A_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 3U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x03U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//ECU生产日期
//4 bytes
boolean SID_RDBI_DID_F18B_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 4U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x03U;
	pRes[3U]  = 0x04U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//ECU 序列号（批次号/流水号）
//36 bytes
boolean SID_RDBI_DID_F18C_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 36U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x01U;
	pRes[19U] = 0x01U;
	pRes[20U] = 0x01U;
	pRes[21U] = 0x01U;
	pRes[22U] = 0x01U;
	pRes[23U] = 0x01U;
	pRes[24U] = 0x01U;
	pRes[25U] = 0x01U;
	pRes[26U] = 0x01U;
	pRes[27U] = 0x01U;
	pRes[28U] = 0x01U;
	pRes[29U] = 0x01U;
	pRes[30U] = 0x01U;
	pRes[31U] = 0x32U;
	pRes[32U] = 0x32U;
	pRes[33U] = 0x32U;
	pRes[34U] = 0x20U;
	pRes[35U] = 0x36U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//车辆识别号
//17 bytes
boolean SID_RDBI_DID_F190_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 17U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x17U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//ECU名称
//10 bytes
boolean SID_RDBI_DID_F197_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 10U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x10U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//Vehicle Configuration 
//整车配置
//900bytes
boolean SID_RDBI_DID_F011_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;
	uint16_t i;

	pResLen[0U] = 900U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x01U;
	pRes[15U] = 0x01U;
	pRes[16U] = 0x01U;
	pRes[17U] = 0x01U;
	pRes[18U] = 0x01U;
	pRes[19U] = 0x01U;
	pRes[20U] = 0x01U;
	pRes[21U] = 0x01U;
	pRes[22U] = 0x01U;
	pRes[23U] = 0x24U;
	for(i=0;i<899;i++)
	{
		pRes[i] = 0xaa;
	}
	pRes[899U] = 0x90;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//当前运行分区信息
//1 bytes
boolean SID_RDBI_DID_F0F0_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//获取安装进度和结果
//2 bytes
boolean SID_RDBI_DID_F0F2_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 2U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x02U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//刷写尝试计数器
//4 bytes
boolean SID_RDBI_DID_F0F1_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 4U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x04U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//编程依赖检查成功计数器
//4 bytes
boolean SID_RDBI_DID_F0F3_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 4U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x04U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//当前诊断会话
//1 bytes
boolean SID_RDBI_DID_F186_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//故障码与故障码编号映射
//m*5+1 bytes
boolean SID_RDBI_DID_F091_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 6U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x06U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//诊断代理模式标志
//1 bytes
boolean SID_RDBI_DID_F150_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//安全访问模式标记
//1 bytes
boolean SID_RDBI_DID_F151_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//诊断授权文件有效状态
//1 bytes
boolean SID_RDBI_DID_F152_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//安全访问模式切换标记
//1 bytes
boolean SID_RDBI_DID_F15b_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//整车物料号
//15 bytes
boolean SID_RDBI_DID_F0FE_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 15U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;
	pRes[9U]  = 0x01U;
	pRes[10U] = 0x01U;
	pRes[11U] = 0x01U;
	pRes[12U] = 0x01U;
	pRes[13U] = 0x01U;
	pRes[14U] = 0x15U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//签名公钥状态
//1 bytes
boolean SID_RDBI_DID_F160_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//安全事件日志
//N bytes
boolean SID_RDBI_DID_F161_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//安全码(PIN)
//4 bytes
boolean SID_RDBI_DID_D008_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 4U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x04U;
	
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//当前应用软件版本hash值
//N bytes
boolean SID_RDBI_DID_F162_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//当前标定软件版本hash值
//N bytes
boolean SID_RDBI_DID_F163_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//CAN配置失效原因
//1 bytes
boolean SID_ECU_DID_4000_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//RMCU参数配置1
//4 bytes
boolean SID_ECU_DID_4100_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 4U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x04U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//蓄电池电压
//1 bytes
boolean SID_ECU_DID_5601_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 1U;
	pRes[0U]  = 0x01U;
	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//Dsp 版本
//9 bytes
boolean SID_ECU_DID_5602_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 9U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;
	pRes[4U]  = 0x01U;
	pRes[5U]  = 0x01U;
	pRes[6U]  = 0x01U;
	pRes[7U]  = 0x01U;
	pRes[8U]  = 0x01U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


//输出电压可调的升压电路温度
//2 bytes
boolean SID_ECU_DID_560B_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 2U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x02U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//classD powerAC芯片温度
//2 bytes
boolean SID_ECU_DID_560C_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 2U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x02U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//数字功放温度 1
//2 bytes
boolean SID_ECU_DID_560D_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 2U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x02U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//数字功放温度 2
//2 bytes
boolean SID_ECU_DID_560E_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 2U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x02U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//数字功放温度 3
//2 bytes
boolean SID_ECU_DID_560F_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 2U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x02U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}



//EAMP 参数配置
//4 bytes
boolean SID_ECU_DID_5600_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 4U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x01U;
	pRes[2U]  = 0x01U;
	pRes[3U]  = 0x01U;


	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}

//车辆配置
//2 bytes
boolean SID_ECU_DID_5604_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean b_Return;

	pResLen[0U] = 2U;
	pRes[0U]  = 0x01U;
	pRes[1U]  = 0x02U;

	Uds_Response.ResCode = UDS_RES_CODE_PR;

	b_Return = E_OK;

	return b_Return;
}


