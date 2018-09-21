/*******************************************************************************
  * @file    acu_uart.c
  * @author  DengLin SOC Team
  * @version V0.0.1
  * @date    2-june-2018
  * @brief   This file contains all the functions prototypes for the UART 
  *          firmware library.
 ******************************************************************************/
#include "acu_uart.h"

/****************************************************************
  * 函数      : UART_DeInit()
  * 参数      : UARTx:    串口类型指针        
  * 返回值     : None
  * 描述      : 复位串口
 ***************************************************************/
void UART_DeInit(UART_TypeDef *UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    RCC_APBPeriphResetCmd(UART_SC, 0, SET);
    RCC_APBPeriphClockCmd(UART_SC, 0, DISABLE);
    RCC_APBPeriphIsoEnCmd(UART_SC, DISABLE);
}

/****************************************************************
  * 函数      : UART_Init()
  * 参数      : UARTx:            串口类型指针    
              UART_InitStruct:  初始化结构体
  * 返回值     : None
  * 描述      : 串口初始化
 ***************************************************************/
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
    uint32_t apbclock = 0x00;
    uint32_t integerdivider = 0x00;
    uint32_t fractionaldivider = 0x00;
    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));  
    assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
    assert_param(IS_UART_STP(UART_InitStruct->UART_StopBits));
    assert_param(IS_UART_FIFO_EN(UART_InitStruct->UART_FIFOControl));
    assert_param(IS_UART_PARITY(UART_InitStruct->UART_ParityMode));
    assert_param(IS_UART_MODE(UART_InitStruct->UART_TransmitMode));
    assert_param(IS_UART_IRDA(UART_InitStruct->UART_IrDAMode));
    assert_param(IS_UART_HW_FLOW_CTRL(UART_InitStruct->UART_HardwareFlowControl));
    assert_param(IS_UART_LBE(UART_InitStruct->UART_LoopBackControl));

    /*----------------------- System Management Configuration -----------------------------*/
    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    RCC_APBPeriphClockCmd(UART_SC, 0, ENABLE);
    RCC_APBPeriphIsoEnCmd(UART_SC, ENABLE);

    /*----------------------- USART BRR Configuration -----------------------------*/
    apbclock = SystemCoreClock; /* apbclock_max = 100MHz */
    
    /* Integer part computing in case Oversampling mode is 16 Samples */
    integerdivider = (25 * apbclock) / (2 * (UART_InitStruct->UART_BaudRate / 5)); /*(1000 * apbclock) / (16 * UART_InitStruct->UART_BaudRate) */ 
    UARTx->IBRD = (uint16_t)(integerdivider / 1000);
    
    /* Determine the fractional part */
    fractionaldivider = ((integerdivider % 1000) * 64 + 500);
    UARTx->FBRD = (uint16_t)(fractionaldivider / 1000);

    /*----------------------- UART Line Control Configuration ---------------------*/
    UARTx->LCR = UART_InitStruct->UART_WordLength | 
                 UART_InitStruct->UART_FIFOControl |
                 UART_InitStruct->UART_StopBits | 
                 UART_InitStruct->UART_ParityMode;
    
    /*----------------------- USART Control Configuration -------------------------*/
    UARTx->CR = UART_InitStruct->UART_TransmitMode | 
                UART_InitStruct->UART_IrDAMode |
                UART_InitStruct->UART_HardwareFlowControl | 
                UART_InitStruct->UART_LoopBackControl;
        
    /*----------------------- USART FIFO Configuration -----------------------------*/
    if (UART_InitStruct->UART_FIFOControl)
    {
        UARTx->IFLS = UART_InitStruct->UART_FIFOTx | UART_InitStruct->UART_FIFORx;
    }
}

/****************************************************************
  * 函数      : UART_StructInit()
  * 参数      : UART_InitStruct:  初始化结构体
  * 返回值     : None
  * 描述      : 串口结构体初始化
 ***************************************************************/
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
    UART_InitStruct->UART_BaudRate = 115200;
    UART_InitStruct->UART_WordLength = UART_WLEN_8b;
    UART_InitStruct->UART_StopBits = UART_STP_1b;
    UART_InitStruct->UART_FIFOControl = UART_FIFO_DIS;
    UART_InitStruct->UART_ParityMode = UART_PARITY_NO;
    UART_InitStruct->UART_TransmitMode = UART_MODE_TX_RX;
    UART_InitStruct->UART_IrDAMode = UART_IRDA_NORMAL;
    UART_InitStruct->UART_HardwareFlowControl = UART_HW_FLOW_CTRL_NONE;
    UART_InitStruct->UART_LoopBackControl = UART_MODE_NORMAL;
    UART_InitStruct->UART_FIFOTx = UART_FIFO_LEVEL_TX1_8;
    UART_InitStruct->UART_FIFORx = UART_FIFO_LEVEL_RX1_8;
}

/****************************************************************
  * 函数      : UART_Cmd()
  * 参数      : UARTx:        串口类型指针
              NewState:     ENABLE
                            DISABLE
  * 返回值     : None
  * 描述      : 串口功能使能
 ***************************************************************/
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    if (NewState == ENABLE)
    {
        SET_BIT(UARTx->CR, UART_ENABLE);
    }
    else
    {
        CLEAR_BIT(UARTx->CR, UART_ENABLE);
    }
}

/****************************************************************
  * 函数      : UART_ITConfig()
  * 参数      : UARTx:        串口类型指针
              UART_IT:      UART_IT_OE
                            UART_IT_BE
                            UART_IT_PE
                            UART_IT_FE               
                            UART_IT_RT                     
                            UART_IT_TX                     
                            UART_IT_RX                   
                            UART_IT_DSR                   
                            UART_IT_DCD                  
                            UART_IT_CTS                   
                            UART_IT_RIM                  
              NewState:     ENABLE
                            DISABLE
  * 返回值     : None
  * 描述      : 中断配置
 ***************************************************************/
void UART_ITConfig(UART_TypeDef* UARTx, uint16_t UART_IT, FunctionalState NewState)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_IT(UART_IT));

    if (NewState == ENABLE)
    {
        SET_BIT(UARTx->IMSC, UART_IT);
    }
    else
    {
        CLEAR_BIT(UARTx->IMSC, UART_IT);
    }
}

/****************************************************************
  * 函数      : UART_DMACmd()
  * 参数      : UARTx:        串口类型指针
              UART_DMAReq:  UART_DMA_DIS    
                            UART_DMA_TX_EN 
                            UART_DMA_RX_EN 
                            UART_DMA_TX_RX_EN 
              NewState:     ENABLE
                            DISABLE
  * 返回值     : None
  * 描述      : DMA使能
 ***************************************************************/
void UART_DMACmd(UART_TypeDef* UARTx, uint16_t UART_DMAReq, FunctionalState NewState)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DMA_EN(UART_DMAReq));

    if (NewState == ENABLE)
    {
        SET_BIT(UARTx->DMACR, UART_DMAReq);
    }
    else
    {
        CLEAR_BIT(UARTx->DMACR, UART_DMAReq);
    }
}

/****************************************************************
  * 函数      : UART_SendData()
  * 参数      : UARTx: 串口类型指针
  * 返回值     : None
  * 描述      : 从数据寄存器写入数据
 ***************************************************************/
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DATA(Data)); 

    /* Transmit Data */
    UARTx->DR = (Data & 0xFF);
}

/****************************************************************
  * 函数      : UART_ReceiveData()
  * 参数      : UARTx: 串口类型指针
  * 返回值     : 返回数据
  * 描述      : 从数据寄存器获取数据
 ***************************************************************/
uint8_t UART_ReceiveData(UART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    
    /* Receive Data */
    return (uint8_t)(UARTx->DR & 0xFF);
}

/****************************************************************
  * 函数      : UART_SendBreak()
  * 参数      : UARTx: 串口类型指针
  * 返回值     : None
  * 描述      : 发送break信号
 ***************************************************************/
void UART_SendBreak(UART_TypeDef* UARTx)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    SET_BIT(UARTx->LCR, UART_SEND_BREAK);
}

/****************************************************************
  * 函数      : UART_IrDACmd()
  * 参数      : UARTx: 串口类型指针
              NewState: ENABLE
                        DISABLE
  * 返回值     : None
  * 描述      : 开关IRDA功能
 ***************************************************************/
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    if (NewState == ENABLE)
    {
        SET_BIT(UARTx->CR, UART_IRDA_ENABLE);
    }
    else
    {
        CLEAR_BIT(UARTx->CR, UART_IRDA_ENABLE);
    }
}

/****************************************************************
  * 函数      : UART_GetFlagStatus()
  * 参数      : UARTx: 串口类型指针
              UART_IT: 状态标志
  * 返回值     : None
  * 描述      : 获取状态寄存器
 ***************************************************************/
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint16_t UART_FLAG)
{    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_FLAG(UART_FLAG));
    
    return ((UARTx->FR & UART_FLAG) ? SET : RESET);
}

/****************************************************************
  * 函数      : UART_GetRawITStatus()
  * 参数      : UARTx: 串口类型指针
              UART_IT: 中断标志
  * 返回值     : None
  * 描述      : 获取Raw中断状态寄存器
 ***************************************************************/
ITStatus UART_GetRawITStatus(UART_TypeDef* UARTx, uint16_t UART_IT)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_GET_IT(UART_IT));
    
    return ((UARTx->RIS & UART_IT) ? SET : RESET);
}

/****************************************************************
  * 函数      : UART_GetMaskITStatus()
  * 参数      : UARTx: 串口类型指针
              UART_IT: 中断标志
  * 返回值     : None
  * 描述      : 获取Mask中断状态寄存器
 ***************************************************************/
ITStatus UART_GetMaskITStatus(UART_TypeDef* UARTx, uint16_t UART_IT)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_GET_IT(UART_IT));
    
    return ((UARTx->MIS & UART_IT) ? SET : RESET);
}

/****************************************************************
  * 函数      : UART_ClearITStatus()
  * 参数      : UARTx: 串口类型指针
              UART_IT: 中断标志
  * 返回值     : None
  * 描述      : 清除中断状态寄存器
 ***************************************************************/
void UART_ClearITStatus(UART_TypeDef* UARTx, uint16_t UART_IT)
{    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CLEAR_IT(UART_IT));
    
    CLEAR_BIT(UARTx->ICR, UART_IT);
}

/****************************************************************
  * 函数      : UART_PrintReg()
  * 参数      : UARTx: 串口类型指针
  * 返回值     : None
  * 描述      : 打印串口寄存器的值
 ***************************************************************/
void UART_PrintReg(UART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    
    DEBUG_PRINT_REG(UARTx->DR);
    DEBUG_PRINT_REG(UARTx->RSR);
    DEBUG_PRINT_REG(UARTx->FR);
    DEBUG_PRINT_REG(UARTx->ILPR);
    DEBUG_PRINT_REG(UARTx->IBRD);
    DEBUG_PRINT_REG(UARTx->FBRD);
    DEBUG_PRINT_REG(UARTx->LCR);
    DEBUG_PRINT_REG(UARTx->CR);
    DEBUG_PRINT_REG(UARTx->IFLS);
    DEBUG_PRINT_REG(UARTx->IMSC);
    DEBUG_PRINT_REG(UARTx->RIS);
    DEBUG_PRINT_REG(UARTx->MIS);
    DEBUG_PRINT_REG(UARTx->ICR);
    DEBUG_PRINT_REG(UARTx->DMACR);
}

