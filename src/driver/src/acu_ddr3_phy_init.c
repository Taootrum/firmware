#include "acu_ddr_init.h"

void ddr3_pub_phy_init(int DPHY_ADDR_BASE,int chs)
{
    // [dwc_ddrphy_phyinit_main] Start of dwc_ddrphy_phyinit_main()
    // [dwc_ddrphy_phyinit_sequence] Start of dwc_ddrphy_phyinit_sequence()
    // [dwc_ddrphy_phyinit_initStruct] Start of dwc_ddrphy_phyinit_initStruct()
    // [dwc_ddrphy_phyinit_initStruct] End of dwc_ddrphy_phyinit_initStruct()
    // [dwc_ddrphy_phyinit_setDefault] Start of dwc_ddrphy_phyinit_setDefault()
    // [dwc_ddrphy_phyinit_setDefault] End of dwc_ddrphy_phyinit_setDefault()


    // //##############################################################
    // 
    // // dwc_ddrphy_phyinit_userCustom_overrideUserInput is a user-editable function.
    // //
    // // See PhyInit App Note for detailed description and function usage
    //
    // //##############################################################

    // //##############################################################
    // //
    // // Step (A) : Bring up VDD, VDDQ, and VAA 
    // //
    // // See PhyInit App Note for detailed description and function usage
    // //
    // //############################################################## 


    //dwc_ddrphy_phyinit_userCustom_A_bringupPower ();

    // [dwc_ddrphy_phyinit_userCustom_A_bringupPower] End of dwc_ddrphy_phyinit_userCustom_A_bringupPower()
    // [dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy] Start of dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy()
    // 
    // 
    // //##############################################################
    // //
    // // Step (B) Start Clocks and Reset the PHY 
    // //
    // // See PhyInit App Note for detailed description and function usage
    // //
    // //##############################################################
    // 
    // 
    //dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy ();

    // [dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy] End of dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy()
    // 

    // //##############################################################
    // //
    // // Step (C) Initialize PHY Configuration 
    // //
    // // Load the required PHY configuration registers for the appropriate mode and memory configuration
    // //
    // //##############################################################
    // 

    // // [phyinit_C_initPhyConfig] Start of dwc_ddrphy_phyinit_C_initPhyConfig()
    // 
    // //##############################################################
    // // TxPreDrvMode[2] = 0
    // //##############################################################
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TxSlewRate::TxPreDrvMode to 0x3
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TxSlewRate::TxPreP to 0xf
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TxSlewRate::TxPreN to 0xf
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for TxSlewRate::TxPreP and TxSlewRate::TxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x1005f,0x3ff); // DWC_DDRPHYA_DBYTE0_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1015f,0x3ff); // DWC_DDRPHYA_DBYTE0_TxSlewRate_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1105f,0x3ff); // DWC_DDRPHYA_DBYTE1_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1115f,0x3ff); // DWC_DDRPHYA_DBYTE1_TxSlewRate_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1205f,0x3ff); // DWC_DDRPHYA_DBYTE2_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1215f,0x3ff); // DWC_DDRPHYA_DBYTE2_TxSlewRate_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1305f,0x3ff); // DWC_DDRPHYA_DBYTE3_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1315f,0x3ff); // DWC_DDRPHYA_DBYTE3_TxSlewRate_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1405f,0x3ff); // DWC_DDRPHYA_DBYTE4_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1415f,0x3ff); // DWC_DDRPHYA_DBYTE4_TxSlewRate_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1505f,0x3ff); // DWC_DDRPHYA_DBYTE5_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1515f,0x3ff); // DWC_DDRPHYA_DBYTE5_TxSlewRate_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1605f,0x3ff); // DWC_DDRPHYA_DBYTE6_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1615f,0x3ff); // DWC_DDRPHYA_DBYTE6_TxSlewRate_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1705f,0x3ff); // DWC_DDRPHYA_DBYTE7_TxSlewRate_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1715f,0x3ff); // DWC_DDRPHYA_DBYTE7_TxSlewRate_b1_p0
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=0
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=0
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=0
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x55,0x3ff); // DWC_DDRPHYA_ANIB0_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=1
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=1
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=1
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x1055,0x3ff); // DWC_DDRPHYA_ANIB1_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=2
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=2
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=2
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x2055,0x3ff); // DWC_DDRPHYA_ANIB2_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=3
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=3
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=3
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x3055,0x3ff); // DWC_DDRPHYA_ANIB3_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x0, ANIB=4
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=4
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=4
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x4055,0xff); // DWC_DDRPHYA_ANIB4_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x0, ANIB=5
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=5
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=5
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x5055,0xff); // DWC_DDRPHYA_ANIB5_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=6
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=6
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=6
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x6055,0x3ff); // DWC_DDRPHYA_ANIB6_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=7
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=7
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=7
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x7055,0x3ff); // DWC_DDRPHYA_ANIB7_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=8
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=8
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=8
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x8055,0x3ff); // DWC_DDRPHYA_ANIB8_ATxSlewRate
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=9
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreP to 0xf, ANIB=9
    // // [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreN to 0xf, ANIB=9
    // // [phyinit_C_initPhyConfig] ### NOTE ### Optimal setting for ATxSlewRate::ATxPreP and ATxSlewRate::ATxPreP are technology specific.
    // // [phyinit_C_initPhyConfig] ### NOTE ### Please consult the "Output Slew Rate" section of HSpice Model App Note in specific technology for recommended settings

    WRITE32(DPHY_ADDR_BASE+4*0x9055,0x3ff); // DWC_DDRPHYA_ANIB9_ATxSlewRate
    WRITE32(DPHY_ADDR_BASE+4*0x200c5,0xa); // DWC_DDRPHYA_MASTER0_PllCtrl2_p0
    // // [phyinit_C_initPhyConfig] Pstate=0,  Memclk=1067MHz, Programming PllCtrl2 to a based on DfiClk frequency = 533.
    // 
    // //##############################################################
    // //
    // // Program ARdPtrInitVal based on Frequency and PLL Bypass inputs
    // // The values programmed here assume ideal properties of DfiClk
    // // and Pclk including:
    // // - DfiClk skew
    // // - DfiClk jitter
    // // - DfiClk PVT variations
    // // - Pclk skew
    // // - Pclk jitter
    // //
    // // PLL Bypassed mode:
    // //     For MemClk frequency > 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 2-6
    // //     For MemClk frequency < 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 1-6
    // //
    // // PLL Enabled mode:
    // //     For MemClk frequency > 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 1-6
    // //     For MemClk frequency < 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 0-6
    // //
    // //##############################################################
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming ARdPtrInitVal to 0x2
    WRITE32(DPHY_ADDR_BASE+4*0x2002e,0x2); // DWC_DDRPHYA_MASTER0_ARdPtrInitVal_p0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DqsPreambleControl::TwoTckRxDqsPre to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DqsPreambleControl::TwoTckTxDqsPre to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DqsPreambleControl::PositionDfeInit to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DqsPreambleControl::LP4TglTwoTckTxDqsPre to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DqsPreambleControl::LP4PostambleExt to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DqsPreambleControl::LP4SttcPreBridgeRxEn to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DqsPreambleControl to 0x0
    WRITE32(DPHY_ADDR_BASE+4*0x20024,0x0); // DWC_DDRPHYA_MASTER0_DqsPreambleControl_p0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DbyteDllModeCntrl to 0x0
    WRITE32(DPHY_ADDR_BASE+4*0x2003a,0x0); // DWC_DDRPHYA_MASTER0_DbyteDllModeCntrl
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming ProcOdtTimeCtl to 0x6
    WRITE32(DPHY_ADDR_BASE+4*0x20056,0x6); // DWC_DDRPHYA_MASTER0_ProcOdtTimeCtl_p0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TxOdtDrvStren::ODTStrenP to 0x8
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TxOdtDrvStren::ODTStrenN to 0x8
    WRITE32(DPHY_ADDR_BASE+4*0x1004d,0x208); // DWC_DDRPHYA_DBYTE0_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1014d,0x208); // DWC_DDRPHYA_DBYTE0_TxOdtDrvStren_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1104d,0x208); // DWC_DDRPHYA_DBYTE1_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1114d,0x208); // DWC_DDRPHYA_DBYTE1_TxOdtDrvStren_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1204d,0x208); // DWC_DDRPHYA_DBYTE2_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1214d,0x208); // DWC_DDRPHYA_DBYTE2_TxOdtDrvStren_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1304d,0x208); // DWC_DDRPHYA_DBYTE3_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1314d,0x208); // DWC_DDRPHYA_DBYTE3_TxOdtDrvStren_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1404d,0x208); // DWC_DDRPHYA_DBYTE4_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1414d,0x208); // DWC_DDRPHYA_DBYTE4_TxOdtDrvStren_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1504d,0x208); // DWC_DDRPHYA_DBYTE5_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1514d,0x208); // DWC_DDRPHYA_DBYTE5_TxOdtDrvStren_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1604d,0x208); // DWC_DDRPHYA_DBYTE6_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1614d,0x208); // DWC_DDRPHYA_DBYTE6_TxOdtDrvStren_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1704d,0x208); // DWC_DDRPHYA_DBYTE7_TxOdtDrvStren_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x1714d,0x208); // DWC_DDRPHYA_DBYTE7_TxOdtDrvStren_b1_p0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TxImpedanceCtrl1::DrvStrenFSDqP to 0x18
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TxImpedanceCtrl1::DrvStrenFSDqN to 0x18
    WRITE32(DPHY_ADDR_BASE+4*0x10049,0x618); // DWC_DDRPHYA_DBYTE0_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x10149,0x618); // DWC_DDRPHYA_DBYTE0_TxImpedanceCtrl1_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x11049,0x618); // DWC_DDRPHYA_DBYTE1_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x11149,0x618); // DWC_DDRPHYA_DBYTE1_TxImpedanceCtrl1_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x12049,0x618); // DWC_DDRPHYA_DBYTE2_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x12149,0x618); // DWC_DDRPHYA_DBYTE2_TxImpedanceCtrl1_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x13049,0x618); // DWC_DDRPHYA_DBYTE3_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x13149,0x618); // DWC_DDRPHYA_DBYTE3_TxImpedanceCtrl1_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x14049,0x618); // DWC_DDRPHYA_DBYTE4_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x14149,0x618); // DWC_DDRPHYA_DBYTE4_TxImpedanceCtrl1_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x15049,0x618); // DWC_DDRPHYA_DBYTE5_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x15149,0x618); // DWC_DDRPHYA_DBYTE5_TxImpedanceCtrl1_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x16049,0x618); // DWC_DDRPHYA_DBYTE6_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x16149,0x618); // DWC_DDRPHYA_DBYTE6_TxImpedanceCtrl1_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x17049,0x618); // DWC_DDRPHYA_DBYTE7_TxImpedanceCtrl1_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x17149,0x618); // DWC_DDRPHYA_DBYTE7_TxImpedanceCtrl1_b1_p0
    // // [phyinit_C_initPhyConfig] Programming ATxImpedance::ADrvStrenP to 0x1f
    // // [phyinit_C_initPhyConfig] Programming ATxImpedance::ADrvStrenN to 0x1f
    WRITE32(DPHY_ADDR_BASE+4*0x43,0x3ff); // DWC_DDRPHYA_ANIB0_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x1043,0x3ff); // DWC_DDRPHYA_ANIB1_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x2043,0x3ff); // DWC_DDRPHYA_ANIB2_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x3043,0x3ff); // DWC_DDRPHYA_ANIB3_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x4043,0x3ff); // DWC_DDRPHYA_ANIB4_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x5043,0x3ff); // DWC_DDRPHYA_ANIB5_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x6043,0x3ff); // DWC_DDRPHYA_ANIB6_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x7043,0x3ff); // DWC_DDRPHYA_ANIB7_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x8043,0x3ff); // DWC_DDRPHYA_ANIB8_ATxImpedance
    WRITE32(DPHY_ADDR_BASE+4*0x9043,0x3ff); // DWC_DDRPHYA_ANIB9_ATxImpedance
    // // [phyinit_C_initPhyConfig] Programming DfiMode to 0x1
    WRITE32(DPHY_ADDR_BASE+4*0x20018,0x1); // DWC_DDRPHYA_MASTER0_DfiMode
    // // [phyinit_C_initPhyConfig] Programming DfiCAMode to 0x0
    WRITE32(DPHY_ADDR_BASE+4*0x20075,0x0); // DWC_DDRPHYA_MASTER0_DfiCAMode
    // // [phyinit_C_initPhyConfig] Programming CalDrvStr0::CalDrvStrPd50 to 0x0
    // // [phyinit_C_initPhyConfig] Programming CalDrvStr0::CalDrvStrPu50 to 0x0
    WRITE32(DPHY_ADDR_BASE+4*0x20050,0x0); // DWC_DDRPHYA_MASTER0_CalDrvStr0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming CalUclkInfo::CalUClkTicksPer1uS to 0x216
    WRITE32(DPHY_ADDR_BASE+4*0x20008,0x216); // DWC_DDRPHYA_MASTER0_CalUclkInfo_p0
    // // [phyinit_C_initPhyConfig] Programming CalRate::CalInterval to 0x9
    // // [phyinit_C_initPhyConfig] Programming CalRate::CalOnce to 0x0
    WRITE32(DPHY_ADDR_BASE+4*0x20088,0x9); // DWC_DDRPHYA_MASTER0_CalRate
    // // [phyinit_C_initPhyConfig] Pstate=0, Programming VrefInGlobal::GlobalVrefInSel to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Programming VrefInGlobal::GlobalVrefInDAC to 0x41
    // // [phyinit_C_initPhyConfig] Pstate=0, Programming VrefInGlobal to 0x208
    WRITE32(DPHY_ADDR_BASE+4*0x200b2,0x208); // DWC_DDRPHYA_MASTER0_VrefInGlobal_p0
    // // [phyinit_C_initPhyConfig] Pstate=0, Programming DqDqsRcvCntrl::MajorModeDbyte to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Programming DqDqsRcvCntrl to 0x581
    WRITE32(DPHY_ADDR_BASE+4*0x10043,0x581); // DWC_DDRPHYA_DBYTE0_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x10143,0x581); // DWC_DDRPHYA_DBYTE0_DqDqsRcvCntrl_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x11043,0x581); // DWC_DDRPHYA_DBYTE1_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x11143,0x581); // DWC_DDRPHYA_DBYTE1_DqDqsRcvCntrl_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x12043,0x581); // DWC_DDRPHYA_DBYTE2_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x12143,0x581); // DWC_DDRPHYA_DBYTE2_DqDqsRcvCntrl_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x13043,0x581); // DWC_DDRPHYA_DBYTE3_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x13143,0x581); // DWC_DDRPHYA_DBYTE3_DqDqsRcvCntrl_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x14043,0x581); // DWC_DDRPHYA_DBYTE4_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x14143,0x581); // DWC_DDRPHYA_DBYTE4_DqDqsRcvCntrl_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x15043,0x581); // DWC_DDRPHYA_DBYTE5_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x15143,0x581); // DWC_DDRPHYA_DBYTE5_DqDqsRcvCntrl_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x16043,0x581); // DWC_DDRPHYA_DBYTE6_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x16143,0x581); // DWC_DDRPHYA_DBYTE6_DqDqsRcvCntrl_b1_p0
    WRITE32(DPHY_ADDR_BASE+4*0x17043,0x581); // DWC_DDRPHYA_DBYTE7_DqDqsRcvCntrl_b0_p0
    WRITE32(DPHY_ADDR_BASE+4*0x17143,0x581); // DWC_DDRPHYA_DBYTE7_DqDqsRcvCntrl_b1_p0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming DfiFreqRatio_p0 to 0x1
    WRITE32(DPHY_ADDR_BASE+4*0x200fa,0x1); // DWC_DDRPHYA_MASTER0_DfiFreqRatio_p0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TristateModeCA::DisDynAdrTri_p0 to 0x0
    // // [phyinit_C_initPhyConfig] Pstate=0, Memclk=1067MHz, Programming TristateModeCA::DDR2TMode_p0 to 0x0
    WRITE32(DPHY_ADDR_BASE+4*0x20019,0x4); // DWC_DDRPHYA_MASTER0_TristateModeCA_p0
    // // [phyinit_C_initPhyConfig] Programming DfiFreqXlat*
    WRITE32(DPHY_ADDR_BASE+4*0x200f0,0x5555); // DWC_DDRPHYA_MASTER0_DfiFreqXlat0
    WRITE32(DPHY_ADDR_BASE+4*0x200f1,0x5555); // DWC_DDRPHYA_MASTER0_DfiFreqXlat1
    WRITE32(DPHY_ADDR_BASE+4*0x200f2,0x5555); // DWC_DDRPHYA_MASTER0_DfiFreqXlat2
    WRITE32(DPHY_ADDR_BASE+4*0x200f3,0x5555); // DWC_DDRPHYA_MASTER0_DfiFreqXlat3
    WRITE32(DPHY_ADDR_BASE+4*0x200f4,0x5555); // DWC_DDRPHYA_MASTER0_DfiFreqXlat4
    WRITE32(DPHY_ADDR_BASE+4*0x200f5,0x5555); // DWC_DDRPHYA_MASTER0_DfiFreqXlat5
    WRITE32(DPHY_ADDR_BASE+4*0x200f6,0x5555); // DWC_DDRPHYA_MASTER0_DfiFreqXlat6
    WRITE32(DPHY_ADDR_BASE+4*0x200f7,0xf000); // DWC_DDRPHYA_MASTER0_DfiFreqXlat7
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.0
    WRITE32(DPHY_ADDR_BASE+4*0x1004a,0x500); // DWC_DDRPHYA_DBYTE0_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.1
    WRITE32(DPHY_ADDR_BASE+4*0x1104a,0x500); // DWC_DDRPHYA_DBYTE1_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.2
    WRITE32(DPHY_ADDR_BASE+4*0x1204a,0x500); // DWC_DDRPHYA_DBYTE2_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.3
    WRITE32(DPHY_ADDR_BASE+4*0x1304a,0x500); // DWC_DDRPHYA_DBYTE3_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.4
    WRITE32(DPHY_ADDR_BASE+4*0x1404a,0x500); // DWC_DDRPHYA_DBYTE4_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.5
    WRITE32(DPHY_ADDR_BASE+4*0x1504a,0x500); // DWC_DDRPHYA_DBYTE5_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.6
    WRITE32(DPHY_ADDR_BASE+4*0x1604a,0x500); // DWC_DDRPHYA_DBYTE6_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.7
    WRITE32(DPHY_ADDR_BASE+4*0x1704a,0x500); // DWC_DDRPHYA_DBYTE7_DqDqsRcvCntrl1
    // // [phyinit_C_initPhyConfig] Programming MasterX4Config::X4TG to 0x0
    WRITE32(DPHY_ADDR_BASE+4*0x20025,0x0); // DWC_DDRPHYA_MASTER0_MasterX4Config
    // // [phyinit_C_initPhyConfig] End of dwc_ddrphy_phyinit_C_initPhyConfig()
    // 
    // 
    // //##############################################################
    // //
    // // dwc_ddrphy_phyihunit_userCustom_customPreTrain is a user-editable function.
    // //
    // // See PhyInit App Note for detailed description and function usage
    // //
    // //##############################################################
    // 
    // // [phyinit_userCustom_customPreTrain] Start of dwc_ddrphy_phyinit_userCustom_customPreTrain()
    // // [phyinit_userCustom_customPreTrain] End of dwc_ddrphy_phyinit_userCustom_customPreTrain()
    // // [dwc_ddrphy_phyinit_D_loadIMEM, 1D] Start of dwc_ddrphy_phyinit_D_loadIMEM (Train2D=0)
    // 
    // 
    // //##############################################################
    // //
    // // (D) Load the 1D IMEM image
    // // 
    // // This function loads the training firmware IMEM image into the SRAM.
    // // See PhyInit App Note for detailed description and function usage
    // // 
    // //##############################################################
    // 
    // 
    // // [dwc_ddrphy_phyinit_D_loadIMEM, 1D] Programming MemResetL to 0x2
    WRITE32(DPHY_ADDR_BASE+4*0x20060,0x2); // DWC_DDRPHYA_MASTER0_MemResetL
    // [dwc_ddrphy_phyinit_storeIncvFile] Reading input file: /home/socplayer/hong.li/synopsys_ddr_2p50a/synopsys/dwc_lpddr4_multiphy_v2_tsmc28hpcp18/Latest/firmware/Latest/ddr3/ddr3_pmu_train_imem.incv

    // // 1.    Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
    // //       This allows the memory controller unrestricted access to the configuration CSRs. 
    WRITE32(DPHY_ADDR_BASE+4*0xd0000,0x0); // DWC_DDRPHYA_APBONLY0_MicroContMuxSel
    // // [dwc_ddrphy_phyinit_WriteOutMem] STARTING. offset 0x50000 size 0x4000
    // // [dwc_ddrphy_phyinit_WriteOutMem] DONE.  Index 0x36a
    // // 2.    Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. 
    // //      This allows the firmware unrestricted access to the configuration CSRs. 
    WRITE32(DPHY_ADDR_BASE+4*0xd0000,0x1); // DWC_DDRPHYA_APBONLY0_MicroContMuxSel
    // // [phyinit_F_loadDMEM, 1D] End of dwc_ddrphy_phyinit_F_loadDMEM()
    // 
    // 
    // //##############################################################
    // //
    // // (G) Execute the Training Firmware 
    // // 
    // // See PhyInit App Note for detailed description and function usage
    // //
    // //##############################################################
    // 
    // 
    // // 1.  Reset the firmware microcontroller by writing the MicroReset CSR to set the StallToMicro and 
    // //     ResetToMicro fields to 1 (all other fields should be zero). 
    // //     Then rewrite the CSR so that only the StallToMicro remains set (all other fields should be zero). 
    WRITE32(DPHY_ADDR_BASE+4*0xd0000,0x1); // DWC_DDRPHYA_APBONLY0_MicroContMuxSel
    WRITE32(DPHY_ADDR_BASE+4*0xd0099,0x9); // DWC_DDRPHYA_APBONLY0_MicroReset
    WRITE32(DPHY_ADDR_BASE+4*0xd0099,0x1); // DWC_DDRPHYA_APBONLY0_MicroReset
    // 
    // // 2. Begin execution of the training firmware by setting the MicroReset CSR to 4'b0000. 
    WRITE32(DPHY_ADDR_BASE+4*0xd0099,0x0); // DWC_DDRPHYA_APBONLY0_MicroReset
    // 
    // // 3.   Wait for the training firmware to complete by following the procedure in "uCtrl Initialization and Mailbox Messaging" 
    // // [dwc_ddrphy_phyinit_userCustom_G_waitFwDone] Wait for the training firmware to complete.  Implement timeout fucntion or follow the procedure in "3.4 Running the firmware" of the Training Firmware Application Note to poll the Mailbox message.
    //dwc_ddrphy_phyinit_userCustom_G_waitFwDone ();
    unsigned int retval = 0;
    retval = do_ddr_training(DPHY_ADDR_BASE, chs);
    if (retval) 
    { 
        DEBUG_MSG("ALL training fail !!!! \r\n");
    }
    else 
    {
        DEBUG_MSG("ALL training pass !!!! \r\n");
    }

    WRITE32(0x40080424,0xFF);//write to 8 umctl2 simutaneously

    // // [dwc_ddrphy_phyinit_userCustom_G_waitFwDone] End of dwc_ddrphy_phyinit_userCustom_G_waitFwDone()
    // // 4.   Halt the microcontroller." 
    WRITE32(DPHY_ADDR_BASE+4*0xd0099,0x1); // DWC_DDRPHYA_APBONLY0_MicroReset
    // // [dwc_ddrphy_phyinit_G_execFW] End of dwc_ddrphy_phyinit_G_execFW ()
    // 
    // 
    // //##############################################################
    // //
    // // (H) Read the Message Block results
    // // 
    // // The procedure is as follows:
    // // 
    // //##############################################################
    // 
    // 
    // // 1.    Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
    WRITE32(DPHY_ADDR_BASE+4*0xd0000,0x0); // DWC_DDRPHYA_APBONLY0_MicroContMuxSel
    // 
    // 2. Read the Firmware Message Block to obtain the results from the training.
    // This can be accomplished by issuing APB read commands to the DMEM addresses.
    // Example:
    // if (Train2D)
    // { 
    //   _read_2d_message_block_outputs_
    // }
    // else
    // {
    //   _read_1d_message_block_outputs_
    // }
    //dwc_ddrphy_phyinit_userCustom_H_readMsgBlock (0);

    // [dwc_ddrphy_phyinit_userCustom_H_readMsgBlock] End of dwc_ddrphy_phyinit_userCustom_H_readMsgBlock ()
    // // 3.    Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. 
    WRITE32(DPHY_ADDR_BASE+4*0xd0000,0x1); // DWC_DDRPHYA_APBONLY0_MicroContMuxSel
    // // 4.    If training is required at another frequency, repeat the operations starting at step (E). 
    // // [dwc_ddrphy_phyinit_H_readMsgBlock] End of dwc_ddrphy_phyinit_H_readMsgBlock()
    // // [phyinit_I_loadPIEImage] Start of dwc_ddrphy_phyinit_I_loadPIEImage()
    // 
    // 
    // //##############################################################
    // //
    // // (I) Load PHY Init Engine Image 
    // // 
    // // Load the PHY Initialization Engine memory with the provided initialization sequence.
    // // See PhyInit App Note for detailed description and function usage
    // // 
    // // 
    // //##############################################################
    // 
    // 
    // // Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0. 
    // // This allows the memory controller unrestricted access to the configuration CSRs. 
    WRITE32(DPHY_ADDR_BASE+4*0xd0000,0x0); // DWC_DDRPHYA_APBONLY0_MicroContMuxSel
    // // [phyinit_I_loadPIEImage] Programming PIE Production Code
    WRITE32(DPHY_ADDR_BASE+4*0x90000,0x10); // DWC_DDRPHYA_INITENG0_PreSequenceReg0b0s0
    WRITE32(DPHY_ADDR_BASE+4*0x90001,0x400); // DWC_DDRPHYA_INITENG0_PreSequenceReg0b0s1
    WRITE32(DPHY_ADDR_BASE+4*0x90002,0x10e); // DWC_DDRPHYA_INITENG0_PreSequenceReg0b0s2
    WRITE32(DPHY_ADDR_BASE+4*0x90003,0x0); // DWC_DDRPHYA_INITENG0_PreSequenceReg0b1s0
    WRITE32(DPHY_ADDR_BASE+4*0x90004,0x0); // DWC_DDRPHYA_INITENG0_PreSequenceReg0b1s1
    WRITE32(DPHY_ADDR_BASE+4*0x90005,0x8); // DWC_DDRPHYA_INITENG0_PreSequenceReg0b1s2
    WRITE32(DPHY_ADDR_BASE+4*0x90029,0xb); // DWC_DDRPHYA_INITENG0_SequenceReg0b0s0
    WRITE32(DPHY_ADDR_BASE+4*0x9002a,0x480); // DWC_DDRPHYA_INITENG0_SequenceReg0b0s1
    WRITE32(DPHY_ADDR_BASE+4*0x9002b,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b0s2
    WRITE32(DPHY_ADDR_BASE+4*0x9002c,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b1s0
    WRITE32(DPHY_ADDR_BASE+4*0x9002d,0x448); // DWC_DDRPHYA_INITENG0_SequenceReg0b1s1
    WRITE32(DPHY_ADDR_BASE+4*0x9002e,0x139); // DWC_DDRPHYA_INITENG0_SequenceReg0b1s2
    WRITE32(DPHY_ADDR_BASE+4*0x9002f,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b2s0
    WRITE32(DPHY_ADDR_BASE+4*0x90030,0x478); // DWC_DDRPHYA_INITENG0_SequenceReg0b2s1
    WRITE32(DPHY_ADDR_BASE+4*0x90031,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b2s2
    WRITE32(DPHY_ADDR_BASE+4*0x90032,0x2); // DWC_DDRPHYA_INITENG0_SequenceReg0b3s0
    WRITE32(DPHY_ADDR_BASE+4*0x90033,0x10); // DWC_DDRPHYA_INITENG0_SequenceReg0b3s1
    WRITE32(DPHY_ADDR_BASE+4*0x90034,0x139); // DWC_DDRPHYA_INITENG0_SequenceReg0b3s2
    WRITE32(DPHY_ADDR_BASE+4*0x90035,0xb); // DWC_DDRPHYA_INITENG0_SequenceReg0b4s0
    WRITE32(DPHY_ADDR_BASE+4*0x90036,0x7c0); // DWC_DDRPHYA_INITENG0_SequenceReg0b4s1
    WRITE32(DPHY_ADDR_BASE+4*0x90037,0x139); // DWC_DDRPHYA_INITENG0_SequenceReg0b4s2
    WRITE32(DPHY_ADDR_BASE+4*0x90038,0x44); // DWC_DDRPHYA_INITENG0_SequenceReg0b5s0
    WRITE32(DPHY_ADDR_BASE+4*0x90039,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b5s1
    WRITE32(DPHY_ADDR_BASE+4*0x9003a,0x159); // DWC_DDRPHYA_INITENG0_SequenceReg0b5s2
    WRITE32(DPHY_ADDR_BASE+4*0x9003b,0x14f); // DWC_DDRPHYA_INITENG0_SequenceReg0b6s0
    WRITE32(DPHY_ADDR_BASE+4*0x9003c,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b6s1
    WRITE32(DPHY_ADDR_BASE+4*0x9003d,0x159); // DWC_DDRPHYA_INITENG0_SequenceReg0b6s2
    WRITE32(DPHY_ADDR_BASE+4*0x9003e,0x47); // DWC_DDRPHYA_INITENG0_SequenceReg0b7s0
    WRITE32(DPHY_ADDR_BASE+4*0x9003f,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b7s1
    WRITE32(DPHY_ADDR_BASE+4*0x90040,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b7s2
    WRITE32(DPHY_ADDR_BASE+4*0x90041,0x4f); // DWC_DDRPHYA_INITENG0_SequenceReg0b8s0
    WRITE32(DPHY_ADDR_BASE+4*0x90042,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b8s1
    WRITE32(DPHY_ADDR_BASE+4*0x90043,0x179); // DWC_DDRPHYA_INITENG0_SequenceReg0b8s2
    WRITE32(DPHY_ADDR_BASE+4*0x90044,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b9s0
    WRITE32(DPHY_ADDR_BASE+4*0x90045,0xe0); // DWC_DDRPHYA_INITENG0_SequenceReg0b9s1
    WRITE32(DPHY_ADDR_BASE+4*0x90046,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b9s2
    WRITE32(DPHY_ADDR_BASE+4*0x90047,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b10s0
    WRITE32(DPHY_ADDR_BASE+4*0x90048,0x7c8); // DWC_DDRPHYA_INITENG0_SequenceReg0b10s1
    WRITE32(DPHY_ADDR_BASE+4*0x90049,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b10s2
    WRITE32(DPHY_ADDR_BASE+4*0x9004a,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b11s0
    WRITE32(DPHY_ADDR_BASE+4*0x9004b,0x1); // DWC_DDRPHYA_INITENG0_SequenceReg0b11s1
    WRITE32(DPHY_ADDR_BASE+4*0x9004c,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b11s2
    WRITE32(DPHY_ADDR_BASE+4*0x9004d,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b12s0
    WRITE32(DPHY_ADDR_BASE+4*0x9004e,0x45a); // DWC_DDRPHYA_INITENG0_SequenceReg0b12s1
    WRITE32(DPHY_ADDR_BASE+4*0x9004f,0x9); // DWC_DDRPHYA_INITENG0_SequenceReg0b12s2
    WRITE32(DPHY_ADDR_BASE+4*0x90050,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b13s0
    WRITE32(DPHY_ADDR_BASE+4*0x90051,0x448); // DWC_DDRPHYA_INITENG0_SequenceReg0b13s1
    WRITE32(DPHY_ADDR_BASE+4*0x90052,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b13s2
    WRITE32(DPHY_ADDR_BASE+4*0x90053,0x40); // DWC_DDRPHYA_INITENG0_SequenceReg0b14s0
    WRITE32(DPHY_ADDR_BASE+4*0x90054,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b14s1
    WRITE32(DPHY_ADDR_BASE+4*0x90055,0x179); // DWC_DDRPHYA_INITENG0_SequenceReg0b14s2
    WRITE32(DPHY_ADDR_BASE+4*0x90056,0x1); // DWC_DDRPHYA_INITENG0_SequenceReg0b15s0
    WRITE32(DPHY_ADDR_BASE+4*0x90057,0x618); // DWC_DDRPHYA_INITENG0_SequenceReg0b15s1
    WRITE32(DPHY_ADDR_BASE+4*0x90058,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b15s2
    WRITE32(DPHY_ADDR_BASE+4*0x90059,0x40c0); // DWC_DDRPHYA_INITENG0_SequenceReg0b16s0
    WRITE32(DPHY_ADDR_BASE+4*0x9005a,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b16s1
    WRITE32(DPHY_ADDR_BASE+4*0x9005b,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b16s2
    WRITE32(DPHY_ADDR_BASE+4*0x9005c,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b17s0
    WRITE32(DPHY_ADDR_BASE+4*0x9005d,0x4); // DWC_DDRPHYA_INITENG0_SequenceReg0b17s1
    WRITE32(DPHY_ADDR_BASE+4*0x9005e,0x48); // DWC_DDRPHYA_INITENG0_SequenceReg0b17s2
    WRITE32(DPHY_ADDR_BASE+4*0x9005f,0x4040); // DWC_DDRPHYA_INITENG0_SequenceReg0b18s0
    WRITE32(DPHY_ADDR_BASE+4*0x90060,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b18s1
    WRITE32(DPHY_ADDR_BASE+4*0x90061,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b18s2
    WRITE32(DPHY_ADDR_BASE+4*0x90062,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b19s0
    WRITE32(DPHY_ADDR_BASE+4*0x90063,0x4); // DWC_DDRPHYA_INITENG0_SequenceReg0b19s1
    WRITE32(DPHY_ADDR_BASE+4*0x90064,0x48); // DWC_DDRPHYA_INITENG0_SequenceReg0b19s2
    WRITE32(DPHY_ADDR_BASE+4*0x90065,0x40); // DWC_DDRPHYA_INITENG0_SequenceReg0b20s0
    WRITE32(DPHY_ADDR_BASE+4*0x90066,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b20s1
    WRITE32(DPHY_ADDR_BASE+4*0x90067,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b20s2
    WRITE32(DPHY_ADDR_BASE+4*0x90068,0x10); // DWC_DDRPHYA_INITENG0_SequenceReg0b21s0
    WRITE32(DPHY_ADDR_BASE+4*0x90069,0x4); // DWC_DDRPHYA_INITENG0_SequenceReg0b21s1
    WRITE32(DPHY_ADDR_BASE+4*0x9006a,0x18); // DWC_DDRPHYA_INITENG0_SequenceReg0b21s2
    WRITE32(DPHY_ADDR_BASE+4*0x9006b,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b22s0
    WRITE32(DPHY_ADDR_BASE+4*0x9006c,0x4); // DWC_DDRPHYA_INITENG0_SequenceReg0b22s1
    WRITE32(DPHY_ADDR_BASE+4*0x9006d,0x78); // DWC_DDRPHYA_INITENG0_SequenceReg0b22s2
    WRITE32(DPHY_ADDR_BASE+4*0x9006e,0x549); // DWC_DDRPHYA_INITENG0_SequenceReg0b23s0
    WRITE32(DPHY_ADDR_BASE+4*0x9006f,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b23s1
    WRITE32(DPHY_ADDR_BASE+4*0x90070,0x159); // DWC_DDRPHYA_INITENG0_SequenceReg0b23s2
    WRITE32(DPHY_ADDR_BASE+4*0x90071,0xd49); // DWC_DDRPHYA_INITENG0_SequenceReg0b24s0
    WRITE32(DPHY_ADDR_BASE+4*0x90072,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b24s1
    WRITE32(DPHY_ADDR_BASE+4*0x90073,0x159); // DWC_DDRPHYA_INITENG0_SequenceReg0b24s2
    WRITE32(DPHY_ADDR_BASE+4*0x90074,0x94a); // DWC_DDRPHYA_INITENG0_SequenceReg0b25s0
    WRITE32(DPHY_ADDR_BASE+4*0x90075,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b25s1
    WRITE32(DPHY_ADDR_BASE+4*0x90076,0x159); // DWC_DDRPHYA_INITENG0_SequenceReg0b25s2
    WRITE32(DPHY_ADDR_BASE+4*0x90077,0x441); // DWC_DDRPHYA_INITENG0_SequenceReg0b26s0
    WRITE32(DPHY_ADDR_BASE+4*0x90078,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b26s1
    WRITE32(DPHY_ADDR_BASE+4*0x90079,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b26s2
    WRITE32(DPHY_ADDR_BASE+4*0x9007a,0x42); // DWC_DDRPHYA_INITENG0_SequenceReg0b27s0
    WRITE32(DPHY_ADDR_BASE+4*0x9007b,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b27s1
    WRITE32(DPHY_ADDR_BASE+4*0x9007c,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b27s2
    WRITE32(DPHY_ADDR_BASE+4*0x9007d,0x1); // DWC_DDRPHYA_INITENG0_SequenceReg0b28s0
    WRITE32(DPHY_ADDR_BASE+4*0x9007e,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b28s1
    WRITE32(DPHY_ADDR_BASE+4*0x9007f,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b28s2
    WRITE32(DPHY_ADDR_BASE+4*0x90080,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b29s0
    WRITE32(DPHY_ADDR_BASE+4*0x90081,0xe0); // DWC_DDRPHYA_INITENG0_SequenceReg0b29s1
    WRITE32(DPHY_ADDR_BASE+4*0x90082,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b29s2
    WRITE32(DPHY_ADDR_BASE+4*0x90083,0xa); // DWC_DDRPHYA_INITENG0_SequenceReg0b30s0
    WRITE32(DPHY_ADDR_BASE+4*0x90084,0x10); // DWC_DDRPHYA_INITENG0_SequenceReg0b30s1
    WRITE32(DPHY_ADDR_BASE+4*0x90085,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b30s2
    WRITE32(DPHY_ADDR_BASE+4*0x90086,0x9); // DWC_DDRPHYA_INITENG0_SequenceReg0b31s0
    WRITE32(DPHY_ADDR_BASE+4*0x90087,0x3c0); // DWC_DDRPHYA_INITENG0_SequenceReg0b31s1
    WRITE32(DPHY_ADDR_BASE+4*0x90088,0x149); // DWC_DDRPHYA_INITENG0_SequenceReg0b31s2
    WRITE32(DPHY_ADDR_BASE+4*0x90089,0x9); // DWC_DDRPHYA_INITENG0_SequenceReg0b32s0
    WRITE32(DPHY_ADDR_BASE+4*0x9008a,0x3c0); // DWC_DDRPHYA_INITENG0_SequenceReg0b32s1
    WRITE32(DPHY_ADDR_BASE+4*0x9008b,0x159); // DWC_DDRPHYA_INITENG0_SequenceReg0b32s2
    WRITE32(DPHY_ADDR_BASE+4*0x9008c,0x18); // DWC_DDRPHYA_INITENG0_SequenceReg0b33s0
    WRITE32(DPHY_ADDR_BASE+4*0x9008d,0x10); // DWC_DDRPHYA_INITENG0_SequenceReg0b33s1
    WRITE32(DPHY_ADDR_BASE+4*0x9008e,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b33s2
    WRITE32(DPHY_ADDR_BASE+4*0x9008f,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b34s0
    WRITE32(DPHY_ADDR_BASE+4*0x90090,0x3c0); // DWC_DDRPHYA_INITENG0_SequenceReg0b34s1
    WRITE32(DPHY_ADDR_BASE+4*0x90091,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b34s2
    WRITE32(DPHY_ADDR_BASE+4*0x90092,0x18); // DWC_DDRPHYA_INITENG0_SequenceReg0b35s0
    WRITE32(DPHY_ADDR_BASE+4*0x90093,0x4); // DWC_DDRPHYA_INITENG0_SequenceReg0b35s1
    WRITE32(DPHY_ADDR_BASE+4*0x90094,0x48); // DWC_DDRPHYA_INITENG0_SequenceReg0b35s2
    WRITE32(DPHY_ADDR_BASE+4*0x90095,0x18); // DWC_DDRPHYA_INITENG0_SequenceReg0b36s0
    WRITE32(DPHY_ADDR_BASE+4*0x90096,0x4); // DWC_DDRPHYA_INITENG0_SequenceReg0b36s1
    WRITE32(DPHY_ADDR_BASE+4*0x90097,0x58); // DWC_DDRPHYA_INITENG0_SequenceReg0b36s2
    WRITE32(DPHY_ADDR_BASE+4*0x90098,0xa); // DWC_DDRPHYA_INITENG0_SequenceReg0b37s0
    WRITE32(DPHY_ADDR_BASE+4*0x90099,0x10); // DWC_DDRPHYA_INITENG0_SequenceReg0b37s1
    WRITE32(DPHY_ADDR_BASE+4*0x9009a,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b37s2
    WRITE32(DPHY_ADDR_BASE+4*0x9009b,0x2); // DWC_DDRPHYA_INITENG0_SequenceReg0b38s0
    WRITE32(DPHY_ADDR_BASE+4*0x9009c,0x10); // DWC_DDRPHYA_INITENG0_SequenceReg0b38s1
    WRITE32(DPHY_ADDR_BASE+4*0x9009d,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b38s2
    WRITE32(DPHY_ADDR_BASE+4*0x9009e,0x5); // DWC_DDRPHYA_INITENG0_SequenceReg0b39s0
    WRITE32(DPHY_ADDR_BASE+4*0x9009f,0x7c0); // DWC_DDRPHYA_INITENG0_SequenceReg0b39s1
    WRITE32(DPHY_ADDR_BASE+4*0x900a0,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b39s2
    WRITE32(DPHY_ADDR_BASE+4*0x900a1,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b40s0
    WRITE32(DPHY_ADDR_BASE+4*0x900a2,0x8140); // DWC_DDRPHYA_INITENG0_SequenceReg0b40s1
    WRITE32(DPHY_ADDR_BASE+4*0x900a3,0x10c); // DWC_DDRPHYA_INITENG0_SequenceReg0b40s2
    WRITE32(DPHY_ADDR_BASE+4*0x900a4,0x10); // DWC_DDRPHYA_INITENG0_SequenceReg0b41s0
    WRITE32(DPHY_ADDR_BASE+4*0x900a5,0x8138); // DWC_DDRPHYA_INITENG0_SequenceReg0b41s1
    WRITE32(DPHY_ADDR_BASE+4*0x900a6,0x10c); // DWC_DDRPHYA_INITENG0_SequenceReg0b41s2
    WRITE32(DPHY_ADDR_BASE+4*0x900a7,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b42s0
    WRITE32(DPHY_ADDR_BASE+4*0x900a8,0x7c8); // DWC_DDRPHYA_INITENG0_SequenceReg0b42s1
    WRITE32(DPHY_ADDR_BASE+4*0x900a9,0x101); // DWC_DDRPHYA_INITENG0_SequenceReg0b42s2
    WRITE32(DPHY_ADDR_BASE+4*0x900aa,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b43s0
    WRITE32(DPHY_ADDR_BASE+4*0x900ab,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b43s1
    WRITE32(DPHY_ADDR_BASE+4*0x900ac,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b43s2
    WRITE32(DPHY_ADDR_BASE+4*0x900ad,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b44s0
    WRITE32(DPHY_ADDR_BASE+4*0x900ae,0x448); // DWC_DDRPHYA_INITENG0_SequenceReg0b44s1
    WRITE32(DPHY_ADDR_BASE+4*0x900af,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b44s2
    WRITE32(DPHY_ADDR_BASE+4*0x900b0,0xf); // DWC_DDRPHYA_INITENG0_SequenceReg0b45s0
    WRITE32(DPHY_ADDR_BASE+4*0x900b1,0x7c0); // DWC_DDRPHYA_INITENG0_SequenceReg0b45s1
    WRITE32(DPHY_ADDR_BASE+4*0x900b2,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b45s2
    WRITE32(DPHY_ADDR_BASE+4*0x900b3,0x47); // DWC_DDRPHYA_INITENG0_SequenceReg0b46s0
    WRITE32(DPHY_ADDR_BASE+4*0x900b4,0x630); // DWC_DDRPHYA_INITENG0_SequenceReg0b46s1
    WRITE32(DPHY_ADDR_BASE+4*0x900b5,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b46s2
    WRITE32(DPHY_ADDR_BASE+4*0x900b6,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b47s0
    WRITE32(DPHY_ADDR_BASE+4*0x900b7,0x618); // DWC_DDRPHYA_INITENG0_SequenceReg0b47s1
    WRITE32(DPHY_ADDR_BASE+4*0x900b8,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b47s2
    WRITE32(DPHY_ADDR_BASE+4*0x900b9,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b48s0
    WRITE32(DPHY_ADDR_BASE+4*0x900ba,0xe0); // DWC_DDRPHYA_INITENG0_SequenceReg0b48s1
    WRITE32(DPHY_ADDR_BASE+4*0x900bb,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b48s2
    WRITE32(DPHY_ADDR_BASE+4*0x900bc,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b49s0
    WRITE32(DPHY_ADDR_BASE+4*0x900bd,0x7c8); // DWC_DDRPHYA_INITENG0_SequenceReg0b49s1
    WRITE32(DPHY_ADDR_BASE+4*0x900be,0x109); // DWC_DDRPHYA_INITENG0_SequenceReg0b49s2
    WRITE32(DPHY_ADDR_BASE+4*0x900bf,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b50s0
    WRITE32(DPHY_ADDR_BASE+4*0x900c0,0x8140); // DWC_DDRPHYA_INITENG0_SequenceReg0b50s1
    WRITE32(DPHY_ADDR_BASE+4*0x900c1,0x10c); // DWC_DDRPHYA_INITENG0_SequenceReg0b50s2
    WRITE32(DPHY_ADDR_BASE+4*0x900c2,0x0); // DWC_DDRPHYA_INITENG0_SequenceReg0b51s0
    WRITE32(DPHY_ADDR_BASE+4*0x900c3,0x1); // DWC_DDRPHYA_INITENG0_SequenceReg0b51s1
    WRITE32(DPHY_ADDR_BASE+4*0x900c4,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b51s2
    WRITE32(DPHY_ADDR_BASE+4*0x900c5,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b52s0
    WRITE32(DPHY_ADDR_BASE+4*0x900c6,0x4); // DWC_DDRPHYA_INITENG0_SequenceReg0b52s1
    WRITE32(DPHY_ADDR_BASE+4*0x900c7,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b52s2
    WRITE32(DPHY_ADDR_BASE+4*0x900c8,0x8); // DWC_DDRPHYA_INITENG0_SequenceReg0b53s0
    WRITE32(DPHY_ADDR_BASE+4*0x900c9,0x7c8); // DWC_DDRPHYA_INITENG0_SequenceReg0b53s1
    WRITE32(DPHY_ADDR_BASE+4*0x900ca,0x101); // DWC_DDRPHYA_INITENG0_SequenceReg0b53s2
    WRITE32(DPHY_ADDR_BASE+4*0x90006,0x0); // DWC_DDRPHYA_INITENG0_PostSequenceReg0b0s0
    WRITE32(DPHY_ADDR_BASE+4*0x90007,0x0); // DWC_DDRPHYA_INITENG0_PostSequenceReg0b0s1
    WRITE32(DPHY_ADDR_BASE+4*0x90008,0x8); // DWC_DDRPHYA_INITENG0_PostSequenceReg0b0s2
    WRITE32(DPHY_ADDR_BASE+4*0x90009,0x0); // DWC_DDRPHYA_INITENG0_PostSequenceReg0b1s0
    WRITE32(DPHY_ADDR_BASE+4*0x9000a,0x0); // DWC_DDRPHYA_INITENG0_PostSequenceReg0b1s1
    WRITE32(DPHY_ADDR_BASE+4*0x9000b,0x0); // DWC_DDRPHYA_INITENG0_PostSequenceReg0b1s2
    WRITE32(DPHY_ADDR_BASE+4*0xd00e7,0x400); // DWC_DDRPHYA_APBONLY0_SequencerOverride
    WRITE32(DPHY_ADDR_BASE+4*0x90017,0x0); // DWC_DDRPHYA_INITENG0_StartVector0b0
    WRITE32(DPHY_ADDR_BASE+4*0x90026,0x2b); // DWC_DDRPHYA_INITENG0_StartVector0b15
    // // [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1067MHz, Programming Seq0BDLY0 to 0x42
    WRITE32(DPHY_ADDR_BASE+4*0x2000b,0x42); // DWC_DDRPHYA_MASTER0_Seq0BDLY0_p0
    // // [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1067MHz, Programming Seq0BDLY1 to 0x85
    WRITE32(DPHY_ADDR_BASE+4*0x2000c,0x85); // DWC_DDRPHYA_MASTER0_Seq0BDLY1_p0
    // // [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1067MHz, Programming Seq0BDLY2 to 0x535
    WRITE32(DPHY_ADDR_BASE+4*0x2000d,0x535); // DWC_DDRPHYA_MASTER0_Seq0BDLY2_p0
    // // [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1067MHz, Programming Seq0BDLY3 to 0x2c
    WRITE32(DPHY_ADDR_BASE+4*0x2000e,0x2c); // DWC_DDRPHYA_MASTER0_Seq0BDLY3_p0
    WRITE32(DPHY_ADDR_BASE+4*0x9000c,0x0); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag0
    WRITE32(DPHY_ADDR_BASE+4*0x9000d,0x173); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag1
    WRITE32(DPHY_ADDR_BASE+4*0x9000e,0x60); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag2
    WRITE32(DPHY_ADDR_BASE+4*0x9000f,0x6110); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag3
    WRITE32(DPHY_ADDR_BASE+4*0x90010,0x2152); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag4
    WRITE32(DPHY_ADDR_BASE+4*0x90011,0xdfbd); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag5
    WRITE32(DPHY_ADDR_BASE+4*0x90012,0xffff); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag6
    WRITE32(DPHY_ADDR_BASE+4*0x90013,0x6152); // DWC_DDRPHYA_INITENG0_Seq0BDisableFlag7
    // // [phyinit_I_loadPIEImage] Turn on calibration and hold idle until dfi_init_start is asserted sequence is triggered.
    WRITE32(DPHY_ADDR_BASE+4*0x20089,0x1); // DWC_DDRPHYA_MASTER0_CalZap
    // // [phyinit_I_loadPIEImage] Programming CalRate::CalInterval to 0x9
    // // [phyinit_I_loadPIEImage] Programming CalRate::CalOnce to 0x0
    // // [phyinit_I_loadPIEImage] Programming CalRate::CalRun to 0x1
    WRITE32(DPHY_ADDR_BASE+4*0x20088,0x19); // DWC_DDRPHYA_MASTER0_CalRate
    // // [phyinit_I_loadPIEImage] Disabling Ucclk (PMU) and Hclk (training hardware)
    WRITE32(DPHY_ADDR_BASE+4*0xc0080,0x0); // DWC_DDRPHYA_DRTUB0_UcclkHclkEnables
    // // [phyinit_I_loadPIEImage] Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. 
    WRITE32(DPHY_ADDR_BASE+4*0xd0000,0x1); // DWC_DDRPHYA_APBONLY0_MicroContMuxSel
    // // [phyinit_I_loadPIEImage] End of dwc_ddrphy_phyinit_I_loadPIEImage()
    // 
    // 
    // //##############################################################
    // //
    // // dwc_ddrphy_phyinit_userCustom_customPostTrain is a user-editable function.
    // //
    // // See PhyInit App Note for detailed description and function usage
    // 
    // //##############################################################
    // 
    //dwc_ddrphy_phyinit_userCustom_customPostTrain ();

    // // [dwc_ddrphy_phyinit_userCustom_customPostTrain] End of dwc_ddrphy_phyinit_userCustom_customPostTrain()
    // // [dwc_ddrphy_phyinit_userCustom_J_enterMissionMode] Start of dwc_ddrphy_phyinit_userCustom_J_enterMissionMode()
    // 
    // 
    // //##############################################################
    // //
    // // (J) Initialize the PHY to Mission Mode through DFI Initialization 
    // //
    // // Initialize the PHY to mission mode as follows: 
    // //
    // // 1. Set the PHY input clocks to the desired frequency. 
    // // 2. Initialize the PHY to mission mode by performing DFI Initialization. 
    // //    Please see the DFI specification for more information. See the DFI frequency bus encoding in section <XXX>.
    // // Note: The PHY training firmware initializes the DRAM state. if skip 
    // // training is used, the DRAM state is not initialized. 
    // //
    // //##############################################################
    // 
    //dwc_ddrphy_phyinit_userCustom_J_enterMissionMode ();

    // 
    // // [dwc_ddrphy_phyinit_userCustom_J_enterMissionMode] End of dwc_ddrphy_phyinit_userCustom_J_enterMissionMode()
    // [dwc_ddrphy_phyinit_sequence] End of dwc_ddrphy_phyinit_sequence()
    // [dwc_ddrphy_phyinit_main] End of dwc_ddrphy_phyinit_main()
}

int do_ddr_training(int DPHY_ADDR_BASE, int chs)
{
    unsigned int main_info = 0;
    unsigned int read_data_16 = 0;
    unsigned int i = 0;
    int ret = 0;

    DEBUG_MSG("DDR training Start !!!!");
    for (i = 0; i < chs; i++)
    {
        WRITE32(0x40080420, i); // dram_sel
        WRITE32(0x40080424, (1 << i));  
        while((main_info != 0x7) && (main_info != 0xff))
        {
            /*Wait UctShadowRegs.UctWriteProtShadow from 1 to 0*/
            do
            {
                read_data_16 = READ16(DPHY_ADDR_BASE + 0x000d0004 * 4);
            } while ((read_data_16 & 0x00000001) != 0x00000000);

            /* Read out Message ID */
            main_info = READ16(DPHY_ADDR_BASE + 0x000d0032 * 4);
            if (main_info == 0x00) {
                DEBUG_MSG("End of Initialization !!!! \r\n");
            } else if (main_info == 0x01) {
                DEBUG_MSG("End of Fine Write leveling !!!! \r\n");
            } else if (main_info == 0x02) {
                DEBUG_MSG("End of read enable training !!!! \r\n");
            } else if (main_info == 0x03) {
                DEBUG_MSG("End of read delay center optimization !!!! \r\n");
            } else if (main_info == 0x04) {
                DEBUG_MSG("End of write delay center optimization !!!! \r\n");
            } else if (main_info == 0x08) {
                DEBUG_MSG("Dump stream Msg!!!! \r\n");
                dump_stream_msg(DPHY_ADDR_BASE);
            } else if (main_info == 0x09) {
                DEBUG_MSG("End of max read latency training !!!! \r\n");
            } else if (main_info == 0x0a) {
                DEBUG_MSG("End of read dq deskew training !!!! \r\n");
            } else if (main_info == 0xfe) {
                DEBUG_MSG("End of write leveling coarse delay !!!! \r\n");
            } else {
                DEBUG_MSG("No use stage !!!! \r\n");
            }
            
            /* Set DctWriteProt=0,user acknowledges the receipt of the message */
            WRITE16(DPHY_ADDR_BASE + 0x000d0031 * 4, 0x0);

            /* Wait UctShadowRegs.UctWriteProtShadow from 0 to 1 */
            do
            {
                read_data_16 = READ16(DPHY_ADDR_BASE + 0x000d0004 * 4);
            } while ((read_data_16 & 0x00000001) != 0x00000001);
            
            /* Set DctWriteProt=1 back */
            WRITE16(DPHY_ADDR_BASE + 0x000d0031 * 4, 0x1);
        }
    }
    
    if (main_info == 0x7)
    {
        DEBUG_MSG("DDR training PASS !!!! \r\n");
    }
    else
    {   
        DEBUG_MSG("DDR training FAIL !!!! \r\n");
        ret += 1;
    }

    return ret;
}


unsigned int get_mail(int DPHY_ADDR_BASE)
{
    unsigned int mail;
    unsigned int wrte_only_shadow;
    unsigned int write_dat_shadow;

    wrte_only_shadow = READ16(DPHY_ADDR_BASE + 0x000d0032 * 4);
    write_dat_shadow = READ16(DPHY_ADDR_BASE + 0x000d0034 * 4);
    mail = (write_dat_shadow << 16) | wrte_only_shadow;

    return mail;
}

void dump_stream_msg(int DPHY_ADDR_BASE)
{
    unsigned int num = 0;
    unsigned int i = 0;
    unsigned int mail = 0;
    
    DEBUG_MSG("Start read string index \r\n");
    mail = get_mail(DPHY_ADDR_BASE);
    DEBUG_MSG("End read string index \r\n");

    switch (mail)
    {
        case 0x00040000: DEBUG_MSG("PMU: Error: User requested MPR read pattern for read DQS training in DDR3 Mode\r\n");break;
        case 0x00110001: DEBUG_MSG("PMU: Error: CS  failed to find a DFIMRL setting that worked for all bytes during MaxRdLat training\r\n");break;
        case 0x00120002: DEBUG_MSG("PMU3: Smallest passing DFIMRL for all dbytes in CS  =   DFIClks\r\n");break;
        case 0x00130000: DEBUG_MSG("PMU: Error: No passing DFIMRL value found for any chip select during MaxRdLat training\r\n");break;
        case 0x00140003: DEBUG_MSG("PMU: Error: Dbyte   lane   txDqDly passing region is too small (width =  )\r\n");break;
        case 0x00150000: DEBUG_MSG("PMU4: TxDqDly Passing Regions (EyeLeft EyeRight -> EyeCenter) Units=1/32 UI\r\n");break;
        case 0x00160005: DEBUG_MSG("PMU4: DB   Lane  :     ->  \r\n");break;
        case 0x00170002: DEBUG_MSG("PMU2: TXDQ delayLeft[ ] =   (DISCONNECTED)\r\n");break;
        case 0x00180004: DEBUG_MSG("PMU2: TXDQ delayLeft[ ] =   oopScaled =   selectOop  \r\n");break;
        case 0x00190002: DEBUG_MSG("PMU2: TXDQ delayRight[ ] =   (DISCONNECTED)\r\n");break;
        case 0x001a0004: DEBUG_MSG("PMU2: TXDQ delayRight[ ] =   oopScaled =   selectOop  \r\n");break;
        case 0x001b0003: DEBUG_MSG("PMU: Error: Dbyte   lane   txDqDly passing region is too small (width =  )\r\n");break;
        case 0x001c0000: DEBUG_MSG("PMU4: TxDqDly Passing Regions (EyeLeft EyeRight -> EyeCenter) Units=1/32 UI\r\n");break;
        case 0x001d0002: DEBUG_MSG("PMU4: DB   Lane  : (DISCONNECTED)\r\n");break;
        case 0x001e0005: DEBUG_MSG("PMU4: DB   Lane  :     ->  \r\n");break;
        case 0x001f0002: DEBUG_MSG("PMU3: Running 1D search csn   for DM Right/NotLeft( ) eye edge\r\n");break;
        case 0x00200002: DEBUG_MSG("PMU3: WrDq DM byte  with Errcnt  \r\n");break;
        case 0x00210002: DEBUG_MSG("PMU3: WrDq DM byte  avgDly case 0x \r\n");break;
        case 0x00220002: DEBUG_MSG("PMU1: WrDq DM byte  with Errcnt  \r\n");break;
        case 0x00230001: DEBUG_MSG("PMU: Error: Dbyte   txDqDly DM training did not start inside the eye\r\n");break;
        case 0x00240000: DEBUG_MSG("PMU4: DM TxDqDly Passing Regions (EyeLeft EyeRight -> EyeCenter) Units=1/32 UI\r\n");break;
        case 0x00250002: DEBUG_MSG("PMU4: DB   Lane  : (DISCONNECTED)\r\n");break;
        case 0x00260005: DEBUG_MSG("PMU4: DB   Lane  :     ->  \r\n");break;
        case 0x00270003: DEBUG_MSG("PMU: Error: Dbyte   lane   txDqDly DM passing region is too small (width =  )\r\n");break;
        case 0x00280004: DEBUG_MSG("PMU3: Errcnt for MRD/MWD search nib   delay = ( , case 0x ) =  \r\n");break;
        case 0x00290000: DEBUG_MSG("PMU3: Precharge all open banks\r\n");break;
        case 0x002a0002: DEBUG_MSG("PMU: Error: Dbyte   nibble   found mutliple working coarse delay setting for MRD/MWD\r\n");break;
        case 0x002b0000: DEBUG_MSG("PMU4: MRD Passing Regions (coarseVal, fineLeft fineRight -> fineCenter)\r\n");break;
        case 0x002c0000: DEBUG_MSG("PMU4: MRW Passing Regions (coarseVal, fineLeft fineRight -> fineCenter)\r\n");break;
        case 0x002d0004: DEBUG_MSG("PMU10: Warning: DB   nibble   has multiple working coarse delays,   and  , choosing the smaller delay\r\n");break;
        case 0x002e0003: DEBUG_MSG("PMU: Error: Dbyte   nibble   MRD/MWD passing region is too small (width =  )\r\n");break;
        case 0x00430003: DEBUG_MSG("PMU3: db  l  first saw a DBI pass->fail edge at rxClkDly  \r\n");break;
        case 0x00440003: DEBUG_MSG("PMU2: db  l  already passed rxPBD =  \r\n");break;
        case 0x00450003: DEBUG_MSG("PMU0: db  l , PBD =  \r\n");break;
        case 0x00460002: DEBUG_MSG("PMU: Error: dbyte   lane   failed read deskew\r\n");break;
        case 0x00470003: DEBUG_MSG("PMU1: Running lane deskew on pstate   csn   rdDBIEn  \r\n");break;
        case 0x00480000: DEBUG_MSG("PMU: Error: Read deskew training has been requested, but csrMajorModeDbyte[2] is set\r\n");break;
        case 0x00490002: DEBUG_MSG("PMU1: AcsmCsMapCtrl  case 0x \r\n");break;
        case 0x004a0002: DEBUG_MSG("PMU1: AcsmCsMapCtrl  case 0x \r\n");break;
        case 0x004b0001: DEBUG_MSG("PMU: Error: Wrong PMU image loaded. message Block DramType = case 0x , but image built for D3U Type\r\n");break;
        case 0x004c0001: DEBUG_MSG("PMU: Error: Wrong PMU image loaded. message Block DramType = case 0x , but image built for D3R Type\r\n");break;
        case 0x004d0001: DEBUG_MSG("PMU: Error: Wrong PMU image loaded. message Block DramType = case 0x , but image built for D4U Type\r\n");break;
        case 0x004e0001: DEBUG_MSG("PMU: Error: Wrong PMU image loaded. message Block DramType = case 0x , but image built for D4R Type\r\n");break;
        case 0x004f0001: DEBUG_MSG("PMU: Error: Wrong PMU image loaded. message Block DramType = case 0x , but image built for D4LR Type\r\n");break;
        case 0x00500000: DEBUG_MSG("PMU: Error: Both 2t timing mode and ddr4 geardown mode specifed in the messageblock's PhyCfg and MR3 fields. Only one can be enabled\r\n");break;
        case 0x006a0009: DEBUG_MSG("PMU3: dtsm fails Odd  Nibbles:                  \r\n");break;
        case 0x006b0002: DEBUG_MSG("PMU3: Preamble search pass=  anyfail= \r\n");break;
        case 0x006c0000: DEBUG_MSG("PMU: Error: RxEn training preamble not found\r\n");break;
        case 0x006d0000: DEBUG_MSG("PMU3: Found DQS pre-amble\r\n");break;
        case 0x006e0001: DEBUG_MSG("PMU: Error: Dbyte   couldn't find the rising edge of DQS during RxEn Training\r\n");break;
        case 0x006f0000: DEBUG_MSG("PMU3: RxEn aligning to first rising edge of burst\r\n");break;
        case 0x00a50002: DEBUG_MSG("PMU3: Setting ATxDly for anib   to  \r\n");break;
        case 0x00a60000: DEBUG_MSG("PMU: Error: CA Training Failed.\r\n");break;
        case 0x00a70000: DEBUG_MSG("PMU1: Writing MRs\r\n");break;
        case 0x00b50001: DEBUG_MSG("PMU10: **** Start LPDDR4 Training. PMU Firmware Revision case 0x  ****\r\n");break;
        case 0x00b60000: DEBUG_MSG("PMU: Error: Mismatched internal revision between DCCM and ICCM images\r\n");break;
        case 0x00b70001: DEBUG_MSG("PMU10: **** Testchip   Specific Firmware ****\r\n");break;
        case 0x00d50000: DEBUG_MSG("PMU2: Starting 2d WrDq training for all ranks\r\n");break;
        case 0x00d60002: DEBUG_MSG("PMU3:read_fifo    \r\n");break;
        case 0x00d70001: DEBUG_MSG("PMU: Error: Invalid PhyDrvImpedance of case 0x  specified in message block.\r\n");break;
        case 0x00d80001: DEBUG_MSG("PMU: Error: Invalid PhyOdtImpedance of case 0x  specified in message block.\r\n");break;
        case 0x00d90001: DEBUG_MSG("PMU: Error: Invalid BPZNResVal of case 0x  specified in message block.\r\n");break;
        case 0x00da0005: DEBUG_MSG("PMU3: fixRxEnBackOff csn:  db:  dn:  bo:  dly: \r\n");break;
        case 0x00db0001: DEBUG_MSG("PMU3: fixRxEnBackOff dly: \r\n");break;
        case 0x00dc0000: DEBUG_MSG("PMU3: Entering setupPpt\r\n");break;
        case 0x00dd0000: DEBUG_MSG("PMU3: Start lp4PopulateHighLowBytes\r\n");break;
        case 0x00de0002: DEBUG_MSG("PMU3:Dbyte Detect: db  received  \r\n");break;
        case 0x00df0002: DEBUG_MSG("PMU3:getDqs2Dq read   from dbyte  \r\n");break;
        case 0x00e00002: DEBUG_MSG("PMU3:getDqs2Dq(2) read   from dbyte  \r\n");break;
        case 0x00e10001: DEBUG_MSG("PMU: Error: Dbyte   read 0 from the DQS oscillator it is connected to\r\n");break;
        case 0x00e20002: DEBUG_MSG("PMU4: Dbyte   dqs2dq =  /32 UI\r\n");break;
        case 0x00e30003: DEBUG_MSG("PMU3:getDqs2Dq set dqs2dq: /32 ui (  ps) from dbyte  \r\n");break;
        case 0x00e40003: DEBUG_MSG("PMU3: Setting coarse delay in AtxDly chiplet   from case 0x  to case 0x  \r\n");break;
        case 0x00e50003: DEBUG_MSG("PMU3: Clearing coarse delay in AtxDly chiplet   from case 0x  to case 0x  \r\n");break;
        case 0x00e60000: DEBUG_MSG("PMU3: Performing DDR4 geardown sync sequence\r\n");break;
        case 0x00e70000: DEBUG_MSG("PMU1: Enter self refresh\r\n");break;
        case 0x00e80000: DEBUG_MSG("PMU1: Exit self refresh\r\n");break;
        case 0x00e90000: DEBUG_MSG("PMU: Error: No dbiEnable with lp4\r\n");break;
        case 0x00ea0000: DEBUG_MSG("PMU: Error: No dbiDisable with lp4\r\n");break;
        case 0x01340002: DEBUG_MSG("PMU0: VrefDAC0/1 vddqStart   dacToVddq  \r\n");break;
        case 0x01350001: DEBUG_MSG("PMU: Error: Messageblock phyVref=case 0x  is above the limit for TSMC28's attenuated LPDDR4 receivers. Please see the pub databook\r\n");break;
        case 0x01360001: DEBUG_MSG("PMU: Error: Messageblock phyVref=case 0x  is above the limit for TSMC28's attenuated DDR4 receivers. Please see the pub databook\r\n");break;
        case 0x01460002: DEBUG_MSG("PMU4: Coarse write leveling iteration   saw   data miscompares across the entire phy\r\n");break;
        case 0x01470000: DEBUG_MSG("PMU: Error: Failed write leveling coarse\r\n");break;
        case 0x01500002: DEBUG_MSG("PMU4: Coarse write leveling iteration   saw   data miscompares across the entire phy\r\n");break;
        case 0x01510000: DEBUG_MSG("PMU: Error: Failed write leveling coarse\r\n");break;
        case 0x01520003: DEBUG_MSG("PMU3: In write_level_coarse() csn=  dimm=  pstate= \r\n");break;
        case 0x01550002: DEBUG_MSG("PMU4: Coarse write leveling iteration   saw   data miscompares across the entire phy\r\n");break;
        case 0x01560000: DEBUG_MSG("PMU: Error: Failed write leveling coarse\r\n");break;
        case 0x01570001: DEBUG_MSG("PMU3: DWL delay =  \r\n");break;
        case 0x015b0000: DEBUG_MSG("PMU2: DWL did nto find a rising edge of memclk for all nibbles. Failing nibbles assumed to have rising edge at fine delay 63\r\n");break;
        case 0x04000000: DEBUG_MSG("PMU: Error:Mailbox Buffer Overflowed.\r\n");break;
        case 0x04010000: DEBUG_MSG("PMU: Error:Mailbox Buffer Overflowed.\r\n");break;
        case 0x04070001: DEBUG_MSG("PMU: Error: acsm_set_cmd to non existant instruction adddress  \r\n");break;
        case 0x04080001: DEBUG_MSG("PMU: Error: acsm_set_cmd with unknown ddr cmd case 0x \r\n");break;
        case 0x040a0000: DEBUG_MSG("PMU: Error: Polling on ACSM done failed to complete in acsm_poll_done()...\r\n");break;
        case 0x040e0002: DEBUG_MSG("PMU: Error: setAcsmCLCWL: cl and cwl must be each >= 2 and 5, resp. CL=  CWL= \r\n");break;
        case 0x040f0002: DEBUG_MSG("PMU: Error: setAcsmCLCWL: cl and cwl must be each >= 5. CL=  CWL= \r\n");break;
        case 0x04110001: DEBUG_MSG("PMU: Error: Reserved value of register F0RC0F found in message block: case 0x \r\n");break;
        case 0x04150001: DEBUG_MSG("PMU: Error: Boot clock divider setting of   is too small\r\n");break;
        case 0x04180000: DEBUG_MSG("PMU: Error: Delay too large in slomo\r\n");break;
        default: DEBUG_MSG("No Error !!!! \r\n");break;
    }

    num = mail & 0xffff;
    if (num) 
    {
        DEBUG_MSG("exist more message \r\n");
        for (i = 0; i < num; i++)
        {
            //mail = get_mail(DPHY_ADDR_BASE);  
        }
    }
    else 
    {
        DEBUG_MSG("No more message \r\n");
    }
}

