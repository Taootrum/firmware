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
    {"CRU_FunctionTest1", CRU_FunctionTest1},
    {"CRU_FunctionTest2", CRU_FunctionTest2},
    {"CRU_FunctionTest3", CRU_FunctionTest3}
};

static ALLCASE SPI_AllCases[] = {
    {"SPI_FunctionTest1", SPI_FunctionTest1},
    {"SPI_FunctionTest2", SPI_FunctionTest2},
    {"SPI_FunctionTest3", SPI_FunctionTest3},
    {"SPI_FunctionTest4", SPI_FunctionTest4},
};

static ALLCASE GPIO_AllCases[] = {
    {"GPIO_FunctionTest1", GPIO_FunctionTest1},
    {"GPIO_FunctionTest2", GPIO_FunctionTest2},
    {"GPIO_FunctionTest3", GPIO_FunctionTest3},
    {"GPIO_FunctionTest4", GPIO_FunctionTest4},
};

static ALLCASE UART_AllCases[] = {
    {"UART_FunctionTest1", UART_FunctionTest1},
    {"UART_FunctionTest2", UART_FunctionTest2},
    {"UART_FunctionTest3", UART_FunctionTest3},
    {"UART_FunctionTest4", UART_FunctionTest4},
};

static ALLCASE FLASH_AllCases[] = {
    {"FLASH_FunctionTest1", FLASH_FunctionTest1},
    {"FLASH_FunctionTest2", FLASH_FunctionTest2},
    {"FLASH_FunctionTest3", FLASH_FunctionTest3},
    {"FLASH_FunctionTest4", FLASH_FunctionTest4},
};

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
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
            DEBUG_MSG("%s is FAILED.  (%d/%d)\r\n", 
                        pSuiteAllCase[Count].FunName, Count + 1, g_SuiteCaseCount);
        }
        else
        {
            g_SuiteSuccessCount++;
            DEBUG_MSG("%s is SUCCESS. (%d/%d)\r\n", 
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
    ACU_ALL_TEST_REPORT();
}

