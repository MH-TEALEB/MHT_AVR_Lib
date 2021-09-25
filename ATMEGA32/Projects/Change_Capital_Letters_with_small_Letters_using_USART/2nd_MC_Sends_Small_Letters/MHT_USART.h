/*
 * MHT_USART.h
 *
 * This is a Header File(.h) for USART Module in AVR ATmega32 Micro-Controller.
 *
 * Created: 6/27/2020 6:12:42 PM
 * Author : MH_TEALEB
 */

#ifndef MHT_USART_H_
#define MHT_USART_H_

    #ifndef F_CPU
		#define F_CPU 1000000UL     // Define System Clock Frequency = 1MHz, if not defined before.
	#endif

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include "MHT_ATMEGA32_StdTypes.h"
	
	// Operation_Mode(mode).
	#define ASYNC_NORMAL_MODE			0
	#define ASYNC_DOUBLE_SPEED_MODE		1
	#define SYNC_MASTER_MODE			2
	#define SYNC_SLAVE_MODE				3
	
	// USART_Character_Size(ucsz)
	#define _5BITS	0
	#define _6BITS  1
	#define _7BITS	2
	#define _8BITS	3
	#define _9BITS	7
	
	// USART_Parity_Mode(upm)
	#define NO_PARITY		0
	#define EVEN_PARITY		2
	#define ODD_PARITY		3
	
	// USART_Stop_Bits_Select(usbs)
	#define _1BIT	0
	#define _2BIT	1
	
	// USART_Clock_Polarity(ucpol)
	#define TX_RISE_RX_FALL		0
	#define TX_FALL_RX_RISE		1
	
	// Enable_Module(module)
	#define TXDIS_RXDIS		0	// Transmitter Disable _ Receiver Disable.
	#define TXEN_RXDIS		1	// Transmitter Enable  _ Receiver Disable.
	#define TXDIS_RXEN		2	// Transmitter Disable _ Receiver Enable.
	#define TXEN_RXEN    	3	// Transmitter Enable  _ Receiver Enable
	
	// Define XCK(Clock_Pin).
	#define XCK	0

	/************************************************************* Functions_Prototype******************************************************************/
	
	void MHT_USART_Init( uint8 mode, uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module);	// USART General Initialize.
	
	void MHT_USART_Init_Async_Normal_Mode(uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module);	// USART Initialize Asynchronous Normal Mode.
	void MHT_USART_Init_Async_Double_Speed_Mode(uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module); // USART Initialize Asynchronous Double Speed Mode.
	void MHT_USART_Init_Sync_Master_Mode(uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module);	// USART Initialize Synchronous Master Mode.
	void MHT_USART_Init_Sync_Slave_Mode(uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module);	// USART Initialize Synchronous Slave Mode.
	
	void MHT_USART_Reinit(uint8 mode, uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module);	// USART Reinitialize.
	
	void MHT_USART_Transmit(uint16 data);					// USART Transmitting Data Bits.
	void MHT_USART_Transmit_String(int8 *str);				/* Function Definition for USART Transmitting string with maximum 65535 characters plus         
															   Null character at the end of transmitting string for every one call of function. */

	uint16 MHT_USART_Receive(void);					        // USART Receiving Data Bits.
	
	void MHT_USART_Select_Operation_Mode(uint8 mode);		// USART Configure Operation Mode. 
	void MHT_USART_Select_Baud_Rate(uint16 ubrr);			// USART Configure Baud Rate Register(UBRR).
	void MHT_USART_Select_Character_Size(uint8 ucsz);		// USART Configure Character Size from _5BITS to _9BITS characters.
	void MHT_USART_Select_Parity_Mode(uint8 upm);			// USART Configure Parity Mode.
	void MHT_USART_Select_Stop_Bits(uint8 usbs);			// USART Select Number of Stop Bits.
	void MHT_USART_Select_Clock_Polarization(uint8 ucpol);	// USART Select Clock Polarization. "This Function is used For Synchronous Mode"
	
	void MHT_USART_EnableOrDisable_Module(uint8 module);	// USART Enable or Disable Transmitter or Receiver or Both. 
	
	void MHT_USART_Flush( void );							// Flushing The USART Data Register.
	uint8 MHT_USART_ReadUCSRC(void);						// Function Definition to Read USART Control and Status Register C (UCSRC).
			
	void MHT_USART_Stop( void );						// USART Stop (Both Transmitter and Receiver).

	/*************************************************************** MACROS ***************************************************************************/
	#define MHT_USART_WAIT_RECEIVE_COMPLETE();	({\
													 while(!( UCSRA & (1 << RXC))); 	/* Wait Until new data is received in USART Data Register.*/ \
												})
	#define MHT_USART_CHECK_RECEIVE_COMPLETE();	({\
													(UCSRA & (1 << RXC) ) != 0);		/* check if new data is received in USART Data Register.*/ \
												})                                         /* If TRUE, return 1. Else, return 0*/
												
												
	#define MHT_USART_WAIT_TRANSMIT_COMPLETE();	 ({\
													 while(!( UCSRA & (1 << TXC) ) );	/* Wait Until ALL Data is Transmitted and There is no new data in USART Data Register.*/ \
												 })
	#define MHT_USART_CHECK_TRANSMIT_COMPLETE(); ({\
													(UCSRA & (1 << TXC) ) != 0); 		/* check if ALL Data is Transmitted and new data.*/ \
												 })										  /* If TRUE, return 1. Else, return 0*/ 


	#define MHT_USART_WAIT_DATA_REGISTER_EMPTY();	({\
														while( !( UCSRA & (1 << UDRE) ) );	/* Wait Until USART Data Register become Empty.*/ \
													})
	#define MHT_USART_CHECK_DATA_REGISTER_EMPTY();	({\
														( (UCSRA & (1 << UDRE) ) != 0);	 	/* check if USART Data Register is Empty.*/ \
													})										  /* If TRUE, return 1. Else, return 0*/
	
	#define MHT_USART_CHECK_ERROR();				({\
														( (UCSRA & ((1<<FE)|(1<<DOR)|(1<<PE)) != 0) );	   /* Check If There is Error or Not.*/ \
													})														 /* If TRUE, return 1. Else, return 0.*/							
	#define MHT_USART_CHECK_FRAME_ERROR();			{\
														( (UCSRA & (1 << FE) ) != 0);	   /* Check If There is Frame Error.*/ \
													}										  /* If TRUE, return 1. Else, return 0.*/
	#define MHT_USART_CHECK_DATA_OVERUN_ERROR();	({\
														( (UCSRA & (1 << DOR)) != 0);	   /* Check If There is Data Overrun Error.*/ \
													})										  /* If TRUE, return 1. Else, return 0.*/				
	#define MHT_USART_CHECK_PARITY_ERROR();			({\
														( (UCSRA & (1 << PE)) != 0);	   /* Check If There is Parity Error.*/ \
													})										  /* If TRUE, return 1. Else, return 0.*/
																			
	#define MHT_USART_SET_DOUBLE_SPEED();	({\
												UCSRA |= (1 << U2X);	/* Set USART Transmission Double Speed.*/ \
	                                        })
	#define MHT_USART_CLEAR_DOUBLE_SPEED();	({\
												UCSRA &= ~(1 << U2X);	/* Clear USART Transmission Double Speed.*/ \
											})
	
	
	#define MHT_USART_ENABLE_MPCM();	({\
											UCSRA |= (1 << MPCM);	/* Enable Multi Processor Communication Mode.*/ \
										})
	#define MHT_USART_DISABLE_MPCM();	({\
											UCSRA &= ~(1 << MPCM);	/* Disable Multi Processor Communication Mode.*/ \
										})
	
	
	#define MHT_USART_INTERRUPT_RX_COMPLETE_ENABLE();	({\
																UCSRB |= (1 << RXCIE); /* Enable Interrupt on Receive Complete Flag (RXC).*/ \
														})
	#define MHT_USART_INTERRUPT_RX_COMPLETE_DISABLE();	({\
																UCSRB &= ~(1 << RXCIE); /* Disable Interrupt on Receive Complete Flag (RXC).*/ \
														})
	
	#define MHT_USART_INTERRUPT_TX_COMPLETE_ENABLE();	({\
																UCSRB |= (1 << TXCIE); /* Enable Interrupt on Transmit Complete Flag (TXC)*/ \
														})
	#define MHT_USART_INTERRUPT_TX_COMPLETE_DISABLE();	({\
																UCSRB &= ~(1 << TXCIE); /* Disable Interrupt on Transmit Complete Flag (RXC).*/ \
														})
	
	#define MHT_USART_INTERRUPT_DATA_REG_EMPTY_ENABLE();	({\
																UCSRB |= (1 << UDRIE); /* Enable Interrupt on USART Data Register Empty Flag (UDR).*/ \
															})
	#define MHT_USART_INTERRUPT_DATA_REG_EMPTY_DISABLE();	({\
																UCSRB &= ~(1 << UDRIE); /* Disable Interrupt on USART Data Register Empty Flag(UDR).*/ \
															})
	
	#define MHT_USART_ENABLE_RECEIVER();	({\
												 UCSRB |= (1 << RXEN); 	/* Enable USART Receiver.*/ \
											})
	#define MHT_USART_DISABLE_RECEIVER();	({\
												 UCSRB &= ~(1 << RXEN);	/* Disable USART Receiver.*/ \
											})
											
	#define MHT_USART_ENABLE_TRANSMITTER();		({\
													 UCSRB |= (1 << TXEN); 	/* Enable USART Transmitter.*/ \
												})
	#define MHT_USART_DISABLE_TRANSMITTER();	({\
													 UCSRB &= ~(1 << TXEN); 	/* Disable USART Transmitter.*/ \
												})
	
	#define MHT_USART_ENABLE_TRANSMITTER_RECEIVER();		({\
																 UCSRB |= (1 << TXEN) | (1 << RXEN); 	/* Enable USART Transmitter and Receiver.*/ \
															})
	#define MHT_USART_DISABLE_TRANSMITTER_RECEIVER();		({\
																UCSRB &= ~( (1 << TXEN) | (1 << RXEN) ); /* Disable USART Transmitter and Receiver.*/ \
															})
	
	#define MHT_USART_9TH_BIT_RECEIVE();	({\									/* Filter The 9th Bit.*/ \
												(UCSRB & (1 << RXB8) != 0);		  /* If 9th bit is 0, return 0. */ \
												                                  /* IF 9th bit is 1, return 1. */ \
											})									  
	#define MHT_USART_9TH_BIT_SET();	({\
											UCSRB |= (1 << TXB8);	/* Set the 9th bit.*/ \
										})
	#define MHT_USART_9TH_BIT_CLEAR();	({\
											UCSRB &= ~(1 << TXB8);	/* Clear the 9th bit.*/ \
										})
	
#endif // MHT_USART_H_