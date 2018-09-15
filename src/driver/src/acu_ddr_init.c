#include "acu_ddr_init.h"

static void DDRC_ClockInit(void)
{
    PLL_InitTypeDef PLL_Init;
    LockStatus PLL_LockStatus = UnLock;
    __IO uint32_t StartUpCounter = 0;
    uint32_t DivValue = 0;

    /* Initialize CPLL 2133MHz for DDR3 / 2400MHz for DDR4  */
    PLL_Init.PLLInputClock = XTAL;
    PLL_Init.PLLOutputClock = CPLL_CLK_FREQ;
    PLL_Init.Divr = CPLL_DIVR;
    PLL_Init.Divf = CPLL_DIVF;
    PLL_Init.Divq = PLL_DIVQ_2;
    RCC_PLLConfig(CPLL_CLK, &PLL_Init);
    do
    {
        PLL_LockStatus = RCC_PLLGetLockStatus(CPLL_CLK);
        StartUpCounter++;  
    } while((PLL_LockStatus == UnLock) && (StartUpCounter < PLL_LOCK_TIMEOUT));
    RCC_PLLCmd(CPLL_CLK, ENABLE);

    /* Initialize DPLL 2133MHz for DDR3 / 2400MHz for DDR4 */
    PLL_Init.PLLInputClock = XTAL;
    PLL_Init.PLLOutputClock = DPLL_CLK_FREQ;
    PLL_Init.Divr = DPLL_DIVR;
    PLL_Init.Divf = DPLL_DIVF;
    PLL_Init.Divq = PLL_DIVQ_2;
    RCC_PLLConfig(DPLL_CLK, &PLL_Init);
    StartUpCounter = 0;
    do
    {
        PLL_LockStatus = RCC_PLLGetLockStatus(DPLL_CLK);
        StartUpCounter++;  
    } while((PLL_LockStatus == UnLock) && (StartUpCounter < PLL_LOCK_TIMEOUT));
    RCC_PLLCmd(DPLL_CLK, ENABLE);

    /* Initialize DDR Clock */
    RCC_SYSCLKSetSource(DDR_CLK, SYSCLK_SOURCE_CPLL);
    DivValue = CPLL_CLK_FREQ / DDR_CLK_FREQ - 1;
    RCC_SYSCLKSetDiv(DDR_CLK, DivValue);
    RCC_SYSCLKCmd(DDR_CLK, ENABLE);

    /* Initialize DDR1 Clock */
    RCC_SYSCLKSetSource(DDR1_CLK, SYSCLK_SOURCE_DPLL);
    DivValue = DPLL_CLK_FREQ / DDR1_CLK_FREQ - 1;
    RCC_SYSCLKSetDiv(DDR1_CLK, DivValue);
    RCC_SYSCLKCmd(DDR1_CLK, ENABLE);
}

static void DDRC_CommonInit(void)
{
    uint8_t i = 0;
    uint32_t TempSet = 0;
    
    /* DDRC read dram_sel config */
    WRITE_REG(RST_SC->DDR_RCFG, 0x0);

    /* DDRC write dram_wcfg config */
    for (i = 0; i < DDRC_NUMBER; i++) 
    {
        TempSet |= (0x1 << i);
    }
    WRITE_REG(RST_SC->DDR_WCFG, TempSet);

    /* DDRC system management config */
    for (i = 0; i < DDRC_NUMBER; i++) 
    {
        /* set pub address non-compress mode */
        WRITE32(0x4008c024 + (i * 0x400), 0x4);
        /* release clock */
        WRITE32(0x4008c004 + (i * 0x400), 0x3f);
        /* release pubphy pwrokin */
        WRITE32(0x4008c000 + (i * 0x400), 0x1f);
        /* release umctl2 apb/debug reset */
        WRITE32(0x4008c000 + (i * 0x400), 0x13);
    }
}

void DDRC_Init(void)
{
    DDRC_ClockInit();
    DDRC_CommonInit();
    #if defined(ACU_DDR3)
    ddrc_x8_ddr3_init(DDRC_NUMBER);
    #elif defined(ACU_DDR4)
    ddrc_x8_ddr4_init(DDRC_NUMBER);
    #endif
}

