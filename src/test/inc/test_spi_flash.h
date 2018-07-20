/*******************************************************************************
  * @file    test.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Boot From Mode Function. 
 ******************************************************************************/
#ifndef __TEST_SPI_FLASH_H
#define __TEST_SPI_FLASH_H

#include "acu.h"

/* SPI Flash test */
#define TEST_FLASH_SECTOR_ADDR      0x4000
#define TEST_FLASH_BLOCK_ADDR       0x10000
#define TEST_BUF_LEN                SPI_FLASH_SUBSECTOR_SIZE

TestStatus FLASH_InterfaceTest1(void);
TestStatus FLASH_InterfaceTest2(void);
TestStatus FLASH_InterfaceTest3(void);
TestStatus FLASH_InterfaceTest4(void);
TestStatus FLASH_InterfaceTest5(void);
TestStatus FLASH_InterfaceTest6(void);
TestStatus FLASH_InterfaceTest7(void);
TestStatus FLASH_InterfaceTest8(void);

#endif

