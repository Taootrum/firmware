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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 2, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 2, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 2, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 2, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 2, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 2, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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

    /*!< I2C Periph reset enable */
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 2, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 2, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);

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
    uint8_t TxBuf[128] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    uint8_t RxBuf[128] = {0x0};

    /*!< I2C Periph reset enable */
    I2C_DeInit(I2C0);
    I2C_DeInit(I2C1);
    RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = I2C_FIFO_TX_LEVEL - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = I2C_FIFO_RX_LEVEL - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);

    /* write system data */
    I2C_PassiveWriteBuffer(&TxBuf[1], 0x20000001, 1);
    I2C_PassiveReadBuffer(RxBuf, 0x20000001, 1);
    printf_memory(RxBuf, 1);

    /* write system data */
    I2C_PassiveWriteBuffer(&TxBuf[5], 0x20000005, 1);
    I2C_PassiveReadBuffer(RxBuf, 0x20000005, 1);
    printf_memory(RxBuf, 1);

    /* write system data */
    I2C_PassiveWriteBuffer(TxBuf, 0x2000000a, 16);
    I2C_PassiveReadBuffer(RxBuf, 0x2000000a, 16);
    printf_memory(RxBuf, 16);

    /* Check the correctness of written dada */
    if (Buffercmp(TxBuf, RxBuf, 16) == FAILED)
    {
        DEBUG_ERROR("i2c0_passive i2c1_master passive fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* I2C0 passive
   I2C1 master
   DDR
*/
#define CU_CMD_BUF_SIZE     0xA8

uint32_t FeCmdBuf[CU_CMD_BUF_SIZE / 4] = {
    0x00010001, 0x00040080, 0x00000000, 0x00000000, 
    0x00010001, 0x00040000, 0xdeadbeef, 0x00000000, 
    0x00010001, 0x00040088, 0x80000000, 0x00000000, //(src addr lo)
    0x00010001, 0x0004008c, 0x00000000, 0x00000000, //(src addr hi)
    0x00010001, 0x00040090, 0x90000000, 0x00000000, //(dst addr lo)
    0x00010001, 0x00040094, 0x00000000, 0x00000000, //(dst addr hi)
    0x00010001, 0x000400a8, 0x00000200, 0x00000000, //(copy size)
    0x00010001, 0x00040098, 0x00000000, 0x00000000, //(src offset x)
    0x00010003, 0xffffffff, 0xee00a171, 0xd69f08b5, 
    0x00010006, 0x0000000f, 0xffffff00, 0x00000000, 
    0x00000009, 0x00000000
};

void CU_CommandInit(uint32_t srcAddr, uint32_t dstAddr, uint32_t size)
{
    FeCmdBuf[0xA] = srcAddr;
    FeCmdBuf[0x12] = dstAddr;
    FeCmdBuf[0x1A] = size;
    DDR_WriteMem((uint8_t *)FeCmdBuf, 0, CU_CMD_BUF_SIZE);
}

void CU_RegInit(uint32_t cmdBufAddr, uint32_t cmdBufSize)
{
    WRITE32(ACU_CU_BASE + 0x0004, 0x000103CF);
    WRITE32(ACU_CU_BASE + 0x0008, 0x00000003);
    WRITE32(ACU_CU_BASE + 0x0020, 0x00000004);
    WRITE32(ACU_CU_BASE + 0x0024, 0x00000302);
    WRITE32(ACU_CU_BASE + 0x0050, 0x1FFFFFFF);
    WRITE32(ACU_CU_BASE + 0x0054, 0x1FFFFFFF);
    WRITE32(ACU_CU_BASE + 0x0058, 0x1FFFFFFF);
    WRITE32(ACU_CU_BASE + 0x005C, 0x1FFFFFFF);
    WRITE32(ACU_CU_BASE + 0x0108, 0x0000001F);

    WRITE32(ACU_CU_BASE + 0x021c, cmdBufAddr);  /* Cmd buffer addr lo */
    WRITE32(ACU_CU_BASE + 0x0220, 0x00000000);  /* Cmd buffer addr hi */
    
    WRITE32(ACU_CU_BASE + 0x0224, cmdBufSize);  /* Cmd buffer size */
    WRITE32(ACU_CU_BASE + 0x0228, 0x0000000F);
    WRITE32(ACU_CU_BASE + 0x023C, 0xFFFFFFFF);
    WRITE32(ACU_CU_BASE + 0x0230, 0x00000002);  /* Kick off */
}

#define DLM_INTERRUPT
uint32_t TxData = 0xA1A2A3A4;
uint32_t RxData = 0xA5A6A7A8;

TestStatus I2C_FunctionTest10(void)
{
    I2C_InitTypeDef I2C_InitStructure;

#ifdef I2C_PASSIVE_WAY
    /*!< I2C Periph reset enable */
    I2C_DeInit(I2C0);
    I2C_DeInit(I2C1);
    RCC_APBPeriphResetCmd(I2C_SC, 0, RESET);
    RCC_APBPeriphResetCmd(I2C_SC, 1, RESET);
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);
    
    /*!< I2C1 as master */
    I2C_InitStructure.I2C_Speed = I2C_Speed_3400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x55;
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = I2C_FIFO_TX_LEVEL - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = I2C_FIFO_RX_LEVEL - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
#endif

#ifdef DLM_INTERRUPT
    WRITE_REG(CU_SC->DLM_INTSEL, 0x1);
	NVIC_EnableIRQ(CU_IRQn);
    __set_PRIMASK(0);
#endif
    
    /* write system data */
    DDR_WriteMem((uint8_t *)&TxData, 0x1000, 4);
    DDR_WriteMem((uint8_t *)&RxData, 0x1000 + 0x80, 4);

    /* CU DMA Copy */
    CU_CommandInit(0x1000, 0x1000 + 0x80, 4);
    CU_RegInit(0x0, CU_CMD_BUF_SIZE / 8);
    
    /* read system data */
#ifdef DLM_INTERRUPT
    while (RxData != 0xA1A2A3A4);
#else
    do
    {
        DDR_ReadMem((uint8_t *)&RxData, 0x1000 + 0x80, 4);
        DEBUG_MSG("Running......"LF);
    } while (RxData != 0xA1A2A3A4);
#endif
    
    /* Check the correctness of written dada */
    if (Buffercmp((uint8_t *)&TxData, (uint8_t *)&RxData, 4) == FAILED)
    {
        DEBUG_ERROR("i2c0_passive i2c1_master DLM fail.");
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

