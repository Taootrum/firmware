/*******************************************************************************
  * @file    system_acu.h
  * @author  DengLin SOC Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Header File.
  ******************************************************************************/

#ifndef __SYSTEM_ACU_H
#define __SYSTEM_ACU_H

#ifdef __cplusplus
 extern "C" {
#endif 

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL                (24000000UL)      /* Oscillator frequency */
#ifdef SIM_ENV
#define APLL_CLK_FREQ       (1800 * 1000000UL)
#define DPLL_CLK_FREQ       (1800 * 1000000UL)
#define SYSTEM_CLK_FREQ     (100 * 1000000UL)
#define IPCORE_CLK_FREQ     (100 * 1000000UL)
#define DDR_CLK_FREQ        (1066 * 1000000UL)
#else
#define APLL_CLK_FREQ       (24 * 1000000UL)
#define DPLL_CLK_FREQ       (24 * 1000000UL)
#define SYSTEM_CLK_FREQ     (12 * 1000000UL)
#define IPCORE_CLK_FREQ     (12 * 1000000UL)
#define DDR_CLK_FREQ        (12 * 1000000UL)
#endif
#define PLL_LOCK_TIMEOUT    ((uint32_t)0x10000)

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_ACU_H */

