#ifndef __SID3E_TESTERPRSENT_H_
#define __SID3E_TESTERPRSENT_H_

#include "Dcm_Drv.h"

/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
    uint8_t SubID;
    boolean (*pFunc)(uint8_t *, uint32_t *);
} Struct_Uds_SID_TP;

typedef struct
{
    boolean TesterPresentFlag;
} Struct_Uds_SID_TP_Info;
extern Struct_Uds_SID_TP_Info Uds_SID_TP_Info;

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_TP_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_TP_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

#endif
