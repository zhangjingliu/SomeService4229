#ifndef __SID2E_WRITEDATABYLDENTIFIER_H_
#define __SID2E_WRITEDATABYLDENTIFIER_H_

#include "Dcm_Drv.h"

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define UDS_SID_WDBI_DID_NUMBER 1U
/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
    uint16_t DID;
    uint32_t DataLen;
    boolean (*pFunc)(uint8_t *, uint8_t *, uint32_t *);
} Struct_Uds_SID_WDBI;
/******************************************************************************
 **                      Export Variables
 ******************************************************************************/
extern const Struct_Uds_SID_WDBI Uds_SID_WDBI[UDS_SID_WDBI_DID_NUMBER];
/******************************************************************************
 **                      Export Functions
 ******************************************************************************/

void SID_WDBI_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_WDBI_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);


#endif
