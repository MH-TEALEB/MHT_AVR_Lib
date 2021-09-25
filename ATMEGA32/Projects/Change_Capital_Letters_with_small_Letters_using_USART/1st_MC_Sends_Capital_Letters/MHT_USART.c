/*
 * MHT_USART.c
 *
 * This is a driver (.c) file for USART Module in AVR ATmega32 Micro-Controller.
 *
 * Created: 6/27/2020 6:12:42 PM
 * Author : MH_TEALEB
 */ 

#include "MHT_USART.h"


// Function Definition for USART General Initialize.
void MHT_USART_Init( uint8 mode, uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module)
{
	/* If 9 Bits is Selected */
	UCSRB &= ~(1 << UCSZ2);		// Put Logic 0 on UCSZ2 bit..
	if(ucsz == _9BITS){			// Filter the 9th bit, if there.
		ucsz = 3;				// To be able to put logic 1 on UCSZ0 and UCSZ1 bits when accessing UCSRC Register in the coming step.
		UCSRB |= (1 << UCSZ2);	// Put logic 1 on UCSZ2 bit.
	}
	
	// Select Operation_Mode(mode), and Configure Data Character Size, Parity_Mode, Number of Stop Bits and Clock Polarization.
	switch(mode){
		
		case ASYNC_NORMAL_MODE:	// If Asynchronous Normal Mode is Selected.
		// Select UCSRC Register, Asynchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
		UCSRC  = ((1 << URSEL) & ~(1 << UMSEL)) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
		UCSRA &= ~(1 << U2X);	// Select Normal Speed Mode.
		break;
		
		case ASYNC_DOUBLE_SPEED_MODE:	// If Asynchronous Double Speed Mode is Selected.
		// Select UCSRC Register, Asynchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
		UCSRC  = ((1 << URSEL) & ~(1 << UMSEL)) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
		UCSRA |= (1 << U2X);	// Select Double Speed Mode.
		break;
		
		case SYNC_MASTER_MODE:	// If Synchronous Master Mode is Selected.
		// Select UCSRC Register, Synchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
		UCSRC  = (1 << URSEL) | (1 << UMSEL) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
		DDRB  |= (1 << XCK);	// Make XCK(USART_Clock_Pin) as Output to Select Master Mode.
		break;
		
		case SYNC_SLAVE_MODE:	// If Synchronous Slave Mode is Selected.
		// Select UCSRC Register, Synchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
		UCSRC  = (1 << URSEL) | (1 << UMSEL) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
		DDRB &= ~(1 << XCK);	// Make XCK(USART_Clock_Pin) as Input to Select Slave Mode.
		break;
	}
	
	// Select the Baud Rate.... " If Synchronous Slave mode is Selected, ubrr value will not effect any thing if written."
	UBRRH = (uint8)(ubrr>>8);	// Write to High Baud Rate Register
	UBRRL = (uint8)ubrr;		//Write to Low Baud Rate Register
	
	/* Enable or Disable The Needed Module(Transmitter, Receiver or Both). */
	UCSRB &= ~((1 << TXEN) | (1 << RXEN));	// Disable Both Modules (Transmitter and Receiver).
	UCSRB |= (module << TXEN);	// Select The Needed Module( Transmitter, Receiver or Both).
}


// Function Definition for USART Initialize Asynchronous Normal Mode.
void MHT_USART_Init_Async_Normal_Mode( uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module)
{
	// If 9 Bits is Selected.
	if(ucsz == _9BITS){
		ucsz = 3;	// To be able to put logic 1 on UCSZ0 and UCSZ1 bits when accessing UCSRC Register in the coming step.
		UCSRB |= (1 << UCSZ2);	// Put logic 1 on UCSZ2 bit.
	}
	
	// Select the Baud Rate.
	UBRRH = (uint8)(ubrr>>8);	// Write to High Baud Rate Register
	UBRRL = (uint8)ubrr;	//Write to Low Baud Rate Register
	
	// Select UCSRC Register, Asynchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
	UCSRC = ((1 <<URSEL) & ~(1 << UMSEL)) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
	UCSRA &= ~(1 << U2X);	// Select Normal Speed Mode.
	
	// Enable The needed Module(Transmitter, Receiver or Both).
	UCSRB |= (module << TXEN);
}

// Function Definition for USART Initialize Asynchronous Double Speed Mode.
void MHT_USART_Init_Async_Double_Speed_Mode( uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module)
{
	// If 9 Bits is Selected.
	if(ucsz == _9BITS)
	{
		ucsz = 3;	// To be able to put logic 1 on UCSZ0 and UCSZ1 bits when accessing UCSRC Register in the coming step.
		UCSRB |= (1 << UCSZ2);	// Put logic 1 on UCSZ2 bit.
	}
	
	// Select the Baud Rate.
	UBRRH = (uint8)(ubrr>>8);	// Write to High Baud Rate Register
	UBRRL = (uint8)ubrr;	//Write to Low Baud Rate Register
	
	// Select UCSRC Register, Asynchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
	UCSRC = ((1 << URSEL) & ~(1 << UMSEL)) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
	UCSRA |= (1 << U2X);	// Select Double Speed Mode.
	
	// Enable The needed Module(Transmitter, Receiver or Both).
	UCSRB |= (module << TXEN);
}

// Function Definition for USART Initialize Synchronous Master Mode.
void MHT_USART_Init_Sync_Master_Mode( uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module)
{
	// If 9 Bits is Selected.
	if(ucsz == _9BITS)
	{
		ucsz = 3;	// To be able to put logic 1 on UCSZ0 and UCSZ1 bits when accessing UCSRC Register in the coming step.
		UCSRB |= (1 << UCSZ2);	// Put logic 1 on UCSZ2 bit.
	}
	
	// Select the Baud Rate.
	UBRRH = (uint8)(ubrr>>8);	// Write to High Baud Rate Register
	UBRRL = (uint8)ubrr;	//Write to Low Baud Rate Register
	
	// Select UCSRC Register, Synchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
	UCSRC = (1 << URSEL) | (1 << UMSEL) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
	DDRB |= (1 << XCK);		// Make XCK(USART_Clock_Pin) as Output to Select Master Mode.	
	
	// Enable The needed Module(Transmitter, Receiver or Both).
	UCSRB |= (module << TXEN);
}

// Function Definition for USART Initialize Synchronous Slave Mode.
void MHT_USART_Init_Sync_Slave_Mode( uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module)
{
	// If 9 Bits is Selected.
	if(ucsz == _9BITS)
	{
		ucsz = 3;	// To be able to put logic 1 on UCSZ0 and UCSZ1 bits when accessing UCSRC Register in the coming step.
		UCSRB |= (1 << UCSZ2);	// Put logic 1 on UCSZ2 bit.
	}
	
	// Select UCSRC Register, Synchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
	UCSRC = (1 << URSEL) | (1 << UMSEL) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
	DDRB &= ~(1 << XCK);	// Make XCK(USART_Clock_Pin) as Input to Select Slave Mode.
		
	// Enable The needed Module(Transmitter, Receiver or Both).
	UCSRB |= (module << TXEN);
}

// Function Definition for USART Reinitialize
void MHT_USART_Reinit( uint8 mode, uint16 ubrr, uint8 ucsz, uint8 upm, uint8 usbs, uint8 ucpol, uint8 module)
{
	/* If 9 Bits is Selected */
	UCSRB &= ~(1 << UCSZ2);		// Put Logic 0 on UCSZ2 bit..
	if(ucsz == _9BITS){			// Filter the 9th bit, if there.
		ucsz = 3;				// To be able to put logic 1 on UCSZ0 and UCSZ1 bits when accessing UCSRC Register in the coming step.
		UCSRB |= (1 << UCSZ2);	// Put logic 1 on UCSZ2 bit.
	}
	
	// Select Operation_Mode(mode) and Update the Other bits.
	switch(mode){
		
		case ASYNC_NORMAL_MODE:	// If Asynchronous Normal Mode is Selected.
			// Select UCSRC Register, Asynchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
			UCSRC  = ((1 << URSEL) & ~(1 << UMSEL)) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
			UCSRA &= ~(1 << U2X);	// Select Normal Speed Mode.
			break;
		
		case ASYNC_DOUBLE_SPEED_MODE:	// If Asynchronous Double Speed Mode is Selected.
			// Select UCSRC Register, Asynchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
			UCSRC  = ((1 << URSEL) & ~(1 << UMSEL)) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
			UCSRA |= (1 << U2X);	// Select Double Speed Mode.
			break;
		
		case SYNC_MASTER_MODE:	// If Synchronous Master Mode is Selected.
			// Select UCSRC Register, Synchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
			UCSRC  = (1 << URSEL) | (1 << UMSEL) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
			DDRB  |= (1 << XCK);	// Make XCK(USART_Clock_Pin) as Output to Select Master Mode.
			break;
		
		case SYNC_SLAVE_MODE:	// If Synchronous Slave Mode is Selected.
			// Select UCSRC Register, Synchronous Operation mode, ucsz Data Character Size, upm Parity Mode, usbs Stop Bits, ucpol Clock Polarization.
			UCSRC  = (1 << URSEL) | (1 << UMSEL) | (ucsz << UCSZ0) | (upm << UPM0) | (usbs << USBS) | (ucpol << UCPOL);
			DDRB &= ~(1 << XCK);	// Make XCK(USART_Clock_Pin) as Input to Select Slave Mode.
			break;
	}
	
	// Select the Baud Rate.... " If Synchronous Slave mode is Selected, ubrr value will not effect any thing if written."
	UBRRH = (uint8)(ubrr>>8);	// Write to High Baud Rate Register
	UBRRL = (uint8)ubrr;		//Write to Low Baud Rate Register
	
	/* Enable or Disable The Needed Module(Transmitter, Receiver or Both). */
	UCSRB &= ~((1 << TXEN) | (1 << RXEN));	// Disable Both Modules (Transmitter and Receiver).
	UCSRB |= (module << TXEN);	// Select The Needed Module( Transmitter, Receiver or Both).
}

// Function Definition for USART Transmitting.
void MHT_USART_Transmit(uint16 data)
{
	while ( !(UCSRA & (1 << UDRE) ) );		// Wait here until USART Data Register become Empty.
	
	// Filter 9th bit to TXB8, if there is.
	UCSRB &= ~(1 << TXB8);	// Clear The 9th bit.
	if ( data & 0x0100 ){	// Check if 9th bit in the Data is 1.
		UCSRB |= (1 << TXB8);	// If True, set 9th bit of the Transmitter to 1.
	}
	
	UDR = data;		// Put data into USART Data Register( Transmit the data).
}

// Function Definition for USART Transmitting string with maximum 65535 characters plus Null character at end for every one call of function.
void MHT_USART_Transmit_String(int8 *str)
{
	uint16 i = 0;	// Declare and initialize variable to point to number of characters.
	while(str[i] != '\0') // continue if the string not finished(not fined Null Character).
	{
		MHT_USART_Transmit(str[i]);	// Transmit The current character.
		++i;	// Point to next Character.
	}
	
	MHT_USART_Transmit('\0');	// Transmit Null Character at the end of string.
}

// Function Definition for USART Receiving.
uint16 MHT_USART_Receive(void)
{
	uint8 rxb8;	// Declare variable to hold the 9th bit.

	while ( !(UCSRA & (1<<RXC)) );	// Wait Until new data is received in USART Data Register.
	
	if ( UCSRA & ( (1<<FE)|(1<<DOR)|(1<<PE)) ){	// If There is error, return -1 
		return -1;
	}
	
	rxb8 = ( UCSRB & ~(1 << RXB8) ) >> RXB8;	// Filter the 9th bit of the Coming data.   
	return ((rxb8 << 8) | UDR);	// Return All the Received Data That are in UDR plus in the 9th bit if there.
}

// Function Definition for USART Selecting Operation Mode.
void MHT_USART_Select_Operation_Mode(uint8 mode)
{	
	// Select Operation_Mode(mod).
	switch(mode){
		
		case ASYNC_NORMAL_MODE:		// If Asynchronous Normal Mode is Selected.
			UCSRC &= ~(1 << UMSEL);	// Select UCSRC Register, Asynchronous Operation mode.
			UCSRA &= ~(1 << U2X);	// Select Normal Speed Mode.
			break;
		
		case ASYNC_DOUBLE_SPEED_MODE:	// If Asynchronous Double Speed Mode is Selected.
			UCSRC &= ~(1 << UMSEL);	// Select UCSRC Register, Asynchronous Operation mode.
			UCSRA |= (1 << U2X);	// Select Double Speed Mode.
			break;
		
		case SYNC_MASTER_MODE:	// If Synchronous Master Mode is Selected.
			UCSRC |= (1 << URSEL) | (1 << UMSEL);		// Select UCSRC Register, Synchronous Operation mode.
			DDRB  |= (1 << XCK);	// Make XCK(USART_Clock_Pin) as Output to Select Master Mode.
			break;
		
		case SYNC_SLAVE_MODE:	// If Synchronous Slave Mode is Selected.
			UCSRC  |= (1 << URSEL) | (1 << UMSEL);	// Select UCSRC Register, Synchronous Operation mode.
			DDRB &= ~(1 << XCK);	// Make XCK(USART_Clock_Pin) as Input to Select Slave Mode.
			break;
	}
}

// Function Definition for USART Selecting Baud Rate Register(UBRR). 
void MHT_USART_Select_Baud_Rate(uint16 ubrr)
{
	// Select the Baud Rate.... " If Synchronous Slave mode is Selected, ubrr value will not effect any thing if written."
	UBRRH = (uint8)(ubrr>>8);	// Write to High Baud Rate Register
	UBRRL = (uint8)ubrr;		//Write to Low Baud Rate Register
}		

// Function Definition for USART Selecting Character Size from _5BITS to _9BITS characters.
void MHT_USART_Select_Character_Size(uint8 ucsz)
{
	// Put 0s in USART Character Size Bits.
	UCSRC &= ~((1 << UCSZ0) | (1 << UCSZ1) );	// Select Accessing UCSRC Register and Put 0s in UCSZ0 and UCSZ1 bits.
	UCSRB &= ~(1 << UCSZ2);	// Put Logic 0 on UCSZ2 bit.
	
	// If 9 Bits is Selected.
	if(ucsz == _9BITS){
		ucsz = 3;	// To be able to put logic 1 on UCSZ0 and UCSZ1 bits when accessing UCSRC Register in the coming step.
		UCSRB |= (1 << UCSZ2);	// Put logic 1 on UCSZ2 bit.
	}
	
	UCSRC |= (1 << URSEL) | (ucsz << UCSZ0);	// Select to Access UCSRC and Configure The Desired Character Size. 
}

// Function Definition for USART Selecting Parity Mode.
void MHT_USART_Select_Parity_Mode(uint8 upm)
{
	UCSRC  &= ~( (1 << UPM0) | (1 << UPM1) );		// Select UCSRC Register and Put 0s in USART Parity Mode bits.
	
	UCSRC  |= (1 << URSEL) | (upm << UPM0);		// Select UCSRC Register,upm Parity Mode.
}		

// Function Definition for USART Selecting Number of Stop Bits.
void MHT_USART_Select_Stop_Bits(uint8 usbs)
{
	UCSRC  &= ~(1 << USBS);		// Select UCSRC Register and Put 0 in USART Stop bits bit Select.
	
	UCSRC  |= (1 << URSEL) | (usbs << USBS);		// Select UCSRC Register and usbs Stop bits Select.
}		

// Function Definition for USART Select Clock Polarization. "This Function is used For Synchronous Mode"
void MHT_USART_Select_Clock_Polarization(uint8 ucpol)	
{
	UCSRC  &= ~(1 << UCPOL);		// Select UCSRC Register and Put 0 in USART Clock Polarization bit.
	
	UCSRC  |= (1 << URSEL) | (ucpol << UCPOL);		// Select UCSRC Register and ucpol Clock Polarization.
}

// Function Definition for USART Enabling or Disabling Transmitter, Receiver or Both.
void MHT_USART_EnableOrDisable_Module(uint8 module)
{	
	UCSRB &= ~((1 << TXEN) | (1 << RXEN));	// Disable Both Modules (Transmitter and Receiver).
	UCSRB |= (module << TXEN);	// Select The Needed Module( Transmitter, Receiver or Both),
}

// Function Definition for Flushing USART Data Register.
void MHT_USART_Flush( void )
{
	uint8 dummy;
	while ( UCSRA & (1 << RXC) ) {
		dummy = UDR;
	}
}

// Function Definition for Reading USART Control and Status Register C (UCSRC).
uint8 MHT_USART_ReadUCSRC( void )
{
	uint8 ucsrc;
	
	ucsrc = UBRRH;
	ucsrc = UCSRC;
	
	return ucsrc;
}

// Function Definition for USART Stop (Both Transmitter and Receiver).
void MHT_USART_Stop(void)
{
	UCSRB &= ~((1 << TXEN) | (1 << RXEN));	// USART Stop (Both Transmitter and Receiver).
}


// Interrupt Service Routine(ISR) for USART
/*

	// Interrupt Service Routine(ISR) for USART Receive Complete Flag (RXC).
	ISR(USART_RXC_vect)
	{

	}

	// Interrupt Service Routine(ISR) for USART Transmit Complete Flag (TXC).
	ISR(USART_TXC_vect)
	{

	}

	// Interrupt Service Routine(ISR) for USART Data Register Empty Flag (UDRE).
	ISR(USART_UDRE_vect)
	{

	}

*/