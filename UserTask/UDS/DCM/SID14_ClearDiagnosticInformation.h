#ifndef __SID14_CLEARDIAGNOSTICINFORMATION_H_
#define __SID14_CLEARDIAGNOSTICINFORMATION_H_


#include "Dcm_Drv.h"

typedef struct
{
    uint32_t GODTC;
    boolean (*pFunc)(uint8_t *, uint32_t *);
} Struct_Uds_SID_CDTCI;
/******************************************************************************
 **                      Export Variables
 ******************************************************************************/

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_CDTCI_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_CDTCI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *resLen);


#endif
