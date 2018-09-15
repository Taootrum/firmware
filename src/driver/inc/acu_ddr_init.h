/*******************************************************************************
  * @file    acu_iwdg.h
  * @author  DengLin SOC Team
  * @version V3.5.0
  * @date    26-March-2018
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
 ******************************************************************************/
#ifndef __ACU_DDR_INIT_H
#define __ACU_DDR_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "acu.h"

#define UMCTL2_ADDR_BASE 0x46000000
#define PUB_ADDR_BASE    0x44000000

/* UMCTL2 REGS registers */
#define               MSTR    (UMCTL2_ADDR_BASE+0X00000000) 
#define               STAT    (UMCTL2_ADDR_BASE+0X00000004) 
#define            MRCTRL0    (UMCTL2_ADDR_BASE+0X00000010) 
#define            MRCTRL1    (UMCTL2_ADDR_BASE+0X00000014) 
#define            MRSTAT     (UMCTL2_ADDR_BASE+0X00000018) 
#define            MRCTRL2    (UMCTL2_ADDR_BASE+0X0000001c) 
#define             PWRCTL    (UMCTL2_ADDR_BASE+0X00000030) 
#define             PWRTMG    (UMCTL2_ADDR_BASE+0X00000034) 
#define            HWLPCTL    (UMCTL2_ADDR_BASE+0X00000038) 
#define           RFSHCTL0    (UMCTL2_ADDR_BASE+0X00000050) 
#define           RFSHCTL3    (UMCTL2_ADDR_BASE+0X00000060) 
#define            RFSHTMG    (UMCTL2_ADDR_BASE+0X00000064) 
#define         CRCPARCTL0    (UMCTL2_ADDR_BASE+0X000000c0) 
#define         CRCPARCTL1    (UMCTL2_ADDR_BASE+0X000000c4) 
#define         CRCPARSTAT    (UMCTL2_ADDR_BASE+0X000000cc) 
#define              INIT0    (UMCTL2_ADDR_BASE+0X000000d0) 
#define              INIT1    (UMCTL2_ADDR_BASE+0X000000d4) 
#define              INIT3    (UMCTL2_ADDR_BASE+0X000000dc) 
#define              INIT4    (UMCTL2_ADDR_BASE+0X000000e0) 
#define              INIT5    (UMCTL2_ADDR_BASE+0X000000e4) 
#define              INIT6    (UMCTL2_ADDR_BASE+0X000000e8) 
#define              INIT7    (UMCTL2_ADDR_BASE+0X000000ec) 
#define            DIMMCTL    (UMCTL2_ADDR_BASE+0X000000f0) 
#define           DRAMTMG0    (UMCTL2_ADDR_BASE+0X00000100) 
#define           DRAMTMG1    (UMCTL2_ADDR_BASE+0X00000104) 
#define           DRAMTMG2    (UMCTL2_ADDR_BASE+0X00000108) 
#define           DRAMTMG3    (UMCTL2_ADDR_BASE+0X0000010c) 
#define           DRAMTMG4    (UMCTL2_ADDR_BASE+0X00000110) 
#define           DRAMTMG5    (UMCTL2_ADDR_BASE+0X00000114) 
#define           DRAMTMG8    (UMCTL2_ADDR_BASE+0X00000120) 
#define           DRAMTMG9    (UMCTL2_ADDR_BASE+0X00000124) 
#define          DRAMTMG10    (UMCTL2_ADDR_BASE+0X00000128) 
#define          DRAMTMG11    (UMCTL2_ADDR_BASE+0X0000012c) 
#define          DRAMTMG12    (UMCTL2_ADDR_BASE+0X00000130) 
#define          DRAMTMG15    (UMCTL2_ADDR_BASE+0X0000013c) 
#define             ZQCTL0    (UMCTL2_ADDR_BASE+0X00000180) 
#define             ZQCTL1    (UMCTL2_ADDR_BASE+0X00000184) 
#define            DFITMG0    (UMCTL2_ADDR_BASE+0X00000190) 
#define            DFITMG1    (UMCTL2_ADDR_BASE+0X00000194) 
#define          DFILPCFG0    (UMCTL2_ADDR_BASE+0X00000198) 
#define          DFILPCFG1    (UMCTL2_ADDR_BASE+0X0000019c) 
#define            DFIUPD0    (UMCTL2_ADDR_BASE+0X000001a0) 
#define            DFIUPD1    (UMCTL2_ADDR_BASE+0X000001a4) 
#define            DFIUPD2    (UMCTL2_ADDR_BASE+0X000001a8) 
#define            DFIMISC    (UMCTL2_ADDR_BASE+0X000001b0) 
#define            DFITMG2    (UMCTL2_ADDR_BASE+0X000001b4) 
#define            DFITMG3    (UMCTL2_ADDR_BASE+0X000001b8) 
#define            DFISTAT    (UMCTL2_ADDR_BASE+0X000001bc) 
#define             DBICTL    (UMCTL2_ADDR_BASE+0X000001c0) 
#define         DFIPHYMSTR    (UMCTL2_ADDR_BASE+0X000001c4) 
#define           ADDRMAP1    (UMCTL2_ADDR_BASE+0X00000204) 
#define           ADDRMAP2    (UMCTL2_ADDR_BASE+0X00000208) 
#define           ADDRMAP3    (UMCTL2_ADDR_BASE+0X0000020c) 
#define           ADDRMAP4    (UMCTL2_ADDR_BASE+0X00000210) 
#define           ADDRMAP5    (UMCTL2_ADDR_BASE+0X00000214) 
#define           ADDRMAP6    (UMCTL2_ADDR_BASE+0X00000218) 
#define           ADDRMAP7    (UMCTL2_ADDR_BASE+0X0000021c) 
#define           ADDRMAP8    (UMCTL2_ADDR_BASE+0X00000220) 
#define           ADDRMAP9    (UMCTL2_ADDR_BASE+0X00000224) 
#define          ADDRMAP10    (UMCTL2_ADDR_BASE+0X00000228) 
#define          ADDRMAP11    (UMCTL2_ADDR_BASE+0X0000022c) 
#define             ODTCFG    (UMCTL2_ADDR_BASE+0X00000240) 
#define             ODTMAP    (UMCTL2_ADDR_BASE+0X00000244) 
#define              SCHED    (UMCTL2_ADDR_BASE+0X00000250) 
#define             SCHED1    (UMCTL2_ADDR_BASE+0X00000254) 
#define           PERFHPR1    (UMCTL2_ADDR_BASE+0X0000025c) 
#define           PERFLPR1    (UMCTL2_ADDR_BASE+0X00000264) 
#define            PERFWR1    (UMCTL2_ADDR_BASE+0X0000026c) 
#define               DBG0    (UMCTL2_ADDR_BASE+0X00000300) 
#define               DBG1    (UMCTL2_ADDR_BASE+0X00000304) 
#define             DBGCAM    (UMCTL2_ADDR_BASE+0X00000308) 
#define             DBGCMD    (UMCTL2_ADDR_BASE+0X0000030c) 
#define              SWCTL    (UMCTL2_ADDR_BASE+0X00000320) 
#define             SWSTAT    (UMCTL2_ADDR_BASE+0X00000324) 
#define          POISONCFG    (UMCTL2_ADDR_BASE+0X0000036c)

/* UMCTL2 MP registers */
#define              PCCFG    (UMCTL2_ADDR_BASE+0X00000400) 
#define            PCFGR_0    (UMCTL2_ADDR_BASE+0X00000404) 
#define            PCFGW_0    (UMCTL2_ADDR_BASE+0X00000408) 
#define            PCTRL_0    (UMCTL2_ADDR_BASE+0X00000490) 
#define         PCFGQOS0_0    (UMCTL2_ADDR_BASE+0X00000494) 
#define         PCFGQOS1_0    (UMCTL2_ADDR_BASE+0X00000498) 
#define        PCFGWQOS0_0    (UMCTL2_ADDR_BASE+0X0000049c) 
#define        PCFGWQOS1_0    (UMCTL2_ADDR_BASE+0X000004a0) 
#define            PCFGR_1    (UMCTL2_ADDR_BASE+0X000004b4) 
#define            PCFGW_1    (UMCTL2_ADDR_BASE+0X000004b8) 
#define            PCTRL_1    (UMCTL2_ADDR_BASE+0X00000540) 
#define         PCFGQOS0_1    (UMCTL2_ADDR_BASE+0X00000544) 
#define         PCFGQOS1_1    (UMCTL2_ADDR_BASE+0X00000548) 
#define        PCFGWQOS0_1    (UMCTL2_ADDR_BASE+0X0000054c) 
#define        PCFGWQOS1_1    (UMCTL2_ADDR_BASE+0X00000550) 
#define            PCFGR_2    (UMCTL2_ADDR_BASE+0X00000564) 
#define            PCFGW_2    (UMCTL2_ADDR_BASE+0X00000568) 
#define            PCTRL_2    (UMCTL2_ADDR_BASE+0X000005f0) 
#define         PCFGQOS0_2    (UMCTL2_ADDR_BASE+0X000005f4) 
#define         PCFGQOS1_2    (UMCTL2_ADDR_BASE+0X000005f8) 
#define        PCFGWQOS0_2    (UMCTL2_ADDR_BASE+0X000005fc) 
#define        PCFGWQOS1_2    (UMCTL2_ADDR_BASE+0X00000600) 
#define               PDCH    (UMCTL2_ADDR_BASE+0X00000f34)
/* UMCTL2 DCH1 registers */
#define          DCH1_STAT    (UMCTL2_ADDR_BASE+0X00001b04) 
#define       DCH1_MRCTRL0    (UMCTL2_ADDR_BASE+0X00001b10)
#define       DCH1_MRCTRL1    (UMCTL2_ADDR_BASE+0X00001b14)
#define       DCH1_MRSTAT     (UMCTL2_ADDR_BASE+0X00001b18) 
#define       DCH1_MRCTRL2    (UMCTL2_ADDR_BASE+0X00001b1c) 
#define        DCH1_PWRCTL    (UMCTL2_ADDR_BASE+0X00001b30) 
#define       DCH1_HWLPCTL    (UMCTL2_ADDR_BASE+0X00001b38) 
#define    DCH1_CRCPARCTL0    (UMCTL2_ADDR_BASE+0X00001bc0) 
#define        DCH1_ODTMAP    (UMCTL2_ADDR_BASE+0X00001d44) 
#define          DCH1_DBG1    (UMCTL2_ADDR_BASE+0X00001e04) 
#define        DCH1_DBGCAM    (UMCTL2_ADDR_BASE+0X00001e08)
#define        DCH1_DBGCMD    (UMCTL2_ADDR_BASE+0X00001e0c) 

/* DDRC NUMBER max = 8 */
#define DDRC_NUMBER     8

void DDRC_Init(void);
void ddrc_x8_ddr3_init(int chs);
void ddrc_x8_ddr4_init(int chs);
int do_ddr_training(int DPHY_ADDR_BASE, int chs);
void dump_stream_msg(int DPHY_ADDR_BASE);
void ddr3_pub_phy_init(int DPHY_ADDR_BASE, int chs);
void ddr4_pub_phy_init(int DPHY_ADDR_BASE, int chs);

#ifdef __cplusplus
}
#endif

#endif 

