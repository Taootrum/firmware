/*******************************************************************************
  * @file    acu_misc.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Share Function. 
 ******************************************************************************/
#include "acu_misc.h"

uint32_t SysTickCount = 0;

void TIMER_ResetSysTick(void)
{
    SysTickCount = 0;
}

uint32_t TIMER_GetSysTick(void)
{
    return SysTickCount;
}

/****************************************************************
  * 函数      : ACU_ReadReg()
  * 参数      : 
              addr: 需要读取的寄存器地址
  * 返回值     : 无
  * 描述      : 从系统指定寄存器地址读数据
 ***************************************************************/
uint32_t ACU_ReadReg(uint32_t addr)
{
    __IO uint32_t *pData = (__IO uint32_t *)addr;

    return *pData;
}

/****************************************************************
  * 函数      : ACU_WriteReg()
  * 参数      : 
              addr: 被写入的寄存器地址
              data: 寄存器被写入的值
  * 返回值     : None
  * 描述      : 向系统指定寄存器地址写数据
 ***************************************************************/
void ACU_WriteReg(uint32_t addr, uint32_t data)
{
    __IO uint32_t *pAddr = (__IO uint32_t *)addr;

    *pAddr = data;
}

/****************************************************************
  * 函数      : ACU_Delay()
  * 参数      : num: deley time
  * 返回值     : 无
  * 描述      : 系统延时函数.
 ***************************************************************/
void ACU_Delay(uint32_t num)
{
    uint32_t i = 0, j = 0;

    for (i = 0; i < num; i++)
        for (j = 0; j < 1000; j++);
}

/****************************************************************
  * 函数      : Buffercmp()
  * 参数      : pBuffer1: buffers to be compared
              pBuffer2:
              BufferLength: buffer's length
  * 返回值     : PASSED: pBuffer1 identical to pBuffer2
              FAILED: pBuffer1 differs from pBuffer2
  * 描述      : 系统延时函数.
 ***************************************************************/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

