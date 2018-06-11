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
    I2C0_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
    I2C1_IRQn                   = 1,      /*!< PVD through EXTI Line detection Interrupt            */
    GPIO_IRQn                   = 2,      /*!< Tamper Interrupt                                     */
    UART_IRQn                   = 3,      /*!< RTC global Interrupt                                 */
    SSP_IRQn                    = 4,      /*!< FLASH global Interrupt                               */
    RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
    TIMER0_IRQn                 = 6,      /*!< EXTI Line0 Interrupt                                 */
    TIMER1_IRQn                 = 7,      /*!< EXTI Line1 Interrupt                                 */
    WDT_IRQn                    = 8,      /*!< EXTI Line2 Interrupt                                 */
    EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
    RESERVED0_IRQn              = 10,     /*!< EXTI Line4 Interrupt                                 */
    RESERVED1_IRQn              = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
    RESERVED2_IRQn              = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
    RESERVED3_IRQn              = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
    RESERVED4_IRQn              = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
    RESERVED5_IRQn              = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
    RESERVED6_IRQn              = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
    RESERVED7_IRQn              = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
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
    __IO uint32_t CON;                     /*!< Offset: 0x000 Control Register (R/W) */
    __I  uint32_t TAR;                    /*!< Offset: 0x004 Target Register (R/ ) */
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
    __I  uint32_t RAW_INTR_MASK;          /*!< Offset: 0x034 Raw Interrupt Status Register (R/ ) */
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
} IOPAD_TypeDef;

/* brief General Purpose I/O */
typedef struct
{
    __IO uint32_t IR;
    __IO uint32_t OR;
    __IO uint32_t DR;
    __IO uint32_t GIMR;
    __IO uint32_t GPIMR;
    __IO uint32_t PIR;
    __IO uint32_t ITR;
    __IO uint32_t IFR;
    __IO uint32_t ICR;
    __IO uint32_t PUDE;
    uint32_t  RESERVED1[6];
} GPIO_TypeDef;

/* brief General Purpose I/O interrupt status */
typedef struct
{
    __I  uint16_t GPIR;                   /*!< Offset: 0x000 GOIO INT Status Register (R/ ) */
} GPIO_IRTypeDef;

/* brief Independent WATCHDOG */
typedef struct
{
    __IO uint32_t CR;                     /*!< Offset: 0x000 Control Register (R/W) */
    __IO uint32_t TORR;                   /*!< Offset: 0x004 Timeout Range Register (R/W) */
    __I  uint32_t CCVR;                   /*!< Offset: 0x008 Current Counter Value Register (R/ ) */
    __O  uint32_t CRR;                    /*!< Offset: 0x00C Counter Restart Register ( /W) */
    __I  uint32_t STAT;                   /*!< Offset: 0x010 Interrupt Status Register (R/ ) */
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
} CHIPRST_TypeDef;

/* Clock System Management */
typedef struct
{
    __IO uint32_t CLKSRC;                 /*!< Offset: 0x080 Fabric clock ClkGen Clock Source Register (R/W) */
    __IO uint32_t CLKRATIO;               /*!< Offset: 0x084 Fabric clock ClkGen Clock Divider Register (R/W) */
       uint8_t  RESERVED2[4];
    __IO uint32_t CLKGT;                  /*!< Offset: 0x08C Fabric clock ClkGen Clock Gate Register (R/W) */
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
} APBSYS_TypeDef;

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
#define ACU_UART_BASE           (ACU_APB_BASE + 0x10000)
#define ACU_GPIO_BASE           (ACU_APB_BASE + 0x20000)
#define ACU_SSP_BASE            (ACU_APB_BASE + 0x30000)
#define ACU_TIM0_BASE           (ACU_APB_BASE + 0x40000)
#define ACU_TIM1_BASE           (ACU_APB_BASE + 0x40014)
#define ACU_WDT_BASE            (ACU_APB_BASE + 0x50000)
#define ACU_SYS_BASE            (ACU_APB_BASE + 0x60000)
#define ACU_PVT_BASE            (ACU_APB_BASE + 0x70000)

#define ACU_GPIO_IR0_BASE       (ACU_GPIO_BASE + 0x4000)
#define ACU_GPIO_IR1_BASE       (ACU_GPIO_BASE + 0x4004)

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
#define ACU_M3SC_BASE           (ACU_SYS_BASE + 0x0A000)
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

/*<! APB Peripheral module declaration */
#define I2C0                    ((I2C_TypeDef *) ACU_I2C0_BASE)
#define I2C1                    ((I2C_TypeDef *) ACU_I2C1_BASE)
#define UART                    ((UART_TypeDef *) ACU_UART_BASE)
#define SPI                     ((SPI_TypeDef *) ACU_SSP_BASE)
#define TIM0                    ((TIM_TypeDef *) ACU_TIM0_BASE)
#define TIM1                    ((TIM_TypeDef *) ACU_TIM1_BASE)
#define WDT                     ((WDT_TypeDef *) ACU_WDT_BASE)

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
#define GPIR0                   ((GPIO_IRTypeDef *) ACU_GPIO_IR0_BASE)
#define GPIR1                   ((GPIO_IRTypeDef *) ACU_GPIO_IR1_BASE)
#define IS_GPIO_ALL_PERIPH(PERIPH)      (((PERIPH) == GPIO0) || ((PERIPH) == GPIO1) || \
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
                                        ((PERIPH) == GPIO26))

/*<! APB Peripheral Clk&Rest Control */
#define RST_SC                  ((CHIPRST_TypeDef *) ACU_RSTSC_BASE)
#define I2C_SC                  ((APBSYS_TypeDef *) ACU_I2CSC_BASE)
#define UART_SC                 ((APBSYS_TypeDef *) ACU_UARTSC_BASE)
#define GPIO_SC                 ((APBSYS_TypeDef *) ACU_GPIOSC_BASE)
#define SPI_SC                  ((APBSYS_TypeDef *) ACU_SSPSC_BASE)
#define TIM_SC                  ((APBSYS_TypeDef *) ACU_TIMSC_BASE)
#define WDT_SC                  ((APBSYS_TypeDef *) ACU_WDTSC_BASE)
#define IS_RCC_APB_PERIPH(periph)   (((periph) == I2C_SC) || ((periph) == UART_SC) || \
                                    ((periph) == GPIO_SC) || ((periph) == SPI_SC) || \
                                    ((periph) == TIM_SC) || ((periph) == WDT_SC))
                                    
/*<! AHB Peripheral Clk&Rest Control */
#define IS_RCC_AHB_PERIPH(periph)   (periph)

/*<! AXI Peripheral Clk&Rest Control */
#define IROM_SC                 ((IMEMC_TypeDef *) ACU_IROMSC_BASE)
#define IRAM_SC                 ((IMEMC_TypeDef *) ACU_IRAMSC_BASE)
#define IS_RCC_AXI_PERIPH(periph)   (((periph) == IROM_SC) || ((periph) == IRAM_SC))

/*<! IOPAD System Control */
#define IOPAD_SC                ((IOPAD_TypeDef *) ACU_IOPADSC_BASE)

/*<! Boot Mode Flag Register */
#define BOOTMODE                ((BMIO_TypeDef *) ACU_BMIO_BASE)

/*<! System Clock Control */
#define FABRIC_SC               ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0x80))
#define PCIE_SC                 ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0x90))
#define IPCORE_SC               ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0xA0))
#define DDR_SC                  ((CLK_TypeDef *) (ACU_CLKSC_BASE + 0xB0))
#define IS_RCC_SYSCLK(clock)    (((clock) == FABRIC_SC) || ((clock) == PCIE_SC) || \
                                ((clock) == IPCORE_SC) || ((clock) == DDR_SC))

/*<! Cortex M3 Control */
#define CM3_SC              ((CM3SYS_TypeDef *) ACU_M3SC_BASE)

/* ================================================================================ */
/* ================               Includes Headfile                ================ */
/* ================================================================================ */

/* Includes driver headfile*/
#include "acu_gpio.h"
#include "acu_i2c.h"
#include "acu_wdg.h"
#include "acu_rcc.h"
#include "acu_spi_flash.h"
#include "acu_spi.h"
#include "acu_tim.h"
#include "acu_uart.h"
#include "acu_misc.h"
#include "acu_debug.h"

#ifdef __cplusplus
}
#endif

#endif /* __ACU_H */
