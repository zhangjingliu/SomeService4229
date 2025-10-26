#ifndef __SID11_ECURESET_H_
#define __SID11_ECURESET_H_

#include "Dcm_Drv.h"

/******************************************************************************
**                      Typedef  Definitions
******************************************************************************/
typedef struct
{
  uint8_t SubID;
  boolean (*pFunc)(uint8_t *, uint32_t *);
} Struct_Uds_SID_ER;

typedef struct
{
  boolean HardResetFlag;
} Struct_Uds_SID_ER_Info;

/******************************************************************************
**                      Export Variables
******************************************************************************/
extern Struct_Uds_SID_ER_Info Uds_SID_ER_Info;
/******************************************************************************
**                      Export Functions
******************************************************************************/
void SID_ER_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_ER_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);


#endif
