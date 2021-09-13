/*
 * MHT_SPI.c
 *
 * This is a driver(.c) File for SPI Module in AVR ATMEGA32 Micro-Controller.
 *
 * Created: 27/07/2020 9:41:48 PM
 *  Author: MH_TEALEB
 */

#include "MHT_SPI.h"

// Function Definition to Initialize SPI.
void MHT_SPI_Init(uint8 mode, uint8 dord, uint8 cpol, uint8 cpha, uint8 spr, uint8 spe)
{
	// Select the Desired Operation_Mode.
	switch(mode){
		case SLAVE_MODE:
				DDRB &= ~( (1 << MOSI) | (1 << SCK) | (1 << SS) );	// Define MOSI, SCK, and SS as Input Pins.
				DDRB |= (1 << MISO);	// Define MISO as Output Pin.
				SPCR &= ~(1 << MSTR);	// Select Slave Mode.
				break;

		case MASTER_MODE:
				DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);	// Define MOSI, SCK, and SS as Output Pins.
				DDRB &= ~(1 << MISO);	// Define MISO as Input Pin.
				SPCR |= (1 << MSTR);	// Select Master Mode.
				break;
	}

	// Select if SPI Clock Rate is Double speed or not.
	if (spr > 3){
		SPSR |= (1 << SPI2X);	// Set Double Speed SPI.
		spr &= 0X03;	// Filter The SPI Clock Rate Bits( SPR0 and SPR1 ).
	}

	// Select Data Order, Clock Polarity, Clock Phase, Clock Rate.
	SPCR |= (dord << DORD) | (cpol << CPOL) | (cpha << CPHA) | (spr << SPR0);

	// Enable or Disable SPI.
	SPCR |= (spe << SPE);
}

// Function Definition to Initialize SPI Master.
void MHT_SPI_Init_Master(uint8 dord, uint8 cpol, uint8 cpha, uint8 spr, uint8 spe)
{
	// Define the Needed input and output pins for Master Mode.
	DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);	// Define MOSI, SCK, and SS as Output Pins.
	DDRB &= ~(1 << MISO);	// Define MISO as Input Pin.

	// Select if SPI Clock Rate is Double speed or not.
	if (spr > 3){
		SPSR |= (1 << SPI2X);	// Set Double Speed SPI.
		spr &= 0X03;	// Filter The SPI Clock Rate Bits( SPR0 and SPR1 ).
	}

	// Select Master Mode, Data Order, Clock Polarity, Clock Phase, Clock Rate.
	SPCR |= (1 << MSTR) | (dord << DORD) | (cpol << CPOL) | (cpha << CPHA) | (spr << SPR0);

	// Enable or Disable SPI.
	SPCR |= (spe << SPE);
}

// Function Definition to Initialize SPI Slave.
void MHT_SPI_Init_Slave(uint8 dord, uint8 cpol, uint8 cpha, uint8 spr, uint8 spe)
{
	// Select The Needed Input and Output Pins for Slave Mode.
	DDRB &= ~( (1 << MOSI) | (1 << SCK) | (1 << SS) );		// Define MOSI, SCK, and SS as Input Pins.
	DDRB |= (1 << MISO);		// Define MISO as Output Pin.

	// Select if SPI Clock Rate is Double speed or not.
	if (spr > 3){
		SPSR |= (1 << SPI2X);	// Set Double Speed SPI.
		spr &= 0X03;	// Filter The SPI Clock Rate Bits( SPR0 and SPR1 ).
	}

	// Select Slave Mode.
	SPCR &= ~(1 << MSTR);

	// Select Data Order, Clock Polarity, Clock Phase, Clock Rate.
	SPCR |= (dord << DORD) | (cpol << CPOL) | (cpha << CPHA) | (spr << SPR0);

	// Enable or Disable SPI.
	SPCR |= (spe << SPE);
}

// Function Definition to Transmit Byte using SPI.
void MHT_SPI_TX_Byte(uint8 TX_byte)
{
    uint8 flush_buffer; // Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used.
	SPDR = TX_byte; 	// Set byte data on SPI Data Register and Start Transmit.
	while(!(SPSR & (1<<SPIF)));		// Wait here until Transmission is completed.
	flush_buffer = SPDR;		    // Flush received data.
}

// Function Definition to Transmit String using SPI.
void MHT_SPI_TX_String(uint8 *TX_string)
{
	while (*TX_string != '\0'){	// check if string not finished.
		MHT_SPI_TX_Byte(*TX_string);	// Transmit the Byte that sting pointer points to it.
		++TX_string;	// point to the Next Byte.
	}
	MHT_SPI_TX_Byte('\0');	// Transmit Null Character "the end of the string".
}

// Function Definition to Receive Byte using SPI.
uint8 MHT_SPI_RX_Byte(void)
{
    SPDR = 0xFF;    // Writing Dummy Data on SPI Data Register to Start Transmission.
	while(!(SPSR & (1<<SPIF)));	// Wait here until Data Byte is Received.
	return SPDR;	// return The Received Data on SPI Data Register.
}

// Function Definition to Receive string using SPI.
void MHT_SPI_RX_String(uint8 *RX_string)
{
	*RX_string = MHT_SPI_RX_Byte();	// Receiving the data byte that and put it on the location that string pointer points towards it.
	while (*RX_string != '\0'){	// check if string not finished.
		++RX_string;	// point to the Next Location to save the next receiving byte.
		*RX_string = MHT_SPI_RX_Byte();	// Transmit the Byte that sting pointer points to it.
	}
}

// Function Definition to Transmit and Receive (Interchange) byte of data using SPI.
uint8 MHT_SPI_TX_RX_Byte(uint8 TX_byte)
{
	SPDR = TX_byte;	// Set byte data on SPI Data Register and Start Transmit.
	while(!(SPSR & (1<<SPIF)));		// Wait here until Transmission is completed.
	return SPDR;	// return The Received Data on SPI Data Register.
}

// Function Definition to Transmit and Receive (Interchange) String of data using SPI.
void MHT_SPI_TX_RX_String(uint8 *TX_string, uint8 *RX_string)
{
	while (*TX_string != '\0'){	// check if string not finished.
		*RX_string = MHT_SPI_TX_RX_Byte(*TX_string);	// Transmit the Byte that TX_string pointer points to it and put the received byte into the location where RX_String points to.
		++TX_string;	// point to the Next Byte.
		++RX_string;	// point to the next location to save the next receiving byte data.
	}
	*RX_string = MHT_SPI_TX_RX_Byte('\0');	// Transmit Null Character "the end of the string" and put the last received byte into the location where RX_string points to.
}

// Function Definition to Enable or Disable SPI interrupt Transfer Complete.
void MHT_SPI_Interrupt(uint8 spie)
{
	SPCR &= ~(1 << SPIE);	// Clear the SPI Interrupt Enable bit.
	SPCR |= (spie << SPIE);	// Disable or Enable SPI Interrupt depend on spie value.
	SREG |= (spie << 7);    // Enable Global Interrupt if SPI Interrupt is Enabled.
}

// Function Definition to Select The Desired Mode(Master or Slave).
void MHT_SPI_Select_Mode(uint8 mode)
{
	// Select the Desired Operation_Mode.
	switch(mode){
		case SLAVE_MODE:
		DDRB &= ~( (1 << MOSI) | (1 << SCK) | (1 << SS) );	// Define MOSI, SCK, and SS as Input Pins.
		DDRB |= (1 << MISO);	// Define MISO as Output Pin.
		SPCR &= ~(1 << MSTR);	// Select Slave Mode.
		break;

		case MASTER_MODE:
		DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);	// Define MOSI, SCK, and SS as Output Pins.
		DDRB &= ~(1 << MISO);	// Define MISO as Input Pin.
		SPCR |= (1 << MSTR);	// Select Master Mode.
		break;
	}
}

// Function Definition to Select The Desire Clock Polarity.
void MHT_SPI_ClockPolarity_Select(uint8 cpol)
{
	SPCR &= ~(1 << CPOL);	// Clear The Clock Polarity Bit.
	SPCR |= (cpol << CPOL);	// Select The Desired Clock Polarity.
}

// Function Definition to Select The Desire Clock Phase.
void MHT_SPI_ClockPhase_Select(uint8 cpha)
{
	SPCR &= ~(1 << CPHA);	// Clear The Clock Phase Bit.
	SPCR |= (cpha << CPOL);	// Select The Desired Clock Phase.
}

// Function Definition to Select The Desire Clock Rate.
void MHT_SPI_ClockRate_Select(uint8 spr)
{
	SPCR &= ~( (1 << SPR0) | (1 << SPR1) );	// Clear The Clock Rate.
	SPSR &= ~(1 << SPI2X);					// Clear The Clock Rate Double Speed.

	// Select if SPI Clock Rate is Double speed or not.
	if (spr > 3){
		SPSR |= (1 << SPI2X);	// Set Double Speed SPI.
		spr &= 0X03;			// Filter The SPI Clock Rate Bits( SPR0 and SPR1 ).
	}

	SPCR |= (spr << SPR0);	// Select The Desired Clock Rate.
}


// Function Definition to Stop SPI.
void MHT_SPI_Stop(void)
{
	SPCR &= ~(1 << SPE);
}




/*
// Interrupt Service Routine(ISR) for SPI Transfer Complete.
ISR(SPI_STC_vect)
{

}
*/
