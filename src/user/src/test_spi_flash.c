/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_spi_flash.h"
#include "spi_flash.h"

/****************************************************************
  * 函数      : FLASH_FunctionTest1()
  * 参数      : None
  * 返回值     : None
  * 描述      : spi flash功能测试
 ***************************************************************/
TestStatus FLASH_FunctionTest1(void)
{
    uint32_t FlashID = 0;

    /* Get SPI Flash ID */
    FlashID = sFLASH_ReadID();
    if (FlashID != sFLASH_W25Q128FV_ID)
    {     
        DEBUG_ERROR("flash read ID fail.\r\n");

        return FAILED;
    }

    return PASSED;
}

TestStatus FLASH_FunctionTest2(void)
{
    uint8_t TxBuf[] = "ACU SPI Test: communication with an SPI_FLASH.";
    uint8_t RxBuf[COUNT_OF(TxBuf) - 1] = {0};
    uint8_t BufSize = COUNT_OF(TxBuf) - 1;

    /* Erase write test */
    sFLASH_EraseSector(TEST_FLASH_SECTOR_ERASE);
    sFLASH_WriteBuffer(TxBuf, TEST_FLASH_WRITE_ADDR, BufSize);
    sFLASH_ReadBuffer(RxBuf, TEST_FLASH_READ_ADDR, BufSize);

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, BufSize) == FAILED)
    {
        DEBUG_ERROR("flash write data fail.\r\n");

        return FAILED;
    }

    return PASSED;
}

TestStatus FLASH_FunctionTest3(void)
{
    uint8_t Index = 0;
    uint8_t TxBuf[] = "ACU SPI Test: communication with an SPI_FLASH.";
    uint8_t RxBuf[COUNT_OF(TxBuf) - 1] = {0};
    uint8_t BufSize = COUNT_OF(TxBuf) - 1;
         
    /* Erase write test */
    sFLASH_EraseSector(TEST_FLASH_SECTOR_ERASE);
    sFLASH_WriteBuffer(TxBuf, TEST_FLASH_WRITE_ADDR, BufSize);
    sFLASH_ReadBuffer(RxBuf, TEST_FLASH_READ_ADDR, BufSize);

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, BufSize) == FAILED)
    {
        DEBUG_ERROR("flash write data fail.\r\n");

        return FAILED;
    }

    /* Erase Test */
    sFLASH_EraseSector(TEST_FLASH_SECTOR_ERASE);
    sFLASH_ReadBuffer(RxBuf, TEST_FLASH_READ_ADDR, BufSize);
    for (Index = 0; Index < BufSize; Index++)
    {
        if (RxBuf[Index] != 0xFF)
        {
            DEBUG_ERROR("flash erase fail.\r\n");

            return FAILED;
        }
    }

    return PASSED;
}

TestStatus FLASH_FunctionTest4(void)
{
    return PASSED;
}

