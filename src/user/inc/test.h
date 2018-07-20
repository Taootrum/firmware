/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#ifndef __TEST_H
#define __TEST_H

#include "test_cru.h"
#include "test_gpio.h"
#include "test_i2c.h"
#include "test_spi.h"
#include "test_spi_flash.h"
#include "test_timer.h"
#include "test_uart.h"
#include "test_wdg.h"

extern uint32_t g_SuiteCaseCount;
extern uint32_t g_SuiteSuccessCount;
extern uint32_t g_SuiteFailCount;
extern uint32_t g_AllCaseCount;
extern uint32_t g_AllSuccessCount;
extern uint32_t g_AllFailCount;

#define ACU_SUITE_TEST(SuiteCases)\
        do  \
        {   \
            DEBUG_MSG("%s: Functional Testing Start..."LF, #SuiteCases); \
            g_SuiteCaseCount = sizeof(SuiteCases) / sizeof(SuiteCases[0]);  \
            g_SuiteSuccessCount = 0;  \
            g_SuiteFailCount = 0;  \
            ACU_SuiteTest(SuiteCases);  \
            g_AllCaseCount += g_SuiteCaseCount; \
            g_AllSuccessCount += g_SuiteSuccessCount;   \
            g_AllFailCount += g_SuiteFailCount; \
            DEBUG_MSG("%s: Total:%d, Success:%d, Fail:%d"LF LF,  \
                        #SuiteCases, g_SuiteCaseCount, g_SuiteSuccessCount, g_SuiteFailCount);  \
        } while (0)

#define ACU_ALL_TEST_REPORT()\
        do  \
        {   \
            DEBUG_MSG("ACU REPORT:All Cases, Total:%d, Success:%d, Fail:%d"LF, \
                        g_AllCaseCount, g_AllSuccessCount, g_AllFailCount); \
        } while (0)

typedef struct AllCase {
    char *FunName;
    TestStatus (*pFun)(void);
}ALLCASE, *PALLCASE;

void ACU_HalFuncTest(void);

#endif

