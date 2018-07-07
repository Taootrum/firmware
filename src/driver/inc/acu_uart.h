/*******************************************************************************
  * @file    acu_uart.h
  * @author  DengLin SOC Team
  * @version V0.0.1
  * @date    2-june-2018
  * @brief   This file contains all the functions prototypes for the UART 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_UART_H
#define __ACU_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"

/** @brief  UART Init Structure definition */ 
typedef struct
{
    uint32_t UART_BaudRate;             /*!< - IntegerDivider = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))
                                             - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 64) + 0.5 */
    uint16_t UART_WordLength;           /*!< Specifies the number of data bits transmitted or received in a frame*/
    uint16_t UART_StopBits;             /*!< Specifies the number of stop bits transmitted */
    uint16_t UART_FIFOControl;          /*!< Specifies the FIFO enabled or disabled */
    uint16_t UART_ParityMode;           /*!< None/odd/even */
    uint16_t UART_TransmitMode;         /*!< Specifies wether the Receive or Transmit mode is enabled or disabled*/
    uint16_t UART_IrDAMode;         /*!< Specifies wether the IRDA is normal or lowpower */
    uint16_t UART_HardwareFlowControl;  /*!< Specifies wether the hardware flow control mode is enabled or disabled */
    uint16_t UART_LoopBackControl;      /*!< Specifies wether the hardware flow control mode is enabled or disabled */
    uint16_t UART_FIFOTx;
    uint16_t UART_FIFORx;
} UART_InitTypeDef;

/** @brief  UART Clock Init Structure definition */ 
typedef struct
{
    uint16_t UART_Clock;   /*!< Specifies whether the UART clock is enabled or disabled.
                               This parameter can be a value of @ref UART_Clock */

    uint16_t UART_CPOL;    /*!< Specifies the steady state value of the serial clock.
                               This parameter can be a value of @ref UART_Clock_Polarity */

    uint16_t UART_CPHA;    /*!< Specifies the clock transition on which the bit capture is made.
                               This parameter can be a value of @ref UART_Clock_Phase */

    uint16_t UART_LastBit; /*!< Specifies whether the clock pulse corresponding to the last transmitted
                               data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                               This parameter can be a value of @ref UART_Last_Bit */
} UART_ClockInitTypeDef;

/** @defgroup UART_Exported_Constants */ 
#define IS_UART_ALL_PERIPH(PERIPH)      ((PERIPH) == UART)

/** @defgroup UART_SPS_Select */ 
#define UART_SPS_SELECT                 ((uint16_t)0x0080)
#define IS_UART_SPS_SELECT(SELECT)      ((SELECT) == UART_SPS_SELECT)

/** @defgroup UART_Word_Length */ 
#define UART_WLEN_8b                    ((uint16_t)0x0060)
#define UART_WLEN_7b                    ((uint16_t)0x0040)
#define UART_WLEN_6b                    ((uint16_t)0x0020)
#define UART_WLEN_5b                    ((uint16_t)0x0000)
#define IS_UART_WORD_LENGTH(LENGTH)     (((LENGTH) == UART_WLEN_8b) || ((LENGTH) == UART_WLEN_7b) || \
                                        ((LENGTH) == UART_WLEN_6b) || ((LENGTH) == UART_WLEN_5b))

/** @defgroup UART_FIFO_Enable */ 
#define UART_FIFO_DIS                   ((uint16_t)0x0000)
#define UART_FIFO_EN                    ((uint16_t)0x0010)
#define IS_UART_FIFO_EN(EN)             ((EN) == UART_FIFO_EN || (EN) == UART_FIFO_DIS)

/** @defgroup UART_Stop_Bits */ 
#define UART_STP_1b                     ((uint16_t)0x0000)
#define UART_STP_2b                     ((uint16_t)0x0008)
#define IS_UART_STP(STP)                (((STP) == UART_STP_1b) || ((STP) == UART_STP_2b))

/** @defgroup UART_Parity */ 
#define UART_PARITY_NO                  ((uint16_t)0x0000)
#define UART_PARITY_ODD                 ((uint16_t)0x0004) 
#define UART_PARITY_EVEN                ((uint16_t)0x0006)
#define IS_UART_PARITY(PARITY)          (((PARITY) == UART_PARITY_NO) || \
                                        ((PARITY) == UART_PARITY_ODD) || \
                                        ((PARITY) == UART_PARITY_EVEN))
/** @defgroup UART_Send_Break */ 
#define UART_SEND_BREAK                 ((uint16_t)0x0001)
                                            

/** @defgroup UART_Hardware_Flow_Control */ 
#define UART_HW_FLOW_CTRL_NONE          ((uint16_t)0x0000)
#define UART_HW_FLOW_CTRL_CTS           ((uint16_t)0x8000)
#define UART_HW_FLOW_CTRL_RTS           ((uint16_t)0x4000)
#define UART_HW_FLOW_CTRL_RTS_CTS       ((uint16_t)0xC000)
#define IS_UART_HW_FLOW_CTRL(CTRL)      (((CTRL) == UART_HW_FLOW_CTRL_NONE) || \
                                        ((CTRL) == UART_HW_FLOW_CTRL_CTS) || \
                                        ((CTRL) == UART_HW_FLOW_CTRL_RTS) || \
                                        ((CTRL) == UART_HW_FLOW_CTRL_RTS_CTS))

/** @defgroup UART_Mode */
#define UART_MODE_NONE                  ((uint16_t)0x0000)
#define UART_MODE_RX                    ((uint16_t)0x0200)
#define UART_MODE_TX                    ((uint16_t)0x0100)
#define UART_MODE_TX_RX                 ((uint16_t)0x0300)
#define IS_UART_MODE(MODE)              (((MODE) == UART_MODE_NONE) || ((MODE) == UART_MODE_RX) || \
                                        ((MODE) == UART_MODE_TX) || ((MODE) == UART_MODE_TX_RX))

/** @defgroup UART_Mode_LoopBack */
#define UART_MODE_NORMAL                ((uint16_t)0x0000)
#define UART_MODE_LOOPBACK              ((uint16_t)0x0080)
#define IS_UART_LBE(LBE)                (((LBE) == UART_MODE_NORMAL) || ((LBE) == UART_MODE_LOOPBACK))

/** @defgroup UART_IrDA_Mode */
#define UART_IRDA_NORMAL                ((uint16_t)0x0000)
#define UART_IRDA_LOWPOWER              ((uint16_t)0x0004)
#define IS_UART_IRDA(IRDA)              (((IRDA) == UART_IRDA_NORMAL) || ((IRDA) == UART_IRDA_LOWPOWER))

/** @defgroup UART_IrDA_Enable */
#define UART_IRDA_ENABLE                ((uint16_t)0x0002)
#define IS_UART_IRDA_ENABLE(ENABLE)     ((ENABLE) == UART_IRDA_ENABLE)
                                      
/** @defgroup UART_Enable */
#define UART_ENABLE                     ((uint16_t)0x0001)
#define IS_UART_ENABLE(ENABLE)          ((ENABLE) == UART_ENABLE)

/** @defgroup UART_FIFO_Level */
#define UART_FIFO_LEVEL_RX1_8           ((uint16_t)0x0000)
#define UART_FIFO_LEVEL_RX1_4           ((uint16_t)0x0008)
#define UART_FIFO_LEVEL_RX1_2           ((uint16_t)0x0010)
#define UART_FIFO_LEVEL_RX3_4           ((uint16_t)0x0018)
#define UART_FIFO_LEVEL_RX7_8           ((uint16_t)0x0020)
#define IS_UART_FIFO_RX(RX)             (((RX) == UART_FIFO_LEVEL_RX1_8) || ((RX) == UART_FIFO_LEVEL_RX1_4) || \
                                        ((RX) == UART_FIFO_LEVEL_RX1_2) || ((RX) == UART_FIFO_LEVEL_RX3_4) || \
                                        ((RX) == UART_FIFO_LEVEL_RX7_8))
                                        
#define UART_FIFO_LEVEL_TX1_8           ((uint16_t)0x0000)
#define UART_FIFO_LEVEL_TX1_4           ((uint16_t)0x0001)
#define UART_FIFO_LEVEL_TX1_2           ((uint16_t)0x0002)
#define UART_FIFO_LEVEL_TX3_4           ((uint16_t)0x0003)
#define UART_FIFO_LEVEL_TX7_8           ((uint16_t)0x0004)
#define IS_UART_FIFO_TX(TX)             (((TX) == UART_FIFO_LEVEL_TX1_8) || ((TX) == UART_FIFO_LEVEL_TX1_4) || \
                                        ((TX) == UART_FIFO_LEVEL_TX1_2) || ((TX) == UART_FIFO_LEVEL_TX3_4) || \
                                        ((TX) == UART_FIFO_LEVEL_TX7_8))

/** @defgroup UART_Interrupt_Mask_definition */
#define UART_IT_OE                      ((uint16_t)0x0400)
#define UART_IT_BE                      ((uint16_t)0x0200)
#define UART_IT_PE                      ((uint16_t)0x0100)
#define UART_IT_FE                      ((uint16_t)0x0080)
#define UART_IT_RT                      ((uint16_t)0x0040)
#define UART_IT_TX                      ((uint16_t)0x0020)
#define UART_IT_RX                      ((uint16_t)0x0010)
#define UART_IT_DSR                     ((uint16_t)0x0008)
#define UART_IT_DCD                     ((uint16_t)0x0004)
#define UART_IT_CTS                     ((uint16_t)0x0002)
#define UART_IT_RIM                     ((uint16_t)0x0001)
#define IS_UART_CONFIG_IT(IT)           (((IT) == UART_IT_OE) || ((IT) == UART_IT_BE) || \
                                        ((IT) == UART_IT_PE) || ((IT) == UART_IT_FE) || \
                                        ((IT) == UART_IT_RT) || ((IT) == UART_IT_TX) || \
                                        ((IT) == UART_IT_RX) || ((IT) == UART_IT_DSR) || \
                                        ((IT) == UART_IT_DCD) || ((IT) == UART_IT_CTS) || \
                                        ((IT) == UART_IT_RIM))
#define IS_UART_GET_IT(IT)              (((IT) == UART_IT_OE) || ((IT) == UART_IT_BE) || \
                                        ((IT) == UART_IT_PE) || ((IT) == UART_IT_FE) || \
                                        ((IT) == UART_IT_RT) || ((IT) == UART_IT_TX) || \
                                        ((IT) == UART_IT_RX) || ((IT) == UART_IT_DSR) || \
                                        ((IT) == UART_IT_DCD) || ((IT) == UART_IT_CTS) || \
                                        ((IT) == UART_IT_RIM))
#define IS_UART_CLEAR_IT(IT)            (((IT) == UART_IT_OE) || ((IT) == UART_IT_BE) || \
                                        ((IT) == UART_IT_PE) || ((IT) == UART_IT_FE) || \
                                        ((IT) == UART_IT_RT) || ((IT) == UART_IT_TX) || \
                                        ((IT) == UART_IT_RX) || ((IT) == UART_IT_DSR) || \
                                        ((IT) == UART_IT_DCD) || ((IT) == UART_IT_CTS) || \
                                        ((IT) == UART_IT_RIM))

/** @defgroup UART_DMA_Requests */
#define UART_DMA_DIS                    ((uint16_t)0x0000)
#define UART_DMA_TX_EN                  ((uint16_t)0x0001)
#define UART_DMA_RX_EN                  ((uint16_t)0x0002)
#define UART_DMA_TX_RX_EN               ((uint16_t)0x0003)
#define IS_UART_DMA_EN(EN)              (((EN) == UART_DMA_DIS) || ((EN) == UART_DMA_TX_EN) || \
                                        ((EN) == UART_DMA_RX_EN) || ((EN) == UART_DMA_TX_RX_EN))

/** @defgroup UART_Recive_Flags */
#define UART_REV_FLAG_OE                ((uint16_t)0x0008)
#define UART_REV_FLAG_BE                ((uint16_t)0x0004)
#define UART_REV_FLAG_PE                ((uint16_t)0x0002)
#define UART_REV_FLAG_FE                ((uint16_t)0x0001)
#define IS_UART_REV_FLAG(FLAG)          (((FLAG) == UART_REV_FLAG_OE) || ((FLAG) == UART_REV_FLAG_BE) || \
                                        ((FLAG) == UART_REV_FLAG_PE) || ((FLAG) == UART_REV_FLAG_FE))
#define IS_UART_CLEAR_REV_FLAG(FLAG)    (((FLAG) <= (uint16_t)0x000F) && ((FLAG) != (uint16_t)0x00))

/** @defgroup UART_Flags */
#define UART_FLAG_RI                    ((uint16_t)0x0100)
#define UART_FLAG_TXFE                  ((uint16_t)0x0080)
#define UART_FLAG_RXFF                  ((uint16_t)0x0040)
#define UART_FLAG_TXFF                  ((uint16_t)0x0020)
#define UART_FLAG_RXFE                  ((uint16_t)0x0010)
#define UART_FLAG_BUSY                  ((uint16_t)0x0008)
#define UART_FLAG_DCD                   ((uint16_t)0x0004)
#define UART_FLAG_DSR                   ((uint16_t)0x0002)
#define UART_FLAG_CTS                   ((uint16_t)0x0001)
#define IS_UART_FLAG(FLAG)              (((FLAG) == UART_FLAG_RI) || \
                                        ((FLAG) == UART_FLAG_TXFE) || ((FLAG) == UART_FLAG_RXFF) || \
                                        ((FLAG) == UART_FLAG_TXFF) || ((FLAG) == UART_FLAG_RXFE) || \
                                        ((FLAG) == UART_FLAG_BUSY) || ((FLAG) == UART_FLAG_DCD) || \
                                        ((FLAG) == UART_FLAG_DSR) || ((FLAG) == UART_FLAG_CTS))
#define IS_UART_CLEAR_FLAG(FLAG)        (((FLAG) <= (uint16_t)0x00FF) && ((FLAG) != (uint16_t)0x00))
#define IS_UART_BAUDRATE(BAUDRATE)      (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))
#define IS_UART_DATA(DATA)              ((DATA) <= 0x1FF)

void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_ITConfig(UART_TypeDef* UARTx, uint16_t UART_IT, FunctionalState NewState);
void UART_DMACmd(UART_TypeDef* UARTx, uint16_t UART_DMAReq, FunctionalState NewState);
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReceiveData(UART_TypeDef* UARTx);
void UART_SendBreak(UART_TypeDef* UARTx);
void UART_IrDAConfig(UART_TypeDef* UARTx, uint16_t UART_IrDAMode);
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint16_t UART_FLAG);
ITStatus UART_GetRawITStatus(UART_TypeDef* UARTx, uint16_t UART_IT);
ITStatus UART_GetMaskITStatus(UART_TypeDef* UARTx, uint16_t UART_IT);
void UART_ClearITStatus(UART_TypeDef* UARTx, uint16_t UART_IT);

void UART_PrintReg(UART_TypeDef* UARTx);

#ifdef __cplusplus
}
#endif

#endif 

