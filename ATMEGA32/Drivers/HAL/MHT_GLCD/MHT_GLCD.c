/*
 * MHT_GLCD.c
 *
 * This file is for GLCD 128*64 Pixels KS0108 module.
 *
 * Created: 29-Nov-19 6:16:11 PM
 *  Author: MH_TEALEB
 */

 
#include "MHT_GLCD.h"


// Function Definition for Initializing GLCD
void MHT_GLCD_Init(void)
{
	GLCD_Data_PORT_Direction = 0XFF;	// Direction of GLCD Data PORT is Output from MC.
	GLCD_Config_PORT_Direction |= (1 << RST) | (1 << CS1) | (1 << CS2) | (1 << RS) | (1 << RW) | (1 << E);	// Direction of RST, CS1, CS2, RS, RW and E is Output from MC.
	BOTH_SIDES_ON();	// Enable Both Left and Right side of GLCD Display.
	GLCD_Config_PORT |= (1 << RST);	 // Keep RST Pin HIGH to don't make Reset because it is active low.
	_delay_ms(20);	// Waiting for GLCD to get Power-ON and be ready to receive data.
	MHT_GLCD_Send_Command(0x3F);	// Display ON.
	MHT_GLCD_Send_Command(0x40);	// Set Y address (column=0).
	MHT_GLCD_Send_Command(0xB8);	// Set x address (page=0).
	MHT_GLCD_Send_Command(0xC0);	// Set z address (start line=0).
}


// Function Definition for Sending command to GLCD.
void MHT_GLCD_Send_Command(char command)
{
	GLCD_Data_PORT = command;	// Send Command to GLCD Data PORT.
	GLCD_Config_PORT &= ~( (1 << RS) | (1 << RW) );	// Select Command Register and Choose Write Data to GLCD.
	MHT_GLCD_ENABLE();
}


// Function Definition for Sending Character to GLCD.
void MHT_GLCD_Send_Data(char data)
{
	GLCD_Data_PORT = data;	// Send Command to GLCD Data PORT.
	GLCD_Config_PORT |=  (1 << RS);	// Select Data Register.  
	GLCD_Config_PORT &= ~(1 << RW);	// Choose Write Data to GLCD.
	MHT_GLCD_ENABLE();	// Inline Function for Enabling GLCD.
}

// Function Definition for Sending Character to GLCD.
void MHT_GLCD_Send_Character(unsigned char character)
{	
	int i, start_font, end_font;
	 
	start_font = (character - 32) * 5;	// Here, we subtract from 32 as space that in "MHT_LCD_Font5x7.h" file starts from element number 0 in the Font5x7 array
	                                    // and in ASCII table it is equal to 32 in decimal.
										// Also, we multiply by 5 as every character starts by element number multiplied by 5 as in "MHT_LCD_Font5x7.h" file.
										
	end_font = start_font + 5;	// Here, we do that as every character are represented in 5 bytes.
	
	for (i = start_font; i < end_font; ++i)
	{
		MHT_GLCD_Send_Data(font5x7[i]);
	}
	
}


// Function Definition for Sending String to GLCD.
void MHT_GLCD_Send_String(char *string)
{	
	while (*string != '\0')	// check if string is not finished (Not reached Null character).
	{
		MHT_GLCD_Send_Character(*string);
		++string;
	}
	
}


// Function Definition for Enabling GLCD.
void MHT_GLCD_Enable(void)
{
	GLCD_Config_PORT |= (1 << E);	// Send High Pulse to E.
	_delay_ms(1);	// Wait more than 500ns.
	GLCD_Config_PORT &= ~(1 << E);	// Send Low Pulse to E.
}


// Function Definition for Clear all GLCD Display.
void MHT_GLCD_ClearAll(void)			
{
	unsigned char i,j;	// Declare 2 variables to use them as counters.
	BOTH_SIDES_ON(); // Select Both Left & Right sides of GLCD Display.
	for(i = 0; i < Total_Pages; ++i)
	{
		MHT_GLCD_Send_Command(0XB8 + i);/* Increment page */
		for(j = 0; j < 64; ++j)
		{
			MHT_GLCD_Send_Data(0);	/* Write zeros to all 64 column */
		}
	}
	MHT_GLCD_Send_Command(0x40);		//Set Y address (column=0)
	MHT_GLCD_Send_Command(0xB8);		// Set x address (page=0)
}


// Function Definition for Go to Specified location.
void MHT_GLCD_GOTO_Page_column(unsigned char x, unsigned char y)
{
	MHT_GLCD_Send_Command(0XB8 + x);	// go to page x ..... x is from 0 to 7.
	MHT_GLCD_Send_Command(0X40 + y);	// go to Column y ..... y is from 0 to 63.
}
