/*
 * MHT_GLCD.h
 *
 * This file is for GLCD 128*64 Pixels KS0108 module.
 *
 *
 * Created: 29-Nov-19 6:15:54 PM
 *  Author: MH_TEALEB
 */ 


#ifndef MHT_GLCD_H_
#define MHT_GLCD_H_

	#ifndef F_CPU
		#define  F_CPU 1000000UL
	#endif
	
	#include <avr/io.h>
	#include <util/delay.h>
	
	#include "MHT_GLCD_Font5x7.h"
	
	#define Total_Pages	 8
	
	
	/*..........GLCD HW PINs.............................*/
	#define GLCD_Data_PORT_Direction		DDRC
	#define GLCD_Data_PORT                  PORTC
	#define GLCD_Data_PIN                   PINC
	#define GLCD_Config_PORT_Direction		DDRD
	#define GLCD_Config_PORT				PORTD
	#define	RST 0
	#define CS1 1
	#define CS2	2
	#define RS  3
	#define RW  4
	#define E   5
	
	
	/*..... Prototype Functions for GLCD......*/
	void MHT_GLCD_Init(void);
	void MHT_GLCD_Send_Command(char command);
	void MHT_GLCD_Send_Data(char data);
	void MHT_GLCD_Send_Character(unsigned char character);
	void MHT_GLCD_Send_String(char *string);
	void MHT_GLCD_Enable(void);
	void MHT_GLCD_ClearAll(void);
	void MHT_GLCD_GOTO_Page_column(unsigned char x, unsigned char y);
	
	
	// Inline Function for Enabling GLCD.
	static inline void MHT_GLCD_ENABLE(void)	   {
														GLCD_Config_PORT |= (1 << E); 	// Send High Pulse to E.
														_delay_us(1);  // Wait more than 1us.
														GLCD_Config_PORT &= ~(1 << E);	// Send Low Pulse to E.
													}
	 
	 
	// Inline Functions to control Left and Right sides display of GLCD.
	 static inline void LEFT_SIDE_ON(void)	    {
													GLCD_Config_PORT |= (1 << CS1);
													GLCD_Config_PORT &= ~(1 << CS2);
												}

	 static inline void RIGHT_SIDE_ON(void)     {
													GLCD_Config_PORT &= ~(1 << CS1);
													GLCD_Config_PORT |= (1 << CS2);
											    }
									
	 static inline void BOTH_SIDES_ON(void)		{
													GLCD_Config_PORT |= ( (1 << CS1) | (1 <<CS2) );
												}
	 
	 static inline void BOTH_SIDES_OFF(void)	{
													GLCD_Config_PORT &= ~( (1 << CS1) | (1 <<CS2) );
												}												


#endif /* MHT_GLCD_H_ */