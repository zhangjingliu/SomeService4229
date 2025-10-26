#ifndef __SID22_READDATABYLDENTIFIER_H_
#define __SID22_READDATABYLDENTIFIER_H_

#include "Dcm_Drv.h"

/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
    uint16_t DID;
    boolean (*pFunc)(uint8_t *, uint32_t *);
} Struct_Uds_SID_RDBI;
/******************************************************************************
 **                      Export Variables
 ******************************************************************************/

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_RDBI_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_RDBI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

#endif
