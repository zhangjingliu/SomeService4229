#ifndef __CAN_TP_DRVCFG_H_
#define __CAN_TP_DRVCFG_H_

#include "Dcm_DrvCfg.h"

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define TP_FRAME_DL 64U /*TP֡ length*/

/*TP ADDR*/
#define TP_CAN_PHY_ADDR UDS_CAN_PHY_ADDR   /*物理地址*/
#define TP_CAN_FUNC_ADDR UDS_CAN_FUNC_ADDR /*功能地址*/

/*TP N_TAtype ISO157658.3.2.4*/
#define TP_ADDR_TYPE_PHY UDS_ADDR_TYPE_PHY   /*物理地址类型*/
#define TP_ADDR_TYPE_FUNC UDS_ADDR_TYPE_FUNC /*功能地址类型*/

#define TP_APPL_DL_MAX UDS_APPL_DL_MAX
#define TP_SF_DL_MIN 1U
#define TP_SF_DL_MAX 7U
#define TP_FF_DL_MIN 8U
#define TP_FF_DL_MAX TP_APPL_DL_MAX

#define TP_SF_DATA_FIELD_OFFSET 1U       /*单帧数据偏移量*/
#define TP_SF_DATA_FIELD_OFFSET_CANFD 2U /*单帧数据偏移量*/
#define TP_FF_DATA_FIELD_OFFSET 2U       /*首帧数据偏移量*/
#define TP_CF_DATA_FIELD_OFFSET 1U       /*连续帧数据偏移量*/

#define TP_BLOCK_SIZE 0U /*Block Size参数值范围应用于向发送方指示在没有来自接收网络实体的中间 FC 帧的情况下可以接收到的连续帧的最大数量*/

#define TP_STMIN_MS_MIN 0x00U /*STMIN ms*/
#define TP_STMIN_MS_MAX 0x7FU /*STMIN ms*/
#define TP_STMIN_US_MIN 0xF1U /*STMIN us*/
#define TP_STMIN_US_MAX 0xF9U /*STMIN us*/
#define TP_STMIN 0x01U        /*0ms*/

#define TP_TIMING_VALUE_N_AS (70U * UDS_MS_MULTI_FACTOR)  /*70ms*/
#define TP_TIMING_VALUE_N_AR (70U * UDS_MS_MULTI_FACTOR)  /*70ms*/
#define TP_TIMING_VALUE_N_BS (150U * UDS_MS_MULTI_FACTOR) /*150ms*/
#define TP_TIMING_VALUE_N_BR (70U * UDS_MS_MULTI_FACTOR)  /*70ms*/
#define TP_TIMING_VALUE_N_CS (70U * UDS_MS_MULTI_FACTOR)  /*70ms*/
#define TP_TIMING_VALUE_N_CR (150U * UDS_MS_MULTI_FACTOR) /*150ms*/


#endif
