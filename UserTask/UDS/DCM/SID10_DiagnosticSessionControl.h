#ifndef __SID10_DIAGNOSTICSESSIONCONTROL_H_
#define __SID10_DIAGNOSTICSESSIONCONTROL_H_

#include "Dcm_Drv.h"
/******************************************************************************
 **                      File Version Check
 ******************************************************************************/

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
/*UDS Session*/
#define UDS_DEFAULT_SESSION_ACTIVE 0x01U	 /*Default Session*/
#define UDS_PROGRAMMING_SESSION_ACTIVE 0x02U /*Programming Session*/
#define UDS_EXTENDED_SESSION_ACTIVE 0x04U	 /*Extended Session*/
/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
	uint8_t SubID;							 /*服务子功能ID*/
	boolean (*pFunc)(uint8_t *, uint32_t *); /*子功能回调函数*/
} Struct_Uds_SID_DSC;

typedef struct
{
	uint8_t Active_Session; /*会话类型*/
} Struct_Uds_SID_DSC_Info;

/******************************************************************************
 **                      Export Variables
 ******************************************************************************/
extern Struct_Uds_SID_DSC_Info Uds_SID_DSC_Info;
/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void ChangeSession_Init(void);

void SID_DSC_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_DSC_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

#endif
