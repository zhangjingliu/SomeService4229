#include "Dcm_Drv.h"
#include "SID14_ClearDiagnosticInformationCfg.h"

/******************************************************************************
 *                      Constants                                      *
 ******************************************************************************/
boolean SID_CDTCI_GODTC_AG_Callback(uint8_t *pRes, uint32_t *pResLen);
/******************************************************************************
 *                      Type definitions                                       *
 ******************************************************************************/

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
const Struct_Uds_SID_CDTCI Uds_SID_CDTCI[UDS_SID_CDTCI_GODTC_NUMBER] =
	{
		{UDS_GODTC_AG,
		 SID_CDTCI_GODTC_AG_Callback},

};
/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
boolean SID_CDTCI_GODTC_AG_Callback(uint8_t *pRes, uint32_t *pResLen)
{
	boolean ret;

	ret = E_OK;

	return ret;
}
