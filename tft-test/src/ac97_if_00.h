/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * Xilinx EDK 11.2 EDK_LS2.6
 *
 * This file is a sample test application
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * XPS project when you run the "Generate Libraries" menu item
 * in XPS.
 *
 * Your XPS project directory is at:
 *    D:\Digilent\Projects\Genesys\Genesys_Custom_BSB\
 */


// Located in: microblaze_0/include/xparameters.h
#include "xparameters.h"
#include "xio.h"
#include "xbasic_types.h"
#include "xstatus.h"

/************************** Constant Definitions ****************************/
/**
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */


#define AC97_ADDR_OFFSET         0x0
#define AC97_CONFIG_DATA_OFFSET  0x4
#define AC97_TAG_AND_ID_OFFSET   0x8
#define AC97_PCM_OUT_L_OFFSET    0xC
#define AC97_PCM_OUT_R_OFFSET    0x10
#define AC97_PCM_IN_L_OFFSET     0x14
#define AC97_PCM_IN_R_OFFSET     0x18
#define AC97_CONTROL_OFFSET      0x1C
#define AC97_STATUS_OFFSET       0x20

#define AC97_MIC_SELECT			 0x00
#define AC97_LINE_IN_SELECT		 0x04

#define AC97_INPUT_SELECT_OFFSET		0x1A
#define AC97_MASTER_VOLUME_OFFSET 		0x02
#define AC97_HEADPHONE_VOLUME_OFFSET 	0x04
#define AC97_MONO_VOLUME_OFFSET 		0x06
#define AC97_MIC_VOLUME_OFFSET 			0x0E
#define AC97_LINE_IN_VOLUME_OFFSET 		0x10
#define AC97_PCM_OUT_VOLUME_OFFSET 		0x18
#define AC97_RECORD_GAIN_OFFSET 		0x1C

#define MUTE 15
#define boost20dB 6

#define VOLUME_MAX 		0x0
#define VOLUME_MID		0x08
#define VOLUME_MIN 		0x1f

#define GAIN_MAX		0x0f
#define GAIN_MID        0x08
#define GAIN_MIN		0x00

#define LEFT_CHANNEL	0x01
#define RIGHT_CHANNEL	0x02
#define BOTH_CHANNELS	0x00



//====================================================

/***************** Macros (Inline Functions) Definitions ********************/


/************************** Function Prototypes *****************************/



/************************** Function Definitions ****************************/



/******************************************************************************/
