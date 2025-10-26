#ifndef __SID34_REQUESTDOWNLOAD_H_
#define __SID34_REQUESTDOWNLOAD_H_


#include "Dcm_Drv.h"

extern void SID_RD_Analysis(uint8_t *pInd, uint16_t indLen);

extern boolean SID_RD_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

#endif 
