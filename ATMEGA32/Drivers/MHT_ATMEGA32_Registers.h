/*
* MHT_ATMEGA32_Registers.h
*
* This is The defined Registers for ATmega32 micro-controller.
*
* Created: 27-Oct-18 12:30:23 PM
* Author : MH_TEALEB
*/

#ifndef MHT_ATMEGA32_REGISTERS_H_
#define MHT_ATMEGA32_REGISTERS_H_

#define MHT_SREG   *((volatile unsigned char* const)0X5F)
#define MHT_SPH    *((volatile unsigned char* const)0X5E)
#define MHT_SPL    *((volatile unsigned char* const)0X5D)
#define MHT_OCR0   *((volatile unsigned char* const)0X5C)
#define MHT_GICR   *((volatile unsigned char* const)0X5B)
#define MHT_GIFR   *((volatile unsigned char* const)0X5A)
#define MHT_TIMSK  *((volatile unsigned char* const)0X59)
#define MHT_TIFR   *((volatile unsigned char* const)0X58)
#define MHT_SPMCR  *((volatile unsigned char* const)0X57)
#define MHT_TWCR   *((volatile unsigned char* const)0X56)
#define MHT_MCUCR  *((volatile unsigned char* const)0X55)
#define MHT_MCUCSR *((volatile unsigned char* const)0X54)

#define MHT_TCCR0  *((volatile unsigned char* const)0X53)
#define MHT_TCNT0  *((volatile unsigned char* const)0X52)
#define MHT_OSCCAL *((volatile unsigned char* const)0X51)
#define MHT_OCDR   *((volatile unsigned char* const)0X51)
#define MHT_SFIOR  *((volatile unsigned char* const)0X50)
#define MHT_TCCR1A *((volatile unsigned char* const)0X4F)
#define MHT_TCCR1B *((volatile unsigned char* const)0X4E)
#define MHT_TCNT1H *((volatile unsigned char* const)0X4D)
#define MHT_TCNT1L *((volatile unsigned char* const)0X4C)
#define MHT_OCR1AH *((volatile unsigned char* const)0X4B)
#define MHT_OCR1AL *((volatile unsigned char* const)0X4A)
#define MHT_OCR1BH *((volatile unsigned char* const)0X49)
#define MHT_OCR1BL *((volatile unsigned char* const)0X48)
#define MHT_ICR1H  *((volatile unsigned char* const)0X47)
#define MHT_ICR1L  *((volatile unsigned char* const)0X46)
#define MHT_TCCR2  *((volatile unsigned char* const)0X45)
#define MHT_TCNT2  *((volatile unsigned char* const)0X44)
#define MHT_OCR2   *((volatile unsigned char* const)0X43)

#define MHT_ASSR   *((volatile unsigned char* const)0X42)
#define MHT_WDTCR  *((volatile unsigned char* const)0X41)
#define MHT_UBRRH  *((volatile unsigned char* const)0X40)
#define MHT_UCSRC  *((volatile unsigned char* const)0X40)
#define MHT_EEARH  *((volatile unsigned char* const)0X3F)
#define MHT_EEARL  *((volatile unsigned char* const)0X3E)
#define MHT_EEDR   *((volatile unsigned char* const)0X3D)
#define MHT_EECR   *((volatile unsigned char* const)0X3C)

#define MHT_PORTA  *((volatile unsigned char* const)0X3B)
#define MHT_DDRA   *((volatile unsigned char* const)0X3A)
#define MHT_PINA   *((volatile unsigned char* const)0X39)
#define MHT_PORTB  *((volatile unsigned char* const)0X38)
#define MHT_DDRB   *((volatile unsigned char* const)0X37)
#define MHT_PINB   *((volatile unsigned char* const)0X36)
#define MHT_PORTC  *((volatile unsigned char* const)0X35)
#define MHT_DDRC   *((volatile unsigned char* const)0X34)
#define MHT_PINC   *((volatile unsigned char* const)0X33)
#define MHT_PORTD  *((volatile unsigned char* const)0X32)
#define MHT_DDRD   *((volatile unsigned char* const)0X31)
#define MHT_PIND   *((volatile unsigned char* const)0X30)

#define MHT_SPDR   *((volatile unsigned char* const)0X2F)
#define MHT_SPSR   *((volatile unsigned char* const)0X2E)
#define MHT_SPCR   *((volatile unsigned char* const)0X2D)
#define MHT_UDR    *((volatile unsigned char* const)0X2C)
#define MHT_UCSRA  *((volatile unsigned char* const)0X2B)
#define MHT_UCSRB  *((volatile unsigned char* const)0X2A)
#define MHT_UBRRL  *((volatile unsigned char* const)0X29)
#define MHT_ACSR   *((volatile unsigned char* const)0X28)
#define MHT_ADMUX  *((volatile unsigned char* const)0X27)
#define MHT_ADCSRA *((volatile unsigned char* const)0X26)
#define MHT_ADCH   *((volatile unsigned char* const)0X25)
#define MHT_ADCL   *((volatile unsigned char* const)0X24)
#define MHT_TWDR   *((volatile unsigned char* const)0X23)
#define MHT_TWAR   *((volatile unsigned char* const)0X22)
#define MHT_TWSR   *((volatile unsigned char* const)0X21)
#define MHT_TWBR   *((volatile unsigned char* const)0X20)

#endif  // MHT_ATMEGA32_REGISTERS_H_
