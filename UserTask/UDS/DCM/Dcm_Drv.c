#include "Tp_Can_Drv.h"
#include "Dcm_Drv.h"
#include "uds_user.h"
#include "bsp_debug_uart.h"
#include "bsp_canfd1.h"


/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
Struct_Uds_Dcm_Info Uds_Dcm_Info;
Struct_Uds_Indication Uds_Indication;
Struct_Uds_Response Uds_Response;

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
void UdsFunc_Init(void)
{
	/*TP层数据给到UDS层*/
	Uds_Indication.TA_Type = &N_USData_Indication.N_TAtype;
	Uds_Indication.MsgData = N_USData_Indication.MsgData;
	Uds_Indication.Length = &N_USData_Indication.Length;
	Uds_Indication.Result = &N_USData_Indication.N_Result;

	/*UDS层响应数据给到TP层*/
	Uds_Response.ResCode = UDS_RES_CODE_INVALID;
	Uds_Response.MsgData = N_USData_Request.MsgData;
	Uds_Response.Length = &N_USData_Request.Length;

	Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
	Uds_Dcm_Info.S3_Timer = UDS_S3_SERVER_MAX;

	/*默认会话为1*/
	Uds_SID_DSC_Info.Active_Session = UDS_DEFAULT_SESSION_ACTIVE;

	/*默认安硬件复位是关闭*/
	Uds_SID_ER_Info.HardResetFlag = false;

	/*bit12:1是可接收 0是不可接收  bit18:1是可发送  0是不可发送  bit1-0: 1是应用报文，2是网络报文， 3：所有报文*/
	Uds_SID_CC_Info.CommuCtrlFlag = UDS_EN_RX_TX_NWMCM_NCM;

	/*默认安全访问是开启*/
	Uds_SID_SA_Info.Security_Locked = true;

	/*默认请求Seed是无效*/
	Uds_SID_SA_Info.RequestSeedFlag = false;

	Uds_SID_SA_Info.FailCount = 0U;

	/*存储的FailCount!=0时，10ms后清零*/
	if (Uds_SID_SA_Info.FailCount != 0)
	{
		Uds_SID_SA_Info.AccessDelay = 60000 * UDS_MS_MULTI_FACTOR;
	}
	else
	{
		Uds_SID_SA_Info.AccessDelay = 0U;
	}

	Uds_SID_TP_Info.TesterPresentFlag = false;
}

/*************************************************************************/
/*
Function:		void UdsFunc_PDU_Analysis(void)

Description:

Parameters: 	void

Return:       	void
*/
void UdsFunc_PDU_Analysis(void)
{
	uint8_t loop;

	if (Uds_Indication.Result[0U] == TP_N_OK)
	{
		Uds_Indication.Result[0U] = TP_N_PENDING;
		Uds_SID_TP_Info.TesterPresentFlag = true;		 /*成功收到一帧诊断帧，b_TesterPresentFlag置起*/
		Uds_Dcm_Info.S3_Timer = UDS_S3_SERVER_MAX;		 /*仅用于非默认会话模式，在S3Server计时*/
		Uds_Indication.SID = Uds_Indication.MsgData[0U]; /*Server ID*/

		for (loop = 0U; loop < UDS_SID_NUMBER; loop++)
		{
			if (Uds_Indication.SID == Uds_Cfg_Info[loop].SID)
			{
				break;
			}
		}
		/*General server response behaviour*/
		if (loop < UDS_SID_NUMBER)
		{
			/* SID 在物理或者功能地址下是否支持*/
			if ((Uds_Indication.TA_Type[0U] & Uds_Cfg_Info[loop].Addr_Support) != 0U)
			{
				/* SID 在当前会话下是否支持*/
				if ((Uds_SID_DSC_Info.Active_Session & Uds_Cfg_Info[loop].Session_Support) != 0U)
				{
					/* SID 是否需要过安全密钥*/
					if ((Uds_Cfg_Info[loop].Security_En == false) || (Uds_SID_SA_Info.Security_Locked == false))
					{
						/* SID 报文长度是否超范围*/
						if ((Uds_Indication.Length[0U] >= Uds_Cfg_Info[loop].DL_Min) && (Uds_Indication.Length[0U] <= Uds_Cfg_Info[loop].DL_Max))
						{
							/*默认没帧报文不做响应抑制，服务中处理*/
							Uds_Response.SuppressPosRspBit = false;
							Uds_Cfg_Info[loop].SidFunc_Callback(&Uds_Indication.MsgData[1U], (Uds_Indication.Length[0U] - 1U));
						}
						else
						{
							Uds_Response.ResCode = UDS_RES_CODE_IMLOIF;
						}
					}
					else
					{
						Uds_Response.ResCode = UDS_RES_CODE_SAD;
					}
				}
				else
				{
					Uds_Response.ResCode = UDS_RES_CODE_SNSIAS;
				}
			}
			else
			{
				NOP();
			}
		}
		else
		{
			Uds_Response.ResCode = UDS_RES_CODE_SNS;
		}
	}
	/*服务器的定时参数：仅用于非默认会话模式，在S3Server 时间内，
	 * 如果服务器没有接收到任何诊断请求报文，则退出非默认会话模式，
	 * 返回默认会话模式*/
	if ((Uds_SID_DSC_Info.Active_Session == UDS_EXTENDED_SESSION_ACTIVE) && (Uds_Response.Length[0U] == 0U))
	{
		if (Uds_Dcm_Info.S3_Timer > 0U)
		{
			Uds_Dcm_Info.S3_Timer--;
		}
		else
		{
			Uds_SID_TP_Info.TesterPresentFlag = false;
			ChangeSession_Init();
			Uds_SID_DSC_Info.Active_Session = UDS_DEFAULT_SESSION_ACTIVE;
			//HLI_Mcu_Reset();
		}
	}
	else if ((Uds_SID_DSC_Info.Active_Session == UDS_PROGRAMMING_SESSION_ACTIVE) && (Uds_Response.Length[0U] == 0U))
	{
		if (Uds_Dcm_Info.S3_Timer > 0U)
		{
			Uds_Dcm_Info.S3_Timer--;
		}
		else
		{

			ChangeSession_Init();
			Uds_SID_DSC_Info.Active_Session = UDS_DEFAULT_SESSION_ACTIVE;
			//HLI_Mcu_Reset();
		}
	}
}

/*************************************************************************/
/*
Function:		void UdsFunc_Receiver_Appl_Deal(void)

Description:

Parameters: 	void

Return:       	void
*/
void UdsFunc_Receiver_Appl_Deal(void)
{
	uint8_t ret;

	switch (Uds_Dcm_Info.Cur_Task)
	{
	case UDS_TASK_IDLE:
	{
		break;
	}

	case UDS_TASK_SID_DSC:
	{
		ret = SID_DSC_Appl_Deal(&Uds_Indication.MsgData[1U],
								&Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_ER:
	{
		ret = SID_ER_Appl_Deal(&Uds_Indication.MsgData[1U],
							   &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_SA:
	{
		ret = SID_SA_Appl_Deal(&Uds_Indication.MsgData[1U],
							   &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_TP:
	{
		ret = SID_TP_Appl_Deal(&Uds_Indication.MsgData[1U],
							   &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_RDBI:
	{
		ret = SID_RDBI_Appl_Deal(&Uds_Indication.MsgData[1U],
								 &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_WDBI:
	{
		ret = SID_WDBI_Appl_Deal(&Uds_Indication.MsgData[1U],
								 &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_RC:
	{
		ret = SID_RC_Appl_Deal(&Uds_Indication.MsgData[1U],
							   &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_RD:
	{
		ret = SID_RD_Appl_Deal(&Uds_Indication.MsgData[1U],
				&Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if(ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_TD:
	{
		ret = SID_TD_Appl_Deal(&Uds_Indication.MsgData[1U],
				(Uds_Indication.Length[0U] - 1U), &Uds_Response.MsgData[1U],
				&Uds_Response.Length[0U]);

		if(ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_RTE:
	{
		ret = SID_RTE_Appl_Deal(&Uds_Indication.MsgData[1U],
				&Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if(ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_CC:
	{
		ret = SID_CC_Appl_Deal(&Uds_Indication.MsgData[1U],
							   &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_CDTCS:
	{
		ret = SID_CDTCS_Appl_Deal(&Uds_Indication.MsgData[1U],
								  &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_CDTCI:
	{
		ret = SID_CDTCI_Appl_Deal(&Uds_Indication.MsgData[1U],
								  &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	case UDS_TASK_SID_RDTCI:
	{
		ret = SID_RDTCI_Appl_Deal(&Uds_Indication.MsgData[1U],
								  &Uds_Response.MsgData[1U], &Uds_Response.Length[0U]);

		if (ret == E_OK)
		{
			Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
		}
		break;
	}

	default:
	{
		Uds_Dcm_Info.Cur_Task = UDS_TASK_IDLE;
	}
	break;
	}
}

/*************************************************************************/
/*
Function:		void UdsFunc_Receiver_Response(void)

Description:

Parameters: 	void

Return:       	void
*/
void UdsFunc_Receiver_Response(void)
{
	if (Uds_Response.ResCode != UDS_RES_CODE_INVALID)
	{
		if ((Uds_Indication.TA_Type[0U] == UDS_ADDR_TYPE_FUNC) && ((Uds_Response.ResCode == UDS_RES_CODE_SNS) || (Uds_Response.ResCode == UDS_RES_CODE_SFNS)
				|| (Uds_Response.ResCode == UDS_RES_CODE_SFNSIAS) || (Uds_Response.ResCode == UDS_RES_CODE_SNSIAS) || (Uds_Response.ResCode == UDS_RES_CODE_ROOR)))
		{
			Uds_Response.Length[0U] = 0U;
		}
		else
		{
			if (Uds_Response.ResCode == UDS_RES_CODE_PR)
			{
				if (Uds_Response.SuppressPosRspBit == true)
				{
					Uds_Response.SuppressPosRspBit = false;
					Uds_Response.Length[0U] = 0U;
				}
				else
				{
					Uds_Response.MsgData[0U] = Uds_Indication.SID + 0x40U;
					Uds_Response.Length[0U] += 1U;
				}
			}
			else
			{
				Uds_Response.Length[0U] = 3U;
				Uds_Response.MsgData[0U] = 0x7FU;
				Uds_Response.MsgData[1U] = Uds_Indication.SID;
				Uds_Response.MsgData[2U] = Uds_Response.ResCode;
			}
		}

		Uds_Response.ResCode = UDS_RES_CODE_INVALID;
	}
}

void UdsFunc_Task(void)
{
	UdsFunc_PDU_Analysis();
	UdsFunc_Receiver_Appl_Deal();
	UdsFunc_Receiver_Response();
}

void UdsFunc_Delay1ms_Handle(void)
{
	if (Uds_SID_SA_Info.AccessDelay != 0U)
	{
		Uds_SID_SA_Info.AccessDelay--;
		if (Uds_SID_SA_Info.AccessDelay == 0U)
		{
			if (Uds_SID_SA_Info.FailCount != 0U)
			{
				Uds_SID_SA_Info.FailCount = 0U;
				/*存储安全访问错误计数 ToDo*/

			}
		}
	}
}
