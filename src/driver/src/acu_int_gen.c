/*******************************************************************************
  * @file    avu_int_gen.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    30-Augest-2018
  * @brief   ACU INT gen Module Function. 
 ******************************************************************************/
#include "acu_int_gen.h"

/****************************************************************
  * 函数      : INT_DeInit()
  * 参数      : None  
  * 返回值     : None
  * 描述      : INT 功能禁止
 ***************************************************************/
void INT_DeInit(void)
{
    RCC_APBPeriphResetCmd(I2C_SC, 3, SET);
    RCC_APBPeriphClockCmd(I2C_SC, 3, DISABLE);
}

/****************************************************************
  * 函数      : INT_Init()
  * 参数      : None
  * 返回值     : None
  * 描述      : INT 初始化
 ***************************************************************/
void INT_Init(void)
{
    RCC_APBPeriphResetCmd(I2C_SC, 3, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 3, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

    WRITE_REG(INT_GEN->MASK, 0x3);
}

/****************************************************************
  * 函数      : INT_Generate()
  * 参数      : Type: TYPE_INT_OFF
                    TYPE_INT_PASSIVE
                    TYPE_INT_PCIE
  * 返回值     : None
  * 描述      : Int 创建中断
 ***************************************************************/
void INT_Generate(IntGenType Type)
{
    WRITE_REG(INT_GEN->STATUS, Type);
}

/****************************************************************
  * 函数      : INT_ClearIT()
  * 参数      : Type: TYPE_INT_PASSIVE
                    TYPE_INT_PCIE
  * 返回值     : None
  * 描述      : Int 清中断标志
 ***************************************************************/
void INT_ClearIT(void)
{
    WRITE_REG(INT_GEN->STATUS, TYPE_INT_OFF);
}

