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
    while (num--);
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

void printf_memory(uint8_t *mem, uint16_t len)
{
    uint8_t i = 0, j = 0;
    uint8_t uMod = len / PRINT_MEM_SIZE, uOft = len % PRINT_MEM_SIZE;
    uint8_t uPrint = 0;
    uint32_t addr = (uint32_t)mem;
    
    for (i = 0; i < uMod + 1; i++)
    {
        uPrint = (i == uMod) ? uOft : PRINT_MEM_SIZE;
        if (uPrint == 0)
        {
            return;
        }

        DEBUG_MSG("%08x:", addr);
        for (j = 0; j < uPrint; j++)
        {
            DEBUG_MSG("%02x", *(mem + PRINT_MEM_SIZE * i + j));
            if ((j + 1) % 4 == 0)
            {
                DEBUG_MSG(" ");
            }
        }
        addr += PRINT_MEM_SIZE;
        DEBUG_MSG(LF);
    }
}

