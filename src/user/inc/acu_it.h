/**************************************************************************//**
 * @file     system_ACU.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM3 Device Series
 * @version  V5.00
 * @date     07. September 2016
 ******************************************************************************/
#ifndef __ACU_IT_H
#define __ACU_IT_H

#include "acu.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/* ACU */
void IIC0_IRQHandler(void);
void IIC1_IRQHandler(void);
void IIC2_IRQHandler(void);
void INT_IRQHandler(void);
void GPIO_IRQHandler(void);
void UART_IRQHandler(void);
void SSP0_IRQHandler(void);
void SSP1_IRQHandler(void);
void TMR0_IRQHandler(void);
void TMR1_IRQHandler(void);
void WDT_IRQHandler(void);
void PVT_IRQHandler(void);
void DDR0_IRQHandler(void);
void DDR1_IRQHandler(void);
void DDR2_IRQHandler(void);
void CU_IRQHandler(void);

#endif

