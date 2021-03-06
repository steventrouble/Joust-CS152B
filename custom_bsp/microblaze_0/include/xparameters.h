
/*******************************************************************
*
* CAUTION: This file is automatically generated by libgen.
* Version: Xilinx EDK 2013.2 EDK_P.68d
* DO NOT EDIT.
*
* Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.

* 
* Description: Driver parameters
*
*******************************************************************/

#define STDIN_BASEADDRESS 0x83E20000
#define STDOUT_BASEADDRESS 0x83E20000

/******************************************************************/


/* Definitions for peripheral AC97_IF_00_0 */
#define XPAR_AC97_IF_00_0_BASEADDR 0xCC800000
#define XPAR_AC97_IF_00_0_HIGHADDR 0xCC80FFFF


/* Definitions for peripheral INPUT_MODULE_0 */
#define XPAR_INPUT_MODULE_0_BASEADDR 0xC3A20000
#define XPAR_INPUT_MODULE_0_HIGHADDR 0xC3A2FFFF


/* Definitions for peripheral INPUT_MODULE_1 */
#define XPAR_INPUT_MODULE_1_BASEADDR 0xC3A00000
#define XPAR_INPUT_MODULE_1_HIGHADDR 0xC3A0FFFF


/* Definitions for peripheral PLBV46_PLBV46_BRIDGE_0 */
#define XPAR_PLBV46_PLBV46_BRIDGE_0_BRIDGE_BASEADDR 0x86200000
#define XPAR_PLBV46_PLBV46_BRIDGE_0_BRIDGE_HIGHADDR 0x8620FFFF
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG0_BASEADDR 0x81400000
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG0_HIGHADDR 0x8147FFFF
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG1_BASEADDR 0x83E00000
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG1_HIGHADDR 0x83E3FFFF
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG2_BASEADDR 0x86800000
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG2_HIGHADDR 0x86FFFFFF
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG3_BASEADDR 0xC3A00000
#define XPAR_PLBV46_PLBV46_BRIDGE_0_RNG3_HIGHADDR 0xC3A3FFFF


/* Definitions for peripheral USB_EPP_IF_0 */
#define XPAR_USB_EPP_IF_0_BASEADDR 0xC7000000
#define XPAR_USB_EPP_IF_0_HIGHADDR 0xC700FFFF


/* Definitions for peripheral XPS_EPC_0 */
#define XPAR_XPS_EPC_0_PRH0_BASEADDR 0x80800000
#define XPAR_XPS_EPC_0_PRH0_HIGHADDR 0x8080FFFF


/******************************************************************/

/* Definitions for driver GPIO */
#define XPAR_XGPIO_NUM_INSTANCES 4

/* Definitions for peripheral CHAR_LCD */
#define XPAR_CHAR_LCD_BASEADDR 0x81460000
#define XPAR_CHAR_LCD_HIGHADDR 0x8146FFFF
#define XPAR_CHAR_LCD_DEVICE_ID 0
#define XPAR_CHAR_LCD_INTERRUPT_PRESENT 0
#define XPAR_CHAR_LCD_IS_DUAL 0


/* Definitions for peripheral DIP_SWITCHES_8BIT */
#define XPAR_DIP_SWITCHES_8BIT_BASEADDR 0x81440000
#define XPAR_DIP_SWITCHES_8BIT_HIGHADDR 0x8144FFFF
#define XPAR_DIP_SWITCHES_8BIT_DEVICE_ID 1
#define XPAR_DIP_SWITCHES_8BIT_INTERRUPT_PRESENT 0
#define XPAR_DIP_SWITCHES_8BIT_IS_DUAL 0


/* Definitions for peripheral LEDS_8BIT */
#define XPAR_LEDS_8BIT_BASEADDR 0x81420000
#define XPAR_LEDS_8BIT_HIGHADDR 0x8142FFFF
#define XPAR_LEDS_8BIT_DEVICE_ID 2
#define XPAR_LEDS_8BIT_INTERRUPT_PRESENT 0
#define XPAR_LEDS_8BIT_IS_DUAL 0


/* Definitions for peripheral PUSH_BUTTONS_7BIT */
#define XPAR_PUSH_BUTTONS_7BIT_BASEADDR 0x81400000
#define XPAR_PUSH_BUTTONS_7BIT_HIGHADDR 0x8140FFFF
#define XPAR_PUSH_BUTTONS_7BIT_DEVICE_ID 3
#define XPAR_PUSH_BUTTONS_7BIT_INTERRUPT_PRESENT 0
#define XPAR_PUSH_BUTTONS_7BIT_IS_DUAL 0


/******************************************************************/

/* Canonical definitions for peripheral CHAR_LCD */
#define XPAR_GPIO_0_BASEADDR 0x81460000
#define XPAR_GPIO_0_HIGHADDR 0x8146FFFF
#define XPAR_GPIO_0_DEVICE_ID XPAR_CHAR_LCD_DEVICE_ID
#define XPAR_GPIO_0_INTERRUPT_PRESENT 0
#define XPAR_GPIO_0_IS_DUAL 0

/* Canonical definitions for peripheral DIP_SWITCHES_8BIT */
#define XPAR_GPIO_1_BASEADDR 0x81440000
#define XPAR_GPIO_1_HIGHADDR 0x8144FFFF
#define XPAR_GPIO_1_DEVICE_ID XPAR_DIP_SWITCHES_8BIT_DEVICE_ID
#define XPAR_GPIO_1_INTERRUPT_PRESENT 0
#define XPAR_GPIO_1_IS_DUAL 0

/* Canonical definitions for peripheral LEDS_8BIT */
#define XPAR_GPIO_2_BASEADDR 0x81420000
#define XPAR_GPIO_2_HIGHADDR 0x8142FFFF
#define XPAR_GPIO_2_DEVICE_ID XPAR_LEDS_8BIT_DEVICE_ID
#define XPAR_GPIO_2_INTERRUPT_PRESENT 0
#define XPAR_GPIO_2_IS_DUAL 0

/* Canonical definitions for peripheral PUSH_BUTTONS_7BIT */
#define XPAR_GPIO_3_BASEADDR 0x81400000
#define XPAR_GPIO_3_HIGHADDR 0x8140FFFF
#define XPAR_GPIO_3_DEVICE_ID XPAR_PUSH_BUTTONS_7BIT_DEVICE_ID
#define XPAR_GPIO_3_INTERRUPT_PRESENT 0
#define XPAR_GPIO_3_IS_DUAL 0


/******************************************************************/

/* Definitions for driver MPMC */
#define XPAR_XMPMC_NUM_INSTANCES 1

/* Definitions for peripheral DDR2_SDRAM */
#define XPAR_DDR2_SDRAM_DEVICE_ID 0
#define XPAR_DDR2_SDRAM_MPMC_CTRL_BASEADDR 0xFFFFFFFF
#define XPAR_DDR2_SDRAM_INCLUDE_ECC_SUPPORT 0
#define XPAR_DDR2_SDRAM_USE_STATIC_PHY 0
#define XPAR_DDR2_SDRAM_PM_ENABLE 0
#define XPAR_DDR2_SDRAM_NUM_PORTS 4
#define XPAR_DDR2_SDRAM_MEM_DATA_WIDTH 64
#define XPAR_DDR2_SDRAM_MEM_PART_NUM_BANK_BITS 2
#define XPAR_DDR2_SDRAM_MEM_PART_NUM_ROW_BITS 13
#define XPAR_DDR2_SDRAM_MEM_PART_NUM_COL_BITS 10
#define XPAR_DDR2_SDRAM_MEM_TYPE DDR2
#define XPAR_DDR2_SDRAM_ECC_SEC_THRESHOLD 1
#define XPAR_DDR2_SDRAM_ECC_DEC_THRESHOLD 1
#define XPAR_DDR2_SDRAM_ECC_PEC_THRESHOLD 1
#define XPAR_DDR2_SDRAM_MEM_DQS_WIDTH 8
#define XPAR_DDR2_SDRAM_MPMC_CLK0_PERIOD_PS 8000


/******************************************************************/


/* Definitions for peripheral DDR2_SDRAM */
#define XPAR_DDR2_SDRAM_MPMC_BASEADDR 0x50000000
#define XPAR_DDR2_SDRAM_MPMC_HIGHADDR 0x5FFFFFFF
#define XPAR_DDR2_SDRAM_SDMA_CTRL_BASEADDR 0x84600000
#define XPAR_DDR2_SDRAM_SDMA_CTRL_HIGHADDR 0x8460FFFF
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL0 0x000
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL0 0x00b
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL2 0x014
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL2 0x01f
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL3 0x020
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL3 0x027
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL4 0x028
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL4 0x033
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL5 0x034
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL5 0x03b
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL6 0x03c
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL6 0x047
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL7 0x048
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL7 0x04f
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL8 0x050
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL8 0x05d
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL9 0x05e
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL9 0x066
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL10 0x067
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL10 0x078
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL11 0x079
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL11 0x085
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL12 0x086
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL12 0x097
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL13 0x098
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL13 0x0a4
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL14 0x0a5
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL14 0x0b5
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL15 0x0b6
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL15 0x0b7
#define XPAR_DDR2_SDRAM_BASEADDR_CTRL16 0x0d9
#define XPAR_DDR2_SDRAM_HIGHADDR_CTRL16 0x0da


/******************************************************************/

/* Canonical definitions for peripheral DDR2_SDRAM */
#define XPAR_MPMC_0_DEVICE_ID XPAR_DDR2_SDRAM_DEVICE_ID
#define XPAR_MPMC_0_MPMC_BASEADDR 0x50000000
#define XPAR_MPMC_0_MPMC_HIGHADDR 0x5FFFFFFF
#define XPAR_MPMC_0_MPMC_CTRL_BASEADDR 0xFFFFFFFF
#define XPAR_MPMC_0_INCLUDE_ECC_SUPPORT 0
#define XPAR_MPMC_0_USE_STATIC_PHY 0
#define XPAR_MPMC_0_PM_ENABLE 0
#define XPAR_MPMC_0_NUM_PORTS 4
#define XPAR_MPMC_0_MEM_DATA_WIDTH 64
#define XPAR_MPMC_0_MEM_PART_NUM_BANK_BITS 2
#define XPAR_MPMC_0_MEM_PART_NUM_ROW_BITS 13
#define XPAR_MPMC_0_MEM_PART_NUM_COL_BITS 10
#define XPAR_MPMC_0_MEM_TYPE DDR2
#define XPAR_MPMC_0_ECC_SEC_THRESHOLD 1
#define XPAR_MPMC_0_ECC_DEC_THRESHOLD 1
#define XPAR_MPMC_0_ECC_PEC_THRESHOLD 1
#define XPAR_MPMC_0_MEM_DQS_WIDTH 8
#define XPAR_MPMC_0_MPMC_CLK0_PERIOD_PS 8000


/******************************************************************/

/* Definitions for driver BRAM */
#define XPAR_XBRAM_NUM_INSTANCES 2

/* Definitions for peripheral DLMB_CNTLR */
#define XPAR_DLMB_CNTLR_DEVICE_ID 0
#define XPAR_DLMB_CNTLR_DATA_WIDTH 32
#define XPAR_DLMB_CNTLR_ECC 0
#define XPAR_DLMB_CNTLR_FAULT_INJECT 0
#define XPAR_DLMB_CNTLR_CE_FAILING_REGISTERS 0
#define XPAR_DLMB_CNTLR_UE_FAILING_REGISTERS 0
#define XPAR_DLMB_CNTLR_ECC_STATUS_REGISTERS 0
#define XPAR_DLMB_CNTLR_CE_COUNTER_WIDTH 0
#define XPAR_DLMB_CNTLR_ECC_ONOFF_REGISTER 0
#define XPAR_DLMB_CNTLR_ECC_ONOFF_RESET_VALUE 0
#define XPAR_DLMB_CNTLR_WRITE_ACCESS 0
#define XPAR_DLMB_CNTLR_BASEADDR 0x00000000
#define XPAR_DLMB_CNTLR_HIGHADDR 0x0000FFFF


/* Definitions for peripheral ILMB_CNTLR */
#define XPAR_ILMB_CNTLR_DEVICE_ID 1
#define XPAR_ILMB_CNTLR_DATA_WIDTH 32
#define XPAR_ILMB_CNTLR_ECC 0
#define XPAR_ILMB_CNTLR_FAULT_INJECT 0
#define XPAR_ILMB_CNTLR_CE_FAILING_REGISTERS 0
#define XPAR_ILMB_CNTLR_UE_FAILING_REGISTERS 0
#define XPAR_ILMB_CNTLR_ECC_STATUS_REGISTERS 0
#define XPAR_ILMB_CNTLR_CE_COUNTER_WIDTH 0
#define XPAR_ILMB_CNTLR_ECC_ONOFF_REGISTER 0
#define XPAR_ILMB_CNTLR_ECC_ONOFF_RESET_VALUE 0
#define XPAR_ILMB_CNTLR_WRITE_ACCESS 0
#define XPAR_ILMB_CNTLR_BASEADDR 0x00000000
#define XPAR_ILMB_CNTLR_HIGHADDR 0x0000FFFF


/******************************************************************/

/* Canonical definitions for peripheral DLMB_CNTLR */
#define XPAR_BRAM_0_DEVICE_ID XPAR_DLMB_CNTLR_DEVICE_ID
#define XPAR_BRAM_0_DATA_WIDTH 32
#define XPAR_BRAM_0_ECC 0
#define XPAR_BRAM_0_FAULT_INJECT 0
#define XPAR_BRAM_0_CE_FAILING_REGISTERS 0
#define XPAR_BRAM_0_UE_FAILING_REGISTERS 0
#define XPAR_BRAM_0_ECC_STATUS_REGISTERS 0
#define XPAR_BRAM_0_CE_COUNTER_WIDTH 0
#define XPAR_BRAM_0_ECC_ONOFF_REGISTER 0
#define XPAR_BRAM_0_ECC_ONOFF_RESET_VALUE 0
#define XPAR_BRAM_0_WRITE_ACCESS 0
#define XPAR_BRAM_0_BASEADDR 0x00000000
#define XPAR_BRAM_0_HIGHADDR 0x0000FFFF

/* Canonical definitions for peripheral ILMB_CNTLR */
#define XPAR_BRAM_1_DEVICE_ID XPAR_ILMB_CNTLR_DEVICE_ID
#define XPAR_BRAM_1_DATA_WIDTH 32
#define XPAR_BRAM_1_ECC 0
#define XPAR_BRAM_1_FAULT_INJECT 0
#define XPAR_BRAM_1_CE_FAILING_REGISTERS 0
#define XPAR_BRAM_1_UE_FAILING_REGISTERS 0
#define XPAR_BRAM_1_ECC_STATUS_REGISTERS 0
#define XPAR_BRAM_1_CE_COUNTER_WIDTH 0
#define XPAR_BRAM_1_ECC_ONOFF_REGISTER 0
#define XPAR_BRAM_1_ECC_ONOFF_RESET_VALUE 0
#define XPAR_BRAM_1_WRITE_ACCESS 0
#define XPAR_BRAM_1_BASEADDR 0x00000000
#define XPAR_BRAM_1_HIGHADDR 0x0000FFFF


/******************************************************************/


/* Definitions for peripheral FLASH */
#define XPAR_FLASH_NUM_BANKS_MEM 1


/******************************************************************/

/* Definitions for peripheral FLASH */
#define XPAR_FLASH_MEM0_BASEADDR 0xC4000000
#define XPAR_FLASH_MEM0_HIGHADDR 0xC5FFFFFF

/******************************************************************/

/* Canonical definitions for peripheral FLASH */
#define XPAR_EMC_0_NUM_BANKS_MEM 1
#define XPAR_EMC_0_MEM0_BASEADDR 0xC4000000
#define XPAR_EMC_0_MEM0_HIGHADDR 0xC5FFFFFF

#define XPAR_XPS_MCH_EMC

/******************************************************************/

/* Definitions for driver LLTEMAC */
#define XPAR_XLLTEMAC_NUM_INSTANCES 1

/* Definitions for peripheral HARD_ETHERNET_MAC Channel 0 */
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_DEVICE_ID 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_BASEADDR 0x87000000
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_HIGHADDR 0x8707ffff
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_TXCSUM 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_RXCSUM 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_PHY_TYPE 1
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_TXVLAN_TRAN 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_RXVLAN_TRAN 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_TXVLAN_TAG 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_RXVLAN_TAG 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_TXVLAN_STRP 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_RXVLAN_STRP 0
#define XPAR_HARD_ETHERNET_MAC_CHAN_0_MCAST_EXTEND 0

/* Canonical definitions for peripheral HARD_ETHERNET_MAC Channel 0 */
#define XPAR_LLTEMAC_0_DEVICE_ID 0
#define XPAR_LLTEMAC_0_BASEADDR 0x87000000
#define XPAR_LLTEMAC_0_HIGHADDR 0x8707ffff
#define XPAR_LLTEMAC_0_TXCSUM 0
#define XPAR_LLTEMAC_0_RXCSUM 0
#define XPAR_LLTEMAC_0_PHY_TYPE 1
#define XPAR_LLTEMAC_0_TXVLAN_TRAN 0
#define XPAR_LLTEMAC_0_RXVLAN_TRAN 0
#define XPAR_LLTEMAC_0_TXVLAN_TAG 0
#define XPAR_LLTEMAC_0_RXVLAN_TAG 0
#define XPAR_LLTEMAC_0_TXVLAN_STRP 0
#define XPAR_LLTEMAC_0_RXVLAN_STRP 0
#define XPAR_LLTEMAC_0_MCAST_EXTEND 0
#define XPAR_LLTEMAC_0_INTR 3


/* LocalLink TYPE Enumerations */
#define XPAR_LL_FIFO    1
#define XPAR_LL_DMA     2


/* Canonical LocalLink parameters for HARD_ETHERNET_MAC */
#define XPAR_LLTEMAC_0_LLINK_CONNECTED_TYPE XPAR_LL_DMA
#define XPAR_LLTEMAC_0_LLINK_CONNECTED_BASEADDR 0x84600100
#define XPAR_LLTEMAC_0_LLINK_CONNECTED_FIFO_INTR 0xFF
#define XPAR_LLTEMAC_0_LLINK_CONNECTED_DMARX_INTR 2
#define XPAR_LLTEMAC_0_LLINK_CONNECTED_DMATX_INTR 1


/******************************************************************/

/* Definitions for driver UARTLITE */
#define XPAR_XUARTLITE_NUM_INSTANCES 1

/* Definitions for peripheral MDM_0 */
#define XPAR_MDM_0_BASEADDR 0x84400000
#define XPAR_MDM_0_HIGHADDR 0x8440FFFF
#define XPAR_MDM_0_DEVICE_ID 0
#define XPAR_MDM_0_BAUDRATE 0
#define XPAR_MDM_0_USE_PARITY 0
#define XPAR_MDM_0_ODD_PARITY 0
#define XPAR_MDM_0_DATA_BITS 0


/******************************************************************/

/* Canonical definitions for peripheral MDM_0 */
#define XPAR_UARTLITE_0_DEVICE_ID XPAR_MDM_0_DEVICE_ID
#define XPAR_UARTLITE_0_BASEADDR 0x84400000
#define XPAR_UARTLITE_0_HIGHADDR 0x8440FFFF
#define XPAR_UARTLITE_0_BAUDRATE 0
#define XPAR_UARTLITE_0_USE_PARITY 0
#define XPAR_UARTLITE_0_ODD_PARITY 0
#define XPAR_UARTLITE_0_DATA_BITS 0
#define XPAR_UARTLITE_0_SIO_CHAN -1


/******************************************************************/

/* Definitions for driver PS2 */
#define XPAR_XPS2_NUM_INSTANCES 1

/* Definitions for peripheral PS2_CONN Device 0 */
#define XPAR_PS2_CONN_0_DEVICE_ID 0
#define XPAR_PS2_CONN_0_BASEADDR 0x86a00000
#define XPAR_PS2_CONN_0_HIGHADDR 0x86A00FFF

/* Canonical definitions for peripheral PS2_CONN Device 0 */
#define XPAR_PS2_0_DEVICE_ID 0
#define XPAR_PS2_0_BASEADDR 0x86a00000
#define XPAR_PS2_0_HIGHADDR 0x86A00FFF



/******************************************************************/

/* Definitions for driver UARTNS550 */
#define XPAR_XUARTNS550_NUM_INSTANCES 2
#define XPAR_XUARTNS550_CLOCK_HZ 125000000

/* Definitions for peripheral RS232_UART_0 */
#define XPAR_RS232_UART_0_DEVICE_ID 0
#define XPAR_RS232_UART_0_BASEADDR 0x83E20000
#define XPAR_RS232_UART_0_HIGHADDR 0x83E2FFFF
#define XPAR_RS232_UART_0_CLOCK_FREQ_HZ 125000000


/* Definitions for peripheral RS232_UART_1 */
#define XPAR_RS232_UART_1_DEVICE_ID 1
#define XPAR_RS232_UART_1_BASEADDR 0x83E00000
#define XPAR_RS232_UART_1_HIGHADDR 0x83E0FFFF
#define XPAR_RS232_UART_1_CLOCK_FREQ_HZ 125000000


/******************************************************************/

/* Canonical definitions for peripheral RS232_UART_0 */
#define XPAR_UARTNS550_0_DEVICE_ID XPAR_RS232_UART_0_DEVICE_ID
#define XPAR_UARTNS550_0_BASEADDR 0x83E20000
#define XPAR_UARTNS550_0_HIGHADDR 0x83E2FFFF
#define XPAR_UARTNS550_0_CLOCK_FREQ_HZ XPAR_RS232_UART_0_CLOCK_FREQ_HZ
#define XPAR_UARTNS550_0_SIO_CHAN -1

/* Canonical definitions for peripheral RS232_UART_1 */
#define XPAR_UARTNS550_1_DEVICE_ID XPAR_RS232_UART_1_DEVICE_ID
#define XPAR_UARTNS550_1_BASEADDR 0x83E00000
#define XPAR_UARTNS550_1_HIGHADDR 0x83E0FFFF
#define XPAR_UARTNS550_1_CLOCK_FREQ_HZ XPAR_RS232_UART_1_CLOCK_FREQ_HZ
#define XPAR_UARTNS550_1_SIO_CHAN 0


/******************************************************************/

#define XPAR_INTC_MAX_NUM_INTR_INPUTS 4
#define XPAR_XINTC_HAS_IPR 1
#define XPAR_XINTC_HAS_SIE 1
#define XPAR_XINTC_HAS_CIE 1
#define XPAR_XINTC_HAS_IVR 1
#define XPAR_XINTC_USE_DCR 0
/* Definitions for driver INTC */
#define XPAR_XINTC_NUM_INSTANCES 1

/* Definitions for peripheral XPS_INTC_0 */
#define XPAR_XPS_INTC_0_DEVICE_ID 0
#define XPAR_XPS_INTC_0_BASEADDR 0x81800000
#define XPAR_XPS_INTC_0_HIGHADDR 0x8180FFFF
#define XPAR_XPS_INTC_0_KIND_OF_INTR 0xFFFFFFF0
#define XPAR_XPS_INTC_0_HAS_FAST 0
#define XPAR_XPS_INTC_0_IVAR_RESET_VALUE 0
#define XPAR_XPS_INTC_0_NUM_INTR_INPUTS 4


/******************************************************************/

#define XPAR_INTC_SINGLE_BASEADDR 0x81800000
#define XPAR_INTC_SINGLE_HIGHADDR 0x8180FFFF
#define XPAR_INTC_SINGLE_DEVICE_ID XPAR_XPS_INTC_0_DEVICE_ID
#define XPAR_XPS_INTC_0_TYPE 0
#define XPAR_USB_EPP_IF_0_EPP_IRPT_MASK 0X000001
#define XPAR_XPS_INTC_0_USB_EPP_IF_0_EPP_IRPT_INTR 0
#define XPAR_DDR2_SDRAM_SDMA2_TX_INTOUT_MASK 0X000002
#define XPAR_XPS_INTC_0_DDR2_SDRAM_SDMA2_TX_INTOUT_INTR 1
#define XPAR_DDR2_SDRAM_SDMA2_RX_INTOUT_MASK 0X000004
#define XPAR_XPS_INTC_0_DDR2_SDRAM_SDMA2_RX_INTOUT_INTR 2
#define XPAR_HARD_ETHERNET_MAC_TEMACINTC0_IRPT_MASK 0X000008
#define XPAR_XPS_INTC_0_HARD_ETHERNET_MAC_TEMACINTC0_IRPT_INTR 3

/******************************************************************/

/* Canonical definitions for peripheral XPS_INTC_0 */
#define XPAR_INTC_0_DEVICE_ID XPAR_XPS_INTC_0_DEVICE_ID
#define XPAR_INTC_0_BASEADDR 0x81800000
#define XPAR_INTC_0_HIGHADDR 0x8180FFFF
#define XPAR_INTC_0_KIND_OF_INTR 0xFFFFFFF0
#define XPAR_INTC_0_HAS_FAST 0
#define XPAR_INTC_0_IVAR_RESET_VALUE 0
#define XPAR_INTC_0_NUM_INTR_INPUTS 4
#define XPAR_INTC_0_INTC_TYPE 0

#define XPAR_INTC_0_MPMC_0_SDMA2_TX_INTOUT_VEC_ID XPAR_XPS_INTC_0_DDR2_SDRAM_SDMA2_TX_INTOUT_INTR
#define XPAR_INTC_0_MPMC_0_SDMA2_RX_INTOUT_VEC_ID XPAR_XPS_INTC_0_DDR2_SDRAM_SDMA2_RX_INTOUT_INTR
#define XPAR_INTC_0_LLTEMAC_0_VEC_ID XPAR_XPS_INTC_0_HARD_ETHERNET_MAC_TEMACINTC0_IRPT_INTR

/******************************************************************/

/* Definitions for driver TFT */
#define XPAR_XTFT_NUM_INSTANCES 1

/* Definitions for peripheral XPS_TFT_0 */
#define XPAR_XPS_TFT_0_SPLB_BASEADDR 0x86E00000
#define XPAR_XPS_TFT_0_SPLB_HIGHADDR 0x86E0FFFF
#define XPAR_XPS_TFT_0_DEVICE_ID 0
#define XPAR_XPS_TFT_0_DEFAULT_TFT_BASE_ADDR 0x50000000
#define XPAR_XPS_TFT_0_DCR_SPLB_SLAVE_IF 1
#define XPAR_XPS_TFT_0_DCR_BASEADDR 0x00000000


/******************************************************************/

/* Canonical definitions for peripheral XPS_TFT_0 */
#define XPAR_TFT_0_DEVICE_ID XPAR_XPS_TFT_0_DEVICE_ID
#define XPAR_TFT_0_BASEADDR 0x86E00000
#define XPAR_TFT_0_HIGHADDR 0x86E0FFFF
#define XPAR_TFT_0_DEFAULT_TFT_BASE_ADDR 0x50000000
#define XPAR_TFT_0_DCR_SPLB_SLAVE_IF 1
#define XPAR_TFT_0_DCR_BASEADDR 0x00000000


/******************************************************************/

/* Definitions for bus frequencies */
#define XPAR_CPU_DPLB_FREQ_HZ 125000000
#define XPAR_CPU_IPLB_FREQ_HZ 125000000
/******************************************************************/

/* Canonical definitions for bus frequencies */
#define XPAR_PROC_BUS_0_FREQ_HZ 125000000
/******************************************************************/

#define XPAR_CPU_CORE_CLOCK_FREQ_HZ 125000000
#define XPAR_MICROBLAZE_CORE_CLOCK_FREQ_HZ 125000000

/******************************************************************/


/* Definitions for peripheral MICROBLAZE_0 */
#define XPAR_MICROBLAZE_0_SCO 0
#define XPAR_MICROBLAZE_0_FREQ 125000000
#define XPAR_MICROBLAZE_0_DATA_SIZE 32
#define XPAR_MICROBLAZE_0_DYNAMIC_BUS_SIZING 1
#define XPAR_MICROBLAZE_0_AREA_OPTIMIZED 0
#define XPAR_MICROBLAZE_0_OPTIMIZATION 0
#define XPAR_MICROBLAZE_0_INTERCONNECT 1
#define XPAR_MICROBLAZE_0_DPLB_DWIDTH 32
#define XPAR_MICROBLAZE_0_DPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_0_DPLB_BURST_EN 0
#define XPAR_MICROBLAZE_0_DPLB_P2P 0
#define XPAR_MICROBLAZE_0_IPLB_DWIDTH 32
#define XPAR_MICROBLAZE_0_IPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_0_IPLB_BURST_EN 0
#define XPAR_MICROBLAZE_0_IPLB_P2P 0
#define XPAR_MICROBLAZE_0_D_PLB 1
#define XPAR_MICROBLAZE_0_D_LMB 1
#define XPAR_MICROBLAZE_0_I_PLB 1
#define XPAR_MICROBLAZE_0_I_LMB 1
#define XPAR_MICROBLAZE_0_USE_MSR_INSTR 1
#define XPAR_MICROBLAZE_0_USE_PCMP_INSTR 1
#define XPAR_MICROBLAZE_0_USE_BARREL 0
#define XPAR_MICROBLAZE_0_USE_DIV 0
#define XPAR_MICROBLAZE_0_USE_HW_MUL 1
#define XPAR_MICROBLAZE_0_USE_FPU 0
#define XPAR_MICROBLAZE_0_UNALIGNED_EXCEPTIONS 0
#define XPAR_MICROBLAZE_0_ILL_OPCODE_EXCEPTION 0
#define XPAR_MICROBLAZE_0_IPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_DPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_DIV_ZERO_EXCEPTION 0
#define XPAR_MICROBLAZE_0_FPU_EXCEPTION 0
#define XPAR_MICROBLAZE_0_FSL_EXCEPTION 0
#define XPAR_MICROBLAZE_0_PVR 0
#define XPAR_MICROBLAZE_0_PVR_USER1 0x00
#define XPAR_MICROBLAZE_0_PVR_USER2 0x00000000
#define XPAR_MICROBLAZE_0_DEBUG_ENABLED 1
#define XPAR_MICROBLAZE_0_NUMBER_OF_PC_BRK 1
#define XPAR_MICROBLAZE_0_NUMBER_OF_RD_ADDR_BRK 0
#define XPAR_MICROBLAZE_0_NUMBER_OF_WR_ADDR_BRK 0
#define XPAR_MICROBLAZE_0_INTERRUPT_IS_EDGE 0
#define XPAR_MICROBLAZE_0_EDGE_IS_POSITIVE 1
#define XPAR_MICROBLAZE_0_RESET_MSR 0x00000000
#define XPAR_MICROBLAZE_0_OPCODE_0X0_ILLEGAL 0
#define XPAR_MICROBLAZE_0_FSL_LINKS 0
#define XPAR_MICROBLAZE_0_FSL_DATA_SIZE 32
#define XPAR_MICROBLAZE_0_USE_EXTENDED_FSL_INSTR 0
#define XPAR_MICROBLAZE_0_ICACHE_BASEADDR 0x50000000
#define XPAR_MICROBLAZE_0_ICACHE_HIGHADDR 0x5FFFFFFF
#define XPAR_MICROBLAZE_0_USE_ICACHE 1
#define XPAR_MICROBLAZE_0_ALLOW_ICACHE_WR 1
#define XPAR_MICROBLAZE_0_ADDR_TAG_BITS 17
#define XPAR_MICROBLAZE_0_CACHE_BYTE_SIZE 2048
#define XPAR_MICROBLAZE_0_ICACHE_USE_FSL 1
#define XPAR_MICROBLAZE_0_ICACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_0_ICACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_0_ICACHE_INTERFACE 0
#define XPAR_MICROBLAZE_0_ICACHE_VICTIMS 0
#define XPAR_MICROBLAZE_0_ICACHE_STREAMS 0
#define XPAR_MICROBLAZE_0_DCACHE_BASEADDR 0x50000000
#define XPAR_MICROBLAZE_0_DCACHE_HIGHADDR 0x5FFFFFFF
#define XPAR_MICROBLAZE_0_USE_DCACHE 1
#define XPAR_MICROBLAZE_0_ALLOW_DCACHE_WR 1
#define XPAR_MICROBLAZE_0_DCACHE_ADDR_TAG 17
#define XPAR_MICROBLAZE_0_DCACHE_BYTE_SIZE 2048
#define XPAR_MICROBLAZE_0_DCACHE_USE_FSL 1
#define XPAR_MICROBLAZE_0_DCACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_0_DCACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_0_DCACHE_INTERFACE 0
#define XPAR_MICROBLAZE_0_DCACHE_USE_WRITEBACK 0
#define XPAR_MICROBLAZE_0_DCACHE_VICTIMS 0
#define XPAR_MICROBLAZE_0_USE_MMU 0
#define XPAR_MICROBLAZE_0_MMU_DTLB_SIZE 4
#define XPAR_MICROBLAZE_0_MMU_ITLB_SIZE 2
#define XPAR_MICROBLAZE_0_MMU_TLB_ACCESS 3
#define XPAR_MICROBLAZE_0_MMU_ZONES 16
#define XPAR_MICROBLAZE_0_USE_INTERRUPT 1
#define XPAR_MICROBLAZE_0_USE_EXT_BRK 1
#define XPAR_MICROBLAZE_0_USE_EXT_NM_BRK 1
#define XPAR_MICROBLAZE_0_USE_BRANCH_TARGET_CACHE 0
#define XPAR_MICROBLAZE_0_BRANCH_TARGET_CACHE_SIZE 0

/******************************************************************/

#define XPAR_CPU_ID 0
#define XPAR_MICROBLAZE_ID 0
#define XPAR_MICROBLAZE_SCO 0
#define XPAR_MICROBLAZE_FREQ 125000000
#define XPAR_MICROBLAZE_DATA_SIZE 32
#define XPAR_MICROBLAZE_DYNAMIC_BUS_SIZING 1
#define XPAR_MICROBLAZE_AREA_OPTIMIZED 0
#define XPAR_MICROBLAZE_OPTIMIZATION 0
#define XPAR_MICROBLAZE_INTERCONNECT 1
#define XPAR_MICROBLAZE_DPLB_DWIDTH 32
#define XPAR_MICROBLAZE_DPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_DPLB_BURST_EN 0
#define XPAR_MICROBLAZE_DPLB_P2P 0
#define XPAR_MICROBLAZE_IPLB_DWIDTH 32
#define XPAR_MICROBLAZE_IPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_IPLB_BURST_EN 0
#define XPAR_MICROBLAZE_IPLB_P2P 0
#define XPAR_MICROBLAZE_D_PLB 1
#define XPAR_MICROBLAZE_D_LMB 1
#define XPAR_MICROBLAZE_I_PLB 1
#define XPAR_MICROBLAZE_I_LMB 1
#define XPAR_MICROBLAZE_USE_MSR_INSTR 1
#define XPAR_MICROBLAZE_USE_PCMP_INSTR 1
#define XPAR_MICROBLAZE_USE_BARREL 0
#define XPAR_MICROBLAZE_USE_DIV 0
#define XPAR_MICROBLAZE_USE_HW_MUL 1
#define XPAR_MICROBLAZE_USE_FPU 0
#define XPAR_MICROBLAZE_UNALIGNED_EXCEPTIONS 0
#define XPAR_MICROBLAZE_ILL_OPCODE_EXCEPTION 0
#define XPAR_MICROBLAZE_IPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_DPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_DIV_ZERO_EXCEPTION 0
#define XPAR_MICROBLAZE_FPU_EXCEPTION 0
#define XPAR_MICROBLAZE_FSL_EXCEPTION 0
#define XPAR_MICROBLAZE_PVR 0
#define XPAR_MICROBLAZE_PVR_USER1 0x00
#define XPAR_MICROBLAZE_PVR_USER2 0x00000000
#define XPAR_MICROBLAZE_DEBUG_ENABLED 1
#define XPAR_MICROBLAZE_NUMBER_OF_PC_BRK 1
#define XPAR_MICROBLAZE_NUMBER_OF_RD_ADDR_BRK 0
#define XPAR_MICROBLAZE_NUMBER_OF_WR_ADDR_BRK 0
#define XPAR_MICROBLAZE_INTERRUPT_IS_EDGE 0
#define XPAR_MICROBLAZE_EDGE_IS_POSITIVE 1
#define XPAR_MICROBLAZE_RESET_MSR 0x00000000
#define XPAR_MICROBLAZE_OPCODE_0X0_ILLEGAL 0
#define XPAR_MICROBLAZE_FSL_LINKS 0
#define XPAR_MICROBLAZE_FSL_DATA_SIZE 32
#define XPAR_MICROBLAZE_USE_EXTENDED_FSL_INSTR 0
#define XPAR_MICROBLAZE_ICACHE_BASEADDR 0x50000000
#define XPAR_MICROBLAZE_ICACHE_HIGHADDR 0x5FFFFFFF
#define XPAR_MICROBLAZE_USE_ICACHE 1
#define XPAR_MICROBLAZE_ALLOW_ICACHE_WR 1
#define XPAR_MICROBLAZE_ADDR_TAG_BITS 17
#define XPAR_MICROBLAZE_CACHE_BYTE_SIZE 2048
#define XPAR_MICROBLAZE_ICACHE_USE_FSL 1
#define XPAR_MICROBLAZE_ICACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_ICACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_ICACHE_INTERFACE 0
#define XPAR_MICROBLAZE_ICACHE_VICTIMS 0
#define XPAR_MICROBLAZE_ICACHE_STREAMS 0
#define XPAR_MICROBLAZE_DCACHE_BASEADDR 0x50000000
#define XPAR_MICROBLAZE_DCACHE_HIGHADDR 0x5FFFFFFF
#define XPAR_MICROBLAZE_USE_DCACHE 1
#define XPAR_MICROBLAZE_ALLOW_DCACHE_WR 1
#define XPAR_MICROBLAZE_DCACHE_ADDR_TAG 17
#define XPAR_MICROBLAZE_DCACHE_BYTE_SIZE 2048
#define XPAR_MICROBLAZE_DCACHE_USE_FSL 1
#define XPAR_MICROBLAZE_DCACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_DCACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_DCACHE_INTERFACE 0
#define XPAR_MICROBLAZE_DCACHE_USE_WRITEBACK 0
#define XPAR_MICROBLAZE_DCACHE_VICTIMS 0
#define XPAR_MICROBLAZE_USE_MMU 0
#define XPAR_MICROBLAZE_MMU_DTLB_SIZE 4
#define XPAR_MICROBLAZE_MMU_ITLB_SIZE 2
#define XPAR_MICROBLAZE_MMU_TLB_ACCESS 3
#define XPAR_MICROBLAZE_MMU_ZONES 16
#define XPAR_MICROBLAZE_USE_INTERRUPT 1
#define XPAR_MICROBLAZE_USE_EXT_BRK 1
#define XPAR_MICROBLAZE_USE_EXT_NM_BRK 1
#define XPAR_MICROBLAZE_USE_BRANCH_TARGET_CACHE 0
#define XPAR_MICROBLAZE_BRANCH_TARGET_CACHE_SIZE 0
#define XPAR_MICROBLAZE_HW_VER "7.30.b"

/******************************************************************/

