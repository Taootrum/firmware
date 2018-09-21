/*******************************************************************************
  * @file    timer.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Flash Application Function. 
 ******************************************************************************/
#include "timer.h"

void SysTick_Init(void)
{
    /* Setup SysTick Timer for 1 msec interrupts */
    SysTick_Config((SystemCoreClock) / 1000);
}

