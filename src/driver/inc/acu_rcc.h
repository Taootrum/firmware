/*******************************************************************************
  * @file    acu_rcc.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   ACU Clock&Reset Module Function. 
 ******************************************************************************/

#ifndef __ACU_RCC_H
#define __ACU_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "acu.h"

typedef struct
{
    uint32_t APLL_Frequency;    /*!< returns system clock frequency 1600M */
    uint32_t DPLL_Frequency;    /*!< returns system clock frequency 1600M */
    uint32_t FCLK_Frequency;    /*!< returns Fabric clock frequency expressed in Hz */
    uint32_t IPCLK_Frequency;   /*!< returns IP_CORE clock frequency expressed in Hz */
    uint32_t DDRCLK_Frequency;  /*!< returns DDR clock frequency expressed in Hz */
} RCC_ClocksTypeDef;

/**@brief  PLL Init structure definition */
typedef struct
{
    /* PLL_CLK = ((24.0/Divr) * divf) / divq */
    uint32_t PLLInputClock;     /*!< input clock */
    uint32_t PLLOutputClock;    /*!< output clock */
    uint32_t Divr;              /*!< divr */
    uint32_t Divf;              /*!< divf */
    uint32_t Divq;              /*!< divq */
} PLL_InitTypeDef;

typedef enum {UnLock = 0, Lock = 1} LockStatus;

/* 24M / (PLL_DIVR + 1) = 24M | 24M / (DPLL_DIVR + 1) = 12M */ 
#define PLL_DIVR                    0x0   
#define DPLL_DIVR                   0x1   
#define IS_PLL_DIVR(DIVR)           ((DIVR) < 3)

/* 24M * (PLL_DIVF + 1) * 2 = 3600M | 12M * (DPLL_DIVF + 1) * 2 = 4248M */ 
#define PLL_DIVF                    0x4A
#define DPLL_DIVF                   0xB0
#define IS_PLL_DIVF(DIVF)           ((DIVF) <= 0x1FF)

/* 3600M / (2 ^ PLL_DIVQ_2) = 1800M | 4248M / (2 ^ PLL_DIVQ_2) = 2124M */ 
#define PLL_DIVQ_2                  0x01
#define PLL_DIVQ_4                  0x02
#define PLL_DIVQ_8                  0x03
#define PLL_DIVQ_16                 0x04
#define PLL_DIVQ_32                 0x05
#define PLL_DIVQ_64                 0x06
#define IS_PLL_DIVQ(DIVQ)           ((DIVQ) && ((DIVQ) <= PLL_DIVQ_64))

#define PLL_ENABLE                  0x02

/* Global reset flag */
#define SOFT_RESET_FLAG             ((uint32_t)0x00000004)
#define WDT_RESET_FLAG              ((uint32_t)0x00000002)
#define PU_RESET_FLAG               ((uint32_t)0x00000001)

/* chip reset system manage*/
#define SYS_RESET_CNT               ((uint32_t)0x00000040)
#define SYS_RESET_HIGH              ((uint32_t)0x00000001)
#define SYS_RESET_LOW               ((uint32_t)0x00000000)

#define DRAM_READ_SEL0              ((uint32_t)0x00000000)
#define DRAM_READ_SEL1              ((uint32_t)0x00000001)
#define DRAM_READ_SEL2              ((uint32_t)0x00000002)
#define DRAM_READ_SEL3              ((uint32_t)0x00000003)
#define DRAM_READ_SEL4              ((uint32_t)0x00000004)
#define DRAM_READ_SEL5              ((uint32_t)0x00000005)
#define DRAM_READ_SEL6              ((uint32_t)0x00000006)
#define DRAM_READ_SEL7              ((uint32_t)0x00000007)
#define IS_DRAM_READ_SEL(select)    ((select) <= DRAM_READ_SEL7)

#define DRAM_WRITE_SEL_MAX          ((uint32_t)0x000000FF)
#define IS_DRAM_WRITE_SEL(select)   ((select) <= DRAM_WRITE_SEL_MAX)

/* system clock manage */
#define SYSCLK_SOURCE_APLL          ((uint32_t)0x00000000)
#define SYSCLK_SOURCE_DPLL          ((uint32_t)0x00000001)
#define SYSCLK_SOURCE_OSC           ((uint32_t)0x00000002)
#define IS_RCC_SYSCLK_SOURCE(source)    (((source) == SYSCLK_SOURCE_APLL) || \
                                        ((source) == SYSCLK_SOURCE_DPLL) || \
                                        ((source) == SYSCLK_SOURCE_OSC))

#define SYSCLK_DIV_MAX              ((uint32_t)0x0000007F)
#define IS_RCC_SYSCLK_DIV(div)      ((div) <= SYSCLK_DIV_MAX)

#define RCC_SYSCLK_DISEN            ((uint32_t)0x00000001)

/* APB phericial reset&clock manage*/
#define RCC_APB_SRESET              ((uint32_t)0x00000001)
#define RCC_APB_CLKEN               ((uint32_t)0x00000001)
#define RCC_APB_IOISOEN             ((uint32_t)0x00000001)
#define RCC_APB_CLKGEN              ((uint32_t)0x00000080)

/* AXI phericial reset&clock manage*/
#define RCC_AXI_SRESET              ((uint32_t)0x00000001)
#define RCC_AXI_CLKEN               ((uint32_t)0x00000001)
#define RCC_AXI_MPDEN               ((uint32_t)0x00000001)
#define RCC_AXI_SCREN               ((uint32_t)0x00000080)

void RCC_SoftReset(void);
void RCC_PCIEReset(void);
void RCC_IPCoreReset(void);
void RCC_ClkManageReset(void);
void RCC_FabricBusReset(void);
void RCC_DDRReset(void);
void RCC_IOPADReset(void);
uint32_t RCC_GetGlobalResetFlag(void);
void RCC_DDRReadSelectCmd(uint32_t DDR_Channels);
void RCC_DDRWriteSelectCmd(uint32_t DDR_Channels);
void RCC_PLLConfig(PLLCLK_TypeDef *RCC_PLLSource, PLL_InitTypeDef *PLL_Init);
void PLL_StructInit(PLL_InitTypeDef *PLL_Init);
LockStatus RCC_PLLGetLockStatus(PLLCLK_TypeDef *RCC_PLLSource);
void RCC_PLLCmd(PLLCLK_TypeDef *RCC_PLLSource, FunctionalState NewState);
void RCC_SYSCLKSetSource(CLK_TypeDef *RCC_SYSCLK, uint32_t RCC_SYSCLKSource);
uint32_t RCC_SYSCLKGetSource(CLK_TypeDef *RCC_SYSCLK);
void RCC_SYSCLKSetDiv(CLK_TypeDef *RCC_SYSCLK, uint32_t RCC_SYSCLKDIV);
uint32_t RCC_SYSCLKGetDiv(CLK_TypeDef *RCC_SYSCLK);
void RCC_SYSCLKGetFreq(RCC_ClocksTypeDef *RCC_Clocks);
void RCC_SYSCLKCmd(CLK_TypeDef *RCC_SYSCLK, FunctionalState NewState);
void RCC_APBPeriphResetCmd(APBSYS_TypeDef *RCC_APBPeriph, uint8_t ModuleNum, ResetStatus NewState);
void RCC_APBPeriphClockCmd(APBSYS_TypeDef *RCC_APBPeriph, uint8_t ModuleNum, FunctionalState NewState);
void RCC_APBPeriphIsoEnCmd(APBSYS_TypeDef *RCC_APBPeriph, FunctionalState NewState);

/* Debug print */
void RCC_SYSCLKPrintReg(CLK_TypeDef* RCC_SYSCLK);
void RCC_APBSYSPrintReg(APBSYS_TypeDef* RCC_APBPeriph);
void RCC_AXISYSPrintReg(IMEMC_TypeDef* RCC_IMEM);
void RCC_PLLPrintReg(PLLCLK_TypeDef *RCC_PLLSource);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_RCC_H */

