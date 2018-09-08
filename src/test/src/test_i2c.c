/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_i2c.h"
#include "i2c_passive.h"

/* I2C0 slave
   I2C1 master
   address 7bit
   poll
*/
TestStatus I2C_FunctionTest1(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x0, 0x1, 0x2, 0x3};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C0 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x05;
    I2C_InitStructure.I2C_AckAddress = 0x55;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C0, DISABLE);
    I2C_Init(I2C0, &I2C_InitStructure);
    I2C_Cmd(I2C0, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C1, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C0, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C0);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c0_slave i2c1_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C0 slave
   I2C1 master
   address 10bit
   poll
*/
TestStatus I2C_FunctionTest2(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x0, 0x1, 0x2, 0x3};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C0 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x05;
    I2C_InitStructure.I2C_AckAddress = 0x55;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C0, DISABLE);
    I2C_Init(I2C0, &I2C_InitStructure);
    I2C_Cmd(I2C0, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C1, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C0, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C0);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c0_slave i2c1_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C0 master
   I2C1 slave
   address 7bit
   poll
*/
TestStatus I2C_FunctionTest3(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x3, 0x2, 0x1, 0x0};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C1 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x56;
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
    
    /*!< I2C0 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x05;
    I2C_InitStructure.I2C_AckAddress = 0x56;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C0, DISABLE);
    I2C_Init(I2C0, &I2C_InitStructure);
    I2C_Cmd(I2C0, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C0, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C0, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C1);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c1_slave i2c0_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C0 master
   I2C1 slave
   address 10bit
   poll
*/
TestStatus I2C_FunctionTest4(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x3, 0x2, 0x1, 0x0};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C1 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x56;
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
    
    /*!< I2C0 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x05;
    I2C_InitStructure.I2C_AckAddress = 0x56;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C0, DISABLE);
    I2C_Init(I2C0, &I2C_InitStructure);
    I2C_Cmd(I2C0, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C0, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C0, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C1);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c1_slave i2c0_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C1 slave
   I2C2 master
   address 7bit
   poll
*/
TestStatus I2C_FunctionTest5(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x0, 0x1, 0x2, 0x3};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C1 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x56;
    I2C_InitStructure.I2C_AckAddress = 0x55;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
    
    /*!< I2C2 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x56;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C2, DISABLE);
    I2C_Init(I2C2, &I2C_InitStructure);
    I2C_Cmd(I2C2, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C2, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C2, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C1);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c0_slave i2c1_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C1 slave
   I2C2 master
   address 10bit
   poll
*/
TestStatus I2C_FunctionTest6(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x0, 0x1, 0x2, 0x3};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C1 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x56;
    I2C_InitStructure.I2C_AckAddress = 0x55;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x56;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C2, DISABLE);
    I2C_Init(I2C2, &I2C_InitStructure);
    I2C_Cmd(I2C2, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C2, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C2, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C1);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c0_slave i2c1_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C1 master
   I2C2 slave
   address 7bit
   poll
*/
TestStatus I2C_FunctionTest7(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x3, 0x2, 0x1, 0x0};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C2 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x56;
    I2C_InitStructure.I2C_AckAddress = 0x55;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C2, DISABLE);
    I2C_Init(I2C2, &I2C_InitStructure);
    I2C_Cmd(I2C2, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x56;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C1, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C2, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C2);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c1_slave i2c0_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C1 master
   I2C2 slave
   address 10bit
   poll
*/
TestStatus I2C_FunctionTest8(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[4] = {0x3, 0x2, 0x1, 0x0};
    uint8_t RxBuf[4] = {0x0, 0x0, 0x0, 0x0};
    uint8_t i = 0;

    /*!< I2C1 as slave */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x56;
    I2C_InitStructure.I2C_AckAddress = 0x55;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C2, DISABLE);
    I2C_Init(I2C2, &I2C_InitStructure);
    I2C_Cmd(I2C2, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_10bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x56;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 4 - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = 4 - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);

    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TFNF) == RESET);
        I2C_SendData(I2C1, TxBuf[i]);
    }
    
    for (i = 0 ; i < 4; i++)
    {
        while (I2C_GetFlagStatus(I2C2, I2C_FLAG_RFNE) == RESET);
        RxBuf[i] = I2C_ReceiveData(I2C2);
    }

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 4) == FAILED)
    {
        DEBUG_ERROR("i2c1_slave i2c0_master loopback fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C0 passive
   I2C1 master
   passive
*/
TestStatus I2C_FunctionTest9(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    uint8_t TxBuf[128] = {0xAA, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x55, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf5};
    uint8_t RxBuf[128] = {0x0};
    
    /*!< I2C Periph reset enable */
    I2C_DeInit(I2C0);
    I2C_DeInit(I2C1);
    RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x52;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = I2C_FIFO_TX_LEVEL - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = I2C_FIFO_RX_LEVEL - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);

    /* write system data */
    I2C_PassiveWriteBuffer(TxBuf, 0x2000000a, 16);
    I2C_PassiveReadBuffer(RxBuf, 0x2000000a, 16);

    /* Check the correctness of written data */
    if (Buffercmp(TxBuf, RxBuf, 16) == FAILED)
    {
        DEBUG_ERROR("i2c0_passive i2c1_master passive fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* printf i2c register */
TestStatus I2C_FunctionTestX(void)
{    
    DEBUG_MSG("I2C0------------------------------\r\n");
    I2C_PrintReg(I2C0);
    DEBUG_MSG("I2C1------------------------------\r\n");
    I2C_PrintReg(I2C1);
    return PASSED;
}

