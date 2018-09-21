/******************************************************************************
module:		cmsis
Description:	CMSIS Cortex-M3 Core Reference Documents
******************************************************************************/
>>inc<<
cmsis_armcc.h:	CMSIS compiler ARMCC (ARM compiler V5) header file
cmsis_compiler.h:	CMSIS compiler generic header file
core_cm3.h:	CMSIS Cortex-M3 Core Peripheral Access Layer Header File
stdint.h:		C99 generic header file

>>src<<
startup_acu.s:	CMSIS Core Device Startup File for ARMCM3 Device Series
system_acu.c:	ACU System Initial C file

/******************************************************************************
module:		driver
Description:	DengLin ACU Driver Reference Documents
******************************************************************************/
>>inc<<
acu_ddr.h:		ACU DDR3/DDR4 Device Access Driver Header File
acu_ddr_init.h:	ACU DDR3/DDR4 Initial Header File
acu_ddr_init_fpga.h:	ACU DDR FPGA Initial Header File
acu_debug.h:	ACU Debug Printf Info API Header File
acu_efuse.h:	ACU Efuse Device Access Driver Header File
acu_gpio.h:	ACU GPIO Device Access Driver Header File
acu_i2c.h:		ACU I2C Device Access Driver Header File
acu_int_gen.h:	ACU Interrupt Generate Device Access Driver Header File
acu_misc.h:	ACU MISC Useful API Header File
acu_pcie.h:	ACU PCIE Device Access Driver Header File
acu_pvt.h:		ACU PVT Device Access Driver Header File
acu_rcc.h:		ACU Reset&Clock Device Control Driver Header File
acu_spi.h:		ACU SSP Device Access Driver Header File
acu_spi_flash.h:	ACU Spi Flash Device Access Driver Header File
acu_tim.h:		ACU Timer Device Access Driver Header File
acu_uart.h:	ACU UART Device Access Driver Header File
acu_wdt.h:	ACU WDT Device Access Driver Header File

>>src<<
acu_ddr.c:			ACU DDR3/DDR4 Device Access Driver C File
acu_ddr_init.c:		ACU DDR3/DDR4 Initial C File
acu_ddr3_init_fpga.c:		ACU DDR3 FPGA Initial C File
acu_ddr3_phy_init.c:		ACU DDR3 Phy Initial C File
acu_ddr3_phy_init_fpga.c:	ACU DDR3 FPGA Phy Initial C File
acu_ddr3_pmu_train_dmen.c:	ACU DDR3 Training Firmware Dmem Initial C File
acu_ddr3_pmu_train_imem.c:	ACU DDR3 Training Firmware Imem Initial C File
acu_ddr4_phy_init.c:		ACU DDR4 Phy Initial C File
acu_ddrc_x8_init.c:		ACU DDR3/DDR4 X8 Initial C File
acu_debug.c:		ACU Debug Printf Info API C File
acu_efuse.c:		ACU Efuse Device Access Driver C File 
acu_gpio.c:		ACU GPIO Device Access Driver C File
acu_i2c.c:			ACU I2C Device Access Driver C File
acu_int_gen.c:		ACU Interrupt Generate Device Access Driver C File
acu_misc.c:		ACU MISC Useful API C File
acu_pcie.c:		ACU PCIE Device Access Driver C File
acu_pvt.c:			ACU PVT Device Access Driver C File
acu_rcc.c:			ACU Reset&Clock Device Control Driver C File
acu_spi.c:			ACU SPI Device Access Driver C File
acu_spi_flash.c:		ACU Spi Flash Device Access Driver C File
acu_tim.c:			ACU Timer Device Access Driver C File
acu_uart.c:		ACU UART Device Access Driver C File
acu_wdt.c:			ACU WDT Device Access Driver C File

/******************************************************************************
module:		include
Description:	DengLin ACU System Include Reference Documents
******************************************************************************/
acu.h:		ACU All Including Header File
system_acu.h:	ACU System Initial Header File

/******************************************************************************
module:		test
Description:	DengLin ACU Testing Reference Documents
******************************************************************************/
>>inc<<
test_cru.h:		ACU Reset&Clock Module Testing Header File
test_cu.h:		ACU DLM Module Testing Header File
test_ddr.h:		ACU DDR Module Testing Header File
test_efuse.h:	ACU Efuse Module Testing Header File
test_gpio.h:	ACU GPIO Module Testing Header File
test_i2c.h:		ACU I2C Module Testing Header File
test_int_gen.h:	ACU Interrupt Generate Testing Header File
test_pcie.h:	ACU PCIE Module Testing Header File
test_pvt.h:		ACU PVT Module Testing Header File
test_spi.h:		ACU SPI Module Testing Header File
test_spi_flash.h:	ACU Spi Flash Module Testing Header File
test_timer.h:	ACU Timer Module Testing Header File
test_uart.h:	ACU UART Module Testing Header File
test_wdt.h:	ACU WDT Module Testing Header File

>>src<<

/******************************************************************************
module:		user
Description:	DengLin ACU APP Reference Documents
******************************************************************************/
>>inc<<
>>src<<

main.c
