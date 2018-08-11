/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_gpio.h"

/****************************************************************
  * 函数      : GPIO_InterfacesTestx()
  * 参数      : None
  * 返回值     : TRUE or FALSE
  * 描述      : GPIO interfaces test cases.
 ***************************************************************/
/* GPIO_DeInit() */
TestStatus GPIO_InterfaceTest1(void)
{
    GPIO_TypeDef *GPIO_X[15] = {GPIO_0, GPIO_1, GPIO_2, GPIO_3, GPIO_4, GPIO_5, GPIO_6, GPIO_7, 
                                GPIO_8, GPIO_9, GPIO_10, GPIO_11, GPIO_12, GPIO_13, GPIO_14};
    BoolStatus result = TRUE;
    uint8_t i = 0;

    GPIO_DeInit();
    for (i = 0; i < 15; i++)
    {
        result &= CHECK_REG_RESERVED(GPIO_X[i]->OR, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->DR, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->PUDE, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->GIMR, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->GPIMR, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->PIR, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->ITR, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->IFR, 0x00);
        result &= CHECK_REG_RESERVED(GPIO_X[i]->ICR, 0x00);
    }
    result &= CHECK_REG_RESERVED(GPIO_IR->GP0IR, 0x00);
    result &= CHECK_REG_RESERVED(GPIO_IR->GP1IR, 0x00);
    result &= CHECK_REG_RESERVED(GPIO_IR->GP2IR, 0x00);
    
    if (result != TRUE)
    {
        DEBUG_ERROR("GPIO_DeInit fail.");
        return FAILED;
    }

    /* 使能GPIO */
    RCC_APBPeriphResetCmd(GPIO_SC, 0, RESET);
    RCC_APBPeriphClockCmd(GPIO_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(GPIO_SC, ENABLE);
    
    return PASSED;
}

/* GPIO_Init() */
TestStatus GPIO_InterfaceTest2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    BoolStatus result = TRUE;
    
    /* reset */
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_Init(GPIO_0, &GPIO_InitStructure);
    result &= CHECK_REG_RESERVED(GPIO_0->IR, 0x00);
    result &= CHECK_REG_RESERVED(GPIO_0->OR, 0x00);
    result &= CHECK_REG_RESERVED(GPIO_0->DR, 0x00);
    result &= CHECK_REG_RESERVED(GPIO_0->PUDE, 0x01);
    result &= CHECK_REG_RESERVED(GPIO_0->GIMR, 0x01);
    result &= CHECK_REG_RESERVED(GPIO_0->GPIMR, 0x01);
    result &= CHECK_REG_RESERVED(GPIO_0->PIR, 0x01);
    result &= CHECK_REG_RESERVED(GPIO_0->ITR, 0x00);
    result &= CHECK_REG_RESERVED(GPIO_0->IFR, 0x00);
    result &= CHECK_REG_RESERVED(GPIO_0->ICR, 0x00);

    if (result != TRUE)
    {
        DEBUG_ERROR("GPIO_Init fail.");
        return FAILED;
    }
    
    /* read reserved */
    RCC_APBPeriphResetCmd(GPIO_SC, 0, SET);
    RCC_APBPeriphResetCmd(GPIO_SC, 0, RESET);
    
    return PASSED;
}

/* GPIO_IOPADMode() */
TestStatus GPIO_InterfaceTest3(void)
{
    TestStatus ret = PASSED;

    while (UART->FR & UART_FLAG_BUSY);
    
    /* reset */
    GPIO_IOPADMode(GPIO0, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO1, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO2, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO3, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO4, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO5, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO6, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO7, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO8, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO9, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO10, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO11, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO12, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO13, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO14, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO15, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO16, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO17, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO18, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO19, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO20, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO21, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO22, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO23, GPIO_IOPAD_GPIO);
    GPIO_IOPADMode(GPIO24, GPIO_IOPAD_GPIO);

    GPIO_IOPADMode(GPIO25, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO26, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO27, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO28, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO29, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO30, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO31, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO32, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO33, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO34, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO35, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO36, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO37, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO38, GPIO_IOPAD_FUNC);
    GPIO_IOPADMode(GPIO39, GPIO_IOPAD_FUNC);

    if ((0xff != READ_REG(IOPAD_MUX->FCR0))
        || (0xff != READ_REG(IOPAD_MUX->FCR1))
        || (0xff != READ_REG(IOPAD_MUX->FCR2))
        || (0x01 != READ_REG(IOPAD_MUX->FCR3))
        || (0x00 != READ_REG(IOPAD_MUX->FCR4)))
    {
        DEBUG_ERROR("SPI_DeInit fail.");
        ret = FAILED;
    }
    
    RCC_IOPADReset();
    
    return ret;
}

/* GPIO_ReadInputData()
   GPIO_SetOutput()
   */
TestStatus GPIO_InterfaceTest4(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TestStatus ret = PASSED;  
    
    /* init */
    GPIO_InitStructure.GPIO_Direction = GPIO_OUTPUT;
    GPIO_InitStructure.GPIO_PullStatus = GPIO_PULLUP;
    GPIO_Init(GPIO_4, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Direction = GPIO_INPUT;
    GPIO_InitStructure.GPIO_PullStatus = GPIO_PULLUP;
    GPIO_Init(GPIO_5, &GPIO_InitStructure);
    
    /* reset */
    GPIO_SetOutput(GPIO_4, GPIO_SET);
    if (GPIO_ReadInputData(GPIO_5) != GPIO_SET)
    {
        DEBUG_ERROR("GPIO_ReadOutputData fail.");
        ret = FAILED;
    }
    
    /* read reserved */
    RCC_APBPeriphResetCmd(GPIO_SC, 0, SET);
    RCC_APBPeriphResetCmd(GPIO_SC, 0, RESET);
    
    return ret;
}

/* GPIO_ReadOutputData()
   GPIO_SetOutput()
   */
TestStatus GPIO_InterfaceTest5(void)
{
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;
    
    /* reset */
    GPIO_SetOutput(GPIO_0, GPIO_SET);
    GPIO_SetOutput(GPIO_1, GPIO_SET);
    GPIO_SetOutput(GPIO_2, GPIO_SET);
    GPIO_SetOutput(GPIO_3, GPIO_SET);
    GPIO_SetOutput(GPIO_4, GPIO_SET);
    GPIO_SetOutput(GPIO_5, GPIO_SET);
    GPIO_SetOutput(GPIO_6, GPIO_SET);
    GPIO_SetOutput(GPIO_7, GPIO_SET);
    GPIO_SetOutput(GPIO_8, GPIO_SET);
    GPIO_SetOutput(GPIO_9, GPIO_SET);
    GPIO_SetOutput(GPIO_10, GPIO_SET);
    GPIO_SetOutput(GPIO_11, GPIO_SET);
    GPIO_SetOutput(GPIO_12, GPIO_SET);
    GPIO_SetOutput(GPIO_13, GPIO_SET);
    GPIO_SetOutput(GPIO_14, GPIO_SET);

    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_0), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_1), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_2), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_3), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_4), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_5), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_6), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_7), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_8), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_9), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_10), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_11), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_12), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_13), GPIO_SET);
    result &= CHECK_REG_RESERVED(GPIO_ReadOutputData(GPIO_14), GPIO_SET);
    if (result != TRUE)
    {
        DEBUG_ERROR("GPIO_ReadOutputData fail.");
        return FAILED;
    }
    
    /* read reserved */
    RCC_APBPeriphResetCmd(GPIO_SC, 0, SET);
    RCC_APBPeriphResetCmd(GPIO_SC, 0, RESET);
    
    return ret;
}

/* GPIO_IntCmd() */
TestStatus GPIO_InterfaceTest6(void)
{
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;
    
    /* reset */
    GPIO_IntCmd(GPIO_0, ENABLE);
    GPIO_IntCmd(GPIO_1, ENABLE);
    GPIO_IntCmd(GPIO_2, ENABLE);
    GPIO_IntCmd(GPIO_3, ENABLE);
    GPIO_IntCmd(GPIO_4, ENABLE);
    GPIO_IntCmd(GPIO_5, ENABLE);
    GPIO_IntCmd(GPIO_6, ENABLE);
    GPIO_IntCmd(GPIO_7, ENABLE);
    GPIO_IntCmd(GPIO_8, ENABLE);
    GPIO_IntCmd(GPIO_9, ENABLE);
    GPIO_IntCmd(GPIO_10, ENABLE);
    GPIO_IntCmd(GPIO_11, ENABLE);
    GPIO_IntCmd(GPIO_12, ENABLE);
    GPIO_IntCmd(GPIO_13, ENABLE);
    GPIO_IntCmd(GPIO_14, ENABLE);

    result &= CHECK_REG_RESERVED(READ_REG(GPIO_0->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_1->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_2->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_3->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_4->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_5->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_6->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_7->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_8->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_9->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_10->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_11->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_12->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_13->GPIMR), GPIO_INTMASK_EN);
    result &= CHECK_REG_RESERVED(READ_REG(GPIO_14->GPIMR), GPIO_INTMASK_EN);
    if (result != TRUE)
    {
        DEBUG_ERROR("GPIO_IntCmd fail.");
        return FAILED;
    }
    
    /* read reserved */
    RCC_APBPeriphResetCmd(GPIO_SC, 0, SET);
    RCC_APBPeriphResetCmd(GPIO_SC, 0, RESET);
    
    return ret;
}

