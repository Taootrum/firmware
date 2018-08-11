/*******************************************************************************
  * @file    acu_iwdg.h
  * @author  DengLin SOC Team
  * @version V3.5.0
  * @date    26-March-2018
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_DDR_H
#define __ACU_DDR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"

#define DDR_CHIP_NUM    16
#define DDR_PAGE_SIZE   0x80
#define DDR_ROW_SIZE    (DDR_CHIP_NUM * DDR_PAGE_SIZE)

void DDR_WriteMem(uint8_t *buf, uint32_t addr, uint32_t size);
void DDR_ReadMem(uint8_t *buf, uint32_t addr, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif 

