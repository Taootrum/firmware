#include "acu_ddr_init.h"

static void soc_addrmap (int ddr_type, int cs_size);

void ddrc_x8_ddr3_init(int chs)
{
    uint8_t i = 0;

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
    WRITE32(              PDCH, 0x00000002); 
    WRITE32(       DCH1_PWRCTL, 0x000000a0); 
    WRITE32(      DCH1_HWLPCTL, 0x0aaf0001); 
    WRITE32(       DCH1_ODTMAP, 0x00000001); 
    WRITE32(         DCH1_DBG1, 0x00000000); 
    WRITE32(       DCH1_DBGCMD, 0x00000000); 
    WRITE32(            PWRCTL, 0x000000a0); 
    WRITE32(       DCH1_PWRCTL, 0x000000a0); 

    soc_addrmap (0, 0);       // address remapping, ddr3 & 1GB

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
    #if 0
    ddr3_init_dmem(PUB_ADDR_BASE);
    ddr3_init_imem(PUB_ADDR_BASE);
    #endif
    
    ddr3_pub_phy_init(PUB_ADDR_BASE, chs);

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

#if 0
    WRITE32(0xa0000000, 0x12345678);
    WRITE32(0xa0000004, 0x9abcdef0);
    WRITE32(0xa0000008, 0x55555555); 
    WRITE32(0xa000000c, 0xaaaaaaaa);
    WRITE32(0xa0000010, 0x55555555); 
    WRITE32(0xa0000014, 0xaaaaaaaa); 
    WRITE32(0xa0000018, 0x11223344);
    WRITE32(0xa000001c, 0x55667788);
    WRITE32(0xa0000020, 0x99aabbcc); 
    WRITE32(0xa0000024, 0xddeeff00);

    WRITE32(0xa0001000, 0x11223344); 
    WRITE32(0xa0001004, 0x55667788); 
    WRITE32(0xa0001008, 0x99aabbcc);
    WRITE32(0xa000100c, 0xddeeff00);
    WRITE32(0xa0001010, 0x11112222);
    WRITE32(0xa0001014, 0x33334444); 
    WRITE32(0xa0001018, 0x55556666);
    WRITE32(0xa000101c, 0x77778888);

    WRITE32( PDCH, 0x00000006);     // port2 switch to ch1
    WRITE32(0xa0000010, 0x87654321);    // 
    WRITE32(0xa0000014, 0x0fedcba9);    // 
    WRITE32(0xa0000018, 0x55555555);    // 
    WRITE32(0xa000001c, 0xaaaaaaaa);    // 
    WRITE32(0xa0000020, 0x55555555);    // 
    WRITE32(0xa0000024, 0xaaaaaaaa);    // 
    WRITE32(0xa0000028, 0x44332211);    // 
    WRITE32(0xa000002c, 0x88776655);    // 
    
    for (i = 0; i < DDRC_NUMBER; i++) 
    {
        WRITE32(0x40080420, i); // dram_sel 
    
        if (i==0) DEBUG_MSG("DDRC#0 ch0 read test. \n"); 
        else if (i==1) DEBUG_MSG("DDRC#1 read test. \n"); 
        else if (i==2) DEBUG_MSG("DDRC#2 read test. \n"); 
        else if (i==3) DEBUG_MSG("DDRC#3 read test. \n"); 
        else if (i==4) DEBUG_MSG("DDRC#4 read test. \n"); 
        else if (i==5) DEBUG_MSG("DDRC#5 read test. \n"); 
        else if (i==6) DEBUG_MSG("DDRC#6 read test. \n"); 
        else if (i==7) DEBUG_MSG("DDRC#7 read test. \n"); 
    
        WRITE32(PDCH, 0x00000002);     // port2 switch to ch0
        if (READ32(0xa0000000) == 0x12345678) {
            DEBUG_MSG("DDR read data = 0x12345678\n");
        } else {
            DEBUG_MSG("DDR read data Error!\n");
        } 
    
        if(READ32(0xa0000004) == 0x9abcdef0) {
            DEBUG_MSG("DDR read data = 0x9abcdef0\n");
        } else {
            DEBUG_MSG("DDR read data Error!\n");
        }
    
        WRITE32(PDCH, 0x00000006);     // port2 switch to ch1
        if(READ32(0xa0000010) == 0x87654321) {
            DEBUG_MSG("DDR read data = 0x87654321\n");
        } else {
            DEBUG_MSG("DDR read data Error!\n");
        }  // 
    
        if(READ32(0xa0000014) == 0x0fedcba9) {
            DEBUG_MSG("DDR read data = 0x0fedcba9\n");
        } else {
            DEBUG_MSG("DDR read data Error!\n");
        }  // 
    }
#endif
}

void ddrc_x8_ddr4_init(int chs)
{
    int i = 0;

    /////////////////////////////////////////////
    // step 1 : Program the DWC_ddr_umctl2 registers 
    WRITE32 (              DBG1, 0x00000001); 
    WRITE32 (            PWRCTL, 0x00000001); 
    WRITE32 (              MSTR, 0x80040410);    // burstchop = 0, BL8
    //WRITE32 (              MSTR, 0x80040610);    // burstchop = 1, BC4/8 on the fly
    WRITE32 (           MRCTRL0, 0x0000f010); 
    WRITE32 (           MRCTRL1, 0x0000d8cd); 
    WRITE32 (           MRCTRL2, 0x85fdc6aa); 
    WRITE32 (            PWRCTL, 0x000000aa); 
    WRITE32 (            PWRTMG, 0x00090002); 
    WRITE32 (           HWLPCTL, 0x00bb0002); 
    WRITE32 (          RFSHCTL0, 0x00e09040); 
    WRITE32 (          RFSHCTL3, 0x00000000); 
    WRITE32 (           RFSHTMG, 0x0092009d); 
    WRITE32 (        CRCPARCTL0, 0x00000000); 
    WRITE32 (        CRCPARCTL1, 0x00000000); 
    WRITE32 (             INIT0, 0xc0020003); 
    WRITE32 (             INIT1, 0x00010004); 
    WRITE32 (             INIT3, 0x0a310001); 
    WRITE32 (             INIT4, 0x00280200); 
    WRITE32 (             INIT5, 0x00110000); 
    WRITE32 (             INIT6, 0x00000640); 
    WRITE32 (             INIT7, 0x00000800); 
    WRITE32 (           DIMMCTL, 0x00000020); 
    WRITE32 (          DRAMTMG0, 0x14132814); 
    WRITE32 (          DRAMTMG1, 0x0004051b); 
    WRITE32 (          DRAMTMG2, 0x0808030f); 
    WRITE32 (          DRAMTMG3, 0x0000400c); 
    WRITE32 (          DRAMTMG4, 0x08030409); 
    WRITE32 (          DRAMTMG5, 0x0a0b0404); 
    WRITE32 (          DRAMTMG8, 0x04040e0e); 
    WRITE32 (          DRAMTMG9, 0x0002040c); 
    WRITE32 (         DRAMTMG10, 0x000e0c0d); 
    WRITE32 (         DRAMTMG11, 0x1309011b); 
    WRITE32 (         DRAMTMG12, 0x0000000d); 
    WRITE32 (         DRAMTMG15, 0x80000000); 
    WRITE32 (            ZQCTL0, 0x51000040); 
    WRITE32 (            ZQCTL1, 0x00000070); 
    WRITE32 (           DFITMG0, 0x048a820b);  // CL=15
    //dfi_t_rddata_en changed, manual setting, due to cl=18 by phyinit
    //WRITE32 (           DFITMG0, 0x048d820b);    // CL=18
    WRITE32 (           DFITMG1, 0x03070303); 
    WRITE32 (         DFILPCFG0, 0x03006030); 
    WRITE32 (         DFILPCFG1, 0x00000020); 
    WRITE32 (           DFIUPD0, 0x00400018); 
    WRITE32 (           DFIUPD1, 0x003400a1); 
    WRITE32 (           DFIUPD2, 0x80000000); 
    WRITE32 (           DFIMISC, 0x00000059); 
    WRITE32 (           DFITMG2, 0x00000a0b); 
    WRITE32 (           DFITMG3, 0x0000001f); 
    WRITE32 (            DBICTL, 0x00000001); 
    WRITE32 (        DFIPHYMSTR, 0x00000000); 

    soc_addrmap (1, 2) ;    // ddr4 4GB

    WRITE32 (            ODTCFG, 0x04180b20); 
    WRITE32 (            ODTMAP, 0x00000001); 
    WRITE32 (             SCHED, 0x408e2303); 
    WRITE32 (            SCHED1, 0x00000000); 
    WRITE32 (          PERFHPR1, 0x88001008); 
    WRITE32 (          PERFLPR1, 0x4c000d1e); 
    WRITE32 (           PERFWR1, 0xd3004f73); 
    WRITE32 (              DBG0, 0x00000004); 
    WRITE32 (              DBG1, 0x00000000); 
    WRITE32 (            DBGCMD, 0x00000000); 
    WRITE32 (             SWCTL, 0x00000001); 
    WRITE32 (         POISONCFG, 0x00000011); 
    WRITE32 (             PCCFG, 0x00000011); 
    WRITE32 (           PCFGR_0, 0x00001122); 
    WRITE32 (           PCFGW_0, 0x0000522a); 
    WRITE32 (           PCTRL_0, 0x00000001); 
    WRITE32 (        PCFGQOS0_0, 0x0012000b); 
    WRITE32 (        PCFGQOS1_0, 0x01a003c6); 
    WRITE32 (       PCFGWQOS0_0, 0x01110e02); 
    WRITE32 (       PCFGWQOS1_0, 0x06a4076f); 
    WRITE32 (           PCFGR_1, 0x000063b0); 
    WRITE32 (           PCFGW_1, 0x0000613a); 
    WRITE32 (           PCTRL_1, 0x00000001); 
    WRITE32 (        PCFGQOS0_1, 0x00020007); 
    WRITE32 (        PCFGQOS1_1, 0x000507c0); 
    WRITE32 (       PCFGWQOS0_1, 0x01010802); 
    WRITE32 (       PCFGWQOS1_1, 0x00d60326); 
    WRITE32 (           PCFGR_2, 0x00002392); 
    WRITE32 (           PCFGW_2, 0x00007159); 
    WRITE32 (           PCTRL_2, 0x00000001); 
    WRITE32 (        PCFGQOS0_2, 0x00010001); 
    WRITE32 (        PCFGQOS1_2, 0x07100408); 
    WRITE32 (       PCFGWQOS0_2, 0x01010b04); 
    WRITE32 (       PCFGWQOS1_2, 0x066603b8); 
    WRITE32 (              PDCH, 0x00000003); 
    WRITE32 (      DCH1_MRCTRL0, 0x0000f010); 
    WRITE32 (      DCH1_MRCTRL1, 0x0000d8cd); 
    WRITE32 (      DCH1_MRCTRL2, 0x85fdc6aa); 
    WRITE32 (       DCH1_PWRCTL, 0x000000aa); 
    WRITE32 (      DCH1_HWLPCTL, 0x00bb0002); 
    WRITE32 (   DCH1_CRCPARCTL0, 0x00000000); 
    WRITE32 (       DCH1_ODTMAP, 0x00000001); 
    WRITE32 (         DCH1_DBG1, 0x00000000); 
    WRITE32 (       DCH1_DBGCMD, 0x00000000); 
    WRITE32 (            PWRCTL, 0x000000a2); 
    WRITE32 (       DCH1_PWRCTL, 0x000000a2); 

    /////////////////////////////////////////////
    //RESET: <aresetn> for Port 2  DEASSERTED
    //RESET: <aresetn> for Port 1  DEASSERTED
    //RESET: <aresetn> for Port 0  DEASSERTED
    //RESET: <core_ddrc_rstn> DEASSERTED
    //
    //// step 2 : Deassert core_ddrc_rstn (according to reference test case)
    for (i = 0; i < chs; i++) 
    {
        WRITE32(0x4008c000 + (i * 0x400), 0x00);    // release core/pub apb reset 
    }

    /////////////////////////////////////////////
    WRITE32 (              DBG1, 0x00000000); 
    WRITE32 (            PWRCTL, 0x000000a2); 
    WRITE32 (            PWRCTL, 0x000000a0); 
    WRITE32 (         DCH1_DBG1, 0x00000000); 
    WRITE32 (       DCH1_PWRCTL, 0x000000a2); 
    WRITE32 (       DCH1_PWRCTL, 0x000000a0); 
    WRITE32 (        DFIPHYMSTR, 0x00000000); 
    WRITE32 (             SWCTL, 0x00000000); 
    WRITE32 (           DFIMISC, 0x00000059); 
    WRITE32 (           DFIMISC, 0x00000058); 
    WRITE32 (           DFIMISC, 0x00000058); 
    WRITE32 (              DBG1, 0x00000002); 
    WRITE32 (         DCH1_DBG1, 0x00000002); 

    //  step 3   Start PHY initialization by accessing relevant PUB registers 
    #if 0
    ddr3_init_dmem(PUB_ADDR_BASE);
    ddr3_init_imem(PUB_ADDR_BASE);
    #endif
    
    ddr4_pub_phy_init(PUB_ADDR_BASE, 1);

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
        while((READ32(DFISTAT) & 0x1) != 0x1) ;
    }
    WRITE32(           DFIMISC , 0x00000058);    // set dfi_init_start = 0 
    WRITE32(           DFIMISC , 0x00000059);    // set dfi_init_complete_en = 1
    WRITE32(            PWRCTL , 0x00000080); 
    WRITE32(       DCH1_PWRCTL , 0x00000080); 

    // step 8 : Set SWCTL.sw_done to 1 
    WRITE32(             SWCTL , 0x00000001);    // set sw_done =1
    // step 9 : Wait for SWSTAT.sw_done_ack to become 1 
    // wait sw_done_ack = 1
    // polling bit[0]= 1 (change from 0 to 1)
    for (i = 0; i < chs; i++) 
    {
        WRITE32(0x40080420, i); // dram_sel 
        while((READ32(SWSTAT) & 0x1) != 0x1) ;
    }

    // step 10 :    Wait for DWC_ddr_umctl2 to move to “normal” operating mode by monitoring STAT.operating_mode signal 
    // wait normal state = 1
    for (i = 0; i < chs; i++) 
    {
        WRITE32(0x40080420, i); // dram_sel 
        while((READ32(STAT) & 0x3) != 0x1) ;
        while((READ32(DCH1_STAT) & 0x3) != 0x1) ;
    }

    WRITE32(        DFIPHYMSTR , 0x00000000);    // set dfi_phymstr_en   = 0
    WRITE32(             SWCTL , 0x00000000);    // set sw_done = 0
    WRITE32(             INIT0 , 0x00020003); 
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
    WRITE32(            PWRCTL , 0x00000082); 
    WRITE32(       DCH1_PWRCTL , 0x00000082); 
    WRITE32(           PCTRL_0 , 0x00000001);    // port enable
    WRITE32(           PCTRL_1 , 0x00000001); 
    WRITE32(           PCTRL_2 , 0x00000001); 
}

static void soc_addrmap (int ddr_type, int cs_size)
{
    // ddr_type -> 0 : ddr3, 1 : ddr4
    // cs_size  -> 0 : 1GB , 1 : 2GB, 2 : 4GB

    //MEMC_BURST_LENGTH=8, MEMC_DRAM_DATA_WIDTH =32, UMCTL2_A_ADDRW = 32, MEMC_FREQ_RATIO=2
    //hif_cmd_addr[36:log2(MEMC_BURST_LENGTH)] = {ARADDR | AWADDR | HADDR} [UMCTL2_A_ADDRW-1:log2(MEMC_BURST_LENGTH)+log2(MEMC_DRAM_DATA_WIDTH/8)]
    //hif_cmd_addr[log2(MEMC_BURST_LENGTH)-1:MEMC_FREQ_RATIO] is internally generated by XPI
    //hif_cmd_addr [MEMC_FREQ_RATIO-1:0] = 0
    //generated :
    //hif_cmd_addr[36:30]   = 0
    //hif_cmd_addr[29:3]    = {ARADDR | AWADDR}[31:5];  // mapping lsb  
    //hif_cmd_addr[2:2]     = internally generated by XPI   // soc[4]
    //hif_cmd_addr[1:0]     = 0                             // soc[3:2]

    //fpga mapping to hif_cmd_addr[28:0] = {row[15:0], bank[2:0], col[9:0]} 
    //axi_addr[30:0] =  {row[15:0], bank[2:0], col[9:0], 2'd0} = 2GB

    //axi_addr[31:0] =  {1'd0, 1'd0, row[14:0], bank[2:0], col[9:0], 2'd0}  // 1GB
    //axi_addr[31:0] =  {1'd0,       row[15:0], bank[2:0], col[9:0], 2'd0}  // 2GB
    //axi_addr[31:0] =  {            row[16:0], bank[2:0], col[9:0], 2'd0}  // 4GB

    //bank_b2/1/0, internal base is 4/3/2
    if (ddr_type == 1) {
        WRITE32(ADDRMAP1, 0x003f0808); //bank[2:0]    // no bank[2] for ddr4
    } else {
        WRITE32(ADDRMAP1, 0x00080808); //bank[2:0] 
    }
    
    //full bus mode
    //col_b5/4/3/2, internal base is 5/4/3/2, col_b2 always set to 0
    WRITE32(ADDRMAP2, 0x00000000); 
    //col_b9/8/7/6, internal base is 9/8/7/6
    WRITE32(ADDRMAP3, 0x00000000); 
    //col_b11/b10, no used, set to 0x1f
    WRITE32(ADDRMAP4, 0x00001f1f); 
    //row_b11, b2_10, b1, b0, internal base from 6 to 17
    WRITE32(ADDRMAP5, 0x07070707); 
    
    //row_b15, b14, b13, b12, internal base from 18 to 21, no use set to 0xf
    if (cs_size == 0) {
        WRITE32(ADDRMAP6, 0x0f070707);        // 1GB
        //row_b17, b16, no used
        WRITE32(ADDRMAP7, 0x00000f0f); 
    } else if (cs_size == 1 ) {
        WRITE32(ADDRMAP6, 0x07070707);        // 2GB 
        WRITE32(ADDRMAP7, 0x00000f0f); 
    } else if (cs_size == 2 ) {
        WRITE32(ADDRMAP6, 0x07070707);        // 4GB 
        WRITE32(ADDRMAP7, 0x00000f07); 
    }
    
    // bg_b1/b0, ddr3 no use
    WRITE32(ADDRMAP8, 0x00003f3f); 
    //row_b5/4/3/2, only used when row_b2_10 set to 0xf
    WRITE32(ADDRMAP9, 0x07070707); 
    //row_b9/8/7/6, only used when row_b2_10 set to 0xf
    WRITE32(ADDRMAP10, 0x07070707); 
    //row_b10, only used when row_b2_10 set to 0xf
    WRITE32(ADDRMAP11, 0x00000007); 
}

