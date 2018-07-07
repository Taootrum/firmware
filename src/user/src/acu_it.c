/**************************************************************************//**
 * @file     system_ACU.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM3 Device Series
 * @version  V5.00
 * @date     07. September 2016
 ******************************************************************************/
#include "acu_it.h"

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    SysTickCount++;
}

void IIC0_IRQHandler(void)
{

}
void IIC1_IRQHandler(void)
{

}
void IIC2_IRQHandler(void)
{

}
void INT_IRQHandler(void)
{

}
void GPIO_IRQHandler(void)
{

}
void UART_IRQHandler(void)
{

}
void SSP0_IRQHandler(void)
{

}
void SSP1_IRQHandler(void)
{

}
void TMR0_IRQHandler(void)
{

}
void TMR1_IRQHandler(void)
{

}
void WDT_IRQHandler(void)
{

}
void PVT_IRQHandler(void)
{

}
void DDR0_IRQHandler(void)
{

}
void DDR1_IRQHandler(void)
{

}
void DDR2_IRQHandler(void)
{

}
void CU_IRQHandler(void)
{

}

