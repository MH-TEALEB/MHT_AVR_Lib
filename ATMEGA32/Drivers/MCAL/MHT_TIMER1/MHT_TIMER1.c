/*
 * MHT_TIMER1.c
 *
 * Created: 20-Jan-20 8:03:52 PM
 *  Author: MH_TEALEB
 */

#include "MHT_TIMER1.h"


// Function Definition to Initialize Timer1.
void MHT_TIMER1_Init(unsigned char wgm1, unsigned char com1A, unsigned char com1B, unsigned short timer1_value, unsigned short timer1_compare_A_value,unsigned short timer1_compare_B_value,unsigned short timer1_input_capture_value, unsigned char ices1, unsigned char icnc1, unsigned char foc1A, unsigned char foc1B,unsigned char tici1, unsigned char tovfi1, unsigned char oci1A,unsigned char oci1B, unsigned char cs)
{
	// Select Timer1 Mode of operation(wgm1).
	TCCR1A &= ~((1 << WGM10) | (1 << WGM11));    // Clear WaveForm Generation Mode(WGM) bits on TCCR1A.
	TCCR1A |= ( ( (wgm1 & (1 << 0) ) != 0) << WGM10) |  ( ( ( (wgm1 & (1 << 1) ) != 0) ) << WGM11);	// Set the desired bits of WGM on TCCR1A.
	
	TCCR1B &= ~((1 << WGM12) | (1 << WGM13));	 // Clear Waveform Generation Mode(WGM) bits on TCCR1B.
	TCCR1B |= ( ( (wgm1 & (1 << 2)) != 0) << WGM12) |  ( ( ( (wgm1 & (1 << 3)) != 0) ) << WGM13);	// Set the desired bits of WGM on TCCR1B.
	
	// Select Timer1 Compare A Match Output Mode(com1A).
	TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));	// To clear compare A match bits.
	TCCR1A |= (com1A << COM1A0);	// Select the compare output mode on OC1A_PIN.
	if (com1A != DISCONNECT_OC1A)	// check if OC1A_PIN is used.
	{
		DDRD |= (1 << DDD5);	// Make Direction of OC1A_PIN as Output.
	}
	
	// Select Timer1 Compare B Match Output Mode(com1B).
	TCCR1A &= ~((1 << COM1B0) | (1 << COM1B1));	// To clear compare B match bits.
	TCCR1A |= (com1B << COM1B0);	// Select the compare output mode on OC1B pin.
	if (com1B != DISCONNECT_OC1B)	// check if OC1B_PIN is used.
	{
		DDRD |= (1 << DDD4);	// Make Direction of OC1B_PIN as Output.
	}
	
	// Assign Value for Timer1 Register(timer1_value). "Note that is should be atomic operation".
	unsigned char sreg = SREG;	// Save Global interrupt flag.
	SREG &= ~(1 << 7);	// clear Global Interrupt.
	TCNT1 = timer1_value;	// Set Timer1 value on its register.
	SREG = sreg;	// Restore Global interrupt flag and Status Register value.
	
	// Assign Value for Timer1 Compare A Register(timer1_compare_A_value). "Note that is should be atomic operation".
	sreg = SREG;	// Save Global interrupt flag.
	SREG &= ~(1 << 7);	// clear Global Interrupt.
	OCR1A = timer1_compare_A_value;	// Set Timer1 Compare A value on its register.
	SREG = sreg;	// Restore Global interrupt flag and Status Register value.

	// Assign Value for Timer1 Compare B Register(timer1_compare_B_value). "Note that is should be atomic operation".
	sreg = SREG;	// Save Global interrupt flag.
	SREG &= ~(1 << 7);	// clear Global Interrupt.
	OCR1B = timer1_compare_B_value;	// Set Timer1 Compare B value on its register.
	SREG = sreg;	// Restore Global interrupt flag and Status Register value.
	
	// Assign Value for Timer1 Input Capture Register(timer1_input_capture_value). "Note that is should be atomic operation".
	sreg = SREG;	// Save Global interrupt flag.
	SREG &= ~(1 << 7);	// clear Global Interrupt.
	ICR1 = timer1_input_capture_value;	// Set Timer1 Input Capture value on its register.
	SREG = sreg;	// Restore Global interrupt flag and Status Register value.
	
	// Choose Input Capture Edge Select(ices1).
	TCCR1B &= ~(1 << ICES1);	// Clear Input Capture Edge Select bit.
	TCCR1B |= (ices1 << ICES1);	// Select Input Capture Edge.
	
	// Enable or Disable Input Capture Noise Canceler(icnc1).
	TCCR1B &= ~(1 << ICNC1);	// Clear Input Capture Noise Canceler bit.
	TCCR1B |= (icnc1 << ICNC1);	// Enable or Disable Input Capture Noise Canceler.
	
	// Choose Force Output Compare A (foc1A) or Not.
	TCCR1A |= (foc1A << FOC1A);
	
	// Choose Force Output Compare B (foc1B) or Not.
	TCCR1A |= (foc1B << FOC1B);
	
	// Enable or Disable Timer1 Input Capture Interrupt(tici1).
	TIMSK &= ~(1 << TICIE1);	// Clear Timer1 Input Capture Interrupt Enable bit.
	TIMSK |= (tici1 << TICIE1);	// Choose Enable or Disable Timer1 Input Capture Interrupt.
	SREG |= (tici1 << 7);	// Enable Global Interrupt if Enable is chosen.
	
	// Enable or Disable Timer1 Overflow Interrupt(tovfi1).
	TIMSK &= ~(1 << TOIE1);	// Clear Timer1 Overflow Interrupt Enable bit.
	TIMSK |= (tovfi1 << TOIE1);	// Choose Enable or Disable Timer1 Overflow Interrupt.
	SREG |= (tovfi1 << 7);	// Enable Global Interrupt if Enable is chosen.

	// Enable or Disable Timer1 Output Compare A Interrupt(oci1A).
	TIMSK &= ~(1 << OCIE1A);	// Clear Timer1 Output Compare A Interrupt Enable bit.
	TIMSK |= (oci1A << OCIE1A);	// Choose Enable or Disable Timer1 Output Compare A Interrupt.
	SREG |= (oci1A << 7);	// Enable Global Interrupt if Enable is chosen.
	
	// Enable or Disable Timer1 Output Compare B Interrupt(oci1B).
	TIMSK &= ~(1 << OCIE1B);	// Clear Timer1 Output Compare B Interrupt Enable bit.
	TIMSK |= (oci1B << OCIE1B);	// Choose Enable or Disable Timer1 Output Compare B Interrupt.
	SREG |= (oci1B << 7);	// Enable Global Interrupt if Enable is chosen.

	// Choose Clock Source(cs).
	TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));	// Clear Clock select bits.
	TCCR1B |= (cs << CS10);	// Choose the Selected Clock.
}


// Function Definition to Stop Timer1.
void MHT_TIMER1_Stop(void)
{
	TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));	// Select No Clock Source (Timer1 Stopped).
}

// Function Definition to Select Waveform Generation Mode(WGM).
void MHT_TIMER1_OperationMode_Select(unsigned char wgm1)
{
   TCCR1A &= ~((1 << WGM10) | (1 << WGM11));    // Clear WaveForm Generation Mode(WGM) bits on TCCR1A.
   TCCR1A |= ( ( (wgm1 & (1 << 0) ) != 0) << WGM10) |  ( ( ( (wgm1 & (1 << 1) ) != 0) ) << WGM11);	// Set the desired bits of WGM on TCCR1A.
   
   TCCR1B &= ~((1 << WGM12) | (1 << WGM13));	 // Clear Waveform Generation Mode(WGM) bits on TCCR1B.
   TCCR1B |= ( ( (wgm1 & (1 << 2)) != 0) << WGM12) |  ( ( ( (wgm1 & (1 << 3)) != 0) ) << WGM13);	// Set the desired bits of WGM on TCCR1B.
}

// Function Definition to Select Timer1 Output Compare A Mode(COM1A).
void MHT_TIMER1_Compare_A_OutputMode_Select(unsigned char com1A)
{
   TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));	// To clear compare A match bits.
   TCCR1A |= (com1A << COM1A0);	// Select the compare output mode on OC1A_PIN.
   if (com1A != DISCONNECT_OC1A)	// check if OC1A_PIN is used.
   {
	   DDRD |= (1 << DDD5);	// Make Direction of OC1A_PIN as Output.
   }
}

// Function Definition to Select Timer1 Output Compare B Mode(COM1B).
void MHT_TIMER1_Compare_B_OutputMode_Select(unsigned char com1B)
{
	TCCR1A &= ~((1 << COM1B0) | (1 << COM1B1));	// To clear compare B match bits.
	TCCR1A |= (com1B << COM1B0);	// Select the compare output mode on OC1B pin.
	if (com1B != DISCONNECT_OC1B)	// check if OC1B_PIN is used.
	{
		DDRD |= (1 << DDD4);	// Make Direction of OC1B_PIN as Output.
	}
}

// Function Definition to Select Prescaler.
void MHT_TIMER1_Prescaler_Select(unsigned char cs)
{
	// Choose Clock Source(cs).
	TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));	// Clear Clock select bits.
	TCCR1B |= (cs << CS10);	// Choose the Selected Clock.
}

// Function Definition to Reset the Prescaler in Timer0 and Timer1 as it is a shared Prescaler.
void MHT_TIMER10_Prescaler_Reset(void)
{
	SFIOR |= (1 << PSR10);
}

// Function Definition to Force Output Compare in Timer1.
void MHT_TIMER1_FOC1A(void)
{
	TCCR1A |= (1 << FOC1A);	//  Force output compare A bit.
}

// Function Definition to Force Output Compare in Timer1.
void MHT_TIMER1_FOC1B(void)
{
	TCCR1A |= (1 << FOC1B);	//  Force output compare B bit.
}

// Function Definition to Set the value of Timer1.
void MHT_Set_TIMER1_Value(unsigned short value)
{
	unsigned char sreg = SREG;	// Save Global interrupt flag.
	SREG &= ~(1 << 7);	// clear Global Interrupt.
	TCNT1 = value;	// Set Timer1 value on its register.
	SREG = sreg;	// Restore Global interrupt flag and Status Register.
}

// Function Definition to Get the value of Timer1.
unsigned short MHT_Get_TIMER1_Value(void)
{
	unsigned char sreg = SREG;	// Save Global interrupt flag.
	unsigned short value;		// Declare variable to hold Timer1 value.
	SREG &= ~(1 << 7);			// clear Global Interrupt.
	value = TCNT1;				// Get Timer1 value from its register.
	SREG = sreg;				// Restore Global interrupt flag and Status Register.
	return value;				// Return the value of Timer1.
}


// Function Definition to Set the value of Timer1 Compare A Register.
void MHT_Set_TIMER1_Compare_A_Value(unsigned short value)
{
	unsigned char sreg = SREG;	// Save Global interrupt flag.
	SREG &= ~(1 << 7);			// clear Global Interrupt.
	OCR1A = value;				// Set Timer1 Compare A value on its register.
	SREG = sreg;				// Restore Global interrupt flag and Status Register value.
}

// Function Definition to Get the value of Timer1 Compare A Register
unsigned short MHT_Get_TIMER1_Compare_A_Value(void)
{
	unsigned char sreg = SREG;	// Save Global interrupt flag.
	unsigned short value;		// Declare variable to hold the Timer1 Compare A value.
	SREG &= ~(1 << 7);			// clear Global Interrupt.
	value = OCR1A;				// Get Timer1 Compare A value from its register.
	SREG = sreg;				// Restore Global interrupt flag and Status Register value.
	return value;				// Return the value of Timer1 Compare A.
}


// Function Definition to Set the value of Timer1 Compare B Register.
void MHT_Set_TIMER1_Compare_B_Value(unsigned short value)
{
	unsigned char sreg = SREG;	// Save Global interrupt flag.
	SREG &= ~(1 << 7);			// clear Global Interrupt.
	OCR1B = value;				// Set Timer1 Compare B value on its register.
	SREG = sreg;				// Restore Global interrupt flag and Status Register value.
}
// Function Definition to Get the value of Timer1 Compare B Register
unsigned short MHT_Get_TIMER1_Compare_B_Value(void)
{
	unsigned char sreg = SREG;	// Save Global interrupt flag.
	unsigned short value;		// Declare variable to hold the Timer1 Compare B value.
	SREG &= ~(1 << 7);			// clear Global Interrupt.
	value = OCR1B;				// Get Timer1 Compare B value from its register.
	SREG = sreg;				// Restore Global interrupt flag and Status Register value.
	return value;				// Return the value for Timer1 Compare B.
}


// Function Definition to Set the value of Timer1 Input Capture Register.
void MHT_Set_TIMER1_Input_Capture_Value(unsigned short value)
{
	unsigned char sreg = SREG;		// Save Global interrupt flag.
	SREG &= ~(1 << 7);				// clear Global Interrupt.
	ICR1 = value;					// Set Timer1 Input Capture value on its register.
	SREG = sreg;					// Restore Global interrupt flag and Status Register value.
}
// Function Definition to Get the value of Timer1 Input Capture Register.
unsigned short MHT_Get_TIMER1_Input_Capture_Value(void)
{
	unsigned char sreg = SREG;		// Save Global interrupt flag.
	unsigned short value;			// Declare variable to hold The Input Capture Register value.
	SREG &= ~(1 << 7);				// clear Global Interrupt.
	value = ICR1;					// Get Timer1 Input Capture value from its register.
	SREG = sreg;					// Restore Global interrupt flag and Status Register value.
	return value;					// Return the value of Input Capture Register.
}


// Function Definition to Select Input Capture Edge.
void MHT_Input_Capture_Edge_Select(unsigned char ices)
{
	TCCR1B &= ~(1 << ICES1);	// Clear Input Capture Edge Select bit.
	TCCR1B |= (ices << ICES1);	// Select Input Capture Edge.
}

// Function Definition to Enable or Disable Input Capture Noise Canceler.
void MHT_Input_Capture_Noise_Canceler(unsigned char icnc)
{
	TCCR1B &= ~(1 << ICNC1);	// Clear Input Capture Noise Canceler bit.
	TCCR1B |= (icnc << ICNC1);	// Enable or Disable Input Capture Noise Canceler.
}	


// Function Definition to Wait until Timer1 Overflow Flag is Set.
void MHT_Wait_TIMER1_Overflow_Flag_Set(void)
{
	while( (TIFR & (1 << TOV1)) == 0);	// Wait here until flag is set.
}

// Function Definition to Check if Timer1 Overflow flag is set. 
unsigned char MHT_Is_TIMER1_Overflow_Flag_Set(void)
{
	return ( (TIFR & (1 << TOV1)) != 0 );	// if set, it will return 1 & if not set, it will return 0.
}


// Function Definition to Wait until Timer1 Output Compare A Flag is Set.
void MHT_Wait_TIMER1_Output_Compare_A_Flag_Set(void)
{
	while( (TIFR & (1 << OCF1A)) == 0);	// Wait here until flag is set.
}

// Function Definition to Check if Timer1 Output Compare A flag is set. 
unsigned char MHT_Is_TIMER1_Output_Compare_A_Flag_Set(void)
{
	return ( (TIFR & (1 << OCF1A)) != 0 );	// if set, it will return 1 & if not set, it will return 0.
}


// Function Definition to Wait until Timer1 Output Compare B Flag is Set.
void MHT_Wait_TIMER1_Output_Compare_B_Flag_Set(void)
{
	while( (TIFR & (1 << OCF1B)) == 0);	// Wait here until flag is set.
}

// Function Definition to Check if Timer1 Output Compare B flag is set.
unsigned char MHT_Is_TIMER1_Output_Compare_B_Flag_Set(void)
{
	return ( (TIFR & (1 << OCF1B)) != 0 );	// if set, it will return 1 & if not set, it will return 0.
}


// Function Definition to Wait until Timer1 Input Capture Flag is Set.
void MHT_Wait_TIMER1_Input_Capture_Flag_Set(void)
{
	while( (TIFR & (1 << ICF1)) == 0);	// Wait here until flag is set.
}

// Function Definition to Check if Timer1 Input Capture flag is set.
unsigned char MHT_Is_TIMER1_Input_Capture_Flag_Set(void)
{
	return ( (TIFR & (1 << ICF1)) != 0 );	// if set, it will return 1 & if not set, it will return 0.
}



// Function Definition to Clear Timer1 Overflow Flag.
void MHT_Clear_TIMER1_Overflow_Flag(void)
{
	TIFR |= (1 << TOV1);	// Clear Timer1 OverFlow Flag.
}

// Function Definition to Clear Timer1 Output Compare A Flag.
void MHT_Clear_TIMER1_Output_Compare_A_Flag(void)
{
	TIFR |= (1 << OCF1A);
}

// Function Definition to Clear Timer1 Output Compare B Flag.
void MHT_Clear_TIMER1_Output_Compare_B_Flag(void)
{
	TIFR |= (1 << OCF1B);
}

// Function Definition to Clear Timer1 Input Capture Flag.
void MHT_Clear_TIMER1_Input_Capture_Flag(void)
{
	TIFR |= (1 << ICF1);
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