#include "Detdtc.h"

/******************************************************************************
 *                      Macro Definitions                                      *
 ******************************************************************************/
#define DTC_CONTROL_MASK(ctrl)     (DTC_ControlBit[(ctrl >> 4)&0x0F] & (1 << (ctrl & 0x0F)))
/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/

/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
uint8_t DETDTC_trip;
uint8_t DETDTC_Control;
uint8_t ECU_Status;
uint8_t COM_Status;
uint8_t DETFUN_MotorFailedCnt;

static uint8_t DETDTC_NotInCrnkEngStr10ms;
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*************************************************************************/
/*
Function:		void DETDTC_ReadData(void)

Description:	when operation trip is OFF, something is needed to be done

Parameters: 	void

Return:       	void
*/
static void DETDTC_TripOff(volatile const OBD_Dtc_Det_Cfg_Format*  pCfg )
{
    OBD_Dtc_Type_Format*  ptype = NULL;
    OBD_Dtc_Status_Format* pstatus = NULL;
    OBD_Extended_Data_Format* pextend_data = NULL;

    ptype = pCfg->pt_dtc_type;
    pstatus = &(ptype->status);
    pextend_data = &(ptype->extended_data);

    if ( (pstatus->DTC_bit.testFailedThisOperCyc == 0)
     &&(pstatus->DTC_bit.testNotCompletedThisOperCyc == 0))
    {
        pstatus->DTC_bit.pendingDTC = 0;
        pextend_data->fault_pending_counter = 0;
        pextend_data->ageing_counter++;
    }
}

/*************************************************************************/
/*
Function:		void DETDTC_ReadData(void)

Description:	when soft begin to init, related information shall be recoverd from EEROM

Parameters: 	void

Return:       	void
*/
static void DETDTC_ReadData(void )
{
	uint8_t loop;
	uint8_t saveddatabuffer[20] = {0U};
    volatile const OBD_Dtc_Det_Cfg_Format* pCfg = NULL;
    OBD_Dtc_Type_Format*  ptype = NULL;
    OBD_Dtc_Status_Format* pstatus = NULL;
    OBD_Extended_Data_Format* pextend_data = NULL;
    OBD_Dtc_Info_Format* pinfo = NULL;

    /* polled the Dtc Configruation Table */
    for(loop=0; loop<OBD_DTC_LEN; loop++)
    {
        pCfg = &(OBD_DtcConfigTbl[loop]);
        ptype = pCfg->pt_dtc_type;
        pstatus = &(ptype->status);
        pextend_data = &(ptype->extended_data);
        pinfo = &(ptype->information);

        pinfo->id = pCfg->id;
        pinfo->failure_type = pCfg->failure_type;

     	/* read data from EEROM*/
//        vdg_EE_ReadEEPROM_ENFORE(pCfg->eerom_index, saveddatabuffer);

        if ( saveddatabuffer[0] != 0xFF )
        {
            pinfo->snapshot.global_power_mode = saveddatabuffer[0];
            pinfo->snapshot.voltage = saveddatabuffer[1];
            ptype->status.status = saveddatabuffer[2];
            ptype->extended_data.fault_occur_counter = saveddatabuffer[3];
            ptype->extended_data.fault_pending_counter = saveddatabuffer[4];
            ptype->extended_data.ageing_counter = saveddatabuffer[5];
            ptype->extended_data.aged_counter = saveddatabuffer[6];
        }

        DETDTC_TripOff(pCfg);
        pstatus->DTC_bit.testFailed = 0U;
        pstatus->DTC_bit.testFailedThisOperCyc= 0U;
        pstatus->DTC_bit.testNotCompletedThisOperCyc = 0U;
        ptype->fault_detect_count = 0U;
        ptype->monitor_rate = 1U;
    }
}

/*************************************************************************/
/*
Function:		void DETDTC_ChkMonCondition(void)

Description:	when any DTC is detecting, checking the trip status

Parameters: 	void

Return:       	void
*/
static void DETDTC_ChkMonCondition(void)
{

}

/*************************************************************************/
/*
Function:		void vdg_DETDTC_Init(void)

Description:

Parameters: 	void

Return:       	void
*/
void DETDTC_Init(void)
{
    DETDTC_trip |= OBD_DTC_OPR_WAKEUP;
    DETDTC_Control = 1U;
    COM_Status = OBD_DTC_OPR_COMEN;
    DETFUN_MotorFailedCnt = 0;

    DETDTC_ReadData();
}

/**********************************************************************************************/
/* function name: vdg_DETDTC_10ms                                                             */
/* parameter    : NULL                                                                        */
/* return       : NULL                                                                        */
/* description  : 10ms                                                                        */
/**********************************************************************************************/
void DETDTC_10ms(uint8_t startindex, uint8_t endIndex)
{
	uint8_t loop;
	uint8_t ctrl;
	uint8_t testfailThisOperCyc_o;
	uint8_t confirmed_o;
	uint8_t testFailed_o;
	uint8_t rtval;
	uint8_t dtctxdatabuf[8] = {0};
    static uint8_t writeEEFlag = 0;
    static uint16_t delaytime10ms = 0;
    volatile const OBD_Dtc_Det_Cfg_Format* pCfg = NULL;
    OBD_Dtc_Type_Format*  ptype = NULL;
    OBD_Dtc_Status_Format* pstatus = NULL;
    OBD_Extended_Data_Format* pextend_data = NULL;

    if(delaytime10ms >= 400)
    {
        writeEEFlag = 1U;
    }
    else
    {
        delaytime10ms++;
    }
    if(startindex == 0)
    {
    	DETDTC_ChkMonCondition();
    }
    rtval = OBD_PRECON_NG;
    for(loop=startindex; loop< endIndex; loop++)
    {
        pCfg = &(OBD_DtcConfigTbl[loop]);
        ptype = pCfg->pt_dtc_type;
        pstatus = &(ptype->status);
        pextend_data = &(ptype->extended_data);
        /*ECU DTC码在什么状态下可正常检测记录*/
        if (( DETDTC_trip & (pCfg->dtc_trip_mask )) != 0U)
        {
            ctrl = (uint8_t)DTC_CONTROL_MASK(pCfg->contorl);
            /*非无效DTC*/
            if ((ctrl != 0U)&&( DETDTC_Control == 1U ))
            {
                if (pCfg->monitor_threshold == ptype->monitor_rate )
                {
                    if (pCfg->dtc_detect_fun != NULL )
                    {
                        rtval = pCfg->dtc_detect_fun();
                        if ( rtval == OBD_PRECON_OK )
                        {
                            ptype->monitor_rate = 1U;

                            if (*(pCfg->failed_flag) == Faulted)
                            {
                                if (ptype->fault_detect_count < 0U)
                                {
                                    ptype->fault_detect_count = 0U;
                                }
                                ptype->fault_detect_count += pCfg->fail_increment;
                            }
                            if (*(pCfg->failed_flag) == Passed)
                            {
                                if (ptype->fault_detect_count > 0U)
                                {
                                    ptype->fault_detect_count = 0U;
                                }
                                ptype->fault_detect_count -= pCfg->pass_decrement;
                            }
                            if (ptype->fault_detect_count >= pCfg->fail_threshold)
                            {
                                ptype->fault_detect_count = pCfg->fail_threshold;
                                /*之前的故障失效记录*/
                                testfailThisOperCyc_o =  pstatus->DTC_bit.testFailed;
                                confirmed_o = pstatus->DTC_bit.confirmedDTC;
                                pstatus->DTC_bit.testFailed = 1U;
                                pstatus->DTC_bit.confirmedDTC = 1U;
                                pextend_data->fault_pending_counter = 1U;
                                /*第一次发送故障，记录扩展数据*/
                                if ( testfailThisOperCyc_o == 0U)
                                {
                                	ptype->dtc_up_req = 1U;
                                    if (pextend_data->fault_occur_counter < 0xFF)
                                    {
                                        pextend_data->fault_occur_counter++;
                                        ptype->info_status &=  0x0F;
                                        ptype->info_status |=  OBD_DTC_EXDATA_READY;
                                    }
                                }
                                /*老化次数清零*/
                                pextend_data->ageing_counter = 0U;
                            }
                            if (ptype->fault_detect_count <= -(pCfg->pass_threshold))
                            {
                                testFailed_o = pstatus->DTC_bit.testNotCompletedThisOperCyc;
                                ptype->fault_detect_count = -(pCfg->pass_threshold);
                                if(pstatus->DTC_bit.testFailed != 0U)
                                {
									ptype->dtc_up_req = 1U;
                                }
                                pstatus->DTC_bit.testFailed = 0U;
                                pstatus->DTC_bit.pendingDTC = 0U;
                                pstatus->DTC_bit.testFailedThisOperCyc= 0U;
                                pstatus->DTC_bit.testNotCompletedSinceLastClr = 0U;
                                pstatus->DTC_bit.testNotCompletedThisOperCyc = 0U;
                                if (( testFailed_o == 1)&&(pstatus->DTC_bit.confirmedDTC == 1U))
                                {
                                    pextend_data->fault_pending_counter = 0U;
                                    pextend_data->ageing_counter++;
                                    ptype->info_status &=  0x0FU;
                                    ptype->info_status |=  OBD_DTC_EXDATA_READY;
                                }
                            }
                            if (pextend_data->ageing_counter >= pCfg->aged_trip_cnt)  /* DTC aging mechanism */
                            {
                                pextend_data->ageing_counter = 0U;

                                if(pextend_data->aged_counter < (uint8_t)0xFF)
                                {
                                    pextend_data->aged_counter++;
                                }

                            }
                        }
                    }
                }
                else
                {
                    if (ptype->monitor_rate < 0xFFU)
                    {
                        ptype->monitor_rate++;
                    }
                }
            }
        }
        if(writeEEFlag == 1)
        {

        }

    }
}
