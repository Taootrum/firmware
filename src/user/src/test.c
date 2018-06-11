/*******************************************************************************
  * @file    test.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#include "test.h"

int acu_run = 0;
int acu_assert = 0;
int acu_fail = 0;
int acu_status = 0;
int acu_all_fail = 0;

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void CRU_FunctionTest1(void)
{
    ;
}

static void CRU_FunctionTest2(void)
{
    ;
}

static void CRU_FunctionTest3(void)
{
    ;
}

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void SUITE_CRUTest(void)
{
    ACU_RUN_TEST(CRU_FunctionTest1);
    ACU_RUN_TEST(CRU_FunctionTest2);
    ACU_RUN_TEST(CRU_FunctionTest3);
}

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void SPI_FunctionTest1(void)
{
   ;
}

static void SPI_FunctionTest2(void)
{
   ;
}

static void SPI_FunctionTest3(void)
{
   ;
}

static void SPI_FunctionTest4(void)
{
   ;
}


/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void SUITE_SPITest(void)
{
    ACU_RUN_TEST(SPI_FunctionTest1);
    ACU_RUN_TEST(SPI_FunctionTest2);
    ACU_RUN_TEST(SPI_FunctionTest3);
    ACU_RUN_TEST(SPI_FunctionTest4);
}

/****************************************************************
  * 函数      : GPIO_FunctionTest1()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void GPIO_FunctionTest1(void)
{
   ;
}

static void GPIO_FunctionTest2(void)
{
   ;
}

static void GPIO_FunctionTest3(void)
{
   ;
}

static void GPIO_FunctionTest4(void)
{
   ;
}

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void SUITE_GPIOTest(void)
{
    ACU_RUN_TEST(GPIO_FunctionTest1);
    ACU_RUN_TEST(GPIO_FunctionTest2);
    ACU_RUN_TEST(GPIO_FunctionTest3);
    ACU_RUN_TEST(GPIO_FunctionTest4);
}

/****************************************************************
  * 函数      : UART_FunctionTest1()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void UART_FunctionTest1(void)
{
   ;
}

static void UART_FunctionTest2(void)
{
   ;
}

static void UART_FunctionTest3(void)
{
   ;
}

static void UART_FunctionTest4(void)
{
   ;
}

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void SUITE_UARTTest(void)
{
    ACU_RUN_TEST(UART_FunctionTest1);
    ACU_RUN_TEST(UART_FunctionTest2);
    ACU_RUN_TEST(UART_FunctionTest3);
    ACU_RUN_TEST(UART_FunctionTest4);
}

/****************************************************************
  * 函数      : SFLASH_FunctionTest1()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void SFLASH_FunctionTest1(void)
{
   ;
}

static void SFLASH_FunctionTest2(void)
{
   ;
}

static void SFLASH_FunctionTest3(void)
{
   ;
}

static void SFLASH_FunctionTest4(void)
{
   ;
}

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
static void SUITE_SFLASHTest(void)
{
    ACU_RUN_TEST(SFLASH_FunctionTest1);
    ACU_RUN_TEST(SFLASH_FunctionTest2);
    ACU_RUN_TEST(SFLASH_FunctionTest3);
    ACU_RUN_TEST(SFLASH_FunctionTest4);
}

/****************************************************************
  * 函数      : ACU_BootRomTest()
  * 参数      : None
  * 返回值     : None
  * 描述      : BootRom Test All
 ***************************************************************/
void ACU_FirmWareTest(void)
{
    ACU_RUN_SUITE(SUITE_CRUTest);
    ACU_RUN_SUITE(SUITE_SPITest);
    ACU_RUN_SUITE(SUITE_GPIOTest);
    ACU_RUN_SUITE(SUITE_UARTTest);
    ACU_RUN_SUITE(SUITE_SFLASHTest);
}

