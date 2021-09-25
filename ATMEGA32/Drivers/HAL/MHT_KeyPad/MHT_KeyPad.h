/*
 * MHT_KeyPad.h
 *
 * Important Notes before use:
 *			- you must connect all rows first to the 1st pins in the port then after it connect directly columns in the same port.
 *			- Here, We use Rows as Output to keypad and Columns as input from KeyPad.
 *          - This Driver can be used for KeyPad 4X4 and KeyPad 4X3. But you should Define just one Keypad Per time. and if you forget it will give you error.
 *
 * Created: 21-Dec-19 12:44:46 AM
 *  Author: MH_TEALEB
 */ 

#include "MHT_LCD.h"

#ifndef MHT_KEYPAD_H_
#define MHT_KEYPAD_H_

	#ifndef F_CPU
		#define F_CPU 1000000UL	// Define Internal Cock frequency as 1MHz.
	#endif
	
	#include <avr/io.h>
	
	/****** HW Pins Connection***********************/
	#define DIR_KeyPad_PORT     DDRC
	#define KeyPad_PORT         PORTC
	#define OutPut_to_KeyPad	PORTC
	#define A					PC0
	#define B                   PC1
	#define C                   PC2
	#define D                   PC3
	
	#define InPut_from_KeyPad	PINC
	#define I1					PC4
	#define I2					PC5
	#define I3					PC6
	#define I4					PC7		// This pin is used in KeyPad 4X4.
	
	/*
		// ******* if you want to use KeyPad_4x4*****
		#define KEYPAD_4X4
		#define N_ROWS 4
		#define N_COLS 4
	*/
	
	// ******* if you want to use KeyPad_4x3*****
	#define KEYPAD_4X3
	#define N_ROWS 4
	#define N_COLS 3
	
	// TO check if you defined more than one type of Keypad it will give error.
	#ifdef KEYPAD_4X4
		#ifdef KEYPAD_4X3
			#error "you defined more than one variable"
		#endif // KEYPAD_4X3
	#endif // KEYPAD_4X4	
	
	
	/********* Functions Prototype **************/
	void MHT_KeyPad_Init(void);
	unsigned char MHT_Get_Pressed_key(void);
	unsigned char MHT_Which_key_Pressed(unsigned char key);

#endif /* MHT_KEYPAD_H_ */