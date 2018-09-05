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

#ifdef ACU_TEST
extern uint8_t INT_TestInterruptFlag;
#endif
void INT_IRQHandler(void)
{
    INT_ClearIT();
    INT_TestInterruptFlag = SET;
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

extern uint16_t Temperature;
void PVT_IRQHandler(void)
{
    if (PVT_GetIntStat() == PVT0_INT) {
        Temperature = PVT_ReadData(PVT0);
        PVT_Cmd(PVT0, DISABLE);
    } else if (PVT_GetIntStat() == PVT1_INT) {
        Temperature = PVT_ReadData(PVT1);
        PVT_Cmd(PVT1, DISABLE);
    } else {
        Temperature = 0xFFFF;
    }
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

extern uint32_t RxData[0x200 / 4];
void CU_IRQHandler(void)
{
    WRITE_REG(CU->CQ_IRQ_CLEAR, 0x1F);
    DDR_InterleaveReadMem((uint8_t *)RxData, 0x20000000, 0x200);
    DEBUG_MSG("Running......"LF);
}

