/*******************************************************************************
  * @file    spi_flash.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Flash Application Function. 
 ******************************************************************************/
#include "spi_flash.h"

/****************************************************************
  * 函数      : Hal_FlashWriteBuffer()
  * 参数      : pBuffer   ：输入buffer
              WriteAddr ：写入地址
              NumWrite  ：数据长度
  * 返回值     : None
  * 描述      : 向Flash写入数据流

  ???不够完善,不够高效，后期测试
 ***************************************************************/
void Hal_FlashWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumWrite)
{
    uint8_t *pSectorBuf = (uint8_t *)ACU_GLOBAL_BUF_ADDR;
    uint8_t *pNext = pBuffer;
    uint16_t SectorNum = 0,SectorMod = 0;
    uint32_t SectorHeadAddr = 0, SectorProgAddr = 0;

    /* 地址超出范围自动限制 */
    if (WriteAddr > SPI_FLASH_CHIP_SIZE)
    {
        WriteAddr = SPI_FLASH_CHIP_SIZE;
    }

    /* 地址+Num超出范围，写入有效Num数据 */
    if (WriteAddr + NumWrite > SPI_FLASH_CHIP_SIZE)
    {
        NumWrite = SPI_FLASH_CHIP_SIZE - WriteAddr;
    }

    /* calc sector head/prog addr and program sector_num */
    SectorHeadAddr = WriteAddr & (~(SPI_FLASH_SUBSECTOR_SIZE - 1));
    SectorProgAddr = WriteAddr & (SPI_FLASH_SUBSECTOR_SIZE - 1);
    SectorNum = (SectorProgAddr + NumWrite) / SPI_FLASH_SUBSECTOR_SIZE;
    SectorMod = (SectorProgAddr + NumWrite) % SPI_FLASH_SUBSECTOR_SIZE;

    SectorNum += 1;
    while (SectorNum--)
    {
        /* final sector check SectorMod whether vaild */
        if (!SectorNum && !SectorMod)
        {
            break;
        }

        /* buffer the sector data */
        sFLASH_ReadBuffer(pSectorBuf, SectorHeadAddr, SPI_FLASH_SUBSECTOR_SIZE);
        
        /* copy pBuffer to sector buffer */
        if (SectorNum)
        {
            memcpy(pSectorBuf + SectorProgAddr, pNext, SPI_FLASH_SUBSECTOR_SIZE - SectorProgAddr);
        }
        else
        {
            memcpy(pSectorBuf + SectorProgAddr, pNext, SectorMod - SectorProgAddr);
        }
        
        /* erase the sector */
        sFLASH_EraseSector(SectorHeadAddr);
        
        /* write to sector */
        sFLASH_WriteBuffer(pSectorBuf, SectorHeadAddr, SPI_FLASH_SUBSECTOR_SIZE);

        /* set offset */
        SectorHeadAddr += SPI_FLASH_SUBSECTOR_SIZE;
        pNext += SPI_FLASH_SUBSECTOR_SIZE - SectorProgAddr;
        SectorProgAddr = 0;
    }
}

/****************************************************************
  * 函数      : Hal_FlashReadBuffer()
  * 参数      : pBuffer   ：输入buffer
              WriteAddr ：读取地址
              NumWrite  ：数据长度
  * 返回值     : None
  * 描述      : 从Flash读取数据流
 ***************************************************************/
void Hal_FlashReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumRead)
{
    uint16_t BlockNum = 0, BlockMod = 0;
    uint16_t MaxBlockRead = SPI_FLASH_BLOCK_SIZE - 1;
    
    /* 地址超出范围自动限制 */
    if (ReadAddr > SPI_FLASH_CHIP_SIZE)
    {
        ReadAddr = SPI_FLASH_CHIP_SIZE;
    }

    /* 地址+Num超出范围，读取有效Num数据 */
    if (ReadAddr + NumRead > SPI_FLASH_CHIP_SIZE)
    {
        NumRead = SPI_FLASH_CHIP_SIZE - ReadAddr;
    }
    
    BlockNum = NumRead / MaxBlockRead;
    while (BlockNum--)
    {
        sFLASH_ReadBuffer(pBuffer, ReadAddr, MaxBlockRead);
        pBuffer += MaxBlockRead;
        ReadAddr += MaxBlockRead;
    }

    BlockMod = NumRead % MaxBlockRead;
    if (BlockMod)
    {
        sFLASH_ReadBuffer(pBuffer, ReadAddr, BlockMod);
    }
}

/****************************************************************
  * 函数      : Hal_FlashWriteWord()
  * 参数      : ReadAddr: 需要写入的地址
              Word    : 写入的字
  * 返回值     : None
  * 描述      : 向Flash写入一个word
 ***************************************************************/
void Hal_FlashWriteWord(uint32_t WriteAddr, uint32_t Word)
{
    Hal_FlashWriteBuffer((uint8_t *)&Word, WriteAddr, sizeof(uint32_t));
}

/****************************************************************
  * 函数      : Hal_FlashReadWord()
  * 参数      : ReadAddr: 需要读取的地址
              Word    : 读取的字
  * 返回值     : None
  * 描述      : 从Flash读取一个word
 ***************************************************************/
void Hal_FlashReadWord(uint32_t ReadAddr, uint32_t *Word)
{
    Hal_FlashReadBuffer((uint8_t *)Word, ReadAddr, sizeof(uint32_t));
}

/****************************************************************
  * 函数      : Hal_FlashWriteByte()
  * 参数      : ReadAddr: 需要写入的地址
              Word    : 写入的字节
  * 返回值     : None
  * 描述      : 向Flash写入一个字节
 ***************************************************************/
void Hal_FlashWriteByte(uint32_t WriteAddr, uint8_t Byte)
{
    Hal_FlashWriteBuffer(&Byte, WriteAddr, sizeof(uint8_t));
}

/****************************************************************
  * 函数      : Hal_FlashReadByte()
  * 参数      : ReadAddr: 需要读取的地址
              Word    : 读取的字节
  * 返回值     : None
  * 描述      : 从Flash读取一个字节
 ***************************************************************/
void Hal_FlashReadByte(uint32_t ReadAddr, uint8_t *Byte)
{
    Hal_FlashReadBuffer(Byte, ReadAddr, sizeof(uint8_t));
}

/****************************************************************
  * 函数      : Hal_WriteBootHead()
  * 参数      : None
  * 返回值     : None
  * 描述      : 向flash写入boot Head_Info
 ***************************************************************/
static void Hal_WriteBootHead(uint32_t Addr, uint8_t *Head)
{
    Hal_FlashWriteBuffer(Head, Addr, ACU_BOOT_HEAD_LEN);
}


/****************************************************************
  * 函数      : Hal_WriteBootSize()
  * 参数      : None
  * 返回值     : None
  * 描述      : 向flash写入boot大小
 ***************************************************************/
static void Hal_WriteBootSize(uint32_t Addr, uint32_t Size)
{
    Hal_FlashWriteWord(Addr, Size);
}

/****************************************************************
  * 函数      : Hal_GetBootMode()
  * 参数      : None
  * 返回值     : BOOTMODE->XOM: return boot mode
  * 描述      : Get boot mode from BMIO register
 ***************************************************************/
static BootMode Hal_GetBootMode(void)
{
    return (BootMode)BOOTMODE->XOM;
}

/****************************************************************
  * 函数      : Hal_GetBootSize()
  * 参数      : None
  * 返回值     : Size: return boot size
  * 描述      : Get boot bin size
 ***************************************************************/
static uint32_t Hal_GetBootSize(void)
{
    return INT_GEN->DATA0;
}

/****************************************************************
  * 函数      : ACU_FlashUpdate()
  * 参数      : None
  * 返回值     : None
  * 描述      : 固件升级
 ***************************************************************/
void ACU_FlashUpdate(void)
{
    BootMode uBootMode = Hal_GetBootMode();
    uint8_t *pData = (uint8_t *)IRAM_BOOT_START_ADDR;
    uint32_t FlashID = 0, Size = 0;
    uint8_t CheckSum = 0;
    uint32_t i = 0;

    assert_param(IS_ALL_BOOT_MODE(uBootMode));

    /* When BOOTMODE is BootFromFlash, Update is illegal */
    if (uBootMode == BOOT_MODE_XMOD00) /*??? || uBootMode == BOOT_MODE_XMOD11*/
    {
        return;
    }

    FlashID = sFLASH_ReadID();
    if (FlashID == SPI_FLASH_ID)
    {
        Size = Hal_GetBootSize();
        for (i = 0; i < Size; i++)
        {
            CheckSum += pData[i];
        }

        /* load boot to flash */
        Hal_WriteBootHead(ACU_BOOT_HEAD_ADDR, (uint8_t *)ACU_BOOT_HEAD_INFO);
        Hal_WriteBootSize(ACU_BOOT_SIZE_ADDR, Size);
        Hal_FlashWriteBuffer(pData, ACU_BOOT_CODE_ADDR, Size);
        Hal_FlashWriteByte(ACU_BOOT_CODE_ADDR + Size, CheckSum);
        
        /* load boot to flash backup */
        Hal_WriteBootHead(ACU_BOOT_BACK_HEAD_ADDR, (uint8_t *)ACU_BOOT_HEAD_INFO);
        Hal_WriteBootSize(ACU_BOOT_BACK_SIZE_ADDR, Size);
        Hal_FlashWriteBuffer(pData, ACU_BOOT_BACK_CODE_ADDR, Size);
        Hal_FlashWriteByte(ACU_BOOT_BACK_CODE_ADDR + Size, CheckSum);
        
        DEBUG_MSG("ACU Firmware Update Done.\r\n");
    }
    else
    {
        DEBUG_PRINT_REG(FlashID);
        DEBUG_ERROR("ACU spi flash is not correct.\r\n");
    }
    while(1);
}

