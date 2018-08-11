#include "acu_ddr_init.h"

void ddrc_x8_ddr3_init(int chs)
{
    int i = 0;

    /////////////////////////////////////////////
    // step 1 : Program the DWC_ddr_umctl2 registers 
    WRITE32(              DBG1, 0x00000001); 
    WRITE32(            PWRCTL, 0x00000001); 
    WRITE32(              MSTR, 0x80040601); 
    WRITE32(            PWRCTL, 0x000000a0); 
    WRITE32(            PWRTMG, 0x00030005); 
    WRITE32(           HWLPCTL, 0x0aaf0001); 
    WRITE32(          RFSHCTL0, 0x00a0d040); 
    WRITE32(          RFSHCTL3, 0x00000000); 
    WRITE32(           RFSHTMG, 0x0081008b); 
    WRITE32(             INIT0, 0xc0030003); 
    WRITE32(           DIMMCTL, 0x00000000); 
    WRITE32(          DRAMTMG0, 0x15132412); 
    WRITE32(          DRAMTMG1, 0x000d0a18); 
    WRITE32(          DRAMTMG2, 0x0b0c040b); 
    WRITE32(          DRAMTMG3, 0x00002008); 
    WRITE32(          DRAMTMG4, 0x01020407); 
    WRITE32(          DRAMTMG5, 0x0c0b0403); 
    WRITE32(          DRAMTMG8, 0x06066f06); 
    WRITE32(          DRAMTMG9, 0x40000004); 
    WRITE32(         DRAMTMG10, 0x00060404); 
    WRITE32(         DRAMTMG11, 0x01010006); 
    WRITE32(         DRAMTMG12, 0x00000000); 
    WRITE32(         DRAMTMG15, 0x80000000); 
    WRITE32(            ZQCTL0, 0x10ab002b); 
    WRITE32(            ZQCTL1, 0x00000070); 
    WRITE32(           DFITMG0, 0x04928210); 
    WRITE32(           DFITMG1, 0x00070303); 
    WRITE32(         DFILPCFG0, 0x06002010); 
    WRITE32(         DFILPCFG1, 0x00000070); 
    WRITE32(           DFIUPD0, 0x60400018); 
    WRITE32(           DFIUPD1, 0x007a00aa); 
    WRITE32(           DFIUPD2, 0x80000000); 
    WRITE32(           DFIMISC, 0x00000049); 
    WRITE32(           DFITMG2, 0x00001210); 
    WRITE32(           DFITMG3, 0x00000008); 
    WRITE32(            DBICTL, 0x00000001); 
    WRITE32(        DFIPHYMSTR, 0x00000000); 
    WRITE32(          ADDRMAP1, 0x00021601); 
    WRITE32(          ADDRMAP2, 0x00000400); 
    WRITE32(          ADDRMAP3, 0x03010105); 
    WRITE32(          ADDRMAP4, 0x00001f1f); 
    WRITE32(          ADDRMAP5, 0x09060307); 
    WRITE32(          ADDRMAP6, 0x0f040409); 
    WRITE32(          ADDRMAP7, 0x00000f0f); 
    WRITE32(          ADDRMAP8, 0x00000000); 
    WRITE32(          ADDRMAP9, 0x0a040a04); 
    WRITE32(         ADDRMAP10, 0x09070903); 
    WRITE32(         ADDRMAP11, 0x00000002); 
    WRITE32(            ODTCFG, 0x091c0678); 
    WRITE32(            ODTMAP, 0x00000001); 
    WRITE32(             SCHED, 0x119a1500); 
    WRITE32(            SCHED1, 0x00000015); 
    WRITE32(          PERFHPR1, 0x9c00ee3b); 
    WRITE32(          PERFLPR1, 0xc400f97c); 
    WRITE32(           PERFWR1, 0x7b000077); 
    WRITE32(              DBG0, 0x00000015); 
    WRITE32(              DBG1, 0x00000000); 
    WRITE32(            DBGCMD, 0x00000000); 
    WRITE32(             SWCTL, 0x00000001); 
    WRITE32(         POISONCFG, 0x00010001); 
    WRITE32(             PCCFG, 0x00000101); 
    WRITE32(           PCFGR_0, 0x0000224a); 
    WRITE32(           PCFGW_0, 0x00006040); 
    WRITE32(           PCTRL_0, 0x00000001); 
    WRITE32(        PCFGQOS0_0, 0x00110002); 
    WRITE32(        PCFGQOS1_0, 0x0056000e); 
    WRITE32(       PCFGWQOS0_0, 0x01110302); 
    WRITE32(       PCFGWQOS1_0, 0x06c3073a); 
    WRITE32(           PCFGR_1, 0x000022e0); 
    WRITE32(           PCFGW_1, 0x00003221); 
    WRITE32(           PCTRL_1, 0x00000001); 
    WRITE32(        PCFGQOS0_1, 0x00210007); 
    WRITE32(        PCFGQOS1_1, 0x06a70038); 
    WRITE32(       PCFGWQOS0_1, 0x01000904); 
    WRITE32(       PCFGWQOS1_1, 0x023104c8); 
    WRITE32(           PCFGR_2, 0x0000214a); 
    WRITE32(           PCFGW_2, 0x0000218a); 
    WRITE32(           PCTRL_2, 0x00000001); 
    WRITE32(        PCFGQOS0_2, 0x00100006); 
    WRITE32(        PCFGQOS1_2, 0x04ac0276); 
    WRITE32(       PCFGWQOS0_2, 0x00110201); 
    WRITE32(       PCFGWQOS1_2, 0x020e06a8); 
    WRITE32(              PDCH, 0x00000004); 
    WRITE32(       DCH1_PWRCTL, 0x000000a0); 
    WRITE32(      DCH1_HWLPCTL, 0x0aaf0001); 
    WRITE32(       DCH1_ODTMAP, 0x00000001); 
    WRITE32(         DCH1_DBG1, 0x00000000); 
    WRITE32(       DCH1_DBGCMD, 0x00000000); 
    WRITE32(            PWRCTL, 0x000000a0); 
    WRITE32(       DCH1_PWRCTL, 0x000000a0); 

/////////////////////////////////////////////
//RESET: <aresetn> for Port 2  DEASSERTED
//RESET: <aresetn> for Port 1  DEASSERTED
//RESET: <aresetn> for Port 0  DEASSERTED
//RESET: <core_ddrc_rstn> DEASSERTED
//
//// step 2 : Deassert core_ddrc_rstn (according to reference test case)
    for (i = 0; i < chs; i++) 
    {
        WRITE32 (0x4008c000 + (i * 0x400), 0x00);    // release core/pub apb reset 
    }

    WRITE32 (              DBG1, 0x00000000);
    WRITE32 (            PWRCTL, 0x000000a0);
    WRITE32 (            PWRCTL, 0x000000a0);
    WRITE32 (         DCH1_DBG1, 0x00000000);
    WRITE32 (       DCH1_PWRCTL, 0x000000a0);
    WRITE32 (       DCH1_PWRCTL, 0x000000a0);
    WRITE32 (        DFIPHYMSTR, 0x00000000);
    WRITE32 (             SWCTL, 0x00000000);
    WRITE32 (           DFIMISC, 0x00000048);
    WRITE32 (           DFIMISC, 0x00000048);
    WRITE32 (              DBG1, 0x00000002);
    WRITE32 (         DCH1_DBG1, 0x00000002);


//  step 3   Start PHY initialization by accessing relevant PUB registers 
    //ddr3_init_dmem(PUB_ADDR_BASE);
    //ddr3_init_imem(PUB_ADDR_BASE);

    pub_phy_init_hong_2p50a_1(PUB_ADDR_BASE, chs);

// step 7 : Set DFIMISC.dfi_init_complete_en to 1 
// DWC_ddr_umctl2 waits for phy_dfi_init_complete to be asserted
//
    // dfi_init_start trigger from umctl2 to pub
    WRITE32(           DFIMISC , 0x00000068);    // set dfi_init_start = 1
    //polling dfi_init_complete from pub to umctl2
    // polling bit[0]= 1 (change from 0 to 1)
    for (i = 0; i < chs; i++) 
    {
        WRITE32(0x40080420, i); // dram_sel 
        while((READ32 (DFISTAT) & 0x1) != 0x1) ;
    }
    WRITE32(           DFIMISC , 0x00000048);    // set dfi_init_start = 0 
    WRITE32(           DFIMISC , 0x00000049);    // set dfi_init_complete_en = 1
    WRITE32(            PWRCTL , 0x00000080); 
    WRITE32(       DCH1_PWRCTL , 0x00000080); 

// step 8 : Set SWCTL.sw_done to 1 
    WRITE32(             SWCTL , 0x00000001);    // set sw_done =1
// step 9 : Wait for SWSTAT.sw_done_ack to become 1 
    // wait sw_done_ack = 1
    // polling bit[0]= 1 (change from 0 to 1)
    for (i = 0; i < chs; i++) {
        WRITE32(0x40080420, i); // dram_sel 
        while((READ32(SWSTAT) & 0x1) != 0x1) ;
    }

// step 10 :    Wait for DWC_ddr_umctl2 to move to “normal” operating mode by monitoring STAT.operating_mode signal 
    // wait normal state = 1
    for (i = 0; i < chs; i++) 
    {
        WRITE32(0x40080420,i); // dram_sel 
        while((READ32(STAT) & 0x3) != 0x1) ;
        while((READ32(DCH1_STAT) & 0x3) != 0x1) ;
    }

    WRITE32(        DFIPHYMSTR , 0x00000000);    // set dfi_phymstr_en   = 0
    WRITE32(             SWCTL , 0x00000000);    // set sw_done = 0
    WRITE32(             INIT0 , 0x00030003); 
    WRITE32(             SWCTL , 0x00000001);    // set sw_done = 1
    // wait sw_done_ack = 1
    for (i = 0; i < chs; i++) 
    {
        WRITE32(0x40080420, i); // dram_sel 
        while((READ32(SWSTAT) & 0x1) != 0x1) ;
    }

    WRITE32(              DBG1 , 0x00000000); 
    WRITE32(         DCH1_DBG1 , 0x00000000); 
    WRITE32(            PWRCTL , 0x00000080); 
    WRITE32(       DCH1_PWRCTL , 0x00000080); 
    WRITE32(            PWRCTL , 0x00000080); 
    WRITE32(       DCH1_PWRCTL , 0x00000080); 
    WRITE32(           PCTRL_0 , 0x00000001);    // port enable
    WRITE32(           PCTRL_1 , 0x00000001); 
    WRITE32(           PCTRL_2 , 0x00000001); 
}

