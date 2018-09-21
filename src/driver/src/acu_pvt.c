/*******************************************************************************
  * @file    acu_pvt.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    15-Augest-2018
  * @brief   ACU PVT Module Function. 
 ******************************************************************************/
#include "acu_pvt.h"

/****************************************************************
  * 函数      : PVT_DeInit()
  * 参数      : PVTx: PVT peripheral
  * 返回值     : None
  * 描述      : PVT清除初始化
 ***************************************************************/
void PVT_DeInit(PVT_TypeDef* PVTx)
{
    /* Check the parameters */
    assert_param(IS_PVT_ALL_PERIPH(PVTx));
    
    if (PVTx == PVT0)
    {
        RCC_APBPeriphResetCmd(PVT_SC, 0, SET);
        RCC_APBPeriphClockCmd(PVT_SC, 0, DISABLE);
    }
    else
    {
        RCC_APBPeriphResetCmd(PVT_SC, 1, SET);
        RCC_APBPeriphClockCmd(PVT_SC, 1, DISABLE);
    }
}
  
/****************************************************************
  * 函数      : PVT_Init()
  * 参数      : PVT_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : PVT初始化
 ***************************************************************/
void PVT_Init(PVT_TypeDef* PVTx, PVT_InitTypeDef* PVT_InitStruct)
{
    uint32_t apbclock = 0, divider = 0;

    /* Check the PVT parameters */
    assert_param(IS_PVT_ALL_PERIPH(PVTx));
    assert_param(IS_PVT_MODE(PVT_InitStruct->PVT_MODE));
    assert_param(IS_PVT_TRIM(PVT_InitStruct->PVT_TIMG));

    /* system management config */
    if (PVTx == PVT0)
    {
        RCC_APBPeriphResetCmd(PVT_SC, 0, RESET);
        RCC_APBPeriphClockCmd(PVT_SC, 0, ENABLE);
    }
    else
    {
        RCC_APBPeriphResetCmd(PVT_SC, 1, RESET);
        RCC_APBPeriphClockCmd(PVT_SC, 1, ENABLE);
    }
    RCC_APBPeriphIsoEnCmd(PVT_SC, ENABLE);
    
    /* PVT Clock Configuration */
    apbclock = SystemCoreClock;
    divider = apbclock / 1200000 - 1; /* pvt clock 1.2M */
    if (PVTx == PVT0)
    {
        WRITE_REG(PVT_SC->PVT0_DIV, divider);
    }
    else
    {
        WRITE_REG(PVT_SC->PVT1_DIV, divider);
    }
    ACU_Delay(10);
    
    /* PVT APB_CTRL Configuration */
    PVTx->APB_CTRL = 0x1;
    /* PVT MODE_CTRL Configuration */
    PVTx->MODE_CTRL = PVT_InitStruct->PVT_MODE;
    /* PVT TRIMG_CTRL Configuration */
    PVTx->TRIMG_CTRL = PVT_InitStruct->PVT_TIMG;
}
  
/****************************************************************
  * 函数      : PVT_StructInit()
  * 参数      : PVT_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : PVT默认初始化
 ***************************************************************/
void PVT_StructInit(PVT_InitTypeDef* PVT_InitStruct)
{
    /* Initialize the SPI_Direction member */
    PVT_InitStruct->PVT_MODE = 0;//PVT_MODE_PSAMPLE1 | PVT_MODE_PSAMPLE0;
    /* initialize the SPI_Mode member */
    PVT_InitStruct->PVT_TIMG = PVT_TRIM;
}
  
/****************************************************************
  * 函数      : PVT_Cmd()
  * 参数      : PVTx: PVT peripheral
              NewState: 使能状态
  * 返回值     : None
  * 描述      : PVT使能/关闭
 ***************************************************************/
void PVT_Cmd(PVT_TypeDef* PVTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        WRITE_REG(PVTx->SENSOR_ENA, PVT_ENABLE);
    }
    else
    {
        WRITE_REG(PVTx->SENSOR_ENA, 0);
    }
}

/****************************************************************
  * 函数      : PVT_ITConfig()
  * 参数      : Type: PVT0_INT = 0x1,
                    PVT1_INT = 0x2,
                    EFUSE_INT = 0x4
              NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : PVT中断配置
 ***************************************************************/
void PVT_ITConfig(PVT_IntType Type, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        SET_BIT(PVT_SC->PVT_INTMASK, Type);
    }
    else
    {
        CLEAR_BIT(PVT_SC->PVT_INTMASK, Type);
    }
}

/****************************************************************
  * 函数      : PVT_ReadData()
  * 参数      : PVTx: PVT peripheral
  * 返回值     : None
  * 描述      : 从数据寄存器读数据
 ***************************************************************/
uint16_t PVT_ReadData(PVT_TypeDef* PVTx)
{
    return PVTx->SENSOR_DATA;
}
  
/****************************************************************
  * 函数      : PVT_GetStatus()
  * 参数      : PVTx: PVT peripheral
  * 返回值     : None
  * 描述      : SPI获取状态寄存器
 ***************************************************************/
FlagStatus PVT_GetStatus(PVT_TypeDef* PVTx)
{
    return (READ_REG(PVTx->DATA_VALID) ? SET : RESET);
}

/****************************************************************
  * 函数      : PVT_GetIntStat()
  * 参数      : PNone
  * 返回值     : None
  * 描述      : SPI获取中断状态寄存器
 ***************************************************************/
uint16_t PVT_GetIntStat(void)
{
    return PVT_SC->PVT_INTSTA;
}

/****************************************************************
  * 函数      : PVT_PrintReg()
  * 参数      : PVTx: PVT peripheral
  * 返回值     : None
  * 描述      : PVT 打印寄存器
 ***************************************************************/
void PVT_PrintReg(PVT_TypeDef* PVTx)
{        
    DEBUG_PRINT_REG(PVTx->APB_CTRL);
    DEBUG_PRINT_REG(PVTx->MODE_CTRL);
    DEBUG_PRINT_REG(PVTx->TRIMO_CTRL);
    DEBUG_PRINT_REG(PVTx->TRIMG_CTRL);
    DEBUG_PRINT_REG(PVTx->SENSOR_DATA);
    DEBUG_PRINT_REG(PVTx->DATA_VALID);
    DEBUG_PRINT_REG(PVTx->SENSOR_ENA);
}

