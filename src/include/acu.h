/*******************************************************************************
  * @file    acu.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File. 
 ******************************************************************************/

#ifndef __ACU_H
#define __ACU_H

#ifdef __cplusplus
 extern "C" {
#endif 
  
/* -------------------------  ACU Interrupt Number Definition  ------------------------ */
typedef enum IRQn
{
/* -------------------  Cortex-M3 Processor Exceptions Numbers  ------------------- */
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/* ----------------------  ACU Specific Interrupt Numbers  --------------------- */
    I2C0_IRQn                   = 0,        /*!< I2C0 Interrupt                                   */
    I2C1_IRQn                   = 1,        /*!< I2C1 Interrupt                                   */
    I2C2_IRQn                   = 2,        /*!< I2C2 Interrupt                                   */
    INT_IRQn                    = 3,        /*!< INT Interrupt                                    */
    GPIO_IRQn                   = 4,        /*!< GPIO Interrupt                                   */
    UART_IRQn                   = 5,        /*!< UART Interrupt                                   */
    SSP0_IRQn                   = 6,        /*!< SSP0 Interrupt                                   */
    SSP1_IRQn                   = 7,        /*!< SSP1 Interrupt                                   */
    TIMER0_IRQn                 = 8,        /*!< Timer0 Interrupt                                 */
    TIMER1_IRQn                 = 9,        /*!< Timer1 Interrupt                                 */
    WDT_IRQn                    = 10,       /*!< Watchdog Timer Interrupt                         */
    PVT_IRQn                    = 11,       /*!< PVT Sensor Interrupt                             */
    DDR0_IRQn                   = 12,       /*!< DDR Interrupt0                                   */
    DDR1_IRQn                   = 13,       /*!< DDR Interrupt1                                   */
    DDR2_IRQn                   = 14,       /*!< DDR Interrupt2                                   */
    CU_IRQn                     = 15,       /*!< CU Interrupt                                     */
} IRQn_Type;

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma anon_unions
#endif

/* --------  Configuration of the Cortex-M3 Processor and Core Peripherals  ------- */
#define __CM3_REV                 0x0201U   /* Core revision r2p1 */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present or not */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */

#include "core_cm3.h"
#include "system_ARMCM3.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define CPUID   0x412FC231

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, ResetStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
typedef enum {FALSE = 0, TRUE = !FAILED} BoolStatus;
  
/* ================================================================================ */
/* ================       Peripheral_registers_structures          ================ */
/* ================================================================================ */

/* brief Inter Integrated Circuit Interface */
typedef struct
{
    __IO uint32_t CR;                     /*!< Offset: 0x000 Control Register (R/W) */
    __IO uint32_t TAR;                    /*!< Offset: 0x004 Target Register (R/W) */
    __IO uint32_t SAR;                    /*!< Offset: 0x008 Slave Register (R/W) */
    __IO uint32_t HS_MADDR;               /*!< Offset: 0x00C HS Master Mode Code Address Register (R/W) */
    __IO uint32_t DATACMD;                /*!< Offset: 0x010 Rx/Tx Data Bufffer and Command Register (R/W) */
    __IO uint32_t SS_SCL_HCNT;            /*!< Offset: 0x014 Standard Speed I2C Clock SCL High Count Register (R/W) */
    __IO uint32_t SS_SCL_LCNT;            /*!< Offset: 0x018 Standard Speed I2C Clock SCL Low Count Register (R/W) */
    __IO uint32_t FS_SCL_HCNT;            /*!< Offset: 0x01C Fast Speed I2C Clock SCL High Count Register (R/W) */
    __IO uint32_t FS_SCL_LCNT;            /*!< Offset: 0x020 Fast Speed I2C Clock SCL Low Count Register (R/W) */
    __IO uint32_t HS_SCL_HCNT;            /*!< Offset: 0x024 High Speed I2C Clock SCL High Count Register (R/W) */
    __IO uint32_t HS_SCL_LCNT;            /*!< Offset: 0x028 High Speed I2C Clock SCL Low Count Register (R/W) */
    __I  uint32_t INTR_STAT;              /*!< Offset: 0x02C Interrupt Status Register (R/ ) */
    __IO uint32_t INTR_MASK;              /*!< Offset: 0x030 Interrupt Mask Register (R/W) */
    __I  uint32_t RAW_INTR_STAT;          /*!< Offset: 0x034 Raw Interrupt Status Register (R/ ) */
    __IO uint32_t RX_TL;                  /*!< Offset: 0x038 Receive FIFO Threshold Register (R/W) */
    __IO uint32_t TX_TL;                  /*!< Offset: 0x03C Transmit FIFO Threshold Register (R/W) */
    __I  uint32_t CLR_INTR;               /*!< Offset: 0x040 Clear Combined and Individual Interrupt Register (R/ ) */
    __I  uint32_t CLR_RX_UNDER;           /*!< Offset: 0x044 Clear RX_UNDER Interrupt Register (R/ ) */
    __I  uint32_t CLR_RX_OVER;            /*!< Offset: 0x048 Clear RX_OVER Interrupt Register (R/ ) */
    __I  uint32_t CLR_TX_OVER;            /*!< Offset: 0x04C Clear TX_OVER Interrupt Register (R/ ) */
    __I  uint32_t CLR_RD_REQ;             /*!< Offset: 0x050 Clear RD_REQ Interrupt Register (R/ ) */
    __I  uint32_t CLR_TX_ABRT;            /*!< Offset: 0x054 Clear TX_ABRT Interrupt Register (R/ ) */
    __I  uint32_t CLR_RX_DONE;            /*!< Offset: 0x058 Clear RX_DONE Interrupt Register (R/ ) */
    __I  uint32_t CLR_ACTIVITY;           /*!< Offset: 0x05C Clear ACTIVITY Interrupt Register (R/ ) */
    __I  uint32_t CLR_STOP_DET;           /*!< Offset: 0x060 Clear STOP_DET Interrupt Register (R/ ) */
    __I  uint32_t CLR_START_DET;          /*!< Offset: 0x064 Clear START_DET Interrupt Register (R/ ) */
    __I  uint32_t CLR_GEN_CALL;           /*!< Offset: 0x068 Clear GEN_CALL Interrupt Register (R/ ) */
    __IO uint32_t ENABLE;                 /*!< Offset: 0x06C Enable Register (R/W) */
    __I  uint32_t STATUS;                 /*!< Offset: 0x070 Status Register (R/ ) */
    __I  uint32_t TXFLR;                  /*!< Offset: 0x074 Transmit FIFO Level Register (R/ ) */
    __I  uint32_t RXFLR;                  /*!< Offset: 0x078 Receive FIFO Level Register (R/ ) */
         uint8_t  RESERVED1[4];
    __IO uint32_t TX_ABRT_SOURCE;         /*!< Offset: 0x080 Transmit Abort Status Register (R/W) */
         uint8_t  RESERVED2[20];
    __IO uint32_t ACK_GENERAL_CALL;       /*!< Offset: 0x098 ACK General Register (R/W) */
    __I  uint32_t ENABLE_STATUS;          /*!< Offset: 0x09C Enable Status Register (R/ ) */
    __IO uint32_t SDA_CFG;                /*!< Offset: 0x0A0 SDA Configuration Register (R/W) */
} I2C_TypeDef;

/* IO PAD System Management */
typedef struct
{
    __IO uint32_t FCR0;                   /*!< Offset: 0x000 Function Configuration0 Register (R/W) */
    __IO uint32_t FCR1;                   /*!< Offset: 0x004 Function Configuration1 Register (R/W) */
    __IO uint32_t FCR2;                   /*!< Offset: 0x008 Function Configuration2 Register (R/W) */
    __IO uint32_t FCR3;                   /*!< Offset: 0x00C Function Configuration3 Register (R/W) */
    __IO uint32_t FCR4;                   /*!< Offset: 0x010 Function Configuration4 Register (R/W) */
} IOPAD_TypeDef;

/* brief General Purpose I/O */
typedef struct
{
    __IO uint32_t IR;
    __IO uint32_t OR;
    __IO uint32_t DR;
    __IO uint32_t PUDE;
    __IO uint32_t GIMR;
    __IO uint32_t GPIMR;
    __IO uint32_t PIR;
    __IO uint32_t ITR;
    __IO uint32_t IFR;
    __IO uint32_t ICR;
    uint32_t  RESERVED[6];
} GPIO_TypeDef;

/* brief General Purpose I/O interrupt status */
typedef struct
{
    __I  uint32_t GP0IR;                  /*!< Offset: 0x000 GPIO group 0 Interrupt Register (R/ ) */
    __I  uint32_t GP1IR;                  /*!< Offset: 0x004 GPIO group 1 Interrupt Register (R/ ) */
    __I  uint32_t GP2IR;                  /*!< Offset: 0x008 GPIO group 2 Interrupt Register (R/ ) */
} GPIO_IRTypeDef;

/* brief Independent WATCHDOG */
typedef struct
{
    __IO uint32_t CR;                     /*!< Offset: 0x000 Control Register (R/W) */
    __IO uint32_t TORR;                   /*!< Offset: 0x004 Timeout Range Register (R/W) */
    __I  uint32_t CCVR;                   /*!< Offset: 0x008 Current Counter Value Register (R/ ) */
    __O  uint32_t CRR;                    /*!< Offset: 0x00C Counter Restart Register ( /W) */
    __I  uint32_t STATUS;                 /*!< Offset: 0x010 Interrupt Status Register (R/ ) */
    __I  uint32_t EOI;                    /*!< Offset: 0x014 Interrupt Clear Register (R/ ) */
} WDT_TypeDef;

/* brief Serial Peripheral Interface */
typedef struct
{
    __IO uint32_t CR0;                    /*!< Offset: 0x000 Control Register 0 (R/W) */
    __IO uint32_t CR1;                    /*!< Offset: 0x004 Control Register 1 (R/W) */
    __IO uint32_t DR;                     /*!< Offset: 0x008 Receive FIFO(read) and transmit FIFO(write) data Register (R/W) */
    __I  uint32_t SR;                     /*!< Offset: 0x00C Status Register (R/ ) */
    __IO uint32_t CPSR;                   /*!< Offset: 0x010 Clock Prescale Register (R/W) */
    __IO uint32_t IMSC;                   /*!< Offset: 0x014 Interrupt Mask Set and Clear Register (R/W) */
    __I  uint32_t RIS;                    /*!< Offset: 0x018 Raw Interrupt Status Register (R/ ) */
    __I  uint32_t MIS;                    /*!< Offset: 0x01C Masked Interrupt Status Register (R/ ) */
    __O  uint32_t ICR;                    /*!< Offset: 0x020 Interrupt Clear Register ( /W) */
    __IO uint32_t DMACR;                  /*!< Offset: 0x024 DMA Control Register (R/W) */
    __IO uint32_t FIFOTH;                 /*!< Offset: 0x028 FIFO Threshold Register (R/W) */
} SPI_TypeDef;

/* brief TIM */
typedef struct
{
    __IO uint32_t LC;                     /*!< Offset: 0x000 Load Counter Register (R/W) */
    __I  uint32_t CV;                     /*!< Offset: 0x004 Current Value Register (R/ ) */
    __IO uint32_t CR;                     /*!< Offset: 0x008 Control Register (R/W) */
    __I  uint32_t EOI;                    /*!< Offset: 0x00C End-of-Interrupt Register (R/ ) */
    __I  uint32_t IS;                     /*!< Offset: 0x010 Interrupt Status Register (R/ ) */
} TIM_TypeDef;

/* brief Universal Synchronous Asynchronous Receiver Transmitter */
typedef struct
{
    __IO uint32_t DR;                     /*!< Offset: 0x000 Data Register (R/W) */
    union {
    __I  uint32_t RSR;                    /*!< Offset: 0x004 Receive Status Register (R/ ) */
    __O  uint32_t ECR;                    /*!< Offset: 0x004 Error Clear Register ( /W) */
    };
         uint8_t  RESERVED1[16];
    __I  uint32_t FR;                     /*!< Offset: 0x018 Flag Register (R/ ) */
         uint8_t  RESERVED2[4];
    __IO uint32_t ILPR;                   /*!< Offset: 0x020 IrDA Low-Power Counter Register (R/W) */
    __IO uint32_t IBRD;                   /*!< Offset: 0x024 Integer Baud Rate Register (R/W) */
    __IO uint32_t FBRD;                   /*!< Offset: 0x028 Fractional Baud Rate Register (R/W) */
    __IO uint32_t LCR;                    /*!< Offset: 0x02C Line Control Register (R/W) */
    __IO uint32_t CR;                     /*!< Offset: 0x030 Control Register (R/W) */
    __IO uint32_t IFLS;                   /*!< Offset: 0x034 Interrupt FIFO Level Select Register (R/W) */
    __IO uint32_t IMSC;                   /*!< Offset: 0x038 Interrupt Mask Set/Clear Register (R/W) */
    __I  uint32_t RIS;                    /*!< Offset: 0x03C Raw Interrupt Status Register (R/ ) */
    __I  uint32_t MIS;                    /*!< Offset: 0x040 Masked Interrupt Status Register (R/ ) */
    __O  uint32_t ICR;                    /*!< Offset: 0x044 Interrupt Clear Register ( /W) */
    __IO uint32_t DMACR;                  /*!< Offset: 0x048 DMA Control Register (R/W) */
} UART_TypeDef;

/* Chip Reset System Management */
typedef struct
{
    __IO uint32_t SRST;                     /*!< Offset: 0x000 Soft Reset Register (R/W) */
    __IO uint32_t SRST_CNT;                 /*!< Offset: 0x004 Soft Reset Timing Register (R/W) */
    __IO uint32_t PCIE_RST;                 /*!< Offset: 0x008 PCIE Subsystem Reset Register (R/W) */
    __IO uint32_t IPCORE_RST;               /*!< Offset: 0x00C IP CORE Subsystem Register (R/W) */
    __IO uint32_t CLKM_RST;                 /*!< Offset: 0x010 Clock Manager Reset Register (R/W) */
    __IO uint32_t BUS_RST;                  /*!< Offset: 0x014 Fabric Bus Reset Register (R/W) */
    __IO uint32_t DDR_RST;                  /*!< Offset: 0x018 DDR Subsystem Reset Register (R/W) */
    __IO uint32_t GRF;                      /*!< Offset: 0x01C Global Reset Flag Register (R/W) */
    __IO uint32_t DDR_RCFG;                 /*!< Offset: 0x020 DDR Select Register (R/W) */
    __IO uint32_t DDR_WCFG;                 /*!< Offset: 0x024 DDR Write Configure Register (R/W) */
    __IO uint32_t IOPAD_RST;                /*!< Offset: 0x028 IOPAD Subsystem Reset Register (R/W) */
} CHIPRST_TypeDef;

/* PLL Clock System Management */
typedef struct
{
    __IO uint32_t RESET;                    /*!< Offset: 0x00 Reset Register (R/W) */
    __IO uint32_t BYPASS;                   /*!< Offset: 0x04 Bypass Register (R/W) */
    __IO uint32_t DIVR;                     /*!< Offset: 0x08 Reference Divider Value Register (R/W) */
    __IO uint32_t DIVF_LOW;                 /*!< Offset: 0x0C Feedback Divider Value bit(0-7) Register (R/W) */
    __IO uint32_t DIVF_HIGH;                /*!< Offset: 0x10 Feedback Divider Value bit(8) Register (R/W) */
    __IO uint32_t DIVQ;                     /*!< Offset: 0x14 Output Divider Value Register (R/W) */
    __IO uint32_t FSE;                      /*!< Offset: 0x18 Chooses Between Internal And External Input Paths Register (R/W) */
    __IO uint32_t RANGE;                    /*!< Offset: 0x1C Filter Range Register (R/W) */
    __IO uint32_t CONTROL;                  /*!< Offset: 0x20 Control Register (R/W) */
    __IO uint32_t ENABLE;                   /*!< Offset: 0x24 Enable Register (R/W) */
    __IO uint32_t LOCK;                     /*!< Offset: 0x28 Lock Register (R/W) */   
        uint32_t RESERVED;                  /*!< Offset: 0x2C Reserved */
} PLLCLK_TypeDef;

/* Clock System Management */
typedef struct
{
    __IO uint32_t CLKSRC;                 /*!< Offset: 0x0C0 Fabric clock ClkGen Clock Source Register (R/W) */
    __IO uint32_t CLKRATIO;               /*!< Offset: 0x0C4 Fabric clock ClkGen Clock Divider Register (R/W) */
       uint8_t  RESERVED2[4];
    __IO uint32_t CLKGT;                  /*!< Offset: 0x0CC Fabric clock ClkGen Clock Gate Register (R/W) */
} CLK_TypeDef;

/* BOOT MODE Management */
typedef struct
{
    __I  uint32_t XOM;                    /*!< Offset: 0x000 Boot Mode IO Status Register (R/ ) */
} BMIO_TypeDef;

/* IRAM/IROM Controller System Management */
typedef struct
{
    __IO uint32_t SR;                     /*!< Offset: 0x000 Soft Reset Register (R/W) */
    __IO uint32_t CGE;                    /*!< Offset: 0x004 Clock Gate Enable Register (R/W) */
       uint8_t  RESERVED1[12];
    __IO uint32_t MPD;                    /*!< Offset: 0x014 Memory Power-Down Register (R/W) */
       uint8_t  RESERVED2[4];
    __IO uint32_t SCR;                    /*!< Offset: 0x01C SyncReset Clock Gate Register (R/W) */
} IMEMC_TypeDef;

/* Cortex M3 System Management */
typedef struct
{
    __IO uint32_t SRR;                    /*!< Offset: 0x000 CM3 CPU Soft Reset Register (R/W) */
    __IO uint32_t CGE;                    /*!< Offset: 0x004 CM3 CPU Clock Gate Enable Register (R/W) */
    __IO uint32_t SHR;                    /*!< Offset: 0x008 CM3 CPU Sleep Hold Register (R/W) */
       uint8_t  RESERVED1[20];
    __IO uint32_t BRR;                    /*!< Offset: 0x020 CM3 CPU Boot Remapping Register (R/W) */
    __IO uint32_t CR;                     /*!< Offset: 0x024 CM3 CPU Configuration Register (R/W) */
    __IO uint32_t SCR0;                   /*!< Offset: 0x028 CM3 CPU Systick Calibration Register 0 (R/W) */
    __IO uint32_t SCR1;                   /*!< Offset: 0x02C CM3 CPU Systick Calibration Register 1 (R/W) */
    __IO uint32_t SCR2;                   /*!< Offset: 0x030 CM3 CPU Systick Calibration Register 2 (R/W) */
    __IO uint32_t NMCR;                   /*!< Offset: 0x034 CM3 CPU NM Configure Register (R/W) */
    __IO uint32_t RXEVCR;                 /*!< Offset: 0x038 CM3 CPU RXEV Configure Register (R/W) */
    __IO uint32_t SER;                    /*!< Offset: 0x03C CM3 CPU SysTick Enable Register (R/W) */
    __I  uint32_t SR0;                    /*!< Offset: 0x040 CM3 CPU Status Register 0 (R/ ) */
    __I  uint32_t SR1;                    /*!< Offset: 0x044 CM3 CPU Status Register 1 (R/ ) */
    __I  uint32_t SR2;                    /*!< Offset: 0x048 CM3 CPU Status Register 2 (R/ ) */
    __I  uint32_t SR3;                    /*!< Offset: 0x04C CM3 CPU Status Register 3 (R/ ) */
    __I  uint32_t SR4;                    /*!< Offset: 0x050 CM3 CPU Status Register 4 (R/ ) */
} CM3SYS_TypeDef;

/* APB peripherals System Management */
typedef struct
{
    __IO uint32_t SR;                     /*!< Offset: 0x000 Soft Reset Register (R/W) */
    __IO uint32_t CGE;                    /*!< Offset: 0x004 Clock Gate Enable Register (R/W) */
       uint8_t  RESERVED1[16];
    __IO uint32_t ISO;                    /*!< Offset: 0x018 Interface ISO Register (R/W) */
    __IO uint32_t SCR;                    /*!< Offset: 0x01C SyncReset Clock Gate Register (R/W) */
    union Adress20{
        __IO uint32_t WDT_PAUSE;          /*!< Offset: 0x020 WDT Pause Register (R/W) */
        __IO uint32_t INT_STATUS;         /*!< Offset: 0x020 Interrupt Status Register (R/W) */
        __IO uint32_t DLM_INTSEL;         /*!< Offset: 0x020 DLM Interrupt Select Register (R/W) */
        __IO uint32_t PVT0_DIV;           /*!< Offset: 0x020 PVT0 Clock Divider Register (R/W) */
        __IO uint32_t DDR_PORT_ADDR;      /*!< Offset: 0x020 DDR Port Addr Register (R/W) */
    };
    union Adress24{
        __IO uint32_t WDT_SPEEDUP;        /*!< Offset: 0x024 WDT Speedup Register (R/W) */
        __IO uint32_t PVT1_DIV;           /*!< Offset: 0x024 PVT1 Clock Divider Register (R/W) */
        __IO uint32_t DDR_MODE_CONFIG;    /*!< Offset: 0x024 DDR Mode Configure Register (R/W) */
    };
    union Adress28{
        __IO uint32_t PVT_INTMASK;        /*!< Offset: 0x028 PVT Interrupt Mask Register (R/W) */
        __IO uint32_t DDR_CSYSREG;        /*!< Offset: 0x028 DDR Csysreg Register (R/W) */
    };
    union Adress2C{
        __IO uint32_t PVT_INTSTA;         /*!< Offset: 0x02C PVT Interrupt Sta Register (R/W) */
        __I  uint32_t DDR_CACTIVE_OR;     /*!< Offset: 0x02C DDR Cactive OR Register (R/ ) */
    };
    __I  uint32_t DDR_CSYSACK;            /*!< Offset: 0x030 DDR Csysack Register (R/ ) */
    __I  uint32_t DDR_CACTIVE;            /*!< Offset: 0x034 DDR Cactive Register (R/ ) */
    __IO uint32_t DDR_ARURGENT;           /*!< Offset: 0x038 DDR AXI Read Urgent Register (R/W) */
    __IO uint32_t DDR_AWURGENT;           /*!< Offset: 0x03C DDR AXI Write Urgent Register (R/W) */
    __IO uint32_t DDR_PARMASK;            /*!< Offset: 0x040 DDR AXI Port Read Mask Register (R/W) */
    __IO uint32_t DDR_PAWMASK;            /*!< Offset: 0x044 DDR AXI Port Write Mask Register (R/W) */
    __IO uint32_t DDR_AQOS0;              /*!< Offset: 0x048 DDR AXI Port0 QoS Register (R/W) */
    __IO uint32_t DDR_AQOS1;              /*!< Offset: 0x04C DDR AXI Port1 QoS Register (R/W) */
    __IO uint32_t DDR_AQOS2;              /*!< Offset: 0x050 DDR AXI Port2 QoS Register (R/W) */
    __I  uint32_t DDR_MRR_DATA0;          /*!< Offset: 0x054 + 0x4*n DDR CH0 MRR Data Register (R/ ) */
    __I  uint32_t DDR_MRR_DATA1;          /*!< Offset: 0x094 + 0x4*n DDR CH1 MRR Data Register (R/ ) */
    __I  uint32_t DDR_CHVLD;              /*!< Offset: 0x0D4 DDR MMR Valid Register (R/ ) */
} APBSYS_TypeDef;

/* Interrupt generator */
typedef struct
{
    __IO uint32_t STATUS;                 /*!< Offset: 0x000 Interrupt Status Register (R/W) */
    __IO uint32_t MASK;                   /*!< Offset: 0x004 Interrupt Mask Register (R/W) */
    __IO uint32_t DATA0;                  /*!< Offset: 0x008 Interrupt Data0 Register (R/W) */
    __IO uint32_t DATA1;                  /*!< Offset: 0x00C Interrupt Data1 Register (R/W) */
    __IO uint32_t DATA2;                  /*!< Offset: 0x010 Interrupt Data2 Register (R/W) */
    __IO uint32_t DATA3;                  /*!< Offset: 0x014 Interrupt Data3 Register (R/W) */
    __IO uint32_t DATA4;                  /*!< Offset: 0x018 Interrupt Data4 Register (R/W) */
    __IO uint32_t DATA5;                  /*!< Offset: 0x01C Interrupt Data5 Register (R/W) */
    __IO uint32_t DATA6;                  /*!< Offset: 0x020 Interrupt Data6 Register (R/W) */
    __IO uint32_t DATA7;                  /*!< Offset: 0x024 Interrupt Data7 Register (R/W) */
} INT_TypeDef;

/* Compute Unit */
typedef struct
{
        uint8_t  RESERVED[0x100];
    __IO uint32_t CQ_IRQ_RAW;             /*!< Offset: 0x100 Interrupt RAW Register (R/W) */
    __IO uint32_t CQ_IRQ_CLEAR;           /*!< Offset: 0x104 Interrupt CLEAR Register (R/W) */
    __IO uint32_t CQ_IRQ_MASK;            /*!< Offset: 0x108 Interrupt MASK Register (R/W) */
    __IO uint32_t CQ_IRQ_STATUS;          /*!< Offset: 0x10C Interrupt STATUS Register (R/W) */
} CU_TypeDef;

/* PVT Module */
typedef struct
{
    __IO uint32_t APB_CTRL;             /*!< Offset: 0x000 APB Interface Enable Register (R/W) */
    __IO uint32_t MODE_CTRL;            /*!< Offset: 0x004 Sensor Modes Control Register (R/W) */
    __IO uint32_t TRIMO_CTRL;           /*!< Offset: 0x008 Reserved */
    __IO uint32_t TRIMG_CTRL;           /*!< Offset: 0x00C TRIM Control Register (R/W) */
    __I  uint32_t SENSOR_DATA;          /*!< Offset: 0x010 Sensor Data Register (R/ ) */
    __I  uint32_t DATA_VALID;           /*!< Offset: 0x014 Data Valid Flag Register (R/ ) */
    __IO uint32_t SENSOR_ENA;           /*!< Offset: 0x018 Sensor Enable Register (R/W) */
} PVT_TypeDef;

/* EFUSE Module */
typedef struct
{
    __IO uint32_t ESI_MEMFUSE_CTRL;     /*!< Offset: 0x000 EFUSE Control Register (R/W) */
    __O  uint32_t ESI_MEMFUSE_WRDATA;   /*!< Offset: 0x004 EFUSE Write Data Register ( /W) */
    __IO uint32_t ESI_MEMFUSE_RDDATA;   /*!< Offset: 0x008 EFUSE Read Data Register (R/W) */
    __I  uint32_t ESI_MEMFUSE_STAT;     /*!< Offset: 0x00C EFUSE Status Register (R/ ) */
    __IO uint32_t ESI_MEMFUSE_DIV;      /*!< Offset: 0x010 EFUSE Clock Divider Register (R/W) */
} EFUSE_TypeDef;

/* PCIE Module */
typedef struct
{
    __IO uint32_t REGISTER0;            /*!< Offset: 0x000 Register (R/W) */
    __IO uint32_t REGISTER1;            /*!< Offset: 0x004 Register (R/W) */
        uint8_t  RESERVED[24];          /*!< Offset: 0x008 Reserved */
    __IO uint32_t REGISTER2;            /*!< Offset: 0x020 Register (R/W) */
    __IO uint32_t REGISTER3;            /*!< Offset: 0x024 Register (R/W) */
    __I  uint32_t REGISTER4;            /*!< Offset: 0x028 Register (R/ ) */
    __I  uint32_t REGISTER5;            /*!< Offset: 0x02C Register (R/ ) */
    __I  uint32_t REGISTER6;            /*!< Offset: 0x030 Register (R/ ) */
    __I  uint32_t REGISTER7;            /*!< Offset: 0x034 Register (R/ ) */
    __I  uint32_t REGISTER8;            /*!< Offset: 0x038 Register (R/ ) */
    __I  uint32_t REGISTER9;            /*!< Offset: 0x03C Register (R/ ) */
    __I  uint32_t REGISTER10;           /*!< Offset: 0x040 Register (R/ ) */
    __I  uint32_t REGISTER11;           /*!< Offset: 0x044 Register (R/ ) */
    __I  uint32_t REGISTER12;           /*!< Offset: 0x048 Register (R/ ) */
    __I  uint32_t REGISTER13;           /*!< Offset: 0x04C Register (R/ ) */
    __I  uint32_t REGISTER14;           /*!< Offset: 0x050 Register (R/ ) */
    __I  uint32_t REGISTER15;           /*!< Offset: 0x054 Register (R/ ) */
    __I  uint32_t REGISTER16;           /*!< Offset: 0x058 Register (R/ ) */
    __I  uint32_t REGISTER17;           /*!< Offset: 0x05C Register (R/ ) */
    __I  uint32_t REGISTER18;           /*!< Offset: 0x060 Register (R/ ) */
    __I  uint32_t REGISTER19;           /*!< Offset: 0x064 Register (R/ ) */
    __I  uint32_t REGISTER20;           /*!< Offset: 0x068 Register (R/ ) */
    __I  uint32_t REGISTER21;           /*!< Offset: 0x06C Register (R/ ) */
    __I  uint32_t REGISTER22;           /*!< Offset: 0x070 Register (R/ ) */
    __I  uint32_t REGISTER23;           /*!< Offset: 0x074 Register (R/ ) */
    __I  uint32_t REGISTER24;           /*!< Offset: 0x078 Register (R/ ) */
    __I  uint32_t REGISTER25;           /*!< Offset: 0x07C Register (R/ ) */
    __I  uint32_t REGISTER26;           /*!< Offset: 0x080 Register (R/ ) */
    __I  uint32_t REGISTER27;           /*!< Offset: 0x084 Register (R/ ) */
    __I  uint32_t REGISTER28;           /*!< Offset: 0x088 Register (R/ ) */
    __I  uint32_t REGISTER29;           /*!< Offset: 0x08C Register (R/ ) */
    __I  uint32_t REGISTER30;           /*!< Offset: 0x090 Register (R/ ) */
    __I  uint32_t REGISTER31;           /*!< Offset: 0x094 Register (R/ ) */
    __I  uint32_t REGISTER32;           /*!< Offset: 0x098 Register (R/ ) */
    __I  uint32_t REGISTER33;           /*!< Offset: 0x09C Register (R/ ) */
    __I  uint32_t REGISTER34;           /*!< Offset: 0x0A0 Register (R/ ) */
    __I  uint32_t REGISTER35;           /*!< Offset: 0x0A4 Register (R/ ) */
        uint8_t  RESERVED1[28];         /*!< Offset: 0x0A8 Reserved */
    __IO uint32_t DBI_SEL;              /*!< Offset: 0x0C4 Register (R/W) */
    __IO uint32_t PHY_LOS_BIAS;         /*!< Offset: 0x0C8 Register (R/W) */
    __IO uint32_t PHY_LOS_LEVEL;        /*!< Offset: 0x0CC Register (R/W) */
    __IO uint32_t PHY_RX0_EQ;           /*!< Offset: 0x0D0 Register (R/W) */
    __IO uint32_t PHY_TX_DEEMPH_GEN23;  /*!< Offset: 0x0D4 Register (R/W) */
    __IO uint32_t PHY_TX_DEEMPH_GEN26;  /*!< Offset: 0x0D8 Register (R/W) */
    __IO uint32_t PHY_TX_DEEMPH_GEN1;   /*!< Offset: 0x0DC Register (R/W) */
    __IO uint32_t PCS_TX_SWING_FULL;    /*!< Offset: 0x0E0 Register (R/W) */
    __IO uint32_t PCS_TX_SWING_LOW;     /*!< Offset: 0x0E4 Register (R/W) */
    __IO uint32_t PHY_TX0_TERM_OFT;     /*!< Offset: 0x0E8 Register (R/W) */
    __IO uint32_t PHY_TX_VBOOST_1V1;    /*!< Offset: 0x0EC Register (R/W) */
    __IO uint32_t VREG_BYPASS;          /*!< Offset: 0x0F0 Register (R/W) */
} PCIE_TypeDef;

/* ================================================================================ */
/* ================           Peripheral_memory_map                ================ */
/* ================================================================================ */

/*!< Peripheral base address */
#define ACU_ROM_BASE            ((uint32_t)0x00000000) /*!< IROM    base address in the alias region */
#define ACU_RAM_BASE            ((uint32_t)0x20000000) /*!< IRAM    base address in the alias region */
#define ACU_PCIE_BASE           ((uint32_t)0x40000000) /*!< PCIE    base address in the alias region */
#define ACU_CU_BASE             ((uint32_t)0x40010000) /*!< CU      base address in the alias region */
#define ACU_APB_BASE            ((uint32_t)0x40020000) /*!< APB     base address in the alias region */
#define ACU_PUB_BASE            ((uint32_t)0x44000000) /*!< PUB     base address in the alias region */
#define ACU_UMCTL2_BASE         ((uint32_t)0x46000000) /*!< UMCTL2  base address in the alias region */
#define ACU_DRAM_BASE           ((uint32_t)0xA0000000) /*!< DRAM    base address in the alias region */

/*!< Peripheral memory map */
#define ACU_I2C0_BASE           (ACU_APB_BASE + 0x00000)
#define ACU_I2C1_BASE           (ACU_APB_BASE + 0x01000)
#define ACU_I2C2_BASE           (ACU_APB_BASE + 0x02000)
#define ACU_INT_BASE            (ACU_APB_BASE + 0x03000)
#define ACU_UART_BASE           (ACU_APB_BASE + 0x10000)
#define ACU_GPIO_BASE           (ACU_APB_BASE + 0x20000)
#define ACU_SSP0_BASE           (ACU_APB_BASE + 0x30000)
#define ACU_SSP1_BASE           (ACU_APB_BASE + 0x31000)
#define ACU_TIM0_BASE           (ACU_APB_BASE + 0x40000)
#define ACU_TIM1_BASE           (ACU_APB_BASE + 0x40014)
#define ACU_WDT_BASE            (ACU_APB_BASE + 0x50000)
#define ACU_SYS_BASE            (ACU_APB_BASE + 0x60000)
#define ACU_PVT_BASE            (ACU_APB_BASE + 0x70000)

#define ACU_GPIO_IR_BASE        (ACU_GPIO_BASE + 0x4000)

/*!< System Controller */
#define ACU_RSTSC_BASE          (ACU_SYS_BASE + 0x00400)
#define ACU_I2CSC_BASE          (ACU_SYS_BASE + 0x04000)
#define ACU_UARTSC_BASE         (ACU_SYS_BASE + 0x04400)
#define ACU_GPIOSC_BASE         (ACU_SYS_BASE + 0x04800)
#define ACU_SSPSC_BASE          (ACU_SYS_BASE + 0x04C00)
#define ACU_TIMSC_BASE          (ACU_SYS_BASE + 0x05000)
#define ACU_WDTSC_BASE          (ACU_SYS_BASE + 0x05400)
#define ACU_PVTSC_BASE          (ACU_SYS_BASE + 0x05C00)
#define ACU_IROMSC_BASE         (ACU_SYS_BASE + 0x08000)
#define ACU_IRAMSC_BASE         (ACU_SYS_BASE + 0x08400)
#define ACU_PCIESC_BASE         (ACU_SYS_BASE + 0x08800)
#define ACU_CUSC_BASE           (ACU_SYS_BASE + 0x08C00)
#define ACU_IOPADSC_BASE        (ACU_SYS_BASE + 0x09000)
#define ACU_BMIO_BASE           (ACU_IOPADSC_BASE + 0x03fc)
#define ACU_CLKSC_BASE          (ACU_SYS_BASE + 0x09400)
#define ACU_M3SC_BASE           (ACU_SYS_BASE + 0x09800)
#define ACU_DRAM0SM_BASE        (ACU_SYS_BASE + 0x0C000)
#define ACU_DRAM1SM_BASE        (ACU_SYS_BASE + 0x0C400)
#define ACU_DRAM2SM_BASE        (ACU_SYS_BASE + 0x0C800)
#define ACU_DRAM3SM_BASE        (ACU_SYS_BASE + 0x0CC00)
#define ACU_DRAM4SM_BASE        (ACU_SYS_BASE + 0x0D000)
#define ACU_DRAM5SM_BASE        (ACU_SYS_BASE + 0x0D400)
#define ACU_DRAM6SM_BASE        (ACU_SYS_BASE + 0x0D800)
#define ACU_DRAM7SM_BASE        (ACU_SYS_BASE + 0x0DC00)

/* ================================================================================ */
/* ================           Peripheral_declaration               ================ */
/* ================================================================================ */

#define I2C_MODULE_MAX          3
#define UART_MODULE_MAX         1
#define SPI_MODULE_MAX          2
#define TIM_MODULE_MAX          2
#define WDT_MODULE_MAX          1
#define GPIO_MODULE_MAX         1

/*<! APB Peripheral module declaration */
#define I2C0                    ((I2C_TypeDef *) ACU_I2C0_BASE)
#define I2C1                    ((I2C_TypeDef *) ACU_I2C1_BASE)
#define I2C2                    ((I2C_TypeDef *) ACU_I2C2_BASE)
#define INT_GEN                 ((INT_TypeDef *) ACU_INT_BASE)
#define UART                    ((UART_TypeDef *) ACU_UART_BASE)
#define SPI0                    ((SPI_TypeDef *) ACU_SSP0_BASE)
#define SPI1                    ((SPI_TypeDef *) ACU_SSP1_BASE)
#define TIM0                    ((TIM_TypeDef *) ACU_TIM0_BASE)
#define TIM1                    ((TIM_TypeDef *) ACU_TIM1_BASE)
#define WDT                     ((WDT_TypeDef *) ACU_WDT_BASE)
#define CU                      ((CU_TypeDef *) ACU_CU_BASE)
#define PVT0                    ((PVT_TypeDef *) ACU_PVT_BASE)
#define PVT1                    ((PVT_TypeDef *) (ACU_PVT_BASE + 0x1000))
#define EFUSE                   ((EFUSE_TypeDef *) (ACU_PVT_BASE + 0x2000))

#define GPIO0                   ((GPIO_TypeDef *) (ACU_GPIO_BASE))
#define GPIO1                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 1))
#define GPIO2                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 2))
#define GPIO3                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 3))
#define GPIO4                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 4))
#define GPIO5                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 5))
#define GPIO6                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 6))
#define GPIO7                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 7))
#define GPIO8                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 8))
#define GPIO9                   ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 9))
#define GPIO10                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 10))
#define GPIO11                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 11))
#define GPIO12                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 12))
#define GPIO13                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 13))
#define GPIO14                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 14))
#define GPIO15                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 15))
#define GPIO16                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 16))
#define GPIO17                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 17))
#define GPIO18                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 18))
#define GPIO19                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 19))
#define GPIO20                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 20))
#define GPIO21                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 21))
#define GPIO22                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 22))
#define GPIO23                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 23))
#define GPIO24                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 24))
#define GPIO25                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 25))
#define GPIO26                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 26))
#define GPIO27                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 27))
#define GPIO28                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 28))
#define GPIO29                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 29))
#define GPIO30                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 30))
#define GPIO31                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 31))
#define GPIO32                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 32))
#define GPIO33                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 33))
#define GPIO34                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 34))
#define GPIO35                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 35))
#define GPIO36                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 36))
#define GPIO37                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 37))
#define GPIO38                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 38))
#define GPIO39                  ((GPIO_TypeDef *) (ACU_GPIO_BASE + 0x40 * 39))
#define GPIO_IR                 ((GPIO_IRTypeDef *) ACU_GPIO_IR_BASE)
#define IS_GPIO_ALL_PERIPH(PERIPH)  (((PERIPH) == GPIO0) || ((PERIPH) == GPIO1) || \
                                    ((PERIPH) == GPIO2) || ((PERIPH) == GPIO3) || \
                                    ((PERIPH) == GPIO4) || ((PERIPH) == GPIO5) || \
                                    ((PERIPH) == GPIO6) || ((PERIPH) == GPIO7) || \
                                    ((PERIPH) == GPIO8) || ((PERIPH) == GPIO9) || \
                                    ((PERIPH) == GPIO10) || ((PERIPH) == GPIO11) || \
                                    ((PERIPH) == GPIO12) || ((PERIPH) == GPIO13) || \
                                    ((PERIPH) == GPIO14) || ((PERIPH) == GPIO15) || \
                                    ((PERIPH) == GPIO16) || ((PERIPH) == GPIO17) || \
                                    ((PERIPH) == GPIO18) || ((PERIPH) == GPIO19) || \
                                    ((PERIPH) == GPIO20) || ((PERIPH) == GPIO21) || \
                                    ((PERIPH) == GPIO22) || ((PERIPH) == GPIO23) || \
                                    ((PERIPH) == GPIO24) || ((PERIPH) == GPIO25) || \
                                    ((PERIPH) == GPIO26) || ((PERIPH) == GPIO27) || \
                                    ((PERIPH) == GPIO28) || ((PERIPH) == GPIO29) || \
                                    ((PERIPH) == GPIO30) || ((PERIPH) == GPIO31) || \
                                    ((PERIPH) == GPIO32) || ((PERIPH) == GPIO33) || \
                                    ((PERIPH) == GPIO34) || ((PERIPH) == GPIO35) || \
                                    ((PERIPH) == GPIO36) || ((PERIPH) == GPIO37) || \
                                    ((PERIPH) == GPIO38) || ((PERIPH) == GPIO39))

/*<! APB Peripheral Clk&Rest Control */
#define RST_SC                  ((CHIPRST_TypeDef *) ACU_RSTSC_BASE)
#define I2C_SC                  ((APBSYS_TypeDef *) ACU_I2CSC_BASE)
#define UART_SC                 ((APBSYS_TypeDef *) ACU_UARTSC_BASE)
#define GPIO_SC                 ((APBSYS_TypeDef *) ACU_GPIOSC_BASE)
#define SPI_SC                  ((APBSYS_TypeDef *) ACU_SSPSC_BASE)
#define TIM_SC                  ((APBSYS_TypeDef *) ACU_TIMSC_BASE)
#define WDT_SC                  ((APBSYS_TypeDef *) ACU_WDTSC_BASE)
#define CU_SC                   ((APBSYS_TypeDef *) ACU_CUSC_BASE)
#define PVT_SC                  ((APBSYS_TypeDef *) ACU_PVTSC_BASE)
#define PCIE_SC                 ((PCIE_TypeDef *) ACU_PCIESC_BASE)
#define IS_RCC_APB_PERIPH(periph)   (((periph) == I2C_SC) || ((periph) == UART_SC) || \
                                    ((periph) == GPIO_SC) || ((periph) == SPI_SC) || \
                                    ((periph) == TIM_SC) || ((periph) == WDT_SC) || \
                                    ((periph) == CU_SC) || ((periph) == PVT_SC) || \
                                    ((periph) == PCIE_SC))
                                    
/*<! AHB Peripheral Clk&Rest Control */
#define IS_RCC_AHB_PERIPH(periph)   (periph)

/*<! AXI Peripheral Clk&Rest Control */
#define IROM_SC                 ((IMEMC_TypeDef *) ACU_IROMSC_BASE)
#define IRAM_SC                 ((IMEMC_TypeDef *) ACU_IRAMSC_BASE)
#define IS_RCC_AXI_PERIPH(periph)   (((periph) == IROM_SC) || ((periph) == IRAM_SC))

/*<! IOPAD System Control */
#define IOPAD_MUX               ((IOPAD_TypeDef *) ACU_IOPADSC_BASE)

/*<! Boot Mode Flag Register */
#define BOOTMODE                ((BMIO_TypeDef *) ACU_BMIO_BASE)

/*<! System Clock Control */
#define APLL_CLK                ((PLLCLK_TypeDef *) (ACU_CLKSC_BASE))
#define BPLL_CLK                ((PLLCLK_TypeDef *) (ACU_CLKSC_BASE + 0x30))
#define CPLL_CLK                ((PLLCLK_TypeDef *) (ACU_CLKSC_BASE + 0x60))
#define DPLL_CLK                ((PLLCLK_TypeDef *) (ACU_CLKSC_BASE + 0x90))
#define IS_PLL_CLK(CLK)         (((CLK) == APLL_CLK) || ((CLK) == BPLL_CLK) ||\
                                ((CLK) == CPLL_CLK) || ((CLK) == DPLL_CLK))

#define FABRIC_CLK              ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0xC0))
#define IPCORE_CLK              ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0xD0))
#define DDR_CLK                 ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0xE0))
#define HASHCORE_CLK            ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0xF0))
#define DDR1_CLK                ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0x100))
#define EFUSE_CLK               ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0x110))
#define IS_RCC_SYSCLK(clock)    (((clock) == FABRIC_CLK) || ((clock) == IPCORE_CLK) || \
                                ((clock) == DDR_CLK) || ((clock) == HASHCORE_CLK) || \
                                ((clock) == DDR1_CLK) || ((clock) == EFUSE_CLK))

/*<! Cortex M3 Control */
#define CM3_SC                  ((CM3SYS_TypeDef *) ACU_M3SC_BASE)

/* ================================================================================ */
/* ================           Application_memory_map               ================ */
/* ================================================================================ */
#define ACU_ROM_SIZE            0x8000
#define ACU_RAM_SIZE            0x28000

#define ACU_GLOBAL_BUF_SIZE     0x1000
#define ACU_GLOBAL_BUF_ADDR     (ACU_RAM_BASE + ACU_RAM_SIZE - ACU_GLOBAL_BUF_SIZE)


/* ================================================================================ */
/* ================               Includes Headfile                ================ */
/* ================================================================================ */

/* Includes driver headfile*/
#include "acu_gpio.h"
#include "acu_i2c.h"
#include "acu_wdt.h"
#include "acu_pcie.h"
#include "acu_ddr.h"
#include "acu_ddr_init.h"
#include "acu_ddr_init_fpga.h"
#include "acu_rcc.h"
#include "acu_spi_flash.h"
#include "acu_spi.h"
#include "acu_tim.h"
#include "acu_pvt.h"
#include "acu_efuse.h"
#include "acu_uart.h"
#include "acu_int_gen.h"
#include "acu_misc.h"
#include "acu_debug.h"
#include "system_acu.h"

#ifdef __cplusplus
}
#endif

#endif /* __ACU_H */

