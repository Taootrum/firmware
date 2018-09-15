/*******************************************************************************
  * @file    test_efuse.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    06-September-2018
  * @brief   ACU EFUSE Function. 
 ******************************************************************************/
#include "test_efuse.h"

/****************************************************************
  * 函数      : PVT_FunctionTestX()
  * 参数      : None
  * 返回值     : TRUE or FALSE
  * 描述      : pvt function test cases.
 ***************************************************************/
/* poll */
TestStatus EFUSE_FunctionTest1(void)
{
    uint32_t TxData[32] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
                           0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20};
    uint32_t RxData[32] = {0x00};
    TestStatus ret = PASSED;

    EFUSE_Init();
    EFUSE_WriteData(0, TxData, 32);
    EFUSE_ReadData(0, RxData, 32);
    if (Buffercmp((uint8_t *)TxData, (uint8_t *)RxData, 32 * 4) == FAILED)
    {
        DEBUG_ERROR("EFUSE poll write and read fail.");
        ret = FAILED;
    }
    EFUSE_DeInit();
    
    return ret;
}

/* Interrupt */
TestStatus EFUSE_FunctionTest2(void)
{
    TestStatus ret = PASSED;

    EFUSE_Init();
    EFUSE_ITConfig(ENABLE);
    NVIC_EnableIRQ(PVT_IRQn);

    EFUSE_DeInit();
    EFUSE_ITConfig(DISABLE);
    NVIC_DisableIRQ(PVT_IRQn);

    return ret;
}

