#ifndef __DCM_DRV_H_
#define __DCM_DRV_H_

#include "uds_main.h"
#include "bsp_debug_uart.h"
#include "AB_Swap.h"

/******************************************************************************
**                      File Version Check
******************************************************************************/

/******************************************************************************
**                      Macro  Definitions
******************************************************************************/
#define E_OK 0U
#define E_NOT_OK 1U

#define UDS_ADDR_TYPE_CAN_BASE_PHY 1U			/*物理地址类型*/
#define UDS_ADDR_TYPE_CAN_BASE_FUNC 2U			/*功能地址类型*/
#define UDS_ADDR_TYPE_CANFD_BASE_PHY 4U			/*物理地址类型*/
#define UDS_ADDR_TYPE_CANFD_BASE_FUNC 8U		/*功能地址类型*/
#define UDS_ADDR_TYPE_CAN_EXTERNDED_PHY 16U		/*物理地址类型*/
#define UDS_ADDR_TYPE_CAN_EXTERNDED_FUNC 32U	/*功能地址类型*/
#define UDS_ADDR_TYPE_CANFD_EXTERNDED_PHY 64U	/*物理地址类型*/
#define UDS_ADDR_TYPE_CANFD_EXTERNDED_FUNC 128U /*功能地址类型*/

#define UDS_TASK_IDLE 0U	   /*UDS IDEL*/
#define UDS_TASK_SID_DSC 1U	   /*DiagnosticSessionControl*/
#define UDS_TASK_SID_ER 2U	   /*ECUReset*/
#define UDS_TASK_SID_SA 3U	   /*SecurityAccess*/
#define UDS_TASK_SID_CC 4U	   /*CommunicationControl*/
#define UDS_TASK_SID_TP 5U	   /*TesterPresent*/
#define UDS_TASK_SID_RDBI 6U   /*ReadDataByIdentifier*/
#define UDS_TASK_SID_WDBI 7U   /*WriteDataByIdentifier*/
#define UDS_TASK_SID_RC 8U	   /*RoutineControl*/
#define UDS_TASK_SID_RD 9U	   /*RequestDownload*/
#define UDS_TASK_SID_TD 10U	   /*TransferData*/
#define UDS_TASK_SID_RTE 11U   /*RequestTransferExit*/
#define UDS_TASK_SID_CDTCS 12U /*ControlDTCSetting*/
#define UDS_TASK_SID_CDTCI 13U /*Clear DTC*/
#define UDS_TASK_SID_RDTCI 14U /*Read DTC*/
/***************************************************************************************/
/*UDS responseCode*/
#define UDS_RES_CODE_PR 0x00U	   /*positiveResponse*/
#define UDS_RES_CODE_GR 0x10U	   /*generalReject*/
#define UDS_RES_CODE_SNS 0x11U	   /*serviceNotSupported*/
#define UDS_RES_CODE_SFNS 0x12U	   /*subFunctionNotSupported*/
#define UDS_RES_CODE_IMLOIF 0x13U  /*incorrectMessageLengthOrInvalidFormat*/
#define UDS_RES_CODE_RTL 0x14U	   /*responseTooLong*/
#define UDS_RES_CODE_BRR 0x21U	   /*busyRepeatRequest*/
#define UDS_RES_CODE_CNC 0x22U	   /*conditionsNotCorrect*/
#define UDS_RES_CODE_RSE 0x24U	   /*requestSequenceError*/
#define UDS_RES_CODE_NRFSC 0x25U   /*noResponseFromSubnetComponent*/
#define UDS_RES_CODE_FPEORA 0x26U  /*failurePreventsExecutionOfRequestedAction*/
#define UDS_RES_CODE_ROOR 0x31U	   /*requestOutOfRange*/
#define UDS_RES_CODE_SAD 0x33U	   /*securityAccessDenied*/
#define UDS_RES_CODE_IK 0x35U	   /*invalidKey*/
#define UDS_RES_CODE_ENOA 0x36U	   /*exceedNumberOfAttempts*/
#define UDS_RES_CODE_RTDNE 0x37U   /*requiredTimeDelayNotExpired*/
#define UDS_RES_CODE_UDNA 0x70U	   /*uploadDownloadNotAccepted*/
#define UDS_RES_CODE_TDS 0x71U	   /*transferDataSuspended*/
#define UDS_RES_CODE_GPF 0x72U	   /*generalProgrammingFailure*/
#define UDS_RES_CODE_WBSC 0x73U	   /*wrongBlockSequenceCounter*/
#define UDS_RES_CODE_RCRRP 0x78U   /*requestCorrectlyReceived-ResponsePending*/
#define UDS_RES_CODE_SFNSIAS 0x7EU /*subFunctionNotSupportedInActiveSession*/
#define UDS_RES_CODE_SNSIAS 0x7FU  /*serviceNotSupportedInActiveSession*/
#define UDS_RES_CODE_RPMTH 0x81U   /*rpmTooHigh*/
#define UDS_RES_CODE_RPMTL 0x82U   /*rpmTooLow*/
#define UDS_RES_CODE_EIR 0x83U	   /*engineIsRunning*/
#define UDS_RES_CODE_EINR 0x84U	   /*engineIsNotRunning*/
#define UDS_RES_CODE_ERTTL 0x85U   /*engineRunTimeTooLow*/
#define UDS_RES_CODE_TEMPTH 0x86U  /*temperatureTooHigh*/
#define UDS_RES_CODE_TEMPTL 0x87U  /*temperatureTooLow*/
#define UDS_RES_CODE_VSTH 0x88U	   /*vehicleSpeedTooHigh*/
#define UDS_RES_CODE_VSTL 0x89U	   /*vehicleSpeedTooLow*/
#define UDS_RES_CODE_TPTH 0x8AU	   /*throttle/PedalTooHigh*/
#define UDS_RES_CODE_TPTL 0x8BU	   /*throttle/PedalTooLow*/
#define UDS_RES_CODE_TRNIN 0x8CU   /*transmissionRangeNotInNeutral*/
#define UDS_RES_CODE_TRNIG 0x8DU   /*transmissionRangeNotInGear*/
#define UDS_RES_CODE_BSNC 0x8FU	   /*brakeSwitch(es)NotClosed (brake pedal not pressed or not applied)*/
#define UDS_RES_CODE_SLNIP 0x90U   /*shifterLeverNotInPark*/
#define UDS_RES_CODE_TCCL 0x91U	   /*torqueConverterClutchLocked*/
#define UDS_RES_CODE_VTH 0x92U	   /*voltageTooHigh*/
#define UDS_RES_CODE_VTL 0x93U	   /*voltageTooLow*/
#define UDS_RES_CODE_INVALID 0xFFU /*invall*/
/******************************************************************************
**                      Typedef  Definitions
******************************************************************************/
typedef void (*pFunc)(uint8_t *, uint16_t);

typedef struct
{
	boolean Service_Enable;
	uint16_t S3_Timer;
	uint8_t Cur_Task;
} Struct_Uds_Dcm_Info;

typedef struct
{
	uint8_t *TA_Type;
	uint8_t SID;
	uint8_t *MsgData;
	uint32_t *Length;
	uint8_t *Result;
} Struct_Uds_Indication;

typedef struct
{
	uint8_t ResCode;
	boolean SuppressPosRspBit;
	uint8_t *MsgData;
	uint32_t *Length;
	uint8_t Neg78_Buf[8U];
	uint8_t Tp_Buf[8U];
} Struct_Uds_Response;

typedef struct
{
	uint8_t SID;			 /*service ID*/
	uint8_t Addr_Support;	 /*物理地址：Bit0=0不支持，Bit0=1支持   */
							 /*功能地址：Bit1=0不支持，Bit0=1支持   */
							 /*物理地址：Bit2=0不支持，Bit0=1支持   */
							 /*功能地址：Bit3=0不支持，Bit0=1支持   */
							 /*物理地址：Bit4=0不支持，Bit0=1支持   */
							 /*功能地址：Bit5=0不支持，Bit0=1支持   */
							 /*物理地址：Bit6=0不支持，Bit0=1支持   */
							 /*功能地址：Bit7=0不支持，Bit0=1支持   */
	uint8_t Session_Support; /*Default:Bit0=0不支持,Bit0=1支持*/
							 /*Programming:Bit1=0不支持,Bit0=1支持*/
							 /*Extended:Bit2=0不支持,Bit0=1支持*/
	boolean Security_En;	 /*安全等级:TRUE:支持,FALSE:不支持*/
	uint32_t DL_Min;		 /*报文最小长度*/
	uint32_t DL_Max;		 /*报文最大长度*/
	pFunc SidFunc_Callback;	 /*服务回调处理*/
} Struct_Uds_Cfg_Info;		 /*UDS报文服务配置*/

/******************************************************************************
**                      Export Variables
******************************************************************************/
extern Struct_Uds_Dcm_Info Uds_Dcm_Info;
extern Struct_Uds_Indication Uds_Indication;
extern Struct_Uds_Response Uds_Response;
/******************************************************************************
**                      Export Functions
******************************************************************************/
void UdsFunc_Init(void);
void UdsFunc_Task(void);
void UdsFunc_Delay1ms_Handle(void);


#endif
