/*******************************************************************************
  * @file    acu_debug.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Debug Output For SIM or Uart. 
 ******************************************************************************/
#include "acu_debug.h"

/****************************************************************
  * 函数      : Debug_DeInit()
  * 参数      : None
  * 返回值     : None
  * 描述      : Disable Initializes Debug Uart
 ***************************************************************/
void Debug_DeInit(void)
{
    UART_DeInit(UART_SC);
}

/****************************************************************
  * 函数      : Debug_Init()
  * 参数      : None
  * 返回值     : None
  * 描述      : Initializes Debug Uart
 ***************************************************************/
void Debug_Init(void)
{
    UART_InitTypeDef UART_InitStructure;

    /*!< UART clk enable*/
    RCC_APBPeriphResetCmd(UART_SC, RESET);
    RCC_APBPeriphClockCmd(UART_SC, ENABLE);
    RCC_APBPeriphIsoEnCmd(UART_SC, ENABLE);
        
    /*!< Uart configuration */
    UART_StructInit(&UART_InitStructure);
    UART_Init(DEBUG_UART, &UART_InitStructure);

    /*!< Enable the Uart  */
    UART_Cmd(DEBUG_UART, ENABLE);
}

/****************************************************************
  * 函数      : PutChar()
  * 参数      : Putchar: what char will put
  * 返回值     : None
  * 描述      : Debug Uart put a char
 ***************************************************************/
void PutChar(uint8_t Putchar)
{
    UART_SendData(DEBUG_UART, Putchar);

    while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_TXFE) == RESET)
    {
        ;
    }
}

/****************************************************************
  * 函数      : PutChar()
  * 参数      : *InChar: what char will get
  * 返回值     : None
  * 描述      : Debug Uart get a char
 ***************************************************************/
BoolStatus GetChar(uint8_t *InChar)
{
    if (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_RXFE) == SET)
    {
        return FALSE;
    }

    *InChar = UART_ReceiveData(DEBUG_UART);
    
    return TRUE;
}

/****************************************************************
  * 函数      : fputc()
  * 参数      : ch: ch
              f: 
  * 返回值     : None
  * 描述      : fputc重定向printf
 ***************************************************************/
int fputc(int ch, FILE *f) 
{    
#if defined(SIM_DEBUG)
    SIM_DEBUG_REG->CR =(ch & 0xFF);
#else
    PutChar(ch & 0xFF); 
#endif

    return (ch);
}

#ifdef USE_FULL_ASSERT
/****************************************************************
  * 函数      : assert_failed()
  * 参数      : file: 文件名
              line: 发生行数
  * 返回值     : None
  * 描述      : 报告assert_param参数错误时的文件名和代码行数
 ***************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{ 
    DEBUG_MSG("[%s|%d]:assert_param error!\n", file, line);
    
    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/****************************************************************
  * 函数      : Debug_FunctionTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : UART功能测试 TX->RX
 ***************************************************************/
void Debug_FunctionTest(void)
{
    uint8_t TxCounter = 0, RxCounter = 0;
    uint8_t TxBuf[] = "ACU UART Test: communication with LoopBack.";
    uint8_t RxBuf[COUNT_OF(TxBuf) - 1] = {0};
    uint8_t BufSize = COUNT_OF(TxBuf) - 1;
    volatile TestStatus Status = FAILED;

    DEBUG_MSG("debug uart test LoopBack_Mode start!\n");

    while (TxCounter < BufSize)
    {   
        /* Send one byte from USARTy to USARTz */
        PutChar(TxBuf[TxCounter++]);

        TIMER_ResetSysTick();
        do
        {
            if (GetChar(&RxBuf[RxCounter]))
            {
                break;
            }
        }
        while (TIMER_GetSysTick() < GET_CHAR_TIMEOUT_MSEC);
        RxCounter++;
    } 
    
    /* Check the correctness of written dada */
    Status = Buffercmp(TxBuf, RxBuf, BufSize);
    if (Status == FAILED)
    {
        DEBUG_MSG("debug uart TX->RX fail.\n");
    }
    else 
    {
        DEBUG_MSG("debug uart TX->RX OK.\n");
    }
    
    DEBUG_MSG("debug uart test LoopBack_Mode end!\n");
}

/****************************************************************
  * 函数      : Debug_FunctionTest1()
  * 参数      : None
  * 返回值     : None
  * 描述      : UART功能测试 RX->TX
 ***************************************************************/
void Debug_FunctionTest1(void)
{
    uint8_t TestChar = 0;
    uint32_t Tick = 0, CurTick = 0;

    DEBUG_MSG("debug uart test Normal_Mode start!\n");
    TIMER_ResetSysTick();

    do
    {   
        Tick = TIMER_GetSysTick();
        do
        {
            if (GetChar(&TestChar))
            {
                break;
            }
            CurTick = TIMER_GetSysTick();
        }
        while (CurTick - Tick < GET_CHAR_TIMEOUT_MSEC);

        if (CurTick - Tick < GET_CHAR_TIMEOUT_MSEC)
        {
            PutChar(TestChar);
        }
        else
        {
            DEBUG_MSG("uart GetChar timeout!\n");
        }
    } 
    while (TIMER_GetSysTick() < GET_CHAR_TIMEOUT_MSEC * 1000 * 10); /* 50s */
    DEBUG_MSG("debug uart test Normal_Mode end!\n");
}

/****************************************************************
  * 函数      : Debug_PrintReg()
  * 参数      : None
  * 返回值     : None
  * 描述      : 打印调试串口寄存器配置
 ***************************************************************/
void Debug_PrintReg(void)
{
    /* RCC */
    DEBUG_MSG("UART_SC:\n");
    DEBUG_PRINT_REG(UART_SC);
    RCC_APBSYSPrintReg(UART_SC);
    
    /* UART */
    DEBUG_MSG("UART:\n");
    DEBUG_PRINT_REG(DEBUG_UART);
    UART_PrintReg(DEBUG_UART);
    DEBUG_MSG("\n");
}

