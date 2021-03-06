/*******************************************************************************
  * @file    acu_i2c.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    26-June-2018
  * @brief   ACU IIC Module Function. 
 ******************************************************************************/
#include "acu_i2c.h"

/****************************************************************
  * 函数      : I2C_DeInit()
  * 参数      : I2Cx:     类型指针  
  * 返回值     : None
  * 描述      : I2C复位all寄存器
 ***************************************************************/
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    /* Check the parameters */
    if (I2Cx == I2C0)
    {
        RCC_APBPeriphResetCmd(I2C_SC, 0, SET);
        RCC_APBPeriphClockCmd(I2C_SC, 0, DISABLE);
    }
    else if (I2Cx == I2C1) 
    {
        RCC_APBPeriphResetCmd(I2C_SC, 1, SET);
        RCC_APBPeriphClockCmd(I2C_SC, 1, DISABLE);
    }
    else
    {
        RCC_APBPeriphResetCmd(I2C_SC, 2, SET);
        RCC_APBPeriphClockCmd(I2C_SC, 2, DISABLE);
    }
}

/****************************************************************
  * 函数      : I2C_Init()
  * 参数      : I2Cx:     类型指针  
              I2C_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : I2C初始化
 ***************************************************************/
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
    uint16_t result = 0;
    uint32_t apbclock = 0;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_SPEED(I2C_InitStruct->I2C_Speed));
    assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
    assert_param(IS_I2C_OWN_ADDRESS(I2C_InitStruct->I2C_OwnAddress));
    assert_param(IS_I2C_HS_MADDRESS(I2C_InitStruct->I2C_HSMasterAddress));
    assert_param(IS_I2C_ADDRESS_MODE(I2C_InitStruct->I2C_AddressMode));
    assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AckAddress));
    assert_param(IS_I2C_ACKNOWLEDGE(I2C_InitStruct->I2C_Acknowledge));
    assert_param(IS_I2C_FIFO_LEVEL(I2C_InitStruct->I2C_TxFIFOLevel));
    assert_param(IS_I2C_FIFO_LEVEL(I2C_InitStruct->I2C_RxFIFOLevel));

    /*---------------------------- System Management Configuration ------------------------*/
    if (I2Cx == I2C0)
    {
        RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
        RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    }
    else if (I2Cx == I2C1) 
    {
        RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
        RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    }
    else
    {
        RCC_APBPeriphResetCmd(I2C_SC, 2, RESET);
        RCC_APBPeriphClockCmd(I2C_SC, 2, ENABLE);
    }
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

    /*---------------------------- I2Cx mode Configuration ------------------------*/
    if (I2C_InitStruct->I2C_Mode == I2C_Mode_Passive)
    {
        I2Cx->SDA_CFG |= I2C_InitStruct->I2C_Mode;
    }
    else
    {
        I2Cx->SDA_CFG &= ~I2C_Mode_Passive;
        if (I2C_InitStruct->I2C_Mode == I2C_Mode_Master)
        {
            I2Cx->CR |= I2C_InitStruct->I2C_Mode;
        }
        else
        {
            I2Cx->CR &= ~I2C_Mode_Master;
        }
    }

    /*---------------------------- I2Cx Speed Configuration ------------------------*/
    I2Cx->CR |= I2C_Speed_3400k;
    if (I2C_InitStruct->I2C_Speed == I2C_Speed_100k)
    {
        I2Cx->CR &= ~I2C_Speed_400k;
    }
    else if (I2C_InitStruct->I2C_Speed == I2C_Speed_400k)
    {
        I2Cx->CR &= ~I2C_Speed_100k;
    }
    if (I2C_InitStruct->I2C_Mode == I2C_Mode_Master)
    {
        /* Get Fabric Clock */
        apbclock = SystemCoreClock;
        
        if (I2C_InitStruct->I2C_Speed == I2C_Speed_100k)
        {
            /* Standard mode */
            result = (uint16_t)(apbclock / 100000);
            I2Cx->SS_SCL_HCNT = result / 2;
            I2Cx->SS_SCL_LCNT = result / 2;
        }
        else if (I2C_InitStruct->I2C_Speed == I2C_Speed_400k) 
        {
            /* Fast mode */
            result = (uint16_t)(apbclock / 400000);
            I2Cx->FS_SCL_HCNT = result / 3;         /*I2C fast mode Tlow/Thigh = 2 */
            I2Cx->FS_SCL_LCNT = 2 * result / 3;
        }
        else 
        {
            /* High mode */
            result = (uint16_t)(apbclock / 7000000);
            //result = (uint16_t)(apbclock / 3400000);
            if (result < 28)
            {
                result = 28;
            }
            I2Cx->HS_SCL_HCNT = result / 2 - 8;     /*I2C high mode Tlow/Thigh = 1 */
            I2Cx->HS_SCL_LCNT = result / 2 - 1;

            /* Set Master Code */
            I2Cx->HS_MADDR = I2C_InitStruct->I2C_HSMasterAddress;
        }
    }
    
    /*---------------------------- I2Cx restart_enable Configuration ------------------------*/
    I2Cx->CR |= I2C_Restart_Enable;
    
    /*---------------------------- I2Cx Address Mode Configuration ------------------------*/
    if (I2C_InitStruct->I2C_AddressMode == I2C_Address_10bit)
    {
        I2Cx->CR |= I2C_Address_10bit;
    }
    else
    {
        I2Cx->CR &= ~I2C_Address_10bit;
    }

    /*---------------------------- I2Cx Own Address Configuration -----------------------*/
    /* I2C0 4bit external io control */
    if (I2C_InitStruct->I2C_OwnAddress)
    {
        I2Cx->SAR = (I2Cx == I2C0) ? I2C_InitStruct->I2C_OwnAddress << 4 : I2C_InitStruct->I2C_OwnAddress;
    }
    
    /*---------------------------- I2Cx Ack Address Configuration -----------------------*/
    I2Cx->TAR = I2C_InitStruct->I2C_AckAddress;

    /*---------------------------- I2Cx Acknowledge Configuration -----------------------*/
    I2Cx->ACK_GENERAL_CALL = I2C_InitStruct->I2C_Acknowledge;
    
    /*---------------------------- I2Cx FIFO Configuration -----------------------*/
    I2Cx->TX_TL = I2C_InitStruct->I2C_TxFIFOLevel;
    I2Cx->RX_TL = I2C_InitStruct->I2C_RxFIFOLevel;
}

/****************************************************************
  * 函数      : I2C_StructInit()
  * 参数      : I2C_InitStruct: 初始化结构体
  * 返回值     : None
  * 描述      : I2C默认初始化
 ***************************************************************/
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
    /* initialize the I2C_ClockSpeed member */
    I2C_InitStruct->I2C_Speed = I2C_Speed_400k;
    /* Initialize the I2C_Mode member */
    I2C_InitStruct->I2C_Mode = I2C_Mode_Master;
    /* Initialize the I2C_AddressMode */
    I2C_InitStruct->I2C_AddressMode = I2C_Address_7bit;
    /* Initialize the I2C_HSMasterAddress member */
    I2C_InitStruct->I2C_HSMasterAddress = 0x01;
    /* Initialize the I2C_OwnAddress member */
    I2C_InitStruct->I2C_OwnAddress = 0x05;
    /* Initialize the I2C_AcknowledgedAddress member */
    I2C_InitStruct->I2C_AckAddress = 0x55;
    /* Initialize the I2C_TxFIFOLevel member */
    I2C_InitStruct->I2C_TxFIFOLevel = I2C_FIFO_TX_LEVEL - 1;
    /* Initialize the I2C_RxFIFOLevel member */
    I2C_InitStruct->I2C_RxFIFOLevel = I2C_FIFO_RX_LEVEL - 1;
}

/****************************************************************
  * 函数      : I2C_Cmd()
  * 参数      : I2Cx:     类型指针  
              NewState: ENABLE/DISABLE
  * 返回值     : None
  * 描述      : I2C功能使能配置
 ***************************************************************/
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        SET_BIT(I2Cx->ENABLE, I2C_ENABLE);
    }
    else
    {
        CLEAR_BIT(I2Cx->ENABLE, I2C_ENABLE);
    }
}

/****************************************************************
  * 函数      : I2C_SendData()
  * 参数      : I2Cx:     类型指针         
  * 返回值     : None
  * 描述      : 发送一个字节数据
 ***************************************************************/
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Write in the DR register the data to be sent */
    I2Cx->DATACMD = Data;
}

/****************************************************************
  * 函数      : I2C_ReceiveData()
  * 参数      : I2Cx:     类型指针         
  * 返回值     : 一个字节数据
  * 描述      : 接收一个字节数据
 ***************************************************************/
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    
    return (uint8_t)I2Cx->DATACMD;
}

/****************************************************************
  * 函数      : I2C_GetFlagStatus()
  * 参数      : I2Cx:     类型指针
              I2C_FLAG: I2C_FLAG_SLV_ACTIVITY
                        I2C_FLAG_MST_ACTIVITY
                        I2C_FLAG_REF               
                        I2C_FLAG_RFNE                 
                        I2C_FLAG_TFE                  
                        I2C_FLAG_TFNF                
                        I2C_FLAG_ACTIVITY          
  * 返回值     : None
  * 描述      : 获取状态寄存器
 ***************************************************************/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{    
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_FLAG(I2C_FLAG));
        
    return ((I2Cx->STATUS & I2C_FLAG) ? SET : RESET);
}

/****************************************************************
  * 函数      : I2C_ITConfig()
  * 参数      : I2Cx:     类型指针
              I2C_IT:   I2C_IT_GEN_CALL                
                        I2C_IT_START_DET            
                        I2C_IT_STOP_DET                
                        I2C_IT_ACTIVITY           
                        I2C_IT_RX_DONE                  
                        I2C_IT_TX_ABRT  
                        I2C_IT_TX_EMPTY
                        I2C_IT_RD_REQ                  
                        I2C_IT_TX_OVER
                        I2C_IT_RX_FULL 
                        I2C_IT_RX_OVER                 
                        I2C_IT_RX_UNDER                
                        I2C_IT_INTR
              NewState: ENABLE / DISABLE   
  * 返回值     : None
  * 描述      : 设置中断
 ***************************************************************/
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_I2C_IT(I2C_IT));

    if (NewState != DISABLE)
    {
        SET_BIT(I2Cx->INTR_MASK, I2C_IT);
    }
    else
    {
        CLEAR_BIT(I2Cx->INTR_MASK, I2C_IT);
    }
}

/****************************************************************
  * 函数      : I2C_GetITStatus()
  * 参数      : I2Cx:     类型指针
              I2C_IT_STATUS:    I2C_IT_GEN_CALL                
                                I2C_IT_START_DET            
                                I2C_IT_STOP_DET                
                                I2C_IT_ACTIVITY           
                                I2C_IT_RX_DONE                  
                                I2C_IT_TX_ABRT  
                                I2C_IT_TX_EMPTY
                                I2C_IT_RD_REQ                  
                                I2C_IT_TX_OVER
                                I2C_IT_RX_FULL 
                                I2C_IT_RX_OVER                 
                                I2C_IT_RX_UNDER                
                                I2C_IT_INTR                 
  * 返回值     : None
  * 描述      : 获取MASK中断标志
 ***************************************************************/
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT_STATUS)
{    
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_IT_FLAG(I2C_IT_STATUS));
    
    return ((I2Cx->INTR_STAT & I2C_IT_STATUS) ? SET : RESET);
}

/****************************************************************
  * 函数      : I2C_GetRawITStatus()
  * 参数      : I2Cx:     类型指针
              I2C_IT_STATUS:    I2C_IT_GEN_CALL                
                                I2C_IT_START_DET            
                                I2C_IT_STOP_DET                
                                I2C_IT_ACTIVITY           
                                I2C_IT_RX_DONE                  
                                I2C_IT_TX_ABRT  
                                I2C_IT_TX_EMPTY
                                I2C_IT_RD_REQ                  
                                I2C_IT_TX_OVER
                                I2C_IT_RX_FULL 
                                I2C_IT_RX_OVER                 
                                I2C_IT_RX_UNDER                
                                I2C_IT_INTR                 
  * 返回值     : None
  * 描述      : 获取RAW中断标志
 ***************************************************************/
ITStatus I2C_GetRawITStatus(I2C_TypeDef* I2Cx, uint16_t I2C_IT_STATUS)
{    
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_IT_FLAG(I2C_IT_STATUS));
    
    return ((I2Cx->RAW_INTR_STAT & I2C_IT_STATUS) ? SET : RESET);
}

/****************************************************************
  * 函数      : I2C_ClearITStatus()
  * 参数      : I2Cx:     类型指针
              I2C_IT_STATUS:    I2C_IT_GEN_CALL                
                                I2C_IT_START_DET            
                                I2C_IT_STOP_DET                
                                I2C_IT_ACTIVITY           
                                I2C_IT_RX_DONE                  
                                I2C_IT_TX_ABRT                 
                                I2C_IT_RD_REQ                  
                                I2C_IT_TX_OVER                 
                                I2C_IT_RX_OVER                 
                                I2C_IT_RX_UNDER                
                                I2C_IT_INTR                 
  * 返回值     : None
  * 描述      : 清除中断标志
 ***************************************************************/
uint32_t I2C_ClearITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT_STATUS)
{
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_IT_FLAG(I2C_IT_STATUS));

    if (I2C_IT_STATUS == I2C_IT_GEN_CALL) {
        return I2Cx->CLR_INTR;
    } else if (I2C_IT_STATUS == I2C_IT_START_DET) {
        return I2Cx->CLR_GEN_CALL;
    } else if (I2C_IT_STATUS == I2C_IT_STOP_DET) {
        return I2Cx->CLR_STOP_DET;
    } else if (I2C_IT_STATUS == I2C_IT_ACTIVITY) {
        return I2Cx->CLR_ACTIVITY;
    } else if (I2C_IT_STATUS == I2C_IT_RX_DONE) {
        return I2Cx->CLR_RX_DONE;
    } else if (I2C_IT_STATUS == I2C_IT_TX_ABRT) {
        return I2Cx->CLR_TX_ABRT;
    } else if (I2C_IT_STATUS == I2C_IT_RD_REQ) {
        return I2Cx->CLR_RD_REQ;
    } else if (I2C_IT_STATUS == I2C_IT_TX_OVER) {
        return I2Cx->CLR_TX_OVER;
    } else if (I2C_IT_STATUS == I2C_IT_RX_OVER) {
        return I2Cx->CLR_RX_OVER;
    } else if (I2C_IT_STATUS == I2C_IT_RX_UNDER) {
        return I2Cx->CLR_RX_UNDER;
    } else{
        return I2Cx->CLR_INTR;
    }
}

/****************************************************************
  * 函数      : I2C_PrintReg()
  * 参数      : None
  * 返回值     : None
  * 描述      : 打印I2C寄存器配置
 ***************************************************************/
void I2C_PrintReg(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    
    DEBUG_PRINT_REG(I2Cx->CR);
    DEBUG_PRINT_REG(I2Cx->TAR);
    DEBUG_PRINT_REG(I2Cx->SAR);
    DEBUG_PRINT_REG(I2Cx->HS_MADDR);
    DEBUG_PRINT_REG(I2Cx->DATACMD);
    DEBUG_PRINT_REG(I2Cx->SS_SCL_HCNT);
    DEBUG_PRINT_REG(I2Cx->SS_SCL_LCNT);
    DEBUG_PRINT_REG(I2Cx->FS_SCL_HCNT);
    DEBUG_PRINT_REG(I2Cx->FS_SCL_LCNT);
    DEBUG_PRINT_REG(I2Cx->HS_SCL_HCNT);
    DEBUG_PRINT_REG(I2Cx->HS_SCL_LCNT);
    DEBUG_PRINT_REG(I2Cx->INTR_STAT);
    DEBUG_PRINT_REG(I2Cx->INTR_MASK);
    DEBUG_PRINT_REG(I2Cx->RAW_INTR_STAT);
    DEBUG_PRINT_REG(I2Cx->RX_TL);
    DEBUG_PRINT_REG(I2Cx->TX_TL);
    DEBUG_PRINT_REG(I2Cx->CLR_INTR);
    DEBUG_PRINT_REG(I2Cx->CLR_RX_UNDER);
    DEBUG_PRINT_REG(I2Cx->CLR_RX_OVER);
    DEBUG_PRINT_REG(I2Cx->CLR_TX_OVER);
    DEBUG_PRINT_REG(I2Cx->CLR_RD_REQ);
    DEBUG_PRINT_REG(I2Cx->CLR_TX_ABRT);
    DEBUG_PRINT_REG(I2Cx->CLR_RX_DONE);
    DEBUG_PRINT_REG(I2Cx->CLR_ACTIVITY);
    DEBUG_PRINT_REG(I2Cx->CLR_STOP_DET);
    DEBUG_PRINT_REG(I2Cx->CLR_START_DET);
    DEBUG_PRINT_REG(I2Cx->CLR_GEN_CALL);
    DEBUG_PRINT_REG(I2Cx->ENABLE);
    DEBUG_PRINT_REG(I2Cx->STATUS);
    DEBUG_PRINT_REG(I2Cx->TXFLR);
    DEBUG_PRINT_REG(I2Cx->RXFLR);
    DEBUG_PRINT_REG(I2Cx->TX_ABRT_SOURCE);
    DEBUG_PRINT_REG(I2Cx->ACK_GENERAL_CALL);
    DEBUG_PRINT_REG(I2Cx->ENABLE_STATUS);
    DEBUG_PRINT_REG(I2Cx->SDA_CFG);
}

