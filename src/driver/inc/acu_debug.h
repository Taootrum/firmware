/*******************************************************************************
  * @file    acu_debug.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Debug Output For SIM or Uart. 
 ******************************************************************************/

#ifndef __ACU_DEBUG_H__
#define __ACU_DEBUG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"

#define DEBUG_UART UART

/* Acu Simulation */
#if defined(SIM_DEBUG)
typedef struct {
    __O  uint32_t   CR;
} DEBUG_SIM_Type;

#define SIM_DEBUG_REG           ((DEBUG_SIM_Type *)0x20006fb0)
#define SIM_END                 (SIM_DEBUG_REG->CR = 0xFF)
#endif

/* System Debug Msg */
#if defined(SIM_DEBUG) || defined(UART_DEBUG)
#define DEBUG_MSG(fmt,args...)      printf(fmt, ##args)
#if defined(SIM_DEBUG)
#define DEBUG_PRINT_REG(r)          printf("%s = %#x\n", #r, (uint32_t)r)
#define DEBUG_ERROR(fmt,args...)    printf("[%s|%d]ERROR: "fmt"\n", __func__, __LINE__, ##args)
#else
#define DEBUG_PRINT_REG(r)          printf("%s = %#x\r\n", #r, (uint32_t)r)
#define DEBUG_ERROR(fmt,args...)    printf("[%s|%d]ERROR: "fmt"\r\n", __func__, __LINE__, ##args)
#endif
#else
#define DEBUG_MSG(fmt,args...)      ((void)0)
#define DEBUG_ERROR(fmt,args...)    ((void)0)
#define DEBUG_PRINT_REG(r)          ((void)0)
#endif

/* Exported macro */
#ifdef USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif

#define GET_CHAR_TIMEOUT_MSEC   5

void Debug_DeInit(void);
void Debug_Init(void);
void PutChar(uint8_t Putchar);
BoolStatus GetChar(uint8_t *InChar);

void Debug_PrintReg(void);

#ifdef __cplusplus
}
#endif

#endif

