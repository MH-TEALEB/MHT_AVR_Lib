/*
 * C File for LCD 4*20-lines.c
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
	LCD_Config_PORT_Direction |= (1 << RS) | (1 << RW) | (1 << E);  // Make Direction of RW, RS, E as output.

	// Initialize LCD with 8 Bit Mode.
	#ifdef _8_Bit_Mode
		Data_PORT_Direction = 0xFF; // Make Direction of Data PORT as output.
		MHT_LCD_Send_Command(0x38);	// 8-bit data bus, 2 Lines display, 5*8 dot format display.
		MHT_LCD_Send_Command(0x0C); // Display ON, Cursor OFF, Blinking OFF.
		MHT_LCD_Send_Command(0x01);	// Clear Display ( Clear DDRAM )
		//_delay_ms(2);	// Delay to let LCD Clear Display.
	#endif

	// Initialize LCD with 4 Bit Mode.
	#ifdef _4_Bit_Mode
		Data_PORT_Direction |= 0XF0;	// Make High 4 Pins as O/P.

		MHT_LCD_Send_Command(0x02);		// initializes LCD 16x2 in 4-bit mode.
		/*......................................................................Another Method instead of sending 0X02 command......................................../
		//MHT_LCD_Send_Command(0X33);
		//MHT_LCD_Send_Command(0X32);
		.............................................................................................................................................................*/
		MHT_LCD_Send_Command(0X28);		// 4-bit mode (D4-D7), 2 Lines display, 5*8 dot format display
		MHT_LCD_Send_Command(0x0C);		// Display ON, Cursor OFF.
		MHT_LCD_Send_Command(0x01);		// Clear Display ( Clear DDRAM )
	#endif
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
	#ifdef _8_Bit_Mode
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
	#endif

	#ifdef _4_Bit_Mode
		 Data_PORT_Direction &= 0X0F;	// Make Direction of 4 High Data Pins as input.
		 LCD_Config_PORT |= (1 << RW);	// Choose Read from The LCD.
		 LCD_Config_PORT &= ~(1 << RS);	// Command Register select.

		 LCD_Config_PORT |= (1 << E);	// Send High to Enable pin
		 while (Data_PIN  & (1 << 7))	// Wait until busy flag (D7) become low.
		 {
			 LCD_Config_PORT &= ~(1 << E);
			 LCD_Config_PORT |= (1 << E);
		 }
		 LCD_Config_PORT &= ~(1 << E);

		 Data_PORT_Direction |= 0xF0;	// Make Direction of 4 High Data Pins as output.
	#endif
}


// Send Command to LCD.
void MHT_LCD_Send_Command(unsigned char command)
{
	#ifdef _8_Bit_Mode
		 //MHT_LCD_IsntBusy();	// wait here until LCD become not busy.
		 Data_PORT_Direction = 0XFF; // Set Direction PORT of MC Data PORT as Output.
		 LCD_Config_PORT &= ~(1<<RW | 1<<RS); // choose Write to The LCD, Command Register select.
		 Data_PORT = command;    // Send Command to Data PORT

		 // LCD Enable
		 LCD_Config_PORT |= (1 << E);	// High pulse to Enable pin
		 _delay_us(1);	// Delay more than 500ns
		 LCD_Config_PORT &= ~(1 << E);	// Low pulse to Enable pin
		 //..........................................................................Another Method for Enable LCD...................................................//
		 //MHT_LCD_Enable();
		 //..........................................................................................................................................................//

		 // Making Delay to let LCD run the command.
		 _delay_us(100);
	#endif

	#ifdef _4_Bit_Mode
		 //MHT_LCD_IsntBusy();	// wait here until LCD become not busy.
		 Data_PORT_Direction |= 0XF0;	// Set Direction of Highest 4 pins of MC Data PORT as Output.
		 LCD_Config_PORT &= ~(1<<RW | 1<<RS); // choose Write to The LCD, Command Register select.

		 // Sending the Highest nibble of Command to Data PORT.
		 Data_PORT &= 0X0F;	// Put the highest nibble to logic 0.
		 Data_PORT |= (command & 0XF0);
		 // LCD Enable for the Highest nibble.
		 LCD_Config_PORT |= (1 << E);	// High pulse to Enable pin
		 _delay_us(1);	// Delay more than 500ns
		 LCD_Config_PORT &= ~(1 << E);	// Low pulse to Enable pin
		 //..........................................................................Another Method for Enable LCD...................................................//
		 //MHT_LCD_Enable();
		 //..........................................................................................................................................................//
		 _delay_us(100);	// Making Delay to let LCD latch the command.

		 // Sending the Lowest nibble of command to Data PORT.
		 Data_PORT &= 0X0F;	// Put The Highest nibble to logic 0
		 Data_PORT |= ( (command << 4) & 0XF0);
		 // LCD Enable for the lowest nibble.
		 LCD_Config_PORT |= (1 << E);	// High pulse to Enable pin
		 _delay_us(1);	// Delay more than 500ns
		 LCD_Config_PORT &= ~(1 << E);	// Low pulse to Enable pin
		 //..........................................................................Another Method for Enable LCD...................................................//
		 //MHT_LCD_Enable();
		 //..........................................................................................................................................................//
		 _delay_us(100);	// Making Delay to let LCD run the command.
	#endif
	if ( (command == 0X01) || (command == 0x02) )
		{
			_delay_ms(2);
		}
}

// Send Data to LCD.
void MHT_LCD_Send_Character(unsigned char Character)
{
	#ifdef _8_Bit_Mode
		//MHT_LCD_IsntBusy();	// Wait here until LCD become not busy.
		Data_PORT_Direction = 0XFF;	// Set Direction of MC Data PORT as Output.
		LCD_Config_PORT |= 1 << RS;	// Data Register select.
		LCD_Config_PORT &= ~(1<<RW); // Choose Write to The LCD.

		Data_PORT = Character;   // Send data to Data PORT

		// LCD Enable
		LCD_Config_PORT |= (1 << E);	// High pulse to Enable pin
		_delay_us(1);	// Delay more than 500ns
		LCD_Config_PORT &= ~(1 << E);	// Low pulse to Enable pin
		//..........................................................................Another Method for Enable LCD...................................................//
		//MHT_LCD_Enable();
		//..........................................................................................................................................................//
		_delay_us(100);		// Wait until LCD write data on LCD.
	#endif

	#ifdef _4_Bit_Mode
		 //MHT_LCD_IsntBusy();	// Wait here until LCD become not busy.
		 Data_PORT_Direction |= 0XF0;	// Set Direction of Highest 4 Pins of MC Data PORT as Output.
		 LCD_Config_PORT |= 1 << RS;	// Data Register select.
		 LCD_Config_PORT &= ~(1<<RW); // Choose Write to The LCD.

		 // Sending the Highest nibble of Character to Data PORT.
		 Data_PORT &= 0X0F;	// Put The Highest nibble to logic 0.
		 Data_PORT |= (Character & 0XF0);
		 // LCD Enable for the Highest nibble.
		 LCD_Config_PORT |= (1 << E);	// High pulse to Enable pin
		 _delay_us(1);	// Delay more than 500ns.
		 LCD_Config_PORT &= ~(1 << E);	// Low pulse to Enable pin
		 //..........................................................................Another Method for Enable LCD...................................................//
		 //MHT_LCD_Enable();
		 //..........................................................................................................................................................//
		_delay_us(100);		// Wait until LCD write data on LCD.

		 // Sending the Lowest nibble of Character to Data PORT.
		 Data_PORT &= 0X0F;	// Put The Highest nibble to logic 0.
		  Data_PORT |= ( (Character << 4) & 0XF0);
		 // LCD Enable for the lowest nibble.
		 LCD_Config_PORT |= (1 << E);	// High pulse to Enable pin
		 _delay_us(1);	// Delay more than 500ns
		 LCD_Config_PORT &= ~(1 << E);	// Low pulse to Enable pin
		 //..........................................................................Another Method for Enable LCD...................................................//
		 //MHT_LCD_Enable();
		 //..........................................................................................................................................................//
		 _delay_us(100);	// Wait until LCD write data on LCD.
	#endif

}

// Send String to LCD
void MHT_LCD_Send_String(char *str_to_char)
{
	while( (*str_to_char) != '\0')
		MHT_LCD_Send_Character(*str_to_char++);
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
void MHT_LCD_Goto_RowColumn(char row, char column)
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

	//MHT_LCD_IsntBusy();	// Wait until LCD isn't busy.

	Data_PORT_Direction = 0X00;	// Make direction of Data PORT as input to receive Data from LCD.
	LCD_Config_PORT |= (1 << RW) | (1 << RS);	// Choose Read from LCD, Data Register Select.
	LCD_Config_PORT |= 1 << E;  // Send Hight to Enable Pin
	Character = Data_PIN ;  // read the Data
	LCD_Config_PORT &= ~(1 << E);   // Send Low to Enable Pin
	Data_PORT_Direction = 0XFF;	// Make direction of Data PORT to be output.
	return Character;
}
