
 

#include "xparameters.h"
#include "xio.h"
#include "xbasic_types.h"
#include "xstatus.h"
#include "stdio.h"
#include "lcd.h"
#include "xtft_hw.h"
#include "xtft.h"

#define FLASH_BASEADDR XPAR_FLASH_MEM0_BASEADDR
#define FLASH_START_ADDR 0x1F0000
#define MEM_BASEADDR XPAR_DDR2_SDRAM_MPMC_BASEADDR

#define BITMAP_FILE_SIZE_OFFSET 0x0002
#define BITMAP_DATA_OFFSET 0x000A
#define BITMAP_WIDTH_OFFSET 0x0012
#define BITMAP_HEIGHT_OFFSET 0x0016
#define BITMAP_BITS_PER_PIXEL_OFFSET 0x001C
#define BITMAP_IMAGE_SIZE_OFFSET 0x0022

#define MEM_ROW_WIDTH 1024
#define MEM_DISPLAYED_ROW_WIDTH 640
#define MEM_DISPLAYED_HEIGHT 480

/******************************************************************************
 * 
 * 	Variable declaration
 * 
 * ***************************************************************************/

extern unsigned char verbose;
extern XTft TftInstance;

/*****************************************************************************
 * 
 * 	Function declaration
 * 
 * ***************************************************************************/

Xuint32 Read_Bitmap_Header_Bytes(Xuint32 FLASH_ADDR, Xuint32 offset)
{
Xuint32 Bitmap_Header_Data;
Xuint8 Flash_Data;

XIo_Out16 (FLASH_ADDR, 0xFF);
Flash_Data = XIo_In8(FLASH_ADDR + offset);
Bitmap_Header_Data = 0x00000000 | Flash_Data;
Flash_Data = XIo_In8(FLASH_ADDR + offset + 1);
Bitmap_Header_Data = Bitmap_Header_Data | (Flash_Data << 8);
Flash_Data = XIo_In8(FLASH_ADDR + offset + 2);
Bitmap_Header_Data = Bitmap_Header_Data | (Flash_Data << 16);
Flash_Data = XIo_In8(FLASH_ADDR + offset + 3);
Bitmap_Header_Data = Bitmap_Header_Data | (Flash_Data << 24);


}

Xuint32 Decode_display_bitmap(XTft * InstancePtr, Xuint32 FRAME_ADDR)
{

Xuint16 Flash_Data;
Xuint8  Pixel_R;
Xuint8  Pixel_G;
Xuint8  Pixel_B;
Xuint32 Pixel_Data0, Pixel_Data1, Pixel_Data2;
Xuint32 temp;
Xuint32 Pixel_Data;
Xuint32 Bitmap_File_Size;
Xuint32 Bitmap_Data_Offset;
Xuint32 Bitmap_Width_Pixels;
Xuint32 Bitmap_Height_Pixels;
Xuint16 Bitmap_Bits_Per_Pixel;
Xuint32 Bitmap_Image_Size;
Xuint32 Bytes_Per_Row;
Xuint32 MEM_ADDR;
Xuint32 MEM_HIGHADDR;

Xuint32 i, j, k;


if (verbose) xil_printf ("\r\nDecoding bitmap");

//reset FLASH to read mode
XIo_Out16 (XPAR_FLASH_MEM0_BASEADDR, 0xFF);

Flash_Data = XIo_In16(XPAR_FLASH_MEM0_BASEADDR+FLASH_START_ADDR);
if (verbose) xil_printf("\r\nFile Type is 0x%X", Flash_Data);

//check if the bitmap is present in the FLASH memory by checking for the 'B' and 'M' characters
//at the beginnig of the file location
if (Flash_Data != 0x424d)
{
   if (verbose) xil_printf("\r\nBitmap was not found in the FLASH memory, data found in the FLASH memory is 0x%X", Flash_Data);	

return 1;
}

//determine bitmap parameters
Bitmap_File_Size = Read_Bitmap_Header_Bytes(FLASH_BASEADDR+FLASH_START_ADDR, BITMAP_FILE_SIZE_OFFSET);
//Bitmap_File_Size = XIo_In32(XPAR_FLASH_MEM0_BASEADDR+FLASH_START_ADDR+BITMAP_FILE_SIZE_OFFSET);
if (verbose) xil_printf("\r\nFile Size is 0x%X", Bitmap_File_Size);

Bitmap_Data_Offset = Read_Bitmap_Header_Bytes(FLASH_BASEADDR+FLASH_START_ADDR, BITMAP_DATA_OFFSET);
if (verbose) xil_printf("\r\nBitmap Data Offset is 0x%X", Bitmap_Data_Offset);

Bitmap_Width_Pixels = Read_Bitmap_Header_Bytes(FLASH_BASEADDR+FLASH_START_ADDR, BITMAP_WIDTH_OFFSET);
if (verbose) xil_printf("\r\nBitmap Width in pixels is %d", Bitmap_Width_Pixels);

Bitmap_Height_Pixels = Read_Bitmap_Header_Bytes(FLASH_BASEADDR+FLASH_START_ADDR, BITMAP_HEIGHT_OFFSET);
if (verbose) xil_printf("\r\nBitmap Height in pixels is %d", Bitmap_Height_Pixels);

Bitmap_Bits_Per_Pixel = XIo_In16(FLASH_BASEADDR + FLASH_START_ADDR + BITMAP_BITS_PER_PIXEL_OFFSET);
Bitmap_Bits_Per_Pixel = Bitmap_Bits_Per_Pixel >> 8;
if (verbose) xil_printf("\r\nBitmap Bits per pixel is %d", Bitmap_Bits_Per_Pixel);

Bitmap_Image_Size = Read_Bitmap_Header_Bytes(FLASH_BASEADDR+FLASH_START_ADDR, BITMAP_IMAGE_SIZE_OFFSET);
if (verbose) xil_printf("\r\nBitmap image size is %d", Bitmap_Image_Size);

Bytes_Per_Row = Bitmap_Image_Size / Bitmap_Height_Pixels;
if (verbose) xil_printf("\r\nBytes per row = %d", Bytes_Per_Row);

MEM_HIGHADDR = (MEM_ROW_WIDTH * MEM_DISPLAYED_HEIGHT) * 4;

//start loading the image in reverse order, because the bitmap data is stored in reverse order
//therefore set the current address to the beginning of the highest line in the frame and
//increment at each pixel in the line, then decrement with a line at the end of each line
MEM_ADDR = MEM_HIGHADDR - (MEM_ROW_WIDTH * 4);

if (verbose) xil_printf("\r\nImage Memory High address = 0x%X, Current Address = 0x%X", MEM_HIGHADDR, MEM_ADDR);

LCDSetLine(2);

for (i = 0;  i<(Bitmap_Height_Pixels * Bytes_Per_Row); i = i + Bytes_Per_Row)
{
	//read three bytes from the FLASH memory that represent B, G and R data for a pixel
	for (j = 0; j <Bytes_Per_Row; j = j + 3)
	{
		Pixel_B = XIo_In8(FLASH_BASEADDR + FLASH_START_ADDR + Bitmap_Data_Offset + i + j);
		Pixel_G = XIo_In8(FLASH_BASEADDR + FLASH_START_ADDR + Bitmap_Data_Offset + i + (j+1));
	    Pixel_R = XIo_In8(FLASH_BASEADDR + FLASH_START_ADDR + Bitmap_Data_Offset + i + (j+2));

		Pixel_Data = ((0x00000000 | Pixel_R) << 16) | ((0x00000000 | Pixel_G) << 8) | (0x00000000 | Pixel_B);
		
		XIo_Out32(FRAME_ADDR + MEM_ADDR, Pixel_Data);
		//increment one pixel
		MEM_ADDR = MEM_ADDR + 4;
	}
	//if (verbose) xil_printf("\r\nCurrent MEM_ADDR value is 0x%X", MEM_ADDR);
	//decrement with one line
	MEM_ADDR = MEM_ADDR - ((MEM_DISPLAYED_ROW_WIDTH + MEM_ROW_WIDTH) * 4);	
	//if (verbose) xil_printf("\r\nMEM_ADDR value is 0x%X", MEM_ADDR);
	
	if (!(i&0xFFF))
	{
		LCDPrintChar('*');
		xil_printf(".");
	}

}

//set the base address of the TFT device to the beginning of the bitmap image
XTft_SetFrameBaseAddr(InstancePtr, FRAME_ADDR);
//XIo_Out32 (XPAR_XPS_TFT_0_SPLB_BASEADDR, XPAR_DDR2_SDRAM_MPMC_BASEADDR + MEM_START_ADDR);

if (verbose) xil_printf("\r\nMEM_ADDR value is 0x%X", MEM_ADDR);


return 0;

}

