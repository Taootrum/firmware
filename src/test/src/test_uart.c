/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_uart.h"

/****************************************************************
* 函数      : UART_InterfacesTestx()
* 参数      : None
* 返回值     : TRUE or FALSE
* 描述      : UART interfaces test cases.
***************************************************************/
/* UART_DeInit() */
TestStatus UART_InterfaceTest1(void)
{
    UART_InitTypeDef UART_InitStructure;
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;

    while (UART->FR & UART_FLAG_BUSY);
    UART_DeInit(UART);
    
    /* check */
    result &= CHECK_REG_RESERVED(UART->DR, 0x0);
    result &= CHECK_REG_RESERVED(UART->RSR, 0x0);
    result &= CHECK_REG_RESERVED(UART->FR & 0xF8, 0x0);
    result &= CHECK_REG_RESERVED(UART->ILPR, 0x0);
    result &= CHECK_REG_RESERVED(UART->IBRD, 0x0);
    result &= CHECK_REG_RESERVED(UART->FBRD, 0x0);
    result &= CHECK_REG_RESERVED(UART->LCR, 0x0);
    result &= CHECK_REG_RESERVED(UART->CR, 0x0);
    result &= CHECK_REG_RESERVED(UART->IFLS, 0x0);
    result &= CHECK_REG_RESERVED(UART->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(UART->RIS & 0x7F0, 0x0);
    result &= CHECK_REG_RESERVED(UART->MIS & 0x7F0, 0x0);
    result &= CHECK_REG_RESERVED(UART->ICR, 0x0);
    result &= CHECK_REG_RESERVED(UART->DMACR, 0x0);

    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    RCC_APBPeriphClockCmd(UART_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(UART_SC, ENABLE);
    UART_StructInit(&UART_InitStructure);
    UART_Init(DEBUG_UART, &UART_InitStructure);
    UART_Cmd(DEBUG_UART, ENABLE);

    if (result != TRUE)
    {
        DEBUG_ERROR("UART_DeInit fail.");
        ret = FAILED;
    }

    return ret;
}

/* UART_Init() */
TestStatus UART_InterfaceTest2(void)
{
    UART_InitTypeDef UART_InitStructure;
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;

    while (UART->FR & UART_FLAG_BUSY);
    RCC_APBPeriphResetCmd(UART_SC, 0, SET);
    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    
    UART_StructInit(&UART_InitStructure);
    UART_Init(DEBUG_UART, &UART_InitStructure);
    
    /* check */
    result &= CHECK_REG_RESERVED(UART->DR, 0x0);
    result &= CHECK_REG_RESERVED(UART->RSR, 0x0);
    result &= CHECK_REG_RESERVED(UART->FR & 0xF8, 0x90);
    result &= CHECK_REG_RESERVED(UART->ILPR, 0x0);
    result &= CHECK_REG_RESERVED(UART->IBRD, 0x36);
    result &= CHECK_REG_RESERVED(UART->FBRD, 0x10);
    result &= CHECK_REG_RESERVED(UART->LCR, 0x60);
    result &= CHECK_REG_RESERVED(UART->CR, 0x300);
    result &= CHECK_REG_RESERVED(UART->IFLS, 0x12);
    result &= CHECK_REG_RESERVED(UART->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(UART->RIS & 0x7F0, 0x0);
    result &= CHECK_REG_RESERVED(UART->MIS & 0x7F0, 0x0);
    result &= CHECK_REG_RESERVED(UART->ICR, 0x0);
    result &= CHECK_REG_RESERVED(UART->DMACR, 0x0);

    UART_Cmd(DEBUG_UART, ENABLE);
    
    if (result != TRUE)
    {
        DEBUG_ERROR("UART_Init fail.");
        ret = FAILED;
    }

    return ret;
}

/* UART_Cmd() */
TestStatus UART_InterfaceTest3(void)
{
    uint32_t temp = 0, result = 0;
    TestStatus ret = PASSED;

    temp = READ_REG(UART->CR);
    
    UART_Cmd(DEBUG_UART, ENABLE);
    result = READ_REG(UART->CR);
    WRITE_REG(UART->CR, temp);
    
    if ((result & UART_ENABLE) != UART_ENABLE)
    {
        DEBUG_ERROR("UART_Cmd enable fail.");
        ret = FAILED;
    }
    
    return ret;
}

/* UART_SendData() 
   UART_ReceiveData() 
   UART_GetStatus() */
TestStatus UART_InterfaceTest4(void)
{
    UART_InitTypeDef UART_InitStructure;
    uint8_t WriteByte = 0x55, ReadByte = 0;
    TestStatus ret = PASSED;

    while (UART->FR & UART_FLAG_BUSY);
    RCC_APBPeriphResetCmd(UART_SC, 0, SET);
    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.UART_LoopBackControl = UART_MODE_LOOPBACK;
    UART_Init(UART, &UART_InitStructure);
    UART_Cmd(UART, ENABLE);
    
    UART_SendData(UART, WriteByte);
    while (UART_GetFlagStatus(UART, UART_FLAG_TXFE) == RESET);
    
    while (UART_GetFlagStatus(UART, UART_FLAG_RXFE) == SET);
    ReadByte = UART_ReceiveData(UART);
    
    Debug_Init();
    
    if (WriteByte != ReadByte)
    {
        DEBUG_ERROR("UART sned & recive data fail.");
        ret = FAILED;
    }

    return ret;
}

/* UART_ITConfig() */
TestStatus UART_InterfaceTest5(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(UART->IMSC);
    UART_ITConfig(UART, UART_IT_OE, ENABLE);
    UART_ITConfig(UART, UART_IT_BE, ENABLE);
    UART_ITConfig(UART, UART_IT_PE, ENABLE);
    UART_ITConfig(UART, UART_IT_FE, ENABLE);
    UART_ITConfig(UART, UART_IT_RT, ENABLE);
    UART_ITConfig(UART, UART_IT_TX, ENABLE);
    UART_ITConfig(UART, UART_IT_RX, ENABLE);
    UART_ITConfig(UART, UART_IT_DSR, ENABLE);
    UART_ITConfig(UART, UART_IT_DCD, ENABLE);
    UART_ITConfig(UART, UART_IT_CTS, ENABLE);
    UART_ITConfig(UART, UART_IT_RIM, ENABLE);
    if (0x7FF != READ_REG(UART->IMSC))
    {
        DEBUG_ERROR("UART_ITConfig fail.");
        ret = FAILED;
    }
    WRITE_REG(UART->IMSC, Temp);
    
    return ret;
}

/* UART_GetRawITStatus() */
TestStatus UART_InterfaceTest6(void)
{
    UART_InitTypeDef UART_InitStructure;
    uint8_t WriteByte = 0x55;
    TestStatus ret = PASSED;

    while (UART->FR & UART_FLAG_BUSY);
    RCC_APBPeriphResetCmd(UART_SC, 0, SET);
    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.UART_LoopBackControl = UART_MODE_LOOPBACK;
    UART_Init(UART, &UART_InitStructure);
    UART_Cmd(UART, ENABLE);
    
    /* config IT */
    UART_ITConfig(UART, UART_IT_RX, ENABLE);
    
    UART_SendData(UART, WriteByte);
    while (UART_GetFlagStatus(UART, UART_FLAG_TXFE) == RESET);

    Debug_Init();
    while (UART->FR & UART_FLAG_BUSY);
    if (UART_GetRawITStatus(UART, UART_IT_RX) == RESET)
    {
        DEBUG_ERROR("UART_GetRawITStatus fail.");
        ret = FAILED;
    }
    
    return ret;
}

/* UART_GetMaskITStatus() */
TestStatus UART_InterfaceTest7(void)
{
    UART_InitTypeDef UART_InitStructure;
    uint8_t WriteByte = 0x55;
    TestStatus ret = PASSED;

    while (UART->FR & UART_FLAG_BUSY);
    RCC_APBPeriphResetCmd(UART_SC, 0, SET);
    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.UART_LoopBackControl = UART_MODE_LOOPBACK;
    UART_Init(UART, &UART_InitStructure);
    UART_Cmd(UART, ENABLE);
    
    /* config IT */
    UART_ITConfig(UART, UART_IT_RX, ENABLE);
    
    UART_SendData(UART, WriteByte);
    while (UART_GetFlagStatus(UART, UART_FLAG_TXFE) == RESET);

    Debug_Init();
    while (UART->FR & UART_FLAG_BUSY);
    if (UART_GetMaskITStatus(UART, UART_IT_RX) == RESET)
    {
        DEBUG_ERROR("UART_GetMaskITStatus fail.");
        ret = FAILED;
    }
    
    return ret;
}

/* UART_ClearITStatus() */
TestStatus UART_InterfaceTest8(void)
{
    UART_InitTypeDef UART_InitStructure;
    uint8_t WriteByte = 0x55;
    TestStatus ret = PASSED;

    while (UART->FR & UART_FLAG_BUSY);
    RCC_APBPeriphResetCmd(UART_SC, 0, SET);
    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.UART_LoopBackControl = UART_MODE_LOOPBACK;
    UART_Init(UART, &UART_InitStructure);
    UART_Cmd(UART, ENABLE);
    
    /* config IT */
    UART_ITConfig(UART, UART_IT_RT, ENABLE);
    UART_ITConfig(UART, UART_IT_RX, ENABLE);
    
    UART_SendData(UART, WriteByte);
    while (UART_GetFlagStatus(UART, UART_FLAG_TXFE) == RESET);

    while (UART_GetFlagStatus(UART, UART_FLAG_RXFE) == SET);
    UART_ReceiveData(UART);

    UART_ClearITStatus(UART, UART_IT_RT);
    UART_ClearITStatus(UART, UART_IT_RX);

    Debug_Init();
    if (UART_GetMaskITStatus(UART, UART_IT_RT) != RESET
        || UART_GetMaskITStatus(UART, UART_IT_RX) != RESET)
    {
        DEBUG_ERROR("UART_GetMaskITStatus fail.");
        ret = FAILED;
    }

    return ret;
}

