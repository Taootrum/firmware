/*******************************************************************************
  * @file    acu_misc.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Share Function. 
 ******************************************************************************/

#ifndef __ACU_MISC_H
#define __ACU_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"

/* ================================================================================ */
/* ================                 Exported_macro                 ================ */
/* ================================================================================ */
#define SET_BIT(REG, BIT)       ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)      ((REG) & (BIT))
#define CLEAR_REG(REG)          ((REG) = (0x0))
#define WRITE_REG(REG, VAL)     ((REG) = (VAL))
#define READ_REG(REG)           ((REG))
#define WRITE32(ADDR, VAL)      (*(__IO uint32_t *)(ADDR) = (VAL))
#define READ32(ADDR)            (*(__IO uint32_t *)(ADDR))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define COUNT_OF(a) (sizeof(a) / sizeof(*(a)))
#define CHECK_REG_RESERVED(REG, VAL) ((REG) == (VAL) ? TRUE : FALSE)
extern uint32_t SysTickCount;

extern void ACU_Delay(uint32_t num);
extern TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
extern void TIMER_ResetSysTick(void);
extern uint32_t TIMER_GetSysTick(void);

#ifdef __cplusplus
}
#endif

#endif

