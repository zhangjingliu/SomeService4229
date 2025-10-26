#include "AB_Swap.h"
#include "hal_data.h"
#include "bsp_debug_uart.h"
#include "bsp_canfd1.h"


/******************************************************************************
 *                      Constants
 ******************************************************************************/
__attribute__((section(".bootChecksum"))) const uint32_t BootChecksum;
 
/******************************************************************************
 *                      Type definitions
 ******************************************************************************/
typedef void (*pFunction)(void);

/******************************************************************************
 *                      Variables
 ******************************************************************************/
static pFunction Jump_To_Application;
static uint32_t  JumpAddress;

/******************************************************************************
 *                      Function definitions
 ******************************************************************************/

/**
 * @brief Calculate and check checksum of firmware
 *
 * @param StartAddr Start address of firmware
 * @param FirmwareLength Length of firmware
 * @param Checksum Except checksum
 * @return uint32_t  0: success; other: fail
 */
uint32_t CalculateAndCheckFirmwareChecksum(uint32_t StartAddr, uint32_t FirmwareLength, uint32_t Checksum)
{
    uint32_t  ret         = 0U;
    uint32_t *ptr         = (uint32_t *)StartAddr;
    uint32_t  len         = FirmwareLength >> 2U;
    uint32_t  calChecksum = 0U;

    for (uint32_t i = 0u; i < len; i++)
    {
        calChecksum = calChecksum + ptr[i];
    }

    if (Checksum != calChecksum)
    {
        ret = 1U;
    }
    else
    { /** Empty */
    }

    return ret;
}

/**
 * @brief Sync DFlash
 *
 * @return uint32_t 0: success; other: fail
 */
uint32_t SyncDFlash(void)
{
    uint32_t  ret = 0U;
    uint32_t *ptr = (uint32_t *)DFLASH_START_ADDR;
    uint32_t  len = DFLASH_LENGTH >> 11U;

    static uint32_t buffer[512] = {0U};

    for (uint32_t i = 0U; i < len; i++)
    {
        ptr = (uint32_t *)(DFLASH_START_ADDR + (i << 11U));

        /** Copy 2KB DFlash Data */
        for (uint32_t j = 0U; j < 512U; j++)
        {
            buffer[j] = ptr[j];
        }
#if 0
        /** Write data to Bank space */
        if (HLI_FLS_STATUS_OK !=
            HLI_PFlash_EraseAndWriteSector(FLS_KEY, (DFLASH_ALTER_START_ADDR + (i << 11U)), 2048U, (uint8_t *)buffer))
        {
            ret = 1U;
            break;
        }
        else
        { /** Empty */
        }
#endif		
    }

    return ret;
}

#if 0
/**
 * @brief Set MSP
 *
 * @param value
 */
static __inline void __set_MSP(uint32_t value)
{
    asm volatile(" MOV SP,%0 \n" : : "r"(value) : "sp");
}
/**
 * @brief Select SP
 *
 * @param Control
 * @return void
 */
static __inline void __set_CONTROL(uint32_t Control)
{
   // SYSTEM_MCTL.bits.SPSEL = Control;
}
#endif
/**
 * @brief Jump to application
 *
 * @param ApplicationAddress APP address
 */
void JumpToApp(uint32_t ApplicationAddress)
{
//    asm volatile("DSI");
//    asm volatile("NOP");
//    SYSTEM_PTR->VECTOFF.reg = ApplicationAddress;
    /** Set JumpAddress */
    JumpAddress         = *(volatile uint32_t *)(ApplicationAddress + 4U);
    Jump_To_Application = (pFunction)JumpAddress;
    /** Select SP to MSP */
    //__set_CONTROL(0);
    /** Set MSP to APP's initial stack address */
    //__set_MSP(*(uint32_t *)ApplicationAddress);
    Jump_To_Application();
}
