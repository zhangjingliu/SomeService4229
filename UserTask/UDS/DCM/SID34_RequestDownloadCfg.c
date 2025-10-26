#include "Dcm_DrvCfg.h"
#include "SID34_RequestDownloadCfg.h"
#include "SID36_TransferDataCfg.h"

Struct_Uds_SID_RD_Info st_Uds_SID_RD_Info;

uint32_t u32_ReqDownloadMemAddr;
uint32_t u32_ReqDownloadMemSize;

/*************************************************************************/
/*
Function:		void UdsFunc_SID_RD_Callback
				(uint8 *ui8_pInd, uint8 *ui8_pRes, uint16 *ui16_pResLen)

Description:

Parameters: 	ui8_pInd
				ui8_pRes
				ui16_pResLen

Return:       	boolean

Return Values:  E_OK
				E_NOT_OK
*/
boolean SID_RD_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	if (st_Uds_SID_RD_Info.b_ReqDownloadFlag == false)
	{
		u32_ReqDownloadMemAddr = pInd[2U] * 0x100U * 0x100U * 0x100U;
		u32_ReqDownloadMemAddr += pInd[3U] * 0x100U * 0x100U;
		u32_ReqDownloadMemAddr += pInd[4U] * 0x100U;
		u32_ReqDownloadMemAddr += pInd[5U];

		u32_ReqDownloadMemSize = pInd[6U] * 0x100U * 0x100U * 0x100U;
		u32_ReqDownloadMemSize += pInd[7U] * 0x100U * 0x100U;
		u32_ReqDownloadMemSize += pInd[8U] * 0x100U;
		u32_ReqDownloadMemSize += pInd[9U];

		if ((u32_ReqDownloadMemAddr >= MEMM_LB0_START_ADDR) && (u32_ReqDownloadMemAddr <= MEMM_LB0_END_ADDR))
		{
			if ((u32_ReqDownloadMemSize >= PAGE_SIZE) && (u32_ReqDownloadMemSize <= (MEMM_LB0_END_ADDR - MEMM_LB0_START_ADDR + 1U)))
			{
				printf("Request download FLS Driver: Addr[%08x], Size[%08x], ", u32_ReqDownloadMemAddr, u32_ReqDownloadMemSize);
				st_Uds_SID_RD_Info.PageSize = MAX_BLOCK_SIZE;
			}
		}
		else if ((u32_ReqDownloadMemAddr >= MEMM_LB1_START_ADDR) && (u32_ReqDownloadMemAddr < MEMM_LB1_END_ADDR))
		{
			if ((u32_ReqDownloadMemSize >= PAGE_SIZE) && (u32_ReqDownloadMemSize <= (MEMM_LB1_END_ADDR - MEMM_LB1_START_ADDR + 1U)))
			{
				printf("Request download Boot: Addr[%08x], Size[%08x], ", u32_ReqDownloadMemAddr, u32_ReqDownloadMemSize);
				st_Uds_SID_RD_Info.PageSize = MAX_BLOCK_SIZE;
			}
		}
		else if ((u32_ReqDownloadMemAddr >= MEMM_LB2_START_ADDR) && (u32_ReqDownloadMemAddr < MEMM_LB2_END_ADDR))
		{
			if ((u32_ReqDownloadMemSize >= PAGE_SIZE) && (u32_ReqDownloadMemSize <= (MEMM_LB2_END_ADDR - MEMM_LB2_START_ADDR + 1U)))
			{
				printf("Request download APP: Addr[%08x], Size[%08x], ", u32_ReqDownloadMemAddr, u32_ReqDownloadMemSize);
				st_Uds_SID_RD_Info.PageSize = MAX_BLOCK_SIZE;
			}
		}
		else
		{
			st_Uds_SID_RD_Info.PageSize = INVALID_PAGE_SIZE;
		}

		if ((pInd[0U] == 0x00U) && (pInd[1U] == 0x44U) && (st_Uds_SID_RD_Info.PageSize != INVALID_PAGE_SIZE))
		{
			printf("[Success]\r\n");
			st_Uds_SID_RD_Info.b_ReqDownloadFlag = true;
			st_Uds_SID_TD_Info.b_TransferDataFlag = false;
			ui8_NewBlockSequenceCounter = 0x01U;
			ui8_LastBlockSequenceCounter = 0x01U;

			pResLen[0U] = 3U;
			pRes[0U] = 0x20U;
			pRes[1U] = 0x0FU;
			pRes[2U] = 0x02U;
			Uds_Response.ResCode = UDS_RES_CODE_PR;
		}
		else
		{
			printf("[Fail]\r\n");
			Uds_Response.ResCode = UDS_RES_CODE_ROOR;
		}
	}
	else
	{
		Uds_Response.ResCode = UDS_RES_CODE_UDNA;
	}

	ret = E_OK;

	return ret;
}
