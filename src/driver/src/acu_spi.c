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
void SPI_DeInit(SPI_TypeDef* SPIx)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    if (SPIx == SPI0)
    {
        RCC_APBPeriphResetCmd(SPI_SC, 0, SET);
        RCC_APBPeriphClockCmd(SPI_SC, 0, DISABLE);
        RCC_APBPeriphIsoEnCmd(SPI_SC, DISABLE);
    }
    else
    {
        RCC_APBPeriphResetCmd(SPI_SC, 1, SET);
        RCC_APBPeriphClockCmd(SPI_SC, 1, DISABLE);
        RCC_APBPeriphIsoEnCmd(SPI_SC, DISABLE);
    }
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
    uint16_t TempShort = 0;
    uint32_t Scr = 0;
    uint16_t CpsDiv = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;
    
    /* check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));   
    /* Check the SPI parameters */
    assert_param(IS_SPI_LBM(SPI_InitStruct->SPI_LBM));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
    assert_param(IS_SPI_FRAME(SPI_InitStruct->SPI_FRAME));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
    assert_param(IS_SPI_BAUDRATE(SPI_InitStruct->SPI_Baudrate));
    assert_param(IS_SPI_FIFO_TH(SPI_InitStruct->SPI_TX_FIFO));
    assert_param(IS_SPI_FIFO_TH(SPI_InitStruct->SPI_RX_FIFO));
    
    /* SPIx CR0 Configuration */
    TempShort = (uint16_t)( SPI_InitStruct->SPI_Mode | SPI_InitStruct->SPI_DataSize | 
                            SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_FRAME | 
                            SPI_InitStruct->SPI_CPHA | SPI_SCR);
    TempShort &= ~SPI_DataSize_16b;
    TempShort |= SPI_InitStruct->SPI_DataSize;
    SPIx->CR0 = TempShort;

    /* SPIx CR1 Configuration */
    SPIx->CR1 = SPI_InitStruct->SPI_LBM;
    
    /* SPIx CPSR Configuration */
    RCC_SYSCLKGetFreq(&RCC_ClocksStatus);
    Scr = RCC_ClocksStatus.FCLK_Frequency / (SPI_SCR + 1);
    TempShort = Scr / SPI_InitStruct->SPI_Baudrate;
    CpsDiv = TempShort + (TempShort % 2); /* CPSDVSR must an even value 2 - 254 */
    SPIx->CPSR = CpsDiv;
    
    /* SPIx FIFOTH Configuration */
    SPIx->FIFOTH = (SPI_InitStruct->SPI_RX_FIFO << 8) | SPI_InitStruct->SPI_TX_FIFO;
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
    /* Initialize the SPI_Baudrate */
    SPI_InitStruct->SPI_Baudrate = SPI_BAUDRATE;
    /* Initialize the SPI_TX_RX_FIFO */
    SPI_InitStruct->SPI_TX_FIFO = SPI_FIFO_TX_TH - 1;
    SPI_InitStruct->SPI_RX_FIFO = SPI_FIFO_RX_TH - 1;
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
        SET_BIT(SPIx->CR1, SPI_ENABLE);
    }
    else
    {
        CLEAR_BIT(SPIx->CR1, SPI_ENABLE);
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
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_GET_FLAG(SPI_FLAG));

    return  ((SPIx->SR & SPI_FLAG) ? SET : RESET);
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
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_GET_RIT_FLAG(SPI_RIT));

    return ((SPIx->RIS & SPI_RIT) ? SET : RESET);
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
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_GET_MIT_FLAG(SPI_MIT));

    return ((SPIx->MIS & SPI_MIT) ? SET : RESET);
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

