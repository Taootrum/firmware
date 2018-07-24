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
    {"FLASH_InterfaceTest7", FLASH_InterfaceTest7},
    {"FLASH_InterfaceTest8", FLASH_InterfaceTest8}
};

static ALLCASE I2C_AllCases[] = {
    {"I2C_FunctionTest1", I2C_FunctionTest1},
    {"I2C_FunctionTest2", I2C_FunctionTest2},
    {"I2C_FunctionTest3", I2C_FunctionTest3},
    {"I2C_FunctionTest4", I2C_FunctionTest4},
    {"I2C_FunctionTest5", I2C_FunctionTest5},
    {"I2C_FunctionTest6", I2C_FunctionTest6},
    {"I2C_FunctionTest7", I2C_FunctionTest7},
    {"I2C_FunctionTest8", I2C_FunctionTest8},
    {"I2C_FunctionTest9", I2C_FunctionTest9},
    //{"I2C_FunctionTest10", I2C_FunctionTestX}
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
    ACU_SUITE_TEST(CRU_AllCases);
    ACU_SUITE_TEST(SPI_AllCases);
    ACU_SUITE_TEST(GPIO_AllCases);
    ACU_SUITE_TEST(UART_AllCases);
    ACU_SUITE_TEST(FLASH_AllCases);
    ACU_SUITE_TEST(I2C_AllCases);
    ACU_ALL_TEST_REPORT();
}

