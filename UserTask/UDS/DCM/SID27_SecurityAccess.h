#ifndef __SID27_SECURITYACCESS_H_
#define __SID27_SECURITYACCESS_H_

#include "Dcm_Drv.h"

/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
	uint8_t SubID;
	boolean (*pFunc)(uint8_t *, uint8_t *, uint32_t *);
} Struct_Uds_SID_SA;

typedef struct
{
	boolean Security_Locked;
	boolean RequestSeedFlag;
	uint8_t FailCount;
	uint32_t AccessDelay;
} Struct_Uds_SID_SA_Info;

/******************************************************************************
 **                      Export Variables
 ******************************************************************************/
extern Struct_Uds_SID_SA_Info Uds_SID_SA_Info;
/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_SA_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_SA_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

#endif
