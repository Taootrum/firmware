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
    {"CRU_InterfaceTest17", CRU_InterfaceTest17},
    {"CRU_InterfaceTest18", CRU_InterfaceTest18},
    {"CRU_InterfaceTest19", CRU_InterfaceTest19}
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
    {"GPIO_InterfaceTest3", GPIO_InterfaceTest5},
    {"GPIO_InterfaceTest4", GPIO_InterfaceTest6}
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
#ifndef SIM_ENV
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
#ifdef SIM_ENV
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
            DEBUG_MSG("%s is FAILED.  (%d/%d)"LF, 
                        pSuiteAllCase[Count].FunName, Count + 1, g_SuiteCaseCount);
        }
        else
        {
            g_SuiteSuccessCount++;
            DEBUG_MSG("%s is SUCCESS. (%d/%d)"LF, 
                        pSuiteAllCase[Count].FunName, Count + 1, g_SuiteCaseCount);
        }
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
#if 1
    ACU_SUITE_TEST(CRU_AllCases);
    ACU_SUITE_TEST(SPI_AllCases);
    ACU_SUITE_TEST(GPIO_AllCases);
    ACU_SUITE_TEST(UART_AllCases);
    ACU_SUITE_TEST(FLASH_AllCases);
    ACU_SUITE_TEST(I2C_AllCases);
    ACU_SUITE_TEST(PVT_AllCases);
    ACU_SUITE_TEST(TIMER_AllCases);
    ACU_SUITE_TEST(WDT_AllCases);
    ACU_SUITE_TEST(PCIE_AllCases);
#else
    ACU_SUITE_TEST(TIMER_AllCases);
    ACU_SUITE_TEST(WDT_AllCases);
#endif
    ACU_ALL_TEST_REPORT();
}

