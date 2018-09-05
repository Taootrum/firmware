/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_wdt.h"

/* WDT timer running */
TestStatus WDT_FunctionTest1(void)
{
    WDT_InitTypeDef WDT_InitStructure;
    uint32_t LastValue = 0, CurValue = 0;
    
    WDT_DeInit();
    WDT_StructInit(&WDT_InitStructure);
    WDT_Init(&WDT_InitStructure);
    WDT_Cmd(ENABLE);
    
    LastValue = WDT_GetCounter();
    CurValue = WDT_GetCounter();
    if (LastValue == CurValue)
    {
        DEBUG_ERROR("WDT timer running fail.");
        return FAILED;
    }
    WDT_DeInit();
    
    return PASSED;
}

/* WDT Pause */
TestStatus WDT_FunctionTest2(void)
{
    WDT_InitTypeDef WDT_InitStructure;
    uint32_t LastValue = 0, CurValue = 0;
    
    WDT_DeInit();
    WDT_StructInit(&WDT_InitStructure);
    WDT_Init(&WDT_InitStructure);
    WDT_Cmd(ENABLE);
    
    LastValue = WDT_GetCounter();
    CurValue = WDT_GetCounter();
    if (LastValue != CurValue)
    {
        WDT_Pause(ENABLE);
        LastValue = WDT_GetCounter();
        CurValue = WDT_GetCounter();
        if (LastValue != CurValue) 
        {
            DEBUG_ERROR("WDT Pause fail.");
            WDT_Pause(DISABLE);
            return FAILED;
        }
    }
    WDT_Pause(DISABLE);
    WDT_DeInit();
    
    return PASSED;
}

/* wdt interrupt */
TestStatus WDT_FunctionTest3(void)
{
    WDT_InitTypeDef WDT_InitStructure;
    uint32_t count = 0x1000;
    
    WDT_DeInit();
    WDT_InitStructure.WDT_Mode = WDT_TIMEOUT_RESET;
    WDT_InitStructure.WDT_Top = WDT_TOP;
    WDT_Init(&WDT_InitStructure);
    WDT_Cmd(ENABLE);

    /* Debug mode */
    WDT_DebugCmd(ENABLE);
    WDT_Restart();
    
    while (WDT_GetITStatus() == 0 && --count > 0);
    WDT_DeInit();
    if (count == 0)
    {
        DEBUG_ERROR("wdt interrupt fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* wdt restart */
TestStatus WDT_FunctionTest4(void)
{
    WDT_InitTypeDef WDT_InitStructure;
    uint32_t count = 0x1000;
    
    WDT_DeInit();
    WDT_InitStructure.WDT_Mode = WDT_TIMEOUT_RESET;
    WDT_InitStructure.WDT_Top = WDT_TOP;
    WDT_Init(&WDT_InitStructure);
    WDT_Cmd(ENABLE);

    /* Debug mode */
    WDT_DebugCmd(ENABLE);
    WDT_Restart();
    while (WDT_GetITStatus() == 0 && --count > 0);
    
    WDT_DebugCmd(DISABLE);
    WDT_Restart();
    if (WDT_GetITStatus() != 0 || WDT_GetCounter() <= 255)
    {
        DEBUG_ERROR("wdt restart fail.");
        WDT_DeInit();
        return FAILED;
    }
    WDT_DeInit();
    
    return PASSED;
}

/* wdt clear interrupt */
TestStatus WDT_FunctionTest5(void)
{
    WDT_InitTypeDef WDT_InitStructure;
    uint32_t count = 0x1000;
    
    WDT_DeInit();
    WDT_InitStructure.WDT_Mode = WDT_TIMEOUT_RESET;
    WDT_InitStructure.WDT_Top = WDT_TOP;
    WDT_Init(&WDT_InitStructure);
    WDT_Cmd(ENABLE);

    /* Debug mode */
    WDT_DebugCmd(ENABLE);
    WDT_Restart();
    while (WDT_GetITStatus() == 0 && --count > 0);
    WDT_ClearIT();
    if (WDT_GetITStatus() != 0)
    {
        DEBUG_ERROR("wdt clear interrupt fail.");
        WDT_DeInit();
        return FAILED;
    }
    WDT_DeInit();
    
    return PASSED;
}

