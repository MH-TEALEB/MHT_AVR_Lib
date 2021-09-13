/*
 * MHT_TIMER2.h
 *
 * Created: 20-Jan-20 8:03:29 PM
 *  Author: MH_TEALEB
 */


#ifndef MHT_TIMER2_H_
#define MHT_TIMER2_H_

	#ifndef F_CPU
		#define F_CPU 1000000UL     // System Clock Frequency = 1MHz.
	#endif

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	
	
	// Timer2 Clock Operation(co)
	#define SYNCHRONOUS  0
	#define ASYNCHRONOUS 1

	// Modes of Operation(wgm).
	#define NORMAL				0
	#define PHASE_CORRECT_PWM   1
	#define	CTC					2
	#define FAST_PWM			3

	// Timer2 Compare Output Mode(com).
	#define	DISCONNECT_OC2     0
	#define TOGGLE_OC2         1
	#define CLEAR_OC2          2
	#define SET_OC2            3
	#define	NON_INVERTING_OC2  2
	#define	INVERTING_OC2      3

	// Timer2 Overflow Interrupt(tovfi).
	#define	TOVFI2_DISABLE  0
	#define	TOVFI2_ENABLE   1

	// Timer2 Output Compare Interrupt(oci).
	#define OCI2_DISABLE  0
	#define	OCI2_ENABLE   1

	// Timer2 Clock Select(cs).
	#define	STOP       0
	#define	NO_PRESC   1
	#define	PRESC_8    2
	#define PRESC_32   3
	#define	PRESC_64   4
	#define	PRESC_128  5
	#define PRESC_256  6
	#define	PRESC_1024 7


	//////////////////////////////////////////////////////////////////////////////////////////Functions Prototype//////////////////////////////////////////////////////
	void MHT_TIMER2_Init(unsigned char co,unsigned char timer2_value, unsigned char timer2_compare_value,unsigned char wgm, unsigned char com, unsigned char tovfi, unsigned char oci, unsigned char cs);	// Initialize Timer2.
	void MHT_TIMER2_Stop(void);										// Stop Timer2.
	void MHT_TIMER2_ClockOperation_Select(unsigned char co);		// Select the desired Clock Operation between Synchronous or Asynchronous.
	void MHT_TIMER2_OperationMode_Select(unsigned char wgm);		// Select the desired Waveform Generation Moder(WGM).
	void MHT_TIMER2_CompareOutputMode_Select(unsigned char com);	// Select Compare Match Output Mode(COM).
	void MHT_TIMER2_Prescaler_Select(unsigned char cs);				// Select the needed Prescaler.
	void MHT_TIMER2_Prescaler_Reset(void);							// Reset The Prescaler in Timer2 and Timer1 as it is a shared prescaler.
	void MHT_TIMER2_FOC(void);										// Force Output Compare for Timer2.
	void MHT_Set_TIMER2_Value(unsigned char value);					// Setting the value of Timer2.
	unsigned char MHT_Get_TIMER2_Value(void);						// Getting the value of Timer2.
	void MHT_Set_TIMER2_Compare_Value(unsigned char value);			// Setting the value of Timer2 Compare Register.
	unsigned char MHT_Get_TIMER2_Compare_Value(void);				// Getting the value of Timer2 Compare Register
	void MHT_Clear_TIMER2_Overflow_Flag(void);						// Clear Timer2 Overflow Flag.
	void MHT_Clear_TIMER2_Output_Compare_Flag(void);				// Clear Timer2 Output Compare Flag.
	void MHT_Wait_TIMER2_Overflow_Flag_Set(void);					// Wait until Timer2 Overflow Flag is Set.
	unsigned char MHT_Is_TIMER2_Overflow_Flag_Set(void);			// Check if Timer2 Overflow flag is set. if set it will return 1 & if not set it will return 0.
	void MHT_Wait_TIMER2_Output_Compare_Flag_Set(void);					// Wait until Timer2 Output Compare Flag is Set.
	unsigned char MHT_Is_TIMER2_Output_Compare_Flag_Set(void);		// Check if Timer2 Output Compare flag is set. if set, it will return 1 & if not set, it will return 0.
	


	///////////////////////////////////////////////////////////////////Functions Macro/////////////////////////////////////////////////////////////////////////////////
	#define MHT_TIMER2_STOP()                           ({\
														   while ( (ASSR & (1 << TCR2UB)) != 0);   /* Wait here until TCCR2 is ready to be updated with a new value.*/\
														   TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));  /* Timer2 Stop.*/\
														})

	#define MHT_TIMER2_PRESCALER_SELECT(CS)             ({\
														   while ( (ASSR & (1 << TCR2UB)) != 0);   /* Wait here until TCCR2 is ready to be updated with a new value.*/\
														   TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));		/* Clear Clock Select bits.*/\
														   while ( (ASSR & (1 << TCR2UB)) != 0);   /* Wait here until TCCR2 is ready to be updated with a new value.*/\
	                                                       TCCR2 |= (CS << CS20);				   /* Select The needed Prescaler.*/\
														})											
	
	#define MHT_TIMER2_PRESCALER_RESET()				({ SFIOR |= (1 << PSR2); })				   // Prescaler Reset of Timer2.

	#define MHT_SET_TIMER2_VALUE(v)						({\
														   while ( (ASSR & (1 << TCN2UB)) != 0);   /* Wait here until TCNT2 is ready to be updated with a new value.*/\
														   TCNT2 = v;							   /* Setting the value of Timer2.*/\
														})
	
	#define MHT_GET_TIMER2_VALUE()						({\
														   while ( (ASSR & (1 << TCN2UB)) != 0);   /* Wait here until TCNT2 is ready to be updated with a new value.*/\
											               TCNT2;								   /* Getting the value of Timer2.*/\
														})						   

	#define MHT_SET_TIMER2_COMPARE_VALUE(v)				({\
														   while ( (ASSR & (1 << OCR2UB)) != 0);   /* Wait here until OCR2 is ready to be updated with a new value.*/\
														   OCR2 = v;							   /* Setting the value of Timer2 Compare Register.*/\
														})
	
	#define MHT_GET_TIMER2_COMPARE_VALUE()				({\
														   while ( (ASSR & (1 << OCR2UB)) != 0);   /* Wait here until OCR2 is ready to be updated with a new value.*/\ 
														   OCR2;								   /* Getting the value of Timer2 Compare Register.*/\
														})								           

	#define MHT_CLEAR_TIMER2_OVERFLOW_FLAG()			({ TIFR |= (1 << TOV2); })				   // Clear Timer2 Overflow Flag.
	#define MHT_CLEAR_TIMER2_OUTPUT_COMPARE_FLAG()		({ TIFR |= (1 << OCF2); })				   // Clear Timer2 Output Compare Flag.

	#define MHT_WAIT_TIMER2_OVERFLOW_FLAG_SET()			({ while( (TIFR & (1 << TOV2) ) == 0); })  // Wait until Timer2 Overflow Flag is Set.
	#define MHT_IS_TIMER2_OVERFLOW_FLAG_SET()			({ (TIFR & (1 << TOV2)) != 0); })		   // Check if Timer2 Overflow flag is set. if set it will return 1 & if not set it will return 0.

	#define MHT_WAIT_TIMER2_OUTPUT_COMPARE_FLAG_SET()	({ while( (TIFR & (1 << OCF2) ) == 0);})   // Wait until Timer2 Output compare Flag is Set.
	#define MHT_IS_TIMER2_OUTPUT_COMPARE_FLAG_SET()		({ (TIFR & (1 << OCF2)) != 0); })		   // Check if Timer2 Output compare flag is set. if set it will return 1 & if not set it will return 0.
	
		
#endif /* MHT_TIMER2_H_ */
