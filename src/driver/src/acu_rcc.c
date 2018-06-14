/*******************************************************************************
  * @file    acu_rcc.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Clock&Reset Module Function. 
 ******************************************************************************/
#include "acu_rcc.h"

void RCC_SoftReset(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RST_SC->SRST_CNT = SYS_RESET_CNT;
        RST_SC->SRST = SYS_RESET_LOW;
    }
    else
    {
        RST_SC->SRST = SYS_RESET_HIGH;
    }
}

void RCC_PCIEReset(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RST_SC->PCIE_RST = SYS_RESET_LOW;
    }
    else
    {
        RST_SC->PCIE_RST = SYS_RESET_HIGH;
    }
}

void RCC_IPCoreReset(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RST_SC->IPCORE_RST = SYS_RESET_LOW;
    }
    else
    {
        RST_SC->IPCORE_RST = SYS_RESET_HIGH;
    }
}

void RCC_ClkManageReset(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RST_SC->CLKM_RST = SYS_RESET_LOW;
    }
    else
    {
        RST_SC->CLKM_RST = SYS_RESET_HIGH;
    }
}

void RCC_FabricBusReset(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RST_SC->BUS_RST = SYS_RESET_LOW;
    }
    else
    {
        RST_SC->BUS_RST = SYS_RESET_HIGH;
    }
}

void RCC_DDRReset(FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        RST_SC->DDR_RST = SYS_RESET_LOW;
    }
    else
    {
        RST_SC->DDR_RST = SYS_RESET_HIGH;
    }
}

uint32_t RCC_GetGlobalResetFlag(void)
{
    return RST_SC->GRF;
}

void RCC_DDRReadSelectCmd(uint32_t DDR_Channels)
{
    assert_param(IS_DRAM_READ_SEL(DDR_Channels));
    RST_SC->DDR_RCFG = DDR_Channels;
}

void RCC_DDRWriteSelectCmd(uint32_t DDR_Channels)
{
    assert_param(IS_DRAM_WRITE_SEL(DDR_Channels));
    RST_SC->DDR_WCFG = DDR_Channels;
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
    uint32_t uClkFreq = 0, uDiv = 0;

    /* system clock */
    RCC_Clocks->SYSCLK_Frequency = SystemCoreClock;

    /* fabric clock */
    uDiv = RCC_SYSCLKGetDiv(FABRIC_SC);
    uClkFreq = SystemCoreClock / (uDiv + 1);
    RCC_Clocks->FCLK_Frequency = uClkFreq;

    /* ipcore clock */
    uDiv = RCC_SYSCLKGetDiv(IPCORE_SC);
    uClkFreq = SystemCoreClock / (uDiv + 1);
    RCC_Clocks->IPCLK_Frequency = uClkFreq;

    /* ipcore clock */
    uDiv = RCC_SYSCLKGetDiv(DDR_SC);
    uClkFreq = SystemCoreClock / (uDiv + 1);
    RCC_Clocks->DDRCLK_Frequency = uClkFreq;
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

void RCC_APBPeriphResetCmd(APBSYS_TypeDef *RCC_APBPeriph, ResetStatus NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == SET)
    {
        SET_BIT(RCC_APBPeriph->SR, RCC_APB_SRESET);
    }
    else
    {
        CLEAR_BIT(RCC_APBPeriph->SR, RCC_APB_SRESET);
    }
}

void RCC_APBPeriphClockCmd(APBSYS_TypeDef *RCC_APBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        SET_BIT(RCC_APBPeriph->CGE, RCC_APB_CLKEN);
    }
    else
    {
        CLEAR_BIT(RCC_APBPeriph->CGE, RCC_APB_CLKEN);
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

