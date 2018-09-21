/*******************************************************************************
  * @file    test_ddr.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    30-Augest-2018
  * @brief   ACU DDR Function. 
 ******************************************************************************/
#include "test_ddr.h"

/****************************************************************
 ***************************************************************/
/* normal 0x00000000 - 0x3FFFFFFF */
TestStatus DDR_FunctionTest1(void)
{
    uint32_t TxBuf[8 * 2] = {0x0000abcd, 0x1111abcd, 0x2222abcd, 0x3333abcd, 0x4444abcd, 0x5555abcd, 0x6666abcd, 0x7777abcd, 
                             0x8888abcd, 0x9999abcd, 0xaaaaabcd, 0xbbbbabcd, 0xccccabcd, 0xddddabcd, 0xeeeeabcd, 0xffffabcd};
    uint32_t RxBuf[8 * 2] = {0};
    uint8_t i = 0;

    /* Write 16 ddrc */
    for (i = 0; i < DDRC_NUMBER * 2; i++)
    {
        DDR_WriteMem((uint8_t *)&TxBuf[i], 0x00000000, sizeof(uint32_t), i);
    }
    
    /* Read 16 ddrc */
    for (i = 0; i < DDRC_NUMBER * 2; i++)
    {
        DDR_ReadMem((uint8_t *)&RxBuf[i], 0x00000000, sizeof(uint32_t), i);
    }
    
    /* Compare 16 ddrc */
    if (Buffercmp((uint8_t *)TxBuf, (uint8_t *)RxBuf, 16 * sizeof(uint32_t)) == FAILED)
    {
        DEBUG_MSG("DDRC3 normal write&read(0x00000000 - 0x3FFFFFFF) fail."LF);
        return FAILED;
    }

    return PASSED;
}

/* normal 0x00000000 - 0xFFFFFFFF */
TestStatus DDR_FunctionTest2(void)
{
    uint32_t TxBuf[64] = {0x0000abcd, 0x0111abcd, 0x0222abcd, 0x0333abcd, 0x0444abcd, 0x0555abcd, 0x0666abcd, 0x0777abcd, 
                          0x0888abcd, 0x0999abcd, 0x0aaaabcd, 0x0bbbabcd, 0x0cccabcd, 0x0dddabcd, 0x0eeeabcd, 0x0fffabcd,
                          0x4000abcd, 0x4111abcd, 0x4222abcd, 0x4333abcd, 0x4444abcd, 0x4555abcd, 0x4666abcd, 0x4777abcd, 
                          0x4888abcd, 0x4999abcd, 0x4aaaabcd, 0x4bbbabcd, 0x4cccabcd, 0x4dddabcd, 0x4eeeabcd, 0x4fffabcd,
                          0x8000abcd, 0x8111abcd, 0x8222abcd, 0x8333abcd, 0x8444abcd, 0x8555abcd, 0x8666abcd, 0x8777abcd, 
                          0x8888abcd, 0x8999abcd, 0x8aaaabcd, 0x8bbbabcd, 0x8cccabcd, 0x8dddabcd, 0x8eeeabcd, 0x8fffabcd,
                          0xc000abcd, 0xc111abcd, 0xc222abcd, 0xc333abcd, 0xc444abcd, 0xc555abcd, 0xc666abcd, 0xc777abcd, 
                          0xc888abcd, 0xc999abcd, 0xcaaaabcd, 0xcbbbabcd, 0xccccabcd, 0xcdddabcd, 0xceeeabcd, 0xcfffabcd};
    uint32_t RxBuf[64] = {0};
    uint8_t i = 0, j = 0;

    /* Write 16 ddrc 0x00000000/0x40000000/0x80000000/0xC0000000*/
    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < DDRC_NUMBER * 2; i++)
        {
            DDR_WriteMem((uint8_t *)&TxBuf[j * 16 + i], j * 0x40000000, sizeof(uint32_t), i);
        }
    }
    
    /* Read 16 ddrc 0x00000000/0x40000000/0x80000000/0xC0000000*/
    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < DDRC_NUMBER * 2; i++)
        {
            DDR_ReadMem((uint8_t *)&RxBuf[j * 16 + i], j * 0x40000000, sizeof(uint32_t), i);
        }
    }
    
    /* Compare 16 ddrc 0x00000000/0x40000000/0x80000000/0xC0000000*/
    if (Buffercmp((uint8_t *)TxBuf, (uint8_t *)RxBuf, 64 * sizeof(uint32_t)) == FAILED)
    {
        DEBUG_MSG("DDRC4 normal write&read(0x00000000 - 0xFFFFFFFF) fail."LF);
        return FAILED;
    }

    return PASSED;
}

/* interleave 0x00000000 - 0xFFFFFFFF */
TestStatus DDR_FunctionTest3(void)
{
    uint32_t TxBuf[8 * 2] = {0x0000abcd, 0x1111abcd, 0x2222abcd, 0x3333abcd, 0x4444abcd, 0x5555abcd, 0x6666abcd, 0x7777abcd, 
                             0x8888abcd, 0x9999abcd, 0xaaaaabcd, 0xbbbbabcd, 0xccccabcd, 0xddddabcd, 0xeeeeabcd, 0xffffabcd};
    uint32_t RxBuf[8 * 2] = {0};
    uint8_t i = 0;

#ifdef I2C_PASSIVE_WAY
    I2C_InitTypeDef I2C_InitStructure;

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
#endif

    /* Write 16 ddrc */
    for (i = 0; i < DDRC_NUMBER * 2; i++)
    {
        DDR_InterleaveWriteMem((uint8_t *)&TxBuf[i], 0x0 + i * 0x80, sizeof(uint32_t));
    }

    /* Read 16 ddrc */
    for (i = 0; i < DDRC_NUMBER * 2; i++)
    {
        DDR_InterleaveReadMem((uint8_t *)&RxBuf[i], 0x0 + i * 0x80, sizeof(uint32_t));
    }

    /* Compare 16 ddrc */
    if (Buffercmp((uint8_t *)TxBuf, (uint8_t *)RxBuf, 16 * sizeof(uint32_t)) == FAILED)
    {
        #ifdef ACU_DDR3
        DEBUG_MSG("DDRC3 interleave write&read(0x00000000 - 0xFFFFFFFF) fail."LF);
        #endif
        #ifdef ACU_DDR4
        DEBUG_MSG("DDRC4 interleave write&read(0x00000000 - 0xFFFFFFFF) fail."LF);
        #endif
        return FAILED;
    }

    return PASSED;
}

