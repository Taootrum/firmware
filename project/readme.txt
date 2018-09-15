1.Device Configration
	ARM->ARM Cortex M3->ARMCM3	

2.Target Configration
	1)Code Generation:    
		1>ARM Compiler:Use default compiler version5
		2>Use MicroLIB

	2)Read/Only Memory Areas:
		on-chip:	Start		Size
		IROM1:	0x20000000      -	0x20000

	3)Read/Write Memory Areas
		on-chip:	Start		Size
		IRAM1:	0x20020000      -	0x8000

3)Output
	Name of Executable:firmware

4)User
	After Build/Rebuild:
	Run#1:	C:\Keil_v5\ARM\ARMCC\bin\fromelf.exe --bin -o ./Objects/@L.bin ./Objects/@L.axf

5)C/C++
	Preprocessor Symbols
	Define:	ACU_DEBUG,ACU_TEST,ACU_SIM,ACU_DDR3,ACU_DDR4,ACU_UPDATE
		1>ACU_DEBUG: 	Open the debug switch to printf debug information.
		2>ACU_TEST:	Run the test cases.
		3>ACU_SIM:	Build the firmware for RTL simulation.
		4>ACU_DDR3:	Build the DDR3 for firmware.
		5>ACU_DDR4:	Build the DDR4 for firmware.
		6>ACU_UPDATE:	Firmware surpport update  itself to spi-flash.

6)Debug/Utilities
	Reference the D:\soc\JLINK\MDK-JINK_Debug.docx