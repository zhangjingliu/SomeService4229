#ifndef __SID31_ROUTINECONTROL_H_
#define __SID31_ROUTINECONTROL_H_

#include "Dcm_Drv.h"

/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
    uint8_t SubID;
    boolean (*pFunc)(uint8_t *, uint8_t *, uint32_t *);
} Struct_Uds_SID_RC;

typedef struct
{
    uint32_t SectorAddrStart;
    uint32_t SectorAddrEnd;
} StructEraseSector;

typedef struct
{
    uint8_t STR_Flag;
    boolean EraseStartFlag;
    uint8_t EraseSectorIndex;
    uint8_t EraseSectorEnd;
    uint32_t EraseAddr;
    uint32_t EraseSize;
} Struct_Uds_SID_RC_Info;

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_RC_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_RC_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);


#endif

