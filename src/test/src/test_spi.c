/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_spi.h"

/****************************************************************
  * 函数      : SPI_InterfacesTestx()
  * 参数      : None
  * 返回值     : TRUE or FALSE
  * 描述      : SPI interfaces test cases.
 ***************************************************************/
/* SPI_DeInit() */
TestStatus SPI_InterfaceTest1(void)
{
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;

    SPI_DeInit(SPI0);
    
    /* check */
    result &= CHECK_REG_RESERVED(SPI0->CR0, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->CR1, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->DR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->SR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->CPSR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->RIS, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->MIS, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->ICR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->DMACR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->FIFOTH, 0x0);
        
    if (result != TRUE)
    {
        DEBUG_ERROR("SPI_DeInit fail.");
        ret = FAILED;
    }

    /* 使能SPI */
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);
    RCC_APBPeriphClockCmd(SPI_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(SPI_SC, ENABLE);

    return ret;
}

/* SPI_Init() */
TestStatus SPI_InterfaceTest2(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;
    
    /* init */
    SPI_StructInit(&SPI_InitStructure);
    SPI_Init(SPI0, &SPI_InitStructure); 
    result &= CHECK_REG_RESERVED(SPI0->CR0, 0x7);
    result &= CHECK_REG_RESERVED(SPI0->CR1, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->DR, 0x0);
    //result &= CHECK_REG_RESERVED(SPI0->CPSR, SPI_CPSDVSR);
    result &= CHECK_REG_RESERVED(SPI0->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->ICR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->DMACR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->FIFOTH, ((SPI_FIFO_TX_TH - 1) << 8) | (SPI_FIFO_TX_TH - 1));
    if (result != TRUE)
    {
        DEBUG_ERROR("SPI_Init fail.");
        ret = FAILED;
    }
    
    /* rest reserved */
    RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);
    
    return ret;
}

/* SPI_Cmd() */
TestStatus SPI_InterfaceTest3(void)
{
    uint32_t temp = 0, result = 0;
    TestStatus ret = PASSED;

    temp = READ_REG(SPI0->CR1);
    
    SPI_Cmd(SPI0, ENABLE);
    result = READ_REG(SPI0->CR1);
    if ((result & SPI_ENABLE) != SPI_ENABLE)
    {
        DEBUG_ERROR("UART_Cmd enable fail.");
        ret = FAILED;
    }
    
    WRITE_REG(SPI0->CR1, temp);
    
    return ret;
}

/* SPI_SendData() 
   SPI_ReceiveData() 
   SPI_GetStatus() */
TestStatus SPI_InterfaceTest4(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    uint8_t HalfWord = 0x55;
    TestStatus ret = PASSED;
        
    SPI_StructInit(&SPI_InitStructure);
    SPI_InitStructure.SPI_LBM = SPI_MODE_LOOPBACK;
    SPI_Init(SPI0, &SPI_InitStructure); 
    SPI_Cmd(SPI0, ENABLE); 
    
    /*!< Loop while DR register in not emplty */
    while (SPI_GetStatus(SPI0, SPI_FLAG_TXE) == RESET);

    /*!< Send Half Word */
    SPI_SendData(SPI0, HalfWord);

    /*!< Wait to receive a Half Word */
    while (SPI_GetStatus(SPI0, SPI_FLAG_RXNE) == RESET);

    /*!< Return the Half Word read from the SPI bus */
    if (HalfWord != SPI_ReceiveData(SPI0))
    {
        DEBUG_ERROR("SPI send & recive data fail.");
        ret = FAILED;
    }

    /* rest reserved */
    RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);

    return ret;
}

/* SPI_ITConfig() */
TestStatus SPI_InterfaceTest5(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(SPI0->IMSC);
    SPI_ITConfig(SPI0, SPI_IT_TXIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RXIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RTIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RORIM, ENABLE);
    if (0xf != READ_REG(SPI0->IMSC))
    {
        DEBUG_ERROR("SPI_ITConfig fail.");
        ret = FAILED;
    }
    WRITE_REG(SPI0->IMSC, Temp);
    
    return ret;
}

/* SPI_GetRawITStatus() */
TestStatus SPI_InterfaceTest6(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    uint8_t HalfWord = 0x55;
    TestStatus ret = PASSED;
        
    SPI_StructInit(&SPI_InitStructure);
    SPI_InitStructure.SPI_LBM = SPI_MODE_LOOPBACK;
    SPI_InitStructure.SPI_TX_FIFO = 0;
    SPI_InitStructure.SPI_RX_FIFO = 0;
    SPI_Init(SPI0, &SPI_InitStructure); 
    SPI_Cmd(SPI0, ENABLE); 

    SPI_ITConfig(SPI0, SPI_IT_TXIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RXIM, ENABLE);

    /*!< Loop while DR register in not emplty */
    while (SPI_GetStatus(SPI0, SPI_FLAG_TXE) == RESET);
    /*!< Send Half Word */
    SPI_SendData(SPI0, HalfWord);
    while (SPI_GetStatus(SPI0, SPI_FLAG_TXE) == RESET);
    
    if (SPI_GetRawITStatus(SPI0, SPI_IT_TXIM) == RESET
        || SPI_GetRawITStatus(SPI0, SPI_IT_RXIM) == RESET)
    {
        DEBUG_ERROR("SPI_GetRawITStatus fail.");
        ret = FAILED;
    }

    /* rest reserved */
    RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);

    return ret;
}

/* SPI_GetMaskITStatus() */
TestStatus SPI_InterfaceTest7(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    uint8_t HalfWord = 0x55;
    TestStatus ret = PASSED;
        
    SPI_StructInit(&SPI_InitStructure);
    SPI_InitStructure.SPI_LBM = SPI_MODE_LOOPBACK;
    SPI_InitStructure.SPI_TX_FIFO = 0;
    SPI_InitStructure.SPI_RX_FIFO = 0;
    SPI_Init(SPI0, &SPI_InitStructure); 
    SPI_Cmd(SPI0, ENABLE); 

    SPI_ITConfig(SPI0, SPI_IT_TXIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RXIM, ENABLE);

    /*!< Loop while DR register in not emplty */
    while (SPI_GetStatus(SPI0, SPI_FLAG_TXE) == RESET);
    /*!< Send Half Word */
    SPI_SendData(SPI0, HalfWord);
    while (SPI_GetStatus(SPI0, SPI_FLAG_TXE) == RESET);
    
    if (SPI_GetMaskITStatus(SPI0, SPI_IT_TXIM) == RESET
        || SPI_GetMaskITStatus(SPI0, SPI_IT_RXIM) == RESET)
    {
        DEBUG_ERROR("SPI_GetMaskITStatus fail.");
        ret = FAILED;
    }

    /* rest reserved */
    RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);

    return ret;
}

/* SPI_ClearIT() */
TestStatus SPI_InterfaceTest8(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    uint8_t HalfWord = 0x55;
    TestStatus ret = PASSED;
        
    SPI_StructInit(&SPI_InitStructure);
    SPI_InitStructure.SPI_LBM = SPI_MODE_LOOPBACK;
    SPI_Init(SPI0, &SPI_InitStructure); 
    SPI_Cmd(SPI0, ENABLE); 

    SPI_ITConfig(SPI0, SPI_IT_TXIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RXIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RTIM, ENABLE);
    SPI_ITConfig(SPI0, SPI_IT_RORIM, ENABLE);
    
    /*!< Loop while DR register in not emplty */
    while (SPI_GetStatus(SPI0, SPI_FLAG_TXE) == RESET);

    /*!< Send Half Word */
    SPI_SendData(SPI0, HalfWord);
    
    /*!< Wait to receive a Half Word */
    while (SPI_GetStatus(SPI0, SPI_FLAG_RXNE) == RESET);
    SPI_ReceiveData(SPI0);

    SPI_ClearIT(SPI0, SPI_IT_RTC);
    SPI_ClearIT(SPI0, SPI_IT_RORC);

    if (SPI_GetMaskITStatus(SPI0, SPI_IT_RTIM) != RESET
        || SPI_GetMaskITStatus(SPI0, SPI_IT_RORIM) != RESET)
    {
        DEBUG_ERROR("SPI_ClearIT fail.");
        ret = FAILED;
    }
    
    /* rest reserved */
    RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);

    return ret;
}

