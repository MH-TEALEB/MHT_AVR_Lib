/*
 * MHT_SPI.h
 *
 * This is a Header(.h) File for SPI Module in AVR ATMEGA32 Micro-Controller.
 *
 * Created: 27/07/2020 9:41:15 PM
 *  Author: MH_TEALEB
 */


#ifndef MHT_SPI_H_
#define MHT_SPI_H_

	#ifndef F_CPU
		#define F_CPU	1000000UL	// Define System Clock Frequency = 1MHz, if not defined before.
	#endif

	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include "MHT_ATMEGA32_StdTypes.h"

	// Operation_Mode(mode).
	#define SLAVE_MODE	0	// Slave SPI Mode.
	#define MASTER_MODE	1	// Master SPI Mode.

	// Data_Order(dord).
	#define LSB_FIRST	0	// LSB of Data Word is Transmitted First.
	#define MSB_FIRST   1	// MSB of Data Word is Transmitted First.

	// Clock_Polarity(cpol).
	#define SCK_LOW		0		// SCK is Low when idle (Meaning Leading Edge is Rising and Trailing Edge is Falling).
	#define SCK_HIGH	1		// SCK is High when idle (Meaning Leading Edge is Falling and Trailing Edge is Rising).

	// Clock_Phase(cpha)
	#define SAMPLE_LEAD_SETUP_TRAIL	0	// Sample Data on Leading Edge - Setup on Trailing Edge.
	#define SETUP_LEAD_SAMPLE_TRAIL	1	// Setup Data on Leading Edge - Sample on Trailing Edge.

	// SPI Clock Rate Set(spr).
	#define FOSC_4		0	//	Divide System Oscillator(clock) Frequency over 4.
	#define FOSC_16		1	//	Divide System Oscillator(clock) Frequency over 16.
	#define FOSC_64		2	//	Divide System Oscillator(clock) Frequency over 64.
	#define FOSC_128	3	//	Divide System Oscillator(clock) Frequency over 128.
	#define FOSC_2		4	//	Divide System Oscillator(clock) Frequency over 2.
	#define FOSC_8		5	//	Divide System Oscillator(clock) Frequency over 8.
	#define FOSC_32		6	//	Divide System Oscillator(clock) Frequency over 32.

	// SPI Interrupt Disable/Enable(spie).
	#define SPI_INTERRUPT_DISABLE	0	// Disable SPI Interrupt.
	#define SPI_INTERRUPT_ENABLE	1	// Enable SPI Interrupt.

	// SPI Disable/Enable(spe).
	#define SPI_DISABLE	0	// Disable SPI.
	#define SPI_ENABLE	1	// Enable SPI.

	// Define SPI PINs.
	#define SS	 4
	#define MOSI 5
	#define MISO 6
	#define SCK  7


	/************************************************************* Functions_Prototype******************************************************************/
	void MHT_SPI_Init(uint8 mode, uint8 dord, uint8 cpol, uint8 cpha, uint8 spr, uint8 spe);	// Initialize SPI.
	void MHT_SPI_Init_Master(uint8 dord, uint8 cpol, uint8 cpha, uint8 spr, uint8 spe);		// Initialize SPI as Master.
	void MHT_SPI_Init_Slave(uint8 dord, uint8 cpol, uint8 cpha, uint8 spr, uint8 spe);			// Initialize SPI as Slave.

	void MHT_SPI_TX_Byte(uint8 TX_byte);		// Transmitting One Byte using SPI.
	void MHT_SPI_TX_String(uint8 *TX_string);	// Transmitting String using SPI.

	uint8 MHT_SPI_RX_Byte(void);			// Receiving Byte using SPI.
	void MHT_SPI_RX_String(uint8 *RX_string);	// Receiving String using SPI.

	uint8 MHT_SPI_TX_RX_Byte(uint8 TX_byte);						// Transmitting and Receiving (Interchange) Byte of data using SPI.
	void MHT_SPI_TX_RX_String(uint8 *TX_string, uint8 *RX_string);	// Transmitting and Receiving (Interchange) String of data using SPI.

	void MHT_SPI_Interrupt(uint8 spie);				// Enable or Disable SPI interrupt Transfer Complete.
	void MHT_SPI_Select_Mode(uint8 mode);			// Select The Desired Mode(Master or Slave).
	void MHT_SPI_ClockPolarity_Select(uint8 cpol);	// Select The Desire Clock Polarity.
	void MHT_SPI_ClockPhase_Select(uint8 cpha);		// Select The Desire Clock phase.
	void MHT_SPI_ClockRate_Select(uint8 spr);		// Select The Desired Clock Rate.

	void MHT_SPI_Stop(void);	// Stop SPI.

	/************************************************************* Functions_MACROS ***************************************************/
	#define MHT_SPI_SS_INPUT()    ({ DDRB &= ~(1 << SS); })   // Make Direction of Slave Select(SS) Pin as Input.
	#define MHT_SPI_SS_OUTPUT()   ({ DDRB |= (1 << SS);  })   // Make Direction of Slave Select(SS) Pin as Output.
    #define MHT_SPI_SS_LOW()    ({ PORTB &= ~(1 << SS); })   // Pull Slave Select(SS) Pin Low.
	#define MHT_SPI_SS_HIGH()   ({ PORTB |= (1 << SS);  })   // Pull Slave Select(SS) Pin High.


	#define MHT_SPI_MOSI_INPUT()    ({ DDRB &= ~(1 << MOSI); })   // Make Direction of MOSI Pin as Input.
	#define MHT_SPI_MOSI_OUTPUT()   ({ DDRB |= (1 << MOSI);  })   // Make Direction of MOSI Pin as Output.
    #define MHT_SPI_MOSI_LOW()    ({ PORTB &= ~(1 << MOSI); })   // Pull MOSI Pin Low.
	#define MHT_SPI_MOSI_HIGH()   ({ PORTB |= (1 << MOSI);  })   // Pull MOSI Pin High.

    #define MHT_SPI_MISO_INPUT()    ({ DDRB &= ~(1 << MISO); })   // Make Direction of MISO Pin as Input.
	#define MHT_SPI_MISO_OUTPUT()   ({ DDRB |= (1 << MISO);  })   // Make Direction of MISO Pin as Output.
    #define MHT_SPI_MISO_LOW()    ({ PORTB &= ~(1 << MISO); })   // Pull MISO Pin Low.
	#define MHT_SPI_MISO_HIGH()   ({ PORTB |= (1 << MISO);  })   // Pull MISO Pin High.

	#define MHT_SPI_SCK_INPUT()    ({ DDRB &= ~(1 << SCK); })   // Make Direction of SCK Pin as Input.
	#define MHT_SPI_SCK_OUTPUT()   ({ DDRB |= (1 << SCK);  })   // Make Direction of SCK Pin as Output.
    #define MHT_SPI_SCK_LOW()    ({ PORTB &= ~(1 << SCK); })   // Pull SCK Pin Low.
	#define MHT_SPI_SCK_HIGH()   ({ PORTB |= (1 << SCK);  })   // Pull SCK Pin High.




	#define MHT_SPI_INTERRUPT_DISABLE()		({ SPCR &= ~(1 << SPIE); })	// Disable SPI Interrupt Transfer Complete.
	#define MHT_SPI_INTERRUPT_ENABLE()		({ \
											   SPCR |= (1 << SPIE);	  /* Enable SPI Interrupt Transfer  Complete.*/ \
											   SREG |= (1 << 7);      /* Enable Global Interrupt*/ \
										    })

	#define MHT_SPI_DISABLE()	({ SPCR &= ~(1 << SPE); })	// Disable SPI.
	#define MHT_SPI_ENABLE()	({ SPCR |= (1 << SPE);	})	// Enable SPI.

	#define MHT_SPI_LSB_FIRST()	({ SPCR &= ~(1 << DORD); })	// LSB of Data Word is Transmitted First.
	#define MHT_SPI_MSB_FIRST()	({ SPCR |= (1 << DORD);  })	// MSB of Data Word is Transmitted First.

	#define MHT_SPI_TRANSFER_COMPLETE_FLAG_CHECK()	({ ( (SPSR & (1 << SPIF)) != 0); })	// Check SPI Transfer Complete flag. if set it will return 1 & if not set it will return 0.
	#define MHT_SPI_TRANSFER_COMPLETE_FLAG_WAIT()	({ while(!(SPSR & (1 << SPIF))); })	// Wait SPI Transfer Complete Flag Set.

	#define MHT_SPI_WRITE_COLLISION_FLAG_CHECK()	({ ( (SPSR & (1 << WCOL)) != 0); })	// Check SPI Write Collision flag. if set it will return 1 & if not set it will return 0.
	#define MHT_SPI_WRITE_COLLISION_FLAG_WAIT()		({ while(!(SPSR & (1 << WCOL))); })	// Wait SPI Write Collision Flag Set.

	#define MHT_SPI_DOUBLE_SPEED_SET()		({ SPSR |= (1 << SPI2X);  })	// Set SPI Double Speed Clock Rate.
	#define MHT_SPI_DOUBLE_SPEED_CLEAR()	({ SPSR &= ~(1 << SPI2X); })	// Clear SPI Double Speed Clock Rate.

#endif /* MHT_SPI_H_ */
