/*
 * MHT_KeyPad_4X4.c
 *
 * Created: 21-Dec-19 12:45:06 AM
 *  Author: MH_TEALEB
 */ 

#include "MHT_KeyPad.h"


// Initialize KeyPad 4X4
void MHT_KeyPad_Init(void)
{
	// IF using KeyPad 4X4.
	#ifdef KEYPAD_4X4
		DIR_KeyPad_PORT = 0X0F;	// Make PINs 0 to 3 as Output to KeyPad " To use them for Rows" & PINs 4 to 7 as Input from KeyPad " To use them for columns".
		OutPut_to_KeyPad |= (1 << A) | (1 << B) | (1 << C) | (1 << D);	// Make the O/P of MC to KeyPad as HIGH "Logic 1".  
		KeyPad_PORT |= (1 << I1) | (1 << I2) | (1 << I3) | (1 << I4);	// Use Internal Pull-Up of the I/P to MC.
	#endif
	
	// If using KeyPad 4X3.
	#ifdef KEYPAD_4X3
		DIR_KeyPad_PORT |= 0X0F;	// Make PINs 0 to 3 as Output to KeyPad " To use them for Rows".  
		DIR_KeyPad_PORT &= 0X8F;	// Make PINs 4 to 6 as Input from KeyPad " To use them for Columns".
		OutPut_to_KeyPad |= (1 << A) | (1 << B) | (1 << C) | (1 << D);	// Make the Output to KeyPad as HIGH "Logic 1".
		KeyPad_PORT |= (1 << I1) | (1 << I2) | (1 << I3);	// Use Internal Pull-Up of the Input from KeyPad.
	#endif
}


// Function Definition to get the Pressed Key
unsigned char MHT_Get_Pressed_key(void)
{
	// it can be used for Keypad 4X4 and KeyPad 4X3.
	while(1)	// to repeat again if no key is pressed
	{
		// Each time,i will send logic 0 to one row and send logic 1 to all others rows.
		for (int row = 0; row < N_ROWS; ++row)
		{
			OutPut_to_KeyPad |= 0X0F;	// send logic 1 to all rows.
			OutPut_to_KeyPad &= ~(1 << row);	// Send logic 0 to the defined row and others rows are in logic 1.
		
			// check which column is become low"Logic 0".
			for (int col = N_ROWS; col < N_ROWS + N_COLS; ++col)
			{
				if ( !(InPut_from_KeyPad & (1 << col) ) )	// check if key is pressed.
				{
					while( !(InPut_from_KeyPad & (1 << col) ) ); // wait here until Pressed Key is released
					return MHT_Which_key_Pressed(col + (row * N_ROWS) );	// return the number of row and column
				}
			}
		}
	}
}


// Get which Key is pressed
unsigned char MHT_Which_key_Pressed(unsigned char key)
{
	// IF using KeyPad 4X4.
	#ifdef KEYPAD_4X4
		switch(key)
		{
			case 4 :
				return '7';
				break;
			case 5 :
				return '8';
				break;
			case 6 :
				return '9';
				break;
			case 7 :
				return '/';
				break;
			case 8 :
				return '4';
				break;
			case 9 :
				return '5';
				break;
			case 10 :
				return '6';
				break;
			case 11 :
				return 'X';
				break;
			case 12 :
				return '1';
				break;
			case 13 :
				return '2';
				break;
			case 14 :
				return '3';
				break;
			case 15 :
				return '-';
				break;
			case 16 :
				return 'C';
				break;
			case 17 :
				return '0';
				break;
			case 18 :
				return '=';
				break;
			case 19 :
				return '+';
				break;
			default:
				return '?';	
		}
	#endif
	
	// IF using KeyPad 4X3.
	#ifdef KEYPAD_4X3
	switch(key)
	{
		case 4 :
			return '1';
			break;
		case 5 :
			return '2';
			break;
		case 6 :
			return '3';
			break;
		case 8 :
			return '4';
			break;
		case 9 :
			return '5';
			break;
		case 10 :
			return '6';
			break;
		case 12 :
			return '7';
			break;
		case 13 :
			return '8';
			break;
		case 14 :
			return '9';
			break;
		case 16 :
			return '*';
			break;
		case 17 :
			return '0';
			break;
		case 18 :
			return '#';
			break;
		default:
			return '?';
	}
	#endif
}