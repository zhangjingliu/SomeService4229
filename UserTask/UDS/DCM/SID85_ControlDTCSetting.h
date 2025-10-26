#ifndef __SID85_CONTROLDTCSETTING_H_
#define __SID85_CONTROLDTCSETTING_H_


#include "Dcm_Drv.h"
/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
    uint8_t SubID;
    boolean (*pFunc)(uint8_t *, uint32_t *);
} Struct_Uds_SID_CDTCS;

typedef struct
{
    uint8_t DTCSettingType;
} Struct_Uds_SID_CDTCS_Info;
extern Struct_Uds_SID_CDTCS_Info Uds_SID_CDTCS_Info;
/******************************************************************************
 **                      Export Variables
 ******************************************************************************/

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_CDTCS_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_CDTCS_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);


#endif
