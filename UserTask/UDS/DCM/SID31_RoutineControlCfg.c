#include "Dcm_DrvCfg.h"
#include "SID31_RoutineControlCfg.h"
#include "SID34_RequestDownloadCfg.h"
#include "bsp_debug_uart.h"
#include "bsp_canfd1.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_RC_SUBID_STR_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

boolean SID_RC_SUBID_STPR_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

boolean SID_RC_SUBID_RRR_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

Struct_Uds_SID_RC_Info	Uds_SID_RC_Info;

uint8_t FlashWriteDataBuffer_APPflag[1030] = {0};
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_RC Uds_SID_RC[SID_RC_SUBFUNC_NUMBER] =
	{
		{0x01U,
		 SID_RC_SUBID_STR_Callback},
		{0x02U,
		 SID_RC_SUBID_STPR_Callback},
		{0x03U,
		 SID_RC_SUBID_RRR_Callback},
};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/*********************************************************************
* Function Name:
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Limitations:
*
*********************************************************************/
Std_ReturnType Dcm_CheckProgrammingPreConditions(void)
{
    /*This function does nothing.*/
    return E_OK;
}

/*************************************************************************/
/*
Function:		void SID_RC_SUBID_STR_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RC_SUBID_STR_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	boolean	b_ValidFlag;
	uint16_t did;
	uint16_t loop;

	did = (uint16_t)pInd[0U] * 0x100U + pInd[1U];
	switch (did)
	{
	case SID_RC_DID_F000:
	{
		ret = E_OK;
		break;
	}

	case SID_RC_DID_FF00:
	{
		Uds_SID_RC_Info.STR_Flag = true;

		if(b_DownLoad_FlashDrv_Flag == true)
		{
			if(Uds_SID_RC_Info.EraseStartFlag == false)
			{
				if(pInd[2U] == 0x44U)
				{
					Uds_SID_RC_Info.EraseAddr = (uint32_t)pInd[3U] * 0x100U * 0x100U * 0x100U;
					Uds_SID_RC_Info.EraseAddr += (uint32_t)pInd[4U] * 0x100U * 0x100U;
					Uds_SID_RC_Info.EraseAddr += (uint32_t)pInd[5U] * 0x100U;
					Uds_SID_RC_Info.EraseAddr += (uint32_t)pInd[6U];

					Uds_SID_RC_Info.EraseSize = (uint32_t)pInd[7U] * 0x100U * 0x100U * 0x100U;
					Uds_SID_RC_Info.EraseSize += (uint32_t)pInd[8U] * 0x100U * 0x100U;
					Uds_SID_RC_Info.EraseSize += (uint32_t)pInd[9U] * 0x100U;
					Uds_SID_RC_Info.EraseSize += (uint32_t)pInd[10U];

					b_ValidFlag = false;
					if((Uds_SID_RC_Info.EraseAddr >= MEMM_LB1_START_ADDR) && (Uds_SID_RC_Info.EraseSize >= 0U)
							&& ((Uds_SID_RC_Info.EraseAddr + Uds_SID_RC_Info.EraseSize - 1U) <= MEMM_LB1_END_ADDR))
					{
						b_ValidFlag = true;
					}
					else if((Uds_SID_RC_Info.EraseAddr >= MEMM_LB2_START_ADDR) && (Uds_SID_RC_Info.EraseSize > 0U)
							&& ((Uds_SID_RC_Info.EraseAddr + Uds_SID_RC_Info.EraseSize - 1U) <= MEMM_LB2_END_ADDR))
					{
						b_ValidFlag = true;
					}

					if(b_ValidFlag == true)
					{
						Uds_SID_RC_Info.EraseSectorIndex = 0U;
						Uds_SID_RC_Info.EraseSectorEnd = (Uds_SID_RC_Info.EraseSize >> 11U) - 1U;
						
						Uds_SID_RC_Info.EraseStartFlag = true;
						Uds_Response.ResCode = UDS_RES_CODE_RCRRP;
						ret = E_NOT_OK;
					}
					else
					{
						Uds_Response.ResCode = UDS_RES_CODE_ROOR;
						ret = E_OK;
					}
				}
				else
				{
					Uds_Response.ResCode = UDS_RES_CODE_ROOR;
					ret = E_OK;
				}
			}
			else
			{
				if(Uds_SID_RC_Info.EraseSectorIndex <= Uds_SID_RC_Info.EraseSectorEnd )
				{			
//					if(HLI_FLS_STATUS_OK ==HLI_Fls_EraseSector((Uds_SID_RC_Info.EraseAddr + BACKUP_AREA_ADDR),0x800))
					{
						Uds_SID_RC_Info.EraseAddr += 0x800;
					}

					Uds_SID_RC_Info.EraseSectorIndex++;

					if(Uds_SID_RC_Info.EraseSectorIndex <= Uds_SID_RC_Info.EraseSectorEnd)
					{
						Uds_Response.ResCode = UDS_RES_CODE_RCRRP;
						ret = E_NOT_OK;
					}
					else
					{
						Uds_SID_RC_Info.EraseStartFlag = false;
						pResLen[0U] = 3U;
						pRes[0U] = (uint8_t)(did / 0x100U);
						pRes[1U] = (uint8_t)(did);
						pRes[2U] = 0U;	/*correctResult*/
						Uds_Response.ResCode = UDS_RES_CODE_PR;
						ret = E_OK;
					}

				}
				else
				{
				}
			}
		}
		else
		{
			Uds_Response.ResCode = UDS_RES_CODE_CNC;
			ret = E_OK;
		}
		break;
	}

	case SID_RC_DID_F001:
	{
		pResLen[0U] = 3U;
		pRes[2U] = 0x01U;
		Uds_Response.ResCode = UDS_RES_CODE_PR;
		ret = E_OK;
		break;
	}

	case SID_RC_DID_FF01:
	{
		uint32_t checkStatus = 0U;
		
		printf("Check BOOT firmware: ");
		if(0U == CalculateAndCheckFirmwareChecksum(BACKUP_BOOT_FIRMWARE_START_ADDRESS, BACKUP_BOOT_FIRMWARE_LENGTH,
			*(uint32_t *)BACKUP_BOOT_FIRMWARE_CHECKSUM_ADDRESS))
		{
			printf("[Success]\r\n");
		}
		else
		{
			checkStatus = 1U;
			printf("[Fail]\r\n");
			
		}
		
		printf("Check APP firmware: ");
		if(0U == CalculateAndCheckFirmwareChecksum(BACKUP_APP_FIRMWARE_START_ADDRESS, BACKUP_APP_FIRMWARE_LENGTH,
			*(uint32_t *)BACKUP_APP_FIRMWARE_CHECKSUM_ADDRESS))
		{
			printf("[Success]\r\n");
		}
		else
		{
			checkStatus = 1U;
			printf("[Fail]\r\n");
		}
		
		if (0u == checkStatus)
		{ /** Check firmware ok */
			uint32_t update_flag;

			update_flag = UPDATE_FLAG_IDLE;
        	//(void)HLI_Fee_Write(EE_ADDRESS_UPDATE_FLAG, 4U, &update_flag);
			
			SyncDFlash();
			//HLI_Fls_A_B_Block_Change();

			pResLen[0U] = 3U;
			pRes[2U] = 0x01U;
			Uds_Response.ResCode = UDS_RES_CODE_PR;
			ret = E_OK;
		}
		else
		{ 
			Uds_Response.ResCode = UDS_RES_CODE_CNC;
			ret = E_OK;
		}

		break;
	}

	case SID_RC_DID_0203:
	{
		if(Dcm_CheckProgrammingPreConditions() == E_OK)
		{
			pResLen[0U] = 3U;
			pRes[2U] = 0x01U;
			Uds_Response.ResCode = UDS_RES_CODE_PR;
			ret = E_OK;
		}
		else
		{
			pResLen[0U] = 3U;
			pRes[2U] = 0x02U;
			Uds_Response.ResCode = UDS_RES_CODE_PR;
			ret = E_OK;
		}

		break;
	}

	default:
	{
		ret = E_OK;
		break;
	}
	}

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_RC_SUBID_STPR_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RC_SUBID_STPR_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint16_t did;
	uint16_t loop;

	did = (uint16_t)pInd[0U] * 0x100U + pInd[1U];
	switch (did)
	{
	case SID_RC_DID_F000:
	{
		ret = E_OK;
		break;
	}

	case SID_RC_DID_FF00:
	{

		ret = E_OK;
		break;
	}

	case SID_RC_DID_F001:
	{
		ret = E_OK;
		break;
	}

	case SID_RC_DID_FF01:
	{
		ret = E_OK;

		break;
	}

	case SID_RC_DID_0203:
	{
		ret = E_OK;
		break;
	}

	default:
	{
		ret = E_OK;
		break;
	}
	}

	return ret;
}

/*************************************************************************/
/*
Function:		void SID_RC_SUBID_STR_Callback
				(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)

Description:

Parameters: 	pInd
				pRes
				pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RC_SUBID_RRR_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;
	uint16_t did;
	uint16_t loop;

	did = (uint16_t)pInd[0U] * 0x100U + pInd[1U];
	switch (did)
	{
	case SID_RC_DID_F000:
	{
		ret = E_OK;
		break;
	}

	case SID_RC_DID_FF00:
	{

		ret = E_OK;
		break;
	}

	case SID_RC_DID_F001:
	{
		ret = E_OK;
		break;
	}

	case SID_RC_DID_FF01:
	{
		ret = E_OK;

		break;
	}

	case SID_RC_DID_0203:
	{
		ret = E_OK;
		break;
	}

	default:
	{
		ret = E_OK;
		break;
	}
	}

	return ret;
}
