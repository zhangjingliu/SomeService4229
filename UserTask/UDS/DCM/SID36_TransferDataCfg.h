#ifndef __SID36_TRANSFERDATACFG_H_
#define __SID36_TRANSFERDATACFG_H_

#include "SID36_TransferData.h"

typedef	struct
{
	boolean	b_TransferDataFlag;
	uint32_t	ui32_LastCrcValue;
}Struct_Uds_SID_TD_Info;
extern	Struct_Uds_SID_TD_Info	st_Uds_SID_TD_Info;

extern	uint8_t ui8_NewBlockSequenceCounter;
extern	uint8_t ui8_LastBlockSequenceCounter;

extern boolean SID_TD_Callback(uint8_t *pInd, uint16_t indLen, uint8_t *pRes, uint32_t *pResLen);

#endif 
