/*******************************************************************************
  * @file    acu_iwdg.h
  * @author  DengLin SOC Team
  * @version V3.5.0
  * @date    26-March-2018
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_DDR_INIT_FPGA_H
#define __ACU_DDR_INIT_FPGA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"
#include "acu_ddr_init.h"

void DDRC_FPGA_INIT(int chs);

void uMCTL2_MISC_config(void);
void DRAM_INIT_timing(void);
void DRAM_prototype_timing(void);
void DFI_config( void );
void ADDR_MAP(void);
void Port_config(void);
void DCH1_config(void);
void acu_umctl2_fpga_init(void);
void Load_PE_SDRAM_init(void);
void Load_PE_training(void);
void acu_pub_phy_fpga_init(int DPHY_ADDR_BASE);
void acu_pub_phy_fpga_training(void);

#ifdef __cplusplus
}
#endif

#endif 

