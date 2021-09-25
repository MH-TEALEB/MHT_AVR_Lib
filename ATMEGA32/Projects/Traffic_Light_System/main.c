/*
 * @file Traffic_Light_System_1stMethod.c
 *
 * @brief A Traffic light system project where The three lights(Red, Green and Yellow) are connected to 3 different pins in the same port,
 *		  and the time for each light is displayed in 2 7segments that are connected to 2 ports.
 *
 * @date	18 Sep. 2021 09:17:19 م
 * @author	MH_TEALEB
 */ 

#ifndef	F_CPU
	#define	F_CPU	1000000UL	// Define CPU frequency with 1MHz.
#endif


#include <avr/io.h>
#include <util/delay.h>
#include "MHT_GPIO.h"
#include "MHT_ATMEGA32_StdTypes.h"

#define RED_LED		0
#define GREEN_LED	1
#define YELLOW_LED	2

int main(void)
{
	// Define the used Local Variables.
	u8 _7SegNumbers[] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};	// Numbers of 7-segment from 0 to 9.
	u8 led_on = RED_LED;	// Define "led_on" variable to choose which led to getting ON, and make RED led getting on at the first.
	u8 time_on;				// Define "time_on" variable to hold the time in seconds for each led it will be ON.
	
	// Initialize the used ports for the two 7segments and leds to be output.
	MHT_GPIO_PINSD_DIRECTION_DEFINE(0X7F);		// Make pins from 0 to 6 in port D as output for the 1st 7segment.
	MHT_GPIO_PINSC_DIRECTION_DEFINE(0X7F);		// Make pins from 0 to 6 in port C as output for the 2nd 7segment.
	MHT_GPIO_PINSA_DIRECTION_DEFINE(0X07);		// Make pins 0, 1, 2 in port A as output for the Green, Yellow and Red Lights.
	
    while (1) 
    {
		if (led_on == RED_LED){	// If its turn for Red led to be ON.
			MHT_GPIO_PIN_OUTPUT_ONE(PA, RED_LED);
			time_on = 40;			// Make Red Led ON for 40 seconds.
		}else if (led_on == GREEN_LED){	// If its turn for Green Led to be ON.
			MHT_GPIO_PIN_OUTPUT_ONE(PA, GREEN_LED);
			time_on = 60;					// Make Green Led ON for 60 seconds.
		}else if (led_on == YELLOW_LED){
			MHT_GPIO_PORTD_OUTPUT_VALUE(0X00);
			MHT_GPIO_PORTC_OUTPUT_VALUE(0X00);
			time_on = 0;
			for (u8 i = 0; i < 10; ++i){
				MHT_GPIO_PIN_OUTPUT_TOGGLE(PA, YELLOW_LED);
				_delay_ms(500);
			}
		}else{
			MHT_GPIO_PORTD_OUTPUT_VALUE(0X3F);
			MHT_GPIO_PORTC_OUTPUT_VALUE(0X3F);
		}
		
		// Loop to count the seconds that the led will be ON.
		while (time_on > 0){
			MHT_GPIO_PORTD_OUTPUT_VALUE(_7SegNumbers[(time_on % 10)]);
			MHT_GPIO_PORTC_OUTPUT_VALUE(_7SegNumbers[(time_on / 10)]);
			_delay_ms(1000);
			--time_on;
		}
		MHT_GPIO_PIN_OUTPUT_ZERO(PA, led_on);
		++led_on;
		if(led_on > 2){
			led_on = RED_LED;
		}
		
	}	// End of while(1).
	
	return	0;	// Return 0 from main function.
	
}	// End of main Function.

