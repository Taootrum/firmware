#include "acu_ddr_init.h"

void DDRC_Init(void)
{
    uint8_t i = 0;
    uint32_t TempSet = 0;
    
    /* DDRC read dram_sel config */
    WRITE_REG(RST_SC->DDR_RCFG, 0x0);

    /* DDRC write dram_wcfg config */
    for (i = 0; i < DDRC_NUMBER; i++) 
    {
        TempSet |= (0x1 << i);
    }
    WRITE_REG(RST_SC->DDR_WCFG, TempSet);

    /* DDRC system management config */
    for (i = 0; i < DDRC_NUMBER; i++) 
    {
        /* set pub address non-compress mode */
        WRITE32(0x4008c024 + (i * 0x400), 0x4);
        /* release clock */
        WRITE32(0x4008c004 + (i * 0x400), 0x3f);
        /* release pubphy pwrokin */
        WRITE32(0x4008c000 + (i * 0x400), 0x1f);
        /* release umctl2 apb/debug reset */
        WRITE32(0x4008c000 + (i * 0x400), 0x13);
    }

    ddrc_x8_ddr3_init(DDRC_NUMBER);

    #if 0
    /* simple test */
    WRITE32(0xa0000000, 0x12345678);
    WRITE32(0xa0000004, 0x9abcdef0);
    WRITE32(0xa0000008, 0x11223344); 
    WRITE32(0xa000000c, 0x55667788);
    for (i = 0; i < DDRC_NUMBER; i++) 
    {
        WRITE32(0x40080420, i); // dram_sel 

        if(i==0) DEBUG_MSG("DDRC#0 read test. \n"); 
        else if(i==1) DEBUG_MSG("DDRC#1 read test. \n"); 
        else if(i==2) DEBUG_MSG("DDRC#2 read test. \n"); 
        else if(i==3) DEBUG_MSG("DDRC#3 read test. \n"); 
        else if(i==4) DEBUG_MSG("DDRC#4 read test. \n"); 
        else if(i==5) DEBUG_MSG("DDRC#5 read test. \n"); 
        else if(i==6) DEBUG_MSG("DDRC#6 read test. \n"); 
        else if(i==7) DEBUG_MSG("DDRC#7 read test. \n"); 

        if(READ32(0xa0000000) == 0x12345678) {
            DEBUG_MSG("DDR read data = 0x12345678\n");
        } else {
            DEBUG_MSG("DDR read data Error! \r\n");
        }   

        if(READ32(0xa0000004) == 0x9abcdef0) {
            DEBUG_MSG("DDR read data = 0x9abcdef0\n");
        } else {
            DEBUG_MSG("DDR read data Error! \r\n");
        }   
    }
    #endif
}

