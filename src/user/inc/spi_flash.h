/*******************************************************************************
  * @file    spi_flash.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Flash Application Function. 
 ******************************************************************************/

#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "acu.h"

/* sFlash Define */
#define SPI_FLASH_ID                sFLASH_N25Q128_ID
#define SPI_FLASH_SUBSECTOR_SIZE    0x1000
#define SPI_FLASH_SECTOR_SIZE       0x10000
#define SPI_FLASH_BLOCK_SIZE        0x10000
#define SPI_FLASH_CHIP_SIZE         0x1000000

/***************************sflash 分区*******************************
*        ALL:    0x000000 - 0xFFFFFF   16384k = 16M                  *
*        ------------------------------------------                  *
*        BOOT:   0x000000 - 0x00EFFF      60k                        *
*        REG:    0x00F000 - 0x00FFFF       4k                        *
*        APP:    0x010000 - 0x03FFFF     256k                        *
*        USER:   0x040000 - 0xFFFFFF   16064k                        *
*********************************************************************/
#define ACU_BOOT_ADDR               (0x000000)                      
#define ACU_BOOT_SIZE               (0x00F000)    /* 60k */
#define ACU_REG_ADDR                (ACU_BOOT_ADDR + ACU_BOOT_SIZE)
#define ACU_REG_SIZE                (0x001000)    /* 4k */
#define ACU_APP_ADDR                (ACU_REG_ADDR + ACU_REG_SIZE)
#define ACU_APP_SIZE                (0x040000)    /* 256k */
#define ACU_USER_ADDR               (ACU_APP_ADDR + ACU_APP_SIZE)
#define ACU_USER_SIZE               (0xFB0000)    /* 16064k */

/* SPI Flash test */
#define TEST_FLASH_WRITE_ADDR       0x4000
#define TEST_FLASH_READ_ADDR        TEST_FLASH_WRITE_ADDR
#define TEST_FLASH_SECTOR_ERASE     TEST_FLASH_WRITE_ADDR

uint32_t sFlash_ReadAPPFlag(void);
uint32_t sFlash_ReadAPPSize(void);
BoolStatus sFlash_CopyBinToIRAM(void);
void sFlash_FunctionTest(void);

#endif
