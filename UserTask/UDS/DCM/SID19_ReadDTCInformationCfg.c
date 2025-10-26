#include "Dcm_Drv.h"
#include "SID19_ReadDTCInformationCfg.h"
#include "Detdtc.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
extern boolean SID_RDTCI_reportNumberOfDTCByStatusMask_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

extern boolean SID_RDTCI_reportDTCByStatusMask_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

extern boolean SID_RDTCI_reportDTCSnapshotRecordByDTCNumber_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

extern boolean SID_RDTCI_reportDTCExtDataRecordByDTCNumber_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

extern boolean SID_RDTCI_reportSupportedDTC_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_RDTCI Uds_SID_RDTCI[UDS_SID_RDTCI_SUBFUNC_NUMBER] =
{
	{0x01,
	SID_RDTCI_reportNumberOfDTCByStatusMask_Callback},
	{0x02,
	SID_RDTCI_reportDTCByStatusMask_Callback},
	{0x04,
	SID_RDTCI_reportDTCSnapshotRecordByDTCNumber_Callback},
	{0x06,
	SID_RDTCI_reportDTCExtDataRecordByDTCNumber_Callback},
	{0x0A,
	SID_RDTCI_reportSupportedDTC_Callback},

};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
boolean SID_RDTCI_reportNumberOfDTCByStatusMask_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t dtcRecodrNum = 0;
	uint8_t loop;
    volatile const OBD_Dtc_Det_Cfg_Format* pCfg = NULL;
    OBD_Dtc_Type_Format*  ptype = NULL;
    OBD_Dtc_Status_Format* pstatus = NULL;

    for(loop=0; loop<OBD_DTC_LEN; loop++)
    {
        pCfg = &(OBD_DtcConfigTbl[loop]);
        ptype = pCfg->pt_dtc_type;
        pstatus = &(ptype->status);
        if ((pInd[0] & pstatus->status) != 0x00)
		{
        	dtcRecodrNum++;
		}
    }
	pRes[0U] = (uint8_t)0x49; 			/*当前ECU支持的状态位 诊断调查表中*/
	pRes[1U] = (uint8_t)0X01;			/*使用DTC格式，01：14229格式  02：J1939格式*/
	pRes[2U] = (uint8_t)(dtcRecodrNum / 0x100U);
	pRes[3U] = (uint8_t)(dtcRecodrNum);
	pResLen[0] = 4U;

	ret = E_OK;
	return ret;
}

boolean SID_RDTCI_reportDTCByStatusMask_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t loop;
    volatile const OBD_Dtc_Det_Cfg_Format* pCfg = NULL;
    OBD_Dtc_Type_Format*  ptype = NULL;
    OBD_Dtc_Status_Format* pstatus = NULL;
    for(loop=0; loop<OBD_DTC_LEN; loop++)
    {
        pCfg = &(OBD_DtcConfigTbl[loop]);
        ptype = pCfg->pt_dtc_type;
        pstatus = &(ptype->status);
        if ((pInd[0] & pstatus->status) != 0x00)
		{
        	pRes[pResLen[0]+ 0U] = (uint8_t)(((pCfg->id) >> 8)& 0x00FF);
        	pRes[pResLen[0]+ 1U] = (uint8_t)((pCfg->id) & 0x00FF);
        	pRes[pResLen[0]+ 2U] = (uint8_t) pCfg->failure_type;
        	pRes[pResLen[0]+ 3U] = (uint8_t) pstatus->status;
		}
        pResLen[0] += 4U;
    }
	ret = E_OK;
	return ret;
}

boolean SID_RDTCI_reportDTCSnapshotRecordByDTCNumber_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint16_t id;
	uint8_t failtype;
	uint8_t snapshotnum;
	uint8_t loop;
    volatile const OBD_Dtc_Det_Cfg_Format* pCfg = NULL;
    OBD_Dtc_Type_Format*  ptype = NULL;
    OBD_Dtc_Status_Format* pstatus = NULL;
    OBD_Dtc_Info_Format* pinfo = NULL;
    OBD_Global_Snapshot_Format * psnapshot = NULL;

    id = (uint16_t)((((uint16_t)(pInd[0])) << 8 ) | (pInd[1]));
    failtype = pInd[2];
    snapshotnum = pInd[3];
    for(loop=0; loop < OBD_DTC_LEN; loop++)
    {
        pCfg = &(OBD_DtcConfigTbl[loop]);
        ptype = pCfg->pt_dtc_type;
        pstatus = &(ptype->status);
        pinfo = &(ptype->information);
        psnapshot = &(pinfo->snapshot);

        if ((id == pCfg->id) && (failtype == pCfg->failure_type))
        {
            break;
        }
    }
    if ( loop == OBD_DTC_LEN )
    {
    	ret = UDS_RES_CODE_ROOR;
    }
    else
    {
    	pRes[0U] = (uint8_t)pInd[0];
    	pRes[1U] = (uint8_t)pInd[1];
    	pRes[2U] = (uint8_t)pInd[2];
    	pRes[3U] = (uint8_t)pstatus->status;  	/*返回当前DTC的状态*/
    	pRes[4U] = snapshotnum;					/*第几个快照记录*/
    	switch (snapshotnum)
    	{
    		case 0x01:
    		{
    			pRes[5U] = (uint8_t)0x00;
				pRes[6U] = (uint8_t)0x02;
				pRes[7U] = (uint8_t)0x02;
				pRes[8U] = (uint8_t)0x11;
				pRes[9U] = (uint8_t)0x11;
				pRes[10U] = (uint8_t)0x11;
				pRes[11U] = (uint8_t)0x11;
				pResLen[0] = 12U;
    			break;
    		}
    		case 0xFF: /*DTC的所有快照信息*/
    		{
    			pRes[5U] = (uint8_t)0x01; /*第几个快照记录*/
				pRes[6U] = (uint8_t)0x02;
				pRes[7U] = (uint8_t)0x02;
				pRes[8U] = (uint8_t)0x11;
				pRes[9U] = (uint8_t)0x11;
				pRes[10U] = (uint8_t)0x11;
				pRes[11U] = (uint8_t)0x11;
				pResLen[0] = 12U;
				break;
    		}
    		default:
    		{
    			ret = UDS_RES_CODE_ROOR;
    			break;
    		}
    	}
    }
	ret = E_OK;
	return ret;
}

boolean SID_RDTCI_reportDTCExtDataRecordByDTCNumber_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint16_t id;
	uint8_t failtype;
	uint8_t loop;
	volatile const OBD_Dtc_Det_Cfg_Format* pCfg = NULL;
	OBD_Dtc_Type_Format*  ptype = NULL;
	OBD_Dtc_Status_Format* pstatus = NULL;

    id = (uint16_t)((((uint16_t)(pInd[0])) << 8 ) | (pInd[1]));
    failtype = pInd[2];

    for(loop=0; loop < OBD_DTC_LEN; loop++)
    {
        pCfg = &(OBD_DtcConfigTbl[loop]);
        ptype = pCfg->pt_dtc_type;
        pstatus = &(ptype->status);

        if ((id == pCfg->id) && (failtype == pCfg->failure_type))
        {
            break;
        }
    }

    if ( loop == OBD_DTC_LEN )
    {
    	ret = UDS_RES_CODE_ROOR;
    }
    else
    {
    	pRes[0] = pInd[0];
    	pRes[1] = pInd[1];
    	pRes[2] = pInd[2];
    	pRes[3] = pstatus->status;
    	pRes[4] = 0x01U;                /* DTCExtendedDataRecordNumber */
    	pRes[5] = ptype->extended_data.fault_occur_counter;
    	pRes[6] = ptype->extended_data.fault_pending_counter;
    	pRes[7] = ptype->extended_data.aged_counter;
    	pRes[8] = ptype->extended_data.ageing_counter;
    	pResLen[0] = 9U;
    }

	ret = E_OK;
	return ret;
}

boolean SID_RDTCI_reportSupportedDTC_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint8_t loop;

    volatile const OBD_Dtc_Det_Cfg_Format* pCfg = NULL;
    OBD_Dtc_Type_Format*  ptype = NULL;
    OBD_Dtc_Status_Format* pstatus = NULL;

    pRes[0] = 0x49U;
    pResLen[0] = 1U;
    for(loop=0; loop<OBD_DTC_LEN; loop++)
    {
            pCfg = &(OBD_DtcConfigTbl[loop]);
            ptype = pCfg->pt_dtc_type;
            pstatus = &(ptype->status);
            pRes[pResLen[0]] = (uint8_t)(((pCfg->id) >> 8U )  & 0xFF);
            pRes[(pResLen[0]) + 1U] = (uint8_t)((pCfg->id)  & 0xFF);
            pRes[(pResLen[0]) + 2U] = pCfg->failure_type;
            pRes[(pResLen[0]) + 3U] = pstatus->status;
            pResLen[0] += 4U;
    }

	ret = E_OK;
	return ret;
}
