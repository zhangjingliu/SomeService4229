#ifndef __SID34_REQUESTDOWNLOADCFG_H_
#define __SID34_REQUESTDOWNLOADCFG_H_


#include "SID34_RequestDownload.h"

/*RAM_FLASH Drv*/
#define MEMM_LB0_START_ADDR 	0x10008000U
#define MEMM_LB0_END_ADDR 		0x10008600U

/**Flash0 boot**/
#define	MEMM_LB1_START_ADDR		0x00000000U
#define	MEMM_LB1_END_ADDR		0x00020000U

/**Flash1 APP**/
#define	MEMM_LB2_START_ADDR		0x00020000U
#define	MEMM_LB2_END_ADDR		0x00100000U


typedef	struct
{
	boolean		b_ReqDownloadFlag;
	uint16_t	PageSize;
}Struct_Uds_SID_RD_Info;


extern Struct_Uds_SID_RD_Info st_Uds_SID_RD_Info;
extern uint32_t u32_ReqDownloadMemAddr;
extern uint32_t u32_ReqDownloadMemSize;

extern boolean SID_RD_Callback(uint8_t *pInd, uint8_t *pRes, uint32_t *pResLen);

#endif 
