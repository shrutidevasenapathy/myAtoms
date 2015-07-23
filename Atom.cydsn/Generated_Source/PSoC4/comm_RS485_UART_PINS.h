/*******************************************************************************
* File Name: comm_RS485_UART_PINS.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_comm_RS485_UART_H)
#define CY_SCB_PINS_comm_RS485_UART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define comm_RS485_UART_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define comm_RS485_UART_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define comm_RS485_UART_REMOVE_MISO_SDA_TX_PIN         (1u)
#define comm_RS485_UART_REMOVE_SCLK_PIN                (1u)
#define comm_RS485_UART_REMOVE_SS0_PIN                 (1u)
#define comm_RS485_UART_REMOVE_SS1_PIN                 (1u)
#define comm_RS485_UART_REMOVE_SS2_PIN                 (1u)
#define comm_RS485_UART_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define comm_RS485_UART_REMOVE_I2C_PINS                (1u)
#define comm_RS485_UART_REMOVE_SPI_MASTER_PINS         (1u)
#define comm_RS485_UART_REMOVE_SPI_SLAVE_PINS          (1u)
#define comm_RS485_UART_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define comm_RS485_UART_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define comm_RS485_UART_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define comm_RS485_UART_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define comm_RS485_UART_REMOVE_UART_TX_PIN             (0u)
#define comm_RS485_UART_REMOVE_UART_RX_TX_PIN          (1u)
#define comm_RS485_UART_REMOVE_UART_RX_PIN             (0u)
#define comm_RS485_UART_REMOVE_UART_RX_WAKE_PIN        (1u)
#define comm_RS485_UART_REMOVE_UART_RTS_PIN            (1u)
#define comm_RS485_UART_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN   (0u == comm_RS485_UART_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define comm_RS485_UART_MOSI_SCL_RX_PIN        (0u == comm_RS485_UART_REMOVE_MOSI_SCL_RX_PIN)
#define comm_RS485_UART_MISO_SDA_TX_PIN        (0u == comm_RS485_UART_REMOVE_MISO_SDA_TX_PIN)
#define comm_RS485_UART_SCLK_PIN               (0u == comm_RS485_UART_REMOVE_SCLK_PIN)
#define comm_RS485_UART_SS0_PIN                (0u == comm_RS485_UART_REMOVE_SS0_PIN)
#define comm_RS485_UART_SS1_PIN                (0u == comm_RS485_UART_REMOVE_SS1_PIN)
#define comm_RS485_UART_SS2_PIN                (0u == comm_RS485_UART_REMOVE_SS2_PIN)
#define comm_RS485_UART_SS3_PIN                (0u == comm_RS485_UART_REMOVE_SS3_PIN)

/* Mode defined pins */
#define comm_RS485_UART_I2C_PINS               (0u == comm_RS485_UART_REMOVE_I2C_PINS)
#define comm_RS485_UART_SPI_MASTER_PINS        (0u == comm_RS485_UART_REMOVE_SPI_MASTER_PINS)
#define comm_RS485_UART_SPI_SLAVE_PINS         (0u == comm_RS485_UART_REMOVE_SPI_SLAVE_PINS)
#define comm_RS485_UART_SPI_MASTER_SS0_PIN     (0u == comm_RS485_UART_REMOVE_SPI_MASTER_SS0_PIN)
#define comm_RS485_UART_SPI_MASTER_SS1_PIN     (0u == comm_RS485_UART_REMOVE_SPI_MASTER_SS1_PIN)
#define comm_RS485_UART_SPI_MASTER_SS2_PIN     (0u == comm_RS485_UART_REMOVE_SPI_MASTER_SS2_PIN)
#define comm_RS485_UART_SPI_MASTER_SS3_PIN     (0u == comm_RS485_UART_REMOVE_SPI_MASTER_SS3_PIN)
#define comm_RS485_UART_UART_TX_PIN            (0u == comm_RS485_UART_REMOVE_UART_TX_PIN)
#define comm_RS485_UART_UART_RX_TX_PIN         (0u == comm_RS485_UART_REMOVE_UART_RX_TX_PIN)
#define comm_RS485_UART_UART_RX_PIN            (0u == comm_RS485_UART_REMOVE_UART_RX_PIN)
#define comm_RS485_UART_UART_RX_WAKE_PIN       (0u == comm_RS485_UART_REMOVE_UART_RX_WAKE_PIN)
#define comm_RS485_UART_UART_RTS_PIN           (0u == comm_RS485_UART_REMOVE_UART_RTS_PIN)
#define comm_RS485_UART_UART_CTS_PIN           (0u == comm_RS485_UART_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if(comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN)
    #include "comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN) */

#if(comm_RS485_UART_MOSI_SCL_RX_PIN)
    #include "comm_RS485_UART_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (comm_RS485_UART_MOSI_SCL_RX_PIN) */

#if(comm_RS485_UART_MISO_SDA_TX_PIN)
    #include "comm_RS485_UART_spi_miso_i2c_sda_uart_tx.h"
#endif /* (comm_RS485_UART_MISO_SDA_TX_PIN_PIN) */

#if(comm_RS485_UART_SCLK_PIN)
    #include "comm_RS485_UART_spi_sclk.h"
#endif /* (comm_RS485_UART_SCLK_PIN) */

#if(comm_RS485_UART_SS0_PIN)
    #include "comm_RS485_UART_spi_ss0.h"
#endif /* (comm_RS485_UART_SS1_PIN) */

#if(comm_RS485_UART_SS1_PIN)
    #include "comm_RS485_UART_spi_ss1.h"
#endif /* (comm_RS485_UART_SS1_PIN) */

#if(comm_RS485_UART_SS2_PIN)
    #include "comm_RS485_UART_spi_ss2.h"
#endif /* (comm_RS485_UART_SS2_PIN) */

#if(comm_RS485_UART_SS3_PIN)
    #include "comm_RS485_UART_spi_ss3.h"
#endif /* (comm_RS485_UART_SS3_PIN) */

#if(comm_RS485_UART_I2C_PINS)
    #include "comm_RS485_UART_scl.h"
    #include "comm_RS485_UART_sda.h"
#endif /* (comm_RS485_UART_I2C_PINS) */

#if(comm_RS485_UART_SPI_MASTER_PINS)
    #include "comm_RS485_UART_sclk_m.h"
    #include "comm_RS485_UART_mosi_m.h"
    #include "comm_RS485_UART_miso_m.h"
#endif /* (comm_RS485_UART_SPI_MASTER_PINS) */

#if(comm_RS485_UART_SPI_SLAVE_PINS)
    #include "comm_RS485_UART_sclk_s.h"
    #include "comm_RS485_UART_mosi_s.h"
    #include "comm_RS485_UART_miso_s.h"
    #include "comm_RS485_UART_ss_s.h"
#endif /* (comm_RS485_UART_SPI_SLAVE_PINS) */

#if(comm_RS485_UART_SPI_MASTER_SS0_PIN)
    #include "comm_RS485_UART_ss0_m.h"
#endif /* (comm_RS485_UART_SPI_MASTER_SS0_PIN) */

#if(comm_RS485_UART_SPI_MASTER_SS1_PIN)
    #include "comm_RS485_UART_ss1_m.h"
#endif /* (comm_RS485_UART_SPI_MASTER_SS1_PIN) */

#if(comm_RS485_UART_SPI_MASTER_SS2_PIN)
    #include "comm_RS485_UART_ss2_m.h"
#endif /* (comm_RS485_UART_SPI_MASTER_SS2_PIN) */

#if(comm_RS485_UART_SPI_MASTER_SS3_PIN)
    #include "comm_RS485_UART_ss3_m.h"
#endif /* (comm_RS485_UART_SPI_MASTER_SS3_PIN) */

#if(comm_RS485_UART_UART_TX_PIN)
    #include "comm_RS485_UART_tx.h"
#endif /* (comm_RS485_UART_UART_TX_PIN) */

#if(comm_RS485_UART_UART_RX_TX_PIN)
    #include "comm_RS485_UART_rx_tx.h"
#endif /* (comm_RS485_UART_UART_RX_TX_PIN) */

#if(comm_RS485_UART_UART_RX_PIN)
    #include "comm_RS485_UART_rx.h"
#endif /* (comm_RS485_UART_UART_RX_PIN) */

#if(comm_RS485_UART_UART_RX_WAKE_PIN)
    #include "comm_RS485_UART_rx_wake.h"
#endif /* (comm_RS485_UART_UART_RX_WAKE_PIN) */

#if(comm_RS485_UART_UART_RTS_PIN)
    #include "comm_RS485_UART_rts.h"
#endif /* (comm_RS485_UART_UART_RTS_PIN) */

#if(comm_RS485_UART_UART_CTS_PIN)
    #include "comm_RS485_UART_cts.h"
#endif /* (comm_RS485_UART_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if(comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN)
    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define comm_RS485_UART_INTCFG_TYPE_MASK                  (0x03u)
    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define comm_RS485_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) comm_RS485_UART_INTCFG_TYPE_MASK << \
                                                                    comm_RS485_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN) */

#if(comm_RS485_UART_MOSI_SCL_RX_PIN)
    #define comm_RS485_UART_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) comm_RS485_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define comm_RS485_UART_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) comm_RS485_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define comm_RS485_UART_MOSI_SCL_RX_HSIOM_MASK     (comm_RS485_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define comm_RS485_UART_MOSI_SCL_RX_HSIOM_POS      (comm_RS485_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_MOSI_SCL_RX_PIN) */

#if(comm_RS485_UART_MISO_SDA_TX_PIN)
    #define comm_RS485_UART_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) comm_RS485_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define comm_RS485_UART_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) comm_RS485_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define comm_RS485_UART_MISO_SDA_TX_HSIOM_MASK     (comm_RS485_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define comm_RS485_UART_MISO_SDA_TX_HSIOM_POS      (comm_RS485_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_MISO_SDA_TX_PIN_PIN) */

#if(comm_RS485_UART_SCLK_PIN)
    #define comm_RS485_UART_SCLK_HSIOM_REG     (*(reg32 *) comm_RS485_UART_spi_sclk__0__HSIOM)
    #define comm_RS485_UART_SCLK_HSIOM_PTR     ( (reg32 *) comm_RS485_UART_spi_sclk__0__HSIOM)
    #define comm_RS485_UART_SCLK_HSIOM_MASK    (comm_RS485_UART_spi_sclk__0__HSIOM_MASK)
    #define comm_RS485_UART_SCLK_HSIOM_POS     (comm_RS485_UART_spi_sclk__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_SCLK_PIN) */

#if(comm_RS485_UART_SS0_PIN)
    #define comm_RS485_UART_SS0_HSIOM_REG      (*(reg32 *) comm_RS485_UART_spi_ss0__0__HSIOM)
    #define comm_RS485_UART_SS0_HSIOM_PTR      ( (reg32 *) comm_RS485_UART_spi_ss0__0__HSIOM)
    #define comm_RS485_UART_SS0_HSIOM_MASK     (comm_RS485_UART_spi_ss0__0__HSIOM_MASK)
    #define comm_RS485_UART_SS0_HSIOM_POS      (comm_RS485_UART_spi_ss0__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_SS1_PIN) */

#if(comm_RS485_UART_SS1_PIN)
    #define comm_RS485_UART_SS1_HSIOM_REG      (*(reg32 *) comm_RS485_UART_spi_ss1__0__HSIOM)
    #define comm_RS485_UART_SS1_HSIOM_PTR      ( (reg32 *) comm_RS485_UART_spi_ss1__0__HSIOM)
    #define comm_RS485_UART_SS1_HSIOM_MASK     (comm_RS485_UART_spi_ss1__0__HSIOM_MASK)
    #define comm_RS485_UART_SS1_HSIOM_POS      (comm_RS485_UART_spi_ss1__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_SS1_PIN) */

#if(comm_RS485_UART_SS2_PIN)
    #define comm_RS485_UART_SS2_HSIOM_REG     (*(reg32 *) comm_RS485_UART_spi_ss2__0__HSIOM)
    #define comm_RS485_UART_SS2_HSIOM_PTR     ( (reg32 *) comm_RS485_UART_spi_ss2__0__HSIOM)
    #define comm_RS485_UART_SS2_HSIOM_MASK    (comm_RS485_UART_spi_ss2__0__HSIOM_MASK)
    #define comm_RS485_UART_SS2_HSIOM_POS     (comm_RS485_UART_spi_ss2__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_SS2_PIN) */

#if(comm_RS485_UART_SS3_PIN)
    #define comm_RS485_UART_SS3_HSIOM_REG     (*(reg32 *) comm_RS485_UART_spi_ss3__0__HSIOM)
    #define comm_RS485_UART_SS3_HSIOM_PTR     ( (reg32 *) comm_RS485_UART_spi_ss3__0__HSIOM)
    #define comm_RS485_UART_SS3_HSIOM_MASK    (comm_RS485_UART_spi_ss3__0__HSIOM_MASK)
    #define comm_RS485_UART_SS3_HSIOM_POS     (comm_RS485_UART_spi_ss3__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_SS3_PIN) */

#if(comm_RS485_UART_I2C_PINS)
    #define comm_RS485_UART_SCL_HSIOM_REG     (*(reg32 *) comm_RS485_UART_scl__0__HSIOM)
    #define comm_RS485_UART_SCL_HSIOM_PTR     ( (reg32 *) comm_RS485_UART_scl__0__HSIOM)
    #define comm_RS485_UART_SCL_HSIOM_MASK    (comm_RS485_UART_scl__0__HSIOM_MASK)
    #define comm_RS485_UART_SCL_HSIOM_POS     (comm_RS485_UART_scl__0__HSIOM_SHIFT)

    #define comm_RS485_UART_SDA_HSIOM_REG     (*(reg32 *) comm_RS485_UART_sda__0__HSIOM)
    #define comm_RS485_UART_SDA_HSIOM_PTR     ( (reg32 *) comm_RS485_UART_sda__0__HSIOM)
    #define comm_RS485_UART_SDA_HSIOM_MASK    (comm_RS485_UART_sda__0__HSIOM_MASK)
    #define comm_RS485_UART_SDA_HSIOM_POS     (comm_RS485_UART_sda__0__HSIOM_SHIFT)
#endif /* (comm_RS485_UART_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define comm_RS485_UART_HSIOM_DEF_SEL      (0x00u)
#define comm_RS485_UART_HSIOM_GPIO_SEL     (0x00u)
#define comm_RS485_UART_HSIOM_UART_SEL     (0x09u)
#define comm_RS485_UART_HSIOM_I2C_SEL      (0x0Eu)
#define comm_RS485_UART_HSIOM_SPI_SEL      (0x0Fu)

#define comm_RS485_UART_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define comm_RS485_UART_MISO_SDA_TX_PIN_INDEX      (1u)
#define comm_RS485_UART_SCLK_PIN_INDEX             (2u)
#define comm_RS485_UART_SS0_PIN_INDEX              (3u)
#define comm_RS485_UART_SS1_PIN_INDEX              (4u)
#define comm_RS485_UART_SS2_PIN_INDEX              (5u)
#define comm_RS485_UART_SS3_PIN_INDEX              (6u)

#define comm_RS485_UART_MOSI_SCL_RX_PIN_MASK      ((uint32) 0x01u << comm_RS485_UART_MOSI_SCL_RX_PIN_INDEX)
#define comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN_MASK ((uint32) 0x01u << comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN_INDEX)
#define comm_RS485_UART_MISO_SDA_TX_PIN_MASK      ((uint32) 0x01u << comm_RS485_UART_MISO_SDA_TX_PIN_INDEX)
#define comm_RS485_UART_SCLK_PIN_MASK             ((uint32) 0x01u << comm_RS485_UART_SCLK_PIN_INDEX)
#define comm_RS485_UART_SS0_PIN_MASK              ((uint32) 0x01u << comm_RS485_UART_SS0_PIN_INDEX)
#define comm_RS485_UART_SS1_PIN_MASK              ((uint32) 0x01u << comm_RS485_UART_SS1_PIN_INDEX)
#define comm_RS485_UART_SS2_PIN_MASK              ((uint32) 0x01u << comm_RS485_UART_SS2_PIN_INDEX)
#define comm_RS485_UART_SS3_PIN_MASK              ((uint32) 0x01u << comm_RS485_UART_SS3_PIN_INDEX)

#define comm_RS485_UART_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define comm_RS485_UART_PIN_DM_ALG_HIZ  (0u)
#define comm_RS485_UART_PIN_DM_DIG_HIZ  (1u)
#define comm_RS485_UART_PIN_DM_OD_LO    (4u)
#define comm_RS485_UART_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Set bits-mask in register */
#define comm_RS485_UART_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define comm_RS485_UART_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define comm_RS485_UART_SET_HSIOM_SEL(reg, mask, pos, sel) comm_RS485_UART_SET_REGISTER_BITS(reg, mask, pos, sel)
#define comm_RS485_UART_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        comm_RS485_UART_SET_REGISTER_BITS(reg, mask, pos, intType)
#define comm_RS485_UART_SET_INP_DIS(reg, mask, val) comm_RS485_UART_SET_REGISTER_BIT(reg, mask, val)

/* comm_RS485_UART_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  comm_RS485_UART_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if(comm_RS485_UART_I2C_PINS)
    #define comm_RS485_UART_SET_I2C_SCL_DR(val) comm_RS485_UART_scl_Write(val)

    #define comm_RS485_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                          comm_RS485_UART_SET_HSIOM_SEL(comm_RS485_UART_SCL_HSIOM_REG,  \
                                                         comm_RS485_UART_SCL_HSIOM_MASK, \
                                                         comm_RS485_UART_SCL_HSIOM_POS,  \
                                                         (sel))
    #define comm_RS485_UART_WAIT_SCL_SET_HIGH  (0u == comm_RS485_UART_scl_Read())

/* Unconfigured SCB: scl signal */
#elif(comm_RS485_UART_MOSI_SCL_RX_WAKE_PIN)
    #define comm_RS485_UART_SET_I2C_SCL_DR(val) \
                            comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define comm_RS485_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                    comm_RS485_UART_SET_HSIOM_SEL(comm_RS485_UART_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   comm_RS485_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   comm_RS485_UART_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

    #define comm_RS485_UART_WAIT_SCL_SET_HIGH  (0u == comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_wake_Read())

#elif(comm_RS485_UART_MOSI_SCL_RX_PIN)
    #define comm_RS485_UART_SET_I2C_SCL_DR(val) \
                            comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define comm_RS485_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                            comm_RS485_UART_SET_HSIOM_SEL(comm_RS485_UART_MOSI_SCL_RX_HSIOM_REG,  \
                                                           comm_RS485_UART_MOSI_SCL_RX_HSIOM_MASK, \
                                                           comm_RS485_UART_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))

    #define comm_RS485_UART_WAIT_SCL_SET_HIGH  (0u == comm_RS485_UART_spi_mosi_i2c_scl_uart_rx_Read())

#else
    #define comm_RS485_UART_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define comm_RS485_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define comm_RS485_UART_WAIT_SCL_SET_HIGH  (0u)
#endif /* (comm_RS485_UART_MOSI_SCL_RX_PIN) */

/* SCB I2C: sda signal */
#if(comm_RS485_UART_I2C_PINS)
    #define comm_RS485_UART_WAIT_SDA_SET_HIGH  (0u == comm_RS485_UART_sda_Read())

/* Unconfigured SCB: sda signal */
#elif(comm_RS485_UART_MISO_SDA_TX_PIN)
    #define comm_RS485_UART_WAIT_SDA_SET_HIGH  (0u == comm_RS485_UART_spi_miso_i2c_sda_uart_tx_Read())

#else
    #define comm_RS485_UART_WAIT_SDA_SET_HIGH  (0u)
#endif /* (comm_RS485_UART_MOSI_SCL_RX_PIN) */

#endif /* (CY_SCB_PINS_comm_RS485_UART_H) */


/* [] END OF FILE */
