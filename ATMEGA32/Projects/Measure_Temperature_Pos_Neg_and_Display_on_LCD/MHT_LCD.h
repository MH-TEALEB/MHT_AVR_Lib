/*
 * Header File for LCD 4*20-lines with 8-bit mode.h
 *Note that:
			The control bits should be in the same PORT.
			you can choose the PORT you want for sending data and control bits by changing the #define below here.
			I use here PORTD for 8-bit Data and Pins 5, 6 and 7 of PORTC for Rs, RW and E respectively.
 *
 * Created: 25-NOV-18 5:25:59 PM
 * Author : MH_TEALEB
 */

#ifndef MHT_LCD_H_
#define MHT_LCD_H_

#ifndef F_CPU
	#define  F_CPU 1000000UL	// System Clock Frequency = 1MHz.
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define Data_PORT_Direction         DDRD
#define Data_PORT                   PORTD
#define Data_PIN                    PIND

#define LCD_Config_PORT_Direction   DDRC
#define LCD_Config_PORT             PORTC
#define RS  5
#define RW  6
#define E   7

void MHT_LCD_Init(void);
void MHT_LCD_Enable(void);
void MHT_LCD_IsntBusy(void);
void MHT_LCD_Send_Command(unsigned char command);
void MHT_LCD_Send_Character(unsigned char data);
void MHT_LCD_Send_String(char *str_to_char);
void MHT_LCD_Send_IntegerNumber(long int number, int width);
void MHT_LCD_Send_RealNumber(float number,int width, int precision);
void MHT_LCD_Goto_Location(char row, char column);   // Go to  specified Location
unsigned char MHT_LCD_Read_Character(void);


#endif // MHT_LCD_H_
