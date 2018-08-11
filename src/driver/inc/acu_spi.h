/*******************************************************************************
  * @file    acu_spi.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Module Function. 
 ******************************************************************************/

#ifndef __ACU_SPI_H
#define __ACU_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"

/* @brief  SPI Init structure definition */
typedef struct {
    uint16_t SPI_LBM;                 /*!< Loop back mode.*/
    uint16_t SPI_SSE;                 /*!< Synchronous serial port enable.*/
    uint16_t SPI_Mode;                /*!< Specifies the SPI operating mode.*/
    uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.*/
    uint16_t SPI_FRAME;               /*!< Specifies the SPI data size.*/
    uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.ref SPI_Clock_Polarity */
    uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.@ref SPI_Clock_Phase */
    uint16_t SPI_BaudRate;            /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.*/
    uint16_t SPI_CPSR;
    uint16_t SPI_TX_FIFO;
    uint16_t SPI_RX_FIFO;
}SPI_InitTypeDef;

#define IS_SPI_ALL_PERIPH(PERIPH)       (((PERIPH) == SPI0) || ((PERIPH) == SPI1))

/* @defgroup SPI_LBM */
#define SPI_MODE_NORMAL                 ((uint16_t)0x0000)
#define SPI_MODE_LOOPBACK               ((uint16_t)0x0001)
#define IS_SPI_LBM(MODE)                (((MODE) == SPI_MODE_LOOPBACK) || \
                                        ((MODE) == SPI_MODE_NORMAL))

#define SPI_ENABLE                      ((uint16_t)0x0002)
                                    
/* @defgroup SPI_mode */
#define SPI_MODE_MASTER                 ((uint16_t)0x0000)
#define SPI_MODE_SLAVE                  ((uint16_t)0x0004)
#define IS_SPI_MODE(MODE)               (((MODE) == SPI_MODE_MASTER) || \
                                        ((MODE) == SPI_MODE_SLAVE))

/* @defgroup SPI_mode */
#define SPI_SLAVE_OUTPUT_EN             ((uint16_t)0x0008)

/* @defgroup SPI_data_size */
#define SPI_DataSize_4b                 ((uint16_t)0x0003)
#define SPI_DataSize_5b                 ((uint16_t)0x0004)
#define SPI_DataSize_6b                 ((uint16_t)0x0005)
#define SPI_DataSize_7b                 ((uint16_t)0x0006)
#define SPI_DataSize_8b                 ((uint16_t)0x0007)
#define SPI_DataSize_9b                 ((uint16_t)0x0008)
#define SPI_DataSize_10b                ((uint16_t)0x0009)
#define SPI_DataSize_11b                ((uint16_t)0x000A)
#define SPI_DataSize_12b                ((uint16_t)0x000B)
#define SPI_DataSize_13b                ((uint16_t)0x000C)
#define SPI_DataSize_14b                ((uint16_t)0x000D)
#define SPI_DataSize_15b                ((uint16_t)0x000E)
#define SPI_DataSize_16b                ((uint16_t)0x000F)
#define IS_SPI_DATASIZE(DATASIZE)       (((DATASIZE) == SPI_DataSize_4b) || ((DATASIZE) == SPI_DataSize_5b) || \
                                        ((DATASIZE) == SPI_DataSize_6b) || ((DATASIZE) == SPI_DataSize_7b) || \
                                        ((DATASIZE) == SPI_DataSize_8b) || ((DATASIZE) == SPI_DataSize_9b) || \
                                        ((DATASIZE) == SPI_DataSize_10b) || ((DATASIZE) == SPI_DataSize_11b) || \
                                        ((DATASIZE) == SPI_DataSize_12b) || ((DATASIZE) == SPI_DataSize_13b) || \
                                        ((DATASIZE) == SPI_DataSize_14b) || ((DATASIZE) == SPI_DataSize_15b) || \
                                        ((DATASIZE) == SPI_DataSize_16b))
                                        
/** @defgroup Frame Format */
#define SPI_FRAME_MOTOROLA              ((uint16_t)0x0000)
#define SPI_FRAME_TI                    ((uint16_t)0x0010)
#define SPI_FRAME_NATIONAL              ((uint16_t)0x0020)
#define IS_SPI_FRAME(FRAME)             (((FRAME) == SPI_FRAME_MOTOROLA) || \
                                        ((FRAME) == SPI_FRAME_TI) || \
                                        ((FRAME) == SPI_FRAME_NATIONAL))

/** @defgroup SPI_Clock_Polarity */
#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   ((uint16_t)0x0040)
#define IS_SPI_CPOL(CPOL)               (((CPOL) == SPI_CPOL_Low) || \
                                        ((CPOL) == SPI_CPOL_High))

/** @defgroup SPI_Clock_Phase */
#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  ((uint16_t)0x0080)
#define IS_SPI_CPHA(CPHA)               (((CPHA) == SPI_CPHA_1Edge) || \
                                        ((CPHA) == SPI_CPHA_2Edge))

/** @defgroup SPI_BaudRate_Prescaler */
#define SPI_BAUDRATE                    ((uint16_t)0x0000)
#define SPI_BAUDRATE_MAX                ((uint16_t)0xFF00)
#define IS_SPI_BAUDRATE(PRESCALER)      ((PRESCALER) <= SPI_BAUDRATE_MAX)
                                        
/** @defgroup SPI_status_definition */
#define SPI_FLAG_TXE                    ((uint16_t)0x0001)
#define SPI_FLAG_TXNF                   ((uint16_t)0x0002)
#define SPI_FLAG_RXNE                   ((uint16_t)0x0004)
#define SPI_FLAG_RXF                    ((uint16_t)0x0008)
#define SPI_FLAG_BSY                    ((uint16_t)0x0010)
#define IS_SPI_GET_FLAG(FLAG)           (((FLAG) == SPI_FLAG_TXE) || ((FLAG) == SPI_FLAG_TXNF) || \
                                        ((FLAG) == SPI_FLAG_RXNE) || ((FLAG) == SPI_FLAG_RXF) || \
                                        ((FLAG) == SPI_FLAG_BSY))
                                        
/** @defgroup SPI_BaudRate_Prescaler */
#define SPI_CPSDVSR                     ((uint16_t)0x0008)
#define SPI_CPSDVSR_MIX                 ((uint16_t)0x0002)
#define SPI_CPSDVSR_MAX                 ((uint16_t)0x00FE)
#define IS_SPI_CPSDVSR(CPSDVSR)         (((CPSDVSR) >= SPI_CPSDVSR_MIX) && \
                                        ((CPSDVSR) <= SPI_CPSDVSR_MAX))

/** @defgroup SPI_interrupts_definition */
#define SPI_IT_TXIM                     ((uint8_t)0x08)
#define SPI_IT_RXIM                     ((uint8_t)0x04)
#define SPI_IT_RTIM                     ((uint8_t)0x02)
#define SPI_IT_RORIM                    ((uint8_t)0x01)
#define IS_SPI_CONFIG_IT(IT)            (((IT) == SPI_IT_TXIM) || ((IT) == SPI_IT_RXIM) || \
                                        ((IT) == SPI_IT_RTIM) || ((IT) == SPI_IT_RORIM))
#define IS_SPI_GET_IT(IT)               (((IT) == SPI_IT_TXIM) || ((IT) == SPI_IT_RXIM) || \
                                        ((IT) == SPI_IT_RTIM) || ((IT) == SPI_IT_RORIM))
                                        
#define SPI_IT_RTC                      ((uint8_t)0x02)
#define SPI_IT_RORC                     ((uint8_t)0x01)                                        
#define IS_SPI_CLEAR_IT(IT)             (((IT) == SPI_IT_RTC) || ((IT) == SPI_IT_RORC))
                                        
#define SPI_RIT_TXRIS                   ((uint8_t)0x08)
#define SPI_RIT_RXRIS                   ((uint8_t)0x04)
#define SPI_RIT_RTRIS                   ((uint8_t)0x02)
#define SPI_RIT_RORRIS                  ((uint8_t)0x01)                                        
#define IS_SPI_GET_RIT_FLAG(RIT)        (((RIT) == SPI_RIT_TXRIS) || ((RIT) == SPI_RIT_RXRIS) || \
                                        ((RIT) == SPI_RIT_RTRIS) || ((RIT) == SPI_RIT_RORRIS))
                                        
#define SPI_MIT_TXMIS                   ((uint8_t)0x08)
#define SPI_MIT_RXMIS                   ((uint8_t)0x04)
#define SPI_MIT_RTMIS                   ((uint8_t)0x02)
#define SPI_MIT_RORMIS                  ((uint8_t)0x01)                                        
#define IS_SPI_GET_MIT_FLAG(MIT)        (((MIT) == SPI_MIT_TXMIS) || ((MIT) == SPI_MIT_RXMIS) || \
                                        ((MIT) == SPI_MIT_RTMIS) || ((MIT) == SPI_MIT_RORMIS))

/** @defgroup SPI_DMA_definition */
#define SPI_DMA_TX                      ((uint8_t)0x02)
#define SPI_DMA_RX                      ((uint8_t)0x01)
#define IS_SPI_DMA(DMA)                 (((DMA) == SPI_DMA_TX) || ((DMA) == SPI_DMA_RX))

/** @defgroup SPI_FIFO_definition */
#define SPI_FIFO_TX_TH                  ((uint8_t)0x40)
#define SPI_FIFO_RX_TH                  ((uint8_t)0x40)
#define SPI_FIFO_TH_MAX                 ((uint8_t)0x3F)
#define IS_SPI_FIFO_TH(TH)              ((TH) <= SPI_FIFO_TH_MAX)

/** @defgroup SPI_Exported_Functions */
void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx);
FlagStatus SPI_GetStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState);
ITStatus SPI_GetRawITStatus(SPI_TypeDef* SPIx, uint8_t SPI_RIT);
ITStatus SPI_GetMaskITStatus(SPI_TypeDef* SPIx, uint8_t SPI_MIT);
void SPI_ClearIT(SPI_TypeDef* SPIx, uint16_t SPI_ITClear);
void SPI_PrintReg(SPI_TypeDef* SPIx);

#ifdef __cplusplus
}
#endif

#endif 

