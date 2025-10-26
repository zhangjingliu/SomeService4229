#ifndef __DCM_DRVCFG_H_
#define __DCM_DRVCFG_H_

#include "Dcm_Drv.h"
#include "AB_Swap.h"

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define UDS_SID_NUMBER 14U /*SID  num*/

#define UDS_CAN_PHY_ADDR 0x7F0U
#define UDS_CAN_FUNC_ADDR 0x7DFU
#define UDS_CAN_TX_ADDR 0x7F8U

#define UDS_ADDR_TYPE_PHY UDS_ADDR_TYPE_CANFD_BASE_PHY
#define UDS_ADDR_TYPE_FUNC UDS_ADDR_TYPE_CANFD_BASE_FUNC

#define UDS_APPL_DL_MAX 4095U /*UDS TP MAX Buf*/

#define UDS_P2_SERVER_MAX 50U    /*P2Server  50ms*/
#define UDS_P2EX_SERVER_MAX 5000U /*P2*Server 5000ms*/

#define UDS_MS_MULTI_FACTOR 1U                         /*ms TASK*/
#define UDS_US_DIVIDE_FACTOR 2U                         /*us TASK*/
#define UDS_S3_SERVER_MAX (5000U * UDS_MS_MULTI_FACTOR) /*S3Server 2500*/

#define MAX_BLOCK_SIZE      3840U
#define PAGE_SIZE   		256U
#define MIN_BLOCK_SIZE      64U
#define	INVALID_PAGE_SIZE	0U

#define	APPL_VALID_FLAG_ADDR		0x00017800U

/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
/*define session mode*/
#define DEFALUT_SESSION (1u << 0u)       /*default session*/
#define PROGRAM_SESSION (1u << 1u)       /*program session*/
#define EXTEND_SESSION  (1u << 2u)       /*extend session*/

/******************************************************************************
 **                      Export Variables
 ******************************************************************************/
extern const Struct_Uds_Cfg_Info Uds_Cfg_Info[UDS_SID_NUMBER];

extern boolean b_Stay_In_Boot_Flag;       /*StayInBoot*/
extern boolean b_DownLoad_FlashDrv_Flag;
extern boolean b_Checkapp_Success;
/******************************************************************************
 **                      Export Functions
 ******************************************************************************/

#endif
