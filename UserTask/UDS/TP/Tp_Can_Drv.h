#ifndef __CAN_TP_DRV_H_
#define __CAN_TP_DRV_H_

#include "Tp_Can_DrvCfg.h"
#include "bsp_debug_uart.h"
#include "bsp_canfd1.h"

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
/*TP任务状态*/
#define TP_TASK_SF_STATE 0U
#define TP_TASK_FF_STATE 1U
#define TP_TASK_CF_STATE 2U
#define TP_TASK_FC_STATE 3U

#define TP_TASK_RX_STATE 0U
#define TP_TASK_TX_STATE 1U

/*TP N_PDU帧状态*/
#define TP_N_PDU_TYPE_SF 0x00U
#define TP_N_PDU_TYPE_FF 0x10U
#define TP_N_PDU_TYPE_CF 0x20U
#define TP_N_PDU_TYPE_FC 0x30U

/*流控帧回复类型*/
#define TP_FC_FS_CTS 0U
#define TP_FC_FS_WT 1U
#define TP_FC_FS_OVFLW 2U

/*TP N_Result IS015765_2 8.3.7*/
#define TP_N_PENDING 0U
#define TP_N_OK 1U
#define TP_N_TIMEOUT_A 2U
#define TP_N_TIMEOUT_Bs 3U
#define TP_N_TIMEOUT_Cr 4U
#define TP_N_WRONG_SN 5U
#define TP_N_INVALID_FS 6U
#define TP_N_UNEXP_PDU 7U
#define TP_N_WFT_OVRN 8U
#define TP_N_BUFFER_OVFLW 9U
#define TP_N_ERROR 10U

/***************************************************************************************/
/* CanTp_RxStateType */
#define CANTPRXSTATE_IDLE 0x00U
#define CANTPRXSTATE_WAITCF 0x01U
#define CANTPRXSTATE_WAITFORTXFC 0x02U
#define CANTPRXSTATE_WAITFORTXFCOVERRUN 0x03U
#define CANTPRXSTATE_WAITFORTXFCWAIT 0x04U
#define CANTPRXSTATE_WAITFORRXBUFFER 0x05U
#define CANTPRXSTATE_ERROR 0x08U
#define CANTPRXSTATE_WAITFORFCCONF 0x10U
#define CANTPRXSTATE_WAITFORFCWAITCONF 0x20U
#define CANTPRXSTATE_WAITFORFCOVERCONF 0x40U
/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef enum
{
	STMIN,
	BS,
} ChangeParameters;

typedef struct
{
	uint8_t Task_FSM;				   /*接收任务状态*/
	boolean Frame_Tx_NewData_Valid;	   /*接收状态，有新帧需要发送*/
	uint16_t Timing_N_Ar;			   /*数据链路层发送等待时间N_Ar*/
	uint16_t Timing_N_Cr;			   /*连续帧等待时间N_Cr*/
	uint8_t CF_SN;					   /*SN*/
	uint8_t BlockSize_Count;		   /*Block Size*/
	uint8_t Frame_Tx_Buf[TP_FRAME_DL]; /*Buf*/
	uint16_t N_USData_Ind_Index;	   /*Ind index*/
	uint8_t ChannelState;			   /*activation status*/
} Struct_Tp_Receiver;				   /*TP Receiver*/

typedef struct
{
	uint8_t Task_FSM;				   /*发送任务状态*/
	boolean Frame_Tx_NewData_Valid;	   /*发送状态，有新帧需要发送*/
	uint16_t Timing_N_As;			   /*数据链路层发送等待时间N_As*/
	uint16_t Timing_N_Bs;			   /*流控制等待时间N_Bs*/
	uint8_t CF_SN;					   /*SN*/
	uint8_t BlockSize_Count;		   /*Block Size Count*/
	uint16_t STmin_Count;			   /*STmin*/
	uint8_t Block_Size;				   /*Block Size*/
	uint16_t STmin;					   /*STmin 接收方发送流控帧之后，发送方发送的连续帧之间的时间最小间隔*/
	uint8_t Frame_Tx_Buf[TP_FRAME_DL]; /*֡发送buf*/
	uint16_t N_USData_Req_Index;	   /*Req index*/
} Struct_Tp_Sender;					   /*TP Sender*/

typedef struct
{
	uint8_t Mtype;	  /*message type*/
	uint8_t N_SA;	  /*network source address*/
	uint8_t N_TA;	  /*network target address*/
	uint8_t N_TAtype; /*Network target address type*/
	uint8_t N_AE;	  /*network address extension*/
	uint8_t *MsgData; /*MessageData*/
	uint32_t Length;  /*Length*/
} Struct_N_USData_Request;

typedef struct
{
	uint8_t Mtype;	  /*message type*/
	uint8_t N_SA;	  /*network source address*/
	uint8_t N_TA;	  /*network target address*/
	uint8_t N_TAtype; /*Network target address type*/
	uint8_t N_AE;	  /*network address extension*/
	uint32_t Length;  /*Length*/
} Struct_N_USData_FF_Indication;

typedef struct
{
	uint8_t Mtype;	  /*message type*/
	uint8_t N_SA;	  /*network source address*/
	uint8_t N_TA;	  /*network target address*/
	uint8_t N_TAtype; /*Network target address type*/
	uint8_t N_AE;	  /*network address extension*/
	uint8_t *MsgData; /*MessageData*/
	uint32_t Length;  /*Length*/
	uint8_t N_Result; /*IS015765-2 8.3.7*/
} Struct_N_USData_Indication;

typedef struct
{
	uint8_t Mtype;	  /*message type*/
	uint8_t N_SA;	  /*network source address*/
	uint8_t N_TA;	  /*network target address*/
	uint8_t N_TAtype; /*Network target address type*/
	uint8_t N_AE;	  /*network address extension*/
	uint8_t N_Result; /*IS015765-2 8.3.7*/
} Struct_N_USData_Confirm;

/*This is an optional service that can be replaced
 * by implementation of fixed parameter values*/
typedef struct
{
	uint8_t Mtype;				/*message type*/
	uint8_t N_SA;				/*network source address*/
	uint8_t N_TA;				/*network target address*/
	uint8_t N_TAtype;			/*Network target address type*/
	uint8_t N_AE;				/*network address extension*/
	ChangeParameters Parameter; /*Parameter*/
	uint8_t Parameter_Value;	/*Parameter_Value*/
} Struct_N_ChangeParameters_Request;

typedef struct
{
	uint8_t Mtype;				/*message type*/
	uint8_t N_SA;				/*network source address*/
	uint8_t N_TA;				/*network target address*/
	uint8_t N_TAtype;			/*Network target address type*/
	uint8_t N_AE;				/*network address extension*/
	ChangeParameters Parameter; /*Parameter*/
	uint8_t N_Result_Parameter; /*IS015765-2 8.3.7*/
} Struct_N_ChangeParameters_Confirm;
/******************************************************************************
 **                      Export Variables
 ******************************************************************************/
extern Struct_N_USData_Indication N_USData_Indication;
extern Struct_N_USData_Request N_USData_Request;
extern HLI_Canfd_MessageType Pdu_Uds_Response;

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void TpFunc_Init(void);
void TpFunc_Recv_Handle(uint32_t ID, uint8_t *pdudata, uint8_t length);
void TpFunc_Send_Handle(void);
void TpFunc_HalfDuplex_Task(void);
void TpFunc_FullDuplex_Task(void);


#endif
