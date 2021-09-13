/*
 * @file MHT_I2C.c
 * @brief Implementation File for Two Wire Interface(I2C) driver.
 *
 * It includes MHT_I2C.h header file and defines Functions that can be used by I2C module.
 *
 * @date 03 February 2021
 * @author MH_TEALEB
 */

#include "MHT_I2C.h"	// Include MHT_I2C Header file

// Function Definition for I2C Initialize.
s8 MHT_I2C_Init(u32 f_cpu, u8 pres_value, u32 scl_freq){
	TWBR = ( (f_cpu - (16 * scl_freq)) / (2 * pres_value * scl_freq));		// Set the Bit rate
	
	TWCR |= 1<<TWEN;	// Enable I2C.

	// Select The Prescaler Value
    TWSR &= ~(1 << TWPS0) & ~(1 << TWPS1);  // TWPS0 = 0 , TWPS1 = 0. Zero The Prescaler bits.
	switch(pres_value){		// Choose the Prescaler
        case 1:		// If the prescaler value is 1.
            TWSR &= ~(1 << TWPS0) & ~(1 << TWPS1);  // TWPS0 = 0 , TWPS1 = 0
            break;
        case 4:		// If the prescaler value is 4.
            TWSR |= (1 << TWPS0) & ~(1 << TWPS1);   // TWPS0 = 1 , TWPS1 = 0
            break;
        case 16:	// If the prescaler value is 16.
            TWSR |= ~(1 << TWPS0) & (1 << TWPS1);   // TWPS0 = 0 , TWPS1 = 1
            break;
        case 64:	// If the prescaler value is 64.
            TWSR |= (1 << TWPS0) | (1 << TWPS1);    // TWPS0 = 1 , TWPS1 = 1
            break;
        default:	// If the prescaler value isn't accurately.
			return ERROR;	// Return error.
	}
	return NO_ERROR;	// Return no error.
}

// Function Definition for config address for this I2C device and recognize of general call.
void MHT_I2C_Address_Device_config(u8 address, u8 general_call){
	TWAR = (address << 1) | (general_call << TWGCE);
}

// Function Definition for starting I2C(Can only be used by Master).
// Note that: start bit(TWSTA) must be cleared by software when the START condition has been transmitted.
void MHT_I2C_Start(void){
	TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);	// Enable I2C if not enabled before, set start bit, and clear interrupt flag.
	while (!(TWCR & (1 << TWINT))); // wait until I2C interrupt flag is set.
	TWCR &= ~(1 << TWSTA);	    // Clear start bit after it was sending.
}

// Function Definition to Transmit address or data on I2C Data Bus(Can only be used by Transmitter).
void MHT_I2C_Transmit(u8 ch){
	TWDR = ch;	// Put the address or data on the I2C Data Register.
	TWCR |= (1 << TWINT) | (1 << TWEN);	// Enable I2C and Clear I2C Interrupt flag to initiate the transmit.
	while (!(TWCR & (1 << TWINT))); //wait until I2C Interrupt flag is set.
}

// Function Definition to receive the slave address(Can only be used by Slave).
void MHT_I2C_Receive_Slave_Address(void){
	TWCR |=(1 << TWINT) | (1 << TWEA) | (1 << TWEN);	// Enable I2C and Acknowledge and Clear I2C Interrupt flag to start receiving.
	while (!(TWCR & (1 << TWINT))); // wait until I2C Interrupt Flag is set.
	TWCR &= ~(1 << TWEA);	// Clear Acknowledge bit.
}

// Function Definition to receive data from I2C Data Bus and respond with Acknowledge(Can only be used by Receiver).
u8 MHT_I2C_Receive_Data_with_ACK(void){
	TWCR |=(1 << TWINT) | (1 << TWEN) | (1 << TWEA);	// Enable I2C and Acknowledge and Clear I2C Interrupt flag to start receiving.
	while (!(TWCR & (1 << TWINT))); // wait until I2C Interrupt flag is set.
	TWCR &= ~(1 << TWEA); // Clear Acknowledge bit after being sending. 
	return TWDR;	// Return the I2C Data Register value.
}

// Function Definition to receive data from I2C Data Bus and respond with Not Acknowledge(Can only be used by Receiver).
u8 MHT_I2C_Receive_Data_with_NACK(void){
	TWCR &= ~(1 << TWEA); // Clear Acknowledge bit if it was enabled before.
	TWCR |=(1 << TWINT) | (1 << TWEN);	// Enable I2C and Clear I2C Interrupt flag to start receiving.
	while (!(TWCR & (1 << TWINT))); // wait until I2C Interrupt flag is set.
	return TWDR;	// Return the I2C Data Register value.
}

// Function Definition that the Master stops arbitration.(Can only be used by Master).
void MHT_I2C_Stop(void){
	TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	TWCR &= ~( (1 << TWSTO) | (1 << TWSTA) | (1 << TWEN) | (1 << TWEA) ) ; // clear stop(cleared automatically), start, 
																		   // enable,and acknowledge bits after stopping.
    // Don't wait TWINT to be set after Stop
}