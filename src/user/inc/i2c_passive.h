/*******************************************************************************
  * @file    i2c_passive.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    07-Augest-2018
  * @brief   ACU I2C Passive Application Function. 
 ******************************************************************************/

#ifndef __I2C_PASSIVE_H
#define __I2C_PASSIVE_H

#include "acu.h"

#define I2C_MASTER          I2C1
#define PASSIVE_PAGE_SIZE   0x400

/** @defgroup I2C_passive */
typedef enum cmd {
    PASSIVE_WRITE_DATA_CMD = 0x0,
    PASSIVE_READ_DATA_CMD,
    PASSIVE_WRITE_REG_CMD,
    PASSIVE_READ_REG_CMD,
    PASSIVE_WRITE_BURST_DATA_CMD,
    PASSIVE_READ_BURST_DATA_CMD
} PassiveCmd;

void I2C_PassiveWriteWord(uint8_t *Data, uint32_t AcuAddr, PassiveCmd Command);
void I2C_PassiveReadWord(uint8_t *Data, uint32_t AcuAddr, PassiveCmd Command);
void I2C_PassiveWritePage(uint8_t *Data, uint32_t AcuAddr, uint16_t Size);
void I2C_PassiveReadPage(uint8_t *Data, uint32_t AcuAddr, uint16_t Size);
void I2C_PassiveAlignedWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size);
void I2C_PassiveAlignedReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t Size);
void I2C_PassiveWriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size);
void I2C_PassiveReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t Size);

#endif

