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
#if 0
    /* Soft reset the modules system manager */
    RCC_PCIEReset();
    RCC_IPCoreReset();
    RCC_ClkManageReset();
    //RCC_FabricBusReset();
    RCC_DDRReset();

    /* IO PAD reset */
    IOPAD_SC->FCR0 = 0x0;
    IOPAD_SC->FCR1 = 0x80;
    IOPAD_SC->FCR2 = 0xff;
    IOPAD_SC->FCR3 = 0;
#endif

    /* Soft reset the peripheral modules */
    I2C_DeInit(I2C0);
    I2C_DeInit(I2C1);
    UART_DeInit(UART);
    GPIO_DeInit();
    SPI_DeInit(SPI0);
    SPI_DeInit(SPI1);
    //TIM_DeInit(TIM0);
    //TIM_DeInit(TIM1);
    //WDT_DeInit(WDT);
}

static void SetSysClock(void)
{
    /* Fabric bus */
    RCC_SYSCLKSetSource(FABRIC_CLK, SYSCLK_SOURCE_APLL);
    RCC_SYSCLKSetDiv(FABRIC_CLK, SYSCLK_DIV_MIX);
    RCC_SYSCLKCmd(FABRIC_CLK, ENABLE);
      
    /* PCIE bus */
    RCC_SYSCLKSetSource(PCIE_CLK, SYSCLK_SOURCE_APLL);
    RCC_SYSCLKSetDiv(PCIE_CLK, SYSCLK_DIV_MIX);
    RCC_SYSCLKCmd(PCIE_CLK, ENABLE);

    /* IPCORE bus */
    RCC_SYSCLKSetSource(IPCORE_CLK, SYSCLK_SOURCE_APLL);
    RCC_SYSCLKSetDiv(IPCORE_CLK, SYSCLK_DIV_MIX);
    RCC_SYSCLKCmd(IPCORE_CLK, ENABLE);
    
    /* DDR bus */
    RCC_SYSCLKSetSource(DDR_CLK, SYSCLK_SOURCE_APLL);
    RCC_SYSCLKSetDiv(DDR_CLK, SYSCLK_DIV_MIX);
    RCC_SYSCLKCmd(DDR_CLK, ENABLE);
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

    /* Rest the System modules */
    ResetSysModules();
    
    /* Configure the System clock frequency */
    SetSysClock();
}

