/* $Id: xuartns550.h,v 1.1.2.1 2009/11/24 04:46:47 svemula Exp $ */
/******************************************************************************
*
* (c) Copyright 2002-2009 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/****************************************************************************/
/**
*
* @file xuartns550.h
*
* This driver supports the following features in the Xilinx 16450/16550
* compatible UART.
*
* 	- Dynamic data format (baud rate, data bits, stop bits, parity)
* 	- Polled mode
* 	- Interrupt driven mode
* 	- Transmit and receive FIFOs (16 bytes each for the 16550)
* 	- Access to the external modem control lines and the two discrete
*		outputs
*
* The only difference between the 16450 and the 16550 is the addition of
* transmit and receive FIFOs in the 16550.
*
* <b>Initialization & Configuration</b>
*
* The XUartNs550_Config structure is used by the driver to configure itself.
* This configuration structure is typically created by the tool-chain based
* on HW build properties.
*
* To support multiple runtime loading and initialization strategies employed
* by various operating systems, the driver instance can be initialized in one
* of the following ways:
*
*	- XUartNs550_Initialize(InstancePtr, DeviceId) - The driver looks
*	up its own configuration structure created by the tool-chain based
*	on an ID provided by the tool-chain.
*
*	- XUartNs550_CfgInitialize(InstancePtr, CfgPtr, EffectiveAddr) - Uses a
*	configuration structure provided by the caller. If running in a system
*	with address translation, the provided virtual memory base address
*	replaces the physical address present in the configuration structure.
*
* <b>Baud Rate</b>
*
* The UART has an internal baud rate generator that is clocked at a specified
* input clock frequency. Not all baud rates can be generated from some clock
* frequencies. The requested baud rate is checked using the provided clock for
* the system, and checked against the acceptable error range. An error may be
* returned from some functions indicating the baud rate was in error because
* it could not be generated.
*
* <b>Interrupts</b>
*
* The device does not have any way to disable the receiver such that the
* receive FIFO may contain unwanted data. The FIFOs are not flushed when the
* driver is initialized, but a function is provided to allow the user to reset
* the FIFOs if desired.
*
* The driver defaults to no interrupts at initialization such that interrupts
* must be enabled if desired. An interrupt is generated for any of the following
* conditions.
*	- Transmit FIFO is empty
*	- Data in the receive FIFO equal to the receive threshold
*	- Data in the receiver when FIFOs are disabled
*	- Any receive status error or break condition detected
*	- Data in the receive FIFO for 4 character times without receiver
*	activity
*	- A change of a modem signal
*
* The application can control which interrupts are enabled using the SetOptions
* function.
*
* In order to use interrupts, it is necessary for the user to connect the driver
* interrupt handler, XUartNs550_InterruptHandler(), to the interrupt system of
* the application. This function does not save and restore the processor context
* such that the user must provide it. A handler must be set for the driver such
* that the handler is called when interrupt events occur. The handler is called
* from interrupt context and is designed to allow application specific
* processing to be performed.
*
* The functions, XUartNs550_Send() and XUartNs550_Recv(), are provided in the
* driver to allow data to be sent and received. They are designed to be used in
* polled or interrupt modes.
*
* @note
*
* The default configuration for the UART after initialization is:
*	- 19,200 bps or XPAR_DEFAULT_BAUD_RATE if defined
*	- 8 data bits
*	- 1 stop bit
*	- no parity
*	- FIFO's are enabled with a receive threshold of 8 bytes
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a ecm  08/16/01 First release
* 1.00b jhl  03/11/02 Repartitioned the driver for smaller files.
* 1.01a jvb  12/14/05 I separated dependency on the static config table and
*                     xparameters.h from the driver initialization by moving
*                     _Initialize and _LookupConfig to _sinit.c. I also added
*                     the new _CfgInitialize routine.
* 1.11a sv   03/20/07 Updated to use the new coding guidelines.
* 1.11a sv   07/25/08 Corrected the definitions of XUN_MODEM_DCD_DELTA_MASK
* 		      and XUN_MODEM_DCD_MASK.
* 1.12a sdm  08/22/08 Removed support for static interrupt handlers from the MDD
*		      file
* 1.12a sdm  12/15/08 Deprecated the CLOCK_HZ parameter in mdd and updated the
*		      Tcl to obtain the bus frequency during libgen
* 1.13a sdm  07/10/09 a) Updated the driver Tcl to obtain the external clock
*                        frequency from MHS, when C_HAS_EXTERNAL_XIN = 1.
*                     b) Added receive line interrupt option to OptionsTable[]
*                        in xuartns550_options.c
* 2.00a ktn  10/20/09 Converted all register accesses to 32 bit access.
*		      Updated to use HAL Processor APIs. _m is removed from the
*		      name of all the macro definitions. XUartNs550_mClearStats
*		      macro is removed, XUartNs550_ClearStats function should be
*		      used in its place.
* 2.01a bss  01/13/12 Updated the XUartNs550_SelfTest to use Xil_AssertNonvoid
*		      in place of XASSERT_NONVOID for CR 641344.
* 		      Removed unneccessary read of the LCR register in the
*                     XUartNs550_CfgInitialize function. Removed compiler
*		      warnings for unused variables in the
*		      XUartNs550_StubHandler.
* </pre>
*
*****************************************************************************/

#ifndef XUARTNS550_H /* prevent circular inclusions */
#define XUARTNS550_H /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files ********************************/

#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xuartns550_l.h"

/************************** Constant Definitions ****************************/

/*
 * The following constants indicate the max and min baud rates and these
 * numbers are based only on the testing that has been done. The hardware
 * is capable of other baud rates.
 */
#define XUN_NS16550_MAX_RATE		115200
#define XUN_NS16550_MIN_RATE		300

/** @name Configuration options
 * @{
 */
/**
 * These constants specify the options that may be set or retrieved
 * with the driver, each is a unique bit mask such that multiple options
 * may be specified.  These constants indicate the function of the option
 * when in the active state.
 */
#define XUN_OPTION_RXLINE_INTR		0x0800 /**< Enable status interrupt */
#define XUN_OPTION_SET_BREAK		0x0400 /**< Set a break condition */
#define XUN_OPTION_LOOPBACK		0x0200 /**< Enable local loopback */
#define XUN_OPTION_DATA_INTR		0x0100 /**< Enable data interrupts */
#define XUN_OPTION_MODEM_INTR		0x0080 /**< Enable modem interrupts */
#define XUN_OPTION_FIFOS_ENABLE		0x0040 /**< Enable FIFOs */
#define XUN_OPTION_RESET_TX_FIFO	0x0020 /**< Reset the transmit FIFO */
#define XUN_OPTION_RESET_RX_FIFO	0x0010 /**< Reset the receive FIFO */
#define XUN_OPTION_ASSERT_OUT2		0x0008 /**< Assert out2 signal */
#define XUN_OPTION_ASSERT_OUT1		0x0004 /**< Assert out1 signal */
#define XUN_OPTION_ASSERT_RTS		0x0002 /**< Assert RTS signal */
#define XUN_OPTION_ASSERT_DTR		0x0001 /**< Assert DTR signal */
/*@}*/

/** @name Data format values
 * @{
 */
/**
 * These constants specify the data format that may be set or retrieved
 * with the driver.  The data format includes the number of data bits, the
 * number of stop bits and parity.
 *
 */
#define XUN_FORMAT_8_BITS		3 /**< 8 data bits */
#define XUN_FORMAT_7_BITS		2 /**< 7 data bits */
#define XUN_FORMAT_6_BITS		1 /**< 6 data bits */
#define XUN_FORMAT_5_BITS 		0 /**< 5 data bits */

#define XUN_FORMAT_EVEN_PARITY		2 /**< Even Parity */
#define XUN_FORMAT_ODD_PARITY		1 /**< Odd Parity */
#define XUN_FORMAT_NO_PARITY		0 /**< No Parity */

#define XUN_FORMAT_2_STOP_BIT		1 /**< 2 stop bits */
#define XUN_FORMAT_1_STOP_BIT		0 /**< 1 stop bit */
/*@}*/

/** @name FIFO trigger values
 * @{
 */
/*
 * These constants specify receive FIFO trigger levels which specify
 * the number of bytes at which a receive data event (interrupt) will occur.
 *
 */
#define XUN_FIFO_TRIGGER_14		0xC0 /**< 14 byte trigger level */
#define XUN_FIFO_TRIGGER_08		0x80 /**< 8 byte trigger level */
#define XUN_FIFO_TRIGGER_04		0x40 /**< 4 byte trigger level */
#define XUN_FIFO_TRIGGER_01		0x00 /**< 1 byte trigger level */
/*@}*/

/** @name Modem status values
 * @{
 */
/**
 * These constants specify the modem status that may be retrieved
 * from the driver.
 *
  */
#define XUN_MODEM_DCD_DELTA_MASK	0x08 /**< DCD signal changed state */
#define XUN_MODEM_DSR_DELTA_MASK	0x02 /**< DSR signal changed state */
#define XUN_MODEM_CTS_DELTA_MASK	0x01 /**< CTS signal changed state */
#define XUN_MODEM_RINGING_MASK		0x40 /**< Ring signal is active */
#define XUN_MODEM_DSR_MASK		0x20 /**< Current state of DSR signal */
#define XUN_MODEM_CTS_MASK		0x10 /**< Current state of CTS signal */
#define XUN_MODEM_DCD_MASK 		0x80 /**< Current state of DCD signal */
#define XUN_MODEM_RING_STOP_MASK	0x04 /**< Ringing has stopped */
/*@}*/

/** @name Callback events
 * @{
 */
/**
 * These constants specify the handler events that are passed to
 * a handler from the driver.  These constants are not bit masks such that
 * only one will be passed at a time to the handler.
 *
 */
#define XUN_EVENT_RECV_DATA		1 /**< Data has been received */
#define XUN_EVENT_RECV_TIMEOUT		2 /**< A receive timeout occurred */
#define XUN_EVENT_SENT_DATA		3 /**< Data has been sent */
#define XUN_EVENT_RECV_ERROR		4 /**< A receive error was detected */
#define XUN_EVENT_MODEM	 		5 /**< A change in modem status */
/*@}*/

/** @name Error values
 * @{
 */
/**
 * These constants specify the errors that may be retrieved from
 * the driver using the XUartNs550_GetLastErrors function. All of them are
 * bit masks, except no error, such that multiple errors may be specified.
 *
 */
#define XUN_ERROR_BREAK_MASK		0x10 /**< Break detected */
#define XUN_ERROR_FRAMING_MASK		0x08 /**< Receive framing error */
#define XUN_ERROR_PARITY_MASK		0x04 /**< Receive parity error */
#define XUN_ERROR_OVERRUN_MASK		0x02 /**< Receive overrun error */
#define XUN_ERROR_NONE 			0x00 /**< No error */
/*@}*/

/**************************** Type Definitions ******************************/

/**
 * This typedef contains configuration information for the device.
 */
typedef struct {
	u16 DeviceId;		/**< Unique ID  of device */
	u32 BaseAddress;	/**< Base address of device */
	u32 InputClockHz;	/**< Input clock frequency */
	u32 DefaultBaudRate;	/**< Baud Rate in bps, ie 1200 */
} XUartNs550_Config;

/**
 * The following data type is used to manage the buffers that are handled
 * when sending and receiving data in the interrupt mode.
 */
typedef struct {
	u8 *NextBytePtr;
	unsigned int RequestedBytes;
	unsigned int RemainingBytes;
} XUartNs550Buffer;

/**
 * This data type allows the data format of the device to be set
 * and retrieved.
 */
typedef struct {
	u32 BaudRate;	/**< In bps, ie 1200 */
	u32 DataBits;	/**< Number of data bits */
	u32 Parity;	/**< Parity */
	u8 StopBits;	/**< Number of stop bits */
} XUartNs550Format;

/*****************************************************************************/
/**
* This data type defines a handler which the application must define
* when using interrupt mode.  The handler will be called from the driver in an
* interrupt context to handle application specific processing.
*
* @param	CallBackRef is a callback reference passed in by the upper layer
*		when setting the handler, and is passed back to the upper layer
*		when the handler is called.
* @param 	Event contains one of the event constants indicating why the
*		handler is being called.
* @param	EventData contains the number of bytes sent or received at
*	 	the time of the call for send and receive events and contains
*		the modem status for modem events.
*
*****************************************************************************/
typedef void (*XUartNs550_Handler)(void *CallBackRef, u32 Event,
		 			unsigned int EventData);

/**
 * UART statistics
 */
typedef struct {
	u16 TransmitInterrupts;		/**< Number of transmit interrupts */
	u16 ReceiveInterrupts;		/**< Number of receive interrupts */
	u16 StatusInterrupts;		/**< Number of status interrupts */
	u16 ModemInterrupts;		/**< Number of modem interrupts */
	u16 CharactersTransmitted; 	/**< Number of characters transmitted */
	u16 CharactersReceived;		/**< Number of characters received */
	u16 ReceiveOverrunErrors;	/**< Number of receive overruns */
	u16 ReceiveParityErrors;	/**< Number of receive parity errors */
	u16 ReceiveFramingErrors;	/**< Number of receive framing errors */
	u16 ReceiveBreakDetected;	/**< Number of receive breaks */
} XUartNs550Stats;

/**
 * The XUartNs550 driver instance data. The user is required to allocate a
 * variable of this type for every UART 16550/16450 device in the system.
 * A pointer to a variable of this type is then passed to the driver API
 * functions.
 */
typedef struct {
	XUartNs550Stats Stats;	/**< Statistics */
	u32 BaseAddress;	/**< Base address of device  */
	u32 InputClockHz;	/**< Input clock frequency */
	int IsReady;		/**< Device is initialized and ready */
	u32 BaudRate;		/**< Current baud rate of hw */
	u8  LastErrors;		/**< The accumulated errors */

	XUartNs550Buffer SendBuffer; /**< Send Buffer */
	XUartNs550Buffer ReceiveBuffer; /**< Receive Buffer */

	XUartNs550_Handler Handler; /**< Call back handler */
	void *CallBackRef;	/* Callback reference for control handler */
} XUartNs550;

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Function Prototypes *****************************/

/*
 * Initialization functions in xuartns550_sinit.c
 */
int XUartNs550_Initialize(XUartNs550 *InstancePtr, u16 DeviceId);
XUartNs550_Config *XUartNs550_LookupConfig(u16 DeviceId);

/*
 * Required functions in xuartns550.c
 */
int XUartNs550_CfgInitialize(XUartNs550 *InstancePtr,
				XUartNs550_Config *Config,
				 u32 EffectiveAddr);
unsigned int XUartNs550_Send(XUartNs550 *InstancePtr, u8 *BufferPtr,
			 	unsigned int NumBytes);
unsigned int XUartNs550_Recv(XUartNs550 *InstancePtr, u8 *BufferPtr,
				unsigned int NumBytes);

/*
 * Options functions in xuartns550_options.c
 */
int XUartNs550_SetOptions(XUartNs550 *InstancePtr, u16 Options);
u16 XUartNs550_GetOptions(XUartNs550 *InstancePtr);

int XUartNs550_SetFifoThreshold(XUartNs550 *InstancePtr,
		 			u8 TriggerLevel);
u8 XUartNs550_GetFifoThreshold(XUartNs550 *InstancePtr);

int XUartNs550_IsSending(XUartNs550 *InstancePtr);

u8 XUartNs550_GetLastErrors(XUartNs550 *InstancePtr);

u8 XUartNs550_GetModemStatus(XUartNs550 *InstancePtr);

/*
 * Data format functions in xuartns550_format.c
 */
int XUartNs550_SetDataFormat(XUartNs550 *InstancePtr,
					XUartNs550Format *Format);
void XUartNs550_GetDataFormat(XUartNs550 *InstancePtr,
		 	 	XUartNs550Format *Format);
/*
 * Interrupt functions in xuartns550_intr.c
 */
void XUartNs550_SetHandler(XUartNs550 *InstancePtr, XUartNs550_Handler FuncPtr,
	 			void *CallBackRef);

void XUartNs550_InterruptHandler(XUartNs550 *InstancePtr);

/*
 * Statistics functions in xuartns550_stats.c
 */
void XUartNs550_GetStats(XUartNs550 *InstancePtr, XUartNs550Stats *StatsPtr);
void XUartNs550_ClearStats(XUartNs550 *InstancePtr);

/*
 * Self-test functions in xuartns550_selftest.c
 */
int XUartNs550_SelfTest(XUartNs550 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */

