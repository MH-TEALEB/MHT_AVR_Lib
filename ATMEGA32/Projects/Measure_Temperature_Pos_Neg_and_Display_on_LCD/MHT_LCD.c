/*
 * C File for LCD 4*20-lines with 8-bit mode.c
 *
 * Created: 25-NOV-18 5:25:59 PM
 * Author : MH_TEALEB
 */

 // Include MHT_LCD Header file
#include "MHT_LCD.h"

// Initialize LCD with 8-bit data bus
void MHT_LCD_Init()
{
	_delay_ms(15);
	Data_PORT_Direction = 0xFF; // Make Direction of Data PORT as output.
	LCD_Config_PORT_Direction |= (1 << RS) | (1 << RW) | (1 << E);  // Make Direction of RW, RS, E as output.
	MHT_LCD_Send_Command(0x38);	// 8-bit data bus, 2 Lines display, 5*8 dot format display.
	MHT_LCD_Send_Command(0x0C); // Display ON, Cursor OFF, Blinking OFF.
	MHT_LCD_Send_Command(0x01);	// Clear Display ( Clear DDRAM )
}

// Enable LCD by sending High to Low pulse.
void MHT_LCD_Enable()
{
	LCD_Config_PORT |= (1 << E);	// High pulse to Enable pin
	_delay_us(1);	// Delay more than 500ns
	LCD_Config_PORT &= ~(1 << E);	// Low pulse to Enable pin
}

// Check if LCD isn't busy, By checking BF"Busy Flag" D7.
void MHT_LCD_IsntBusy(void)
{
	Data_PORT_Direction = 0X00;	// Make direction Data PORT as input.
	LCD_Config_PORT |= (1 << RW);		// Choose Read from The LCD.
	LCD_Config_PORT &= ~(1 << RS);	// Command Register select.
	LCD_Config_PORT |= (1 << E);	// Send High to Enable pin
	while (Data_PIN  & (1 << 7))	// Wait until busy flag (D7) become low.
	{
		LCD_Config_PORT &= ~(1 << E);
		LCD_Config_PORT |= (1 << E);
	}
	LCD_Config_PORT &= ~(1 << E);
	Data_PORT_Direction = 0xFF;	// Make direction Data PORT as output.
}

// Send Command to LCD.
void MHT_LCD_Send_Command(unsigned char command)
{
	MHT_LCD_IsntBusy();
	LCD_Config_PORT &= ~(1<<RW | 1<<RS); // choose Write to The LCD, Command Register select.
	Data_PORT = command;    // Send Command to Data PORT
	MHT_LCD_Enable();

	//if ((command ==0x01) | (command == 0x02))
	//_delay_ms(2);
	//else
	//_delay_us(100);
}

// Send Data to LCD.
void MHT_LCD_Send_Character(unsigned char Character)
{
	MHT_LCD_IsntBusy();
	LCD_Config_PORT |= 1 << RS;	// Data Register select.
	LCD_Config_PORT &= ~(1<<RW); // Choose Write to The LCD.
	Data_PORT = Character;   // Send data to Data PORT
	MHT_LCD_Enable();
	//_delay_us(100);
}

// Send String to LCD
void MHT_LCD_Send_String(char *str_to_char)
{
	while(*str_to_char != 0)
		MHT_LCD_Send_Character(*(str_to_char++));
}

// Send Integer Decimal Number to LCD
void MHT_LCD_Send_IntegerNumber(long int number, int width)
{
	char *number_as_string = (char*)malloc((width + 1) * sizeof(char));  // Allocate dynamic memory for the number_as_string
	itoa(number,number_as_string,10);   // convert from integer number to string
	MHT_LCD_Send_String(number_as_string);  // Send the string number to LCD
	free(number_as_string); // Free the the allocated dynamic memory of number_as_string
}

// Send Real(float and doubles) numbers to LCD
void MHT_LCD_Send_RealNumber(float number,int width, int precision)
{
	float Fractional_Number = 0;
	int Int_Number1 = 0; 
	volatile unsigned int Int_Number2 = 0, Multiplier_Number = 1;
	Int_Number1 = number;  
	Fractional_Number = number - Int_Number1; 
	for (int i = 0; i < precision; ++i)
		Multiplier_Number *=10;
	Int_Number2 = Fractional_Number * Multiplier_Number;
	MHT_LCD_Send_IntegerNumber(Int_Number1, width - precision);
	MHT_LCD_Send_Character('.');
	MHT_LCD_Send_IntegerNumber(Int_Number2, precision);
}

// Go to specified Location
void MHT_LCD_Goto_Location(char row, char column)
{
	if (column > 20 || column < 1 || row > 4 || row < 1 )
		goto Error;
	switch(row)
	{
		case 1:
			MHT_LCD_Send_Command(0x80 + column - 1);
			break;
		case 2:
			MHT_LCD_Send_Command(0xC0 + column - 1);
			break;
		case 3:
			MHT_LCD_Send_Command(0x94 + column - 1);
			break;
		case 4:
			MHT_LCD_Send_Command(0xD4 + column - 1);
			break;
	Error:		
		default:
			MHT_LCD_Send_Command(0x01);
			MHT_LCD_Send_Command(0x80); // go to 1st line.
			MHT_LCD_Send_String("Error!plz Enter your");
			MHT_LCD_Send_Command(0xC0); // go to 2nd line
			MHT_LCD_Send_String("row from 1 to 4");
			MHT_LCD_Send_Command(0x94); // got to 3rd line
			MHT_LCD_Send_String("column from 1 to 20");
	}
} 

// Read Character from LCD
unsigned char MHT_LCD_Read_Character(void)
{
	unsigned char Character;
	MHT_LCD_IsntBusy();	// Wait until LCD isn't busy.
	Data_PORT_Direction = 0X00;	// Make direction of Data PORT as input to receive Data from LCD.
	LCD_Config_PORT |= (1 << RW) | (1 << RS);	// Choose Read from LCD, Data Register Select.
	LCD_Config_PORT |= 1 << E;  // Send Hight to Enable Pin
	Character = Data_PIN ;  // read the Data
	LCD_Config_PORT &= ~(1 << E);   // Send Low to Enable Pin
	Data_PORT_Direction = 0XFF;	// Make direction of Data PORT to be output.
	return Character;
}



