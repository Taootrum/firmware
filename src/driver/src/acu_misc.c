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

