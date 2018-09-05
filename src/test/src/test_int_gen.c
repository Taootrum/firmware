/*******************************************************************************
  * @file    test_int_gen.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    30-Augest-2018
  * @brief   ACU INT Generate Function. 
 ******************************************************************************/
#include "test_int_gen.h"

#ifdef ACU_TEST
uint8_t INT_TestInterruptFlag = RESET;
#endif

/* INT generate from PCIE */
TestStatus INT_FunctionTest1(void)
{
    uint32_t count = 0x1000;
    
    INT_Init();
    NVIC_EnableIRQ(INT_IRQn);

    INT_TestInterruptFlag = RESET;
    INT_Generate(TYPE_INT_PASSIVE);
    while ((INT_TestInterruptFlag == RESET) && (--count > 0));
    
    if (INT_TestInterruptFlag == RESET)
    {
        DEBUG_ERROR("INT generate from PCIE fail.");
        return FAILED;
    }
    INT_DeInit();
    NVIC_DisableIRQ(INT_IRQn);
    
    return PASSED;
}

/* INT generate from passive */
TestStatus INT_FunctionTest2(void)
{
    uint32_t count = 0x1000;
    
    INT_Init();
    NVIC_EnableIRQ(INT_IRQn);
    
    INT_TestInterruptFlag = RESET;
    INT_Generate(TYPE_INT_PCIE);
    while ((INT_TestInterruptFlag == RESET) && (--count > 0));
    
    if (INT_TestInterruptFlag == RESET)
    {
        DEBUG_ERROR("INT generate from passive fail.");
        return FAILED;
    }
    INT_DeInit();
    NVIC_DisableIRQ(INT_IRQn);
    
    return PASSED;
}

