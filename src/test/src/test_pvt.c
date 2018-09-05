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
    uint16_t Temperature0 = 0, Temperature1 = 0;
    PVT_InitTypeDef PVT_InitStruct;
    TestStatus ret = PASSED;

    /* PVT0 Temperature */
    PVT_InitStruct.PVT_MODE = 0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT0, &PVT_InitStruct);
    PVT_Cmd(PVT0, ENABLE);

    while (PVT_GetStatus(PVT0) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("PVT0 Temperature evaluation fail.");
        ret = FAILED;
    }
    Temperature0 = PVT_ReadData(PVT0);
    DEBUG_PRINT_REG(Temperature0);
    PVT_DeInit(PVT0);
    
    /* PVT1 Temperature */
    PVT_InitStruct.PVT_MODE = 0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT1, &PVT_InitStruct);
    PVT_Cmd(PVT1, ENABLE);

    count = 0x1000;
    while (PVT_GetStatus(PVT1) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("PVT1 Temperature evaluation fail.");
        ret = FAILED;
    }
    Temperature1 = PVT_ReadData(PVT1);
    DEBUG_PRINT_REG(Temperature1);
    PVT_DeInit(PVT1);
    
    return ret;
}

/* Voltage evaluation */
TestStatus PVT_FunctionTest2(void)
{
    uint16_t count = 0x1000;
    uint16_t Voltage0 = 0, Voltage1 = 0;
    PVT_InitTypeDef PVT_InitStruct;
    TestStatus ret = PASSED;

    /* PVT0 Voltage */
    PVT_InitStruct.PVT_MODE = PVT_MODE_VSAMPLE;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT0, &PVT_InitStruct);
    PVT_Cmd(PVT0, ENABLE);

    while (PVT_GetStatus(PVT0) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("PVT0 Voltage evaluation fail.");
        ret = FAILED;
    }
    Voltage0 = PVT_ReadData(PVT0);
    DEBUG_PRINT_REG(Voltage0);
    PVT_DeInit(PVT0);

    /* PVT1 Voltage */
    PVT_InitStruct.PVT_MODE = PVT_MODE_VSAMPLE;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT1, &PVT_InitStruct);
    PVT_Cmd(PVT1, ENABLE);

    count = 0x1000;
    while (PVT_GetStatus(PVT1) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("PVT1 Voltage evaluation fail.");
        ret = FAILED;
    }
    Voltage1 = PVT_ReadData(PVT1);
    DEBUG_PRINT_REG(Voltage1);
    PVT_DeInit(PVT1);
    
    return ret;
}

/* Process evaluation(LVT) */
TestStatus PVT_FunctionTest3(void)
{
    uint16_t count = 0x1000;
    uint16_t ProcessLVT0 = 0,ProcessLVT1 = 0;
    PVT_InitTypeDef PVT_InitStruct;
    TestStatus ret = PASSED;

    /* PVT0 ProcessLVT */
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT0, &PVT_InitStruct);
    PVT_Cmd(PVT0, ENABLE);

    while (PVT_GetStatus(PVT0) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(LVT0) fail.");
        ret = FAILED;
    }
    ProcessLVT0 = PVT_ReadData(PVT0);
    DEBUG_PRINT_REG(ProcessLVT0);
    PVT_DeInit(PVT0);

    /* PVT0 ProcessLVT */
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT1, &PVT_InitStruct);
    PVT_Cmd(PVT1, ENABLE);

    count = 0x1000;
    while (PVT_GetStatus(PVT1) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(LVT1) fail.");
        ret = FAILED;
    }
    ProcessLVT1 = PVT_ReadData(PVT1);
    DEBUG_PRINT_REG(ProcessLVT1);
    PVT_DeInit(PVT1);

    return ret;
}

/* Process evaluation(HVT) */
TestStatus PVT_FunctionTest4(void)
{
    uint16_t count = 0x1000;
    uint16_t ProcessHVT0 = 0, ProcessHVT1 = 0;
    PVT_InitTypeDef PVT_InitStruct;
    TestStatus ret = PASSED;

    /* PVT0 ProcessHVT */
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE1;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT0, &PVT_InitStruct);
    PVT_Cmd(PVT0, ENABLE);

    while (PVT_GetStatus(PVT0) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(HVT0) fail.");
        ret = FAILED;
    }
    ProcessHVT0 = PVT_ReadData(PVT0);
    DEBUG_PRINT_REG(ProcessHVT0);
    PVT_DeInit(PVT0);
    
    /* PVT1 ProcessHVT */
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE1;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT1, &PVT_InitStruct);
    PVT_Cmd(PVT1, ENABLE);

    count = 0x1000;
    while (PVT_GetStatus(PVT1) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(HVT1) fail.");
        ret = FAILED;
    }
    ProcessHVT1 = PVT_ReadData(PVT1);
    DEBUG_PRINT_REG(ProcessHVT1);
    PVT_DeInit(PVT1);

    return ret;
}

/* Process evaluation(SVT) */
TestStatus PVT_FunctionTest5(void)
{
    uint16_t count = 0x1000;
    uint16_t ProcessSVT0 = 0, ProcessSVT1 = 0;
    PVT_InitTypeDef PVT_InitStruct;
    TestStatus ret = PASSED;

    /* PVT0 ProcessSVT */
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE1 | PVT_MODE_PSAMPLE0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT0, &PVT_InitStruct);
    PVT_Cmd(PVT0, ENABLE);

    while (PVT_GetStatus(PVT0) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(SVT0) fail.");
        ret = FAILED;
    }
    ProcessSVT0 = PVT_ReadData(PVT0);
    DEBUG_PRINT_REG(ProcessSVT0);
    PVT_DeInit(PVT0);

    /* PVT1 ProcessSVT */
    PVT_InitStruct.PVT_MODE = PVT_MODE_PSAMPLE1 | PVT_MODE_PSAMPLE0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT1, &PVT_InitStruct);
    PVT_Cmd(PVT1, ENABLE);

    count = 0x1000;
    while (PVT_GetStatus(PVT1) == RESET && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("Process evaluation(SVT1) fail.");
        ret = FAILED;
    }
    ProcessSVT1 = PVT_ReadData(PVT1);
    DEBUG_PRINT_REG(ProcessSVT1);
    PVT_DeInit(PVT1);

    return ret;
}

uint16_t Temperature = 0;
/* Interrupt */
TestStatus PVT_FunctionTest6(void)
{
    uint16_t count = 0x1000;
    uint16_t Temperature0 = 0, Temperature1 = 0;
    PVT_InitTypeDef PVT_InitStruct;
    TestStatus ret = PASSED;

    /* PVT0 Interrupt */
    PVT_InitStruct.PVT_MODE = 0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT0, &PVT_InitStruct);
    /* Enable Interrupt */
    PVT_ITConfig(PVT0_INT, ENABLE);
	NVIC_EnableIRQ(PVT_IRQn);
    /* Enable PVT */
    PVT_Cmd(PVT0, ENABLE);
    
    while (Temperature == 0 && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("PVT0 Temperature evaluation interrupt fail.");
        ret = FAILED;
    }
    Temperature0 = Temperature;
    DEBUG_PRINT_REG(Temperature0);
    /* recover to default */
    PVT_DeInit(PVT0);
    PVT_ITConfig(PVT0_INT, DISABLE);
	NVIC_DisableIRQ(PVT_IRQn);

    /* PVT1 Interrupt */
    PVT_InitStruct.PVT_MODE = 0;
    PVT_InitStruct.PVT_TIMG = PVT_TRIM;
    PVT_Init(PVT1, &PVT_InitStruct);
    /* Enable Interrupt */
    PVT_ITConfig(PVT1_INT, ENABLE);
	NVIC_EnableIRQ(PVT_IRQn);
    /* Enable PVT */
    PVT_Cmd(PVT1, ENABLE);
    
    while (Temperature == 0 && --count > 0);
    if (count == 0)
    {
        DEBUG_ERROR("PVT1 Temperature evaluation interrupt fail.");
        ret = FAILED;
    }
    Temperature1 = Temperature;
    DEBUG_PRINT_REG(Temperature1);
    /* recover to default */
    PVT_DeInit(PVT1);
    PVT_ITConfig(PVT1_INT, DISABLE);
	NVIC_DisableIRQ(PVT_IRQn);

    return ret;
}

