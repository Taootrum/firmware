/*******************************************************************************
  * @file    acu_int_gen.h
  * @author  DengLin SOC Team
  * @version V1.0.0
  * @date    30-Augest-2018
  * @brief   This file contains all the functions prototypes for the INT generator 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_INT_GEN_H
#define __ACU_INT_GEN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"

/**@brief  WDT Input Capture Init structure definition */
typedef enum
{
    TYPE_INT_OFF = 0x0,
    TYPE_INT_PASSIVE,
    TYPE_INT_PCIE
} IntGenType;

/** @defgroup WDT_Exported_Functions */
void INT_DeInit(void);
void INT_Init(void);
void INT_Generate(IntGenType Type);
void INT_ClearIT(void);

#ifdef __cplusplus
}
#endif

#endif 

