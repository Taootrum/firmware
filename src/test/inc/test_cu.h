/*******************************************************************************
  * @file    test_cu.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    30-Augest-2018
  * @brief   ACU CU Function. 
 ******************************************************************************/
#ifndef __TEST_CU_H
#define __TEST_CU_H

#include "acu.h"

#define DLM_INTERRUPT

#define INSTRUCTION_SIZE    0x70
#define MEM_INIT_SIZE       0x200
#define DMA_CMDBUF_SIZE     0xA8
#define SHD_CMDBUF_SIZE     0x220

TestStatus CU_FunctionTest1(void);
TestStatus CU_FunctionTest2(void);
TestStatus CU_FunctionTest3(void);

#endif
