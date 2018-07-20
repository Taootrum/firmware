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
#ifdef SIM_ENV
#define SPI_FLASH_ID                sFLASH_N25Q128_ID
#else
#define SPI_FLASH_ID                sFLASH_W25Q128FV_ID
#endif
#define SPI_FLASH_SUBSECTOR_SIZE    0x1000
#define SPI_FLASH_BLOCK_SIZE        0x10000
#define SPI_FLASH_CHIP_SIZE         0x1000000

/***************************sflash 分区*******************************
*        ALL:    0x000000 - 0xFFFFFF   16384k = 16M                  *
*        ------------------------------------------                  *
*        BOOT:   0x000000 - 0x01FFFF     128k                        *
*        APP:    0x020000 - 0x05FFFF     256k                        *
*        USER:   0x060000 - 0xFFFFFF   16000k                        *
*********************************************************************/
#define ACU_BOOT_ADDR               (0x000000)                      
#define ACU_BOOT_SIZE               (0x020000)    /* 128k */
#define ACU_APP_ADDR                (ACU_BOOT_ADDR + ACU_BOOT_SIZE)
#define ACU_APP_SIZE                (0x040000)    /* 256k */
#define ACU_USER_ADDR               (ACU_APP_ADDR + ACU_APP_SIZE)
#define ACU_USER_SIZE               (0xFA0000)    /* 16000k */

/* Register Config */
#define ACU_BOOT_HEAD_ADDR          (ACU_BOOT_ADDR)
#define ACU_BOOT_SIZE_ADDR          (ACU_BOOT_ADDR + 0x8)
#define ACU_BOOT_CODE_ADDR          (ACU_BOOT_ADDR + 0xC)
#define ACU_BOOT_HEAD               "ACU_BOOT"
#define ACU_BOOT_HEAD_LEN           8

/* IRAM BOOT */
#define IRAM_BOOT_START_ADDR    	ACU_RAM_BASE
#define IRAM_BOOT_SIZE_MAX      	((uint32_t)0x20000)

typedef enum {
    BOOT_MODE_XMOD00 = 0,   /* Boot From FLASH */
    BOOT_MODE_XMOD01,       /* Boot From UART */
    BOOT_MODE_XMOD10,       /* Boot From PCIE */
    BOOT_MODE_XMOD11        /* Boot From IIC */
} BootMode;
#define IS_ALL_BOOT_MODE(MODE) 		(((MODE) == BOOT_MODE_XMOD00) || ((MODE) == BOOT_MODE_XMOD01) ||\
                               		((MODE) == BOOT_MODE_XMOD10) || ((MODE) == BOOT_MODE_XMOD11))

void Hal_FlashWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumWrite);
void Hal_FlashReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumRead);
void Hal_FlashWriteWord(uint32_t WriteAddr, uint32_t Word);
void Hal_FlashReadWord(uint32_t ReadAddr, uint32_t *Word);
void Hal_FlashWriteByte(uint32_t WriteAddr, uint8_t Byte);
void Hal_FlashReadByte(uint32_t ReadAddr, uint8_t *Byte);
void ACU_FlashUpdate(void);

#endif

