/*******************************************************************************
  * @file    acu_efuse.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    6-September-2018
  * @brief   ACU EFUSE Module Function. 
 ******************************************************************************/
#include "acu_efuse.h"

/****************************************************************
  * 函数      : EFUSE_DeInit()
  * 参数      : None
  * 返回值     : None
  * 描述      : EFUSE清除初始化
 ***************************************************************/
void EFUSE_DeInit(void)
{
    RCC_APBPeriphResetCmd(PVT_SC, 2, SET);
    RCC_APBPeriphResetCmd(PVT_SC, 3, SET);
    RCC_APBPeriphClockCmd(PVT_SC, 2, DISABLE);
    RCC_APBPeriphClockCmd(PVT_SC, 3, DISABLE);
}
  
/****************************************************************
  * 函数      : EFUSE_Init()
  * 参数      : None
  * 返回值     : None
  * 描述      : EFUSE初始化
 ***************************************************************/
void EFUSE_Init(void)
{
    uint32_t DivValue = 0;

    /* system management config */
    RCC_APBPeriphResetCmd(PVT_SC, 2, RESET);
    RCC_APBPeriphResetCmd(PVT_SC, 3, RESET);
    RCC_APBPeriphClockCmd(PVT_SC, 2, ENABLE);
    RCC_APBPeriphClockCmd(PVT_SC, 3, ENABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);

    /* Initialize EFUSE Clock */
    /* First divider 100M */
    RCC_SYSCLKSetSource(EFUSE_CLK, SYSCLK_SOURCE_APLL);
    DivValue = APLL_CLK_FREQ / 100000000 - 1;
    RCC_SYSCLKSetDiv(EFUSE_CLK, DivValue);
    RCC_SYSCLKCmd(EFUSE_CLK, ENABLE);
    /* Seconf divider */
    DivValue = 100000000 / EFUSE_CLK_FREQ - 1;
    WRITE_REG(EFUSE->ESI_MEMFUSE_DIV, DivValue);
}

/****************************************************************
  * 函数      : EFUSE_ITConfig()
  * 参数      : 
              NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : EFUSE中断配置
 ***************************************************************/
void EFUSE_ITConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        SET_BIT(PVT_SC->PVT_INTMASK, EFUSE_INT);
    }
    else
    {
        CLEAR_BIT(PVT_SC->PVT_INTMASK, EFUSE_INT);
    }
}

/****************************************************************
  * 函数      : EFUSE_WriteData()
  * 参数      : Array: number of array
  * 返回值     : None
  * 描述      : 向array写入数据
 ***************************************************************/
void EFUSE_WriteData(uint8_t Array, uint32_t *Data, uint8_t Num)
{
    uint32_t TempReg = 0;

    if (Array + Num > FUSE_ARRAY_MAX)
    {
        return;
    }
    
    TempReg = EFUSE_KEY | EFUSE_RESETB | EFUSE_VDDQPS | EFUSE_CLOCK_APB | EFUSE_AUTO | Array;
    WRITE_REG(EFUSE->ESI_MEMFUSE_CTRL, TempReg);

    while (Num--)
    {
        WRITE_REG(EFUSE->ESI_MEMFUSE_WRDATA, *Data++);
        while (EFUSE_GetStatus() == RESET);
    }
}

/****************************************************************
  * 函数      : EFUSE_ReadData()
  * 参数      : Array: number of array
  * 返回值     : None
  * 描述      : 从array读数据
 ***************************************************************/
void EFUSE_ReadData(uint8_t Array, uint32_t *Data, uint8_t Num)
{
    uint32_t TempReg = 0;

    if (Array + Num > FUSE_ARRAY_MAX)
    {
        return;
    }
    
    TempReg = EFUSE_KEY | EFUSE_RESETB | EFUSE_CLOCK_APB | EFUSE_AUTO | Array;
    WRITE_REG(EFUSE->ESI_MEMFUSE_CTRL, TempReg);

    while (Num--)
    {
        /* generate a read operation */
        WRITE_REG(EFUSE->ESI_MEMFUSE_RDDATA, 0x0);
        while (EFUSE_GetStatus() == RESET);
        /* read data */
        *Data++ = READ_REG(EFUSE->ESI_MEMFUSE_RDDATA);
    }
}
  
/****************************************************************
  * 函数      : EFUSE_GetStatus()
  * 参数      : PVTx: PVT peripheral
  * 返回值     : None
  * 描述      : EFUSE获取状态寄存器
 ***************************************************************/
FlagStatus EFUSE_GetStatus(void)
{
    return (FlagStatus)EFUSE->ESI_MEMFUSE_STAT;
}

/****************************************************************
  * 函数      : EFUSE_GetIntStat()
  * 参数      : PNone
  * 返回值     : None
  * 描述      : EFUSE获取中断状态寄存器
 ***************************************************************/
uint16_t EFUSE_GetIntStat(void)
{
    return PVT_SC->PVT_INTSTA;
}

/****************************************************************
  * 函数      : EFUSE_PrintReg()
  * 参数      : None
  * 返回值     : None
  * 描述      : EFUSE 打印寄存器
 ***************************************************************/
void EFUSE_PrintReg(void)
{        
    DEBUG_PRINT_REG(EFUSE->ESI_MEMFUSE_CTRL);
    DEBUG_PRINT_REG(EFUSE->ESI_MEMFUSE_WRDATA);
    DEBUG_PRINT_REG(EFUSE->ESI_MEMFUSE_RDDATA);
    DEBUG_PRINT_REG(EFUSE->ESI_MEMFUSE_STAT);
    DEBUG_PRINT_REG(EFUSE->ESI_MEMFUSE_DIV);
}

