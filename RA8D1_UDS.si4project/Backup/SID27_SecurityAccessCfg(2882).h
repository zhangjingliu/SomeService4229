#ifndef __SID27_SECURITYACCESSCFG_H_
#define __SID27_SECURITYACCESSCFG_H_

#include "SID27_SecurityAccess.h"
#include "aes_cbc_cmac.h"

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define SID_SA_SUBFUNC_NUMBER 4U
/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
extern const Struct_Uds_SID_SA Uds_SID_SA[SID_SA_SUBFUNC_NUMBER];

#endif
