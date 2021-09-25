/*
 * @file LED_Blinking.c
 * @brief Starting making LED ON then wait for 2 seconds then make the same LED OFF,
 *        Then every 1 second make another LED Blinking.
 *
 * @date    08 Dec. 2016 07:28:56 م
 * @author  MH_TEALEB
 *
 */

#ifndef	F_CPU
	#define	F_CPU	1000000UL	// Define CPU frequency with 1MHz.
#endif

#include <avr/io.h> // This is the header file for Atmel family.
#include <util/delay.h> // This is the header file for making delay.
#include "MHT_GPIO.h"

int main(void)
{
	MHT_GPIO_PINSB_DIRECTION_DEFINE(0b10000001);	// Make Direction of Pins 0 & 7 in Port B as Output.

	MHT_GPIO_PIN_OUTPUT_ONE(PB, 7);			// Make LED ON on Pin 7 in Port B.
	_delay_ms(2000);						// Wait for 2 seconds.
	MHT_GPIO_PIN_OUTPUT_ZERO(PB, 7);		// Make LED OFF on Pin 7 in Port B.


	while (1) // To make the loop running without stop(infinite).
	{
		MHT_GPIO_PIN_OUTPUT_TOGGLE(PB, 0);	// Make LED Toggle on pin 0 in port B.
		 _delay_ms(1000);					// Wait for 1 seconds.
	}
	return 0;
}
