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
#define TEST_FLASH_WRITE_ADDR       0x4000
#define TEST_FLASH_READ_ADDR        TEST_FLASH_WRITE_ADDR
#define TEST_FLASH_SECTOR_ERASE     TEST_FLASH_WRITE_ADDR

TestStatus FLASH_FunctionTest1(void);
TestStatus FLASH_FunctionTest2(void);
TestStatus FLASH_FunctionTest3(void);
TestStatus FLASH_FunctionTest4(void);

#endif

