/*******************************************************************************
  * @file    spi_flash.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Flash Application Function. 
 ******************************************************************************/
#include "spi_flash.h"

/****************************************************************
  * 函数      : sFlash_CopyBinToIRAM()
  * 参数      : None
  * 返回值     : None
  * 描述      : 拷贝fw固件到iram中
 ***************************************************************/
uint32_t sFlash_ReadAPPFlag(void)
{
    return 0;
}

/****************************************************************
  * 函数      : sFlash_CopyBinToIRAM()
  * 参数      : None
  * 返回值     : None
  * 描述      : 拷贝fw固件到iram中
 ***************************************************************/
uint32_t sFlash_ReadAPPSize(void)
{
    return 0;
}

/****************************************************************
  * 函数      : sFlash_CopyBinToIRAM()
  * 参数      : None
  * 返回值     : None
  * 描述      : 拷贝fw固件到iram中
 ***************************************************************/
BoolStatus sFlash_CopyBinToIRAM(void)
{
    return TRUE;
}

/****************************************************************
  * 函数      : sFlash_FunctionTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : spi flash功能测试
 ***************************************************************/
void sFlash_FunctionTest(void)
{
    uint8_t Index = 0;
    uint32_t FlashID = 0;
    uint8_t TxBuf[] = "ACU SPI Test: communication with an SPI_FLASH.";
    uint8_t RxBuf[COUNT_OF(TxBuf) - 1] = {0};
    uint8_t BufSize = COUNT_OF(TxBuf) - 1;
    volatile TestStatus Status1 = FAILED, Status2 = PASSED;

    DEBUG_MSG("spi flash test start!\n");

    /* Get SPI Flash ID */
    FlashID = sFLASH_ReadID();

    if (FlashID == SPI_FLASH_ID)
    {    
        sFLASH_ReadBuffer((uint8_t *)&FlashID, 0, 4);
        
        /* Erase write test */
        sFLASH_EraseSector(TEST_FLASH_SECTOR_ERASE);
        sFLASH_WriteBuffer(TxBuf, TEST_FLASH_WRITE_ADDR, BufSize);
        sFLASH_ReadBuffer(RxBuf, TEST_FLASH_READ_ADDR, BufSize);

        /* Check the correctness of written dada */
        Status1 = Buffercmp(TxBuf, RxBuf, BufSize);
        if (Status1 == FAILED)
        {
            DEBUG_MSG("spi flash write data fail.\n");
        }
        else 
        {
            DEBUG_MSG("spi flash write data OK.\n");
        }

        /* Erase Test */
        sFLASH_EraseSector(TEST_FLASH_SECTOR_ERASE);
        sFLASH_ReadBuffer(RxBuf, TEST_FLASH_READ_ADDR, BufSize);
        for (Index = 0; Index < BufSize; Index++)
        {
            if (RxBuf[Index] != 0xFF)
            {
                Status2 = FAILED;
            }
        }
        
        if (Status2 == FAILED)
        {
            DEBUG_MSG("spi flash erase fail.\n");
        }
        else 
        {
            DEBUG_MSG("spi flash erase OK.\n");
        }
    }
    else
    {
        DEBUG_PRINT_REG(FlashID);
    }
    
    DEBUG_MSG("spi flash test end!\n");
}

