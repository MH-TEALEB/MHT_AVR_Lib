/*
 * MHT_TIMER2.c
 *
 * Created: 20-Jan-20 8:03:52 PM
 *  Author: MH_TEALEB
 */ 

#include "MHT_TIMER2.h"


// Function Definition to Initialize Timer2. 
void MHT_TIMER2_Init(unsigned char co,unsigned char timer2_value, unsigned char timer2_compare_value,unsigned char wgm, unsigned char com, unsigned char tovfi, unsigned char oci, unsigned char cs)
{
	// Select Clock Operation between Synchronous or Asynchronous operation.
	ASSR &= ~(1 << AS2);	// Clear Asynchronous Timer2 bit.
	ASSR |= (co << AS2);	// Select the clock operation.
	
	// Assign Values for Timer2 and Compare Registers.
	while ( (ASSR & (1 << TCN2UB)) != 0);	// Wait here until TCNT2 is ready to be updated with a new value.
	TCNT2 = timer2_value;
	
	while ( (ASSR & (1 << OCR2UB)) != 0);	// Wait here until OCR2 is ready to be updated with a new value.
	OCR2 = timer2_compare_value;
	
	// Select Mode of operation.
	while ( (ASSR & (1 << TCR2UB)) != 0);	// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 &= ~((1 << WGM21) | (1 << WGM20));	// Clear WaveForm Generation Mode(WGM) bits.
	
	while ( (ASSR & (1 << TCR2UB)) != 0);	// Wait here until TCCR2 is ready to be updated with a new value.
	switch(wgm)
	{
		case NORMAL:
				// It is already selected when WGM bits are cleared before..
				break;
		case PHASE_CORRECT_PWM:
				TCCR2 |= (1 << WGM20);
				break;
		case CTC:
				TCCR2 |= (1 << WGM21);
				break;
		case FAST_PWM:
				TCCR2 |= (1 << WGM21) | (1 << WGM20);
				break;		
	}
	
	// Select Compare Match Output Mode.
	while ( (ASSR & (1 << TCR2UB)) != 0);		// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 &= ~((1 << COM20) | (1 << COM21));	// To clear compare match bits.
	
	while ( (ASSR & (1 << TCR2UB)) != 0);		// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 |= (com << COM20);					// Select the compare output mode.
	
	if (com != DISCONNECT_OC2)					// check if OC_PIN is used.
	{
		DDRD |= (1 << DDB7);	// Make Direction of OC_PIN as Output.
		PORTD &= ~(1 << PINB7);	// Initialize OC_PIN with Logic 0.
	}
	
	// Enable or Disable Timer2 Overflow Interrupt.
	TIMSK &= ~(1 << TOIE2);		// Clear Timer2 Overflow Interrupt Enable bit.
	TIMSK |= (tovfi << TOIE2);	// Choose Enable or Disable Timer2 Overflow Interrupt.
	SREG |= (tovfi << 7);		// Enable Global Interrupt. 
						
	// Enable or Disable Timer2 Output Compare Interrupt.
	TIMSK &= ~(1 << OCIE2);		// Clear Timer2 Output Compare Interrupt Enable bit. 
	TIMSK |= (oci << OCIE2);	// Choose Enable or Disable Timer2 Output Compare Interrupt.
	SREG |= (oci << 7);			// Enable Global Interrupt.

	
	// Choose Clock Select(Clock Source).
	while ( (ASSR & (1 << TCR2UB)) != 0);	                // Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));	// Clear Clock select bits.
	
	while ( (ASSR & (1 << TCR2UB)) != 0);					// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 |= (cs << CS20);	                                // Choose the Selected Clock.
}


// Function Definition to Stop Timer2.
void MHT_TIMER2_Stop(void)
{
	while ( (ASSR & (1 << TCR2UB)) != 0);	// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));	// Select No Clock Source (Timer2 Stopped).
}

// Function Definition to Select Clock Operation Between Synchronous and Asynchronous Operation.
void MHT_TIMER2_ClockOperation_Select(unsigned char co)
{
	ASSR &= ~(1 << AS2);	// Clear Asynchronous Timer2 bit.
	ASSR |= (co << AS2);	// Select the clock operation.
}

// Function Definition to Select Waveform Generation Mode(WGM).
void MHT_TIMER2_OperationMode_Select(unsigned char wgm)
{
	while ( (ASSR & (1 << TCR2UB)) != 0);		// Wait here until TCCR2 is ready to be updated with a new value if in Asynchronous Operation.
	TCCR2 &= ~((1 << WGM21) | (1 << WGM20));	// Clear WaveForm Generation Mode(WGM) bits.
	
	while ( (ASSR & (1 << TCR2UB)) != 0);		// Wait here until TCCR2 is ready to be updated with a new value.
	switch(wgm)
	{
		case NORMAL:
				// It is already selected when WGM bits are cleared before..
				break;
		case PHASE_CORRECT_PWM:
				TCCR2 |= (1 << WGM20);
				break;
		case CTC:
				TCCR2 |= (1 << WGM21);
				break;
		case FAST_PWM:
				TCCR2 |= (1 << WGM21) | (1 << WGM20);
				break;
	}
}

// Function Definition to select Compare Match Output Mode(COM).
void MHT_TIMER2_CompareOutputMode_Select(unsigned char com)
{
	while ( (ASSR & (1 << TCR2UB)) != 0);		// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 &= ~((1 << COM20) | (1 << COM21));	// To clear compare match bits.
	
	while ( (ASSR & (1 << TCR2UB)) != 0);		// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 |= (com << COM20);					// Select the compare output mode.
	
	if (com != DISCONNECT_OC2)					// check if OC_PIN is used.
	{
		DDRD |= (1 << DDB7);	// Make Direction of OC_PIN as Output.
		PORTD &= ~(1 << PINB7);	// Initialize OC_PIN with Logic 0.
	}	
}

// Function Definition to Force Output Compare in Timer2.
void MHT_TIMER2_FOC(void)
{
	while ( (ASSR & (1 << TCR2UB)) != 0);	// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 |= (1 << FOC2);	// Send Logic 1 to Force output compare bit.
}

// Function Definition to Set the value of Timer2.
void MHT_Set_TIMER2_Value(unsigned char value)
{
	while ( (ASSR & (1 << TCN2UB)) != 0);	// Wait here until TCNT2 is ready to be updated with a new value.
	TCNT2 = value;
}

// Function Definition to Get the value of Timer2.
unsigned char MHT_Get_TIMER2_Value(void)
{
	while ( (ASSR & (1 << TCN2UB)) != 0);	// Wait here until TCNT2 is ready to be updated with a new value.
	return TCNT2;
}

// Function Definition to Set the value of Timer2 Compare Register.
void MHT_Set_TIMER2_Compare_Value(unsigned char value)
{
	while ( (ASSR & (1 << OCR2UB)) != 0);	// Wait here until OCR2 is ready to be updated with a new value.
	OCR2 = value;
}

// Function Definition to Get the value of Timer2 Compare Register
unsigned char MHT_Get_TIMER2_Compare_Value(void)
{
	while ( (ASSR & (1 << OCR2UB)) != 0);	// Wait here until OCR2 is ready to be updated with a new value.
	return OCR2;
}

// Function Definition to Clear Timer2 Overflow Flag.
void MHT_Clear_TIMER2_Overflow_Flag(void)
{
	TIFR |= (1 << TOV2);
}

// Function Definition to Clear Timer2 Output Compare Flag.
void MHT_Clear_TIMER2_Output_Compare_Flag(void)
{
	TIFR |= (1 << OCF2);
}	

// Function Definition to Wait until Timer2 Overflow Flag is Set.
void MHT_Wait_TIMER2_Overflow_Flag_Set(void)
{
	while( (TIFR & (1 << TOV2)) == 0);	// Wait here until flag is set.	
}

// Function Definition to Check if Timer2 Overflow flag is set. if set it will return 1 & if not set it will return 0.
unsigned char MHT_Is_TIMER2_Overflow_Flag_Set(void)
{
	return ( (TIFR & (1 << TOV2)) != 0 );
}

// Function Definition to Wait until Timer2 Output Compare Flag is Set.
void MHT_Wait_TIMER2_Output_Compare_Flag_Set(void)
{
	while( (TIFR & (1 << OCF2)) == 0);	// Wait here until flag is set.
}

// Function Definition to Check if Timer2 Output Compare flag is set. if set, it will return 1 & if not set, it will return 0.
unsigned char MHT_Is_TIMER2_Output_Compare_Flag_Set(void)
{
	return ( (TIFR & (1 << OCF2)) != 0 );
}

// Function Definition to Reset the Prescaler in Timer2.
void MHT_TIMER2_Prescaler_Reset(void)
{
	SFIOR |= (1 << PSR2);
}

// Function Definition to Select Prescaler.
void MHT_TIMER2_Prescaler_Select(unsigned char cs)
{
	while ( (ASSR & (1 << TCR2UB)) != 0);	// Wait here until TCCR2 is ready to be updated with a new value.
	TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));	// Clear Clock select bits.
	while ( (ASSR & (1 << TCR2UB)) != 0);	// Wait here until TCCR2 is ready to be updated with a new value.	
	TCCR2 |= (cs << CS20);	// Choose the Selected Clock.
}

/*
// Interrupt Service Routine(ISR) for Timer2 Overflow Interrupt.
ISR(TIMER2_OVF_vect)
{

}

// Interrupt Service Routine(ISR) for Timer2 Output Compare Interrupt.
ISR(TIMER2_COMP_vect)
{
	
}
*/