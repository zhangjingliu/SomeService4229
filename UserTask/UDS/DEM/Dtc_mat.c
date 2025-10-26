#include  "Detdtc.h"
#include  "Detfun.h"

/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/
#define DTC_CONTROLBIT(byte, bit)    (uint8_t)( ( (byte - 1) << 4) |(bit & 0x0F ) )

#define  DTC_IncStep_BattVolHi   	(int8_t)1
#define  DTC_IncLimit_BattVolHi  	(int16_t)100
#define  DTC_DecStep_BattVolHi  	(int8_t)1
#define  DTC_DecLimit_BattVolHi  	(int16_t)100
/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
OBD_Dtc_Type_Format   DTC_BattVolHi;                /* Battery voltage is too high */

uint8_t DTC_ControlBit[16] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                             0xFF,0,0,0,0,0,0,0};

//01 B1C0016 == 9C0016  //System power voltage below threshold
//02 B1C0017 == 9C0017  //System power voltage above threshold
//03 B1C0101 == 9C0101  //Speaker (FL) is short to across
//04 B1C0111 == 9C0111  //Speaker (FL) is short to ground
//05 B1C0112 == 9C0112  //Speaker (FL) is short to battery
//06 B1C0113 == 9C0113  //Speaker (FL) is open
//07 B1C0213 == 9C0213  //Speaker (FL) is TW open
//08 B1C0301 == 9C0301  //Speaker (FR) is short to across
//09 B1C0311 == 9C0311  //Speaker (FR) is short to ground
//10 B1C0312 == 9C0312  //Speaker (FR) is short to battery
//11 B1C0313 == 9C0313  //Speaker (FR) is open
//12 B1C0413 == 9C0413  //Speaker (FR) is TW open
//13 B1C0501 == 9C0501  //Speaker (RL) is short to across
//14 B1C0511 == 9C0511  //Speaker (RL) is short to ground
//15 B1C0512 == 9C0512  //Speaker (RL) is short to battery
//16 B1C0513 == 9C0513  //Speaker (RL) is open
//17 B1C0613 == 9C0613  //Speaker (RL) is TW open
//18 B1C0701 == 9C0701  //Speaker (RR) is short to across
//19 B1C0711 == 9C0711  //Speaker (RR) is short to ground
//20 B1C0712 == 9C0712  //Speaker (RR) is short to battery
//21 B1C0713 == 9C0713  //Speaker (RR) is open
//22 B1C0813 == 9C0813  //Speaker (RR) is TW open
//23 B1C0901 == 9C0901  //Speaker (CTR) is short to across
//24 B1C0911 == 9C0911  //Speaker (CTR) is short to ground
//25 B1C0912 == 9C0912  //Speaker (CTR) is short to battery
//26 B1C0913 == 9C0913  //Speaker (CTR) is open
//27 B1C0A01 == 9C0A01  //Speaker (SRD) is short to across
//28 B1C0A11 == 9C0A11  //Speaker (SRD) is short to ground
//29 B1C0A12 == 9C0A12  //Speaker (SRD) is short to battery
//30 B1C0A13 == 9C0A13  //Speaker (SRD) is open
//31 B1C0B01 == 9C0B01  //Speaker (SUB1) is short to across
//32 B1C0B11 == 9C0B11  //Speaker (SUB1) is short to ground
//33 B1C0B12 == 9C0B12  //Speaker (SUB1) is short to battery
//34 B1C0B13 == 9C0B13  //Speaker (SUB1) is open
//35 B1C0C01 == 9C0C01  //Speaker (SUB2) is short to across
//36 B1C0C11 == 9C0C11  //Speaker (SUB2) is short to ground
//37 B1C0C12 == 9C0C12  //Speaker (SUB2) is short to battery
//38 B1C0C13 == 9C0C13  //Speaker (SUB2) is open
//39 B1C0D00 == 9C0D00  //A2B Error                        
//40 B1C0E00 == 9C0E00  //D-AMP Diag. Failure
//41 B1C0F41 == 9C0F41  //Checksum Fail at Application Code
//42 B1C1042 == 9C1042  //Storage Area is Fail
//43 B1C1156 == 9C1156  //Configuration Incompatible
//44 U007388 == C07388  //Control Module Communication Bus Off
//45 U012987 == C12987  //Lost Communication With BSM
//46 U015587 == C15587  //Lost Communication With ICM
//47 U300051 == F00051  //Control Module Not Programmed
//48 U014087 == C14087  //Lost Communication With BCM


volatile const OBD_Dtc_Det_Cfg_Format OBD_DtcConfigTbl[] =
{
	{
		.id 				= 0x9117U,   			//DTC值->DTC显示码B1117
		.failure_type 		= 0x17U,					//1：故障类别，7：故障子类别
		.dtc_type 			= 0x05U,					//DTC类别
		.serious_level 		= 0x01U,					//DTC的严重级别
		.dtc_trip_mask 		= OBD_DTC_OPR_WAKEUP,	//DTC记录的类别
		.contorl 			= DTC_CONTROLBIT(1,7),
		.monitor_threshold 	= 1U,					//监控阈值
		.aged_trip_cnt 		= 40U,
		.fail_increment 	= DTC_IncStep_BattVolHi,
		.pass_decrement 	= DTC_DecStep_BattVolHi,
		.fail_threshold 	= DTC_IncLimit_BattVolHi,
		.pass_threshold 	= DTC_DecLimit_BattVolHi,
		.failed_flag 		= &DETFUN_BattVolHi_d,
		.dtc_detect_fun 	= DETFUN_BattVolHi,
		.pt_dtc_type 		= &DTC_BattVolHi,
		.eerom_index 		= DTC_911717
	},
	//Speaker (FL) is short to across
	{
		.id 				= 0x9C01U,				//DTC值->DTC显示码B1C01
		.failure_type		= 0x01U,					//1：故障类别，7：故障子类别
		.dtc_type			= 0x05U,					//DTC类别
		.serious_level		= 0x01U,					//DTC的严重级别
		.dtc_trip_mask		= OBD_DTC_OPR_WAKEUP,	//DTC记录的类别
		.contorl			= DTC_CONTROLBIT(1,7),
		.monitor_threshold	= 1U,					//监控阈值
		.aged_trip_cnt		= 40U,
		.fail_increment 	= DTC_IncStep_BattVolHi,
		.pass_decrement 	= DTC_DecStep_BattVolHi,
		.fail_threshold 	= DTC_IncLimit_BattVolHi,
		.pass_threshold 	= DTC_DecLimit_BattVolHi,
		.failed_flag		= &DETFUN_BattVolHi_d,
		.dtc_detect_fun 	= DETFUN_BattVolHi,
		.pt_dtc_type		= &DTC_BattVolHi,
		.eerom_index		= DTC_9C0101
	},
	//Speaker (FL) is short to ground
	{
		.id 				= 0x9C01U,				//DTC值->DTC显示码B1C01
		.failure_type		= 0x11U,					//1：故障类别，7：故障子类别
		.dtc_type			= 0x05U,					//DTC类别
		.serious_level		= 0x01U,					//DTC的严重级别
		.dtc_trip_mask		= OBD_DTC_OPR_WAKEUP,	//DTC记录的类别
		.contorl			= DTC_CONTROLBIT(1,7),
		.monitor_threshold	= 1U,					//监控阈值
		.aged_trip_cnt		= 40U,
		.fail_increment 	= DTC_IncStep_BattVolHi,
		.pass_decrement 	= DTC_DecStep_BattVolHi,
		.fail_threshold 	= DTC_IncLimit_BattVolHi,
		.pass_threshold 	= DTC_DecLimit_BattVolHi,
		.failed_flag		= &DETFUN_BattVolHi_d,
		.dtc_detect_fun 	= DETFUN_BattVolHi,
		.pt_dtc_type		= &DTC_BattVolHi,
		.eerom_index		= DTC_9C0111
	},
	//Speaker (FL) is short to battery
	{
		.id 				= 0x9C01U,				//DTC值->DTC显示码B1C01
		.failure_type		= 0x12U,					//1：故障类别，7：故障子类别
		.dtc_type			= 0x05U,					//DTC类别
		.serious_level		= 0x01U,					//DTC的严重级别
		.dtc_trip_mask		= OBD_DTC_OPR_WAKEUP,	//DTC记录的类别
		.contorl			= DTC_CONTROLBIT(1,7),
		.monitor_threshold	= 1U,					//监控阈值
		.aged_trip_cnt		= 40U,
		.fail_increment 	= DTC_IncStep_BattVolHi,
		.pass_decrement 	= DTC_DecStep_BattVolHi,
		.fail_threshold 	= DTC_IncLimit_BattVolHi,
		.pass_threshold 	= DTC_DecLimit_BattVolHi,
		.failed_flag		= &DETFUN_BattVolHi_d,
		.dtc_detect_fun 	= DETFUN_BattVolHi,
		.pt_dtc_type		= &DTC_BattVolHi,
		.eerom_index		= DTC_9C0112
	},	
	//Speaker (FL) is open
	{
		.id 				= 0x9C01U,				//DTC值->DTC显示码B1C01
		.failure_type		= 0x13U,					//1：故障类别，7：故障子类别
		.dtc_type			= 0x05U,					//DTC类别
		.serious_level		= 0x01U,					//DTC的严重级别
		.dtc_trip_mask		= OBD_DTC_OPR_WAKEUP,	//DTC记录的类别
		.contorl			= DTC_CONTROLBIT(1,7),
		.monitor_threshold	= 1U,					//监控阈值
		.aged_trip_cnt		= 40U,
		.fail_increment 	= DTC_IncStep_BattVolHi,
		.pass_decrement 	= DTC_DecStep_BattVolHi,
		.fail_threshold 	= DTC_IncLimit_BattVolHi,
		.pass_threshold 	= DTC_DecLimit_BattVolHi,
		.failed_flag		= &DETFUN_BattVolHi_d,
		.dtc_detect_fun 	= DETFUN_BattVolHi,
		.pt_dtc_type		= &DTC_BattVolHi,
		.eerom_index		= DTC_9C0113
	},	
	//Speaker (FL) is TW open
	{
		.id 				= 0x9C02U,				//DTC值->DTC显示码B1C02
		.failure_type		= 0x13U,					//1：故障类别，7：故障子类别
		.dtc_type			= 0x05U,					//DTC类别
		.serious_level		= 0x01U,					//DTC的严重级别
		.dtc_trip_mask		= OBD_DTC_OPR_WAKEUP,	//DTC记录的类别
		.contorl			= DTC_CONTROLBIT(1,7),
		.monitor_threshold	= 1U,					//监控阈值
		.aged_trip_cnt		= 40U,
		.fail_increment 	= DTC_IncStep_BattVolHi,
		.pass_decrement 	= DTC_DecStep_BattVolHi,
		.fail_threshold 	= DTC_IncLimit_BattVolHi,
		.pass_threshold 	= DTC_DecLimit_BattVolHi,
		.failed_flag		= &DETFUN_BattVolHi_d,
		.dtc_detect_fun 	= DETFUN_BattVolHi,
		.pt_dtc_type		= &DTC_BattVolHi,
		.eerom_index		= DTC_9C0213
	},	
	//A2B Error 
	{
		.id 				= 0x9C0DU,				//DTC值->DTC显示码B1C0D
		.failure_type		= 0x00U,					//1：故障类别，7：故障子类别
		.dtc_type			= 0x05U,					//DTC类别
		.serious_level		= 0x01U,					//DTC的严重级别
		.dtc_trip_mask		= OBD_DTC_OPR_WAKEUP,	//DTC记录的类别
		.contorl			= DTC_CONTROLBIT(1,7),
		.monitor_threshold	= 1U,					//监控阈值
		.aged_trip_cnt		= 40U,
		.fail_increment 	= DTC_IncStep_BattVolHi,
		.pass_decrement 	= DTC_DecStep_BattVolHi,
		.fail_threshold 	= DTC_IncLimit_BattVolHi,
		.pass_threshold 	= DTC_DecLimit_BattVolHi,
		.failed_flag		= &DETFUN_BattVolHi_d,
		.dtc_detect_fun 	= DETFUN_BattVolHi,
		.pt_dtc_type		= &DTC_BattVolHi,
		.eerom_index		= DTC_9C0D00
	},	

};

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
const uint8_t OBD_DTC_LEN= (sizeof(OBD_DtcConfigTbl)/sizeof(OBD_DtcConfigTbl[0]));
