/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_cru.h"

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
TestStatus CRU_FunctionTest1(void)
{
    return PASSED;
}

TestStatus CRU_FunctionTest2(void)
{
    return FAILED;
}

TestStatus CRU_FunctionTest3(void)
{
    return PASSED;
}


