/**************************************************************************//**
 * @file     system_ACU.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU WDG Module Function. 
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "acu.h"
#include "timer.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL            (24000000UL)      /* Oscillator frequency */
#define SYSTEM_CLOCK    (1U * XTAL)

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;

/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
    SystemCoreClock = SYSTEM_CLOCK;
}

static void ResetSysModules(void)
{
    /* Soft reset the modules system manager */
    RST_SC->PCIE_RST = (uint32_t)0x0;
    RST_SC->PCIE_RST = (uint32_t)0x1;

    RST_SC->IPCORE_RST = (uint32_t)0x0;
    RST_SC->IPCORE_RST = (uint32_t)0x01;
   
    RST_SC->CLKM_RST = (uint32_t)0x0;
    RST_SC->CLKM_RST = (uint32_t)0x1;

    RST_SC->BUS_RST = (uint32_t)0x0;
    RST_SC->BUS_RST = (uint32_t)0x1;

    RST_SC->DDR_RST = (uint32_t)0x0;
    RST_SC->DDR_RST = (uint32_t)0x1;
    RST_SC->DDR_RCFG = (uint32_t)0x0;
    RST_SC->DDR_WCFG = (uint32_t)0x0;

#if 0
    /* IO PAD reset */
    IOPAD_SC->FCR0 = 0x0;
    IOPAD_SC->FCR1 = 0x80;
    IOPAD_SC->FCR2 = 0xff;
    IOPAD_SC->FCR3 = 0;
#endif

    /* Soft reset the peripheral modules */
    I2C_SC->SR  = (uint32_t)0x1;
    UART_SC->SR = (uint32_t)0x1;
    GPIO_SC->SR = (uint32_t)0x1;
    SPI_SC->SR  = (uint32_t)0x1;
    TIM_SC->SR  = (uint32_t)0x1;
    WDT_SC->SR  = (uint32_t)0x1;
}

static void SetSysClock(void)
{
    /* HCLK = SYSCLK */
    FABRIC_SC->CLKRATIO = (uint32_t)0x1;
      
    /* PCLK2 = HCLK */
    PCIE_SC->CLKRATIO   = (uint32_t)0x1;

    /* HCLK = SYSCLK */
    IPCORE_SC->CLKRATIO = (uint32_t)0x1;
    
    /* HCLK = SYSCLK */
    DDR_SC->CLKRATIO    = (uint32_t)0x1;
}

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void SystemInit (void)
{
    /* Disable all interrupt */
    __set_PRIMASK(1);

    SystemCoreClock = SYSTEM_CLOCK;

    /* configuration systick*/
    SysTick_Configuration();

#if 0
    /* Rest the System modules */
    ResetSysModules();
    
    /* Configure the System clock frequency */
    SetSysClock();
#endif
}

