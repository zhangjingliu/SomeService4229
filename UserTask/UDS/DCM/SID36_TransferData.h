#ifndef __SID36_TRANSFERDATA_H_
#define __SID36_TRANSFERDATA_H_

#include "Dcm_Drv.h"

#define	UDS_SID_TP_SUBFUNC_NUMBER		1U

typedef	struct
{
	uint8_t	ui8_SubID;
	boolean	(*pFunc)(uint8_t*, uint16_t*);
}Struct_Uds_SID_TD;


extern void SID_TD_Analysis(uint8_t *pInd, uint16_t indLen);

extern boolean SID_TD_Appl_Deal(uint8_t *pInd, uint16_t indLen, uint8_t *pRes, uint32_t *pResLen);

#endif 
