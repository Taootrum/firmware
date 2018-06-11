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

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_ACU_H */

