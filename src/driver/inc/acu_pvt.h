/*******************************************************************************
  * @file    acu_pvt.h
  * @author  DengLin SOC Team
  * @version V3.5.0
  * @date    15-Augest-2018
  * @brief   This file contains all the functions prototypes for the PVT(Power/Voltage/Temprature) 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_PVT_H
#define __ACU_PVT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"

/* @brief  PVT Init structure definition */
typedef struct {
    uint16_t PVT_MODE;                 /*!< Mode: PSAMPLE1/PSAMPLE0/VSAMPLE. */
    uint16_t PVT_TIMG;                 /*!< TRIM input of Sensor[4:0].*/
} PVT_InitTypeDef;

/* @defgroup PVT_MODE */
#define PVT_MODE_PSAMPLE1               ((uint16_t)0x0001)
#define PVT_MODE_PSAMPLE0               ((uint16_t)0x0002)
#define PVT_MODE_VSAMPLE                ((uint16_t)0x0004)
#define IS_PVT_MODE(MODE)               ((MODE) <= 0x0007)

/* @defgroup TRIM */
#define PVT_TRIM                        ((uint16_t)0x000F)
#define IS_PVT_TRIM(TRIM)               ((TRIM) <= 0x000F))

/* @defgroup SENSOR_ENA */
#define PVT_ENABLE                      ((uint16_t)0x0001)
#define PVT_INT_ENABLE                  ((uint16_t)0x0001)

/** @defgroup PVT_Exported_Functions */
void PVT_DeInit(void);
void PVT_Init(PVT_InitTypeDef* PVT_InitStruct);
void PVT_StructInit(PVT_InitTypeDef* PVT_InitStruct);
void PVT_Cmd(FunctionalState NewState);
void PVT_ITConfig(FunctionalState NewState);
uint16_t PVT_ReadData(void);
FlagStatus PVT_GetStatus(void);
void PVT_PrintReg(void);
                                   
#ifdef __cplusplus
}
#endif

#endif 

