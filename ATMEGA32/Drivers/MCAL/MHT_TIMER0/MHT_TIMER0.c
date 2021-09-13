/*
 * MHT_TIMER0.c
 *
 * Created: 20-Jan-20 8:03:52 PM
 *  Author: MH_TEALEB
 */

#include "MHT_TIMER0.h"


// Function Definition to Initialize Timer0
void MHT_TIMER0_Init(unsigned char timer0_value, unsigned char timer0_compare_value,unsigned char wgm, unsigned char com, unsigned char tovfi, unsigned char oci, unsigned char cs)
{
	// Assign Values for Timer and Compare Registers.
	TCNT0 = timer0_value;
	OCR0 = timer0_compare_value;

	// Select Mode of operation.
	TCCR0 &= ~((1 << WGM00) | (1 << WGM01));    // Clear WaveForm Generation Mode(WGM) bits.
	switch(wgm)
	{
		case NORMAL:
				// It is already selected when WGM bits is cleared before.
				break;
		case PHASE_CORRECT_PWM:
				TCCR0 |= (1 << WGM00);
				break;
		case CTC:
				TCCR0 |= (1 << WGM01);
				break;
		case FAST_PWM:
				TCCR0 |= (1 << WGM01) | (1 << WGM00);
				break;

	}

	// Select Compare Match Output Mode
	TCCR0 &= ~((1 << COM00) | (1 << COM01));	// To clear compare match bits.
	TCCR0 |= (com << COM00);	// Select the compare output mode.
	if (com != DISCONNECT_OC0)	// check if OC_PIN is used.
	{
		DDRB |= (1 << DDB3);	// Make Direction of OC_PIN as Output.
		PORTB &= ~(1 << PINB3);	// Initialize OC_PIN with Logic 0.
	}

	// Enable or Disable Timer0 Overflow Interrupt.
	TIMSK &= ~(1 << TOIE0);	// Clear Timer0 Overflow Interrupt Enable bit.
	TIMSK |= (tovfi << TOIE0);	// Choose Enable or Disable Timer0 Overflow Interrupt.
	SREG |= (tovfi << 7);	// Enable Global Interrupt.

	// Enable or Disable Timer0 Output Compare Interrupt.
	TIMSK &= ~(1 << OCIE0);	// Clear Timer0 Output Compare Interrupt Enable bit.
	TIMSK |= (oci << OCIE0);	// Choose Enable or Disable Timer0 Output Compare Interrupt.
	SREG |= (oci << 7);	// Enable Global Interrupt.


	// Choose Clock Select(Clock Source).
	TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));	// Clear Clock select bits.
	TCCR0 |= (cs << CS00);	// Choose the Selected Clock.
}


// Function Definition to Stop Timer0.
void MHT_TIMER0_Stop(void)
{
	TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));	// Select No Clock Source (Timer0 Stopped).
}

// Function Definition to Select Waveform Generation Mode(WGM).
void MHT_TIMER0_OperationMode_Select(unsigned char wgm)
{
    TCCR0 &= ~((1 << WGM00) | (1 << WGM01));    // Clear WaveForm Generation Mode(WGM) bits.
	switch(wgm)
	{
		case NORMAL:
				// It is already selected when WGM bits is cleared before.
				break;
		case PHASE_CORRECT_PWM:
				TCCR0 |= (1 << WGM00);
				break;
		case CTC:
				TCCR0 |= (1 << WGM01);
				break;
		case FAST_PWM:
				TCCR0 |= (1 << WGM01) | (1 << WGM00);
				break;

	}
}

// Function Definition to Select Output Compare Mode(COM).
void MHT_TIMER0_CompareOutputMode_Select(unsigned char com)
{
    TCCR0 &= ~((1 << COM00) | (1 << COM01));	// To clear compare match bits.
	TCCR0 |= (com << COM00);	// Select the compare output mode.
	if (com != DISCONNECT_OC0)	// check if OC_PIN is used.
	{
		DDRB |= (1 << DDB3);	// Make Direction of OC_PIN as Output.
		PORTB &= ~(1 << PINB3);	// Initialize OC_PIN with Logic 0.
	}
}

// Function Definition to Select Prescaler.
void MHT_TIMER0_Prescaler_Select(unsigned char cs)
{
	TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));	// Clear Clock select bits.
	TCCR0 |= (cs << CS00);	                                // Choose the Selected Clock.
}

// Function Definition to Reset the Prescaler in Timer0 and Timer1 as it is a shared Prescaler.
void MHT_TIMER10_Prescaler_Reset(void)
{
	SFIOR |= (1 << PSR10);
}

// Function Definition to Force Output Compare in Timer0.
void MHT_TIMER0_FOC(void)
{
	TCCR0 |= (1 << FOC0);	// Send Logic 1 to Force output compare bit.
}

// Function Definition to Set the value of Timer0.
void MHT_Set_TIMER0_Value(unsigned char value)
{
	TCNT0 = value;
}

// Function Definition to Get the value of Timer0.
unsigned char MHT_Get_TIMER0_Value(void)
{
	return TCNT0;
}

// Function Definition to Set the value of Timer0 Compare Register.
void MHT_Set_TIMER0_Compare_Value(unsigned char value)
{
	OCR0 = value;
}

// Function Definition to Get the value of Timer0 Compare Register
unsigned char MHT_Get_TIMER0_Compare_Value(void)
{
	return OCR0;
}

// Function Definition to Clear Timer0 Overflow Flag.
void MHT_Clear_TIMER0_Overflow_Flag(void)
{
	TIFR |= (1 << TOV0);
}

// Function Definition to Clear Timer0 Output Compare Flag.
void MHT_Clear_TIMER0_Output_Compare_Flag(void)
{
	TIFR |= (1 << OCF0);
}

// Function Definition to Wait until Timer0 Overflow Flag is Set.
void MHT_Wait_TIMER0_Overflow_Flag_Set(void)
{
	while( (TIFR & (1 << TOV0)) == 0);	// Wait here until flag is set.
}

// Function Definition to Check if Timer0 Overflow flag is set. if set it will return 1 & if not set it will return 0.
unsigned char MHT_Is_TIMER0_Overflow_Flag_Set(void)
{
	return ( (TIFR & (1 << TOV0)) != 0 );
}

// Function Definition to Wait until Timer0 Output Compare Flag is Set.
void MHT_Wait_TIMER0_Output_Compare_Flag_Set(void)
{
	while( (TIFR & (1 << OCF0)) == 0);	// Wait here until flag is set.
}

// Function Definition to Check if Timer0 Output Compare flag is set. if set, it will return 1 & if not set, it will return 0.
unsigned char MHT_Is_TIMER0_Output_Compare_Flag_Set(void)
{
	return ( (TIFR & (1 << OCF0)) != 0 );
}


/*
// Interrupt Service Routine(ISR) for Timer0 Overflow Interrupt.
ISR(TIMER0_OVF_vect)
{

}

// Interrupt Service Routine(ISR) for Timer0 Output Compare Interrupt.
ISR(TIMER0_COMP_vect)
{

}
*/
