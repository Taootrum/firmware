/*******************************************************************************
  * @file    acu_efuse.h
  * @author  DengLin SOC Team
  * @version V3.5.0
  * @date    6-September-2018
  * @brief   This file contains all the functions prototypes for the EFUSE 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_EFUSE_H
#define __ACU_EFUSE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"

/* @defgroup EFUSE_KEY */
#define EFUSE_KEY           ((uint32_t)0xBEAF0000)

/* @defgroup EFUSE_RESETB */
#define EFUSE_RESETB        ((uint32_t)0x00008000)

/* @defgroup EFUSE_VDDQPS */
#define EFUSE_VDDQPS        ((uint32_t)0x00004000)

/* @defgroup EFUSE_CLOCK_SOURCE */
#define EFUSE_CLOCK_APB     ((uint32_t)0x00002000)

/* @defgroup EFUSE_AUTO */
#define EFUSE_AUTO          ((uint32_t)0x00000100)

#define FUSE_ARRAY_MAX      32

/** @defgroup PVT_Exported_Functions */
void EFUSE_DeInit(void);
void EFUSE_Init(void);
void EFUSE_ITConfig(FunctionalState NewState);
void EFUSE_WriteData(uint8_t Array, uint32_t *Data, uint8_t Num);
void EFUSE_ReadData(uint8_t Array, uint32_t *Data, uint8_t Num);
FlagStatus EFUSE_GetStatus(void);
uint16_t EFUSE_GetIntStat(void);
void EFUSE_PrintReg(void);
                                   
#ifdef __cplusplus
}
#endif

#endif 

