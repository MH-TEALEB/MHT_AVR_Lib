/*
 * MHT_TIMER0.h
 *
 * Created: 20-Jan-20 8:03:29 PM
 *  Author: MH_TEALEB
 */


#ifndef MHT_TIMER0_H_
#define MHT_TIMER0_H_

	#ifndef F_CPU
		#define F_CPU 8000000UL     // System Clock Frequency = 8MHz.
	#endif

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>


	// Modes of Operation(wgm).
	#define NORMAL				0
	#define PHASE_CORRECT_PWM   1
	#define	CTC					2
	#define FAST_PWM			3

	// Timer0 Compare Output Mode(com).
	#define	DISCONNECT_OC0     0
	#define TOGGLE_OC0         1
	#define CLEAR_OC0          2
	#define SET_OC0            3
	#define	NON_INVERTING_OC0  2
	#define	INVERTING_OC0      3

	// Timer0 Overflow Interrupt(tovfi).
	#define	TOVFI0_DISABLE  0
	#define	TOVFI0_ENABLE   1

	// Timer0 Output Compare Interrupt(oci).
	#define OCI0_DISABLE  0
	#define	OCI0_ENABLE   1

	// Timer0 Clock Select(cs).
	#define	STOP       0
	#define	NO_PRESC   1
	#define	PRESC_8    2
	#define PRESC_64   3
	#define	PRESC_256  4
	#define	PRESC_1024 5
	#define T0_FALLING 6
	#define	T0_RISING  7


	//////////////////////////////////////////////////////////////////////////////////////////Functions Prototype//////////////////////////////////////////////////////
	void MHT_TIMER0_Init(unsigned char timer0_value, unsigned char timer0_compare_value,unsigned char wgm, unsigned char com, unsigned char tovfi, unsigned char oci, unsigned char cs);	// Initialize Timer0.
	void MHT_TIMER0_Stop(void);                                     // Stop Timer0.
	void MHT_TIMER0_OperationMode_Select(unsigned char wgm);	    // Select WaveForm Generation Mode(WGM).
	void MHT_TIMER0_CompareOutputMode_Select(unsigned char com);    // Select Compare Output Mode(COM).
    void MHT_TIMER0_Prescaler_Select(unsigned char cs);		        // Select the needed Prescaler.
    void MHT_TIMER10_Prescaler_Reset(void);						    // Reset The Prescaler in Timer0 and Timer1 as it is a shared Prescaler.
	void MHT_TIMER0_FOC(void);									    // Force Output Compare for Timer0.
	void MHT_Set_TIMER0_Value(unsigned char value);				    // Setting the value of Timer0.
	unsigned char MHT_Get_TIMER0_Value(void);					    // Getting the value of Timer0.
	void MHT_Set_TIMER0_Compare_Value(unsigned char value);		    // Setting the value of Timer0 Compare Register.
	unsigned char MHT_Get_TIMER0_Compare_Value(void);			    // Getting the value of Timer0 Compare Register
	void MHT_Clear_TIMER0_Overflow_Flag(void);					    // Clear Timer0 Overflow Flag.
	void MHT_Clear_TIMER0_Output_Compare_Flag(void);			    // Clear Timer0 Output Compare Flag.
	void MHT_Wait_TIMER0_Overflow_Flag_Set(void);				    // Wait until Timer0 Overflow Flag is Set.
	unsigned char MHT_Is_TIMER0_Overflow_Flag_Set(void);		    // Check if Timer0 Overflow flag is set. if set it will return 1 & if not set it will return 0.
	void MHT_Wait_TIMER0_Output_Compare_Flag_Set(void);			    // Wait until Timer0 Output Compare Flag is Set.
	unsigned char MHT_Is_TIMER0_Output_Compare_Flag_Set(void);	    // Check if Timer0 Output Compare flag is set. if set, it will return 1 & if not set, it will return 0.


	///////////////////////////////////////////////////////////////////Functions Macro/////////////////////////////////////////////////////////////////////////////////
    #define MHT_TIMER0_STOP()                           ({ TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02)); })  // Timer0 Stop.

    #define MHT_TIMER0_PRESCALER_SELECT(CS)             ({ TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02)); /*Clear Clock Select bits*/\
                                                           TCCR0 |= (CS << CS00);  /* Select Prescaler.*/\
                                                        })

	#define MHT_TIMER10_PRESCALER_RESET()				({ SFIOR |= (1 << PSR10); })			    // Prescaler Reset of Timer0 and Timer1 as it is a shared Prescaler.

	#define MHT_TIMER0_VALUE_SET(v)						({ TCNT0 = v; })						    // Setting the value of Timer0.
	#define MHT_TIMER0_VALUE_GET()						({ TCNT0; })							    // Getting the value of Timer0.

	#define MHT_TIMER0_COMPARE_VALUE_SET(v)				({ OCR0 = v; })							    // Setting the value of Timer0 Compare Register.
	#define MHT_TIMER0_COMPARE_VALUE_GET()				({ OCR0; })								    // Getting the value of Timer0 Compare Register.

	#define MHT_TIMER0_OVERFLOW_FLAG_CLEAR()			({ TIFR |= (1 << TOV0); })				    // Clear Timer0 Overflow Flag.
	#define MHT_TIMER0_OUTPUT_COMPARE_FLAG_CLEAR()		({ TIFR |= (1 << OCF0); })				    // Clear Timer0 Output Compare Flag.

	#define MHT_TIMER0_OVERFLOW_FLAG_WAIT()			    ({ while( (TIFR & (1 << TOV0) ) == 0); })	// Wait until Timer0 Overflow Flag is Set.
	#define MHT_TIMER0_OVERFLOW_FLAG_CHECK()			({ (TIFR & (1 << TOV0)) != 0); })			// Check Timer0 Overflow flag. if set it will return 1 & if not set it will return 0.

	#define MHT_TIMER0_OUTPUT_COMPARE_FLAG_WAIT()	    ({ while( (TIFR & (1 << OCF0) ) == 0);} )	// Wait until Timer0 Output compare Flag is Set.
	#define MHT_TIMER0_OUTPUT_COMPARE_FLAG_CHECK()		({ (TIFR & (1 << OCF0)) != 0); })			// Check Timer0 Output compare flag. if set it will return 1 & if not set it will return 0.


#endif /* MHT_TIMER0_H_ */
