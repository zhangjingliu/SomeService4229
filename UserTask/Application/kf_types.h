#ifndef KFTYPES_H_
#define KFTYPES_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum
{
    /* Generic error codes */
    /** @brief Generic operation success status */
    STATUS_OK = 0x000U,
    /** @brief Generic operation failure status */
    STATUS_ERROR = 0x001U,
    /** @brief Generic operation busy status */
    STATUS_BUSY = 0x002U,
    /** @brief Generic operation timeout status */
    STATUS_TIMEOUT = 0x003U,
    /** @brief Generic operation unsupported status */
    STATUS_UNSUPPORTED = 0x004U,

    /* MCU specific error codes */
    /** @brief Module is gated off */
    STATUS_MCU_GATED_OFF = 0x100U,
    /** @brief Error occurs during transition. */
    STATUS_MCU_TRANSITION_FAILED = 0x101U,
    /** @brief Unsupported in current state. */
    STATUS_MCU_INVALID_STATE = 0x102U,
    /** @brief Error occurs during send "BEFORE" notification. */
    STATUS_MCU_NOTIFY_BEFORE_ERROR = 0x103U,
    /** @brief Error occurs during send "AFTER" notification. */
    STATUS_MCU_NOTIFY_AFTER_ERROR = 0x104U,

    /* I2C specific error codes */
    /** @brief NACK signal received  */
    STATUS_I2C_RECEIVED_NACK = 0x200U,
    /** @brief TX underrun error */
    STATUS_I2C_TX_UNDERRUN = 0x201U,
    /** @brief RX overrun error */
    STATUS_I2C_RX_OVERRUN = 0x202U,
    /** @brief Arbitration lost */
    STATUS_I2C_ARBITRATION_LOST = 0x203U,
    /** @brief A transfer was aborted */
    STATUS_I2C_ABORTED = 0x204U,
    /** @brief I2C bus is busy, cannot start transfer */
    STATUS_I2C_BUS_BUSY = 0x205U,

    /* CAN specific error codes */
    /** @brief The specified MB index is out of the configurable range */
    STATUS_CAN_BUFF_OUT_OF_RANGE = 0x300U,
    /** @brief There is no transmission or reception in progress */
    STATUS_CAN_NO_TRANSFER_IN_PROGRESS = 0x301U,
    /** @brief There is no buffer for mailbox */
    STATUS_CAN_BUFF_FULL = 0x302U,
    /** @brief There is error occured */
    STATUS_CAN_ERROR = 0x303U,
    /** @brief CAN is not synchronized to bus */
    STATUS_CAN_OFFLINE = 0x304U,

    /* CANFD specific error codes */
    /** @brief The specified MB index is out of the configurable range */
    STATUS_CANFD_BUFF_OUT_OF_RANGE = 0x380U,
    /** @brief There is no transmission or reception in progress */
    STATUS_CANFD_NO_TRANSFER_IN_PROGRESS = 0x381U,

    /* SPI specific error codes */
    /** @brief TX underrun error */
    STATUS_SPI_TX_UNDERRUN = 0x500U,
    /** @brief RX overrun error */
    STATUS_SPI_RX_OVERRUN = 0x501U,
    /** @brief A transfer was aborted */
    STATUS_SPI_ABORTED = 0x502U,

    /* UART specific error codes */
    /** @brief TX underrun error */
    STATUS_UART_TX_UNDERRUN = 0x600U,
    /** @brief RX overrun error */
    STATUS_UART_RX_OVERRUN = 0x601U,
    /** @brief A transfer was aborted */
    STATUS_UART_ABORTED = 0x602U,
    /** @brief Framing error */
    STATUS_UART_FRAMING_ERROR = 0x603U,
    /** @brief Parity error */
    STATUS_UART_PARITY_ERROR = 0x604U,
    /** @brief Noise error */
    STATUS_UART_NOISE_ERROR = 0x605U,

    /* I2S specific error codes */
    /** @brief TX underrun error */
    STATUS_I2S_TX_UNDERRUN = 0x700U,
    /** @brief RX overrun error */
    STATUS_I2S_RX_OVERRUN = 0x701U,
    /** @brief A transfer was aborted */
    STATUS_I2S_ABORTED = 0x702U,

    /* FLASH specific error codes */
    /** @brief It's impossible to enable an operation */
    STATUS_FLASH_ERROR_ENABLE = 0x901U,
    /** @brief No blocks have been enabled for Array Integrity check */
    STATUS_FLASH_ERROR_NO_BLOCK = 0x902U,
    /** @brief InProgress status */
    STATUS_FLASH_INPROGRESS = 0x903U,

    /* CCP specific error codes */
    /** @brief CCP triggers TimeOut when try to enter in Config State */
    STATUS_CCP_ERROR_CONFIG_TIMEOUT = 0xB01U,
    /** @brief CCP Initializing CCP Module */
    STATUS_CCP_ERROR_INIT_CCP = 0xB02U,
    /** @brief CCP Fail to Enter in Config Mode  */
    STATUS_CCP_ERROR_SET_CONFIG = 0xB03U,
    /** @brief CCP Fail to Enter in Normal Mode  */
    STATUS_CCP_ERROR_SET_NORMAL = 0xB04U,
    /** @brief CCP Fail to set NoCritical Faults  */
    STATUS_CCP_ERROR_APPLY_NCF_CONFIG = 0xB05U,
    /** @brief CCP Fail to update Freez Status registers */
    STATUS_CCP_ERROR_UPDATE_FREEZE = 0xB06U,
    /** @brief CCP Fail to Clear Freez Status registers */
    STATUS_CCP_ERROR_CLEAR_FREEZE = 0xB07U,
    /** @brief CCP Fail to Set Eout Configuration */
    STATUS_CCP_ERROR_SET_EOUT = 0xB08U,
    /** @brief CCP Faults Detected */
    STATUS_CCP_ERROR_FAULT_DETECTED = 0xB09U,
    /** @brief CCP other Error */
    STATUS_CCP_ERROR_OTHER = 0xB0AU,

    /* EEE specific error codes */
    /** @brief The data is too big to fit in any of the block */
    STATUS_EEE_ERROR_NO_ENOUGH_SPACE = 0xD00U,
    /** @brief The block numbers is not enough for round robin */
    STATUS_EEE_ERROR_NO_ENOUGH_BLOCK = 0xD01U,
    /** @brief The required data is not found in the EEPROM emulation */
    STATUS_EEE_ERROR_DATA_NOT_FOUND = 0xD02U,
    /** @brief The required data is not in the cache table */
    STATUS_EEE_ERROR_NOT_IN_CACHE = 0xD03U,
    /** @brief Failed to make block indicator to non-blank for several times */
    STATUS_EEE_ERROR_PROGRAM_INDICATOR = 0xD04U,
    /** @brief The high voltage operation is in progress */
    STATUS_EEE_HVOP_INPROGRESS = 0xD05U,

} kf_status_t;

#define REG_BIT_SET(reg, mask)           ((reg) |= (mask))
#define REG_BIT_CLR(reg, mask)           ((reg) &= ~(mask))
#define REG_BITS_WRITE(reg, mask, value) ((reg) = ((reg) & ~(mask)) | (value))
#define REG_BITS_READ(reg, mask, pos)    (((reg) & (mask)) >> (pos))
#define REG_BIT_BOOLED(reg, mask)        (((reg) & (mask)) > 0U)
#define REG_WRITE(reg, value)            ((reg) = (value))
#define REG_READ(reg)                    (reg)

//#define KF_CLR_BIT(reg, offset) __asm volatile("CLR [%0], #%1" ::"r"(&(reg)), "i"(offset) : "memory")
//#define KF_SET_BIT(reg, offset) __asm volatile("SET [%0], #%1" ::"r"(&(reg)), "i"(offset) : "memory")

#ifndef STD_ON
#define STD_ON 1U
#endif
#ifndef STD_OFF
#define STD_OFF 0U
#endif

#ifndef BIT_SET
#define BIT_SET 0x1U
#endif
#ifndef BIT_CLR
#define BIT_CLR 0x0U
#endif

#ifndef NULL
#define NULL 0U
#endif
#ifndef NULL_PTR
#define NULL_PTR ((void *)0U)
#endif

/**
 * @brief Enum for Bit Level status
 *
 */
typedef enum
{
    /** @brief IO Bit Logic Low  */
    BIT_LEVEL_LOW,
    /** @brief IO Bit Logic High  */
    BIT_LEVEL_HIGH
} kfBitLevel_t;

/**
 * @brief Enum for Ability
 *
 */
typedef enum
{
    /** @brief Functionality Disable State  */
    KF_DISABLE,
    /** @brief Functionality Enable State  */
    KF_ENABLE
} kfOption_t;

#ifndef __I
/** @brief Defines 'read only' permissions */
#define __I volatile const
#endif
#ifndef __O
/** @brief Defines 'write only' permissions */
#define __O volatile
#endif
#ifndef __IO
/** @brief Defines 'read / write' permissions */
#define __IO volatile
#endif

#ifndef KF_INLINE
#define KF_INLINE static inline
#endif


#define NOP()   __asm volatile("NOP")
#define RESET() __asm volatile("RESET")

#if 0
/* It should be noted that macro parameters that contain '#' or '##' in macro definitions will not be expanded. so we
 * need additional intermediate  macro */

#define KF_STATIC_ASSERT(x, msg)    typedef char KF_STATIC_COMBO(msg, __LINE__)[(x) ? 1 : -1]
#define KF_STATIC_COMBO(msg, line)  KF_STATIC_COMBO_(msg, line)
#define KF_STATIC_COMBO_(msg, line) ASSERT_##msg##_##line##_Failed
#define KF_STATIC_ASSERT(x, msg)    typedef char ASSERT_##msg##_Failed[(x) ? 1 : -1]
#else
/* static assert is build-in kf32-gcc */
#define KF_STATIC_ASSERT(cond, msg) _Static_assert((cond), msg)
#endif

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
