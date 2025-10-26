#include "Dcm_DrvCfg.h"
#include "SID36_TransferDataCfg.h"
#include "SID34_RequestDownloadCfg.h"
#include "bsp_debug_uart.h"
#include "bsp_canfd1.h"


Struct_Uds_SID_TD_Info	st_Uds_SID_TD_Info;



uint8_t ui8_NewBlockSequenceCounter;
uint8_t ui8_LastBlockSequenceCounter;

uint32_t CheckMemoryCRC32(const uint8_t* pData, uint32_t nLength, uint32_t lastCRCvalue)
{
	uint8_t i; uint32_t crc = lastCRCvalue;
	while(nLength != 0)
	{
		crc ^= *pData;
		for(i=0; i< 8; i++)
		{
			if(crc& 1)
			{
				crc>>= 1;
				crc ^= 0xEDB88320u;
			}
			else
			{
				crc>>= 1;
			}
		}
		pData = &pData[1];
		nLength--;
	}
	return(crc);
}

/*----------------------------------------------------------------------------------------------------*/
/*
Function:		boolean UdsDownloadFlsDrv(uint32_t TargetAddress, uint8_t *SourceAddressPtr, uint32_t Length)
Description:
Input:
Output:  		void
Return:			boolean

*/
boolean UdsDownloadFlsDrv(uint32_t TargetAddress, uint8_t *SourceAddressPtr, uint32_t Length)
{
	boolean b_Return;
	uint16_t	ui16_Loop_1;

	uint8_t* ui8_Memory_Point = (uint8_t*)(TargetAddress);
	for(ui16_Loop_1 = 0U; ui16_Loop_1 < Length; ui16_Loop_1++)
	{
		*ui8_Memory_Point = *SourceAddressPtr;
		ui8_Memory_Point++;
		SourceAddressPtr++;
	}

	b_Return = E_OK;

	return b_Return;
}

/*************************************************************************/
/*
Function:		void UdsFunc_SID_TD_Callback
				(uint8 *ui8_pInd, uint16 ui16_IndLen, uint8 *ui8_pRes, uint16 *ui16_pResLen)

Description:

Parameters: 	ui8_pInd
				ui16_IndLen
				ui8_pRes
				ui16_pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
uint16_t ui16_BlockLength = 0;
boolean SID_TD_Callback
	(uint8_t *pInd, uint16_t indLen, uint8_t *pRes, uint32_t *pResLen)
{
	boolean	b_Return;
#if 0
	HLI_Fls_StatusType b_Download_Return;
	uint16_t	ui16_Loop_1;
	ui16_BlockLength = indLen -1U;

	if( (st_Uds_SID_RD_Info.PageSize >= ui16_BlockLength)
				&& (ui16_BlockLength <= u32_ReqDownloadMemSize ))
	{
		if(st_Uds_SID_RD_Info.b_ReqDownloadFlag == true)
		{
			if((pInd[0U] == ui8_NewBlockSequenceCounter)
					|| (pInd[0U] == ui8_LastBlockSequenceCounter))
			{
				b_Download_Return = HLI_FLS_STATUS_OK;
				if(pInd[0U] == ui8_NewBlockSequenceCounter)
				{
					if(u32_ReqDownloadMemSize > 0)
					{
						if((u32_ReqDownloadMemAddr >= MEMM_LB0_START_ADDR) && (u32_ReqDownloadMemAddr <= MEMM_LB0_END_ADDR))
						{
							b_DownLoad_FlashDrv_Flag = true;
						}
						else
						{
							printf("[%02d],Addr[%08x], Size[%0x]\r\n", ui8_NewBlockSequenceCounter, (BACKUP_AREA_ADDR + u32_ReqDownloadMemAddr), ui16_BlockLength);
							//b_Download_Return = HLI_Fls_WriteMinimumWriteableBytes((BACKUP_AREA_ADDR + u32_ReqDownloadMemAddr),ui16_BlockLength,&pInd[1U]);
							b_Download_Return = HLI_FLS_STATUS_OK;//我加的 为了方便移植到其它MCU上
						}

						if(b_Download_Return == HLI_FLS_STATUS_OK)
						{
							ui8_LastBlockSequenceCounter = ui8_NewBlockSequenceCounter;
							ui8_NewBlockSequenceCounter += 1U;

							u32_ReqDownloadMemAddr += ui16_BlockLength;
							u32_ReqDownloadMemSize -= ui16_BlockLength;

							st_Uds_SID_TD_Info.ui32_LastCrcValue = CheckMemoryCRC32(&pInd[1U], ui16_BlockLength
																		, st_Uds_SID_TD_Info.ui32_LastCrcValue);
							st_Uds_SID_TD_Info.b_TransferDataFlag = true;
						}
					}
					else
					{
						Uds_Response.ResCode = UDS_RES_CODE_TDS;
					}
				}

				if(b_Download_Return == HLI_FLS_STATUS_OK)
				{
					pResLen[0U] = 1U;
					pRes[0U] = ui8_LastBlockSequenceCounter;
					Uds_Response.ResCode = UDS_RES_CODE_PR;
				}
				else
				{
					Uds_Response.ResCode = UDS_RES_CODE_GPF;
				}
			}
			else
			{
				Uds_Response.ResCode = UDS_RES_CODE_WBSC;
			}
		}
		else
		{
			Uds_Response.ResCode = UDS_RES_CODE_RSE;
		}
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_IMLOIF;
	}
#endif
	b_Return = E_OK;

	return	b_Return;
}
