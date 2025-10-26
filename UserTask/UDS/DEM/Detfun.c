#include  "Detdtc.h"
#include  "Detfun.h"

/******************************************************************************
 *                      Variables                                          *
 ******************************************************************************/
OBD_DTC_FLAG DETFUN_BattVolHi_d;

/******************************************************************************
 *                      Function definitions                                   *
 ******************************************************************************/
/**********************************************************************************************/
/* function name: u8g_DETFUN_BattVolHi                                                             */
/* parameter    : NULL                                                                        */
/* return       : NULL                                                                        */
/* description  : 10ms                                                                        */
/**********************************************************************************************/
uint8_t DETFUN_BattVolHi(void)
{
	uint8_t ret_val = OBD_PRECON_OK;

    /* Monitor Enable Conditions  */
//    if ( big_DTC_NotInCrankEngStar == ON )
//    {
//        if ( u16g_ADC_KL30U > u16s_DETFUN_BattVolH_D )
//        {
//            u8g_DETFUN_BattVolHi_d = Faulted;
//        }
//        else  if ( u16g_ADC_KL30U < u16s_DETFUN_BattVolH_P )
//        {
//            u8g_DETFUN_BattVolHi_d = Passed;
//        }
//        else
//        {
//            u8g_DETFUN_BattVolHi_d = Pending;
//        }
//    }
//    else
//    {
//        ret_val = OBD_PRECON_NG;
//    }

    return ret_val;
}
