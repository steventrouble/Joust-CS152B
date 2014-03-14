/******************************************************************************
*
*       XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
*       AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
*       SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
*       OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
*       APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
*       THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
*       AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
*       FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
*       WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
*       IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
*       REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
*       INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*       FOR A PARTICULAR PURPOSE.
*
*       (c) Copyright 2007 Xilinx Inc.
*       All rights reserved.
*
******************************************************************************/

#include <stdio.h>
#include "sleep.h"
#include "xgpio_l.h"
#include "xparameters.h"

#include "lcd.h"

// usec delay timer during initialization, important to change if
// clock speed changes
#define INIT_DELAY 10000 
#define INST_DELAY 1000    //usec delay timer between instructions
#define DATA_DELAY 1000    //usec delay timer between data

#define XGpio_mSetDataDirection(BaseAddress, Channel, DirectionMask) 	\
	XGpio_WriteReg((BaseAddress), 					\
	(((Channel) - 1) * XGPIO_CHAN_OFFSET) + XGPIO_TRI_OFFSET, 	\
	(DirectionMask))

#define XGpio_mSetDataReg(BaseAddress, Channel, Data) 			\
	XGpio_WriteReg((BaseAddress), 					\
	(((Channel) - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET,	\
	(Data))

/*
#------------------------------------------------------------------------------
# IO Pad Location Constraints / Properties for Character LCD GPIO
#------------------------------------------------------------------------------

Net Char_LCD_GPIO_IO<0> LOC = AA5 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_E
Net Char_LCD_GPIO_IO<1> LOC = V7 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_RS
Net Char_LCD_GPIO_IO<2> LOC = W6 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_RW
Net Char_LCD_GPIO_IO<3> LOC = AD7 | IOSTANDARD=LVCMOS33 |TIG | PULLDOWN; #LCD_D7
Net Char_LCD_GPIO_IO<4> LOC = AC7 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_D6
Net Char_LCD_GPIO_IO<5> LOC = AC5 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_D5
Net Char_LCD_GPIO_IO<6> LOC = AB6 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_D4
Net Char_LCD_GPIO_IO<7> LOC = AC4 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_D3
Net Char_LCD_GPIO_IO<8> LOC = AB5 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_D2
Net Char_LCD_GPIO_IO<9> LOC = AB7 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_D1
Net Char_LCD_GPIO_IO<10> LOC = Y8 | IOSTANDARD=LVCMOS33 | TIG | PULLDOWN; #LCD_D0
*/

//==============================================================================
//
//								INTERNAL FUNCTIONS
//
//==============================================================================

void WaitForBusyFlag(void)
{
	Xuint32 LCD_Status;

	XGpio_mSetDataDirection(LCD_BASEADDR, 1, 0xFFFFF8FF);
	XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
    usleep(10);
	XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000500);
    usleep(10);
	LCD_Status = XGpio_ReadReg(LCD_BASEADDR, 1);
    usleep(10);
	XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
    usleep(10);
	//xil_printf("\r\nLCD status = 0x%X", LCD_Status);
		
	while (LCD_Status & 0x00000080){
		XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
	    usleep(10);
		XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000500);
	    usleep(10);
		LCD_Status = XGpio_ReadReg(LCD_BASEADDR, 1);
		//xil_printf("\r\nLCD status = 0x%X", LCD_Status);
		XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
	    usleep(10);
	}
	//set LCD data to output again
	XGpio_mSetDataDirection(LCD_BASEADDR, 1, 0xFFFFF800);
}

void InitInst(void)
{

	Xuint32 LCD_Status;

/* 4-bit mode
    XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000003); //function set 4-bit mode,
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000043); //set enable and data
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000003);
    usleep(INIT_DELAY);
*/
	XGpio_mSetDataDirection(LCD_BASEADDR, 1, 0xFFFFF800);
	
    XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x0000003C);//function set, 8-bit mode, 2 lines, 8 X 11 dots
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x0000043C); //set enable and data
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x0000003C);

	//read the Busy Flag
	XGpio_mSetDataDirection(LCD_BASEADDR, 1, 0xFFFFF8FF);
	XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
	XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000500);
	LCD_Status = XGpio_ReadReg(LCD_BASEADDR, 1);
	//xil_printf("\r\nLCD status = 0x%X", LCD_Status);

	XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
	while (LCD_Status & 0x00000080){
		XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
		XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000500);
		LCD_Status = XGpio_ReadReg(LCD_BASEADDR, 1);
		//xil_printf("\r\nLCD status = 0x%X", LCD_Status);
		XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000100);
	}
	//set LCD data to output again
	XGpio_mSetDataDirection(LCD_BASEADDR, 1, 0xFFFFF800);
}

//write instruction on 8 bits
void WriteInst8(unsigned long inst)
{
    unsigned long printinst;

	XGpio_WriteReg((LCD_BASEADDR),
		(((1) - 1) * XGPIO_CHAN_OFFSET) + XGPIO_TRI_OFFSET,
		(0xFFFFF800));
    
    printinst = 0x00000400 | inst;

    XGpio_mSetDataReg(LCD_BASEADDR, 1, inst);      //write data
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, printinst);  //set enable
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, inst);      //turn off enable
    usleep(10);

	WaitForBusyFlag();

//    usleep(INST_DELAY);	
}


void WriteInst(unsigned long inst1, unsigned long inst2)
{
    unsigned long printinst;

    printinst = 0x00000040 | inst1;

    XGpio_mSetDataReg(LCD_BASEADDR, 1, inst1);      //write data
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, printinst);  //set enable
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, inst1);      //turn off enable
    usleep(10);

    printinst = 0x00000040 | inst2;

    XGpio_mSetDataReg(LCD_BASEADDR, 1, printinst);  //set enable and data
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, inst2);      //turn off enable

    usleep(INST_DELAY);	
}

void WriteData8(unsigned long data)
{
    unsigned long rs_data, enable_rs_data;
    //	int busy=true;	

    rs_data = 0x00000200 | data; //sets rs, data1
    enable_rs_data = 0x00000600 | data;

    XGpio_mSetDataReg(LCD_BASEADDR, 1, rs_data); //write data, rs
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, enable_rs_data); //set enable, keep data, rs
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, rs_data); //turn off enable
    usleep(10);

	WaitForBusyFlag();
//    usleep(DATA_DELAY);
}

void WriteData(unsigned long data1, unsigned long data2)
{
    unsigned long rs_data, enable_rs_data;
    //	int busy=true;	

    rs_data = 0x00000020 | data1; //sets rs, data1
    enable_rs_data = 0x00000060 | data1;

    XGpio_mSetDataReg(LCD_BASEADDR, 1, rs_data); //write data, rs
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, enable_rs_data); //set enable, keep data, rs
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, rs_data); //turn off enable
    usleep(10);

    rs_data = 0x00000020 | data2; //sets rs, data2
    enable_rs_data = 0x00000060 | data2; //sets rs, data2

    XGpio_mSetDataReg(LCD_BASEADDR, 1, enable_rs_data); //set enable, rs, data
    usleep(10);
    XGpio_mSetDataReg(LCD_BASEADDR, 1, rs_data); //turn off enable

    usleep(DATA_DELAY);
}

//==================================================================================
//
//								EXTERNAL FUNCTIONS
//
//==================================================================================

void LCDOn()
{
    //printf("DISPLAY ON\r\n");
//    WriteInst(0x00000000, 0x0000000E);
    WriteInst8(0x0000000E); //display on, cursor on, cursor blink off
}

void LCDOff()
{
    // printf("DISPLAY OFF\r\n");
//    WriteInst(0x00000000, 0x00000008);
    WriteInst8(0x00000008); //display off, cursor off
}

void LCDClear()
{
    // printf("DISPLAY CLEAR\r\n");
//    WriteInst(0x00000000, 0x00000001);
//    WriteInst(0x00000000, 0x00000010);

    WriteInst8(0x00000001); //clear display
    WriteInst8(0x00000002); //return home


}

void LCDInit()
{
    // Sets CHAR LCD Reg to Write Mode
    XGpio_mSetDataDirection(LCD_BASEADDR, 1, 0x00000000);
    // Zeroes CHAR LCD Reg
    XGpio_mSetDataReg(LCD_BASEADDR, 1, 0x00000000);

    // LCD INIT
    usleep(15000);  //After VCC>4.5V Wait 15ms to Init Char LCD
    InitInst();
    
    usleep(4100);   //Wait 4.1ms
    InitInst();
    usleep(100);    //Wait 100us
    InitInst();
    InitInst();

    // Function Set
//    WriteInst(0x00000002, 0x00000002);
	WriteInst8(0x00000038);

    // Display Off
//    WriteInst(0x00000000, 0x00000008);
	WriteInst8(0x00000008);
	
    // Display Clear
//    WriteInst(0x00000000, 0x00000001);
	WriteInst8(0x00000001);
	
    // Entry Mode Set
//    WriteInst(0x00000000, 0x00000006);
	WriteInst8(0x00000006); //cursor moves right, no shift

    // Display On
//    WriteInst(0x00000000, 0x0000000E);
    WriteInst8(0x0000000E);//display on, cursor on, cursor blink off
}

void LCDEnableDisplayShift()
{
	WriteInst8(0x00000007); //cursor moves right, shift enabled
}
void LCDEnableCursorBlink()
{
	WriteInst8(0x0000000F);//display on, cursor on, cursor blink on
}

void LCDDisableDisplayShift()
{
	WriteInst8(0x00000006); //cursor moves right, no shift
	
}
void LCDDisableCursorBlink()
{
    WriteInst8(0x0000000E);//display on, cursor on, cursor blink off	
}



void MoveCursorHome()
{
//    WriteInst(0x00000000, 0x00000002);
    WriteInst8(0x00000002);  
}

void MoveCursorLeft()
{
//    WriteInst(0x00000001, 0x00000000);
	WriteInst8(0x00000010);
}

void MoveCursorRight()
{
//    WriteInst(0x00000001, 0x00000004);
    WriteInst8(0x00000014);  
}

void LCDSetLine(int line)
{
    //line1 = 1, line2 = 2
    int i;

    if((line - 1))
    {
         MoveCursorHome();
	 for(i=0; i<40; i++)
	 {
	      MoveCursorRight();
	 }
    }
    else
    {
         MoveCursorHome();
    }

}

void LCDPrintChar(char c)
{
//    WriteData(((c >> 4) & 0x0000000F), (c & 0x0000000F));
	 WriteData8(c);
}

void LCDPrintString(char * line1, char * line2)
{
    int i=0;

    LCDSetLine(1);

    for(i=0; i<16; i++)
    {
         if(line1[i])
              LCDPrintChar(line1[i]);
         else
	      break;
    }
i=0;	
//xil_printf ("\r\nFirst Line printed");
     LCDSetLine(2);

//	WriteInst8(0x000000C0);
	
    for(i=0; i<16; i++)
    {
         if(line2[i])
              LCDPrintChar(line2[i]);
         else
              break;
    }	
//xil_printf ("\r\nSecond Line printed");
    return;
}



