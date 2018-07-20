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
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLK_FREQ;

static void SetSysClock(void);

/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
    SystemCoreClock = SYSTEM_CLK_FREQ;
}

static void ResetSysModules(void)
{
    /* Clock system manager reset */
    RCC_ClkManageReset();
    /* IO PAD reset */
    RCC_IOPADReset();

    /* Soft reset the peripheral modules */
    I2C_DeInit(I2C0);
    I2C_DeInit(I2C1);
    I2C_DeInit(I2C2);
    UART_DeInit(UART);
    GPIO_DeInit();
    SPI_DeInit(SPI0);
    SPI_DeInit(SPI1);
    //TIM_DeInit(TIM0);
    //TIM_DeInit(TIM1);
    //WDT_DeInit(WDT);

#if 0
    RCC_APBSYSPrintReg(I2C_SC);
    RCC_APBSYSPrintReg(UART_SC);
    RCC_APBSYSPrintReg(GPIO_SC);
    RCC_APBSYSPrintReg(SPI_SC);
    RCC_APBSYSPrintReg(TIM_SC);
    RCC_APBSYSPrintReg(WDT_SC);
    RCC_PLLPrintReg(APLL_CLK);
    RCC_PLLPrintReg(DPLL_CLK);
    RCC_SYSCLKPrintReg(FABRIC_CLK);
    RCC_SYSCLKPrintReg(IPCORE_CLK);
    RCC_SYSCLKPrintReg(DDR_CLK);
#endif
}

static void SetSysClock(void)
{
    PLL_InitTypeDef PLL_Init;
    LockStatus PLL_LockStatus = UnLock;
    __IO uint32_t StartUpCounter = 0;
    uint32_t DivValue = 0;

    /* Initialize APLL */
    PLL_StructInit(&PLL_Init);
    RCC_PLLConfig(APLL_CLK, &PLL_Init);
    do
    {
        PLL_LockStatus = RCC_PLLGetLockStatus(APLL_CLK);
        StartUpCounter++;
    } while((PLL_LockStatus == UnLock) && (StartUpCounter < PLL_LOCK_TIMEOUT));
    RCC_PLLCmd(APLL_CLK, ENABLE);

    /* Initialize DPLL */
    PLL_Init.PLLInputClock = XTAL;
    PLL_Init.PLLOutputClock = DPLL_CLK_FREQ;
    PLL_Init.Divr = PLL_DIVR;
    PLL_Init.Divf = PLL_DIVF;
    PLL_Init.Divq = PLL_DIVQ_2;
    RCC_PLLConfig(DPLL_CLK, &PLL_Init);
    StartUpCounter = 0;
    do
    {
        PLL_LockStatus = RCC_PLLGetLockStatus(DPLL_CLK);
        StartUpCounter++;  
    } while((PLL_LockStatus == UnLock) && (StartUpCounter < PLL_LOCK_TIMEOUT));
    RCC_PLLCmd(DPLL_CLK, ENABLE);

    /* Initialize Fabric Clock */
    RCC_SYSCLKSetSource(FABRIC_CLK, SYSCLK_SOURCE_APLL);
    DivValue = APLL_CLK_FREQ / SYSTEM_CLK_FREQ - 1;
    RCC_SYSCLKSetDiv(FABRIC_CLK, DivValue);
    RCC_SYSCLKCmd(FABRIC_CLK, ENABLE);

    /* Initialize IPCORE Clock */
    RCC_SYSCLKSetSource(IPCORE_CLK, SYSCLK_SOURCE_APLL);
    DivValue = APLL_CLK_FREQ / IPCORE_CLK_FREQ - 1;
    RCC_SYSCLKSetDiv(IPCORE_CLK, DivValue);
    RCC_SYSCLKCmd(IPCORE_CLK, ENABLE);

    /* Initialize DDR Clock */
    RCC_SYSCLKSetSource(DDR_CLK, SYSCLK_SOURCE_DPLL);
    DivValue = DPLL_CLK_FREQ / DDR_CLK_FREQ - 1;
    RCC_SYSCLKSetDiv(DDR_CLK, DivValue);
    RCC_SYSCLKCmd(DDR_CLK, ENABLE);
	
    /*!< GPIO Periph clock enable */
    RCC_APBPeriphResetCmd(GPIO_SC, 0, RESET);
    RCC_APBPeriphClockCmd(GPIO_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(GPIO_SC, ENABLE);
}

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void SystemInit (void)
{
    /* Disable all interrupt */
    __set_PRIMASK(1);
    
    /* Rest the System modules */
    ResetSysModules();

    /* Set System Clock */
    SetSysClock();

    /* Update Core Clock */
    SystemCoreClockUpdate();
        
    /* configuration systick*/
    SysTick_Configuration();
}

