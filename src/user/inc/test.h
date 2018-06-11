/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#ifndef __TEST_H
#define __TEST_H

#include "acu.h"

extern int acu_run;
extern int acu_assert;
extern int acu_fail;
extern int acu_status;
extern int acu_all_fail;

/* Maximum length of last message */
#define ACU_MESSAGE_LEN 1024


/* Definitions */
#define ACU_SAFE_BLOCK(block) do {\
        block\
    } while(0)

/* Test suite */
#define ACU_RUN_SUITE(suite_name) \
    ACU_SAFE_BLOCK(\
                    acu_run = 0;\
                    acu_assert = 0;\
                    acu_fail = 0;\
                    acu_status = 0;  \
                    suite_name();\
                    acu_all_fail += acu_fail;\
                    DEBUG_MSG("[ACU REPORT] %d tests, %d failures out of %d checks\n\n",\
                          acu_run, acu_fail, acu_assert);\
                  )

/* Test runner */
#define ACU_RUN_TEST(test) \
    ACU_SAFE_BLOCK(\
                    acu_status = 0;\
                    test();\
                    acu_run++;\
                    if (acu_status) {\
                        acu_fail++;\
                        DEBUG_MSG(" Fail\n");\
                    }\
                  )

/* Assertions */
#define ACU_CHECK(test) \
    ACU_SAFE_BLOCK(\
                    acu_assert++;\
                    if (!(test)) {\
                        DEBUG_MSG("%s failed:\n%s: %d: %s\n",   \
                           __func__, __FILE__, __LINE__, #test);\
                        acu_status = 1;\
                        ASSERT(FALSE);\
                        return;\
                    } else {\
                        DEBUG_MSG(".");\
                    }\
                  )


void ACU_FirmWareTest(void);

#endif
