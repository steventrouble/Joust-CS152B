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

#include <math.h>
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
#include "ac97_if_00.h"
/************************** Constant Definitions ****************************/
/**
 * The following constants maps to the XPAR parameter created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */

#define TFT_DEVICE_ID	XPAR_TFT_0_DEVICE_ID

//The upper three memory regions of 2MB in the DDR2 are defined to display
//the colorbar, bitmap and a drawing

#define AC97_CODEC_BASEADDR XPAR_AC97_IF_00_0_BASEADDR
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

#define XGpio_mSetDataReg(BaseAddress, Channel, Data) 			\
	XGpio_WriteReg((BaseAddress), 					\
	(((Channel) - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET,	\
	(Data))

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
	int *stage = base + FRAME_SIZE;

	const int bufferSize = 1024;
	const int screenLeft = 174;
	const int screenTop = 120 * bufferSize;
	const int screenBottom = (120+240) * bufferSize;
	const int screenRight = 174+292;

	int dudeLeft = 0;//79;
	int dudeTop = 100 * bufferSize;//184 * bufferSize;
	int dudeRight = dudeLeft + 15;
	int dudeBottom = dudeTop + 20*bufferSize;

	int dudeVertVel = 0;
	int dudeHorizVel = 0;
	const int MAX_HORIZ_VEL = 10;

	int dudeLeftPrev = 0;
	int dudeTopPrev = 0;
	int dudeRightPrev = 0;
	int dudeBottomPrev = 0;

	int n = 0;

	// For iterating the screen
	int i, j;
	// For iterating a texture
	int it, jt;


	int jump = 0;
	int jumpPrev = 0;


	int note [5][3];
	note [0][0] = 349;
	note [1][0]= 261;
	note [2][0]= 415;
	note [3][0]= 392;
	note [4][0]= 0;


	note [0][1] = 51;
	note [1][1]= 17;
	note [2][1]= 34;
	note [3][1]= 34;
	note [4][1]= 51;

	note [0][2] = 51;
	note [1][2]= 17;
	note [2][2]= 34;
	note [3][2]= 34;
	note [4][2]= 51;

	int noteIndex = 0;

	// Copy sprites to alternate staging area
	for (i = 0; i < 640; i++) {
		for (j = 0; j < 60 * bufferSize; j+=1024) {
			// Copy sprite
			*(stage + i + j) = *(base + i*2 + j*2);

			// Blank out pixel
			*(base + i*2 + j*2) = 0x00000000;
			*(base + i*2 + j*2 + 1) = 0x00000000;
			*(base + i*2 + j*2 + bufferSize) = 0x00000000;
			*(base + i*2 + j*2 + bufferSize + 1) = 0x00000000;
		}
	}

	int* getBase[] = {0, 20, 40, 60};
	int* getBaseReverse[] = {180, 200, 220, 240};

	int animFrame = 0;

	while (n < 50)
	    {

			Xuint32 stuff = XGpio_ReadReg(XPAR_INPUT_JOYSTICK_GPIO_BASEADDR, 1);
			xil_printf("%x\r\n", stuff);
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

			// Sing us a song, you're the piano man
			if(note[noteIndex][1]>0){
				note[noteIndex][1]--;
				if(noteIndex!=4){
					int freq = note[noteIndex][0];
					if (jump && !jumpPrev)
						GenSquare (AC97_CODEC_BASEADDR, BOTH_CHANNELS, 1000, 15);
					else
						GenSquare (AC97_CODEC_BASEADDR, BOTH_CHANNELS, freq, 15);
					usleep(10000);
				} else {
					usleep(15000);
				}
			}
			else{

				if(noteIndex!=4){
					int freq = note[noteIndex][0];
					if (jump == 1 && !jumpPrev)
						GenSquare (AC97_CODEC_BASEADDR, BOTH_CHANNELS, 1000, 15);
					else
						GenSquare (AC97_CODEC_BASEADDR, BOTH_CHANNELS, freq, 15);
					usleep(10000);
				} else {
					usleep(15000);
				}

				note[noteIndex][1] = note[noteIndex][2];
				if(noteIndex !=4){
					noteIndex++;
				}
				else{
					noteIndex =0;
				}
			}

			// Jump
			int grounded = 0;
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

			// Vertical Collisions + Gravity
			if (dudeVertVel > 0) {
				if (dudeBottom >= 204 * bufferSize) { // Bottom Platform
					dudeVertVel = 0;
					dudeBottom = 204 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				} else if (dudeBottom >= 62 * bufferSize && dudeBottom <= 68 * bufferSize && dudeRight >= 0 && dudeLeft <= 32) { // Platform 1
					dudeVertVel = 0;
					dudeBottom = 62 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				} else if (dudeBottom >= 74 * bufferSize && dudeBottom <= 83 * bufferSize && dudeRight >= 87 && dudeLeft <= 184) { // Platform 2
					dudeVertVel = 0;
					dudeBottom = 74 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				} else if (dudeBottom >= 62 * bufferSize && dudeBottom <= 68 * bufferSize && dudeRight >= 270 && dudeLeft <= 340) { // Platform 3
					dudeVertVel = 0;
					dudeBottom = 62 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				} else if (dudeBottom >= 131 * bufferSize && dudeBottom <= 138 * bufferSize && dudeRight >= 0 && dudeLeft <= 65) { // Platform 4
					dudeVertVel = 0;
					dudeBottom = 131 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				} else if (dudeBottom >= 156 * bufferSize && dudeBottom <= 162 * bufferSize && dudeRight >= 110 && dudeLeft <= 179) { // Platform 5
					dudeVertVel = 0;
					dudeBottom = 156 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				} else if (dudeBottom >= 122 * bufferSize && dudeBottom <= 125 * bufferSize && dudeRight >= 215 && dudeLeft <= 270) { // Platform 6
					dudeVertVel = 0;
					dudeBottom = 122 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				} else if (dudeBottom >= 131 * bufferSize && dudeBottom <= 136 * bufferSize && dudeRight >= 274 && dudeLeft <= 340) { // Platform 7
					dudeVertVel = 0;
					dudeBottom = 131 * bufferSize;
					dudeTop = dudeBottom - 20 * bufferSize;
					grounded = 1;
				}
			} else {
				if (dudeTop < 0) { // Top Boundary
					dudeVertVel *= -1;
					//dudeVertVel += 6;
					dudeTop = 0 * bufferSize;
					dudeBottom = 10 * bufferSize;
				} else if (dudeTop >= 63 * bufferSize && dudeTop < 69 * bufferSize && dudeRight >= 0 && dudeLeft <= 32) { // Platform 1
					dudeVertVel *= -1;
					dudeTop = 69 * bufferSize;
					dudeBottom = dudeTop + 20 * bufferSize;
				} else if (dudeTop >= 75 * bufferSize && dudeTop < 84 * bufferSize && dudeRight >= 87 && dudeLeft <= 184) { // Platform 2
					dudeVertVel *= -1;
					dudeTop = 84 * bufferSize;
					dudeBottom = dudeTop + 20 * bufferSize;
				} else if (dudeTop >= 63 * bufferSize && dudeTop < 69 * bufferSize && dudeRight >= 270 && dudeLeft <= 340) { // Platform 3
					dudeVertVel *= -1;
					dudeTop = 69 * bufferSize;
					dudeBottom = dudeTop + 20 * bufferSize;
				} else if (dudeTop >= 132 * bufferSize && dudeTop < 139 * bufferSize && dudeRight >= 0 && dudeLeft <= 65) { // Platform 4
					dudeVertVel *= -1;
					dudeTop = 139 * bufferSize;
					dudeBottom = dudeTop + 20 * bufferSize;
				} else if (dudeTop >= 157 * bufferSize && dudeTop < 163 * bufferSize && dudeRight >= 110 && dudeLeft <= 179) { // Platform 5
					dudeVertVel *= -1;
					dudeTop = 163 * bufferSize;
					dudeBottom = dudeTop + 20 * bufferSize;
				} else if (dudeTop >= 123 * bufferSize && dudeTop < 132 * bufferSize && dudeRight >= 215 && dudeLeft <= 270) { // Platform 6
					dudeVertVel *= -1;
					dudeTop = 132 * bufferSize;
					dudeBottom = dudeTop + 20 * bufferSize;
				} else if (dudeTop >= 132 * bufferSize && dudeTop < 137 * bufferSize && dudeRight >= 274 && dudeLeft <= 340) { // Platform 7
					dudeVertVel *= -1;
					dudeTop = 137 * bufferSize;
					dudeBottom = dudeTop + 20 * bufferSize;
				}
			}
			dudeVertVel += 1;

			// Horizontal Collisions
			if (dudeHorizVel > 0) {
				if (dudeBottom >= 75 * bufferSize && dudeTop <= 83 * bufferSize && dudeRight >= 87 && dudeRight <= 184) { // Platform 2
					dudeHorizVel *= -1;
					dudeRight = 87;
					dudeLeft = dudeRight - 15;
				} else if (dudeBottom >= 63 * bufferSize && dudeTop <= 68 * bufferSize && dudeRight >= 270 && dudeRight <= 340) { // Platform 3
					dudeHorizVel *= -1;
					dudeRight = 270;
					dudeLeft = dudeRight - 15;
				} else if (dudeBottom >= 157 * bufferSize && dudeTop <= 162 * bufferSize && dudeRight >= 110 && dudeRight <= 179) { // Platform 5
					dudeHorizVel *= -1;
					dudeRight = 110;
					dudeLeft = dudeRight - 15;
				} else if (dudeBottom >= 124 * bufferSize && dudeTop <= 131 * bufferSize && dudeRight >= 215 && dudeRight <= 270) { // Platform 6
					dudeHorizVel *= -1;
					dudeRight = 215;
					dudeLeft = dudeRight - 15;
				} else if (dudeBottom >= 132 * bufferSize && dudeTop <= 136 * bufferSize && dudeRight >= 274 && dudeRight <= 340) { // Platform 7
					dudeHorizVel *= -1;
					dudeRight = 274;
					dudeLeft = dudeRight - 15;
				}
			} else {
				if (dudeBottom > 64 * bufferSize && dudeTop < 69 * bufferSize && dudeLeft >= 0 && dudeLeft <= 32) { // Platform 1
					dudeHorizVel *= -1;
					dudeLeft = 32;
					dudeRight = dudeLeft + 15;
				} else if (dudeBottom > 75 * bufferSize && dudeTop < 82 * bufferSize && dudeLeft >= 87 && dudeLeft <= 184) { // Platform 2
					dudeHorizVel *= -1;
					dudeLeft = 184;
					dudeRight = dudeLeft + 15;
				} else if (dudeBottom > 133 * bufferSize && dudeTop < 137 * bufferSize && dudeLeft >= 0 && dudeLeft <= 65) { // Platform 4
					dudeHorizVel *= -1;
					dudeLeft = 65;
					dudeRight = dudeLeft + 15;
				} else if (dudeBottom > 158 * bufferSize && dudeTop < 161 * bufferSize && dudeLeft >= 110 && dudeLeft <= 179) { // Platform 5
					dudeHorizVel *= -1;
					dudeLeft = 179;
					dudeRight = dudeLeft + 15;
				} else if (dudeBottom > 124 * bufferSize && dudeTop < 131 * bufferSize && dudeLeft >= 215 && dudeLeft <= 270) { // Platform 6
					dudeHorizVel *= -1;
					dudeLeft = 270;
					dudeRight = dudeLeft + 15;
				}
			}

			// Wrapping
			if (dudeLeft > 320) {
				dudeLeft -= 335;
				dudeRight -= 335;
			} else if (dudeRight < 0) {
				dudeLeft += 335;
				dudeRight += 335;
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

			int animOffset = 0;
			if (grounded) {
				if (dudeHorizVel >= 0) {
					animFrame += dudeHorizVel;
					if (animFrame >= 3*8) {
						animFrame -= 3*8;
					}
					animOffset = getBase[animFrame/8];
				} else {
					animFrame += -dudeHorizVel;
					if (animFrame >= 3*8) {
						animFrame -= 3*8;
					}
					animOffset = getBaseReverse[animFrame/8];
				}
			} else {
				if (dudeHorizVel >= 0) {
					if (jump) {
						animOffset = 99;
					} else {
						animOffset = 121;
					}
				} else {
					if (jump) {
						animOffset = 281;
					} else {
						animOffset = 300;
					}
				}
			}


			// Drawing
			for (i = dudeLeft, it = 2; i < dudeRight; i++, it++) {
				for (j = dudeTop, jt = bufferSize; j < dudeBottom; j += bufferSize, jt += bufferSize) {
					int pixelColor = *(stage + it + jt + animOffset);
					*(base + i*2 + j*2) = pixelColor;
					*(base + i*2 + j*2 + 1) = pixelColor;
					*(base + i*2 + j*2 + bufferSize) = pixelColor;
					*(base + i*2 + j*2 + bufferSize + 1) = pixelColor;
				}
			}
			if (n % 32 == 0) {
				//xil_printf("%d\r\n", n);
			}
			n++;


			dudeLeftPrev = dudeLeft;
			dudeRightPrev = dudeRight;
			dudeTopPrev = dudeTop;
			dudeBottomPrev = dudeBottom;

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




void GenerateSound(){
	XStatus Status;
	while (!(AC97_Link_Is_Ready (AC97_CODEC_BASEADDR)));
	   //set TAG and ID to 0x7C in order to access the AC'97 codec internal registers
	AC97_Set_Tag_And_Id (AC97_CODEC_BASEADDR, 0x7C);

	   //unmute the Master, Output and Headphone channels
	Status = AC97_Unmute (AC97_CODEC_BASEADDR, AC97_MASTER_VOLUME_OFFSET);
	Status = AC97_Unmute (AC97_CODEC_BASEADDR, AC97_HEADPHONE_VOLUME_OFFSET);
	Status = AC97_Unmute (AC97_CODEC_BASEADDR, AC97_PCM_OUT_VOLUME_OFFSET);

	   //set the volume on these channels
	Status = AC97_Set_Volume (AC97_CODEC_BASEADDR, AC97_MASTER_VOLUME_OFFSET,
	   						     BOTH_CHANNELS, VOLUME_MAX);
	Status = AC97_Set_Volume (AC97_CODEC_BASEADDR, AC97_HEADPHONE_VOLUME_OFFSET,
	   						     BOTH_CHANNELS, VOLUME_MAX);
	Status = AC97_Set_Volume (AC97_CODEC_BASEADDR, AC97_PCM_OUT_VOLUME_OFFSET,
	   						     BOTH_CHANNELS, VOLUME_MAX);

	//set the volume on the LINE IN input
	Status = AC97_Set_Volume (AC97_CODEC_BASEADDR, AC97_LINE_IN_VOLUME_OFFSET,
	   						     BOTH_CHANNELS, VOLUME_MAX);
	   	//set the volume on the MIC input and allow 20db boost
	Status = AC97_Set_Volume (AC97_CODEC_BASEADDR, AC97_MIC_VOLUME_OFFSET,
	   						     BOTH_CHANNELS, (1 << boost20dB) | VOLUME_MAX);

		//set record gain
	Status = AC97_Set_Volume (AC97_CODEC_BASEADDR, AC97_RECORD_GAIN_OFFSET,
	   						     BOTH_CHANNELS, GAIN_MIN);

	   //set 3D and unselect loopback
	Status = AC97_WriteReg (AC97_CODEC_BASEADDR, 0x20, 0x2000);

	Status = AC97_Select_Input (AC97_CODEC_BASEADDR, BOTH_CHANNELS, AC97_MIC_SELECT);
	Status = AC97_Unmute (AC97_CODEC_BASEADDR, AC97_MIC_VOLUME_OFFSET);
	Status = AC97_Mute (AC97_CODEC_BASEADDR, AC97_LINE_IN_VOLUME_OFFSET);


}

