/*******************************************************************************
  * @file    i2c_passive.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Flash Application Function. 
 ******************************************************************************/
#include "i2c_passive.h"

/****************************************************************
  * 函数      : I2C_PassiveWriteWord()
  * 参数      : Data:    写入的数据buf
              AcuAddr: 写入的地址
              Command: PASSIVE_WRITE_SDATA_CMD = 0x0,
                       PASSIVE_READ_SDATA_CMD,
                       PASSIVE_WRITE_SREG_CMD,
                       PASSIVE_READ_SREG_CMD,
  * 返回值     : None
  * 描述      : 向Passive写入一个word
 ***************************************************************/
void I2C_PassiveWriteWord(uint8_t *Data, uint32_t AcuAddr, PassiveCmd Command)
{
    uint8_t i = 0;

    /* write system data */
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, Command);
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)(AcuAddr & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 8) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 16) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 24) & 0xff));
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C_MASTER, Data[i]);
    }
}

/****************************************************************
  * 函数      : I2C_PassiveReadWord()
  * 参数      : Data:    写入的数据buf
              AcuAddr: 写入的地址
              Command: PASSIVE_WRITE_SDATA_CMD = 0x0,
                       PASSIVE_READ_SDATA_CMD,
                       PASSIVE_WRITE_SREG_CMD,
                       PASSIVE_READ_SREG_CMD,
  * 返回值     : None
  * 描述      : 从Passive读取一个word
 ***************************************************************/
void I2C_PassiveReadWord(uint8_t *Data, uint32_t AcuAddr, PassiveCmd Command)
{
    uint8_t i = 0;

    /* read system data */
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, Command);
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)(AcuAddr & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 8) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 16) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 24) & 0xff));

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
        I2C_MASTER->DATACMD = I2C_MASTER_READ_CMD;
    }
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_RFNE) == RESET);
        Data[i] = I2C_ReceiveData(I2C_MASTER);
    }
}

/****************************************************************
  * 函数      : I2C_PassiveWritePage()
  * 参数      : Data:    写入的数据buf
              AcuAddr: 写入的地址
              Size:    max = 255
  * 返回值     : None
  * 描述      : 向Passive写stream
 ***************************************************************/
void I2C_PassiveWritePage(uint8_t *Data, uint32_t AcuAddr, uint16_t Size)
{
    uint16_t tx = 0, tx_end = Size;

    if ((Size == 0) || (Size % 4))
    {
        return;
    }
    
    /* write system data */
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, PASSIVE_WRITE_BURST_DATA_CMD);
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, Size / 4 - 1);
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)(AcuAddr & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 8) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 16) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 24) & 0xff));

    /* send burst datas to pasive */
    while (tx < tx_end)
    {
        while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C_MASTER, Data[tx]);
        tx++;
    }

    /* wait for cmd send complex */
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFE) == RESET);
}

/****************************************************************
  * 函数      : I2C_PassiveReadPage()
  * 参数      : Data:    写入的数据buf
              AcuAddr: 写入的地址
              Size:    max = 256
  * 返回值     : None
  * 描述      : 从Passive读stream
 ***************************************************************/
void I2C_PassiveReadPage(uint8_t *Data, uint32_t AcuAddr, uint16_t Size)
{
    uint16_t tx = 0, tx_end = Size;
    uint8_t *pRx = Data, *pRxEnd = Data + Size;
    uint8_t txfifolevel = 0;

    if ((Size == 0) || (Size % 4))
    {
        return;
    }
    
    /* read system data */
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, PASSIVE_READ_BURST_DATA_CMD);
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, Size / 4 - 1);
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)(AcuAddr & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 8) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 16) & 0xff));
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFNF) == RESET);
    I2C_SendData(I2C_MASTER, (uint8_t)((AcuAddr >> 24) & 0xff));

    /* wait for cmd send complex */
    while (I2C_GetFlagStatus(I2C_MASTER, I2C_FLAG_TFE) == RESET);

    /* read burst datas form pasive */
    while (pRx < pRxEnd)
    {      
        /*!< Loop while DR register in not empty */
        while ((txfifolevel < I2C_FIFO_TX_LEVEL) && (tx < tx_end))
        {
            I2C_MASTER->DATACMD = I2C_MASTER_READ_CMD;
            tx++;
            txfifolevel++;
            
            /*!< Read data when Rx_FIFO not empty */
            if (I2C_MASTER->STATUS & I2C_FLAG_RFNE)
            {
                *pRx++ = (uint8_t)I2C_MASTER->DATACMD;
                txfifolevel--;
            }
        }

        /*!< Read data when Rx_FIFO not empty */
        if (I2C_MASTER->STATUS & I2C_FLAG_RFNE)
        {
            *pRx++ = (uint8_t)I2C_MASTER->DATACMD;
            txfifolevel--;
        }
    }
}

/****************************************************************
  * 函数      : I2C_PassiveAlignedWriteBuffer()
  * 参数      : pBuffer   ：输入buffer
              WriteAddr ：写入地址
              Size  ：     数据长度
  * 返回值     : None
  * 描述      : 地址和大小4字节对齐向Passive写入数据流
 ***************************************************************/
void I2C_PassiveAlignedWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size)
{
    uint32_t PageHeadAddr = 0, PageProgAddr = 0;
    uint32_t PageNum = 0, PageMod = 0;

    if ((WriteAddr % 4) || (Size == 0) || (Size % 4))
    {
        return;
    }
    
    /* calc page head/prog addr and program page_num */
    PageHeadAddr = WriteAddr & (~(PASSIVE_PAGE_SIZE - 1));
    PageProgAddr = WriteAddr & (PASSIVE_PAGE_SIZE - 1);
    PageNum = (PageProgAddr + Size) / PASSIVE_PAGE_SIZE;
    PageMod = (PageProgAddr + Size) % PASSIVE_PAGE_SIZE;

    /* write start page data */
    if (PageNum && PageProgAddr)
    {
        I2C_PassiveWritePage(pBuffer, PageHeadAddr + PageProgAddr, PASSIVE_PAGE_SIZE - PageProgAddr);
        pBuffer += PASSIVE_PAGE_SIZE - PageProgAddr;
        PageHeadAddr += PASSIVE_PAGE_SIZE;
        PageProgAddr = 0;
        PageNum--;
    }

    /* write middle page data */
    while (PageNum--)
    {
        I2C_PassiveWritePage(pBuffer, PageHeadAddr, PASSIVE_PAGE_SIZE);
        pBuffer += PASSIVE_PAGE_SIZE;
        PageHeadAddr += PASSIVE_PAGE_SIZE;
    }

    /* write end page data */
    if (PageMod)
    {
        I2C_PassiveWritePage(pBuffer, PageHeadAddr + PageProgAddr, PageMod - PageProgAddr);
    }
}

/****************************************************************
  * 函数      : I2C_PassiveAlignedReadBuffer()
  * 参数      : pBuffer   ：输入buffer
              ReadAddr ：  读取地址
              Size  ：     数据长度
  * 返回值     : None
  * 描述      : 地址和大小4字节对齐从Passive读取数据流
 ***************************************************************/
void I2C_PassiveAlignedReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t Size)
{
    uint32_t PageNum = 0, PageMod = 0;

    if ((ReadAddr % 4) || (Size == 0) || (Size % 4))
    {
        return;
    }

    /* read full page */
    PageNum = Size / PASSIVE_PAGE_SIZE;
    while (PageNum--)
    {
        I2C_PassiveReadPage(pBuffer, ReadAddr, PASSIVE_PAGE_SIZE);
        pBuffer += PASSIVE_PAGE_SIZE;
        ReadAddr += PASSIVE_PAGE_SIZE;
    }

    /* read remainder page */
    PageMod = Size % PASSIVE_PAGE_SIZE;
    if (PageMod)
    {
        I2C_PassiveReadPage(pBuffer, ReadAddr, PageMod);
    }
}

/****************************************************************
  * 函数      : I2C_PassiveWriteBuffer()
  * 参数      : pBuffer   ：输入buffer
              WriteAddr ：写入地址
              Size  ：     数据长度
  * 返回值     : None
  * 描述      : 向Passive写入数据流
 ***************************************************************/
void I2C_PassiveWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size)
{
    uint8_t TempBuf[4] = {0};
    uint32_t WriteHeadAddr = 0, WriteOftSize = 0;
    uint32_t PageHeadAddr = 0, PageProgAddr = 0;
    uint32_t PageNum = 0, PageMod = 0;
    uint32_t LastSize = 0;

    /* start program word unaliged */
    WriteHeadAddr = WriteAddr & (~(4 - 1));
    WriteOftSize = WriteAddr & (4 - 1);
    if (WriteOftSize)
    {
        I2C_PassiveReadWord(TempBuf, WriteHeadAddr, PASSIVE_READ_DATA_CMD);
        if (Size <= 4 - WriteOftSize)
        {
            memcpy(TempBuf + WriteOftSize, pBuffer, Size);
            I2C_PassiveWriteWord(TempBuf, WriteHeadAddr, PASSIVE_WRITE_DATA_CMD);
            return;
        }
        
        memcpy(TempBuf + WriteOftSize, pBuffer, 4 - WriteOftSize);
        I2C_PassiveWriteWord(TempBuf, WriteHeadAddr, PASSIVE_WRITE_DATA_CMD);
        pBuffer += 4 - WriteOftSize;
        WriteHeadAddr += 4;
        Size -= 4 - WriteOftSize;
    }
    
    /* calc page head/prog addr and program page_num */
    PageHeadAddr = WriteHeadAddr & (~(PASSIVE_PAGE_SIZE - 1));
    PageProgAddr = WriteHeadAddr & (PASSIVE_PAGE_SIZE - 1);
    PageNum = (PageProgAddr + Size) / PASSIVE_PAGE_SIZE;
    PageMod = (PageProgAddr + Size) % PASSIVE_PAGE_SIZE;

    /* write start page data */
    if (PageNum && PageProgAddr)
    {
        I2C_PassiveWritePage(pBuffer, PageHeadAddr + PageProgAddr, PASSIVE_PAGE_SIZE - PageProgAddr);
        pBuffer += PASSIVE_PAGE_SIZE - PageProgAddr;
        PageHeadAddr += PASSIVE_PAGE_SIZE;
        PageProgAddr = 0;
        PageNum--;
    }

    /* write middle page data */
    while (PageNum--)
    {
        I2C_PassiveWritePage(pBuffer, PageHeadAddr, PASSIVE_PAGE_SIZE);
        pBuffer += PASSIVE_PAGE_SIZE;
        PageHeadAddr += PASSIVE_PAGE_SIZE;
    }

    /* write end page data */
    if (PageMod)
    {
        LastSize = PageMod % 4;
        if (LastSize == 0)
        {
            I2C_PassiveWritePage(pBuffer, PageHeadAddr + PageProgAddr, PageMod - PageProgAddr);
        }
        else
        {
            I2C_PassiveWritePage(pBuffer, PageHeadAddr + PageProgAddr, PageMod - LastSize - PageProgAddr);
            /* last LastSize do only */
            pBuffer += PageMod - LastSize - PageProgAddr;
            PageHeadAddr += PageMod - LastSize;
            I2C_PassiveReadWord(TempBuf, PageHeadAddr, PASSIVE_READ_DATA_CMD);
            memcpy(TempBuf, pBuffer, LastSize);
            I2C_PassiveWriteWord(TempBuf, PageHeadAddr, PASSIVE_WRITE_DATA_CMD);
        }
    }
}

/****************************************************************
  * 函数      : I2C_PassiveReadBuffer()
  * 参数      : pBuffer   ：输入buffer
              ReadAddr ：  读取地址
              Size  ：     数据长度
  * 返回值     : None
  * 描述      : 从Passive读取数据流
 ***************************************************************/
void I2C_PassiveReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t Size)
{
    uint8_t TempBuf[4] = {0};
    uint32_t ReadHeadAddr = 0, ReadOftSize = 0;
    uint32_t PageNum = 0, PageMod = 0;
    uint32_t LastSize = 0;

    /* read start word */
    ReadHeadAddr = ReadAddr & (~(4 - 1));
    ReadOftSize = ReadAddr & (4 - 1);
    if (ReadOftSize)
    {
        I2C_PassiveReadWord(TempBuf, ReadHeadAddr, PASSIVE_READ_DATA_CMD);
        /* Size less than 4 - ReadOftSize */
        if (Size <= 4 - ReadOftSize)
        {
            memcpy(pBuffer, TempBuf + ReadOftSize, Size);
            return;
        }
        /* Size more than 4 - ReadOftSize */
        memcpy(pBuffer, TempBuf + ReadOftSize, 4 - ReadOftSize);
        pBuffer += 4 - ReadOftSize;
        ReadHeadAddr += 4;
        Size -= 4 - ReadOftSize;
    }
    
    /* read full page */
    PageNum = Size / PASSIVE_PAGE_SIZE;
    while (PageNum--)
    {
        I2C_PassiveReadPage(pBuffer, ReadHeadAddr, PASSIVE_PAGE_SIZE);
        pBuffer += PASSIVE_PAGE_SIZE;
        ReadHeadAddr += PASSIVE_PAGE_SIZE;
    }

    /* read remainder page */
    PageMod = Size % PASSIVE_PAGE_SIZE;
    if (PageMod)
    {
        LastSize = PageMod % 4;
        if (LastSize == 0)
        {
            I2C_PassiveReadPage(pBuffer, ReadHeadAddr, PageMod);
        }
        else
        {
            I2C_PassiveReadPage(pBuffer, ReadHeadAddr, PageMod - LastSize);
            /* last LastSize do only */
            pBuffer += PageMod - LastSize;
            ReadHeadAddr += PageMod - LastSize;
            I2C_PassiveReadWord(TempBuf, ReadHeadAddr, PASSIVE_READ_DATA_CMD);
            memcpy(pBuffer, TempBuf, LastSize);
        }
    }
}

