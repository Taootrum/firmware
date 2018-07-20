/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_cru.h"

/****************************************************************
  * 函数      : CRU_InterfacesTestx()
  * 参数      : None
  * 返回值     : TRUE or FALSE
  * 描述      : CRU interfaces test cases.
 ***************************************************************/
/* RCC_SoftReset()
   RCC_GetGlobalResetFlag() */
TestStatus CRU_InterfaceTest1(void)
{
    uint32_t Flag = 0;

    Flag = RCC_GetGlobalResetFlag();

    if (SOFT_RESET_FLAG & Flag)
    {
        return PASSED;
    }
    RCC_SoftReset();
        
    return FAILED;
}

/* RCC_PCIEReset() */
TestStatus CRU_InterfaceTest2(void)
{
    return FAILED;
}

/* RCC_IPCoreReset() */
TestStatus CRU_InterfaceTest3(void)
{
    return FAILED;
}

/* RCC_ClkManageReset() */
TestStatus CRU_InterfaceTest4(void)
{
    return FAILED;
}

/* RCC_FabricBusReset() */
TestStatus CRU_InterfaceTest5(void)
{
    return FAILED;
}

/* RCC_DDRReset() */
TestStatus CRU_InterfaceTest6(void)
{
    return FAILED;
}

/* RCC_IOPADReset() */
TestStatus CRU_InterfaceTest7(void)
{
    IOPAD_TypeDef IOPAD_Structure;
    TestStatus ret = PASSED;

    IOPAD_Structure.FCR0 = READ_REG(IOPAD_MUX->FCR0);
    IOPAD_Structure.FCR1 = READ_REG(IOPAD_MUX->FCR1);
    IOPAD_Structure.FCR2 = READ_REG(IOPAD_MUX->FCR2);
    IOPAD_Structure.FCR3 = READ_REG(IOPAD_MUX->FCR3);
    IOPAD_Structure.FCR4 = READ_REG(IOPAD_MUX->FCR4);

    RCC_IOPADReset();
    if ((0x00 != READ_REG(IOPAD_MUX->FCR0))
        || (0x00 != READ_REG(IOPAD_MUX->FCR1))
        || (0x00 != READ_REG(IOPAD_MUX->FCR2))
        || (0xfe != READ_REG(IOPAD_MUX->FCR3))
        || (0xff != READ_REG(IOPAD_MUX->FCR4)))
    {
        DEBUG_ERROR("RCC_IOPADReset fail.");
        ret = FAILED;
    }

    WRITE_REG(IOPAD_MUX->FCR0, IOPAD_Structure.FCR0);
    WRITE_REG(IOPAD_MUX->FCR1, IOPAD_Structure.FCR1);
    WRITE_REG(IOPAD_MUX->FCR2, IOPAD_Structure.FCR2);
    WRITE_REG(IOPAD_MUX->FCR3, IOPAD_Structure.FCR3);
    WRITE_REG(IOPAD_MUX->FCR4, IOPAD_Structure.FCR4);
            
    return ret;
}

/* RCC_GetGlobalResetFlag() */
TestStatus CRU_InterfaceTest8(void)
{
    if (RCC_GetGlobalResetFlag() != READ_REG(RST_SC->GRF))
    {
        DEBUG_ERROR("RCC_GetGlobalResetFlag fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* RCC_DDRReadSelectCmd() */
TestStatus CRU_InterfaceTest9(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(RST_SC->DDR_RCFG);
    
    RCC_DDRReadSelectCmd(DRAM_READ_SEL5);
    if (DRAM_READ_SEL5 != READ_REG(RST_SC->DDR_RCFG))
    {
        DEBUG_ERROR("RCC_DDRReadSelectCmd fail.");
        ret = FAILED;
    }
    
    RCC_DDRReadSelectCmd(Temp);
    
    return ret;
}

/* RCC_DDRWriteSelectCmd() */
TestStatus CRU_InterfaceTest10(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(RST_SC->DDR_WCFG);
    
    RCC_DDRWriteSelectCmd(0x55);
    
    if (0x55 != READ_REG(RST_SC->DDR_WCFG))
    {
        DEBUG_ERROR("RCC_DDRWriteSelectCmd fail.");
        ret = FAILED;
    }

    RCC_DDRWriteSelectCmd(Temp);

    return ret;
}

/* RCC_SYSCLKSetSource() */
TestStatus CRU_InterfaceTest11(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(FABRIC_CLK->CLKSRC);
    RCC_SYSCLKSetSource(FABRIC_CLK, SYSCLK_SOURCE_DPLL);
    if (SYSCLK_SOURCE_DPLL != RCC_SYSCLKGetSource(FABRIC_CLK))
    {
        DEBUG_ERROR("RCC_SYSCLKSetSource fail.");
        ret = FAILED;
    }
    RCC_SYSCLKSetSource(FABRIC_CLK, Temp);
    
    return ret;
}

/* RCC_SYSCLKGetSource() */
TestStatus CRU_InterfaceTest12(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(FABRIC_CLK->CLKSRC);
    RCC_SYSCLKSetSource(FABRIC_CLK, SYSCLK_SOURCE_OSC);
    if (SYSCLK_SOURCE_OSC != RCC_SYSCLKGetSource(FABRIC_CLK))
    {
        DEBUG_ERROR("RCC_SYSCLKGetSource fail.");
        ret = FAILED;
    }
    RCC_SYSCLKSetSource(FABRIC_CLK, Temp);
    
    return ret;
}

/* RCC_SYSCLKSetDiv() */
TestStatus CRU_InterfaceTest13(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(FABRIC_CLK->CLKRATIO);
    RCC_SYSCLKSetDiv(FABRIC_CLK, 0x55);
    if (0x55 != RCC_SYSCLKGetDiv(FABRIC_CLK))
    {
        DEBUG_ERROR("RCC_SYSCLKSetDiv fail.");
        ret = FAILED;
    }
    RCC_SYSCLKSetDiv(FABRIC_CLK, Temp);
    
    return ret;
}

/* RCC_SYSCLKGetDiv() */
TestStatus CRU_InterfaceTest14(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(FABRIC_CLK->CLKRATIO);
    RCC_SYSCLKSetDiv(FABRIC_CLK, 0x33);
    if (0x33 != RCC_SYSCLKGetDiv(FABRIC_CLK))
    {
        DEBUG_ERROR("RCC_SYSCLKGetDiv fail.");
        ret = FAILED;
    }
    RCC_SYSCLKSetDiv(FABRIC_CLK, Temp);
    
    return ret;
}

/* RCC_SYSCLKGetFreq() */
TestStatus CRU_InterfaceTest15(void)
{
    uint32_t uDiv = 0;
    uint32_t uFreq = 0;
    RCC_ClocksTypeDef RCC_Clock;
    
    RCC_SYSCLKGetFreq(&RCC_Clock);
    if (RCC_Clock.APLL_Frequency != APLL_CLK_FREQ
        || RCC_Clock.DPLL_Frequency != DPLL_CLK_FREQ)
    {
        DEBUG_ERROR("RCC_SYSCLKGetFreq fail.");
        return FAILED;
    }

    /* fabric clock */
    uDiv = RCC_SYSCLKGetDiv(FABRIC_CLK);
    if (RCC_SYSCLKGetSource(FABRIC_CLK) == SYSCLK_SOURCE_APLL)
    {
        uFreq = APLL_CLK_FREQ;
    }
    else if (RCC_SYSCLKGetSource(FABRIC_CLK) == SYSCLK_SOURCE_DPLL)
    {
        uFreq = DPLL_CLK_FREQ;
    }
    else if (RCC_SYSCLKGetSource(FABRIC_CLK) == SYSCLK_SOURCE_OSC)
    {
        uFreq = XTAL;
    }
    if (RCC_Clock.FCLK_Frequency != uFreq / (uDiv + 1))
    {
        DEBUG_ERROR("RCC_SYSCLKGetFreq fail.");
        return FAILED;
    }

    /* ipcore clock */
    uDiv = RCC_SYSCLKGetDiv(IPCORE_CLK);
    if (RCC_SYSCLKGetSource(IPCORE_CLK) == SYSCLK_SOURCE_APLL)
    {
        uFreq = APLL_CLK_FREQ;
    }
    else if (RCC_SYSCLKGetSource(IPCORE_CLK) == SYSCLK_SOURCE_DPLL)
    {
        uFreq = DPLL_CLK_FREQ;
    }
    else if (RCC_SYSCLKGetSource(IPCORE_CLK) == SYSCLK_SOURCE_OSC)
    {
        uFreq = XTAL;
    }
    if (RCC_Clock.FCLK_Frequency != uFreq / (uDiv + 1))
    {
        DEBUG_ERROR("RCC_SYSCLKGetFreq fail.");
        return FAILED;
    }

    /* ddr clock */
    uDiv = RCC_SYSCLKGetDiv(DDR_CLK);
    if (RCC_SYSCLKGetSource(DDR_CLK) == SYSCLK_SOURCE_APLL)
    {
        uFreq = APLL_CLK_FREQ;
    }
    else if (RCC_SYSCLKGetSource(DDR_CLK) == SYSCLK_SOURCE_DPLL)
    {
        uFreq = DPLL_CLK_FREQ;
    }
    else if (RCC_SYSCLKGetSource(DDR_CLK) == SYSCLK_SOURCE_OSC)
    {
        uFreq = XTAL;
    }
    if (RCC_Clock.FCLK_Frequency != uFreq / (uDiv + 1))
    {
        DEBUG_ERROR("RCC_SYSCLKGetFreq fail.");
        return FAILED;
    }

    return PASSED;
}

/* RCC_SYSCLKCmd() */
TestStatus CRU_InterfaceTest16(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(PCIE_CLK->CLKGT);
    RCC_SYSCLKCmd(PCIE_CLK, DISABLE);
    if (ENABLE != READ_REG(PCIE_CLK->CLKGT))
    {
        DEBUG_ERROR("RCC_SYSCLKCmd fail.");
        ret = FAILED;
    }
    WRITE_REG(PCIE_CLK->CLKGT, Temp);
    
    return ret;
}

/* RCC_APBPeriphResetCmd() */
TestStatus CRU_InterfaceTest17(void)
{
    uint8_t Temp = 0;
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;

    /* SPI0 Reset*/
    Temp = READ_REG(SPI_SC->SR);
    RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);
    result &= CHECK_REG_RESERVED(SPI0->CR0, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->CR1, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->DR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->SR, 0x3);
    result &= CHECK_REG_RESERVED(SPI0->CPSR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->RIS, 0x8);
    result &= CHECK_REG_RESERVED(SPI0->MIS, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->ICR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->DMACR, 0x0);
    result &= CHECK_REG_RESERVED(SPI0->FIFOTH, 0x404);
    WRITE_REG(SPI_SC->SR, Temp);
    if (result != TRUE)
    {
        DEBUG_ERROR("SPI0 reset fail.");
        ret = FAILED;
    }

    /* I2C1 Reset*/
    Temp = READ_REG(SPI_SC->SR);
    RCC_APBPeriphClockCmd(SPI_SC, 1, ENABLE);
    RCC_APBPeriphResetCmd(SPI_SC, 1, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 1, RESET);
    result &= CHECK_REG_RESERVED(SPI1->CR0, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->CR1, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->DR, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->SR, 0x3);
    result &= CHECK_REG_RESERVED(SPI1->CPSR, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->RIS, 0x8);
    result &= CHECK_REG_RESERVED(SPI1->MIS, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->ICR, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->DMACR, 0x0);
    result &= CHECK_REG_RESERVED(SPI1->FIFOTH, 0x404);
    WRITE_REG(SPI_SC->SR, Temp);
    RCC_APBPeriphClockCmd(SPI_SC, 1, DISABLE);
    if (result != TRUE)
    {
        DEBUG_ERROR("SPI1 reset fail.");
        ret = FAILED;
    }
    
    return ret;
}

/* RCC_APBPeriphClockCmd() */
TestStatus CRU_InterfaceTest18(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(I2C_SC->CGE);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 2, ENABLE);
    if (0x7 != (READ_REG(I2C_SC->CGE) & 0x7))
    {
        ret = FAILED;
    }
    WRITE_REG(I2C_SC->CGE, Temp);
    
    return ret;
}

/* RCC_APBPeriphIsoEnCmd() */
TestStatus CRU_InterfaceTest19(void)
{
    uint32_t Temp = 0;
    TestStatus ret = PASSED;

    Temp = READ_REG(I2C_SC->ISO);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);
    if (0x1 != READ_REG(I2C_SC->ISO))
    {
        ret = FAILED;
    }
    WRITE_REG(I2C_SC->ISO, Temp);
    
    return ret;
}

