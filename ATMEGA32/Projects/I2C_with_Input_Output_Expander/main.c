/*
 * I2C with PCF8574 I/O Expander.c
 *
 * Created: 03 February 2021
 *  Author: MH_TEALEB
 */

// Using I2C with PCF8574 which it is I2C expander pins

#define F_CPU 8000000UL

#include <avr/io.h>
#include "MHT_I2C.h"
#include <util/delay.h>


int main(void)
{
	MHT_I2C_Init(F_CPU,1,100000);	// Initialize I2c with presclaer_value = 1 , SCl_freq = 100KHz.
	MHT_I2C_Start();
	MHT_I2C_Transmit(0x40); // Write address of the PCF8574 to enable it ( SLA + W(0) )
    while(1)
    {
		MHT_I2C_Transmit(0x21);	// Send data 0X21.
		_delay_ms(1000);	// Wait 1 sec.
		MHT_I2C_Transmit(0xDE);	// Send data 0xDE.
		_delay_ms(1000);	// Wait 1 sec.
    }
}
