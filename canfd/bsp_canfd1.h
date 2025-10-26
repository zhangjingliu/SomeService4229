#ifndef __BSP_CANFD_1_H
#define	__BSP_CANFD_1_H
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

/**
 * @brief Canfd message frame type
 */
typedef enum
{
    /**
     * @brief Classical frame
     */
    HLI_CANFD_FRAME_CLASSICAL,

    /**
     * @brief FD frame
     */
    HLI_CANFD_FRAME_FD,
} HLI_Canfd_MsgFrameType;


/**
 * @brief Canfd message Id type
 */
typedef enum
{
    /**
     * @brief Standard Id data frame
     */
    HLI_CANFD_DATA_STD,

    /**
     * @brief Extended Id data frame
     */
    HLI_CANFD_DATA_EXT,
} HLI_Canfd_MsgIDType;


typedef struct
{
    /**
     * @brief Frame Id
     */
    uint32_t ID;

    /**
     * @brief Frame data length, unit: byte
     */
    uint8_t DataLength;

    /**
     * @brief Frame data buffer pointer
     */
    uint8_t *DataPtr;

    /**
     * @brief Id type
     */
    HLI_Canfd_MsgIDType IDType;

    /**
     * @brief Frame type
     */
    HLI_Canfd_MsgFrameType FrameType;

} HLI_Canfd_MessageType;


extern can_frame_t canfd1_tx_frame; //CAN transmit frame
extern can_frame_t canfd1_rx_frame;

void CANFD1_Init(void);
void CAN1_Operation(void);
void CANFD1_Operation(void);

void CANFD1_SendMessage(uint32_t U32_transmitCANid, uint8_t *U8_dataarr, uint8_t U8_DLC);
void CAN1_SendMessage(uint32_t U32_transmitCANid, uint8_t *U8_dataarr, uint8_t U8_DLC);


void HLI_CanFD_Write(HLI_Canfd_MessageType MsgPtr);

#endif
