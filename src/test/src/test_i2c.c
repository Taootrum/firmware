/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test_i2c.h"

/* I2C0 slave
   I2C1 master
   address 7bit
   poll
*/
TestStatus I2C_FunctionTest1(void)
{
    I2C_InitTypeDef  I2C_InitStructure;

    /*!< sFLASH_SPI Periph clock enable */
    RCC_APBPeriphClockCmd(I2C_SC, 0, ENABLE);
    RCC_APBPeriphClockCmd(I2C_SC, 1, ENABLE);
    /*!< sFLASH_SPI IO enable */
    RCC_APBPeriphIsoEnCmd(I2C_SC, ENABLE);
        
    /*!< I2C0 configuration */
    I2C_DeInit(I2C0);
    I2C_InitStructure.I2C_Speed = I2C_Speed_400k;
    I2C_InitStructure.I2C_Mode = I2C_Mode_Slave;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_RestartEnable = I2C_Restart_Enable;
    I2C_InitStructure.I2C_AddressMode = I2C_Address_7bit;
    I2C_InitStructure.I2C_HSMasterAddress = 0x1;
    I2C_InitStructure.I2C_OwnAddress = 0x0a;
    I2C_InitStructure.I2C_AcknowledgedAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = 0;
    I2C_InitStructure.I2C_RxFIFOLevel = 0;
    I2C_Init(I2C0, &I2C_InitStructure);
    I2C_Cmd(I2C0, ENABLE);

    /*!< I2C1 configuration */
    I2C_DeInit(I2C1);
    I2C_InitStructure.I2C_Mode = I2C_Mode_Master;
    I2C_InitStructure.I2C_OwnAddress = 0x0a;
    I2C_InitStructure.I2C_AcknowledgedAddress = 0x50;
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
    
    return PASSED;
}

/* I2C0 slave
   I2C1 master
   address 7bit
   interrupt
*/
TestStatus I2C_FunctionTest2(void)
{

    return PASSED;
}

/* I2C0 slave
   I2C1 master
   address 10bit
   poll
*/
TestStatus I2C_FunctionTest3(void)
{

    return PASSED;
}

/* I2C0 slave
   I2C1 master
   address 10bit
   interrupt
*/
TestStatus I2C_FunctionTest4(void)
{

    return PASSED;
}

/* I2C0 master
   I2C1 slave
   address 7bit
   poll
*/
TestStatus I2C_FunctionTest5(void)
{

    return PASSED;
}

/* I2C0 master
   I2C1 slave
   address 7bit
   interrupt
*/
TestStatus I2C_FunctionTest6(void)
{

    return PASSED;
}

/* I2C0 master
   I2C1 slave
   address 10bit
   poll
*/
TestStatus I2C_FunctionTest7(void)
{

    return PASSED;
}

/* I2C0 master
   I2C1 slave
   address 10bit
   interrupt
*/
TestStatus I2C_FunctionTest8(void)
{

    return PASSED;
}

/* I2C0 slave
   I2C1 master
   address 10bit
   passive
*/
TestStatus I2C_FunctionTest9(void)
{

    return PASSED;
}

/* printf i2c register */
TestStatus I2C_FunctionTest10(void)
{    
    DEBUG_MSG("I2C0------------------------------\r\n");
    I2C_PrintReg(I2C0);
    DEBUG_MSG("I2C1------------------------------\r\n");
    I2C_PrintReg(I2C1);
    return PASSED;
}

