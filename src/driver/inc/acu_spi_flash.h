/*******************************************************************************
  * @file    acu_spi_flash.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU SPI Flash Module Function. 
 ******************************************************************************/

#ifndef __ACU_SPI_FLASH_H
#define __ACU_SPI_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu_spi.h"

/**@brief  M25P FLASH SPI Interface pins */  
#define sFLASH_SPI                SPI0                    
#define sFLASH_CS_GPIO            GPIO_SSP0_CSN        
#define sFLASH_CLK_GPIO           GPIO_SSP0_CLK
#define sFLASH_MOSI_GPIO          GPIO_SSP0_TXD
#define sFLASH_MISO_GPIO          GPIO_SSP0_RXD

/**@brief  M25P SPI Flash supported commands */  
#define sFLASH_CMD_WRITE          0x02  /*!< Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /*!< Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /*!< Write enable instruction */
#define sFLASH_CMD_WRDIS          0x04  /*!< Write disable instruction */
#define sFLASH_CMD_READ           0x03  /*!< Read from Memory instruction */
#define sFLASH_CMD_FREAD          0x0B  /*!< Fast Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /*!< Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /*!< Read identification */
#define sFLASH_CMD_SSE            0x20  /*!< Sector Erase instruction */
#define sFLASH_CMD_SE             0xD8  /*!< Block Erase instruction */
#define sFLASH_CMD_BE             0xC7  /*!< Bulk Erase instruction */

#define sFLASH_WIP_FLAG           0x01  /*!< Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100
#define sFLASH_N25Q128_ID         0x20BA18
#define sFLASH_W25Q128FV_ID       0xEF4018

/**@brief sFLASH: Chip Select pin */
#define sFLASH_CS_LOW()       GPIO_SetOutput(sFLASH_CS_GPIO, GPIO_RESET)
#define sFLASH_CS_HIGH()      GPIO_SetOutput(sFLASH_CS_GPIO, GPIO_SET)  

/**@brief  High layer functions */
void sFLASH_DeInit(void);
void sFLASH_Init(void);
void sFLASH_EraseSector(uint32_t SectorAddr);
void sFLASH_EraseBlock(uint32_t BlockAddr);
void sFLASH_EraseBulk(void);
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t sFLASH_ReadID(void);
void sFLASH_StartReadSequence(uint32_t ReadAddr);

/**@brief  Low layer functions */
uint8_t sFLASH_ReadByte(void);
uint8_t sFLASH_SendByte(uint8_t byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);

void Flash_PrintReg(void);

#ifdef __cplusplus
}
#endif

#endif

