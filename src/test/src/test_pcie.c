/*******************************************************************************
  * @file    test_pcie.h
  * @author  Denglin SOC Team
  * @version V1.0.0
  * @date    20-Augest-2018
  * @brief   ACU PCIE Function. 
 ******************************************************************************/
#include "test_pcie.h"

/****************************************************************
  * 函数      : PCIE_FunctionTestX()
  * 参数      : None
  * 返回值     : TRUE or FALSE
  * 描述      : PCIE function test cases.
 ***************************************************************/
/* pcie_reg_default_test */
TestStatus PCIE_FunctionTest1(void)
{    
    BoolStatus result = TRUE;
    
    PCIE_Init();
    /* check */
    result &= CHECK_REG_RESERVED(READ32(0x40000000), 0x11E27);
    result &= CHECK_REG_RESERVED(READ32(0x40000008), 0x1);
    result &= CHECK_REG_RESERVED(READ32(0x4000000C), 0x0);
    result &= CHECK_REG_RESERVED(READ32(0x40000010), 0x0);
    result &= CHECK_REG_RESERVED(READ32(0x40000014), 0x1000000);
    result &= CHECK_REG_RESERVED(READ32(0x40000018), 0x10000000);
    result &= CHECK_REG_RESERVED(READ32(0x4000001C), 0x20000000);
    result &= CHECK_REG_RESERVED(READ32(0x40000020), 0x30000000);
    result &= CHECK_REG_RESERVED(READ32(0x40000024), 0x40000000);
    result &= CHECK_REG_RESERVED(READ32(0x40000028), 0x0);
    result &= CHECK_REG_RESERVED(READ32(0x4000002C), 0x0);
    result &= CHECK_REG_RESERVED(READ32(0x40000030), 0x0);
    result &= CHECK_REG_RESERVED(READ32(0x40000034), 0x40);
    result &= CHECK_REG_RESERVED(READ32(0x4000003C), 0x1FF);
    if (result != TRUE)
    {
        DEBUG_ERROR("pcie_reg_default_test fail.");
        return FAILED;
    }

    return PASSED;
}

/* pcie_reg_test */
TestStatus PCIE_FunctionTest2(void)
{
    BoolStatus result = TRUE;

    PCIE_Init();

    /* check */
    WRITE32(0x40000028, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x40000028), 0x0);
    WRITE32(0x4000002C, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000002C), 0x0);
    WRITE32(0x40000030, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x40000030), 0xFFFF0001);
    WRITE32(0x40000034, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x40000034), 0x40);
    WRITE32(0x4000003C, 0x0);
    result &= CHECK_REG_RESERVED(READ32(0x4000003C), 0x100);
    WRITE32(0x40000030, 0x0);
    WRITE32(0x4000003C, 0x1FF);
    if (result != TRUE)
    {
        DEBUG_ERROR("pcie_reg_test fail.");
        return FAILED;
    }

    return PASSED;
}

/* pcie_for_iATU */
TestStatus PCIE_FunctionTest3(void)
{
    BoolStatus result = TRUE;

    PCIE_Init();

    /* check */
    WRITE32(0x4000c000, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000c000), 0x007027FF);
    WRITE32(0x4000c004, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000c004), 0xB0F9FFFF);
    WRITE32(0x4000c014, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000c014), 0xFFFFFFFF);
    WRITE32(0x4000c114, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000c114), 0xFFFF0000);
    WRITE32(0x4000c118, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000c118), 0x0);
    WRITE32(0x4000c11C, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000c11C), 0x0);
    WRITE32(0x4000c120, 0xFFFFFFFF);
    result &= CHECK_REG_RESERVED(READ32(0x4000c120), 0x0);
    PCIE_DeInit();
    if (result != TRUE)
    {
        DEBUG_ERROR("pcie_for_iATU fail.");
        return FAILED;
    }

    return PASSED;
}

/* pcie_phy_test */
TestStatus PCIE_FunctionTest4(void)
{
    BoolStatus result = TRUE;

    PCIE_Init();
    WRITE_REG(PCIE_SC->DBI_SEL, 0x1);

    /* check default */
    result &= CHECK_REG_RESERVED(READ16(0x40000000), 0x74CD);
    result &= CHECK_REG_RESERVED(READ16(0x40000004), 0xA21C);
    result &= CHECK_REG_RESERVED(READ16(0x40000008), 0x000A);
    result &= CHECK_REG_RESERVED(READ16(0x400000E4), 0x0000);
    result &= CHECK_REG_RESERVED(READ16(0x40004000), 0x0000);
    result &= CHECK_REG_RESERVED(READ16(0x40004004), 0x0000);
    result &= CHECK_REG_RESERVED(READ16(0x40004104), 0x0018);
    result &= CHECK_REG_RESERVED(READ16(0x40004108), 0x0040);
    
    /* check */
    WRITE16(0x40000000, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x40000000), 0x74CD);
    WRITE16(0x40000004, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x40000004), 0xA21C);
    WRITE16(0x40000008, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x40000008), 0x007F);
    WRITE16(0x400000E4, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x400000E4), 0x00FF);
    WRITE16(0x40004000, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x40004000), 0x3FFF);
    WRITE16(0x40004004, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x40004004), 0x03FF);
    WRITE16(0x40004104, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x40004104), 0x01FF);
    WRITE16(0x40004108, 0xFFFF);
    result &= CHECK_REG_RESERVED(READ16(0x40004108), 0x01FF);
    WRITE_REG(PCIE_SC->DBI_SEL, 0x0);
    PCIE_DeInit();
    if (result != TRUE)
    {
        DEBUG_ERROR("pcie_phy_test fail.");
        return FAILED;
    }

    return PASSED;
}

/* PCIE system management registers */
TestStatus PCIE_FunctionTest5(void)
{
    uint32_t TempReg2 = 0, TempReg3 = 0;
    TestStatus ret = PASSED;

    TempReg2 = READ_REG(PCIE_SC->REGISTER2);
    TempReg3 = READ_REG(PCIE_SC->REGISTER3);
    WRITE_REG(PCIE_SC->REGISTER2, 0xFF);
    WRITE_REG(PCIE_SC->REGISTER3, 0xFF);
    if (0xFF != READ_REG(PCIE_SC->REGISTER2) || 0xFF != READ_REG(PCIE_SC->REGISTER3))
    {
        DEBUG_ERROR("PCIE access system management registers fail.");
        ret =  FAILED;
    }
    WRITE_REG(PCIE_SC->REGISTER2, TempReg2);
    WRITE_REG(PCIE_SC->REGISTER3, TempReg3);

    return ret;
}

/* ELBI write&read access */
TestStatus PCIE_FunctionTest6(void)
{
    uint32_t TempMask = 0;
    TestStatus ret = PASSED;

    PCIE_Init();
    
    TempMask = READ_REG(CU->CQ_IRQ_MASK);
    ELBI_WriteAccess(ACU_CU_BASE + 0x108, 0x1F);
    if (0x1F != ELBI_ReadAccess(ACU_CU_BASE + 0x108))
    {
        DEBUG_ERROR("ELBI write access fail.");
        ret = FAILED;
    }
    WRITE_REG(CU->CQ_IRQ_MASK, TempMask);
    
    return ret;
}

