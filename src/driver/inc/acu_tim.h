/*******************************************************************************
  * @file    acu_tim.h
  * @author  DengLin SOC Team
  * @version V1.0.0
  * @date    24-Augest-2018
  * @brief   This file contains all the functions prototypes for the TIM firmware 
  *          library.
 ******************************************************************************/
#ifndef __ACU_TIM_H
#define __ACU_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"     

/**@brief  TIM Input Capture Init structure definition */
typedef struct
{
    uint16_t TIM_Mode;          /*!< Timer running mode:free-running mode,user-defined count mode */
    uint16_t TIM_TimingTime;    /*!< N * ms time will be load. */
} TIM_InitTypeDef;

/** @defgroup TIM_Exported_constants */
#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM0) || ((PERIPH) == TIM1))

/** @defgroup TIM_Mode */
#define FREE_RUNNING        0x0
#define USER_DEFINED        0x2
#define IS_TIM_MODE(MODE)   (((MODE) == FREE_RUNNING) || ((MODE) == USER_DEFINED))

/** @defgroup TIM_Timing_Time */
#define TIM_TIMING_TIME     0x1
#define IS_TIM_TIME(TIME)   ((TIME) && (TIME) <= 1000) /* max timing time is 1000 * 1ms */

/** @defgroup TIM_INT_EANBLE */
#define TIM_INT_ENABLE      0x4

/** @defgroup TIM_EANBLE */
#define TIM_ENABLE          0x1

/** @defgroup TIM_Exported_Functions
  * @{
  */
void TIM_DeInit(void);
void TIM_Init(TIM_TypeDef* TIMx, TIM_InitTypeDef *TIM_InitStruct);
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx);
void TIM_ITConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
uint32_t TIM_ClearIT(TIM_TypeDef* TIMx);
uint32_t TIM_GetITStatus(TIM_TypeDef* TIMx);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif 

