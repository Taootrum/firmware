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

/****************************************************************
  * 函数      : main()
  * 参数      : None
  * 返回值     : None
  * 描述      : 系统主函数，执行boot启动功能
 ***************************************************************/
int main(void)
{        
    /* Init the Debug Uart */
    Debug_Init();
    DEBUG_MSG("firmware main start!\r\n");

    /* Init the SPI Flash */
    sFLASH_Init();
    /* Enable all interrupt */
    __set_PRIMASK(0);

    /* function test */
#ifdef ACU_TEST
    ACU_FirmWareTest();
#endif

#ifdef SIM_DEBUG
    SIM_END;
#endif

    /* Infinite loop */
    while (1)
    {
    }
}

