#ifndef __BSP_CANFD_0_H
#define	__BSP_CANFD_0_H
#include "hal_data.h"
#include "stdio.h"
#include "CANFD_A2B.h"


// CANFD1模块的调试信息输出控制
#define CANFD1_DEBUG                    1
#if (1 == CANFD1_DEBUG)
  #define CANFD1_MSG_PRINTF(format, ...)  printf("[CANFD1 Operation] "format"\r\n", ##__VA_ARGS__)
#else
  #define CANFD1_MSG_PRINTF(format, ...)
#endif


#define CAN_MAILBOX_NUMBER_0            (CANFD_TX_MB_0)    //邮箱号码
#define CAN_CLASSIC_FRAME_DATA_BYTES    (8U)               //用于经典帧的数据长度代码
#define CAN_FD_DATA_LENGTH_CODE         (12)               //FD帧的数据长度编码
#define CAN_ID                          (0x1100)           //要在传输帧中更新的ID

/* 验收过滤器数组参数 */
#define CANFD_FILTER_ID                 (0x00001000)
#define MASK_ID                         (0x1FFFF000)
#define MASK_ID_MODE                    (1)


#define WAIT_TIME                       (0xFFFF)

extern can_frame_t canfd0_tx_frame; //CAN transmit frame
extern can_frame_t canfd0_rx_frame;

void CANFD0_Init(void);
void CAN0_Operation(void);
void CANFD0_Operation(void);

void CANFD0_SendMessage(uint32_t U32_transmitCANid, uint8_t *U8_dataarr, uint8_t U8_DLC);
void CAN0_SendMessage(uint32_t U32_transmitCANid, uint8_t *U8_dataarr, uint8_t U8_DLC);


void HLI_CanFD0_Write(can_frame_t MsgPtr);

#endif
