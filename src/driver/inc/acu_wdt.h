/*******************************************************************************
  * @file    acu_wdt.h
  * @author  DengLin SOC Team
  * @version V1.0.0
  * @date    28-Augest-2018
  * @brief   This file contains all the functions prototypes for the WDT 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_WDT_H
#define __ACU_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"

/**@brief  WDT Input Capture Init structure definition */
typedef struct
{
    uint16_t WDT_Mode;          /*!< WDT mode:Directly reset, Timeout reset */
    uint16_t WDT_Top;           /*!< t = 2^(16 + WDT_Top). */
} WDT_InitTypeDef;
                                      
/** @defgroup WDT_Mode */
#define WDT_DIRECT_RESET            ((uint16_t)0x0000)
#define WDT_TIMEOUT_RESET           ((uint16_t)0x0002)
#define IS_WDT_MODE(MODE)           (((MODE) == WDT_DIRECT_RESET) || ((MODE) == WDT_TIMEOUT_RESET))

/** @defgroup WDT_TimeoutRange */
#define WDT_TOP                     ((uint16_t)0x0006)
#define IS_WDT_TOP(TOP)             ((TOP) <= 0xF)

/** @defgroup WDT_Enable */
#define WDT_ENABLE               ((uint16_t)0x0001)


/** @defgroup WDT_Exported_Functions */
void WDT_DeInit(void);
void WDT_Init(WDT_InitTypeDef *WDT_InitStruct);
void WDT_StructInit(WDT_InitTypeDef* WDT_InitStruct);
void WDT_Cmd(FunctionalState NewState);
uint32_t WDT_GetCounter(void);
void WDT_Pause(FunctionalState NewState);
void WDT_DebugCmd(FunctionalState NewState);
void WDT_Restart(void);
uint32_t WDT_GetITStatus(void);
uint32_t WDT_ClearIT(void);

#ifdef __cplusplus
}
#endif

#endif 

