/*******************************************************************************
  * @file    acu_spi_flash.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Flash Module Function. 
 ******************************************************************************/
#include "acu_spi_flash.h"

/****************************************************************
  * 函数      : sFLASH_DeInit()
  * 参数      : None
  * 返回值     : None
  * 描述      : DeInitializes the peripherals used by the SPI FLASH driver
 ***************************************************************/
void sFLASH_DeInit(void)
{
    /*!< DeInitializes the sFLASH_SPI */
    SPI_DeInit(sFLASH_SPI);
}

/****************************************************************
  * 函数      : sFLASH_DeInit()
  * 参数      : None
  * 返回值     : None
  * 描述      : Initializes Flash_SPI
 ***************************************************************/
void sFLASH_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    if (sFLASH_SPI == SPI0)
    {
        RCC_APBPeriphResetCmd(SPI_SC, 0, RESET);
        RCC_APBPeriphClockCmd(SPI_SC, 0, ENABLE);
    }
    else
    {
        RCC_APBPeriphResetCmd(SPI_SC, 1, RESET);
        RCC_APBPeriphClockCmd(SPI_SC, 1, ENABLE);
    }
    RCC_APBPeriphIsoEnCmd(SPI_SC, ENABLE);

    /*!< GPIO IO as GPIO*/
    GPIO_IOPADMode(sFLASH_CS_GPIO, GPIO_IOPAD_GPIO);
    GPIO_InitStructure.GPIO_Direction = GPIO_OUTPUT;
    GPIO_InitStructure.GPIO_PullStatus = GPIO_PULLUP;
    GPIO_Init(sFLASH_CS_GPIO, &GPIO_InitStructure);
    sFLASH_CS_HIGH();
    
    /*!< SPI configuration */
    SPI_StructInit(&SPI_InitStructure);
    SPI_Init(sFLASH_SPI, &SPI_InitStructure);

    /*!< Enable the sFLASH_SPI  */
    SPI_Cmd(sFLASH_SPI, ENABLE);
    
#ifdef SIM_ENV    
    /* set connect to flash */
    GPIO_Init(GPIO_14, &GPIO_InitStructure);
    GPIO_SetOutput(GPIO_14, GPIO_SET);
#endif
}

/****************************************************************
  * 函数      : sFLASH_EraseSector()
  * 参数      : SectorAddr: address of the sector to erase.
  * 返回值     : None
  * 描述      : Initializes Flash_SPI
 ***************************************************************/
void sFLASH_EraseSector(uint32_t SectorAddr)
{
    /*!< Send write enable instruction */
    sFLASH_WriteEnable();

    sFLASH_CS_LOW();
    /*!< Send Sector Erase instruction */
    sFLASH_SendByte(sFLASH_CMD_SSE);
    /*!< Send SectorAddr high nibble address byte */
    sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
    /*!< Send SectorAddr medium nibble address byte */
    sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
    /*!< Send SectorAddr low nibble address byte */
    sFLASH_SendByte(SectorAddr & 0xFF);
    sFLASH_CS_HIGH();
    
    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}

/****************************************************************
  * 函数      : sFLASH_EraseBlock()
  * 参数      : SectorAddr: address of the block to erase.
  * 返回值     : None
  * 描述      : Initializes Flash_SPI
 ***************************************************************/
void sFLASH_EraseBlock(uint32_t BlockAddr)
{
    /*!< Send write enable instruction */
    sFLASH_WriteEnable();

    sFLASH_CS_LOW();
    /*!< Send Sector Erase instruction */
    sFLASH_SendByte(sFLASH_CMD_SE);
    /*!< Send SectorAddr high nibble address byte */
    sFLASH_SendByte((BlockAddr & 0xFF0000) >> 16);
    /*!< Send SectorAddr medium nibble address byte */
    sFLASH_SendByte((BlockAddr & 0xFF00) >> 8);
    /*!< Send SectorAddr low nibble address byte */
    sFLASH_SendByte(BlockAddr & 0xFF);
    sFLASH_CS_HIGH();
    
    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}

/****************************************************************
  * 函数      : sFLASH_EraseBulk()
  * 参数      : SectorAddr: Erases the entire FLASH.
  * 返回值     : None
  * 描述      : Eflash Bulk Erase
 ***************************************************************/
void sFLASH_EraseBulk(void)
{
    /*!< Send write enable instruction */
    sFLASH_WriteEnable();

    sFLASH_CS_LOW();
    /*!< Send Bulk Erase instruction  */
    sFLASH_SendByte(sFLASH_CMD_BE);
    sFLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}
  
/****************************************************************
  * 函数      : sFLASH_WritePage()
  * 参数      : pBuffer:  pointer to the buffer  containing the data to be written
  *                     to the FLASH.
              WriteAddr: FLASH's internal address to write to.
              NumByteToWrite:   number of bytes to write to the FLASH, must be equal
  *                             or less than "sFLASH_PAGESIZE" value.
  * 返回值     : None
  * 描述      : Writes more than one byte to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
 ***************************************************************/
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t tx = 0, tx_end = NumByteToWrite;
    uint8_t txfifolevel = 0, temp = 0;

    /*!< Enable the write access to the FLASH */
    sFLASH_WriteEnable();

    sFLASH_CS_LOW();
    /*!< Send "Write to Memory " instruction */
    sFLASH_SendByte(sFLASH_CMD_WRITE);
    /*!< Send WriteAddr high nibble address byte to write to */
    sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    /*!< Send WriteAddr medium nibble address byte to write to */
    sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    /*!< Send WriteAddr low nibble address byte to write to */
    sFLASH_SendByte(WriteAddr & 0xFF);

    /*!< while there is data to be written on the FLASH */
    while (NumByteToWrite)
    {      
        /*!< Loop while DR register in not empty */
        while ((txfifolevel < SPI_FIFO_TX_TH) && (tx < tx_end))
        {
            sFLASH_SPI->DR = *pBuffer++;
            tx++;
            txfifolevel++;
            
            /*!< Read data when Rx_FIFO not empty */
            if (sFLASH_SPI->SR & SPI_FLAG_RXNE)
            {
                temp = sFLASH_SPI->DR;
                NumByteToWrite--;
                txfifolevel--;
            }
        }

        /*!< Read data when Rx_FIFO not empty */
        if (sFLASH_SPI->SR & SPI_FLAG_RXNE)
        {
            temp = sFLASH_SPI->DR;
            NumByteToWrite--;
            txfifolevel--;
        }
    }
    (void)temp;
    sFLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    sFLASH_WaitForWriteEnd();
}
  
/****************************************************************
  * 函数      : sFLASH_WriteBuffer()
  * 参数      : pBuffer:  pointer to the buffer  containing the data to be written
                        to the FLASH.
              WriteAddr: FLASH's internal address to write to.
              NumByteToWrite: number of bytes to write to the FLASH.
  * 返回值     : None
  * 描述      : Writes more than one byte to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
 ***************************************************************/
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % sFLASH_SPI_PAGESIZE;
    count = sFLASH_SPI_PAGESIZE - Addr;
    NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
    NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

    if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            while (NumOfPage--)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr +=  sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
            {
                temp = NumOfSingle - count;

                sFLASH_WritePage(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;

                sFLASH_WritePage(pBuffer, WriteAddr, temp);
            }
            else
            {
                sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            NumByteToWrite -= count;
            NumOfPage = NumByteToWrite / sFLASH_SPI_PAGESIZE;
            NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

            sFLASH_WritePage(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr +=  sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            if (NumOfSingle != 0)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/****************************************************************
  * 函数      : sFLASH_ReadBuffer8Bit()
  * 参数      : pBuffer: pointer to the buffer that receives the data read from the FLASH.
              ReadAddr: FLASH's internal address to read from.
              NumByteToRead: number of bytes to read from the FLASH.
  * 返回值     : None
  * 描述      : Reads a block of data from the FLASH by spi work in 8bits transfer.
 ***************************************************************/
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint16_t tx = 0, tx_end = NumByteToRead;
    uint8_t *pRx = pBuffer;
    uint8_t *pRxEnd = pRx + NumByteToRead;
    uint8_t txfifolevel = 0;
    
    sFLASH_CS_LOW();

    /*!< Send read instruction */
    sFLASH_SendByte(sFLASH_CMD_FREAD);

    /*!< Send ReadAddr  */
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
    sFLASH_SendByte(ReadAddr & 0xFF);

    /* Read data*/
    sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    while (pRx < pRxEnd)
    {      
        /*!< Loop while DR register in not empty */
        while ((txfifolevel < SPI_FIFO_TX_TH) && (tx < tx_end))
        {
            sFLASH_SPI->DR = sFLASH_DUMMY_BYTE;
            tx++;
            txfifolevel++;
            
            /*!< Read data when Rx_FIFO not empty */
            if (sFLASH_SPI->SR & SPI_FLAG_RXNE)
            {
                *pRx++ = sFLASH_SPI->DR;
                txfifolevel--;
            }
        }

        /*!< Read data when Rx_FIFO not empty */
        if (sFLASH_SPI->SR & SPI_FLAG_RXNE)
        {
            *pRx++ = sFLASH_SPI->DR;
            txfifolevel--;
        }
    }
    
    sFLASH_CS_HIGH();
}

/****************************************************************
  * 函数      : sFLASH_ReadBuffer()
  * 参数      : pBuffer: pointer to the buffer that receives the data read from the FLASH.
              ReadAddr: FLASH's internal address to read from.
              NumByteToRead: number of bytes to read from the FLASH.
  * 返回值     : None
  * 描述      : Reads a block of data from the FLASH by spi work in 16bits transfer.
 ***************************************************************/
void sFLASH_ReadBuffer16Bit(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t txfifolevel = 0;
    uint16_t tx = 0, tx_end = NumByteToRead / 2, temp = 0;
    uint16_t *pRx = (uint16_t *)pBuffer;
    uint16_t *pRxEnd = pRx + (NumByteToRead / 2);
    
    sFLASH_CS_LOW();

    /*!< Send read instruction and address */
    sFLASH_SendHalfWord((sFLASH_CMD_READ << 8) | ((ReadAddr & 0xFF0000) >> 16));
    sFLASH_SendHalfWord(ReadAddr & 0xFFFF);

    /* Read data*/
    while (pRx < pRxEnd)
    {          
        /*!< Write as much to Tx_FIFO */
        while ((txfifolevel < SPI_FIFO_TX_TH) && (tx < tx_end))
        {
            sFLASH_SPI->DR = sFLASH_DUMMY_BYTE;
            tx++;
            txfifolevel++;

            /*!< Read data when Rx_FIFO not empty */
            if (sFLASH_SPI->SR & SPI_FLAG_RXNE)
            {
                temp = sFLASH_SPI->DR;
                *pRx++ = (temp << 8) | (temp >> 8);
                txfifolevel--;
            }
        }

        /*!< Read data when Rx_FIFO not empty */
        if (sFLASH_SPI->SR & SPI_FLAG_RXNE)
        {
            temp = sFLASH_SPI->DR;
            *pRx++ = (temp << 8) | (temp >> 8);
            txfifolevel--;
        }
    }

    /* Prevent memory from being out of bounds */
    if (NumByteToRead % 2)
    {
        sFLASH_SPI->DR = sFLASH_DUMMY_BYTE;
        while (SPI_GetStatus(sFLASH_SPI, SPI_FLAG_RXNE) == RESET);
        temp = sFLASH_SPI->DR;
        *(pBuffer + NumByteToRead - 1) = temp >> 8;
    }

    sFLASH_CS_HIGH();
}

/****************************************************************
  * 函数      : sFLASH_ReadID()
  * 参数      : None
  * 返回值     : FLASH identification
  * 描述      : Reads FLASH identification.
 ***************************************************************/
uint32_t sFLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    sFLASH_CS_LOW();
    
    /*!< Send "RDID" instruction */
    sFLASH_SendByte(sFLASH_CMD_RDID);
    
    /*!< Read ID from the FLASH */
    Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    
    sFLASH_CS_HIGH();

    /*!< Calculation ID */
    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    
    return Temp;
}

/****************************************************************
  * 函数      : sFLASH_StartReadSequence()
  * 参数      : ReadAddr: FLASH's internal address to read from.
  * 返回值     : None
  * 描述      : Initiates a read data byte (READ) sequence from the Flash.
 ***************************************************************/
void sFLASH_StartReadSequence(uint32_t ReadAddr)
{
    sFLASH_CS_LOW();

    /*!< Send "FREAD" instruction */
    sFLASH_SendByte(sFLASH_CMD_FREAD);

    /*!< Send the 24-bit address*/
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
    sFLASH_SendByte(ReadAddr & 0xFF);
}

/****************************************************************
  * 函数      : sFLASH_ReadByte()
  * 参数      : None
  * 返回值     : Byte Read from the SPI Flash.
  * 描述      : Reads a byte from the SPI Flash.
 ***************************************************************/
uint8_t sFLASH_ReadByte(void)
{
    return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}

/****************************************************************
  * 函数      : sFLASH_SendByte()
  * 参数      : byte: byte to send.
  * 返回值     : The value of the received byte.
  * 描述      : Sends a byte through the SPI interface and return the byte received
              from the SPI bus.
 ***************************************************************/
uint8_t sFLASH_SendByte(uint8_t byte)
{
    /*!< Loop while DR register in not emplty */
    while (SPI_GetStatus(sFLASH_SPI, SPI_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_SendData(sFLASH_SPI, byte);

    /*!< Wait to receive a byte */
    while (SPI_GetStatus(sFLASH_SPI, SPI_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_ReceiveData(sFLASH_SPI);
}

/****************************************************************
  * 函数      : sFLASH_SendHalfWord()
  * 参数      : HalfWord: Half Word to send.
  * 返回值     : The value of the received Half Word.
  * 描述      : Sends a Half Word through the SPI interface and return the Half Word
                received from the SPI bus.
 ***************************************************************/
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
    /*!< Loop while DR register in not emplty */
    while (SPI_GetStatus(sFLASH_SPI, SPI_FLAG_TXE) == RESET);

    /*!< Send Half Word through the sFLASH peripheral */
    SPI_SendData(sFLASH_SPI, HalfWord);

    /*!< Wait to receive a Half Word */
    while (SPI_GetStatus(sFLASH_SPI, SPI_FLAG_RXNE) == RESET);

    /*!< Return the Half Word read from the SPI bus */
    return SPI_ReceiveData(sFLASH_SPI);
}

/****************************************************************
  * 函数      : sFLASH_WriteEnable()
  * 参数      : None
  * 返回值     : None
  * 描述      : Enables the write access to the FLASH.
 ***************************************************************/
void sFLASH_WriteEnable(void)
{
    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_WREN);
    sFLASH_CS_HIGH();
}

/****************************************************************
  * 函数      : sFLASH_WriteEnable()
  * 参数      : None
  * 返回值     : None
  * 描述      : Polls the status of the Write In Progress (WIP) flag in the FLASH's
                status register and loop until write opertaion has completed.
 ***************************************************************/
void sFLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;

    sFLASH_CS_LOW();

    /*!< Send "Read Status Register" instruction */
    sFLASH_SendByte(sFLASH_CMD_RDSR);

    /*!< Loop as long as the memory is busy with a write cycle */
    do
    {
        flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    }
    while ((flashstatus & sFLASH_WIP_FLAG) == SET);

    sFLASH_CS_HIGH();
}

/****************************************************************
  * 函数      : Flash_PrintReg()
  * 参数      : RCC_IMEM: IRAM/IROM
  * 返回值     : None
  * 描述      : 
 ***************************************************************/
void Flash_PrintReg(void)
{   
    /* RCC */
    DEBUG_MSG("FABRIC_CLK:"LF);
    DEBUG_PRINT_REG(FABRIC_CLK);
    RCC_SYSCLKPrintReg(FABRIC_CLK);
    DEBUG_MSG("SPI_SC:"LF);
    DEBUG_PRINT_REG(SPI_SC);
    RCC_APBSYSPrintReg(SPI_SC);
    DEBUG_MSG("GPIO_SC:"LF);
    DEBUG_PRINT_REG(GPIO_SC);
    RCC_APBSYSPrintReg(GPIO_SC);

    /* GPIO */
    DEBUG_MSG("IOPAD_SC:"LF);
    DEBUG_PRINT_REG(IOPAD_MUX);
    GPIO_IOPADPrintReg(IOPAD_MUX);
    DEBUG_MSG("sFLASH_CS_GPIO:"LF);
    DEBUG_PRINT_REG(sFLASH_CS_GPIO);
    GPIO_PrintReg(sFLASH_CS_GPIO);
    
    /* SPI */
    DEBUG_MSG("sFLASH_SPI:"LF);
    DEBUG_PRINT_REG(sFLASH_SPI);
    SPI_PrintReg(sFLASH_SPI);
    DEBUG_MSG(LF);
}

