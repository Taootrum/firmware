/*******************************************************************************
  * @file    test.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test.h"

uint32_t g_SuiteCaseCount = 0;
uint32_t g_SuiteSuccessCount = 0;
uint32_t g_SuiteFailCount = 0;
uint32_t g_AllCaseCount = 0;
uint32_t g_AllSuccessCount = 0;
uint32_t g_AllFailCount = 0;

static ALLCASE CRU_AllCases[] = {
#if 1
    {"CRU_InterfaceTest1", CRU_InterfaceTest1},
    {"CRU_InterfaceTest2", CRU_InterfaceTest2},
    {"CRU_InterfaceTest3", CRU_InterfaceTest3},
    {"CRU_InterfaceTest4", CRU_InterfaceTest4},
    {"CRU_InterfaceTest5", CRU_InterfaceTest5},
    {"CRU_InterfaceTest6", CRU_InterfaceTest6},
    {"CRU_InterfaceTest7", CRU_InterfaceTest7},
    {"CRU_InterfaceTest8", CRU_InterfaceTest8},
    {"CRU_InterfaceTest9", CRU_InterfaceTest9},
    {"CRU_InterfaceTest10", CRU_InterfaceTest10},
    {"CRU_InterfaceTest11", CRU_InterfaceTest11},
    {"CRU_InterfaceTest12", CRU_InterfaceTest12},
    {"CRU_InterfaceTest13", CRU_InterfaceTest13},
    {"CRU_InterfaceTest14", CRU_InterfaceTest14},
    {"CRU_InterfaceTest15", CRU_InterfaceTest15},
    {"CRU_InterfaceTest16", CRU_InterfaceTest16},
    {"CRU_InterfaceTest17", CRU_InterfaceTest17}
#else
    {"CRU_InterfaceTest4", CRU_InterfaceTest4},
    {"CRU_InterfaceTest5", CRU_InterfaceTest5},
    {"CRU_InterfaceTest6", CRU_InterfaceTest6},
    {"CRU_InterfaceTest7", CRU_InterfaceTest7},
    {"CRU_InterfaceTest8", CRU_InterfaceTest8},
    {"CRU_InterfaceTest9", CRU_InterfaceTest9},
    {"CRU_InterfaceTest10", CRU_InterfaceTest10},
    {"CRU_InterfaceTest11", CRU_InterfaceTest11},
    {"CRU_InterfaceTest12", CRU_InterfaceTest12},
    {"CRU_InterfaceTest13", CRU_InterfaceTest13},
    {"CRU_InterfaceTest14", CRU_InterfaceTest14},
    {"CRU_InterfaceTest15", CRU_InterfaceTest15},
    {"CRU_InterfaceTest16", CRU_InterfaceTest16},
    {"CRU_InterfaceTest17", CRU_InterfaceTest17}
#endif
};

static ALLCASE SPI_AllCases[] = {
    {"SPI_InterfaceTest1", SPI_InterfaceTest1},
    {"SPI_InterfaceTest2", SPI_InterfaceTest2},
    {"SPI_InterfaceTest3", SPI_InterfaceTest3},
    {"SPI_InterfaceTest4", SPI_InterfaceTest4},
    {"SPI_InterfaceTest5", SPI_InterfaceTest5},
    {"SPI_InterfaceTest6", SPI_InterfaceTest6},
    {"SPI_InterfaceTest7", SPI_InterfaceTest7},
    {"SPI_InterfaceTest8", SPI_InterfaceTest8}
};

static ALLCASE GPIO_AllCases[] = {
    {"GPIO_InterfaceTest1", GPIO_InterfaceTest1},
    {"GPIO_InterfaceTest2", GPIO_InterfaceTest2},
    {"GPIO_InterfaceTest3", GPIO_InterfaceTest3},
    {"GPIO_InterfaceTest4", GPIO_InterfaceTest4},
    {"GPIO_InterfaceTest5", GPIO_InterfaceTest5},
    {"GPIO_InterfaceTest6", GPIO_InterfaceTest6}
};

static ALLCASE UART_AllCases[] = {
    {"UART_InterfaceTest1", UART_InterfaceTest1},
    {"UART_InterfaceTest2", UART_InterfaceTest2},
    {"UART_InterfaceTest3", UART_InterfaceTest3},
    {"UART_InterfaceTest4", UART_InterfaceTest4},
    {"UART_InterfaceTest5", UART_InterfaceTest5},
    {"UART_InterfaceTest6", UART_InterfaceTest6},
    {"UART_InterfaceTest7", UART_InterfaceTest7},
    {"UART_InterfaceTest8", UART_InterfaceTest8}
};

static ALLCASE FLASH_AllCases[] = {
    {"FLASH_InterfaceTest1", FLASH_InterfaceTest1},
    {"FLASH_InterfaceTest2", FLASH_InterfaceTest2},
#ifndef ACU_SIM
    {"FLASH_InterfaceTest3", FLASH_InterfaceTest3},
    {"FLASH_InterfaceTest4", FLASH_InterfaceTest4},
    {"FLASH_InterfaceTest5", FLASH_InterfaceTest5},
#endif
    {"FLASH_InterfaceTest6", FLASH_InterfaceTest6},
    {"FLASH_InterfaceTest7", FLASH_InterfaceTest7}
};

static ALLCASE I2C_AllCases[] = {
    {"I2C_FunctionTest1", I2C_FunctionTest1},
    {"I2C_FunctionTest2", I2C_FunctionTest2},
    {"I2C_FunctionTest3", I2C_FunctionTest3},
    {"I2C_FunctionTest4", I2C_FunctionTest4},
#ifdef ACU_SIM
    {"I2C_FunctionTest5", I2C_FunctionTest5},
    {"I2C_FunctionTest6", I2C_FunctionTest6},
    {"I2C_FunctionTest7", I2C_FunctionTest7},
    {"I2C_FunctionTest8", I2C_FunctionTest8},
#endif
    {"I2C_FunctionTest9", I2C_FunctionTest9}
};

static ALLCASE PVT_AllCases[] = {
    {"PVT_FunctionTest1", PVT_FunctionTest1},
    {"PVT_FunctionTest2", PVT_FunctionTest2},
    {"PVT_FunctionTest3", PVT_FunctionTest3},
    {"PVT_FunctionTest4", PVT_FunctionTest4},
    {"PVT_FunctionTest5", PVT_FunctionTest5},
    {"PVT_FunctionTest6", PVT_FunctionTest6}
};

static ALLCASE EFUSE_AllCases[] = {
    {"EFUSE_FunctionTest1", EFUSE_FunctionTest1},
    {"EFUSE_FunctionTest2", EFUSE_FunctionTest2}
};

static ALLCASE TIMER_AllCases[] = {
    {"TIMER_FunctionTest1", TIMER_FunctionTest1},
    {"TIMER_FunctionTest2", TIMER_FunctionTest2},
    {"TIMER_FunctionTest3", TIMER_FunctionTest3},
    {"TIMER_FunctionTest4", TIMER_FunctionTest4}
};

static ALLCASE WDT_AllCases[] = {
    {"WDT_FunctionTest1", WDT_FunctionTest1},
    {"WDT_FunctionTest2", WDT_FunctionTest2},
    {"WDT_FunctionTest3", WDT_FunctionTest3},
    {"WDT_FunctionTest4", WDT_FunctionTest4},
    {"WDT_FunctionTest5", WDT_FunctionTest5}
};

static ALLCASE PCIE_AllCases[] = {
    {"PCIE_FunctionTest1", PCIE_FunctionTest1},
    {"PCIE_FunctionTest2", PCIE_FunctionTest2},
    {"PCIE_FunctionTest3", PCIE_FunctionTest3},
    {"PCIE_FunctionTest4", PCIE_FunctionTest4},
    {"PCIE_FunctionTest5", PCIE_FunctionTest5},
    {"PCIE_FunctionTest6", PCIE_FunctionTest6}
};

static ALLCASE INT_AllCases[] = {
    {"INT_FunctionTest1", INT_FunctionTest1},
    {"INT_FunctionTest2", INT_FunctionTest2}
};
    
static ALLCASE DDR_AllCases[] = {
#ifdef ACU_DDR3
    {"DDR_FunctionTest1", DDR_FunctionTest1},
#endif
#ifdef ACU_DDR4
    {"DDR_FunctionTest2", DDR_FunctionTest2},
#endif
    {"DDR_FunctionTest3", DDR_FunctionTest3}
};

static ALLCASE CU_AllCases[] = {
    {"CU_FunctionTest1", CU_FunctionTest1},
    {"CU_FunctionTest2", CU_FunctionTest2},
#ifndef ACU_SIM
    {"CU_FunctionTest3", CU_FunctionTest3}
#endif
};

/****************************************************************
  * 函数      : ACU_SuiteTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : 单元测试
 ***************************************************************/
static void ACU_SuiteTest(PALLCASE pSuiteAllCase)
{
    TestStatus CaseStatus = FAILED;
    uint32_t Count = 0;

    for (Count = 0; Count < g_SuiteCaseCount; Count++)
    {
        CaseStatus = pSuiteAllCase[Count].pFun();
        if (CaseStatus == FAILED)
        {
            g_SuiteFailCount++;
            DEBUG_MSG("%s is FAILED. (%d/%d)"LF, 
                        pSuiteAllCase[Count].FunName, Count + 1, g_SuiteCaseCount);
        }
        else
        {
            g_SuiteSuccessCount++;
            DEBUG_MSG("%s is PASSED. (%d/%d)"LF, 
                        pSuiteAllCase[Count].FunName, Count + 1, g_SuiteCaseCount);
        }
    }                
}

/****************************************************************
  * 函数      : ACU_SingleTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : 单例测试
 ***************************************************************/
static void ACU_SingleTest(uint8_t TestNum, PALLCASE pSingleCase)
{
    TestStatus CaseStatus = FAILED;

    CaseStatus = pSingleCase->pFun();
    if (CaseStatus == FAILED)
    {
        DEBUG_MSG("<%2d>:%s TEST CASE FAILED."LF, TestNum, pSingleCase->FunName);
    }
    else
    {
        DEBUG_MSG("<%2d>:%s TEST CASE PASSED."LF, TestNum, pSingleCase->FunName);
    }
}

/****************************************************************
  * 函数      : ACU_HalFuncTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : Hal Test All
 ***************************************************************/
void ACU_HalFuncTest(void)
{
    uint32_t TestNum = 0;//READ_REG(INT_GEN->DATA6);
    
    /* All Cases Testing */
    if (TestNum == 0)
    {
        #if 1
        ACU_SUITE_TEST(CRU_AllCases);
        ACU_SUITE_TEST(SPI_AllCases);
        ACU_SUITE_TEST(GPIO_AllCases);
        ACU_SUITE_TEST(UART_AllCases);
        ACU_SUITE_TEST(FLASH_AllCases);
        ACU_SUITE_TEST(I2C_AllCases);
        ACU_SUITE_TEST(PVT_AllCases);
        ACU_SUITE_TEST(EFUSE_AllCases);
        ACU_SUITE_TEST(TIMER_AllCases);
        ACU_SUITE_TEST(WDT_AllCases);
        ACU_SUITE_TEST(PCIE_AllCases);
        ACU_SUITE_TEST(INT_AllCases);
        
        /* Initialize Fabric Clock */
        DDRC_Init();
        ACU_SUITE_TEST(DDR_AllCases);
        ACU_SUITE_TEST(CU_AllCases);
        #else
        DDRC_Init();
        ACU_SUITE_TEST(CU_AllCases);
        #endif
        ACU_ALL_TEST_REPORT();
        
        if (g_AllCaseCount == g_AllSuccessCount)
        {
            DEBUG_MSG("TEST CASE PASSED."LF LF);
        }
        else
        {
            DEBUG_MSG("TEST CASE FAILED."LF LF);
        }
        
        return;
    }

    /* Single Case Testing */
    uint8_t CaseStepNum = 0;
    uint8_t CruNum = sizeof(CRU_AllCases) / sizeof(CRU_AllCases[0]);
    uint8_t SpiNum = sizeof(SPI_AllCases) / sizeof(SPI_AllCases[0]);
    uint8_t GpioNum = sizeof(GPIO_AllCases) / sizeof(GPIO_AllCases[0]);
    uint8_t UartNum = sizeof(UART_AllCases) / sizeof(UART_AllCases[0]);
    uint8_t FlashNum = sizeof(FLASH_AllCases) / sizeof(FLASH_AllCases[0]);
    uint8_t I2cNum = sizeof(I2C_AllCases) / sizeof(I2C_AllCases[0]);
    uint8_t PvtNum = sizeof(PVT_AllCases) / sizeof(PVT_AllCases[0]);
    uint8_t EfuseNum = sizeof(EFUSE_AllCases) / sizeof(EFUSE_AllCases[0]);
    uint8_t TimerNum = sizeof(TIMER_AllCases) / sizeof(TIMER_AllCases[0]);
    uint8_t WdtNum = sizeof(WDT_AllCases) / sizeof(WDT_AllCases[0]);
    uint8_t PcieNum = sizeof(PCIE_AllCases) / sizeof(PCIE_AllCases[0]);
    uint8_t IntNum = sizeof(INT_AllCases) / sizeof(INT_AllCases[0]);
    uint8_t DDRNum = sizeof(DDR_AllCases) / sizeof(DDR_AllCases[0]);
    uint8_t CUNum = sizeof(CU_AllCases) / sizeof(CU_AllCases[0]);

    if (TestNum <= CaseStepNum + CruNum)
    {
        ACU_SingleTest(TestNum, &CRU_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += CruNum;
    if (TestNum <= CaseStepNum + SpiNum)
    {
        ACU_SingleTest(TestNum, &SPI_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }
    
    CaseStepNum += SpiNum;
    if (TestNum <= CaseStepNum + GpioNum)
    {
        ACU_SingleTest(TestNum, &GPIO_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }
    
    CaseStepNum += GpioNum;
    if (TestNum <= CaseStepNum + UartNum)
    {
        ACU_SingleTest(TestNum, &UART_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += UartNum;
    if (TestNum <= CaseStepNum + FlashNum)
    {
        ACU_SingleTest(TestNum, &FLASH_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += FlashNum;
    if (TestNum <= CaseStepNum + I2cNum)
    {
        ACU_SingleTest(TestNum, &I2C_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += I2cNum;
    if (TestNum <= CaseStepNum + PvtNum)
    {
        ACU_SingleTest(TestNum, &PVT_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += PvtNum;
    if (TestNum <= CaseStepNum + EfuseNum)
    {
        ACU_SingleTest(TestNum, &EFUSE_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += EfuseNum;
    if (TestNum <= CaseStepNum + TimerNum)
    {
        ACU_SingleTest(TestNum, &TIMER_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += TimerNum;
    if (TestNum <= CaseStepNum + WdtNum)
    {
        ACU_SingleTest(TestNum, &WDT_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += WdtNum;
    if (TestNum <= CaseStepNum + PcieNum)
    {
        ACU_SingleTest(TestNum, &PCIE_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += PcieNum;
    if (TestNum <= CaseStepNum + IntNum)
    {
        ACU_SingleTest(TestNum, &INT_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += IntNum;
    if (TestNum <= CaseStepNum + DDRNum)
    {
        DDRC_Init();
        ACU_SingleTest(TestNum, &DDR_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }

    CaseStepNum += DDRNum;
    if (TestNum <= CaseStepNum + CUNum)
    {
        DDRC_Init();
        ACU_SingleTest(TestNum, &CU_AllCases[TestNum - CaseStepNum - 1]);
        return;
    }
}

