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
#define SPI_FLASH_ID                sFLASH_W25Q128FV_ID
#define SPI_FLASH_SUBSECTOR_SIZE    0x1000
#define SPI_FLASH_BLOCK_SIZE        0x10000
#define SPI_FLASH_CHIP_SIZE         0x1000000

/***************************sflash 分区*******************************
*        ALL:    0x000000 - 0xFFFFFF   16384k = 16M                  *
*        ------------------------------------------                  *
*        REG:    0x000000 - 0x000FFF       4k                        *
*        BOOT:   0x001000 - 0x00FFFF      60k                        *
*        APP:    0x010000 - 0x03FFFF     256k                        *
*        USER:   0x040000 - 0xFFFFFF   16064k                        *
*********************************************************************/
#define ACU_REG_ADDR                (0x000000)
#define ACU_REG_SIZE                (0x001000)    /* 4k */
#define ACU_BOOT_ADDR               (ACU_REG_ADDR + ACU_REG_SIZE)                      
#define ACU_BOOT_SIZE               (0x00F000)    /* 60k */
#define ACU_APP_ADDR                (ACU_BOOT_ADDR + ACU_BOOT_SIZE)
#define ACU_APP_SIZE                (0x040000)    /* 256k */
#define ACU_USER_ADDR               (ACU_APP_ADDR + ACU_APP_SIZE)
#define ACU_USER_SIZE               (0xFB0000)    /* 16064k */

/* Register Config */
#define ACU_BOOT_FLAG_ADDR          (ACU_REG_ADDR)
#define ACU_BOOT_SIZE_ADDR          (ACU_REG_ADDR + 0x4)
#define ACU_BOOT_CHECKSUM_ADDR      (ACU_REG_ADDR + 0x8)
#define ACU_BOOT_FLAG               0xA5A6A7A8

/* IRAM BOOT */
#define IRAM_BOOT_START_ADDR    ACU_RAM_BASE
#define IRAM_BOOT_SIZE_MAX      ((uint32_t)0x20000)

typedef enum {
    BOOT_MODE_XMOD00 = 0,   /* Boot From PCIE */
    BOOT_MODE_XMOD01,       /* Boot From FLASH */
    BOOT_MODE_XMOD10,       /* Boot From IIC */
    BOOT_MODE_XMOD11        /* Boot From UART */
} BootMode;
#define IS_ALL_BOOT_MODE(MODE) (((MODE) == BOOT_MODE_XMOD00) || ((MODE) == BOOT_MODE_XMOD01) ||\
                               ((MODE) == BOOT_MODE_XMOD10) || ((MODE) == BOOT_MODE_XMOD11))

void Hal_FlashWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumWrite);
void Hal_FlashReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumRead);
void ACU_FlashUpdate(void);

#endif

