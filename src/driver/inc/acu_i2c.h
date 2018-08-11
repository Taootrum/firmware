/*******************************************************************************
  * @file    acu_i2c.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU IIC Module Function. 
 ******************************************************************************/
#ifndef __ACU_I2C_H
#define __ACU_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"

/** @brief  I2C Init structure definition */
typedef struct
{
    uint32_t I2C_Speed;                 /*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 3.4MHz */
    uint16_t I2C_Mode;                  /*!< Specifies the I2C mode. */
    uint16_t I2C_AddressMode;           /*!< 7-bit or 10-bit. */
    uint16_t I2C_HSMasterAddress;       /*!< Specifies Hign speed master address. */
    uint16_t I2C_OwnAddress;            /*!< Specifies own address. */
    uint16_t I2C_AckAddress;            /*!< Specifies if 7-bit or 10-bit address is acknowledged. */
    uint16_t I2C_Acknowledge;           /*!< Specifies Enable or Disable. */
    uint16_t I2C_TxFIFOLevel;           /*!< Specifies Tx FIFO Level. */
    uint16_t I2C_RxFIFOLevel;           /*!< Specifies Rx FIFO Level. */
}I2C_InitTypeDef;

/** @defgroup I2C_Exported_Constants */
#define IS_I2C_ALL_PERIPH(PERIPH)       (((PERIPH) == I2C0) || ((PERIPH) == I2C1) || \
                                        ((PERIPH) == I2C2))

/** @defgroup I2C_Speed */
#define I2C_Speed_100k                  ((uint16_t)0x0002)
#define I2C_Speed_400k                  ((uint16_t)0x0004)  
#define I2C_Speed_3400k                 ((uint16_t)0x0006)
#define IS_I2C_SPEED(SPEED)             (((SPEED) == I2C_Speed_100k) || ((SPEED) == I2C_Speed_400k) || \
                                        ((SPEED) == I2C_Speed_3400k))

/** @defgroup I2C_mode */
#define I2C_Mode_Master                 ((uint16_t)0x0041)  
#define I2C_Mode_Slave                  ((uint16_t)0x0000)
#define I2C_Mode_Passive                ((uint16_t)0x0400)
#define IS_I2C_MODE(MODE)               (((MODE) == I2C_Mode_Master) || ((MODE) == I2C_Mode_Slave) || \
                                        ((MODE) == I2C_Mode_Passive))

/** @defgroup I2C_restart_en */
#define I2C_Restart_Enable              ((uint16_t)0x0020)

/** @defgroup I2C_duty_cycle_in_fast_mode */
/*!< I2C fast mode Tlow/Thigh = 16/9 */
/*!< I2C fast mode Tlow/Thigh = 2 */

/** @defgroup I2C_acknowledged_address */
#define I2C_Address_7bit                ((uint16_t)0x0000)
#define I2C_Address_10bit               ((uint16_t)0x0018)
#define IS_I2C_ADDRESS_MODE(MODE)       (((MODE) == I2C_Address_7bit) || ((MODE) == I2C_Address_10bit))

/** @defgroup I2C_ack_en */
#define I2C_ACK_DISABLE                 ((uint16_t)0x0000)
#define I2C_ACK_ENABLE                  ((uint16_t)0x0001)
#define IS_I2C_ACKNOWLEDGE(ACKNOWLEDGE) (((ACKNOWLEDGE) == I2C_ACK_DISABLE) || ((ACKNOWLEDGE) == I2C_ACK_ENABLE))

/** @defgroup I2C_interrupts_definition */
#define I2C_IT_GEN_CALL                 ((uint32_t)0x00000800)
#define I2C_IT_START_DET                ((uint32_t)0x00000400)
#define I2C_IT_STOP_DET                 ((uint32_t)0x00000200)
#define I2C_IT_ACTIVITY                 ((uint32_t)0x00000100)
#define I2C_IT_RX_DONE                  ((uint32_t)0x00000080)
#define I2C_IT_TX_ABRT                  ((uint32_t)0x00000040)
#define I2C_IT_RD_REQ                   ((uint32_t)0x00000020)
#define I2C_IT_TX_EMPTY                 ((uint32_t)0x00000010)
#define I2C_IT_TX_OVER                  ((uint32_t)0x00000008)
#define I2C_IT_RX_FULL                  ((uint32_t)0x00000004)
#define I2C_IT_RX_OVER                  ((uint32_t)0x00000002)
#define I2C_IT_RX_UNDER                 ((uint32_t)0x00000001)
#define I2C_IT_INTR                     ((uint32_t)0x00000FFF)
#define IS_I2C_IT(IT)                   (((IT) == I2C_IT_GEN_CALL) || ((IT) == I2C_IT_START_DET) || \
                                        ((IT) == I2C_IT_STOP_DET) || ((IT) == I2C_IT_ACTIVITY) || \
                                        ((IT) == I2C_IT_RX_DONE) || ((IT) == I2C_IT_TX_ABRT) || \
                                        ((IT) == I2C_IT_RD_REQ) || ((IT) == I2C_IT_TX_EMPTY) || \
                                        ((IT) == I2C_IT_TX_OVER) || ((IT) == I2C_IT_RX_FULL) || \
                                        ((IT) == I2C_IT_RX_OVER) || ((IT) == I2C_IT_RX_UNDER))
#define IS_I2C_IT_FLAG(IT)              (((IT) == I2C_IT_GEN_CALL) || ((IT) == I2C_IT_START_DET) || \
                                        ((IT) == I2C_IT_STOP_DET) || ((IT) == I2C_IT_ACTIVITY) || \
                                        ((IT) == I2C_IT_RX_DONE) || ((IT) == I2C_IT_TX_ABRT) || \
                                        ((IT) == I2C_IT_RD_REQ) || ((IT) == I2C_IT_TX_EMPTY) || \
                                        ((IT) == I2C_IT_TX_OVER) || ((IT) == I2C_IT_RX_FULL) || \
                                        ((IT) == I2C_IT_RX_OVER) || ((IT) == I2C_IT_RX_UNDER))
#define IS_I2C_CLEAR_IT_FLAG(IT)        (((IT) == I2C_IT_GEN_CALL) || ((IT) == I2C_IT_START_DET) || \
                                        ((IT) == I2C_IT_STOP_DET) || ((IT) == I2C_IT_ACTIVITY) || \
                                        ((IT) == I2C_IT_RX_DONE) || ((IT) == I2C_IT_TX_ABRT) || \
                                        ((IT) == I2C_IT_RD_REQ) || ((IT) == I2C_IT_TX_OVER) || \
                                        ((IT) == I2C_IT_RX_OVER) || ((IT) == I2C_IT_RX_UNDER) || \
                                        ((IT) == I2C_IT_INTR))

/** @brief  SR register flags */
#define I2C_FLAG_SLV_ACTIVITY           ((uint32_t)0x00000040)
#define I2C_FLAG_MST_ACTIVITY           ((uint32_t)0x00000020)
#define I2C_FLAG_REF                    ((uint32_t)0x00000010)
#define I2C_FLAG_RFNE                   ((uint32_t)0x00000008)
#define I2C_FLAG_TFE                    ((uint32_t)0x00000004)
#define I2C_FLAG_TFNF                   ((uint32_t)0x00000002)
#define I2C_FLAG_ACTIVITY               ((uint32_t)0x00000001)
#define IS_I2C_FLAG(FLAG)               (((FLAG) == I2C_FLAG_SLV_ACTIVITY) || ((FLAG) == I2C_FLAG_MST_ACTIVITY) || \
                                        ((FLAG) == I2C_FLAG_REF) || ((FLAG) == I2C_FLAG_RFNE) || \
                                        ((FLAG) == I2C_FLAG_TFE) || ((FLAG) == I2C_FLAG_TFNF) || \
                                        ((FLAG) == I2C_FLAG_ACTIVITY))
                                        
/** @defgroup I2C_FIFO_definition */
#define I2C_FIFO_TX_LEVEL               ((uint8_t)0x10)
#define I2C_FIFO_RX_LEVEL               ((uint8_t)0x10)
#define I2C_FIFO_LEVEL_MAX              ((uint8_t)0x10)
#define IS_I2C_FIFO_TH(TH)              ((TH) <= I2C_FIFO_LEVEL_MAX)

/** @defgroup I2C_hs_master_address */
#define IS_I2C_HS_MADDRESS(ADDRESS)     ((ADDRESS) <= 0x7)
/** @defgroup I2C_own_address */
#define IS_I2C_OWN_ADDRESS(ADDRESS)     ((ADDRESS) <= 0x3FF)
/** @defgroup I2C_ack_address */
#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS) ((ADDRESS) <= 0x3FF)
/** @defgroup I2C_fifo_level */
#define IS_I2C_FIFO_LEVEL(LEVEL)        ((LEVEL) <= 0x0F)

#define I2C_ENABLE                      ((uint32_t)0x00000001)
#define I2C_MASTER_READ_CMD             ((uint32_t)0x00000100)

/** @defgroup I2C_Exported_Functions */
void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT_STATUS);
ITStatus I2C_GetRawITStatus(I2C_TypeDef* I2Cx, uint16_t I2C_IT_STATUS);
void I2C_ClearITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT_STATUS);
void I2C_PrintReg(I2C_TypeDef* I2Cx);

#ifdef __cplusplus
}
#endif

#endif 

