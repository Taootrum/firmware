/*******************************************************************************
  * @file    acu_spi.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Module Function. 
 ******************************************************************************/
#include "acu_spi.h"

/****************************************************************
  * 函数      : SPI_DeInit()
  * 参数      : 
              SPIx: SPI peripheral
  * 返回值     : None
  * 描述      : SPI清除初始化
 ***************************************************************/
void SPI_DeInit(APBSYS_TypeDef* SPIx)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB_PERIPH(SPIx));
    RCC_APBPeriphResetCmd(SPIx, SET);
}
  
/****************************************************************
  * 函数      : SPI_Init()
  * 参数      : 
              SPIx: SPI peripheral
              SPI_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : SPI初始化
 ***************************************************************/
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
    /* check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));   

    /* Check the SPI parameters */
    assert_param(IS_SPI_LBM(SPI_InitStruct->SPI_LBM));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
    assert_param(IS_SPI_FRAME(SPI_InitStruct->SPI_FRAME));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
    assert_param(IS_SPI_BAUDRATE(SPI_InitStruct->SPI_BaudRate));
    assert_param(IS_SPI_CPSDVSR(SPI_InitStruct->SPI_CPSR));
    assert_param(IS_SPI_FIFO_TH(SPI_InitStruct->SPI_FIFO));
    
    /* SPIx CR1 Configuration */
    SPIx->CR0 = (uint16_t)( SPI_InitStruct->SPI_Mode | SPI_InitStruct->SPI_DataSize | 
                            SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_FRAME | 
                            SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_BaudRate);

    /* SPIx CR2 Configuration */
    SPIx->CR1 = SPI_InitStruct->SPI_LBM;
    /* SPIx CPSR Configuration */
    SPIx->CPSR = SPI_InitStruct->SPI_CPSR;
    /* SPIx FIFOTH Configuration */
    SPIx->FIFOTH = (SPI_InitStruct->SPI_FIFO << 8) | SPI_InitStruct->SPI_FIFO;
}
  
/****************************************************************
  * 函数      : SPI_StructInit()
  * 参数      : 
              SPI_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : SPI默认初始化
 ***************************************************************/
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
    /* Initialize the SPI_Direction member */
    SPI_InitStruct->SPI_LBM = SPI_MODE_NORMAL;
    /* initialize the SPI_Mode member */
    SPI_InitStruct->SPI_Mode = SPI_MODE_MASTER;
    /* initialize the SPI_DataSize member */
    SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
    /* initialize the SPI_DataSize member */
    SPI_InitStruct->SPI_FRAME = SPI_FRAME_MOTOROLA;
    /* Initialize the SPI_CPOL member */
    SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
    /* Initialize the SPI_CPHA member */
    SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
    /* Initialize the SPI_BaudRatePrescaler member */
    SPI_InitStruct->SPI_BaudRate = SPI_BAUDRATE;
    SPI_InitStruct->SPI_CPSR = SPI_CPSDVSR;
    SPI_InitStruct->SPI_FIFO = SPI_FIFO_TH;
}
  
/****************************************************************
  * 函数      : SPI_Cmd()
  * 参数      : 
              SPIx: spi外设
              NewState: 使能状态
  * 返回值     : None
  * 描述      : SPI使能/关闭
 ***************************************************************/
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        SET_BIT(SPIx->CR1, SPI_EN);
    }
    else
    {
        CLEAR_BIT(SPIx->CR1, SPI_EN);
    }
}

/****************************************************************
  * 函数      : SPI_SendData()
  * 参数      : SPIx: SPI peripheral
              Data: data register          
  * 返回值     : None
  * 描述      : 向数据寄存器写数据
 ***************************************************************/
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* Write in the DR register the data to be sent */
  SPIx->DR = Data;
}

/****************************************************************
  * 函数      : SPI_ReceiveData()
  * 参数      : SPIx: SPI peripheral
              Data: data register          
  * 返回值     : None
  * 描述      : 从数据寄存器读数据
 ***************************************************************/
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    return SPIx->DR;
}

/****************************************************************
  * 函数      : SPI_DataSizeConfig()
  * 参数      : SPIx: SPI peripheral
              SPI_DataSize: SPI_DataSize_4b
                            SPI_DataSize_5b
                            SPI_DataSize_6b
                            SPI_DataSize_7b
                            SPI_DataSize_8b
                            SPI_DataSize_9b
                            SPI_DataSize_10b 
                            SPI_DataSize_11b              
                            SPI_DataSize_12b            
                            SPI_DataSize_13b             
                            SPI_DataSize_14b               
                            SPI_DataSize_15b             
                            SPI_DataSize_16b           
  * 返回值     : None
  * 描述      : 向系统指定寄存器地址写数据
 ***************************************************************/
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
  
  /* Clear DFF bit */
  SPIx->CR1 &= ~SPI_DataSize_16b;
  /* Set new DFF bit value */
  SPIx->CR1 |= SPI_InitStruct->SPI_DataSize;
}
  
/****************************************************************
  * 函数      : SPI_GetStatus()
  * 参数      : SPIx: SPI peripheral
              SPI_FLAG: SPI_FLAG_TXE 
                        SPI_FLAG_TXNF
                        SPI_FLAG_RXNE
                        SPI_FLAG_RXF
                        SPI_FLAG_BSY
  * 返回值     : None
  * 描述      : SPI获取状态寄存器
 ***************************************************************/
FlagStatus SPI_GetStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG)
{
    FlagStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_GET_FLAG(SPI_FLAG));
    bitstatus = (SPIx->SR & (uint32_t)SPI_FLAG) ? SET : RESET;

    return  bitstatus;
}

/****************************************************************
  * 函数      : SPI_ITConfig()
  * 参数      : 
              SPIx: spi外设
              SPI_IT: SPI_IT_TXIM
                      SPI_IT_RXIM
                      SPI_IT_RTIM
                      SPI_IT_RORIM
              NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : SPI中断配置
 ***************************************************************/
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_CONFIG_IT(SPI_IT));

    if (NewState == ENABLE)
    {
        SET_BIT(SPIx->IMSC, SPI_IT);
    }
    else
    {
        CLEAR_BIT(SPIx->IMSC, SPI_IT);
    }
}

/****************************************************************
  * 函数      : SPI_GetRawITStatus()
  * 参数      : SPIx: SPI peripheral
              SPI_FLAG: SPI_RIT_TXRIS                
                        SPI_RIT_RXRIS                 
                        SPI_RIT_RTRIS                  
                        SPI_RIT_RORRIS                 
  * 返回值     : None
  * 描述      : SPI获取RAW中断状态
 ***************************************************************/
ITStatus SPI_GetRawITStatus(SPI_TypeDef* SPIx, uint8_t SPI_RIT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_GET_RIT_FLAG(SPI_RIT));
  bitstatus = ((SPIx->RIS & SPI_RIT) == (uint16_t)SET) ? SET : RESET;
  
  return  bitstatus;
}

/****************************************************************
  * 函数      : SPI_GetRawITStatus()
  * 参数      : SPIx: SPI peripheral
              SPI_FLAG: SPI_RIT_TXRIS                
                        SPI_RIT_RXRIS                 
                        SPI_RIT_RTRIS                  
                        SPI_RIT_RORRIS                 
  * 返回值     : None
  * 描述      : SPI获取RAW中断状态
 ***************************************************************/
ITStatus SPI_GetMaskITStatus(SPI_TypeDef* SPIx, uint8_t SPI_MIT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_GET_MIT_FLAG(SPI_MIT));
  bitstatus = ((SPIx->MIS & SPI_MIT) == (uint16_t)SET) ? SET : RESET;
  
  return  bitstatus;
}

/****************************************************************
  * 函数      : SPI_ClearIT()
  * 参数      : 
              SPIx: SPI peripheral
              SPI_ITClear: SPI_IT_RTC
                           SPI_IT_RORC
  * 返回值     : None
  * 描述      : 向系统指定寄存器地址写数据
 ***************************************************************/
void SPI_ClearIT(SPI_TypeDef* SPIx, uint16_t SPI_ITClear)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_CLEAR_IT(SPI_ITClear));

    SET_BIT(SPIx->ICR, SPI_ITClear);
}
  
/****************************************************************
  * 函数      : SPI_DMACmd()
  * 参数      : SPIx: SPI peripheral
              SPI_DMA: SPI_DMA_TX
                       SPI_DMA_RX
              NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : SSP DMA控制寄存器设置
 ***************************************************************/
void SPI_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_DMA, FunctionalState NewState)
{    
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DMA(SPI_DMA));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState == ENABLE)
    {
        SET_BIT(SPIx->DMACR, SPI_DMA);
    }
    else
    {
        CLEAR_BIT(SPIx->DMACR, SPI_DMA);
    }
}

/****************************************************************
  * 函数      : SPI_PrintReg()
  * 参数      : SPIx: SPI peripheral
  * 返回值     : None
  * 描述      : SSP FIFO阈值设置
 ***************************************************************/
void SPI_PrintReg(SPI_TypeDef* SPIx)
{        
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    
    DEBUG_PRINT_REG(SPIx->CR0);
    DEBUG_PRINT_REG(SPIx->CR1);
    DEBUG_PRINT_REG(SPIx->DR);
    DEBUG_PRINT_REG(SPIx->SR);
    DEBUG_PRINT_REG(SPIx->CPSR);
    DEBUG_PRINT_REG(SPIx->IMSC);
    DEBUG_PRINT_REG(SPIx->RIS);
    DEBUG_PRINT_REG(SPIx->MIS);
    DEBUG_PRINT_REG(SPIx->ICR);
    DEBUG_PRINT_REG(SPIx->DMACR);
    DEBUG_PRINT_REG(SPIx->FIFOTH);
}
