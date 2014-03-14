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

/*****************************************************************************
*
* @Project TFT_Demo
*
* This project represents an example to use the xps_tft core in order to show some of
* its features. The application loads the bitmap file stored initially in the FLASH
* memory and displays it in a predefined DDR2 memory area If the bitmap file is not found
* in the FLASH memory an error message is displayed on both the terminal, LCD screen and
* the screen.
* The application then displays a colorbar (R, G, B) with gradients into another
* predefined DDR2 memory area.
* Pressing the Up button sets the xps_tft video base address to the colorbar image,
* so the colorbar is displayed. Pressing the  Down button sets the video base address to
* the bitmap image therefore the bitmap is displayed on the screen.
*
* @note
* The 256MB DDR2 memory has to be present in order to make the xps_tft core to work
*
******************************************************************************/


#include <stdio.h>
#include <string.h>
#include "xparameters.h"
#include "xenv_standalone.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "sleep.h"
#include "xuartns550_l.h"
#include "lcd.h"
#include "xintc.h"
#include "xtft_hw.h"
#include "xtft.h"
#include "stdlib.h"

/************************** Constant Definitions ****************************/
/**
 * The following constants maps to the XPAR parameter created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */

#define TFT_DEVICE_ID	XPAR_TFT_0_DEVICE_ID

//The upper three memory regions of 2MB in the DDR2 are defined to display
//the colorbar, bitmap and a drawing
#define TFT_COLORBAR_ADDR		XPAR_MPMC_0_MPMC_HIGHADDR - 0x001FFFFF
#define TFT_BITMAP_ADDR			XPAR_MPMC_0_MPMC_HIGHADDR - 0x003FFFFF

#define FRAME_SIZE	0x400000

#define DISPLAY_ROW_BUFFER_WIDTH 1024
#define DISPLAY_COLUMNS  640
#define DISPLAY_ROWS     480

/******************************************************************************
 *
 * 	Variable declaration
 *
 * ***************************************************************************/

//set to 1 in order to display debug messages
unsigned char verbose=0;

//TFT instance
static XTft TftInstance;

	//LCD globals
	u8 LCD_FirstPrint;
	u8 LCD_LinePos[2];
	u8 * LCD_CurrentLinePos;
	u8 LCD_CurrentLine;

/******************************************************************************
 *
 * 	Function prototypes
 *
 * ***************************************************************************/

void LCDInitAndPrint (char * First_Line, char * Second_Line);
int TftWriteString(XTft *InstancePtr, const u8 *CharValue);
int covertdigit (char c);

int convertdigit (char c) {
	return c-48;
}

int convert (char* num1, int index1){
	int ans=0;
	int digits = index1;
	int i;
	for (i=0;i<index1;i++){
		ans += convertdigit(num1[i])*(10^(digits-1));
		digits--;
	}

	return ans;

}

int main()
{
  XTft_Config *TftConfigPtr;
  XStatus Status;

  /* Initialize RS232_Uart_0 - Set baudrate and number of stop bits */
  XUartNs550_SetBaud(XPAR_RS232_UART_0_BASEADDR, XPAR_XUARTNS550_CLOCK_HZ, 9600);
  XUartNs550_SetLineControlReg(XPAR_RS232_UART_0_BASEADDR, XUN_LCR_8_DATA_BITS);



  XCACHE_ENABLE_ICACHE();
  XCACHE_ENABLE_DCACHE();

  //initialize LCD
  LCDInitAndPrint ((char *) "-   TFT Demo   -", (char *)"-  v0.0   r09  -");


	/*
	 * Get address of the XTft_Config structure for the given device id.
	 */
	TftConfigPtr = XTft_LookupConfig(TFT_DEVICE_ID);
	if (TftConfigPtr == (XTft_Config *)NULL) {
		if (verbose) xil_printf("Error in TFT initialize\r\n");
		return XST_FAILURE;
	}

	/*
	 * Initialize all the TftInstance members and fills the screen with
	 * default background color.
	 */
	Status = XTft_CfgInitialize(&TftInstance, TftConfigPtr,
					TftConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		if (verbose) xil_printf("Error in TFT cfginitialize\r\n");
		return XST_FAILURE;
	}

	/*
	 * Wait till Vsync(Video address latch) status bit is set before writing
	 * the frame address into the Address Register. This ensures that the
	 * current frame has been displayed and we can display a new frame of
	 * data. Checking the Vsync state ensures that there is no data flicker
	 * when displaying frames in real time though there is some delay due to
	 * polling.
	 */
	while (XTft_GetVsyncStatus(&TftInstance) !=
					XTFT_IESR_VADDRLATCH_STATUS_MASK);


  /*
	 * Change the Video Memory Base Address from default value to
	 * the address where the colorbar is displayed
	 */
	//XTft_SetFrameBaseAddr(&TftInstance, 0x50000000);

	XTft_SetColor(&TftInstance, 0xffffffff, 0);

	Decode_display_bitmap(&TftInstance, 0x50000000);

	int *base = (int*) TftInstance.TftConfig.VideoMemBaseAddr;

	const int bufferSize = 1024;
	const int screenLeft = 174;
	const int screenTop = 120 * bufferSize;
	const int screenBottom = (120+240) * bufferSize;
	const int screenRight = 174+292;

	const int* input0Base = XPAR_INPUT_MODULE_0_BASEADDR;
	const int* input1Base = XPAR_INPUT_MODULE_1_BASEADDR;

	int dudeLeft = 89;
	int dudeTop = 194 * bufferSize;
	int dudeRight = dudeLeft + 10;
	int dudeBottom = dudeTop + 10*bufferSize;

	int dudeVertVel = 0;
	int dudeHorizVel = 0;
	const int MAX_HORIZ_VEL = 10;

	int dudeLeftPrev = 0;
	int dudeTopPrev = 0;
	int dudeRightPrev = 0;
	int dudeBottomPrev = 0;

	int n = 0, i, j;

	int jump = 0;
	int jumpPrev = 0;
	while (n < 15)
	    {
			//XTft_ClearScreen(&TftInstance);

			//void XTft_SetPixel(XTft *nIstancePtr, u32 ColVal, u32 RowVal, u32 PixelVal);
			//XTft_SetPixel(&TftInstance, numInt1-2+i, numInt2-2+j, 0xFFFFFF00);
			//XTft_SetPixel(&TftInstance, numInt1+i, numInt2+j, 0xFFFFFF00);
			//XTft_SetColor(&TftInstance, 0xaaaffaaa, 0);
			/* *(base + numInt1 + numInt2) = background[numInt1][numInt2];
			numInt1 += 1;
			numInt3 += 1;
			if (numInt1 > screenRight)
			{
				numInt1 = screenLeft;
				numInt2 += bufferSize;
			}
			if (numInt2 > screenBottom) {
				//usleep(10000);
				numInt1 = screenLeft;
				numInt2 = screenTop;
				n++;
			}
			if (n > 1) {
				break;
			}*/

			int btn_data = XIo_In32(XPAR_PUSH_BUTTONS_7BIT_BASEADDR);

		 	jumpPrev = jump;
		 	jump = 0;

			 if (btn_data & 0x40) {
				jump = 1;
			 }
			if (btn_data & 0x8) {
				if (dudeHorizVel < MAX_HORIZ_VEL) {
					dudeHorizVel += 2;
				}
			}
			if (btn_data & 0x1) {
				if (dudeHorizVel > -MAX_HORIZ_VEL) {
					dudeHorizVel -= 2;
				}
			}

			if (jump && !jumpPrev) {
				dudeVertVel += -12;
			}

			if (dudeVertVel < -12) {
				dudeVertVel = -12;
			}

			// Input
			//if (n == 50) {
			//	dudeVertVel = -bufferSize * 8;
			//}

			// Velocity
			dudeTop += (dudeVertVel/4) * bufferSize;
			dudeBottom += (dudeVertVel/4) * bufferSize;
			dudeLeft += dudeHorizVel/2;
			dudeRight += dudeHorizVel/2;

			// Collisions + Gravity
			if (dudeTop > 194 * bufferSize) {
				dudeVertVel = 0;
				dudeTop = 194 * bufferSize;
				dudeBottom = 204 * bufferSize;
			} else if (dudeTop <= 0) {
				dudeVertVel *= -1;
				dudeTop = 0 * bufferSize;
				dudeBottom = 10 * bufferSize;
			}
			dudeVertVel += 1;

			// Wrapping
			if (dudeLeft >= 292) {
				dudeLeft -= 292;
				dudeRight -= 292;
			} else if (dudeLeft <= 0) {
				dudeLeft += 292;
				dudeRight += 292;
			}

			// Clearing
			for (i = dudeLeftPrev; i < dudeRightPrev; i++) {
				for (j = dudeTopPrev; j < dudeBottomPrev; j += bufferSize) {
					if ((i < dudeLeft || i >= dudeRight) || (j < dudeTop || j >= dudeBottom)) {
						*(base + i*2 + j*2) = 0x00000000;
						*(base + i*2 + j*2 + 1) = 0x00000000;
						*(base + i*2 + j*2 + bufferSize) = 0x00000000;
						*(base + i*2 + j*2 + bufferSize + 1) = 0x00000000;
					}
				}
			}

			// Drawing
			for (i = dudeLeft; i < dudeRight; i++) {
				for (j = dudeTop; j < dudeBottom; j += bufferSize) {
					*(base + i*2 + j*2) = 0xffffffff;
					*(base + i*2 + j*2 + 1) = 0xffffffff;
					*(base + i*2 + j*2 + bufferSize) = 0xffffffff;
					*(base + i*2 + j*2 + bufferSize + 1) = 0xffffffff;
				}
			}
			if (n % 32 == 0) {
				xil_printf("%d\r\n", n);
			}
			n++;

			dudeLeftPrev = dudeLeft;
			dudeRightPrev = dudeRight;
			dudeTopPrev = dudeTop;
			dudeBottomPrev = dudeBottom;

			xil_printf("%d %d\r\n", input0Base[0], input0Base[1]);
			usleep(15000);
	    }

   XCACHE_DISABLE_ICACHE();
   XCACHE_DISABLE_DCACHE();
   xil_printf("Returning\r\n");
   return 0;
}

/*****************************************************************************
*
* This function initializes the LCD screen and prints a text on it
*
* @param    First_Line, Second_Line are pointers to the strings to be printed
*           on the LCD screen
*
* @return   None
*
* @note     None
*
******************************************************************************/

void LCDInitAndPrint (char * First_Line, char * Second_Line)
{

   LCDOff();
   LCDClear();
   LCDOn();
   LCDInit();
   LCDPrintString   (First_Line, Second_Line);

}

/*****************************************************************************/
/**
* Write a string of characters to the TFT.
*
* @param	InstancePtr is a pointer to the XTft instance.
* @param	CharValue is a pointer to the character array to be written
*		to the TFT screen.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if unsuccessful.
*
* @note		None.
*
******************************************************************************/
int TftWriteString(XTft *InstancePtr, const u8 *CharValue)
{
	/*
	 * Writes a character from the string to the screen
	 * until it reaches null or end of the string.
	 */
	while (*CharValue != 0) {
		XTft_Write(InstancePtr, *CharValue);
		CharValue++;
	}

	return XST_SUCCESS;
}
