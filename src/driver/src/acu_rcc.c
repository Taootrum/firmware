/*******************************************************************************
  * @file    acu_rcc.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Clock&Reset Module Function. 
 ******************************************************************************/
#include "acu_rcc.h"

void RCC_SoftReset(void)
{
    WRITE_REG(RST_SC->SRST_CNT, SYS_RESET_CNT);
    WRITE_REG(RST_SC->SRST, SYS_RESET_LOW);
    WRITE_REG(RST_SC->SRST, SYS_RESET_HIGH);
}

void RCC_PCIEReset(void)
{
    WRITE_REG(RST_SC->PCIE_RST, SYS_RESET_LOW);
    WRITE_REG(RST_SC->PCIE_RST, SYS_RESET_HIGH);
}

void RCC_IPCoreReset(void)
{
    WRITE_REG(RST_SC->IPCORE_RST, SYS_RESET_LOW);
    WRITE_REG(RST_SC->IPCORE_RST, SYS_RESET_HIGH);
}

void RCC_ClkManageReset(void)
{
    WRITE_REG(RST_SC->CLKM_RST, SYS_RESET_LOW);
    WRITE_REG(RST_SC->CLKM_RST, SYS_RESET_HIGH);
}

void RCC_FabricBusReset(void)
{
    WRITE_REG(RST_SC->BUS_RST, SYS_RESET_LOW);
    WRITE_REG(RST_SC->BUS_RST, SYS_RESET_HIGH);
}

void RCC_DDRReset(void)
{
    WRITE_REG(RST_SC->DDR_RST, SYS_RESET_LOW);
    WRITE_REG(RST_SC->DDR_RST, SYS_RESET_HIGH);
}

void RCC_IOPADReset(void)
{
    WRITE_REG(RST_SC->IOPAD_RST, SYS_RESET_LOW);
    WRITE_REG(RST_SC->IOPAD_RST, SYS_RESET_HIGH);
}

uint32_t RCC_GetGlobalResetFlag(void)
{
    return READ_REG(RST_SC->GRF);
}

void RCC_DDRReadSelectCmd(uint32_t DDR_Channels)
{
    assert_param(IS_DRAM_READ_SEL(DDR_Channels));
    WRITE_REG(RST_SC->DDR_RCFG, DDR_Channels);
}

void RCC_DDRWriteSelectCmd(uint32_t DDR_Channels)
{
    assert_param(IS_DRAM_WRITE_SEL(DDR_Channels));
    WRITE_REG(RST_SC->DDR_WCFG, DDR_Channels);
}

void RCC_PLLConfig(PLLCLK_TypeDef *RCC_PLLSource, PLL_InitTypeDef *PLL_Init)
{
    uint8_t range = 0;
    
    assert_param(IS_PLL_CLK(RCC_PLLSource));
    assert_param(IS_PLL_DIVR(PLL_Init->Divr));
    assert_param(IS_PLL_DIVF(PLL_Init->Divf));
    assert_param(IS_PLL_DIVQ(PLL_Init->Divq));

    /* reset PLL */
    RCC_PLLSource->RESET = 0x1;

    /* cross PLL */
    RCC_PLLSource->BYPASS = 0;

    /* config Divr */
    RCC_PLLSource->DIVR = PLL_Init->Divr;

    /* config Divf */
    RCC_PLLSource->DIVF_LOW = (uint8_t)PLL_Init->Divf;
    RCC_PLLSource->DIVF_HIGH = (uint8_t)(PLL_Init->Divf >> 8);

    /* Config Range */
    if (RCC_PLLSource->BYPASS) 
    {
        RCC_PLLSource->RANGE = 0x0;
    }
    else
    {
        range = PLL_Init->PLLInputClock / 1000000;
        if (range >= 7 && range <= 11) {
            RCC_PLLSource->RANGE = 0x1;
        } else if (range >= 11 && range <= 18) {
            RCC_PLLSource->RANGE = 0x2;
        } else if (range >= 18 && range <= 30) {
            RCC_PLLSource->RANGE = 0x3;
        } else if (range >= 30 && range <= 50) {
            RCC_PLLSource->RANGE = 0x4;
        } else if (range >= 50 && range <= 80) {
            RCC_PLLSource->RANGE = 0x5;
        } else if (range >= 80 && range <= 130) {
            RCC_PLLSource->RANGE = 0x6;
        } else if (range >= 130 && range <= 200) {
            RCC_PLLSource->RANGE = 0x7;
        }
    }
    
    /* config Divq */
    RCC_PLLSource->DIVQ = PLL_Init->Divq;

    /* Enable parameter load & clock gate enable */
    RCC_PLLSource->CONTROL = 0x2;
    
    /* normal operation */ 
    RCC_PLLSource->RESET = 0;
}

/****************************************************************
  * 函数      : PLL_StructInit()
  * 参数      : 
              PLL_StructInit: 初始化结构体
  * 返回值     : None
  * 描述      : PLL默认初始化
 ***************************************************************/
void PLL_StructInit(PLL_InitTypeDef *PLL_Init)
{
    /* Initialize the SPI_Direction member */
    PLL_Init->PLLInputClock = XTAL;
    /* initialize the SPI_Mode member */
    PLL_Init->PLLOutputClock = APLL_CLK_FREQ;
    /* 24M / (0 + 1) = 24M */ 
    PLL_Init->Divr = PLL_DIVR;
    /* 24M * (0x4A + 1) * 2 = 3600M */ 
    PLL_Init->Divf = PLL_DIVF;
    /* 3600M / (2 ^ 1) = 1800M */ 
    PLL_Init->Divq = PLL_DIVQ_2;
}

LockStatus RCC_PLLGetLockStatus(PLLCLK_TypeDef *RCC_PLLSource)
{
    assert_param(IS_PLL_CLK(RCC_PLLSource));

    return (LockStatus)RCC_PLLSource->LOCK;
}

void RCC_PLLCmd(PLLCLK_TypeDef *RCC_PLLSource, FunctionalState NewState)
{
    assert_param(IS_PLL_CLK(RCC_PLLSource));

    if (NewState == ENABLE)
    {
        SET_BIT(RCC_PLLSource->ENABLE, PLL_ENABLE);
    }
    else
    {
        CLEAR_BIT(RCC_PLLSource->ENABLE, PLL_ENABLE);
    }
}

void RCC_SYSCLKSetSource(CLK_TypeDef *RCC_SYSCLK, uint32_t RCC_SYSCLKSource)
{
    assert_param(IS_RCC_SYSCLK(RCC_SYSCLK));
    assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
    RCC_SYSCLK->CLKSRC = RCC_SYSCLKSource;
}

uint32_t RCC_SYSCLKGetSource(CLK_TypeDef *RCC_SYSCLK)
{
    assert_param(IS_RCC_SYSCLK(RCC_SYSCLK));
    
    return RCC_SYSCLK->CLKSRC;
}

void RCC_SYSCLKSetDiv(CLK_TypeDef *RCC_SYSCLK, uint32_t RCC_SYSCLKDIV)
{
    assert_param(IS_RCC_SYSCLK(RCC_SYSCLK));
    assert_param(IS_RCC_SYSCLK_DIV(RCC_SYSCLKDIV));
    RCC_SYSCLK->CLKRATIO = RCC_SYSCLKDIV;
}

uint32_t RCC_SYSCLKGetDiv(CLK_TypeDef *RCC_SYSCLK)
{
    assert_param(IS_RCC_SYSCLK(RCC_SYSCLK));
    
    return RCC_SYSCLK->CLKRATIO;
}

void RCC_SYSCLKGetFreq(RCC_ClocksTypeDef *RCC_Clocks)
{
    uint32_t uDiv = 0;

    /* system clock */
    RCC_Clocks->APLL_Frequency = APLL_CLK_FREQ;
    RCC_Clocks->DPLL_Frequency = DPLL_CLK_FREQ;
    
    /* fabric clock */
    uDiv = RCC_SYSCLKGetDiv(FABRIC_CLK);
    if (RCC_SYSCLKGetSource(FABRIC_CLK) == SYSCLK_SOURCE_APLL)
    {
        RCC_Clocks->FCLK_Frequency = RCC_Clocks->APLL_Frequency / (uDiv + 1);
    }
    else if (RCC_SYSCLKGetSource(FABRIC_CLK) == SYSCLK_SOURCE_DPLL)
    {
        RCC_Clocks->FCLK_Frequency = RCC_Clocks->DPLL_Frequency / (uDiv + 1);
    }
    else
    {
        RCC_Clocks->FCLK_Frequency = XTAL / (uDiv + 1);
    }
    
    /* ipcore clock */
    uDiv = RCC_SYSCLKGetDiv(IPCORE_CLK);
    if (RCC_SYSCLKGetSource(IPCORE_CLK) == SYSCLK_SOURCE_APLL)
    {
        RCC_Clocks->IPCLK_Frequency = RCC_Clocks->APLL_Frequency / (uDiv + 1);
    }
    else if (RCC_SYSCLKGetSource(IPCORE_CLK) == SYSCLK_SOURCE_DPLL)
    {
        RCC_Clocks->IPCLK_Frequency = RCC_Clocks->DPLL_Frequency / (uDiv + 1);
    }
    else
    {
        RCC_Clocks->IPCLK_Frequency = XTAL / (uDiv + 1);
    }

    /* ddr clock */
    uDiv = RCC_SYSCLKGetDiv(DDR_CLK);
    if (RCC_SYSCLKGetSource(DDR_CLK) == SYSCLK_SOURCE_APLL)
    {
        RCC_Clocks->DDRCLK_Frequency = RCC_Clocks->APLL_Frequency / (uDiv + 1);
    }
    else if (RCC_SYSCLKGetSource(DDR_CLK) == SYSCLK_SOURCE_DPLL)
    {
        RCC_Clocks->DDRCLK_Frequency = RCC_Clocks->DPLL_Frequency / (uDiv + 1);
    }
    else
    {
        RCC_Clocks->DDRCLK_Frequency = XTAL / (uDiv + 1);
    }
}

void RCC_SYSCLKCmd(CLK_TypeDef *RCC_SYSCLK, FunctionalState NewState)
{
    assert_param(IS_RCC_SYSCLK(RCC_SYSCLK));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        CLEAR_BIT(RCC_SYSCLK->CLKGT, RCC_SYSCLK_DISEN);
    }
    else
    {
        SET_BIT(RCC_SYSCLK->CLKGT, RCC_SYSCLK_DISEN);
    }
}

void RCC_APBPeriphResetCmd(APBSYS_TypeDef *RCC_APBPeriph, uint8_t ModuleNum, ResetStatus NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (RCC_APBPeriph == I2C_SC) {
        assert_param(ModuleNum < I2C_MODULE_MAX);    
    }
    else if (RCC_APBPeriph == UART_SC) {
        assert_param(ModuleNum < UART_MODULE_MAX); 
    }
    else if (RCC_APBPeriph == SPI_SC) {
        assert_param(ModuleNum < SPI_MODULE_MAX);
    }
    else if (RCC_APBPeriph == TIM_SC) {
        assert_param(ModuleNum < TIM_MODULE_MAX);
    }
    else if (RCC_APBPeriph == WDT_SC) {
        assert_param(ModuleNum < WDT_MODULE_MAX);    
    }
    else if (RCC_APBPeriph == GPIO_SC) {
        assert_param(ModuleNum < GPIO_MODULE_MAX);
    }

    if (NewState == SET)
    {
        SET_BIT(RCC_APBPeriph->SR, RCC_APB_SRESET << ModuleNum);
    }
    else
    {
        CLEAR_BIT(RCC_APBPeriph->SR, RCC_APB_SRESET << ModuleNum);
    }
}

void RCC_APBPeriphClockCmd(APBSYS_TypeDef *RCC_APBPeriph, uint8_t ModuleNum, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (RCC_APBPeriph == I2C_SC) {
        assert_param(ModuleNum < I2C_MODULE_MAX);    
    }
    else if (RCC_APBPeriph == UART_SC) {
        assert_param(ModuleNum < UART_MODULE_MAX); 
    }
    else if (RCC_APBPeriph == SPI_SC) {
        assert_param(ModuleNum < SPI_MODULE_MAX);
    }
    else if (RCC_APBPeriph == TIM_SC) {
        assert_param(ModuleNum < TIM_MODULE_MAX);
    }
    else if (RCC_APBPeriph == WDT_SC) {
        assert_param(ModuleNum < WDT_MODULE_MAX);    
    }
    else if (RCC_APBPeriph == GPIO_SC) {
        assert_param(ModuleNum < GPIO_MODULE_MAX);
    }
    
    if (NewState == ENABLE)
    {
        SET_BIT(RCC_APBPeriph->CGE, RCC_APB_CLKEN << ModuleNum);
    }
    else
    {
        CLEAR_BIT(RCC_APBPeriph->CGE, RCC_APB_CLKEN << ModuleNum);
    }
}

void RCC_APBPeriphIsoEnCmd(APBSYS_TypeDef *RCC_APBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        SET_BIT(RCC_APBPeriph->ISO, RCC_APB_IOISOEN);
    }
    else
    {
        CLEAR_BIT(RCC_APBPeriph->ISO, RCC_APB_IOISOEN);
    }
}

void RCC_AXIPeriphResetCmd(IMEMC_TypeDef *RCC_AXIPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AXI_PERIPH(RCC_AXIPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        SET_BIT(RCC_AXIPeriph->SR, RCC_AXI_SRESET);
    }
    else
    {
        CLEAR_BIT(RCC_AXIPeriph->SR, RCC_AXI_SRESET);
    }
}

void RCC_AXIPeriphClockCmd(IMEMC_TypeDef *RCC_AXIPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AXI_PERIPH(RCC_AXIPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        SET_BIT(RCC_AXIPeriph->CGE, RCC_AXI_CLKEN);
    }
    else
    {
        CLEAR_BIT(RCC_AXIPeriph->CGE, RCC_AXI_CLKEN);
    }
}

/****************************************************************
  * 函数      : RCC_SYSCLKPrintReg()
  * 参数      : RCC_SYSCLK: sysclk module
  * 返回值     : None
  * 描述      : 
 ***************************************************************/
void RCC_SYSCLKPrintReg(CLK_TypeDef* RCC_SYSCLK)
{        
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK(RCC_SYSCLK));
    
    DEBUG_PRINT_REG(RCC_SYSCLK->CLKSRC);
    DEBUG_PRINT_REG(RCC_SYSCLK->CLKRATIO);
    DEBUG_PRINT_REG(RCC_SYSCLK->CLKGT);
}

/****************************************************************
  * 函数      : RCC_APBSYSPrintReg()
  * 参数      : RCC_APBPeriph: apb peripheral
  * 返回值     : None
  * 描述      : 
 ***************************************************************/
void RCC_APBSYSPrintReg(APBSYS_TypeDef* RCC_APBPeriph)
{        
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
    
    DEBUG_PRINT_REG(RCC_APBPeriph->SR);
    DEBUG_PRINT_REG(RCC_APBPeriph->CGE);
    DEBUG_PRINT_REG(RCC_APBPeriph->ISO);
    DEBUG_PRINT_REG(RCC_APBPeriph->SCR);
}

/****************************************************************
  * 函数      : RCC_AXISYSPrintReg()
  * 参数      : RCC_IMEM: IRAM/IROM
  * 返回值     : None
  * 描述      : 
 ***************************************************************/
void RCC_AXISYSPrintReg(IMEMC_TypeDef* RCC_IMEM)
{        
    /* Check the parameters */
    assert_param(IS_RCC_AXI_PERIPH(RCC_IMEM));
    
    DEBUG_PRINT_REG(RCC_IMEM->SR);
    DEBUG_PRINT_REG(RCC_IMEM->CGE);
    DEBUG_PRINT_REG(RCC_IMEM->MPD);
    DEBUG_PRINT_REG(RCC_IMEM->SCR);
}

/****************************************************************
  * 函数      : RCC_PLLPrintReg()
  * 参数      : RCC_PLLSource: APLL/DPLL
  * 返回值     : None
  * 描述      : 
 ***************************************************************/
void RCC_PLLPrintReg(PLLCLK_TypeDef *RCC_PLLSource)
{        
    /* Check the parameters */
    assert_param(IS_PLL_CLK(RCC_PLLSource));
    
    DEBUG_PRINT_REG(RCC_PLLSource->RESET);
    DEBUG_PRINT_REG(RCC_PLLSource->BYPASS);
    DEBUG_PRINT_REG(RCC_PLLSource->DIVR);
    DEBUG_PRINT_REG(RCC_PLLSource->DIVF_LOW);
    DEBUG_PRINT_REG(RCC_PLLSource->DIVF_HIGH);
    DEBUG_PRINT_REG(RCC_PLLSource->DIVQ);
    DEBUG_PRINT_REG(RCC_PLLSource->FSE);
    DEBUG_PRINT_REG(RCC_PLLSource->RANGE);
    DEBUG_PRINT_REG(RCC_PLLSource->CONTROL);
    DEBUG_PRINT_REG(RCC_PLLSource->ENABLE);
    DEBUG_PRINT_REG(RCC_PLLSource->LOCK);
}

