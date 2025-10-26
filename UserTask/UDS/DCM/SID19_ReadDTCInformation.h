#ifndef __SID19_READDTCINFORMATION_H_
#define __SID19_READDTCINFORMATION_H_

#include "Dcm_Drv.h"

/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
uint8_t SubID;
boolean (*pFunc)(uint8_t *, uint8_t *, uint32_t *);
} Struct_Uds_SID_RDTCI;

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_RDTCI_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_RDTCI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *resLen);


#endif
