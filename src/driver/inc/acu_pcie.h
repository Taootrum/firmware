/*******************************************************************************
  * @file    acu_iwdg.h
  * @author  DengLin SOC Team
  * @version V3.5.0
  * @date    26-March-2018
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_PCIE_H
#define __ACU_PCIE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"

void PCIE_DeInit(void);
void PCIE_Init(void);
void PCIE_PrintReg(void);

#ifdef __cplusplus
}
#endif

#endif 

