/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_timer.h"

/* free time running */
TestStatus TIMER_FunctionTest1(void)
{
    TIM_InitTypeDef TIM_InitStructure;
    uint32_t LastValue = 0, CurValue = 0;
    
    TIM_DeInit();
    TIM_InitStructure.TIM_Mode = FREE_RUNNING;
    TIM_Init(TIM0, &TIM_InitStructure);
    TIM_Cmd(TIM0, ENABLE);
    
    LastValue = TIM_GetCounter(TIM0);
    CurValue = TIM_GetCounter(TIM0);
    if (LastValue == CurValue)
    {
        DEBUG_ERROR("TIM free running fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* user-defined running */
TestStatus TIMER_FunctionTest2(void)
{
    TIM_InitTypeDef TIM_InitStructure;
    uint32_t LastValue = 0, CurValue = 0;
    
    TIM_DeInit();
    TIM_InitStructure.TIM_Mode = USER_DEFINED;
    TIM_InitStructure.TIM_TimingTime = 100;     /* 100ms */
    TIM_Init(TIM0, &TIM_InitStructure);
    TIM_Cmd(TIM0, ENABLE);
    
    LastValue = TIM_GetCounter(TIM0);
    CurValue = TIM_GetCounter(TIM0);
    if (LastValue == CurValue)
    {
        DEBUG_ERROR("TIM user-defined running fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* user-defined interrupt */
TestStatus TIMER_FunctionTest3(void)
{
    TIM_InitTypeDef TIM_InitStructure;
    uint32_t count = 0x20000;
    
    TIM_DeInit();
    TIM_InitStructure.TIM_Mode = USER_DEFINED;
    TIM_InitStructure.TIM_TimingTime = 1;     /* 100ms */
    TIM_Init(TIM0, &TIM_InitStructure);
    TIM_ITConfig(TIM0, ENABLE);
    TIM_Cmd(TIM0, ENABLE);
    
    while (TIM_GetITStatus(TIM0) == 0 && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("TIM user-defined interrupt fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* clear interrupt status */
TestStatus TIMER_FunctionTest4(void)
{
    TIM_InitTypeDef TIM_InitStructure;
    uint32_t count = 0x20000;
    
    TIM_DeInit();
    TIM_InitStructure.TIM_Mode = USER_DEFINED;
    TIM_InitStructure.TIM_TimingTime = 1;     /* 100ms */
    TIM_Init(TIM0, &TIM_InitStructure);
    TIM_ITConfig(TIM0, ENABLE);
    TIM_Cmd(TIM0, ENABLE);
    
    while (TIM_GetITStatus(TIM0) == 0 && --count > 0);
    TIM_ClearIT(TIM0);
    if (TIM_GetITStatus(TIM0) != 0)
    {
        DEBUG_ERROR("TIM clear interrupt status fail.");
        return FAILED;
    }
    
    return PASSED;
}

