/*******************************************************************************
  * @file    acu_ddr.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    03-Augest-2018
  * @brief   ACU DDR Module Function. 
 ******************************************************************************/
#include "acu_ddr.h"
#include "i2c_passive.h"

#if 0
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
            memcpy((uint8_t *)ProgAddr, buf, DDR_PAGE_SIZE - PageProgAddr);
        }
        else
        {
            memcpy((uint8_t *)ProgAddr, buf, PageMod - PageProgAddr);
            break;
        }
                
        /* calcu LineNum and ChipNum */
        ChipNum++;
        if (ChipNum == DDR_CHANNEL_NUM)
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
        RCC_DDRWriteSelectCmd(0x1 << FirstMux);
        RCC_DDRReadSelectCmd(FirstMux);
        WRITE32(PDCH, SecondMux << 2 | 0x2);

        /* copy buf to DDR */
        ProgAddr = ACU_DRAM_BASE + LineNum * DDR_PAGE_SIZE + PageProgAddr;
        if (PageNum)
        {
            memcpy(buf, (uint8_t *)ProgAddr, DDR_PAGE_SIZE - PageProgAddr);
        }
        else
        {
            memcpy(buf, (uint8_t *)ProgAddr, PageMod - PageProgAddr);
            break;
        }
                
        /* calcu LineNum and ChipNum */
        ChipNum++;
        if (ChipNum == DDR_CHANNEL_NUM)
        {
            ChipNum = 0;
            LineNum++;
        }
        buf += DDR_PAGE_SIZE - PageProgAddr;
        PageProgAddr = 0;
    }
}
#endif

void DDR_WriteMem(uint8_t *buf, uint32_t addr, uint32_t size, uint8_t channel)
{
    uint8_t FirstMux = channel / 2, SecondMux = channel % 2;
    APBSYS_TypeDef *DDR_SystemManage = (APBSYS_TypeDef *)(ACU_DRAM0SM_BASE + FirstMux * 0x400);
    uint32_t SpaceHeadAddr = 0, SpaceProgAddr = 0;
    uint32_t SpaceNum = 0, SpaceMod = 0;

    /* set ddrc channel */
    RCC_DDRWriteSelectCmd(0x1 << FirstMux);
    WRITE32(PDCH, SecondMux << 2 | 0x2);
    
    /* calc page head/prog addr and program page_num */
    SpaceHeadAddr = addr & (~(DDR_SPACE_SIZE - 1));
    SpaceProgAddr = addr & (DDR_SPACE_SIZE - 1);
    SpaceNum = (SpaceProgAddr + size) / DDR_SPACE_SIZE;
    SpaceMod = (SpaceProgAddr + size) % DDR_SPACE_SIZE;

    /* write start space data */
    if (SpaceNum && SpaceProgAddr)
    {
        CLEAR_BIT(DDR_SystemManage->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(DDR_SystemManage->DDR_PORT_ADDR, (SpaceHeadAddr / DDR_SPACE_SIZE) << 2);
        memcpy((uint8_t *)(ACU_DRAM_BASE + SpaceProgAddr), buf, DDR_SPACE_SIZE - SpaceProgAddr);
        buf += DDR_SPACE_SIZE - SpaceProgAddr;
        SpaceHeadAddr += DDR_SPACE_SIZE;
        SpaceProgAddr = 0;
        SpaceNum--;
    }

    /* write middle page data */
    while (SpaceNum--)
    {
        CLEAR_BIT(DDR_SystemManage->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(DDR_SystemManage->DDR_PORT_ADDR, (SpaceHeadAddr / DDR_SPACE_SIZE) << 2);
        memcpy((uint8_t *)ACU_DRAM_BASE, buf, DDR_SPACE_SIZE);
        buf += DDR_SPACE_SIZE;
        SpaceHeadAddr += DDR_SPACE_SIZE;
    }

    /* write end page data */
    if (SpaceMod)
    {
        CLEAR_BIT(DDR_SystemManage->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(DDR_SystemManage->DDR_PORT_ADDR, (SpaceHeadAddr / DDR_SPACE_SIZE) << 2);
        memcpy((uint8_t *)(ACU_DRAM_BASE + SpaceProgAddr), buf, SpaceMod - SpaceProgAddr);
    }
}

void DDR_ReadMem(uint8_t *buf, uint32_t addr, uint32_t size, uint8_t channel)
{
    uint8_t FirstMux = channel / 2, SecondMux = channel % 2;
    APBSYS_TypeDef *DDR_SystemManage = (APBSYS_TypeDef *)(ACU_DRAM0SM_BASE + FirstMux * 0x400);
    uint32_t SpaceHeadAddr = 0, SpaceProgAddr = 0;
    uint32_t SpaceNum = 0, SpaceMod = 0;

    /* set ddrc channel */
    RCC_DDRWriteSelectCmd(0x1 << FirstMux);
    RCC_DDRReadSelectCmd(FirstMux);
    WRITE32(PDCH, SecondMux << 2 | 0x2);
    
    /* calc page head/prog addr and program page_num */
    SpaceHeadAddr = addr & (~(DDR_SPACE_SIZE - 1));
    SpaceProgAddr = addr & (DDR_SPACE_SIZE - 1);
    SpaceNum = (SpaceProgAddr + size) / DDR_SPACE_SIZE;
    SpaceMod = (SpaceProgAddr + size) % DDR_SPACE_SIZE;

    /* write start space data */
    if (SpaceNum && SpaceProgAddr)
    {
        CLEAR_BIT(DDR_SystemManage->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(DDR_SystemManage->DDR_PORT_ADDR, (SpaceHeadAddr / DDR_SPACE_SIZE) << 2);
        memcpy(buf, (uint8_t *)(ACU_DRAM_BASE + SpaceProgAddr), DDR_SPACE_SIZE - SpaceProgAddr);
        buf += DDR_SPACE_SIZE - SpaceProgAddr;
        SpaceHeadAddr += DDR_SPACE_SIZE;
        SpaceProgAddr = 0;
        SpaceNum--;
    }

    /* write middle page data */
    while (SpaceNum--)
    {
        CLEAR_BIT(DDR_SystemManage->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(DDR_SystemManage->DDR_PORT_ADDR, (SpaceHeadAddr / DDR_SPACE_SIZE) << 2);
        memcpy(buf, (uint8_t *)ACU_DRAM_BASE, DDR_SPACE_SIZE);
        buf += DDR_SPACE_SIZE;
        SpaceHeadAddr += DDR_SPACE_SIZE;
    }

    /* write end page data */
    if (SpaceMod)
    {
        CLEAR_BIT(DDR_SystemManage->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(DDR_SystemManage->DDR_PORT_ADDR, (SpaceHeadAddr / DDR_SPACE_SIZE) << 2);
        memcpy(buf, (uint8_t *)(ACU_DRAM_BASE + SpaceProgAddr), SpaceMod - SpaceProgAddr);
    }
}

void DDR_InterleaveWriteMem(uint8_t *buf, uint64_t addr, uint32_t size)
{
    uint64_t PageHeadAddr = 0;
    uint8_t PageProgAddr = 0;
    uint32_t RowNum = 0, LineNum = 0;
    uint32_t PageNum = 0, PageMod = 0;
    uint32_t ProgAddr = 0;
    uint8_t FirstMux = 0, SecondMux = 0;
    
    /* calc page head/prog addr and program page_num */
    PageHeadAddr = addr & (~(DDR_PAGE_SIZE - 1));
    PageProgAddr = addr & (DDR_PAGE_SIZE - 1);
    RowNum = PageHeadAddr / DDR_ROW_SIZE;
    LineNum = (PageHeadAddr % DDR_ROW_SIZE) / DDR_PAGE_SIZE;
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
        FirstMux = LineNum / 2;
        SecondMux = LineNum % 2;
        RCC_DDRWriteSelectCmd(0x1 << FirstMux);
        WRITE32(PDCH, SecondMux << 2 | 0x2);
        
        /* copy buf to DDR */
        CLEAR_BIT(((APBSYS_TypeDef *)(ACU_DRAM0SM_BASE + FirstMux * 0x400))->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(((APBSYS_TypeDef *)(ACU_DRAM0SM_BASE + FirstMux * 0x400))->DDR_PORT_ADDR, (RowNum / DDR_SPACE_ROW_NUM) << 2);
        ProgAddr = ACU_DRAM_BASE + (RowNum % DDR_SPACE_ROW_NUM) * DDR_PAGE_SIZE + PageProgAddr;
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
        if (++LineNum == DDR_CHANNEL_NUM)
        {
            LineNum = 0;
            RowNum++;
        }
        buf += DDR_PAGE_SIZE - PageProgAddr;
        PageProgAddr = 0;
    }
}

void DDR_InterleaveReadMem(uint8_t *buf, uint64_t addr, uint32_t size)
{
    uint64_t PageHeadAddr = 0;
    uint8_t PageProgAddr = 0;
    uint32_t RowNum = 0, LineNum = 0;
    uint32_t PageNum = 0, PageMod = 0;
    uint32_t ProgAddr = 0;
    uint8_t FirstMux = 0, SecondMux = 0;
    
    /* calc page head/prog addr and program page_num */
    PageHeadAddr = addr & (~(DDR_PAGE_SIZE - 1));
    PageProgAddr = addr & (DDR_PAGE_SIZE - 1);
    RowNum = PageHeadAddr / DDR_ROW_SIZE;
    LineNum = (PageHeadAddr % DDR_ROW_SIZE) / DDR_PAGE_SIZE;
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
        FirstMux = LineNum / 2;
        SecondMux = LineNum % 2;
        RCC_DDRWriteSelectCmd(0x1 << FirstMux);
        RCC_DDRReadSelectCmd(FirstMux);
        WRITE32(PDCH, SecondMux << 2 | 0x2);

        /* copy buf to DDR */
        CLEAR_BIT(((APBSYS_TypeDef *)(ACU_DRAM0SM_BASE + FirstMux * 0x400))->DDR_PORT_ADDR, 0x3 << 2);
        SET_BIT(((APBSYS_TypeDef *)(ACU_DRAM0SM_BASE + FirstMux * 0x400))->DDR_PORT_ADDR, (RowNum / DDR_SPACE_ROW_NUM) << 2);
        ProgAddr = ACU_DRAM_BASE + (RowNum % DDR_SPACE_ROW_NUM) * DDR_PAGE_SIZE + PageProgAddr;
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
        if (++LineNum == DDR_CHANNEL_NUM)
        {
            LineNum = 0;
            RowNum++;
        }
        buf += DDR_PAGE_SIZE - PageProgAddr;
        PageProgAddr = 0;
    }
}

