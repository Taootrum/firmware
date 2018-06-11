/*******************************************************************************
  * @file    acu_gpio.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU GPIO Module Function. 
 ******************************************************************************/

#include "acu_gpio.h"

/****************************************************************
  * 函数      : GPIO_DeInit()
  * 参数      : GPIOx: GPIOx peripheral addr
  * 返回值     : None
  * 描述      : GPIOx清除初始化
 ***************************************************************/
void GPIO_DeInit(APBSYS_TypeDef*    GPIO)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(GPIO));
    RCC_APBPeriphResetCmd(GPIO, SET);
}

/****************************************************************
  * 函数      : GPIO_Init()
  * 参数      : GPIOx: GPIOx peripheral addr
              GPIO_InitStruct:  GPIO_InitStruct->GPIO_Direction
                                GPIO_InitStruct->GPIO_InterruptMask
                                GPIO_InitStruct->GPIO_PullStatus
                                GPIO_InitStruct->GPIO_InterruptType
  * 返回值     : None
  * 描述      : GPIOx初始化
 ***************************************************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    /* check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));   

    /* Check the SPI parameters */
    assert_param(IS_GPIO_DR(GPIO_InitStruct->GPIO_Direction));
    //assert_param(IS_GPIO_IM(GPIO_InitStruct->GPIO_InterruptMask));
    assert_param(IS_GPIO_PULL(GPIO_InitStruct->GPIO_PullStatus));
    //assert_param(IS_GPIO_IT(GPIO_InitStruct->GPIO_InterruptType));
    
    /* SPIx CR1 Configuration */
    GPIOx->DR = GPIO_InitStruct->GPIO_Direction;
    //GPIOx->GPIMR = GPIO_InitStruct->GPIO_InterruptMask;
    GPIOx->PUDE = GPIO_InitStruct->GPIO_PullStatus;
    //GPIOx->ITR = GPIO_InitStruct->GPIO_InterruptType;
}

/****************************************************************
  * 函数      : GPIO_StructInit()
  * 参数      : GPIO_InitStruct:  GPIO_InitStruct->GPIO_Direction
                                GPIO_InitStruct->GPIO_InterruptMask
                                GPIO_InitStruct->GPIO_PullStatus
                                GPIO_InitStruct->GPIO_InterruptType
  * 返回值     : None
  * 描述      : GPIO_StructInit默认初始化
 ***************************************************************/
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Direction = GPIO_INPUT;
    GPIO_InitStruct->GPIO_InterruptMask = GPIO_INTMASK_DIS;
    GPIO_InitStruct->GPIO_PullStatus = GPIO_PULLUP;
    GPIO_InitStruct->GPIO_InterruptType = GPIO_LOW_LEVEL;
}

/****************************************************************
  * 函数      : GPIO_IOPADMode()
  * 参数      : GPIOx:  GPIO0
                      GPIO1
                      ...
                      GPIO26
              IoPadMode: GPIO_IOPAD_GPIO
                         GPIO_IOPAD_FUNC
  * 返回值     : None
  * 描述      : GPIO 功能配置
 ***************************************************************/
void GPIO_IOPADMode(GPIO_TypeDef* GPIOx, uint32_t IoPadMode)
{    
    uint8_t GpioPinNum = 0;
    uint32_t GpioOffset = 0;
    GPIO_TypeDef* pGPIOx = GPIO_0;
    
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_IOPAD_MODE(IoPadMode));

    for (pGPIOx = GPIO0; pGPIOx <= GPIO26; pGPIOx++)
    {
        if (GPIOx == pGPIOx)
        {
            break;
        }
        GpioPinNum++;
    }

    GpioOffset = GpioPinNum % 8;
    GpioOffset = GPIO_IOPAD_GPIO << GpioOffset;
    if (IoPadMode == GPIO_IOPAD_GPIO)
    {
        if (GpioPinNum >= 24)
        {
            SET_BIT(IOPAD_SC->FCR3, GpioOffset);
        }
        else if (GpioPinNum >= 16)
        {
            SET_BIT(IOPAD_SC->FCR2, GpioOffset);
        }
        else if (GpioPinNum >= 8)
        {
            SET_BIT(IOPAD_SC->FCR1, GpioOffset);
        }
        else
        {
            SET_BIT(IOPAD_SC->FCR0, GpioOffset);
        }
    }
    else
    {
        if (GpioPinNum >= 24)
        {
            CLEAR_BIT(IOPAD_SC->FCR3, GpioOffset);
        }
        else if (GpioPinNum >= 16)
        {
            CLEAR_BIT(IOPAD_SC->FCR2, GpioOffset);
        }
        else if (GpioPinNum >= 8)
        {
            CLEAR_BIT(IOPAD_SC->FCR1, GpioOffset);
        }
        else
        {
            CLEAR_BIT(IOPAD_SC->FCR0, GpioOffset);
        }
    }
}

/****************************************************************
  * 函数      : GPIO_ReadInputData()
  * 参数      : GPIOx: GPIOx peripheral addr
  * 返回值     : 输入结果
  * 描述      : 读取GPIOx输入值
 ***************************************************************/
uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));   

    return GPIOx->IR;
}

/****************************************************************
  * 函数      : GPIO_ReadOutputData()
  * 参数      : GPIOx: GPIOx peripheral addr
  * 返回值     : 输入结果
  * 描述      : 读取GPIOx输出值
 ***************************************************************/
uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return GPIOx->OR;
}

/****************************************************************
  * 函数      : GPIO_SetBits()
  * 参数      : GPIOx: GPIOx peripheral addr
              Action：GPIO_RESET
                      GPIO_SET
  * 返回值     : None
  * 描述      : 设置GPIOx输出
 ***************************************************************/
void GPIO_SetOutput(GPIO_TypeDef* GPIOx, GPIO_Action Action)
{
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_ACTION(Action));

    GPIOx->OR = Action;
}

/****************************************************************
  * 函数      : GPIO_IntCmd()
  * 参数      : GPIOx: GPIOx peripheral addr
              NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : GPIO中断使能
 ***************************************************************/
void GPIO_IntCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState)
{
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE)
    {
        GPIOx->GPIMR = GPIO_INTMASK_EN;
    }
    else
    {
        GPIOx->GPIMR = GPIO_INTMASK_DIS;
    }
}

/****************************************************************
  * 函数      : GPIO_PrintReg()
  * 参数      : GPIOx: GPIO peripheral
  * 返回值     : None
  * 描述      : GPIO打印寄存器
 ***************************************************************/
void GPIO_PrintReg(GPIO_TypeDef* GPIOx)
{        
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
    DEBUG_PRINT_REG(GPIOx->IR);
    DEBUG_PRINT_REG(GPIOx->OR);
    DEBUG_PRINT_REG(GPIOx->DR);
    DEBUG_PRINT_REG(GPIOx->GIMR);
    DEBUG_PRINT_REG(GPIOx->GPIMR);
    DEBUG_PRINT_REG(GPIOx->PIR);
    DEBUG_PRINT_REG(GPIOx->ITR);
    DEBUG_PRINT_REG(GPIOx->IFR);
    DEBUG_PRINT_REG(GPIOx->ICR);
    DEBUG_PRINT_REG(GPIOx->PUDE);
}

void GPIO_IOPADPrintReg(IOPAD_TypeDef* IOPad)
{            
    DEBUG_PRINT_REG(IOPad->FCR0);
    DEBUG_PRINT_REG(IOPad->FCR1);
    DEBUG_PRINT_REG(IOPad->FCR2);
    DEBUG_PRINT_REG(IOPad->FCR3);
}

