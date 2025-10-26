#ifndef __SID85_CONTROLDTCSETTINGCFG_H_
#define __SID85_CONTROLDTCSETTINGCFG_H_


#include "SID85_ControlDTCSetting.h"


/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define UDS_SID_CDTCS_SUBFUNC_NUMBER 4U

#define UDS_CDTCS_ON 0x01U  /*DTC ON*/
#define UDS_CDTCS_OFF 0x02U /*DTC OFF*/
/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/


/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
extern const Struct_Uds_SID_CDTCS Uds_SID_CDTCS[UDS_SID_CDTCS_SUBFUNC_NUMBER];


#endif
