#ifndef __SID37_REQUESTTRANSFEREXIT_H_
#define __SID37_REQUESTTRANSFEREXIT_H_

#include "Dcm_Drv.h"

extern void SID_RTE_Analysis(uint8_t *ui8_pInd, uint16_t ui16_IndLen);

extern boolean SID_RTE_Appl_Deal(uint8_t *ui8_pInd, uint8_t *ui8_pRes, uint32_t *ui16_pResLen);

#endif 
