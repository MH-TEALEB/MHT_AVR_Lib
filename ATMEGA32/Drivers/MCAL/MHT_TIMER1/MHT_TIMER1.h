/*
 * MHT_TIMER1.h
 *
 * Created: 20-Jan-20 8:03:29 PM
 *  Author: MH_TEALEB
 */


#ifndef MHT_TIMER1_H_
#define MHT_TIMER1_H_

	#ifndef F_CPU
		#define F_CPU 8000000UL     // System Clock Frequency = 8MHz.
	#endif

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>


	// Modes of Operation(wgm1).
	#define NORMAL									0
	#define PHASE_CORRECT_PWM_8bit					1
	#define PHASE_CORRECT_PWM_9bit					2
	#define PHASE_CORRECT_PWM_10bit					3
	#define	CTC_OCR1A								4
	#define FAST_PWM_8bit							5
	#define FAST_PWM_9bit							6
	#define FAST_PWM_10bit							7
	#define PHASE_FREQUENCY_CORRECT_PWM_ICR1		8
	#define PHASE_FREQUENCY_CORRECT_PWM_OCR1A		9
	#define PHASE_CORRECT_PWM_ICR1					10
	#define PHASE_CORRECT_PWM_OCR1A					11
	#define CTC_ICR1								12
	#define FAST_PWM_ICR1							14
	#define FAST_PWM_OCR1A							15

	// Timer1 Compare A Output Mode(com1A).
	#define	DISCONNECT_OC1A     0
	#define TOGGLE_OC1A         1
	#define CLEAR_OC1A          2
	#define SET_OC1A            3
	#define	NON_INVERTING_OC1A  2
	#define	INVERTING_OC1A      3
	
	// Timer1 Compare B Output Mode(com1B).
	#define	DISCONNECT_OC1B     0
	#define TOGGLE_OC1B         1
	#define CLEAR_OC1B	        2
	#define SET_OC1B            3
	#define	NON_INVERTING_OC1A  2
	#define	INVERTING_OC1A      3
	
	// Timer 1 Force Output Compare A (foc1A)
	#define FOC1A_DISABLE	0
	#define FOC1A_ENABLE	1
	
	// Timer 1 Force Output Compare B (foc1B)
	#define FOC1B_DISABLE	0
	#define FOC1B_ENABLE	1
	
	// Enable or Disable Input Capture Noise Canceler(icnc1).
	#define ICNC1_DISABLE	0
	#define ICNC1_ENABLE	1
	
	// Choose Input Capture Edge Select(ices1)
	#define ICES1_FALLING	0
	#define ICES1_RISING	1
	
	// Enable of Disable Timer1 Input Capture Interrupt(tici1).
	#define	TICI1_DISABLE  0
	#define	TICI1_ENABLE   1

	// Enable or Disable Timer1 Overflow Interrupt(tovfi1).
	#define	TOVFI1_DISABLE  0
	#define	TOVFI1_ENABLE   1

	// Enable or Disable Timer1 Output Compare Interrupt A(oci1A).
	#define OCI1A_DISABLE  0
	#define	OCI1A_ENABLE   1
	
	// Enable or Disable Timer1 Output Compare Interrupt B(oci1B).
	#define OCI1B_DISABLE  0
	#define	OCI1B_ENABLE   1

	// Timer1 Clock Select(cs).
	#define	STOP1       0
	#define	NO_PRESC1   1
	#define	PRESC1_8    2
	#define PRESC1_64   3
	#define	PRESC1_256  4
	#define	PRESC1_1024 5
	#define T1_FALLING	6
	#define	T1_RISING	7


	//////////////////////////////////////////////////////////////////////////////////////////Functions Prototype//////////////////////////////////////////////////////
	void MHT_TIMER1_Init(unsigned char wgm1, unsigned char com1A, unsigned char com1B, unsigned short timer1_value, unsigned short timer1_compare_A_value,unsigned short timer1_compare_B_value,unsigned short timer1_input_capture_value, unsigned char ices1, unsigned char icnc1, unsigned char foc1A, unsigned char foc1B,unsigned char tici1, unsigned char tovfi1, unsigned char oci1A,unsigned char oci1B, unsigned char cs);	// Initialize Timer1.
	void MHT_TIMER1_Stop(void);											// Stop Timer1.
	
	void MHT_TIMER1_OperationMode_Select(unsigned char wgm1);			// Select Timer1 WaveForm Generation Mode(WGM1).
	
	void MHT_TIMER1_Compare_A_OutputMode_Select(unsigned char com1A);    // Select Timer1 Compare A Output Mode(COM1A).
	void MHT_TIMER1_Compare_B_OutputMode_Select(unsigned char com1B);    // Select Timer1 Compare B Output Mode(COM1B).
    
	void MHT_TIMER1_Prescaler_Select(unsigned char cs);					// Select the needed Prescaler.
    void MHT_TIMER10_Prescaler_Reset(void);								// Reset The Prescaler in Timer0 and Timer1 as it is a shared Prescaler.
	
	void MHT_TIMER1_FOC1A(void);									    // Force Output Compare A for Timer1.
	void MHT_TIMER1_FOC1B(void);										// Force Output Compare B for Timer1.
	
	void MHT_Set_TIMER1_Value(unsigned short value);					// Setting the value of Timer1.
	unsigned short MHT_Get_TIMER1_Value(void);							// Getting the value of Timer1.
	
	void MHT_Set_TIMER1_Compare_A_Value(unsigned short value);		    // Setting the value of Timer1 Compare A Register.
	unsigned short MHT_Get_TIMER1_Compare_A_Value(void);			    // Getting the value of Timer1 Compare A Register
	
	void MHT_Set_TIMER1_Compare_B_Value(unsigned short value);		    // Setting the value of Timer1 Compare B Register.
	unsigned short MHT_Get_TIMER1_Compare_B_Value(void);			    // Getting the value of Timer1 Compare B Register
	
	void MHT_Set_TIMER1_Input_Capture_Value(unsigned short value);		// Setting the value of Timer1 Input Capture Register.
	unsigned short MHT_Get_TIMER1_Input_Capture_Value(void);			// Getting the value of Timer1 Input Capture Register.
	
	void MHT_Input_Capture_Edge_Select(unsigned char ices);				// Select Input Capture Edge.
	void MHT_Input_Capture_Noise_Canceler(unsigned char icnc);			// Enable or Disable Input Capture Noise Canceler
	
	void MHT_Wait_TIMER1_Overflow_Flag_Set(void);						// Wait until Timer1 Overflow Flag is Set.
	unsigned char MHT_Is_TIMER1_Overflow_Flag_Set(void);				// Check if Timer1 Overflow flag is set. if set it will return 1 & if not set it will return 0.
	
	void MHT_Wait_TIMER1_Output_Compare_A_Flag_Set(void);			    // Wait until Timer1 Output Compare A Flag is Set.
	unsigned char MHT_Is_TIMER1_Output_Compare_A_Flag_Set(void);	    // Check if Timer1 Output Compare A flag is set. if set, it will return 1 & if not set, it will return 0.

	void MHT_Wait_TIMER1_Output_Compare_B_Flag_Set(void);			    // Wait until Timer1 Output Compare B Flag is Set.
	unsigned char MHT_Is_TIMER1_Output_Compare_B_Flag_Set(void);	    // Check if Timer1 Output Compare B flag is set. if set, it will return 1 & if not set, it will return 0.

	void MHT_Wait_TIMER1_Input_Capture_Flag_Set(void);					// Wait until Timer1 Input Capture Flag is Set.
	unsigned char MHT_Is_TIMER1_Input_Capture_Flag_Set(void);			// Check if Timer1 Input Capture flag is set. if set, it will return 1 & if not set, it will return 0.



	void MHT_Clear_TIMER1_Overflow_Flag(void);							// Clear Timer1 Overflow Flag.
	void MHT_Clear_TIMER1_Output_Compare_A_Flag(void);					// Clear Timer1 Output Compare A Flag.
	void MHT_Clear_TIMER1_Output_Compare_B_Flag(void);					// Clear Timer1 Output Compare B Flag.
	void MHT_Clear_TIMER1_Input_Capture_Flag(void);						// Clear Timer1 Input Capture Flag.
	
	///////////////////////////////////////////////////////////////////Functions Macro/////////////////////////////////////////////////////////////////////////////////
    #define MHT_TIMER1_STOP()									({ TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); })  // Timer1 Stop.

    #define MHT_TIMER1_PRESCALER_SELECT(CS)						({ TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); /*Clear Clock Select bits*/\
																   TCCR1B |= (CS << CS10);  /* Select Prescaler.*/\
																})

	#define MHT_TIMER10_PRESCALER_RESET()						({ SFIOR |= (1 << PSR10); })		// Prescaler Reset of Timer0 and Timer1 as it is a shared Prescaler.


	
	// Note That: This is Not atomic operation and may or may not cause an issue.
	#define MHT_SET_TIMER1_VALUE(v)								({ TCNT1 = v; })					// Setting the value of Timer1.
	#define MHT_GET_TIMER1_VALUE()								({ TCNT1; })						// Getting the value of Timer1.
	
	// Note That: This is Not atomic operation and may or may not cause an issue.
	#define MHT_SET_TIMER1_COMPARE_A_VALUE(v)					({ OCR1A = v; })					// Setting the value of Timer1 Compare A Register.
	#define MHT_GET_TIMER1_COMPARE_A_VALUE()					({ OCR1A; })						// Getting the value of Timer1 Compare A Register.
	
	// Note That: This is Not atomic operation and may or may not cause an issue.
	#define MHT_SET_TIMER1_COMPARE_B_VALUE(v)					({ OCR1B = v; })					// Setting the value of Timer1 Compare B Register.
	#define MHT_GET_TIMER1_COMPARE_B_VALUE()					({ OCR1B; })						// Getting the value of Timer1 Compare B Register.	

	// Note That: This is Not atomic operation and may or may not cause an issue.
	#define MHT_SET_TIMER1_INPUT_CAPTURE_VALUE(v)				({ ICR1 = v; })						// Setting the value of Timer1 Input Capture Register.
	#define MHT_GET_TIMER1_INPUT_CAPTURE_VALUE()				({ ICR1; })							// Getting the value of Timer1 Input Capture Register.

		
			
	#define MHT_TIMER1_OVERFLOW_INTERRUPT_ENABLE()				({ TIMSK |= (1 << TOIE1) })			// Enable Timer1 Overflow Interrupt.
	#define MHT_TIMER1_OVERFLOW_INTERRUPT_DISABLE()				({ TIMSK &= ~(1 << TOIE1)})			// Disable Timer1 Overflow Interrupt.		
			
	#define MHT_TIMER1_OUTPUT_COMPARE_A_INTERRUPT_ENABLE()      ({ TIMSK |= (1 << OCIE1A) })		// Enable Timer1 Output Compare A Interrupt.
	#define MHT_TIMER1_OUTPUT_COMPARE_A_INTERRUPT_DISABLE()		({ TIMSK &= ~(1 << OCIE1A)})		// Disable Timer1 Output Compare A Interrupt.

	#define MHT_TIMER1_OUTPUT_COMPARE_B_INTERRUPT_ENABLE()      ({ TIMSK |= (1 << OCIE1B) })		// Enable Timer1 Output Compare B Interrupt.
	#define MHT_TIMER1_OUTPUT_COMPARE_B_INTERRUPT_DISABLE()		({ TIMSK &= ~(1 << OCIE1B)})		// Disable Timer1 Output Compare B Interrupt.
		
	#define MHT_TIMER1_INPUT_CAPTURE_INTERRUPT_ENABLE()			({ TIMSK |= (1 << TICIE1) })		// Enable Timer1 Input Capture Interrupt.
	#define MHT_TIMER1_INPUT_CAPTURE_INTERRUPT_DISABLE()		({ TIMSK &= ~(1 << TICIE1)})		// Disable Timer1 Input Capture Interrupt.



	#define MHT_TIMER1_SELECT_INPUT_CAPTURE_EDGE_RISING()		({ TCCR1B |= (1 << ICES1) })		// Select Timer1 Trigger on Rising Edge.
	#define MHT_TIMER1_SELECT_INPUT_CAPTURE_EDGE_FALLING()		({ TCCR1B &= ~(1 << ICES1) })		// Select Timer1 Trigger on Falling Edge.
		
	#define MHT_TIMER1_INPUT_CAPTURE_NOISE_CANCELER_ENABLE()	({ TCCR1B |= (1 << ICNC1) })		// Enable Timer1 Input Capture Noise Canceler.
	#define MHT_TIMER1_INPUT_CAPTURE_NOISE_CANCELER_DISABLE()	({ TCCR1B &= ~(1 << ICNC1)})		// Disable Timer1 Input Capture Noise Canceler.
	
	
			
	#define MHT_WAIT_TIMER1_OVERFLOW_FLAG_SET()				({ while( (TIFR & (1 << TOV1) ) == 0); })	// Wait until Timer1 Overflow Flag is Set.
	#define MHT_IS_TIMER1_OVERFLOW_FLAG_SET()				({ (TIFR & (1 << TOV1)) != 0); })			// Check if Timer1 Overflow flag is set. if set it will return 1 & if not set it will return 0.

	#define MHT_WAIT_TIMER1_OUTPUT_COMPARE_A_FLAG_SET()		({ while( (TIFR & (1 << OCF1A) ) == 0);} )	// Wait until Timer1 Output compare A Flag is Set.
	#define MHT_IS_TIMER1_OUTPUT_COMPARE_A_FLAG_SET()		({ (TIFR & (1 << OCF1A)) != 0); })			// Check if Timer1 Output compare A flag is set. if set it will return 1 & if not set it will return 0.

	#define MHT_WAIT_TIMER1_OUTPUT_COMPARE_B_FLAG_SET()		({ while( (TIFR & (1 << OCF1B) ) == 0);} )	// Wait until Timer1 Output compare B Flag is Set.
	#define MHT_IS_TIMER1_OUTPUT_COMPARE_B_FLAG_SET()		({ (TIFR & (1 << OCF1B)) != 0); })			// Check if Timer1 Output compare B flag is set. if set it will return 1 & if not set it will return 0.

	#define MHT_WAIT_TIMER1_INPUT_CAPTURE_FLAG_SET()		({ while( (TIFR & (1 << ICF1) ) == 0);} )	// Wait until Input Capture Flag is Set.
	#define MHT_IS_TIMER1_INPUT_CAPTURE_FLAG_SET()			({ (TIFR & (1 << ICF1)) != 0); })			// Check if Timer1 Input Capture flag is set. if set it will return 1 & if not set it will return 0.

	#define MHT_CLEAR_TIMER1_OVERFLOW_FLAG()			({ TIFR |= (1 << TOV1); })				    // Clear Timer1 Overflow Flag.
	#define MHT_CLEAR_TIMER1_OUTPUT_COMPARE_A_FLAG()	({ TIFR |= (1 << OCF1A); })				    // Clear Timer1 Output Compare A Flag.
	#define MHT_CLEAR_TIMER1_OUTPUT_COMPARE_B_FLAG()	({ TIFR |= (1 << OCF1B); })				    // Clear Timer1 Output Compare B Flag.
	#define MHT_CLEAR_TIMER1_INPUT_CAPTURE_FLAG()		({ TIFR |= (1 << ICF1); })				    // Clear Timer1 Input Capture Flag.


#endif /* MHT_TIMER1_H_ */
