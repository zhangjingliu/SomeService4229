#ifndef __AB_SWAP_H_
#define __AB_SWAP_H_

#include <stdint.h>
#include <stdbool.h>
#include "AB_Swap_Config.h"
#include "bsp_debug_uart.h"

/**
 * @brief Calculate and check checksum of firmware
 *
 * @param StartAddr Start address of firmware
 * @param FirmwareLength Length of firmware
 * @param Checksum Except checksum
 * @return uint32_t  0: success; other: fail
 */
uint32_t CalculateAndCheckFirmwareChecksum(uint32_t StartAddr, uint32_t FirmwareLength, uint32_t Checksum);

/**
 * @brief Sync DFlash
 *
 * @return uint32_t 0: success; other: fail
 */
uint32_t SyncDFlash(void);

/**
 * @brief Jump to application
 *
 * @param ApplicationAddress APP address
 */
void JumpToApp(uint32_t ApplicationAddress);


#endif
