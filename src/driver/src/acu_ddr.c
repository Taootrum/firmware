/*******************************************************************************
  * @file    acu_ddr.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    03-Augest-2018
  * @brief   ACU DDR Module Function. 
 ******************************************************************************/
#include "acu_ddr.h"
#include "i2c_passive.h"

void DDR_WriteMem(uint8_t *buf, uint32_t addr, uint32_t size)
{
    uint32_t PageHeadAddr = 0, PageProgAddr = 0;
    uint32_t LineNum = 0, ChipNum = 0;
    uint32_t PageNum = 0, PageMod = 0;
    uint32_t ProgAddr = 0;
    uint8_t FirstMux = 0, SecondMux = 0;
    
    /* calc page head/prog addr and program page_num */
    PageHeadAddr = addr & (~(DDR_PAGE_SIZE - 1));
    PageProgAddr = addr & (DDR_PAGE_SIZE - 1);
    LineNum = PageHeadAddr / DDR_ROW_SIZE;
    ChipNum = (PageHeadAddr % DDR_ROW_SIZE) / DDR_PAGE_SIZE;
    PageNum = (PageProgAddr + size) / DDR_PAGE_SIZE;
    PageMod = (PageProgAddr + size) % DDR_PAGE_SIZE;

    PageNum += 1;
    while (PageNum--)
    {
        /* final sector check SectorMod whether vaild */
        if (PageNum == 0 && PageMod == 0)
        {
            break;
        }
        
        /* select chip 0 - 15 */
        FirstMux = ChipNum / 2;
        SecondMux = ChipNum % 2;
        RCC_DDRWriteSelectCmd(0x1 << FirstMux);
        WRITE32(PDCH, SecondMux << 2 | 0x2);

        /* copy buf to DDR */
        ProgAddr = ACU_DRAM_BASE + LineNum * DDR_PAGE_SIZE + PageProgAddr;
        if (PageNum)
        {
            #ifdef I2C_PASSIVE_WAY
            I2C_PassiveAlignedWriteBuffer(buf, ProgAddr, DDR_PAGE_SIZE - PageProgAddr);
            #else
            memcpy((uint8_t *)ProgAddr, buf, DDR_PAGE_SIZE - PageProgAddr);
            #endif
        }
        else
        {
            #ifdef I2C_PASSIVE_WAY
            I2C_PassiveAlignedWriteBuffer(buf, ProgAddr, PageMod - PageProgAddr);
            #else
            memcpy((uint8_t *)ProgAddr, buf, PageMod - PageProgAddr);
            #endif
            break;
        }
                
        /* calcu LineNum and ChipNum */
        ChipNum++;
        if (ChipNum == DDR_CHIP_NUM)
        {
            ChipNum = 0;
            LineNum++;
        }
        buf += DDR_PAGE_SIZE - PageProgAddr;
        PageProgAddr = 0;
    }
}

void DDR_ReadMem(uint8_t *buf, uint32_t addr, uint32_t size)
{
    uint32_t PageHeadAddr = 0, PageProgAddr = 0;
    uint32_t LineNum = 0, ChipNum = 0;
    uint32_t PageNum = 0, PageMod = 0;
    uint32_t ProgAddr = 0;
    uint8_t FirstMux = 0, SecondMux = 0;
    
    /* calc page head/prog addr and program page_num */
    PageHeadAddr = addr & (~(DDR_PAGE_SIZE - 1));
    PageProgAddr = addr & (DDR_PAGE_SIZE - 1);
    LineNum = PageHeadAddr / DDR_ROW_SIZE;
    ChipNum = (PageHeadAddr % DDR_ROW_SIZE) / DDR_PAGE_SIZE;
    PageNum = (PageProgAddr + size) / DDR_PAGE_SIZE;
    PageMod = (PageProgAddr + size) % DDR_PAGE_SIZE;

    PageNum += 1;
    while (PageNum--)
    {
        /* final sector check SectorMod whether vaild */
        if (PageNum == 0 && PageMod == 0)
        {
            break;
        }
        
        /* select chip 0 - 15 */
        FirstMux = ChipNum / 2;
        SecondMux = ChipNum % 2;
        RCC_DDRReadSelectCmd(FirstMux);
        WRITE32(PDCH, SecondMux << 2 | 0x2);

        /* copy buf to DDR */
        ProgAddr = ACU_DRAM_BASE + LineNum * DDR_PAGE_SIZE + PageProgAddr;
        if (PageNum)
        {
            #ifdef I2C_PASSIVE_WAY
            I2C_PassiveAlignedReadBuffer(buf, ProgAddr, DDR_PAGE_SIZE - PageProgAddr);
            #else
            memcpy(buf, (uint8_t *)ProgAddr, DDR_PAGE_SIZE - PageProgAddr);
            #endif
        }
        else
        {
            #ifdef I2C_PASSIVE_WAY
            I2C_PassiveAlignedReadBuffer(buf, ProgAddr, PageMod - PageProgAddr);
            #else
            memcpy(buf, (uint8_t *)ProgAddr, PageMod - PageProgAddr);
            #endif
            break;
        }
                
        /* calcu LineNum and ChipNum */
        ChipNum++;
        if (ChipNum == DDR_CHIP_NUM)
        {
            ChipNum = 0;
            LineNum++;
        }
        buf += DDR_PAGE_SIZE - PageProgAddr;
        PageProgAddr = 0;
    }
}

