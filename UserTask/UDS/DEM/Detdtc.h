#ifndef __DETDTC_H_
#define __DETDTC_H_

#include "uds_main.h"


/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define OBD_DTC_DATA_INEE_READY      (0x01)
#define OBD_DTC_DATA_INEE_VALID      (0x02)
#define OBD_DTC_EXDATA_UNUSED        (0x00)
#define OBD_DTC_EXDATA_READY         (0x10)
#define OBD_DTC_EXDATA_SAVED         (0x20)

#define OBD_PRECON_NG    0x00
#define OBD_PRECON_OK    0x01

/* Operation Cycle */
#define OBD_DTC_OPR_WAKEUP               0x01              /* ECU Wakeup */
#define OBD_DTC_OPR_COMEN                0x02              /* Communication Enabled */

#define DTC_911717        	 40
#define DTC_911717_S         8

#define DTC_9C0101			 40
#define DTC_9C0111			 40
#define DTC_9C0112			 40
#define DTC_9C0113			 40
#define DTC_9C0213			 40
#define DTC_9C0D00			 40

/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef uint8_t (*dtc_detect_fun_format)(void);

typedef enum {
    Pending = 0,
    Passed,
    Faulted
}OBD_DTC_FLAG;

typedef union
{
	uint8_t status;
    struct{
		uint8_t testFailed : 1;
		uint8_t testFailedThisOperCyc : 1;
		uint8_t pendingDTC : 1;
		uint8_t confirmedDTC : 1;
		uint8_t testNotCompletedSinceLastClr : 1;
		uint8_t testFailedSinceLastClear : 1;
		uint8_t testNotCompletedThisOperCyc : 1;
		uint8_t warningIndicatorReq : 1;
	}DTC_bit;
}OBD_Dtc_Status_Format;

/* extended data definition */
typedef struct
{
	uint8_t fault_occur_counter;
	uint8_t fault_pending_counter;
	uint8_t aged_counter;
	uint8_t ageing_counter;
}OBD_Extended_Data_Format;

/* snapshot time & data structure definition */
typedef struct
{
	uint8_t  second;
	uint8_t  minute;
	uint8_t  hour;
	uint8_t  day;
	uint8_t  month;
	uint8_t  year;
}OBD_Global_Snapshot_DataTime_Format;

/* dtc global snapshot data structure definition */
typedef struct
{
	uint8_t   voltage;
    uint8_t   global_power_mode;
    OBD_Global_Snapshot_DataTime_Format st_global_snapshot_datatime;
}OBD_Global_Snapshot_Format;

typedef  struct
{
	uint16_t 	id;                                /* DTC_MBS | DTC_LBS             */
	uint8_t   	failure_type;                      /* DTC failure type information  */
    OBD_Global_Snapshot_Format   snapshot;         /* snapshot information          */

}OBD_Dtc_Info_Format;

typedef struct
{
    OBD_Dtc_Status_Format         status;                   /* DTC Status byte */
    int16_t                       fault_detect_count;       /* Fault detection count */
    uint8_t                       control;                  /* control dtc on/off swith on:TRUE off: FALSE  */
    OBD_Extended_Data_Format      extended_data;            /* extended data information */
    OBD_Dtc_Info_Format           information;              /* snapshot information*/
    uint8_t                       info_status;              /* status of the information*/
    uint8_t                       monitor_rate;
    uint8_t                       dtc_up_req;
} OBD_Dtc_Type_Format;

typedef struct
{
	uint16_t      id; 			    /*DTC值 高8位和中8位*/
	uint8_t       failure_type;	    /*1：故障类别，7：故障子类别*/
	uint8_t       dtc_type;		    /*DTC type*/
	uint8_t       serious_level;    /*DTC的严重级别*/
	uint8_t       dtc_trip_mask;    /*DTC记录的类别*/
	uint8_t       contorl;		    /*Bit位控制*/
	uint8_t       monitor_threshold;/*监控阈值*/
	uint8_t       aged_trip_cnt;    /*老化次数*/
	int16_t       fail_increment;	/*减 offset*/
	int16_t       pass_decrement;	/*加offset*/
	int16_t       fail_threshold;	/*加到多大失败*/
	int16_t       pass_threshold;	/*减到多大成功*/
	OBD_DTC_FLAG*    failed_flag;   /*该Flag是根据上阈值而设定的*/
	dtc_detect_fun_format    dtc_detect_fun; /*当前DTC的处理函数*/
	OBD_Dtc_Type_Format*     pt_dtc_type;	 /*dtc的状态信息*/
	uint8_t                  eerom_index;	 /*EEPROM存储的位置*/
}OBD_Dtc_Det_Cfg_Format;
/******************************************************************************
 **                      Export Variables
 ******************************************************************************/
extern volatile const  OBD_Dtc_Det_Cfg_Format OBD_DtcConfigTbl[];
extern const uint8_t OBD_DTC_LEN;
extern uint8_t DTC_ControlBit[16];
/******************************************************************************
 **                      Export Functions
 ******************************************************************************/


#endif
