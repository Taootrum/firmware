/*******************************************************************************
  * @file    acu_gpio.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU GPIO Module Function. 
 ******************************************************************************/

#ifndef __ACU_GPIO_H
#define __ACU_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"

/**@brief  GPIO Init structure definition */
typedef struct
{
    uint32_t GPIO_Direction;          /*!< input/output */
    uint32_t GPIO_InterruptMask;      /*!< interrupt mask */
    uint32_t GPIO_PullStatus;         /*!< pull up/pull down */
    uint32_t GPIO_InterruptType;      /*!< LowLevel/HighLevel/FallingEdge/RisingEdge/BothEdge */
} GPIO_InitTypeDef;

/**@brief  Bit_SET and Bit_RESET enumeration */
typedef enum
{ 
    GPIO_RESET = 0,
    GPIO_SET
} GPIO_Action;
#define IS_GPIO_ACTION(ACTION)      (((ACTION) == GPIO_RESET) || ((ACTION) == GPIO_SET))

/** @defgroup GPIO_Direciton_define */
#define GPIO_INPUT                  ((uint32_t)0x00000000)   
#define GPIO_OUTPUT                 ((uint32_t)0x00000001)      
#define IS_GPIO_DR(DR)              (((DR) == GPIO_INPUT) || ((DR) == GPIO_OUTPUT))

/** @defgroup GPIO_InterruptMask_define */
#define GPIO_INTMASK_EN             ((uint32_t)0x00000000)   
#define GPIO_INTMASK_DIS            ((uint32_t)0x00000001)      
#define IS_GPIO_IM(IM)              (((IM) == GPIO_INTMASK_EN) || ((IM) == GPIO_INTMASK_DIS))

/** @defgroup GPIO_PullStatus_define */
#define GPIO_PULLUP                 ((uint32_t)0x00000001)   
#define GPIO_PULLDOWN               ((uint32_t)0x00000000)      
#define IS_GPIO_PULL(PULL)          (((PULL) == GPIO_PULLUP) || ((PULL) == GPIO_PULLDOWN))

/** @defgroup GPIO_InterruptType_define */
#define GPIO_LOW_LEVEL              ((uint32_t)0x00000000)   
#define GPIO_GIGH_LEVEL             ((uint32_t)0x00000001)
#define GPIO_FALLING_EDGE           ((uint32_t)0x00000002)
#define GPIO_RISING_EDGE            ((uint32_t)0x00000004)
#define GPIO_BOTH_EDGE              ((uint32_t)0x00000006)
#define IS_GPIO_IT(IT)              (((IT) == GPIO_LOW_LEVEL) || ((IT) == GPIO_GIGH_LEVEL) || \
                                    ((IT) == GPIO_FALLING_EDGE) || ((IT) == GPIO_RISING_EDGE) || \
                                    ((IT) == GPIO_BOTH_EDGE))

/** @defgroup GPIO_function_define */
#define GPIO_IOPAD_GPIO             ((uint32_t)0x00000001)   
#define GPIO_IOPAD_FUNC             ((uint32_t)0x00000000)
#define IS_GPIO_IOPAD_MODE(MODE)    (((MODE) == GPIO_IOPAD_GPIO) || ((MODE) == GPIO_IOPAD_FUNC))

/** @defgroup GPIO_pins_define */
#define GPIO_0                      GPIO15       /*!< Pin 0 selected */
#define GPIO_1                      GPIO16       /*!< Pin 1 selected */
#define GPIO_2                      GPIO17       /*!< Pin 2 selected */
#define GPIO_3                      GPIO18       /*!< Pin 3 selected */
#define GPIO_4                      GPIO19       /*!< Pin 4 selected */
#define GPIO_5                      GPIO20       /*!< Pin 5 selected */
#define GPIO_6                      GPIO21       /*!< Pin 6 selected */
#define GPIO_7                      GPIO22       /*!< Pin 7 selected */
#define GPIO_8                      GPIO23       /*!< Pin 8 selected */
#define GPIO_9                      GPIO24       /*!< Pin 9 selected */
#define GPIO_10                     GPIO25       /*!< Pin 10 selected */
#define GPIO_11                     GPIO26       /*!< Pin 11 selected */
#define IS_GET_GPIO_PIN(PIN)    (((PIN) == GPIO_0) || ((PIN) == GPIO_1) || \
                                  ((PIN) == GPIO_2) || ((PIN) == GPIO_3) || \
                                  ((PIN) == GPIO_4) || ((PIN) == GPIO_5) || \
                                  ((PIN) == GPIO_6) || ((PIN) == GPIO_7) || \
                                  ((PIN) == GPIO_8) || ((PIN) == GPIO_9) || \
                                  ((PIN) == GPIO_10) || ((PIN) == GPIO_11))

/** @defgroup GPIO_MUX_define */
#define GPIO_SSP_TXD                GPIO0       /*!< GPIO0 SSP_TXD */
#define GPIO_SSP_RXD                GPIO1       /*!< GPIO1 SSP_RXD */
#define GPIO_SSP_CSN                GPIO2       /*!< GPIO2 SSP_CSN */
#define GPIO_SSP_CLK                GPIO3       /*!< GPIO3 SSP_CLK */
#define GPIO_IIC_SCL0               GPIO4       /*!< GPIO4 IIC_SCL0 */
#define GPIO_IIC_SDA0               GPIO5       /*!< GPIO5 IIC_SDA0 */
#define GPIO_IIC_SCL1               GPIO6       /*!< GPIO6 IIC_SCL1 */
#define GPIO_IIC_SDA1               GPIO7       /*!< GPIO7 IIC_SDA1 */
#define GPIO_JTAG_TDO               GPIO8       /*!< GPIO8 JTAG_TDO */
#define GPIO_JTAG_TDI               GPIO9       /*!< GPIO9 JTAG_TDI */
#define GPIO_JTAG_TMS               GPIO10      /*!< GPIO10 JTAG_TMS */
#define GPIO_JTAG_TCK               GPIO11      /*!< GPIO11 JTAG_TCK */
#define GPIO_UART_TXD               GPIO12      /*!< GPIO12 UART_TXD */
#define GPIO_UART_RXD               GPIO13      /*!< GPIO13 UART_RXD */
#define GPIO_JTAG_TRSTN             GPIO14      /*!< GPIO14 JTAG_TRSTN */
#define IS_GPIO_MUXMAP(MUXMAP) (((MUXMAP) == GPIO_SSP_TXD) || ((MUXMAP) == GPIO_SSP_RXD) || \
                                  ((MUXMAP) == GPIO_SSP_CSN) || ((MUXMAP) == GPIO_SSP_CLK) || \
                                  ((MUXMAP) == GPIO_IIC_SCL0) || ((MUXMAP) == GPIO_IIC_SCL1) || \
                                  ((MUXMAP) == GPIO_IIC_SCL1) || ((MUXMAP) == GPIO_IIC_SDA1) || \
                                  ((MUXMAP) == GPIO_JTAG_TDO) || ((MUXMAP) == GPIO_JTAG_TDI) || \
                                  ((MUXMAP) == GPIO_JTAG_TMS) || ((MUXMAP) == GPIO_JTAG_TCK) || \
                                  ((MUXMAP) == GPIO_UART_TXD) || ((MUXMAP) == GPIO_UART_RXD) || \
                                  ((MUXMAP) == GPIO_JTAG_TRSTN))

/** @defgroup GPIO_Exported_Functions */
void GPIO_DeInit(APBSYS_TypeDef*    GPIO);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_IOPADMode(GPIO_TypeDef* GPIOx, uint32_t IoPadMode);
uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetOutput(GPIO_TypeDef* GPIOx, GPIO_Action Action);
void GPIO_IntCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState);

/* Debug print */
void GPIO_PrintReg(GPIO_TypeDef* GPIOx);
void GPIO_IOPADPrintReg(IOPAD_TypeDef* IOPad);

#ifdef __cplusplus
}
#endif

#endif 

