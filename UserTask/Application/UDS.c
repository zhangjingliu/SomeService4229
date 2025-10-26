#include "UDS.h"


volatile uint32_t TickCount = 0U;

/******************************************************************************
 *                      Function definitions
 ******************************************************************************/

/**
 * @brief
 *
 * @return uint32_t
 */
void UDSInit(void)
{
    TpFunc_Init();
    UdsFunc_Init();
}

void UDS(void)
{
    TpFunc_Send_Handle();
    UdsFunc_Delay1ms_Handle();
    TpFunc_HalfDuplex_Task();
    UdsFunc_Task();
}

#if 0
void Canfd_RxPacketCallback(HLI_Canfd_MessageType RxPdu)
{
    TpFunc_Recv_Handle(RxPdu.ID, RxPdu.DataPtr, RxPdu.DataLength);
}
#endif

void Gpt_OverflowCallback(void)
{
    TickCount++;
}
