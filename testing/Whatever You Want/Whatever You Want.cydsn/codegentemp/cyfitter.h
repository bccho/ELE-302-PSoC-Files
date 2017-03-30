#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* Counter_CounterHW */
#define Counter_CounterHW__CAP0 CYREG_TMR0_CAP0
#define Counter_CounterHW__CAP1 CYREG_TMR0_CAP1
#define Counter_CounterHW__CFG0 CYREG_TMR0_CFG0
#define Counter_CounterHW__CFG1 CYREG_TMR0_CFG1
#define Counter_CounterHW__CFG2 CYREG_TMR0_CFG2
#define Counter_CounterHW__CNT_CMP0 CYREG_TMR0_CNT_CMP0
#define Counter_CounterHW__CNT_CMP1 CYREG_TMR0_CNT_CMP1
#define Counter_CounterHW__PER0 CYREG_TMR0_PER0
#define Counter_CounterHW__PER1 CYREG_TMR0_PER1
#define Counter_CounterHW__PM_ACT_CFG CYREG_PM_ACT_CFG3
#define Counter_CounterHW__PM_ACT_MSK 0x01u
#define Counter_CounterHW__PM_STBY_CFG CYREG_PM_STBY_CFG3
#define Counter_CounterHW__PM_STBY_MSK 0x01u
#define Counter_CounterHW__RT0 CYREG_TMR0_RT0
#define Counter_CounterHW__RT1 CYREG_TMR0_RT1
#define Counter_CounterHW__SR0 CYREG_TMR0_SR0

/* LCD_LCDPort */
#define LCD_LCDPort__0__MASK 0x01u
#define LCD_LCDPort__0__PC CYREG_PRT2_PC0
#define LCD_LCDPort__0__PORT 2
#define LCD_LCDPort__0__SHIFT 0
#define LCD_LCDPort__1__MASK 0x02u
#define LCD_LCDPort__1__PC CYREG_PRT2_PC1
#define LCD_LCDPort__1__PORT 2
#define LCD_LCDPort__1__SHIFT 1
#define LCD_LCDPort__2__MASK 0x04u
#define LCD_LCDPort__2__PC CYREG_PRT2_PC2
#define LCD_LCDPort__2__PORT 2
#define LCD_LCDPort__2__SHIFT 2
#define LCD_LCDPort__3__MASK 0x08u
#define LCD_LCDPort__3__PC CYREG_PRT2_PC3
#define LCD_LCDPort__3__PORT 2
#define LCD_LCDPort__3__SHIFT 3
#define LCD_LCDPort__4__MASK 0x10u
#define LCD_LCDPort__4__PC CYREG_PRT2_PC4
#define LCD_LCDPort__4__PORT 2
#define LCD_LCDPort__4__SHIFT 4
#define LCD_LCDPort__5__MASK 0x20u
#define LCD_LCDPort__5__PC CYREG_PRT2_PC5
#define LCD_LCDPort__5__PORT 2
#define LCD_LCDPort__5__SHIFT 5
#define LCD_LCDPort__6__MASK 0x40u
#define LCD_LCDPort__6__PC CYREG_PRT2_PC6
#define LCD_LCDPort__6__PORT 2
#define LCD_LCDPort__6__SHIFT 6
#define LCD_LCDPort__AG CYREG_PRT2_AG
#define LCD_LCDPort__AMUX CYREG_PRT2_AMUX
#define LCD_LCDPort__BIE CYREG_PRT2_BIE
#define LCD_LCDPort__BIT_MASK CYREG_PRT2_BIT_MASK
#define LCD_LCDPort__BYP CYREG_PRT2_BYP
#define LCD_LCDPort__CTL CYREG_PRT2_CTL
#define LCD_LCDPort__DM0 CYREG_PRT2_DM0
#define LCD_LCDPort__DM1 CYREG_PRT2_DM1
#define LCD_LCDPort__DM2 CYREG_PRT2_DM2
#define LCD_LCDPort__DR CYREG_PRT2_DR
#define LCD_LCDPort__INP_DIS CYREG_PRT2_INP_DIS
#define LCD_LCDPort__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define LCD_LCDPort__LCD_EN CYREG_PRT2_LCD_EN
#define LCD_LCDPort__MASK 0x7Fu
#define LCD_LCDPort__PORT 2
#define LCD_LCDPort__PRT CYREG_PRT2_PRT
#define LCD_LCDPort__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define LCD_LCDPort__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define LCD_LCDPort__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define LCD_LCDPort__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define LCD_LCDPort__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define LCD_LCDPort__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define LCD_LCDPort__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define LCD_LCDPort__PS CYREG_PRT2_PS
#define LCD_LCDPort__SHIFT 0
#define LCD_LCDPort__SLW CYREG_PRT2_SLW

/* PWM_PWMUDB */
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB14_15_ACTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB14_15_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB14_15_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB14_15_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_COUNT_REG CYREG_B0_UDB14_15_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_MASK_REG CYREG_B0_UDB14_15_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_PERIOD_REG CYREG_B0_UDB14_15_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_MASK_REG CYREG_B0_UDB14_15_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB14_15_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__7__MASK 0x80u
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__7__POS 7
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_AUX_CTL_REG CYREG_B0_UDB14_ACTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG CYREG_B0_UDB14_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_ST_REG CYREG_B0_UDB14_ST_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_REG CYREG_B0_UDB14_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_ST_REG CYREG_B0_UDB14_ST_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__MASK 0x80u
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__PERIOD_REG CYREG_B0_UDB14_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__PER_CTL_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG CYREG_B0_UDB14_15_A0
#define PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG CYREG_B0_UDB14_15_A1
#define PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG CYREG_B0_UDB14_15_D0
#define PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG CYREG_B0_UDB14_15_D1
#define PWM_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB14_15_ACTL
#define PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG CYREG_B0_UDB14_15_F0
#define PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG CYREG_B0_UDB14_15_F1
#define PWM_PWMUDB_sP8_pwmdp_u0__A0_A1_REG CYREG_B0_UDB14_A0_A1
#define PWM_PWMUDB_sP8_pwmdp_u0__A0_REG CYREG_B0_UDB14_A0
#define PWM_PWMUDB_sP8_pwmdp_u0__A1_REG CYREG_B0_UDB14_A1
#define PWM_PWMUDB_sP8_pwmdp_u0__D0_D1_REG CYREG_B0_UDB14_D0_D1
#define PWM_PWMUDB_sP8_pwmdp_u0__D0_REG CYREG_B0_UDB14_D0
#define PWM_PWMUDB_sP8_pwmdp_u0__D1_REG CYREG_B0_UDB14_D1
#define PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG CYREG_B0_UDB14_ACTL
#define PWM_PWMUDB_sP8_pwmdp_u0__F0_F1_REG CYREG_B0_UDB14_F0_F1
#define PWM_PWMUDB_sP8_pwmdp_u0__F0_REG CYREG_B0_UDB14_F0
#define PWM_PWMUDB_sP8_pwmdp_u0__F1_REG CYREG_B0_UDB14_F1
#define PWM_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define PWM_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__0__MASK 0x01u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__0__POS 0
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB14_15_ACTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__16BIT_STATUS_REG CYREG_B0_UDB14_15_ST
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__2__MASK 0x04u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__2__POS 2
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__3__MASK 0x08u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__3__POS 3
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__5__MASK 0x20u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__5__POS 5
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK 0x2Du
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG CYREG_B0_UDB14_MSK
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_ST_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__PER_ST_AUX_CTL_REG CYREG_B0_UDB14_MSK_ACTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG CYREG_B0_UDB14_ACTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_CNT_REG CYREG_B0_UDB14_ST_CTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_CONTROL_REG CYREG_B0_UDB14_ST_CTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG CYREG_B0_UDB14_ST

/* Clock_1 */
#define Clock_1__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define Clock_1__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define Clock_1__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define Clock_1__CFG2_SRC_SEL_MASK 0x07u
#define Clock_1__INDEX 0x00u
#define Clock_1__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define Clock_1__PM_ACT_MSK 0x01u
#define Clock_1__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define Clock_1__PM_STBY_MSK 0x01u

/* inter_1 */
#define inter_1__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define inter_1__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define inter_1__INTC_MASK 0x01u
#define inter_1__INTC_NUMBER 0
#define inter_1__INTC_PRIOR_NUM 7
#define inter_1__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define inter_1__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define inter_1__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* inter_2 */
#define inter_2__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define inter_2__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define inter_2__INTC_MASK 0x02u
#define inter_2__INTC_NUMBER 1
#define inter_2__INTC_PRIOR_NUM 7
#define inter_2__INTC_PRIOR_REG CYREG_NVIC_PRI_1
#define inter_2__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define inter_2__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Pin_1 */
#define Pin_1__0__MASK 0x02u
#define Pin_1__0__PC CYREG_PRT6_PC1
#define Pin_1__0__PORT 6
#define Pin_1__0__SHIFT 1
#define Pin_1__AG CYREG_PRT6_AG
#define Pin_1__AMUX CYREG_PRT6_AMUX
#define Pin_1__BIE CYREG_PRT6_BIE
#define Pin_1__BIT_MASK CYREG_PRT6_BIT_MASK
#define Pin_1__BYP CYREG_PRT6_BYP
#define Pin_1__CTL CYREG_PRT6_CTL
#define Pin_1__DM0 CYREG_PRT6_DM0
#define Pin_1__DM1 CYREG_PRT6_DM1
#define Pin_1__DM2 CYREG_PRT6_DM2
#define Pin_1__DR CYREG_PRT6_DR
#define Pin_1__INP_DIS CYREG_PRT6_INP_DIS
#define Pin_1__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define Pin_1__LCD_EN CYREG_PRT6_LCD_EN
#define Pin_1__MASK 0x02u
#define Pin_1__PORT 6
#define Pin_1__PRT CYREG_PRT6_PRT
#define Pin_1__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define Pin_1__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define Pin_1__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define Pin_1__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define Pin_1__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define Pin_1__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define Pin_1__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define Pin_1__PS CYREG_PRT6_PS
#define Pin_1__SHIFT 1
#define Pin_1__SLW CYREG_PRT6_SLW

/* Pin_2 */
#define Pin_2__0__MASK 0x04u
#define Pin_2__0__PC CYREG_PRT6_PC2
#define Pin_2__0__PORT 6
#define Pin_2__0__SHIFT 2
#define Pin_2__AG CYREG_PRT6_AG
#define Pin_2__AMUX CYREG_PRT6_AMUX
#define Pin_2__BIE CYREG_PRT6_BIE
#define Pin_2__BIT_MASK CYREG_PRT6_BIT_MASK
#define Pin_2__BYP CYREG_PRT6_BYP
#define Pin_2__CTL CYREG_PRT6_CTL
#define Pin_2__DM0 CYREG_PRT6_DM0
#define Pin_2__DM1 CYREG_PRT6_DM1
#define Pin_2__DM2 CYREG_PRT6_DM2
#define Pin_2__DR CYREG_PRT6_DR
#define Pin_2__INP_DIS CYREG_PRT6_INP_DIS
#define Pin_2__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define Pin_2__LCD_EN CYREG_PRT6_LCD_EN
#define Pin_2__MASK 0x04u
#define Pin_2__PORT 6
#define Pin_2__PRT CYREG_PRT6_PRT
#define Pin_2__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define Pin_2__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define Pin_2__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define Pin_2__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define Pin_2__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define Pin_2__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define Pin_2__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define Pin_2__PS CYREG_PRT6_PS
#define Pin_2__SHIFT 2
#define Pin_2__SLW CYREG_PRT6_SLW

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
#define CYDEV_CHIP_MEMBER_5B 3
#define CYDEV_CHIP_FAMILY_PSOC5 3
#define CYDEV_CHIP_DIE_PSOC5LP 3
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_PSOC5LP
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_LEOPARD 1
#define CYDEV_CHIP_DIE_PANTHER 2
#define CYDEV_CHIP_DIE_UNKNOWN 0
#define CYDEV_CHIP_FAMILY_PSOC3 1
#define CYDEV_CHIP_FAMILY_PSOC4 2
#define CYDEV_CHIP_FAMILY_UNKNOWN 0
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x2E123069
#define CYDEV_CHIP_MEMBER_3A 1
#define CYDEV_CHIP_MEMBER_5A 2
#define CYDEV_CHIP_MEMBER_UNKNOWN 0
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5B
#define CYDEV_CHIP_REVISION_3A_ES1 0
#define CYDEV_CHIP_REVISION_3A_ES2 1
#define CYDEV_CHIP_REVISION_3A_ES3 3
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
#define CYDEV_CHIP_REVISION_5A_ES0 0
#define CYDEV_CHIP_REVISION_5A_ES1 1
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
#define CYDEV_CHIP_REVISION_5B_ES 0
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5B_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_PSOC5LP_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0
#define CYDEV_CHIP_REV_LEOPARD_ES2 1
#define CYDEV_CHIP_REV_LEOPARD_ES3 3
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
#define CYDEV_CHIP_REV_PANTHER_ES0 0
#define CYDEV_CHIP_REV_PANTHER_ES1 1
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
#define CYDEV_CHIP_REV_PSOC5LP_ES 0
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_FORCE_ROUTE 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_REQXRES 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x20
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DMA_CHANNELS_AVAILABLE 24
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x1000
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x4000
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
