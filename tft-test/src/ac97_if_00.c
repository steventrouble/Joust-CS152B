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
#include "ac97_if_00.h"
#include "xparameters.h"
#include "xio.h"
#include "xbasic_types.h"
#include "xstatus.h"
#include "stdio.h"



char C;
Xuint32 Memory_Addr=0;
Xuint32 sample=0;
Xuint32 sample_num=0;

extern unsigned char verbose;

int AC97_Link_Is_Ready (Xuint32 AC97_Baseaddr )
{
Xuint32 STATUS;

	XIo_Out32 ((AC97_Baseaddr + AC97_TAG_AND_ID_OFFSET), 0x7C);
   STATUS = XIo_In32(AC97_Baseaddr + AC97_TAG_AND_ID_OFFSET);
   if (verbose) xil_printf ("\r\nAC97 link Status: 0x%X", STATUS);
   if (STATUS & 0x1000) return 1;
   else return 0;
}

void AC97_Wait_For_New_Frame (Xuint32 AC97_Baseaddr)
{
Xuint32 STATUS;
 STATUS = XIo_In32(AC97_Baseaddr + AC97_STATUS_OFFSET);
   STATUS = STATUS & 0xFFFFFFFD;
   XIo_Out32 ((AC97_Baseaddr + AC97_STATUS_OFFSET), STATUS);
   STATUS = XIo_In32(AC97_Baseaddr + AC97_STATUS_OFFSET);
   while (!(STATUS & 0x02)){
      STATUS = XIo_In32(AC97_Baseaddr + AC97_STATUS_OFFSET);
      }
}

void AC97_Set_Tag_And_Id (Xuint32 AC97_Baseaddr, Xuint16 TAG_AND_ID_DATA )
{
Xuint32 STATUS;

	XIo_Out32 ((AC97_Baseaddr + AC97_TAG_AND_ID_OFFSET), TAG_AND_ID_DATA);
}




int AC97_ReadReg (Xuint32 AC97_Baseaddr, Xuint32 Addr){


Xuint32 AC97_REG_DATA;
Xuint32 TAG_AND_ID_DATA;
Xuint32 STATUS;
Xuint32 ADDR;
Xuint32 i=0;  

   //clear STATUS register and wait for one more frame
	AC97_Wait_For_New_Frame (AC97_Baseaddr);

   //set tag data: bit 4 - valid data in at least one slot, bit 3 - valid address
   TAG_AND_ID_DATA = 0x60;
   AC97_Set_Tag_And_Id (AC97_Baseaddr, TAG_AND_ID_DATA );
   
   XIo_Out32 ((AC97_Baseaddr + AC97_CONFIG_DATA_OFFSET), 0x0);
   //set address register
   XIo_Out32 ((AC97_Baseaddr + AC97_ADDR_OFFSET), Addr);   
   //set RNW and LOAD;
   XIo_Out32 ((AC97_Baseaddr + AC97_CONTROL_OFFSET), 0x03);

   //wait until data has been received by polling bit 32 in the STATUS register
   //if bit 31 is cleared, then data was received
   STATUS = XIo_In32(AC97_Baseaddr + AC97_STATUS_OFFSET);
   while ((STATUS & 0x01)){
      STATUS = XIo_In32(AC97_Baseaddr + AC97_STATUS_OFFSET);
      i++;
      }

   //wait for a new frame again
  AC97_Wait_For_New_Frame (AC97_Baseaddr);



  AC97_REG_DATA = XIo_In32 (AC97_Baseaddr + AC97_CONFIG_DATA_OFFSET);

  return (AC97_REG_DATA >> 16);

}


int AC97_WriteReg (Xuint32 AC97_Baseaddr, Xuint32 Addr, Xuint16 DATA){


Xuint32 AC97_REG_DATA;
Xuint32 TAG_AND_ID_DATA;
Xuint32 STATUS;
Xuint32 ADDR;
Xuint32 i=0;  

   //clear STATUS register and wait for one more frame
   AC97_Wait_For_New_Frame (AC97_Baseaddr);


   //set tag data: bit 4 - valid data in at least one slot, bit 3 - valid address, bit 2 - valid data
   TAG_AND_ID_DATA = 0x70;
   AC97_Set_Tag_And_Id (AC97_Baseaddr, TAG_AND_ID_DATA );
   
   //set data register
   XIo_Out32 ((AC97_Baseaddr + AC97_CONFIG_DATA_OFFSET), DATA);
   //set address register
   XIo_Out32 ((AC97_Baseaddr + AC97_ADDR_OFFSET), Addr); 
   
   //clear RNW and set LOAD;
   XIo_Out32 ((AC97_Baseaddr + AC97_CONTROL_OFFSET), 0x01);

   //wait until data has been received by polling bit 32 in the STATUS register
   //if bit 31 is cleared, then data was received
   STATUS = XIo_In32(AC97_Baseaddr + AC97_STATUS_OFFSET);
   while ((STATUS & 0x01)){
      STATUS = XIo_In32(AC97_Baseaddr + AC97_STATUS_OFFSET);
      i++;
      }

   //Wait for two more frames
   AC97_Wait_For_New_Frame (AC97_Baseaddr);
   AC97_Wait_For_New_Frame (AC97_Baseaddr);

   AC97_REG_DATA = XIo_In32 (AC97_Baseaddr + AC97_CONFIG_DATA_OFFSET);

   return (AC97_REG_DATA >> 16);

}


int AC97_Select_Input (Xuint32 AC97_Baseaddr, char channel, char input)
{
//input can be  AC97_MIC_SELECT 0x00
//or  AC97_LINE_IN_SELECT	0x04	

Xuint16 register_data, temp;
Xuint16 DATA;

	temp = 0x0000 | input;
	if (channel == LEFT_CHANNEL) register_data = (temp << 8);
	else if (channel == RIGHT_CHANNEL) register_data = temp;
	else if (channel == BOTH_CHANNELS) register_data = (temp << 8) | temp; 
	else return 1;
	
    DATA = AC97_WriteReg (AC97_Baseaddr, AC97_INPUT_SELECT_OFFSET, register_data); //0x00 for microphone
    if (verbose) xil_printf ("\r\nData written to register AC97_INPUT_SELECT_OFFSET is 0x%X", DATA);
    DATA = AC97_ReadReg (AC97_Baseaddr, AC97_INPUT_SELECT_OFFSET);
    if (verbose) xil_printf ("\r\nData read from register AC97_INPUT_SELECT_OFFSET is 0x%X", DATA);
   return 0;
}

int AC97_Set_Volume (Xuint32 AC97_Baseaddr, char Volume_Reg, char channel, char volume)
{
//Volume_Reg values are:
//AC97_INPUT_SELECT_OFFSET		0x1A
//AC97_MASTER_VOLUME_OFFSET 		0x02
//AC97_HEADPHONE_VOLUME_OFFSET 	0x04
//AC97_MIC_VOLUME_OFFSET 			0x0e
//AC97_LINE_IN_VOLUME_OFFSET 		0x10
//AC97_PCM_OUT_VOLUME_OFFSET 		0x18
//AC97_RECORD_GAIN_OFFSET 		0x1C
Xuint16 register_data, temp;
Xuint16 DATA;
 
 	temp = 0x0000 | volume;
	if (channel == LEFT_CHANNEL) register_data = (temp << 8);
	else if (channel == RIGHT_CHANNEL) register_data = temp;
	else if (channel == BOTH_CHANNELS) register_data = (temp << 8) | temp; 
	else return 1;
	
	DATA = AC97_WriteReg (AC97_Baseaddr, Volume_Reg, register_data);
    if (verbose) xil_printf ("\r\nData written to register 0x%X is 0x%X", Volume_Reg, DATA);
    DATA = AC97_ReadReg (AC97_Baseaddr, Volume_Reg);
    if (verbose) xil_printf ("\r\nData read from register 0x%X is 0x%X", Volume_Reg, DATA);
    return DATA;
	
}

int AC97_Mute (Xuint32 AC97_Baseaddr, char Volume_Reg)
{
//Volume_Reg values are:
//AC97_INPUT_SELECT_OFFSET		0x1A
//AC97_MASTER_VOLUME_OFFSET 		0x02
//AC97_HEADPHONE_VOLUME_OFFSET 	0x04
//AC97_MIC_VOLUME_OFFSET 			0x0e
//AC97_LINE_IN_VOLUME_OFFSET 		0x10
//AC97_PCM_OUT_VOLUME_OFFSET 		0x18
//AC97_RECORD_GAIN_OFFSET 		0x1C
Xuint16 register_data;
Xuint16 DATA;

	DATA = AC97_ReadReg (AC97_Baseaddr, Volume_Reg);
	register_data = DATA | (1 << MUTE);
	DATA = AC97_WriteReg (AC97_Baseaddr, Volume_Reg, register_data);
    if (verbose) xil_printf ("\r\nData written to register 0x%X is 0x%X", Volume_Reg, DATA);
    DATA = AC97_ReadReg (AC97_Baseaddr, Volume_Reg);
    if (verbose) xil_printf ("\r\nData read from register 0x%X is 0x%X", Volume_Reg, DATA);

	return DATA;
}

int AC97_Unmute (Xuint32 AC97_Baseaddr, char Volume_Reg)
{
//Volume_Reg values are:
//AC97_INPUT_SELECT_OFFSET		0x1A
//AC97_MASTER_VOLUME_OFFSET 		0x02
//AC97_HEADPHONE_VOLUME_OFFSET 	0x04
//AC97_MIC_VOLUME_OFFSET 			0x0e
//AC97_LINE_IN_VOLUME_OFFSET 		0x10
//AC97_PCM_OUT_VOLUME_OFFSET 		0x18
//AC97_RECORD_GAIN_OFFSET 		0x1C
Xuint16 register_data;
int DATA; 

	DATA = AC97_ReadReg (AC97_Baseaddr, Volume_Reg);
	register_data = DATA & (~(1 <<MUTE));
	DATA = AC97_WriteReg (AC97_Baseaddr, Volume_Reg, register_data);
    if (verbose) xil_printf ("\r\nData written to register 0x%X is 0x%X", Volume_Reg, DATA);
    DATA = AC97_ReadReg (AC97_Baseaddr, Volume_Reg);
    if (verbose) xil_printf ("\r\nData read from register 0x%X is 0x%X", Volume_Reg, DATA);
	
	return DATA;
}

int AC97_IsMuted (Xuint32 AC97_Baseaddr, char Volume_Reg)
{
//returns 1 if the specified channel is muted, 0 if not
//Volume_Reg values are:
//AC97_INPUT_SELECT_OFFSET		0x1A
//AC97_MASTER_VOLUME_OFFSET 		0x02
//AC97_HEADPHONE_VOLUME_OFFSET 	0x04
//AC97_MIC_VOLUME_OFFSET 			0x0e
//AC97_LINE_IN_VOLUME_OFFSET 		0x10
//AC97_PCM_OUT_VOLUME_OFFSET 		0x18
//AC97_RECORD_GAIN_OFFSET 		0x1C
Xuint16 register_data;
int DATA; 

	DATA = AC97_ReadReg (AC97_Baseaddr, Volume_Reg);
	register_data = DATA & (1 << MUTE );
    if (verbose) xil_printf ("\r\nData read from register 0x%X is 0x%X", Volume_Reg, DATA);

	return (register_data >> MUTE);

}



int Ac97_Loopback_Swap_channels (Xuint32 AC97_Baseaddr)
{
Xuint32 STATUS;
Xuint32 PCM_DATA_L, PCM_DATA_R;
	
	//set tag and ID to 0x4C for sending and receiving valid PCM data 
	AC97_Set_Tag_And_Id (AC97_Baseaddr, 0x4C);
	
	 while (1)
	 {	
		 AC97_Wait_For_New_Frame (AC97_Baseaddr);
		    PCM_DATA_L = XIo_In32(AC97_Baseaddr + AC97_PCM_IN_L_OFFSET);
	   		PCM_DATA_R = XIo_In32(AC97_Baseaddr + AC97_PCM_IN_R_OFFSET);
	   		//swap the left and right channel
	   		XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_L_OFFSET), 0x00);
   			XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_R_OFFSET), 0x00);

	 }
return 0;
}

void GenSquare (Xuint32 AC97_Baseaddr, u8 channel, int freq_HZ, int milisec){

Xuint32 i, j;
Xuint32 PCM_DATA;
Xuint32 Status;
Xuint32 TAG_AND_ID_DATA;
Xuint32 count_skip_frame=0;

int line_in_muted, mic_muted;

i=0;

Xuint32 num_frames_send = 48 * milisec;

Xuint32 frames_freq = 24000 / freq_HZ;


	line_in_muted =  AC97_IsMuted (AC97_Baseaddr, AC97_LINE_IN_VOLUME_OFFSET);
	mic_muted = AC97_IsMuted (AC97_Baseaddr, AC97_MIC_VOLUME_OFFSET);

	//mute MIC and LINE-IN inputs if not muted and unmute PCM output first
    if (!(line_in_muted))
    		Status = AC97_Mute (AC97_Baseaddr, AC97_LINE_IN_VOLUME_OFFSET);
    
    if (!(mic_muted))
    	Status = AC97_Mute (AC97_Baseaddr, AC97_MIC_VOLUME_OFFSET);
    
    Status = AC97_Unmute (AC97_Baseaddr, AC97_MASTER_VOLUME_OFFSET);
   Status = AC97_Unmute (AC97_Baseaddr, AC97_HEADPHONE_VOLUME_OFFSET);
   Status = AC97_Unmute (AC97_Baseaddr, AC97_PCM_OUT_VOLUME_OFFSET);
    
//change TAG to send valid data in the PCM slots
   TAG_AND_ID_DATA = 0x4C;
   AC97_Set_Tag_And_Id (AC97_Baseaddr, TAG_AND_ID_DATA );

// set the first value for the PCM data;
PCM_DATA = 0x0001FFFF;


// wait for a frame
   AC97_Wait_For_New_Frame (AC97_Baseaddr);

j=0;
	//send the square-wave frames
	while (j<num_frames_send){
	   j++;
	   //wait for the next frame;
	  AC97_Wait_For_New_Frame (AC97_Baseaddr);
	
	  //send out PCM_DATA to the AC'97 codec
	  switch (channel)
	  {
	  case LEFT_CHANNEL:{
	  		XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_L_OFFSET), PCM_DATA);
	   		XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_R_OFFSET), 0x00000000);  
	  }
	  break;
	  case RIGHT_CHANNEL:
	  {
	  		XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_L_OFFSET), 0x00000000);
	   		XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_R_OFFSET), PCM_DATA);  
	  }
	  break;
	  case BOTH_CHANNELS:
	  {
	  		XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_L_OFFSET), PCM_DATA);
	   		XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_R_OFFSET), PCM_DATA);  
	  }
	  break;
	  }
	  	
	  //wait until the PCM data has to be changed
	  count_skip_frame++;
	  if (count_skip_frame >= frames_freq)
	  {
	   PCM_DATA = ~PCM_DATA;
	   count_skip_frame = 0;
	  }
	}

	//set 0 to both PCM channels in order to not let the amplifier close to saturation
	XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_L_OFFSET), 0x00);
    XIo_Out32 ((AC97_Baseaddr + AC97_PCM_OUT_R_OFFSET), 0x00);  

	//unmute MIC and LINE-IN inputs if were unmuted previously
    if (!(line_in_muted))
   		Status = AC97_Unmute (AC97_Baseaddr, AC97_LINE_IN_VOLUME_OFFSET);
    
    if (!(mic_muted))
    	Status = AC97_Unmute (AC97_Baseaddr, AC97_MIC_VOLUME_OFFSET);

}

Xuint32 Read_PCM_Samples (Xuint32 AC97_Baseaddr, Xuint32 * MEM_ADDRESS, char channel)
{
//returns the number of samples read
Xuint32 * ADDRESS;
Xuint32 TAG_AND_ID_DATA;
//change TAG to send valid data in the PCM slots
   TAG_AND_ID_DATA = 0x4C;
   AC97_Set_Tag_And_Id (AC97_Baseaddr, TAG_AND_ID_DATA );
   // wait for a frame
   AC97_Wait_For_New_Frame (AC97_Baseaddr);
  
  ADDRESS = MEM_ADDRESS;
 
	if (channel == LEFT_CHANNEL) 
	{
		* ADDRESS = (*(Xuint32 *) (AC97_Baseaddr + AC97_PCM_IN_L_OFFSET));
		return 1;
	}
	else if (channel == RIGHT_CHANNEL)
	{
		* ADDRESS = (*(Xuint32 *) (AC97_Baseaddr + AC97_PCM_IN_R_OFFSET));
		return 1;
	}
	else if (channel == BOTH_CHANNELS)
	{
		* ADDRESS = (*(Xuint32 *) (AC97_Baseaddr + AC97_PCM_IN_L_OFFSET));
		ADDRESS++;
		* ADDRESS = (*(Xuint32 *) (AC97_Baseaddr + AC97_PCM_IN_R_OFFSET));
		return 2;
	}
 }

Xuint32 Write_PCM_Samples (Xuint32 AC97_Baseaddr, Xuint32 * MEM_ADDRESS, char channel)
{
//returns the number of samples written
Xuint32 * ADDRESS;
Xuint32 TAG_AND_ID_DATA;
//change TAG to send valid data in the PCM slots
   TAG_AND_ID_DATA = 0x4C;
   AC97_Set_Tag_And_Id (AC97_Baseaddr, TAG_AND_ID_DATA );
   // wait for a frame
   AC97_Wait_For_New_Frame (AC97_Baseaddr);
  
  ADDRESS = MEM_ADDRESS;

	if (channel == LEFT_CHANNEL) 
	{
 		* (Xuint32 *) (AC97_Baseaddr + AC97_PCM_OUT_L_OFFSET) = * (ADDRESS);
		return 1;
	}
	else if (channel == RIGHT_CHANNEL)
	{
	   * (Xuint32 *) (AC97_Baseaddr + AC97_PCM_OUT_R_OFFSET) = * (ADDRESS);
		return 1;
	}
	else if (channel == BOTH_CHANNELS)
	{
		* (Xuint32 *) (AC97_Baseaddr + AC97_PCM_OUT_L_OFFSET) = * (ADDRESS);
		ADDRESS++;
	   * (Xuint32 *) (AC97_Baseaddr + AC97_PCM_OUT_R_OFFSET) = * (ADDRESS);
		return 2;
	}
 }


void Ac97_Codec_Initialize()
{
XStatus Status;

 while (!(AC97_Link_Is_Ready (XPAR_AC97_IF_00_0_BASEADDR)));
   
   AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x7C);
   Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_MASTER_VOLUME_OFFSET);
   Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_HEADPHONE_VOLUME_OFFSET);
   Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_PCM_OUT_VOLUME_OFFSET);
   
   Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_MASTER_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MAX);
   Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_HEADPHONE_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MAX);
   Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_PCM_OUT_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MAX);	
   AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x4C);	

}





int Audio_Test (char input, Xuint32 MEM_ADDRESS, Xuint32 SIZE)
{
XStatus Status;
Xuint32 Count_Samples;
Xuint32 Sample_L;
Xuint32 Sample_R;

   while (!(AC97_Link_Is_Ready (XPAR_AC97_IF_00_0_BASEADDR)));
   
   AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x7C);


   if (verbose) xil_printf ("\r\nUnmute and Setting Volume on Master Volume and Headphone");						   
   
 
   Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_MASTER_VOLUME_OFFSET);
   Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_HEADPHONE_VOLUME_OFFSET);
   Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_PCM_OUT_VOLUME_OFFSET);
   
   Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_MASTER_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MAX);
   Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_HEADPHONE_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MAX);
   Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_PCM_OUT_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MAX);	
	
	//generate square on left, right and then both channels
   AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x4C);
   GenSquare (XPAR_AC97_IF_00_0_BASEADDR, LEFT_CHANNEL, 1000, 1000);
   GenSquare (XPAR_AC97_IF_00_0_BASEADDR, RIGHT_CHANNEL, 1000, 1000);
   GenSquare (XPAR_AC97_IF_00_0_BASEADDR, BOTH_CHANNELS, 1000, 1000);

   AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x7C);
   
	if (input == AC97_LINE_IN_SELECT)
	{
	   Status = AC97_Select_Input (XPAR_AC97_IF_00_0_BASEADDR, BOTH_CHANNELS, 
   							   AC97_LINE_IN_SELECT);
	}
	else
	{
	   Status = AC97_Select_Input (XPAR_AC97_IF_00_0_BASEADDR, BOTH_CHANNELS, 
   							   AC97_MIC_SELECT);
	}      
 
   if (input == AC97_LINE_IN_SELECT)
   {
	  Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_LINE_IN_VOLUME_OFFSET);
	  Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_LINE_IN_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MAX);
   }
   else
   {
      Status = AC97_Unmute (XPAR_AC97_IF_00_0_BASEADDR, AC97_MIC_VOLUME_OFFSET);
      Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_MIC_VOLUME_OFFSET, 
   						     BOTH_CHANNELS, VOLUME_MID);
   }

	//set record gain
	Status = AC97_Set_Volume (XPAR_AC97_IF_00_0_BASEADDR, AC97_RECORD_GAIN_OFFSET, 
   						     BOTH_CHANNELS, 0x00);
 
   //set 3D and unselect loopback
    Status = AC97_WriteReg (XPAR_AC97_IF_00_0_BASEADDR, 0x20, 0x2000);
    if (verbose) xil_printf ("\r\nData written to register 0x20 is 0x%X", Status);
    Status = AC97_ReadReg (XPAR_AC97_IF_00_0_BASEADDR, 0x20);
    if (verbose) xil_printf ("\r\nData read from register 0x20 is 0x%X", Status);

   AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x4C);
 
   
   Count_Samples =  0;
   
   if (verbose) xil_printf("\r\nRecording...");
   while ((Count_Samples/8) < SIZE)
   {
   		 AC97_Wait_For_New_Frame (XPAR_AC97_IF_00_0_BASEADDR);
   		 AC97_Wait_For_New_Frame (XPAR_AC97_IF_00_0_BASEADDR);
   		 
		Sample_L = XIo_In32(XPAR_AC97_IF_00_0_BASEADDR + AC97_PCM_IN_L_OFFSET);
	   	Sample_R = XIo_In32(XPAR_AC97_IF_00_0_BASEADDR + AC97_PCM_IN_R_OFFSET);
	   	XIo_Out32 (MEM_ADDRESS + Count_Samples, Sample_L);
   		Count_Samples = Count_Samples +4;
	   	XIo_Out32 (MEM_ADDRESS + Count_Samples, Sample_R);
   		Count_Samples = Count_Samples +4;
   }
   if (verbose) xil_printf("\r\nRecorded 0x%X samples", (Count_Samples/8));
   
	//Set Tag and ID to configure the codec
	AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x7C);

   if (input == AC97_LINE_IN_SELECT)
   {   
      Status = AC97_Mute (XPAR_AC97_IF_00_0_BASEADDR, AC97_LINE_IN_VOLUME_OFFSET);
   }
   else
   {
      Status = AC97_Mute (XPAR_AC97_IF_00_0_BASEADDR, AC97_MIC_VOLUME_OFFSET);
   }

  
    AC97_Set_Tag_And_Id (XPAR_AC97_IF_00_0_BASEADDR, 0x4C);

	Count_Samples =  0;
   
   if (verbose) xil_printf("\r\nPlaying...");
   while ((Count_Samples/8) < SIZE)
   {
   		AC97_Wait_For_New_Frame (XPAR_AC97_IF_00_0_BASEADDR);
   		AC97_Wait_For_New_Frame (XPAR_AC97_IF_00_0_BASEADDR);
   		
   		Sample_L = XIo_In32 (MEM_ADDRESS + Count_Samples);
   		Count_Samples = Count_Samples +4;
   		Sample_R = XIo_In32 (MEM_ADDRESS + Count_Samples);
   		Count_Samples = Count_Samples +4;   		
		
		XIo_Out32 ((XPAR_AC97_IF_00_0_BASEADDR + AC97_PCM_OUT_L_OFFSET), Sample_L);
	   	XIo_Out32 ((XPAR_AC97_IF_00_0_BASEADDR + AC97_PCM_OUT_R_OFFSET), Sample_R);
   }

   if (verbose) xil_printf("\r\nPlayed 0x%X samples", (Count_Samples/8));

   return 0;
}


