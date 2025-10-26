#ifndef __SID28_COMMUNICATIONCONTROL_H_
#define __SID28_COMMUNICATIONCONTROL_H_


#include "Dcm_Drv.h"

/*  第四位表接收：1使能0关闭  第五位表示发送：1使能 2关闭  */
#define UDS_EN_RX_TX_NCM 0x31U   /*normalCommunicationMessages*/
#define UDS_EN_RX_TX_NWMCM 0x32U /*networkManagementCommunicationMessage*/
#define UDS_EN_RX_TX_NWMCM_NCM 0x33U
#define UDS_EN_RX_DIS_TX_NCM 0x11U   /*normalCommunicationMessages*/
#define UDS_EN_RX_DIS_TX_NWMCM 0x12U /*networkManagementCommunicationMessage*/
#define UDS_EN_RX_DIS_TX_NWMCM_NCM 0x13U
#define UDS_DIS_RX_EN_TX_NCM 0x21U   /*normalCommunicationMessages*/
#define UDS_DIS_RX_EN_TX_NWMCM 0x22U /*networkManagementCommunicationMessage*/
#define UDS_DIS_RX_EN_TX_NWMCM_NCM 0x23U
#define UDS_DIS_RX_TX_NCM 0x01U   /*normalCommunicationMessages*/
#define UDS_DIS_RX_TX_NWMCM 0x02U /*networkManagementCommunicationMessage*/
#define UDS_DIS_RX_TX_NWMCM_NCM 0x03U
/******************************************************************************
 **                      Typedef  Definitions
 ******************************************************************************/
typedef struct
{
    uint8_t SubID;
    boolean (*pFunc)(uint8_t *, uint8_t *, uint32_t *);
} Struct_Uds_SID_CC;

typedef struct
{
    uint16_t CommuCtrlFlag;
    uint32_t Boot_State255_Delay;
} Struct_Uds_SID_CC_Info;
extern Struct_Uds_SID_CC_Info Uds_SID_CC_Info;
/******************************************************************************
 **                      Export Variables
 ******************************************************************************/

/******************************************************************************
 **                      Export Functions
 ******************************************************************************/
void SID_CC_Analysis(uint8_t *pInd, uint16_t indLen);

boolean SID_CC_Appl_Deal(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);



#endif
