/*******************************************************************************
  * @file    main.c
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    11-MAY-2018
  * @brief   user application file.
 ******************************************************************************/
#include "acu.h"
#include "spi_flash.h"
#include "timer.h"
#include "test.h"

static const char *acu_version = "ACU_FW_V0.0.1";

/****************************************************************
  * 函数      : main()
  * 参数      : None
  * 返回值     : None
  * 描述      : 系统主函数
 ***************************************************************/
int main(void)
{    
    /* system clock update */
    SystemCoreClockUpdate();
    /* configuration systick */
    SysTick_Init();
    /* Initialize the Uart */
    Debug_Init();
    /* Init the SPI Flash */
    sFLASH_Init();
    /* Init the PCIE */
    //PCIE_Init();
    
    /* Init the DDRC */
#ifdef ACU_SIM
    //DDRC_Init();
#else
    //DDRC_FPGAInit();
#endif

    DEBUG_MSG("Version: %s (%s/%s)"LF LF, acu_version, __DATE__, __TIME__);

    /* Enable all interrupt */
    __set_PRIMASK(0);

    /* Infinite loop */
    while (1)
    {
#ifdef ACU_UPDATE
        /* update flash */
        ACU_FlashUpdate();
#endif

#ifdef ACU_TEST
        /* function test */
        ACU_HalFuncTest();
#endif
        
#ifdef ACU_SIM
        SIM_END;
#endif
        return 1;
    }
}

