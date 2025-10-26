#ifndef USERTASK_APPLICATION_UDS_H_
#define USERTASK_APPLICATION_UDS_H_

/******************************************************************************
 *                      Include Files
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "AB_Swap_Config.h"

#include "hal_data.h"
#include "bsp_debug_uart.h"
#include "Systick.h"
#include "bsp_canfd1.h"

#include "Tp_Can_Drv.h"
#include "SID10_DiagnosticSessionControl.h"
#include "SID11_ECUReset.h"

/******************************************************************************
 *                      Macro or Inline
 ******************************************************************************/

/******************************************************************************
 *                      Export Variables
 ******************************************************************************/
extern volatile uint32_t TickCount;

/******************************************************************************
 *                      Export Functions
 ******************************************************************************/

void UDSInit(void);

void UDS(void);

void Gpt_OverflowCallback(void);

#endif 
