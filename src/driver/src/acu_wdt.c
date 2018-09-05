/*******************************************************************************
  * @file    avu_iwdg.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU WDG Module Function. 
 ******************************************************************************/
#include "acu_wdt.h"

/****************************************************************
  * 函数      : WDT_DeInit()
  * 参数      : None  
  * 返回值     : None
  * 描述      : WDT Disable
 ***************************************************************/
void WDT_DeInit(void)
{
    RCC_APBPeriphResetCmd(WDT_SC, 0, SET);
    RCC_APBPeriphClockCmd(WDT_SC, 0, DISABLE);
    RCC_APBPeriphIsoEnCmd(WDT_SC, DISABLE);
}

/****************************************************************
  * 函数      : WDT_Init()
  * 参数      : WDT_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : WDT初始化
 ***************************************************************/
void WDT_Init(WDT_InitTypeDef *WDT_InitStruct)
{
    assert_param(IS_WDT_MODE(WDT_InitStruct->WDT_Mode));
    assert_param(IS_WDT_TOP(WDT_InitStruct->WDT_Top));
    
    /*---------------------------- System Management Configuration ------------------------*/
    RCC_APBPeriphResetCmd(WDT_SC, 0, RESET);
    RCC_APBPeriphClockCmd(WDT_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(WDT_SC, ENABLE);

    /*---------------------------- WDT Seed Configuration ------------------------*/
    WRITE_REG(WDT_SC->WDT_SPEEDUP, 0);

    /*---------------------------- WDT CR Configuration ------------------------*/
    WDT->CR |= WDT_InitStruct->WDT_Mode;

    /*---------------------------- WDT TOP Configuration ------------------------*/
    WDT->TORR = WDT_InitStruct->WDT_Top;
}

/****************************************************************
  * 函数      : WDT_StructInit()
  * 参数      : WDT_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : WDT默认初始化
 ***************************************************************/
void WDT_StructInit(WDT_InitTypeDef* WDT_InitStruct)
{
    /* initialize the WDT_Mode member */
    WDT_InitStruct->WDT_Mode = WDT_DIRECT_RESET;
    /* Initialize the WDT_Top member */
    WDT_InitStruct->WDT_Top = WDT_TOP;
}

/****************************************************************
  * 函数      : WDT_Cmd()
  * 参数      : NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : WDT功能使能配置
 ***************************************************************/
void WDT_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        SET_BIT(WDT->CR, WDT_ENABLE);
    }
    else
    {
        CLEAR_BIT(WDT->CR, WDT_ENABLE);
    }
}

/****************************************************************
  * 函数      : WDT_GetCounter()
  * 参数      : None
  * 返回值     : None
  * 描述      : 获取当前定时器值
 ***************************************************************/
uint32_t WDT_GetCounter(void)
{
    return WDT->CCVR;
}

/****************************************************************
  * 函数      : WDT_Restart()
  * 参数      : None
  * 返回值     : None
  * 描述      : 重启WDT
 ***************************************************************/
void WDT_Restart(void)
{
    WRITE_REG(WDT->CRR, 0x76);
}

/****************************************************************
  * 函数      : WDT_Pause()
  * 参数      : NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : 重启WDT
 ***************************************************************/
void WDT_Pause(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        WRITE_REG(WDT_SC->WDT_PAUSE, WDT_ENABLE);
    }
    else
    {
        WRITE_REG(WDT_SC->WDT_PAUSE, 0);
    }
}

/****************************************************************
  * 函数      : WDT_Pause()
  * 参数      : NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : 重启WDT
 ***************************************************************/
void WDT_DebugCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        WRITE_REG(WDT_SC->WDT_SPEEDUP, WDT_ENABLE);
    }
    else
    {
        WRITE_REG(WDT_SC->WDT_SPEEDUP, 0);
    }
}

/****************************************************************
  * 函数      : WDT_GetITStatus()
  * 参数      : None
  * 返回值     : None
  * 描述      : 获取中断状态
 ***************************************************************/
uint32_t WDT_GetITStatus(void)
{
    return WDT->STATUS;
}

/****************************************************************
  * 函数      : WDT_ClearIT()
  * 参数      : None
  * 返回值     : None
  * 描述      : 清除中断状态
 ***************************************************************/
uint32_t WDT_ClearIT(void)
{
    return WDT->EOI;
}

