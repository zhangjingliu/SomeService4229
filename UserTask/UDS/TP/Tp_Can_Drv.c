#include "uds_main.h"
#include "uds_user.h"
#include "Tp_Can_Drv.h"

/******************************************************************************
 *                      Macro Definitions                                      *
 ******************************************************************************/
#define max(a, b) ((a) > (b) ? (a) : (b))

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
uint8_t Tp_Rx_Buf_From_Drv[TP_APPL_DL_MAX]; /*为指针赋值，防止空指针*/
uint8_t Tp_Tx_Buf_To_Drv[TP_APPL_DL_MAX]; /*为指针赋值，防止空指针*/

uint32_t Tp_Rx_CAN_ID;			/*TP Receive CAN ID*/
uint8_t Tp_Frame_AddrType;		/*TP Receive AddrType*/
uint32_t Tp_CAN_DL;				/*TP CAN data Length*/
uint32_t Tp_RX_DL;				/*TP RX data Length*/
uint32_t Tp_TX_DL;				/*TP TX data Length*/
uint8_t Tp_Rx_Buf[TP_FRAME_DL]; /*TP Receive Buf*/
boolean Tp_Rx_NewData_Valid;	/*Tp Receive Success flag */

Struct_Tp_Receiver Tp_Receiver; /*TP Receiver*/
Struct_Tp_Sender Tp_Sender;		/*TP Sender*/

Struct_N_USData_FF_Indication N_USData_FF_Indication; /*接收单帧、连续帧处理结构体*/
Struct_N_USData_Indication N_USData_Indication;		  /*接收TP层处理结构体*/
Struct_N_USData_Request N_USData_Request;			  /*正响应发送TP层处理结构体*/
Struct_N_USData_Confirm N_USData_Confirm;			  /*响应结果：正响应、负响应*/


HLI_Canfd_MessageType Pdu_Uds_Response;

uint8_t u8_Tp_Task_Dir_FSM; /*半双工模式*/
/******************************************************************************
 *                      Internal function definitions                 *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void TpFunc_Receiver_Frame_Tx_Buf_Init(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Receiver_Frame_Tx_Buf_Init(void)
{
	uint16_t loop;

	for (loop = 0U; loop < Tp_CAN_DL; loop++)
	{
		Tp_Receiver.Frame_Tx_Buf[loop] = 0x00U;
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_Sender_Frame_Tx_Buf_Init(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Sender_Frame_Tx_Buf_Init(void)
{
	uint16_t loop;

	for (loop = 0U; loop < Tp_CAN_DL; loop++)
	{
		Tp_Sender.Frame_Tx_Buf[loop] = 0x00U;
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_Receiver_SF_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Receiver_SF_PDU_Handle(void)
{
	uint16_t loop;

	if (Tp_Receiver.ChannelState == CANTPRXSTATE_IDLE)
	{
		if (Tp_CAN_DL <= 8U)
		{
			N_USData_Indication.Length = Tp_Rx_Buf[0U] & 0x0FU; /*SF length*/
			/*ISO15765 9.6.2.2  SF_DL error handling*/
			if ((0U < N_USData_Indication.Length) && (N_USData_Indication.Length <= (Tp_CAN_DL - 1U)))
			{
				for (loop = 0U; loop < N_USData_Indication.Length; loop++)
				{
					N_USData_Indication.MsgData[loop] = Tp_Rx_Buf[TP_SF_DATA_FIELD_OFFSET + loop];
				}
				N_USData_Indication.N_TAtype = Tp_Frame_AddrType; /*ADDR TYPE*/
				N_USData_Indication.N_Result = TP_N_OK;
			}
			else
			{
				N_USData_Indication.N_Result = TP_N_ERROR;
			}
		}
		else
		{
			N_USData_Indication.Length = Tp_Rx_Buf[1U] & 0xFFU; /*SF length*/
			/*ISO15765 9.6.2.2  SF_DL error handling*/
			if ((0U < N_USData_Indication.Length) && (N_USData_Indication.Length <= 62U))
			{
				for (loop = 0U; loop < N_USData_Indication.Length; loop++)
				{
					N_USData_Indication.MsgData[loop] = Tp_Rx_Buf[TP_SF_DATA_FIELD_OFFSET_CANFD + loop];
				}
				N_USData_Indication.N_TAtype = Tp_Frame_AddrType; /*ADDR TYPE*/
				N_USData_Indication.N_Result = TP_N_OK;
			}
			else
			{
				N_USData_Indication.N_Result = TP_N_ERROR;
			}
		}
	}
	else
	{
		N_USData_Indication.N_Result = TP_N_UNEXP_PDU; /*TP_N_UNEXP_PDU*/
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_Receiver_FF_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Receiver_FF_PDU_Handle(void)
{
	uint16_t loop;

	if (Tp_Receiver.ChannelState == CANTPRXSTATE_IDLE)
	{
		Tp_RX_DL = max(8, Tp_CAN_DL);
		N_USData_FF_Indication.Length = ((Tp_Rx_Buf[0U] & 0x0FU) << 8) + Tp_Rx_Buf[1U];
		if (N_USData_FF_Indication.Length != 0U)
		{
			if (((Tp_RX_DL - 2U) <= N_USData_FF_Indication.Length) && (N_USData_FF_Indication.Length <= 0xFFFU))
			{
				Tp_Receiver.N_USData_Ind_Index = 0U;
				for (loop = 0U; loop < (Tp_RX_DL - 2U); loop++)
				{
					N_USData_Indication.MsgData[Tp_Receiver.N_USData_Ind_Index] = Tp_Rx_Buf[TP_FF_DATA_FIELD_OFFSET + loop];
					Tp_Receiver.N_USData_Ind_Index++;
				}
				/*ISO15765 9.6.4.3 that the SN of the first CF immediately following the FF shall be set to one*/
				Tp_Receiver.CF_SN = 1U;
				Tp_Receiver.Task_FSM = TP_TASK_FC_STATE;
				N_USData_FF_Indication.N_TAtype = Tp_Frame_AddrType;
				N_USData_Indication.N_Result = TP_N_PENDING;
			}
			else
			{
				N_USData_Indication.N_Result = TP_N_ERROR;
			}
		}
		else
		{
			N_USData_FF_Indication.Length = ((Tp_Rx_Buf[2U] & 0xFFU) << 24) + ((Tp_Rx_Buf[3U] & 0xFFU) << 16) + ((Tp_Rx_Buf[4U] & 0xFFU) << 8) + Tp_Rx_Buf[4U];
			if (N_USData_FF_Indication.Length > 4095U)
			{
				for (loop = 0U; loop < (Tp_RX_DL - 6U); loop++)
				{
					N_USData_Indication.MsgData[Tp_Receiver.N_USData_Ind_Index] = Tp_Rx_Buf[TP_FF_DATA_FIELD_OFFSET + loop];
					Tp_Receiver.N_USData_Ind_Index++;
				}
				/*ISO15765 9.6.4.3 that the SN of the first CF immediately following the FF shall be set to one*/
				Tp_Receiver.CF_SN = 1U;
				Tp_Receiver.Task_FSM = TP_TASK_FC_STATE;
				N_USData_FF_Indication.N_TAtype = Tp_Frame_AddrType;
				N_USData_Indication.N_Result = TP_N_PENDING;
			}
			else
			{
				N_USData_Indication.N_Result = TP_N_ERROR;
			}
		}
		Tp_Receiver.ChannelState = CANTPRXSTATE_WAITFORTXFC;
	}
	else
	{
		N_USData_Indication.N_Result = TP_N_UNEXP_PDU; /*TP_N_UNEXP_PDU*/
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_Receiver_CF_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Receiver_CF_PDU_Handle(void)
{
	uint16_t loop;

	if (Tp_Receiver.ChannelState == CANTPRXSTATE_WAITCF)
	{
		Tp_Receiver.Timing_N_Cr = TP_TIMING_VALUE_N_CR;	  /*N_Cr 接收方接收连续帧的等待时间*/
		if ((Tp_Rx_Buf[0U] & 0x0FU) == Tp_Receiver.CF_SN) /*CF帧 SN index号*/
		{
			Tp_Receiver.CF_SN++;
			/*ISO15765 2016-2 9.6.4*/

			if (Tp_Receiver.CF_SN > 15U)
			{
				Tp_Receiver.CF_SN = 0U;
			}
			if (TP_BLOCK_SIZE != 0U) /*Block Size*/
			{
				Tp_Receiver.BlockSize_Count++;
				if (Tp_Receiver.BlockSize_Count >= TP_BLOCK_SIZE) /*CF帧 BlockSize*/
				{
					Tp_Receiver.Task_FSM = TP_TASK_FC_STATE;
				}
			}
			for (loop = 0U; loop < (Tp_CAN_DL - 1U); loop++)
			{
				N_USData_Indication.MsgData[Tp_Receiver.N_USData_Ind_Index] = Tp_Rx_Buf[TP_CF_DATA_FIELD_OFFSET + loop];
				Tp_Receiver.N_USData_Ind_Index++;
				if (Tp_Receiver.N_USData_Ind_Index >= N_USData_FF_Indication.Length)
				{
					N_USData_Indication.Length = N_USData_FF_Indication.Length;
					N_USData_Indication.N_TAtype = Tp_Frame_AddrType;
					N_USData_Indication.N_Result = TP_N_OK;
					Tp_Receiver.ChannelState = CANTPRXSTATE_IDLE;
				}
				else
				{
//					Tp_Receiver.ChannelState = CANTPRXSTATE_WAITFORRXBUFFER;
				}
			}
		}
		else
		{
			/*ISO15765 2016-2 9.6.4.4 */
			N_USData_Indication.N_Result = TP_N_WRONG_SN;
		}
	}
	else
	{
		N_USData_Indication.N_Result = TP_N_UNEXP_PDU; /*TP_N_UNEXP_PDU*/
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_Receiver_FC_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Receiver_FC_PDU_Handle(void)
{
	/*	/*This is an optional service that can be replaced
	 * by implementation of fixed parameter values*/
	TpFunc_Receiver_Frame_Tx_Buf_Init();

	if (N_USData_FF_Indication.Length > TP_FF_DL_MAX)
	{
		Tp_Receiver.Frame_Tx_Buf[0U] = TP_N_PDU_TYPE_FC + TP_FC_FS_OVFLW;
		Tp_Receiver.ChannelState = CANTPRXSTATE_WAITFORTXFCOVERRUN;
	}
	else
	{
		Tp_Receiver.Frame_Tx_Buf[0U] = TP_N_PDU_TYPE_FC + TP_FC_FS_CTS;
		Tp_Receiver.ChannelState = CANTPRXSTATE_WAITCF;
	}

	Tp_Receiver.Frame_Tx_Buf[1U] = TP_BLOCK_SIZE;
//	Tp_Receiver.Frame_Tx_Buf[2U] = TP_STMIN;
	Tp_Receiver.Frame_Tx_Buf[2U] = TP_STMIN+1;//2024-10-21 Add the time of STMIN
	Tp_Receiver.Frame_Tx_NewData_Valid = true;
	Tp_Receiver.Timing_N_Ar = TP_TIMING_VALUE_N_AR; /*N_Ar*/

	Tp_Receiver.BlockSize_Count = 0U;
	Tp_Receiver.Task_FSM = TP_TASK_CF_STATE;
	Tp_Receiver.Timing_N_Cr = TP_TIMING_VALUE_N_CR; /*N_Cr*/
}

/*************************************************************************/
/*
Function:		void TpFunc_Receiver_Task(void)

Description: 	CAN_Receiver TP State machine

Parameters: 	void

Return:       	void
*/
static void TpFunc_Receiver_Task(void)
{
	if (Tp_Receiver.Frame_Tx_NewData_Valid == false) /*N_Ar数据链路层发送阶段*/
	{
		switch (Tp_Receiver.Task_FSM) /*任务任务状态*/
		{
		case TP_TASK_SF_STATE:
		case TP_TASK_FF_STATE:
		{
			if (Tp_Rx_NewData_Valid == true) /*接收有效帧֡*/
			{
				Tp_Rx_NewData_Valid = false;

				switch (Tp_Rx_Buf[0U] & 0xF0U) /*帧类型状态*/
				{
				case TP_N_PDU_TYPE_SF: /*Single Frame*/
				{
					TpFunc_Receiver_SF_PDU_Handle();
					break;
				}
				case TP_N_PDU_TYPE_FF: /*First Frame*/
				{
					TpFunc_Receiver_FF_PDU_Handle();
					break;
				}
				default:
				{
					/* do nothing */
					break;
				}
				}
			}
			break;
		}

		case TP_TASK_CF_STATE:
		{
			if (Tp_Rx_NewData_Valid == true)
			{
				Tp_Rx_NewData_Valid = false;

				switch (Tp_Rx_Buf[0U] & 0xF0U)
				{
				case TP_N_PDU_TYPE_SF:
				{
					TpFunc_Receiver_SF_PDU_Handle();
					break;
				}
				case TP_N_PDU_TYPE_FF:
				{
					TpFunc_Receiver_FF_PDU_Handle();
					break;
				}
				case TP_N_PDU_TYPE_CF:
				{
					TpFunc_Receiver_CF_PDU_Handle();
					break;
				}
				default:
				{
					if (Tp_Receiver.Timing_N_Cr != 0U)
					{
						Tp_Receiver.Timing_N_Cr--;
					}

					if (Tp_Receiver.Timing_N_Cr == 0U) /*Timing*/
					{
						N_USData_Indication.N_Result = TP_N_TIMEOUT_Cr; /*N_TIMEOUT_Cr*/
					}
					break;
				}
				}
			}
			else
			{
				if (Tp_Receiver.Timing_N_Cr != 0U)
				{
					Tp_Receiver.Timing_N_Cr--;
				}

				if (Tp_Receiver.Timing_N_Cr == 0U) /*Timing*/
				{
					N_USData_Indication.N_Result = TP_N_TIMEOUT_Cr; /*N_TIMEOUT_Cr*/
				}
			}
			break;
		}

		case TP_TASK_FC_STATE:
		{
			TpFunc_Receiver_FC_PDU_Handle();
			break;
		}

		default:
		{
			Tp_Receiver.Task_FSM = TP_TASK_SF_STATE;
			break;
		}
		}
	}
	else /*N_Ar*/
	{
		if (Tp_Receiver.Timing_N_Ar != 0U) /*等待数据链路层发送的时间*/
		{
			Tp_Receiver.Timing_N_Ar--;
		}

		if (Tp_Receiver.Timing_N_Ar == 0U) /*Timing*/
		{
			Tp_Receiver.Frame_Tx_NewData_Valid = false;
			N_USData_Indication.N_Result = TP_N_TIMEOUT_A; /*N_TIMEOUT*/
		}
	}

	if (N_USData_Indication.N_Result != TP_N_PENDING)
	{
		Tp_Receiver.Task_FSM = TP_TASK_SF_STATE;
		Tp_Receiver.ChannelState = CANTPRXSTATE_IDLE;
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_Send_SF_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Send_SF_PDU_Handle(void)
{
	uint16_t loop;
	TpFunc_Sender_Frame_Tx_Buf_Init();
	Tp_Sender.Frame_Tx_Buf[0U] = TP_N_PDU_TYPE_SF + N_USData_Request.Length;
	for (loop = 0U; loop < N_USData_Request.Length; loop++)
	{
		Tp_Sender.Frame_Tx_Buf[TP_SF_DATA_FIELD_OFFSET + loop] = N_USData_Request.MsgData[loop];
	}
	Tp_Sender.Frame_Tx_NewData_Valid = true;
	Tp_Sender.Timing_N_As = TP_TIMING_VALUE_N_AS;

	N_USData_Confirm.N_Result = TP_N_OK;
}

/*************************************************************************/
/*
Function:		void TpFunc_Send_FF_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Send_FF_PDU_Handle(void)
{
	uint16_t loop;
	TpFunc_Sender_Frame_Tx_Buf_Init();
	Tp_Sender.Frame_Tx_Buf[0U] = TP_N_PDU_TYPE_FF + (uint8_t)(N_USData_Request.Length / 0x100U);
	Tp_Sender.Frame_Tx_Buf[1U] = (uint8_t)N_USData_Request.Length;
	Tp_Sender.N_USData_Req_Index = 0U;
	for (loop = 0U; loop < (Tp_CAN_DL - 2U); loop++)
	{
		Tp_Sender.Frame_Tx_Buf[TP_FF_DATA_FIELD_OFFSET + loop] = N_USData_Request.MsgData[Tp_Sender.N_USData_Req_Index];
		Tp_Sender.N_USData_Req_Index++;
	}
	Tp_Sender.Frame_Tx_NewData_Valid = true;
	Tp_Sender.Timing_N_As = TP_TIMING_VALUE_N_AS;
	Tp_Sender.CF_SN = 1U;
	Tp_Sender.Task_FSM = TP_TASK_FC_STATE;
	Tp_Sender.Timing_N_Bs = TP_TIMING_VALUE_N_BS;
	N_USData_Confirm.N_Result = TP_N_PENDING;
}

/*************************************************************************/
/*
Function:		void TpFunc_Send_CF_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Send_CF_PDU_Handle(void)
{
	uint16_t loop;
	TpFunc_Sender_Frame_Tx_Buf_Init();
	Tp_Sender.Frame_Tx_Buf[0U] = TP_N_PDU_TYPE_CF + Tp_Sender.CF_SN;
	Tp_Sender.CF_SN++;
	if (Tp_Sender.CF_SN > 15U)
	{
		Tp_Sender.CF_SN = 0U;
	}

	if (TP_BLOCK_SIZE != 0U)
	{
		Tp_Sender.BlockSize_Count++;
		if (Tp_Sender.BlockSize_Count >= Tp_Sender.Block_Size)
		{
			Tp_Sender.Task_FSM = TP_TASK_FC_STATE;
			Tp_Sender.Timing_N_Bs = TP_TIMING_VALUE_N_BS;
		}
	}

	for (loop = 0U; loop < 7; loop++)
	{
		Tp_Sender.Frame_Tx_Buf[TP_CF_DATA_FIELD_OFFSET + loop] = N_USData_Request.MsgData[Tp_Sender.N_USData_Req_Index];
		Tp_Sender.N_USData_Req_Index++;

		if (Tp_Sender.N_USData_Req_Index >= N_USData_Request.Length)
		{
			N_USData_Confirm.N_Result = TP_N_OK;
			break;
		}
	}
	Tp_Sender.Frame_Tx_NewData_Valid = true;
	Tp_Sender.Timing_N_As = TP_TIMING_VALUE_N_AS;
}

/*************************************************************************/
/*
Function:		void TpFunc_Send_CF_PDU_Handle(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Send_FC_PDU_Handle(void)
{
	Tp_Sender.Block_Size = Tp_Rx_Buf[1U];
	Tp_Sender.STmin = Tp_Rx_Buf[2U];
	if (Tp_Sender.STmin <= TP_STMIN_MS_MAX)
	{
		Tp_Sender.STmin *= UDS_MS_MULTI_FACTOR;
	}
	else if ((Tp_Sender.STmin >= TP_STMIN_US_MIN) && (Tp_Sender.STmin <= TP_STMIN_US_MAX)) /*STMIN us*/
	{
		Tp_Sender.STmin -= 0xF0U;
		Tp_Sender.STmin /= UDS_US_DIVIDE_FACTOR;
	}
	else
	{
		Tp_Sender.STmin = TP_STMIN_MS_MAX * UDS_MS_MULTI_FACTOR;
	}
	Tp_Sender.BlockSize_Count = 0U;
	Tp_Sender.STmin_Count = Tp_Sender.STmin;

	Tp_Sender.Task_FSM = TP_TASK_CF_STATE;
}

/*************************************************************************/
/*
Function:		void TpFunc_Sender_Task(void)

Description:

Parameters: 	void

Return:       	void
*/
static void TpFunc_Sender_Task(void)
{
	uint16_t loop;

	if (Tp_Sender.Frame_Tx_NewData_Valid == false)
	{
		switch (Tp_Sender.Task_FSM)
		{
		case TP_TASK_SF_STATE:
		case TP_TASK_FF_STATE:
		{
			if ((0U < N_USData_Request.Length) && (N_USData_Request.Length <= (Tp_CAN_DL - 1U)))
			{
				TpFunc_Send_SF_PDU_Handle();
			}
			else if ((N_USData_Request.Length > (Tp_CAN_DL - 1U)) && (N_USData_Request.Length <= TP_FF_DL_MAX))
			{
				TpFunc_Send_FF_PDU_Handle();
			}
			else
			{
				N_USData_Confirm.N_Result = TP_N_ERROR;
			}
			break;
		}

		case TP_TASK_CF_STATE:
		{
			if (Tp_Sender.STmin_Count == 0U)
			{
				Tp_Sender.STmin_Count = Tp_Sender.STmin;
				TpFunc_Send_CF_PDU_Handle();
			}
			else
			{
				Tp_Sender.STmin_Count--;
			}
			break;
		}

		case TP_TASK_FC_STATE:
		{
			if (Tp_Rx_NewData_Valid == true)
			{
				Tp_Rx_NewData_Valid = false;
				switch (Tp_Rx_Buf[0U] & 0xF0U)
				{
				case TP_N_PDU_TYPE_FC:
				{
					switch (Tp_Rx_Buf[0U] & 0x0FU)
					{
					case TP_FC_FS_CTS:
					{
						TpFunc_Send_FC_PDU_Handle();
						break;
					}

					case TP_FC_FS_WT:
					{
						Tp_Sender.Timing_N_Bs = TP_TIMING_VALUE_N_BS;
						break;
					}

					case TP_FC_FS_OVFLW:
					{
						N_USData_Confirm.N_Result = TP_N_BUFFER_OVFLW;
						break;
					}

					default:
					{
						N_USData_Confirm.N_Result = TP_N_INVALID_FS;
						break;
					}
					}
					break;
				}

				default:
				{
					if (Tp_Sender.Timing_N_Bs != 0U)
					{
						Tp_Sender.Timing_N_Bs--;
					}

					if (Tp_Sender.Timing_N_Bs == 0U)
					{
						N_USData_Confirm.N_Result = TP_N_TIMEOUT_Bs;
					}
					break;
				}
				}
			}
			else
			{
				if (Tp_Sender.Timing_N_Bs != 0U)
				{
					Tp_Sender.Timing_N_Bs--;
				}

				if (Tp_Sender.Timing_N_Bs == 0U)
				{
					N_USData_Confirm.N_Result = TP_N_TIMEOUT_Bs;
				}
			}
			break;
		}
		default:
		{
			Tp_Sender.Task_FSM = TP_TASK_SF_STATE;
			break;
		}
		}
	}
	else
	{
		if (Tp_Sender.Timing_N_As != 0U)
		{
			Tp_Sender.Timing_N_As--;
		}

		if (Tp_Sender.Timing_N_As == 0U)
		{
			Tp_Sender.Frame_Tx_NewData_Valid = false;
			N_USData_Confirm.N_Result = TP_N_TIMEOUT_A;
		}
	}

	if (N_USData_Confirm.N_Result != TP_N_PENDING)
	{
		N_USData_Request.Length = 0U;
		Tp_Sender.Task_FSM = TP_TASK_SF_STATE;
	}
}
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void TpFunc_Init(void)

Description:

Parameters: 	void

Return:       	void
*/
void TpFunc_Init(void)
{
	N_USData_Indication.MsgData = &Tp_Rx_Buf_From_Drv[0U];
	N_USData_Request.MsgData = &Tp_Tx_Buf_To_Drv[0U];

	Tp_Rx_NewData_Valid = false;

	u8_Tp_Task_Dir_FSM = TP_TASK_RX_STATE;

	Tp_Receiver.ChannelState = CANTPRXSTATE_IDLE;
	Tp_Receiver.Task_FSM = TP_TASK_SF_STATE;
	Tp_Receiver.Frame_Tx_NewData_Valid = false;
	Tp_Receiver.Timing_N_Ar = 0U;
	Tp_Receiver.Timing_N_Cr = 0U;
	Tp_Receiver.N_USData_Ind_Index = 0U;

	Tp_Sender.Task_FSM = TP_TASK_SF_STATE;
	Tp_Sender.Frame_Tx_NewData_Valid = false;
	Tp_Sender.Timing_N_As = 0U;
	Tp_Sender.Timing_N_Bs = 0U;
	Tp_Sender.N_USData_Req_Index = 0U;

	N_USData_Request.Length = 0U;
	N_USData_Indication.N_Result = TP_N_PENDING;
	N_USData_Confirm.N_Result = TP_N_PENDING;
}

/*************************************************************************/
/*
Function:		void TpFunc_Recv_CANMsg(void)

Description:

Parameters: 	void

Return:       	void
*/
void TpFunc_Recv_Handle(uint32_t ID, uint8_t *pdudata, uint8_t length)
{
	boolean ret;

	Tp_Rx_CAN_ID = ID;
	memcpy(&Tp_Rx_Buf[0], pdudata, length);

	if (Tp_Rx_CAN_ID == TP_CAN_PHY_ADDR)
	{
		if((Tp_Rx_Buf[0U] == 0x02U) && (Tp_Rx_Buf[1U] == 0x3EU) && ((Tp_Rx_Buf[2U] & 0x7FU) == 0x00U))
		{
			Uds_SID_TP_Info.TesterPresentFlag = true;
			Uds_Dcm_Info.S3_Timer = UDS_S3_SERVER_MAX;
			if((Tp_Rx_Buf[2U] == 0x00U))
			{
				Pdu_Uds_Response.DataLength = length;
				Pdu_Uds_Response.ID = UDS_CAN_TX_ADDR;
				Pdu_Uds_Response.FrameType = HLI_CANFD_FRAME_FD;
				Pdu_Uds_Response.IDType = HLI_CANFD_DATA_STD;
				Pdu_Uds_Response.DataPtr = &Tp_Receiver.Frame_Tx_Buf[0U];
				Pdu_Uds_Response.DataPtr[0] = 0x02;
				Pdu_Uds_Response.DataPtr[1] = 0x7E;
				Pdu_Uds_Response.DataPtr[2] = 0x00;
				Pdu_Uds_Response.DataPtr[3] = 0xCC;
				Pdu_Uds_Response.DataPtr[4] = 0xCC;
				Pdu_Uds_Response.DataPtr[5] = 0xCC;
				Pdu_Uds_Response.DataPtr[6] = 0xCC;
				Pdu_Uds_Response.DataPtr[7] = 0xCC;
				HLI_CanFD_Write(Pdu_Uds_Response);
				Tp_Receiver.Frame_Tx_NewData_Valid = false;
			}
		}
		else
		{
			Tp_CAN_DL = length;
			Tp_Frame_AddrType = TP_ADDR_TYPE_PHY;
			Tp_Rx_NewData_Valid = true;
		}
	}
	/*15765-2 功能地址只能发送单帧*/
	else if ((Tp_Rx_CAN_ID == TP_CAN_FUNC_ADDR) && ((Tp_Rx_Buf[0U] & 0xF0U) == 0x00U))
	{
		if((Tp_Rx_Buf[0U] == 0x02U) && (Tp_Rx_Buf[1U] == 0x3EU) && ((Tp_Rx_Buf[2U] & 0x7FU) == 0x00U))
		{
			Uds_SID_TP_Info.TesterPresentFlag = true;
			Uds_Dcm_Info.S3_Timer = UDS_S3_SERVER_MAX;
			if((Tp_Rx_Buf[2U] == 0x00U))
			{
				Pdu_Uds_Response.DataLength = length;
				Pdu_Uds_Response.ID = UDS_CAN_TX_ADDR;
				Pdu_Uds_Response.FrameType = HLI_CANFD_FRAME_FD;
				Pdu_Uds_Response.IDType = HLI_CANFD_DATA_STD;
				Pdu_Uds_Response.DataPtr = &Tp_Receiver.Frame_Tx_Buf[0U];
				Pdu_Uds_Response.DataPtr[0] = 0x02;
				Pdu_Uds_Response.DataPtr[1] = 0x7E;
				Pdu_Uds_Response.DataPtr[2] = 0x00;
				Pdu_Uds_Response.DataPtr[3] = 0xCC;
				Pdu_Uds_Response.DataPtr[4] = 0xCC;
				Pdu_Uds_Response.DataPtr[5] = 0xCC;
				Pdu_Uds_Response.DataPtr[6] = 0xCC;
				Pdu_Uds_Response.DataPtr[7] = 0xCC;
				HLI_CanFD_Write(Pdu_Uds_Response);
				Tp_Receiver.Frame_Tx_NewData_Valid = false;
	
			}
		}
		else
		{
			Tp_CAN_DL = length;
			Tp_Frame_AddrType = TP_ADDR_TYPE_FUNC;
			Tp_Rx_NewData_Valid = true;
		}
	}
	else
	{
	    if(((Uds_SID_CC_Info.CommuCtrlFlag && 0x10U) >> 4U) == 1U)
	    {
			/*非诊断报文处理*/
	    	switch ((Uds_SID_CC_Info.CommuCtrlFlag && 0x03U))
			{
				case 3:
				{
					/*APP报文和网络报文都接收*/
					break;
				}
				case 2:
				{
					/*APP报文接收*/
					break;
				}
				case 1:
				{
					/*网络报文接收*/
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_Send_CANMsg(void)

Description:

Parameters: 	void

Return:       	void
*/
void TpFunc_Send_Handle(void)
{
	boolean ret;

	if (Tp_Receiver.Frame_Tx_NewData_Valid == true)
	{
		Pdu_Uds_Response.DataLength = Tp_CAN_DL;
		Pdu_Uds_Response.ID = UDS_CAN_TX_ADDR;
		Pdu_Uds_Response.FrameType = HLI_CANFD_FRAME_FD;
		Pdu_Uds_Response.IDType = HLI_CANFD_DATA_STD;
		Pdu_Uds_Response.DataPtr = &Tp_Receiver.Frame_Tx_Buf[0U];
		HLI_CanFD_Write(Pdu_Uds_Response);
		Tp_Receiver.Frame_Tx_NewData_Valid = false;
	}

	if (Tp_Sender.Frame_Tx_NewData_Valid == true)
	{
		Pdu_Uds_Response.DataLength = Tp_CAN_DL;
		Pdu_Uds_Response.ID = UDS_CAN_TX_ADDR;
		Pdu_Uds_Response.FrameType = HLI_CANFD_FRAME_FD;
		Pdu_Uds_Response.IDType = HLI_CANFD_DATA_STD;
		Pdu_Uds_Response.DataPtr = &Tp_Sender.Frame_Tx_Buf[0U];
		HLI_CanFD_Write(Pdu_Uds_Response);
		Tp_Sender.Frame_Tx_NewData_Valid = false;
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_HalfDuplex_Task(void)

Description:

Parameters: 	void

Return:       	void
*/
void TpFunc_HalfDuplex_Task(void)
{
	if (N_USData_Request.Length == 0U)
	{
		u8_Tp_Task_Dir_FSM = TP_TASK_RX_STATE;
	}
	else
	{
		u8_Tp_Task_Dir_FSM = TP_TASK_TX_STATE;
	}
	switch (u8_Tp_Task_Dir_FSM)
	{
	case TP_TASK_RX_STATE:
	{
		TpFunc_Receiver_Task();
		break;
	}

	case TP_TASK_TX_STATE:
	{
		TpFunc_Sender_Task();
		break;
	}

	default:
	{
		u8_Tp_Task_Dir_FSM = TP_TASK_RX_STATE;
		break;
	}
	}
}

/*************************************************************************/
/*
Function:		void TpFunc_FullDuplex_Task(void)

Description:

Parameters: 	void

Return:       	void
*/
void TpFunc_FullDuplex_Task(void)
{
	TpFunc_Receiver_Task();
	TpFunc_Sender_Task();
}
