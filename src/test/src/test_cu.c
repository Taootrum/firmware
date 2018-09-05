/*******************************************************************************
  * @file    test_cu.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    30-Augest-2018
  * @brief   ACU CU Function. 
 ******************************************************************************/
#include "test_cu.h"
#include "i2c_passive.h"

/****************************************************************
  * I2C0 passive
  * I2C1 master
  * DDR
 ***************************************************************/
uint32_t TxData[MEM_INIT_SIZE / 4] = {
    0x8764845f, 0xc35cdea7,0xf5fbcfa9,0x0a39254f,
    0x99bebd01, 0x123f0dcc,0x3822f3e7,0xe4412e7b,
    0x39be8b0d, 0x438c9f70,0x092e4ae5,0x1c870a26,
    0x0f9c95e5, 0x2f13297d,0x6a97644e,0xdaf438af,
    0x136e019e, 0xb61ea567,0xa23143ba,0x11459e20,
    0x2c52466e, 0xa60486c1,0x5c48683b,0x51704169,
    0xff2e3509, 0x554ed0d2,0x832ced75,0x60e55534,
    0xcd76c222, 0xb98e874d,0x7883da5e,0x270692b6,
    
    0x364bbb50, 0x9f933c53,0x8aaea181,0xa1a59ea7,
    0x30f477fb, 0x9f57bdaf,0xc5ba3bbf,0xa6ac939b,
    0x61903750, 0x79cb5a4d,0xd76f4ac2,0x9c655150,
    0xce4eb7ca, 0xa2d2b346,0xdb161104,0x4c100400,
    0xe78e9f39, 0x13cb6f42,0x724d69e9,0x8b214c93,
    0x6ea0787e, 0x7c467ece,0x9713a336,0xcbe2e709,
    0xc72915e0, 0xc76c118c,0x3182224e,0x94ab588f,
    0x443b8b0b, 0x286d2ebf,0x1c8849ed,0x4cfe8a9b,
    
    0xf52728ec, 0x8b0fd369,0x90e2d1ac,0x7b957196,
    0xc4381cb6, 0xd7f86145,0xa6eca77a,0x8593578e,
    0xa85f3fff, 0xec0dffec,0x2a0a82f5,0x8aa0c4fe,
    0x39c498fa, 0xf4c69ed9,0x050746dd,0x38cfdf35,
    0xdb012632, 0xe075b269,0xea411409,0x29fa4d20,
    0x31f4aa0c, 0x2c573d6d,0xa85ba8bf,0x1fbe3e8f,
    0x682a4633, 0xa40bd87c,0xa022447f,0x69e76136,
    0x317fadf3, 0x829db4f1,0xcc28ac9b,0x4293ef84,
    
    0xf6348bb4, 0x0e73b904,0xdeac075e,0x1b09b37b,
    0x26ab34d8, 0x35ae2a8a,0xa9a6cfc6,0x40fbe1cc,
    0x5acb90c6, 0x0f39b210,0x8d5884af,0xbfa93ebb,
    0xec8d67ff, 0xc9f3e5db,0x24e8ea5c,0x9f4ef5fc,
    0x8561fb0e, 0x6fa9c314,0xa50a1c77,0x38cd12bf,
    0x38e6b92e, 0x27d0d92c,0x449bdcea,0x2443b2d8,
    0xbc54bad0, 0x4202b185,0x0b921e3b,0xdeea4bfd,
    0x2ba9c5d9, 0xdc0ca2a2,0x3fde9118,0x9ab406e4
};
uint32_t RxData[MEM_INIT_SIZE / 4] = {0};

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

uint32_t DMA_CmdBuf[DMA_CMDBUF_SIZE / 4] = {
    0x00010001, 0x00040080, 0x00000000, 0x00000000, 
    0x00010001, 0x00040000, 0xdeadbeef, 0x00000000, 
    0x00010001, 0x00040088, 0x10000000, 0x00000000, //(src addr lo)
    0x00010001, 0x0004008c, 0x00000000, 0x00000000, //(src addr hi)
    0x00010001, 0x00040090, 0x20000000, 0x00000000, //(dst addr lo)
    0x00010001, 0x00040094, 0x00000000, 0x00000000, //(dst addr hi)
    0x00010001, 0x000400a8, 0x00000200, 0x00000000, //(copy size)
    0x00010001, 0x00040098, 0x00000000, 0x00000000, //(src offset x)
    0x00010003, 0xffffffff, 0xee00a171, 0xd69f08b5, 
    0x00010006, 0x0000000f, 0xffffff00, 0x00000000, 
    0x00000009, 0x00000000
};

/* FE DMA */
TestStatus CU_FunctionTest1(void)
{
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
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = I2C_FIFO_TX_LEVEL - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = I2C_FIFO_RX_LEVEL - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
#endif

    /* Enable Interrupt */
    WRITE_REG(CU_SC->DLM_INTSEL, 0x1);
    NVIC_EnableIRQ(CU_IRQn);
    
    /* write mem_init data */
    DDR_InterleaveWriteMem((uint8_t *)TxData, 0x10000000, MEM_INIT_SIZE);
    /* Init command buffer */
    DDR_InterleaveWriteMem((uint8_t *)DMA_CmdBuf, 0x0, DMA_CMDBUF_SIZE);
    /* Enable FE kickoff */
    CU_RegInit(0x0, DMA_CMDBUF_SIZE / 8);
    
    /* read system data */
    while (RxData[0] != 0x8764845f);
    
    /* Check the correctness of written data */
    if (Buffercmp((uint8_t *)TxData, (uint8_t *)RxData, MEM_INIT_SIZE) == FAILED)
    {
        DEBUG_ERROR("DLM FE DMA fail.");
        return FAILED;
    }
    
    return PASSED;
}

uint32_t Instruction[INSTRUCTION_SIZE / 4] = {
    0x00000714, 0x02000015, 0x00000314, 0x02000014,
    0x00000414, 0x0200000c, 0x00000114, 0x02000000,
    0x00030214, 0x00000000, 0x02220224, 0x00000001,
    0x02000524, 0x00000000, 0x00600610, 0x00000000,
    0x06250624, 0x00000504, 0x06090610, 0x00000200,
    0x06000824, 0x00000003, 0x08040800, 0x00000000,
    0x06000924, 0x00000007, 0x09040008, 0x00000008
};

uint32_t SHD_CmdBuf[SHD_CMDBUF_SIZE / 4] = {
    0x00010001,0x0004017c,0x04000000,0x00000000,
    0x00010001,0x00040180,0x00000000,0x00000000,
    0x00010001,0x0004018c,0x0000040e,0x00000000,
    0x00010001,0x00040184,0x00000000,0x00000000,
    0x00010001,0x00040188,0x0000000e,0x00000000,
    0x00010001,0x00040194,0x000001fd,0x00000000,
    0x00010001,0x000406f8,0x00000080,0x00000000,
    0x00010001,0x000406fc,0x00000000,0x00000000,
    
    0x00010001,0x00040700,0x00000000,0x00000000,
    0x00010001,0x00040704,0x00000000,0x00000000,
    0x00010001,0x00040708,0x00000000,0x00000000,
    0x00010001,0x0004070c,0x00000000,0x00000000,
    0x00010001,0x00040710,0x00000000,0x00000000,
    0x00010001,0x00040714,0x00000000,0x00000000,
    0x00010001,0x00040718,0x00000000,0x00000000,
    0x00010001,0x0004071c,0x00000000,0x00000000,
    
    0x00010001,0x00040720,0x00000000,0x00000000,
    0x00010001,0x00040724,0x00000000,0x00000000,
    0x00010001,0x00040728,0x00000080,0x00000000,
    0x00010001,0x0004072c,0x00000000,0x00000000,
    0x00010001,0x00040730,0x00000000,0x00000000,
    0x00010001,0x00040734,0x00000000,0x00000000,
    0x00010001,0x00040738,0x00000000,0x00000000,
    0x00010001,0x0004073c,0x00000000,0x00000000,
    
    0x00010001,0x00040740,0x00000000,0x00000000,
    0x00010001,0x00040744,0x00000000,0x00000000,
    0x00010001,0x00040748,0x10000000,0x00000000,
    0x00010001,0x0004074c,0x20000000,0x00000000,
    0x00010001,0x00040750,0x00000000,0x00000000,
    0x00010001,0x00040754,0x00000000,0x00000000,
    0x00020002,0x777d2fb7,0x00000001,0x00010001,
    0x00000023,0x00000000,0x00010006,0x0000000f,
    
    0xffffff00,0x00000000,0x00000008,0x007f0003,
    0x00000000,0x00000000,0x00000009,0x00000000
};

/* ONE CU DMA */
TestStatus CU_FunctionTest2(void)
{
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
    I2C_InitStructure.I2C_AckAddress = 0x50;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_ENABLE;
    I2C_InitStructure.I2C_TxFIFOLevel = I2C_FIFO_TX_LEVEL - 1;
    I2C_InitStructure.I2C_RxFIFOLevel = I2C_FIFO_RX_LEVEL - 1;
    I2C_Cmd(I2C1, DISABLE);
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
#endif

    /* Enable Interrupt */
    WRITE_REG(CU_SC->DLM_INTSEL, 0x1);
    NVIC_EnableIRQ(CU_IRQn);

    /* write instruction data */
    DDR_InterleaveWriteMem((uint8_t *)Instruction, 0x4000000, INSTRUCTION_SIZE);
    /* write mem_init data */
    DDR_InterleaveWriteMem((uint8_t *)TxData, 0x10000000, MEM_INIT_SIZE);
    /* Init command buffer */
    DDR_InterleaveWriteMem((uint8_t *)SHD_CmdBuf, 0x0, SHD_CMDBUF_SIZE);
    /* Enable FE kickoff */
    CU_RegInit(0x0, SHD_CMDBUF_SIZE / 8);
    
    /* read system data */
    while (RxData[0] != 0x8764845f);
    
    /* Check the correctness of written data */
    if (Buffercmp((uint8_t *)TxData, (uint8_t *)RxData, MEM_INIT_SIZE) == FAILED)
    {
        DEBUG_ERROR("DLM ONE CU DMA fail.");
        return FAILED;
    }
    
    return PASSED;
}

/* Do Ethernet test */
TestStatus CU_FunctionTest3(void)
{    
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
#endif

    /* write instruction data */
    DDR_InterleaveWriteMem((uint8_t *)Instruction, 0x4000000, INSTRUCTION_SIZE);
    /* write mem_init data */
    DDR_InterleaveWriteMem((uint8_t *)TxData, 0x10000000, MEM_INIT_SIZE);
    /* Init command buffer */
    DDR_InterleaveWriteMem((uint8_t *)SHD_CmdBuf, 0x0, SHD_CMDBUF_SIZE);
    /* Enable FE kickoff */
    CU_RegInit(0x0, SHD_CMDBUF_SIZE / 8);
    
    /* read system data */
#ifdef DLM_INTERRUPT
    while (RxData[0] != 0x8764845f);
#else
    do
    {
        DDR_ReadMem((uint8_t *)RxData, 0x20000000, MEM_INIT_SIZE);
        DEBUG_MSG("Running......"LF);
    } while (RxData[0] != 0x8764845f);
#endif
    
    /* Check the correctness of written data */
    if (Buffercmp((uint8_t *)TxData, (uint8_t *)RxData, MEM_INIT_SIZE) == FAILED)
    {
        DEBUG_ERROR("DLM ONE CU DMA fail.");
        return FAILED;
    }
    
    return PASSED;
}

