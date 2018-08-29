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
  * 参数      : None
  * 返回值     : None
  * 描述      : PVT清除初始化
 ***************************************************************/
void PVT_DeInit(void)
{
    RCC_APBPeriphResetCmd(PVT_SC, 0, SET);
    RCC_APBPeriphClockCmd(PVT_SC, 0, DISABLE);
    RCC_APBPeriphIsoEnCmd(PVT_SC, DISABLE);
}
  
/****************************************************************
  * 函数      : PVT_Init()
  * 参数      : PVT_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : PVT初始化
 ***************************************************************/
void PVT_Init(PVT_InitTypeDef* PVT_InitStruct)
{
    uint32_t apbclock = 0, divider = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    /* Check the PVT parameters */
    assert_param(IS_PVT_MODE(PVT_InitStruct->PVT_MODE));
    assert_param(IS_PVT_TRIM(PVT_InitStruct->PVT_TIMG));

    /* PVT Clock Configuration */
    RCC_SYSCLKGetFreq(&RCC_ClocksStatus);
    apbclock = RCC_ClocksStatus.FCLK_Frequency;
    divider = apbclock / 1200000 - 1; /* pvt clock 1.2M */
    WRITE_REG(PVT_SC->PVT_DIV, divider);
    
    /* PVT APB_CTRL Configuration */
    PVT->APB_CTRL = 0x1;
    /* PVT MODE_CTRL Configuration */
    PVT->MODE_CTRL = PVT_InitStruct->PVT_MODE;
    /* PVT TRIMG_CTRL Configuration */
    PVT->TRIMG_CTRL = PVT_InitStruct->PVT_TIMG;
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
  * 参数      : NewState: 使能状态
  * 返回值     : None
  * 描述      : PVT使能/关闭
 ***************************************************************/
void PVT_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        WRITE_REG(PVT->SENSOR_ENA, PVT_ENABLE);
    }
    else
    {
        WRITE_REG(PVT->SENSOR_ENA, 0);
    }
}

/****************************************************************
  * 函数      : PVT_ITConfig()
  * 参数      : NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : SPI中断配置
 ***************************************************************/
void PVT_ITConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        WRITE_REG(PVT_SC->PVT_INTMASK, PVT_INT_ENABLE);
    }
    else
    {
        WRITE_REG(PVT_SC->PVT_INTMASK, 0);
    }
}

/****************************************************************
  * 函数      : PVT_ReadData()
  * 参数      : None
  * 返回值     : None
  * 描述      : 从数据寄存器读数据
 ***************************************************************/
uint16_t PVT_ReadData(void)
{
    return PVT->SENSOR_DATA;
}
  
/****************************************************************
  * 函数      : PVT_GetStatus()
  * 参数      : None
  * 返回值     : None
  * 描述      : SPI获取状态寄存器
 ***************************************************************/
FlagStatus PVT_GetStatus(void)
{
    return (READ_REG(PVT->DATA_VALID) ? SET : RESET);
}

/****************************************************************
  * 函数      : PVT_PrintReg()
  * 参数      : PVTx: PVT peripheral
  * 返回值     : None
  * 描述      : PVT 打印寄存器
 ***************************************************************/
void PVT_PrintReg(void)
{        
    DEBUG_PRINT_REG(PVT->APB_CTRL);
    DEBUG_PRINT_REG(PVT->MODE_CTRL);
    DEBUG_PRINT_REG(PVT->TRIMO_CTRL);
    DEBUG_PRINT_REG(PVT->TRIMG_CTRL);
    DEBUG_PRINT_REG(PVT->SENSOR_DATA);
    DEBUG_PRINT_REG(PVT->DATA_VALID);
    DEBUG_PRINT_REG(PVT->SENSOR_ENA);
}

