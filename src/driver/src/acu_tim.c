#include "acu_tim.h"

/****************************************************************
  * 函数      : TIM_DeInit()
  * 参数      : None  
  * 返回值     : None
  * 描述      : TIM复位all寄存器
 ***************************************************************/
void TIM_DeInit(void)
{
    RCC_APBPeriphResetCmd(TIM_SC, 0, SET);
    RCC_APBPeriphClockCmd(TIM_SC, 0, DISABLE);
    RCC_APBPeriphIsoEnCmd(TIM_SC, DISABLE);
}

/****************************************************************
  * 函数      : TIM_Init()
  * 参数      : TIMx:     类型指针  
              TIM_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : TIM初始化
 ***************************************************************/
void TIM_Init(TIM_TypeDef* TIMx, TIM_InitTypeDef *TIM_InitStruct)
{
    uint32_t apbclock = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_MODE(TIM_InitStruct->TIM_Mode));
    assert_param(IS_TIM_TIME(TIM_InitStruct->TIM_TimingTime));
    
    /*------------------ System Management Configuration ---------------*/
    RCC_APBPeriphResetCmd(TIM_SC, 0, RESET);
    RCC_APBPeriphClockCmd(TIM_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(TIM_SC, ENABLE);

    /*------------------ TIMx TimerNLoadCountRegister Configuration ---------------*/
    if (TIM_InitStruct->TIM_Mode == FREE_RUNNING)
    {
        TIMx->LC = 0xFFFFFFFF;
    }
    else
    {
        RCC_SYSCLKGetFreq(&RCC_ClocksStatus);
        apbclock = RCC_ClocksStatus.FCLK_Frequency;
        TIMx->LC = apbclock / (1000 / TIM_InitStruct->TIM_TimingTime); /* 1-1000ms */
    }

    /*---------------------------- TIMx Mode Configuration ------------------------*/
    TIMx->CR |= TIM_InitStruct->TIM_Mode;
}

/****************************************************************
  * 函数      : TIM_StructInit()
  * 参数      : TIM_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : TIM默认初始化
 ***************************************************************/
void TIM_StructInit(TIM_InitTypeDef* TIM_InitStruct)
{
    /* initialize the TIM_Mode member */
    TIM_InitStruct->TIM_Mode = USER_DEFINED;
    /* Initialize the TIM_TimingTime member */
    TIM_InitStruct->TIM_TimingTime = TIM_TIMING_TIME;
}

/****************************************************************
  * 函数      : TIM_Cmd()
  * 参数      : TIMx:     类型指针  
              NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : TIM功能使能配置
 ***************************************************************/
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        SET_BIT(TIMx->CR, TIM_ENABLE);
    }
    else
    {
        CLEAR_BIT(TIMx->CR, TIM_ENABLE);
    }
}

/****************************************************************
  * 函数      : TIM_GetCounter()
  * 参数      : TIMx:     类型指针
  * 返回值     : None
  * 描述      : 获取当前定时器值
 ***************************************************************/
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    return TIMx->CV;
}

/****************************************************************
  * 函数      : TIM_ITConfig()
  * 参数      : TIMx:     类型指针
              NewState: ENABLE / DISABLE   
  * 返回值     : None
  * 描述      : 设置中断
 ***************************************************************/
void TIM_ITConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    if (NewState == ENABLE)
    {
        CLEAR_BIT(TIMx->CR, TIM_INT_ENABLE);
    }
    else
    {
        SET_BIT(TIMx->CR, TIM_INT_ENABLE);
    }
}

/****************************************************************
  * 函数      : TIM_ClearIT()
  * 参数      : TIMx:     类型指针                
  * 返回值     : None
  * 描述      : 清除中断标志
 ***************************************************************/
uint32_t TIM_ClearIT(TIM_TypeDef* TIMx)
{
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    
    return TIMx->EOI;
}

/****************************************************************
  * 函数      : TIM_GetITStatus()
  * 参数      : TIMx:     类型指针                
  * 返回值     : None
  * 描述      : 获取中断状态
 ***************************************************************/
uint32_t TIM_GetITStatus(TIM_TypeDef* TIMx)
{
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    
    return TIMx->IS;
}

