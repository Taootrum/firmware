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
    /* Init the Debug Uart */
    Debug_Init();
    /* Init the SPI Flash */
    sFLASH_Init();
    
    DEBUG_MSG("Version: %s (%s/%s)\r\n\r\n", acu_version, __DATE__, __TIME__);
    /* Enable all interrupt */
    __set_PRIMASK(0);

#ifdef ACU_UPDATE
    ACU_FlashUpdate();
#endif

    /* Infinite loop */
    while (1)
    {
        /* function test */
#ifdef ACU_TEST
        ACU_HalFuncTest();
#endif

#ifdef SIM_DEBUG
        SIM_END;
#endif
        return 1;
    }
}

