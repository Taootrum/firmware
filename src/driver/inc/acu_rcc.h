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
    uint32_t SYSCLK_Frequency;  /*!< returns system clock frequency 1600M */
    uint32_t FCLK_Frequency;    /*!< returns Fabric clock frequency expressed in Hz */
    uint32_t IPCLK_Frequency;   /*!< returns IP_CORE clock frequency expressed in Hz */
    uint32_t DDRCLK_Frequency;  /*!< returns DDR clock frequency expressed in Hz */
} RCC_ClocksTypeDef;

/* chip reset system manage*/
#define SYS_RESET_CNT       ((uint32_t)0x00000040)
#define SYS_RESET_HIGH      ((uint32_t)0x00000001)
#define SYS_RESET_LOW       ((uint32_t)0x00000000)

#define DRAM_READ_SEL0      ((uint32_t)0x00000000)
#define DRAM_READ_SEL1      ((uint32_t)0x00000001)
#define DRAM_READ_SEL2      ((uint32_t)0x00000002)
#define DRAM_READ_SEL3      ((uint32_t)0x00000003)
#define DRAM_READ_SEL4      ((uint32_t)0x00000004)
#define DRAM_READ_SEL5      ((uint32_t)0x00000005)
#define DRAM_READ_SEL6      ((uint32_t)0x00000006)
#define DRAM_READ_SEL7      ((uint32_t)0x00000007)
#define IS_DRAM_READ_SEL(select) (((select) == DRAM_READ_SEL0) || ((select) == DRAM_READ_SEL1) ||\
                                   ((select) == DRAM_READ_SEL2) || ((select) == DRAM_READ_SEL3) ||\
                                   ((select) == DRAM_READ_SEL4) || ((select) == DRAM_READ_SEL5) ||\
                                   ((select) == DRAM_READ_SEL6) || ((select) == DRAM_READ_SEL7))

#define DRAM_WRITE_SEL_MIX  ((uint32_t)0x00000001)
#define DRAM_WRITE_SEL_MAX  ((uint32_t)0x000000FF)
#define IS_DRAM_WRITE_SEL(select) (((select) >= DRAM_WRITE_SEL_MIX) || ((select) <= DRAM_WRITE_SEL_MAX))

/* system clock manage */
#define SYSCLK_SOURCE_APLL  ((uint32_t)0x00000000)
#define SYSCLK_SOURCE_DPLL  ((uint32_t)0x00000001)
#define SYSCLK_SOURCE_OSC   ((uint32_t)0x00000002)
#define IS_RCC_SYSCLK_SOURCE(source) (((source) == SYSCLK_SOURCE_APLL) || \
                                    ((source) == SYSCLK_SOURCE_DPLL) || \
                                    ((source) == SYSCLK_SOURCE_OSC))

#define SYSCLK_DIV_MIX      ((uint32_t)0x00000001)
#define SYSCLK_DIV_MAX      ((uint32_t)0x0000007F)
#define IS_RCC_SYSCLK_DIV(div) (((div) >= SYSCLK_DIV_MIX) || \
                                ((div) <= SYSCLK_DIV_MAX))

#define RCC_SYSCLK_DISEN    ((uint32_t)0x00000001)


/* APB phericial reset&clock manage*/
#define RCC_APB_SRESET      ((uint32_t)0x00000001)
#define RCC_APB_CLKEN       ((uint32_t)0x00000001)
#define RCC_APB_IOISOEN     ((uint32_t)0x00000001)
#define RCC_APB_CLKGEN      ((uint32_t)0x00000080)

/* AXI phericial reset&clock manage*/
#define RCC_AXI_SRESET      ((uint32_t)0x00000001)
#define RCC_AXI_CLKEN       ((uint32_t)0x00000001)
#define RCC_AXI_MPDEN       ((uint32_t)0x00000001)
#define RCC_AXI_SCREN       ((uint32_t)0x00000080)

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

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_RCC_H */

