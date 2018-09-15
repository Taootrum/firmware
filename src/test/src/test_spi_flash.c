/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_spi_flash.h"
#include "spi_flash.h"

uint8_t TxBuf[TEST_BUF_LEN] = {0};
uint8_t RxBuf[TEST_BUF_LEN] = {0};

/****************************************************************
* 函数      : FLASH_InterfacesTestx()
* 参数      : None
* 返回值     : TRUE or FALSE
* 描述      : FLASH interfaces test cases.
***************************************************************/
/* sFLASH_DeInit() */
TestStatus FLASH_InterfaceTest1(void)
{
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;

    /* reset */
    sFLASH_DeInit();
    
    /* reset & check */
    result &= CHECK_REG_RESERVED(sFLASH_SPI->CR0, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->CR1, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->DR, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->SR, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->CPSR, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->RIS, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->MIS, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->ICR, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->DMACR, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->FIFOTH, 0x0);
    if (result != TRUE)
    {
        DEBUG_ERROR("SPI_DeInit fail.");
        ret = FAILED;
    }
    
    sFLASH_Init();

    return ret;
}
/* sFLASH_Init() */
TestStatus FLASH_InterfaceTest2(void)
{
    TestStatus ret = PASSED;
    BoolStatus result = TRUE;

    RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
    RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);

    /* init */
    sFLASH_Init();
    result &= CHECK_REG_RESERVED(sFLASH_SPI->CR0, 0x7);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->CR1, SPI_ENABLE);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->DR, 0x0);
    //result &= CHECK_REG_RESERVED(sFLASH_SPI->CPSR, SPI_CPSDVSR);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->IMSC, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->ICR, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->DMACR, 0x0);
    result &= CHECK_REG_RESERVED(sFLASH_SPI->FIFOTH, ((SPI_FIFO_TX_TH - 1) << 8) | (SPI_FIFO_TX_TH - 1));
    if (result != TRUE)
    {
        DEBUG_ERROR("SPI_Init fail.");
        ret = FAILED;
    }
    
    return ret;
}

/* sFLASH_EraseSector() */
TestStatus FLASH_InterfaceTest3(void)
{
    uint32_t Index = 0;

    memset(TxBuf, 0x55, TEST_BUF_LEN);
    memset(RxBuf, 0x0, TEST_BUF_LEN);

    /* Erase write test */
    sFLASH_EraseSector(TEST_FLASH_SECTOR_ADDR);
    sFLASH_WriteBuffer(TxBuf, TEST_FLASH_SECTOR_ADDR, TEST_BUF_LEN);
    sFLASH_ReadBuffer(RxBuf, TEST_FLASH_SECTOR_ADDR, TEST_BUF_LEN);

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, TEST_BUF_LEN) == FAILED)
    {
        DEBUG_ERROR("flash write data fail.");
        return FAILED;
    }

    /* Erase Test */
    sFLASH_EraseSector(TEST_FLASH_SECTOR_ADDR);
    sFLASH_ReadBuffer(RxBuf, TEST_FLASH_SECTOR_ADDR, TEST_BUF_LEN);
    for (Index = 0; Index < TEST_BUF_LEN; Index++)
    {
        if (RxBuf[Index] != 0xFF)
        {
            DEBUG_ERROR("flash erase fail.");
            return FAILED;
        }
    }

    return PASSED;
}

/* sFLASH_EraseBlock() */
TestStatus FLASH_InterfaceTest4(void)
{
    uint32_t Index = 0, Index_sector = 0;

    memset(TxBuf, 0x55, TEST_BUF_LEN);
    memset(RxBuf, 0x0, TEST_BUF_LEN);
    
    /* Erase write test */
    sFLASH_EraseBlock(TEST_FLASH_BLOCK_ADDR);
    for (Index = 0; Index < SPI_FLASH_BLOCK_SIZE / TEST_BUF_LEN; Index++)
    {
        sFLASH_WriteBuffer(TxBuf, TEST_FLASH_BLOCK_ADDR + Index * TEST_BUF_LEN, TEST_BUF_LEN);
        sFLASH_ReadBuffer(RxBuf, TEST_FLASH_BLOCK_ADDR + Index * TEST_BUF_LEN, TEST_BUF_LEN);

        /* Check the correctness of written dada */
        if (Buffercmp(TxBuf, RxBuf, TEST_BUF_LEN) == FAILED)
        {
            DEBUG_ERROR("flash write data fail.");
            return FAILED;
        }
    }
    
    /* Erase Test */
    sFLASH_EraseBlock(TEST_FLASH_BLOCK_ADDR);
    for (Index_sector = 0; Index_sector < SPI_FLASH_BLOCK_SIZE / TEST_BUF_LEN; Index_sector++)
    {
        sFLASH_ReadBuffer(RxBuf, TEST_FLASH_BLOCK_ADDR + Index_sector * TEST_BUF_LEN, TEST_BUF_LEN);
        for (Index = 0; Index < TEST_BUF_LEN; Index++)
        {
            if (RxBuf[Index] != 0xFF)
            {
                DEBUG_ERROR("flash erase fail.");
                return FAILED;
            }
        }
    }
    
    return PASSED;
}

/* sFLASH_EraseBulk() */
TestStatus FLASH_InterfaceTest5(void)
{
    uint32_t Index = 0, Index_sector = 0;

    memset(TxBuf, 0x55, TEST_BUF_LEN);
    memset(RxBuf, 0x0, TEST_BUF_LEN);
    
    /* Erase write test */
    sFLASH_EraseBulk();
    for (Index = 0; Index < SPI_FLASH_CHIP_SIZE / TEST_BUF_LEN; Index++)
    {
        sFLASH_WriteBuffer(TxBuf, Index * TEST_BUF_LEN, TEST_BUF_LEN);
        sFLASH_ReadBuffer(RxBuf, Index * TEST_BUF_LEN, TEST_BUF_LEN);

        /* Check the correctness of written dada */
        if (Buffercmp(TxBuf, RxBuf, TEST_BUF_LEN) == FAILED)
        {
            DEBUG_ERROR("flash write data fail.");
            return FAILED;
        }
    }
    
    /* Erase Test */
    sFLASH_EraseBulk();
    for (Index_sector = 0; Index_sector < SPI_FLASH_CHIP_SIZE / TEST_BUF_LEN; Index_sector++)
    {
        sFLASH_ReadBuffer(RxBuf, Index_sector * TEST_BUF_LEN, TEST_BUF_LEN);
        for (Index = 0; Index < TEST_BUF_LEN; Index++)
        {
            if (RxBuf[Index] != 0xFF)
            {
                DEBUG_ERROR("flash erase fail.");
                return FAILED;
            }
        }
    }
    
    return PASSED;
}

/* sFLASH_ReadID() */
TestStatus FLASH_InterfaceTest6(void)
{
    uint32_t FlashID = 0;
    
    /* Get SPI Flash ID */
    FlashID = sFLASH_ReadID();
    if (FlashID != SPI_FLASH_ID)
    {     
        DEBUG_ERROR("flash read ID fail.");
        return FAILED;
    }

    return PASSED;
}

/* sFLASH_WriteBuffer() 
    sFLASH_ReadBuffer() */
TestStatus FLASH_InterfaceTest7(void)
{
    uint8_t TxBuf[] = "Access a SPI_Flash.";
    uint8_t RxBuf[COUNT_OF(TxBuf) - 1] = {0};
    uint8_t BufSize = COUNT_OF(TxBuf) - 1;
    
    /* Erase write test */
    sFLASH_EraseSector(TEST_FLASH_SECTOR_ADDR);
    sFLASH_WriteBuffer(TxBuf, TEST_FLASH_SECTOR_ADDR, BufSize);
    sFLASH_ReadBuffer(RxBuf, TEST_FLASH_SECTOR_ADDR, BufSize);

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, BufSize) == FAILED)
    {
        DEBUG_ERROR("flash write data fail.");
        return FAILED;
    }

    return PASSED;
}

