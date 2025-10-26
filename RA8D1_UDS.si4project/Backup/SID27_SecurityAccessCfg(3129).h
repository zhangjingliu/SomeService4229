#ifndef __SID27_SECURITYACCESSCFG_H_
#define __SID27_SECURITYACCESSCFG_H_

#include "SID27_SecurityAccess.h"

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define MASK_VALUE 0x55ACF799U

#define SID_SA_SUBFUNC_NUMBER 4U
/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
extern const Struct_Uds_SID_SA Uds_SID_SA[SID_SA_SUBFUNC_NUMBER];

#endif
