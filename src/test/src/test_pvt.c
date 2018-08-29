/*******************************************************************************
  * @file    test_pvt.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    15-Augest-2018
  * @brief   ACU PVT Function. 
 ******************************************************************************/
#include "test_pvt.h"

/****************************************************************
  * 函数      : PVT_FunctionTestX()
  * 参数      : None
  * 返回值     : TRUE or FALSE
  * 描述      : pvt function test cases.
 ***************************************************************/
/* Temperature evaluation */
TestStatus PVT_FunctionTest1(void)
{
    uint16_t count = 0x1000;
    uint16_t Temperature = 0;
    PVT_InitTypeDef PVT_InitStruct;

    /* Init */
    RCC_APBPeriphResetCmd(PVT_SC, 0, RESET);
    RCC_APBPeriphClockCmd(PVT_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);
    PVT_InitStruct.PVT_MODE = 0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(&PVT_InitStruct);
    PVT_Cmd(ENABLE);

    while (PVT_GetStatus() == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Temperature evaluation fail.");
        return FAILED;
    }
    /* read Temperature */
    Temperature = PVT_ReadData();
    DEBUG_PRINT_REG(Temperature);

    PVT_DeInit();
    
    return PASSED;
}

/* Voltage evaluation */
TestStatus PVT_FunctionTest2(void)
{
    uint16_t count = 0x1000;
    uint16_t Voltage = 0;
    PVT_InitTypeDef PVT_InitStruct;

    /* Init */
    RCC_APBPeriphResetCmd(PVT_SC, 0, RESET);
    RCC_APBPeriphClockCmd(PVT_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);
    PVT_InitStruct.PVT_MODE = PVT_MODE_VSAMPLE;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(&PVT_InitStruct);
    PVT_Cmd(ENABLE);

    while (PVT_GetStatus() == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Voltage evaluation fail.");
        return FAILED;
    }

    Voltage = PVT_ReadData();
    DEBUG_PRINT_REG(Voltage);

    PVT_DeInit();
    
    return PASSED;
}

/* Process evaluation(LVT) */
TestStatus PVT_FunctionTest3(void)
{
    uint16_t count = 0x1000;
    uint16_t ProcessLVT = 0;
    PVT_InitTypeDef PVT_InitStruct;

    /* Init */
    RCC_APBPeriphResetCmd(PVT_SC, 0, RESET);
    RCC_APBPeriphClockCmd(PVT_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(&PVT_InitStruct);
    PVT_Cmd(ENABLE);

    while (PVT_GetStatus() == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(LVT) fail.");
        return FAILED;
    }

    ProcessLVT = PVT_ReadData();
    DEBUG_PRINT_REG(ProcessLVT);
    
    PVT_DeInit();

    return PASSED;
}

/* Process evaluation(HVT) */
TestStatus PVT_FunctionTest4(void)
{
    uint16_t count = 0x1000;
    uint16_t ProcessHVT = 0;
    PVT_InitTypeDef PVT_InitStruct;

    /* Init */
    RCC_APBPeriphResetCmd(PVT_SC, 0, RESET);
    RCC_APBPeriphClockCmd(PVT_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE1;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(&PVT_InitStruct);
    PVT_Cmd(ENABLE);

    while (PVT_GetStatus() == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(HVT) fail.");
        return FAILED;
    }

    ProcessHVT = PVT_ReadData();
    DEBUG_PRINT_REG(ProcessHVT);
    
    PVT_DeInit();

    return PASSED;
}

/* Process evaluation(SVT) */
TestStatus PVT_FunctionTest5(void)
{
    uint16_t count = 0x1000;
    uint16_t ProcessSVT = 0;
    PVT_InitTypeDef PVT_InitStruct;

    /* Init */
    RCC_APBPeriphResetCmd(PVT_SC, 0, RESET);
    RCC_APBPeriphClockCmd(PVT_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE1 | PVT_MODE_PSAMPLE0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(&PVT_InitStruct);
    PVT_Cmd(ENABLE);

    while (PVT_GetStatus() == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(SVT) fail.");
        return FAILED;
    }

    ProcessSVT = PVT_ReadData();
    DEBUG_PRINT_REG(ProcessSVT);
    
    PVT_DeInit();

    return PASSED;
}

uint16_t Temperature = 0;
/* Interrupt */
TestStatus PVT_FunctionTest6(void)
{
    uint16_t count = 0x1000;
    PVT_InitTypeDef PVT_InitStruct;

    /* Init */
    RCC_APBPeriphResetCmd(PVT_SC, 0, RESET);
    RCC_APBPeriphClockCmd(PVT_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);
    PVT_InitStruct.PVT_MODE = 0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(&PVT_InitStruct);

    /* Enable Interrupt */
    PVT_ITConfig(ENABLE);
	NVIC_EnableIRQ(PVT_IRQn);

    /* Enable PVT */
    PVT_Cmd(ENABLE);
    
    while (Temperature == 0 && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Temperature evaluation interrupt fail.");
        return FAILED;
    }
    DEBUG_PRINT_REG(Temperature);

    /* recover to default */
    PVT_DeInit();
    PVT_ITConfig(DISABLE);
	NVIC_DisableIRQ(PVT_IRQn);
    
    return PASSED;
}

