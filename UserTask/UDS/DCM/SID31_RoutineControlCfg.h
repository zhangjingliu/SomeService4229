#ifndef __SID31_ROUTINECONTROLCFG_H_
#define __SID31_ROUTINECONTROLCFG_H_

#include "SID31_RoutineControl.h"

/******************************************************************************
 **                      Macro  Definitions
 ******************************************************************************/
#define SID_RC_SUBFUNC_NUMBER 5U

#define SID_RC_DID_F000 0xF000U
#define SID_RC_DID_FF00 0xFF00U
#define SID_RC_DID_F001 0xF001U /*CheckMemory*/
#define SID_RC_DID_FF01 0xFF01U /*checkProgrammingDependencies*/
#define SID_RC_DID_0203 0x0203U /*checkProgrammingPreconditions*/

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
extern const Struct_Uds_SID_RC Uds_SID_RC[SID_RC_SUBFUNC_NUMBER];

#endif
