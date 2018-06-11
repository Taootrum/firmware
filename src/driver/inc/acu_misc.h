/*******************************************************************************
  * @file    acu_misc.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Share Function. 
 ******************************************************************************/

#ifndef __ACU_MISC_H
#define __ACU_MISC_H

#include "acu.h"

/* ================================================================================ */
/* ================                 Exported_macro                 ================ */
/* ================================================================================ */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define COUNT_OF(a) (sizeof(a) / sizeof(*(a)))

extern uint32_t SysTickCount;

extern uint32_t ACU_ReadReg(uint32_t addr);
extern void ACU_WriteReg(uint32_t addr, uint32_t data);
extern void ACU_Delay(uint32_t num);
extern TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
extern void TIMER_ResetSysTick(void);
extern uint32_t TIMER_GetSysTick(void);

#endif
