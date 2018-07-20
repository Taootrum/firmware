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
    UART_DeInit(UART);
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

    /*!< UART clk enable & iso disable */
    RCC_APBPeriphResetCmd(UART_SC, 0, RESET);
    RCC_APBPeriphClockCmd(UART_SC, 0, ENABLE);
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
#if defined(SIM_ENV)
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
    DEBUG_MSG("[%s|%d]:assert_param error!"LF, file, line);
    
    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/****************************************************************
  * 函数      : Debug_PrintReg()
  * 参数      : None
  * 返回值     : None
  * 描述      : 打印调试串口寄存器配置
 ***************************************************************/
void Debug_PrintReg(void)
{
    /* RCC */
    DEBUG_MSG("UART_SC:"LF);
    DEBUG_PRINT_REG(UART_SC);
    RCC_APBSYSPrintReg(UART_SC);
    
    /* UART */
    DEBUG_MSG("UART:"LF);
    DEBUG_PRINT_REG(DEBUG_UART);
    UART_PrintReg(DEBUG_UART);
    DEBUG_MSG(LF);
}

