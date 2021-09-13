/*
 * MHT_ADC.h
 *
 * Created: 29-Feb-20 2:16:30 PM
 *  Author: MH_TEALEB
 */ 


#ifndef MHT_ADC_H_
#define MHT_ADC_H_


	#ifndef F_CPU
		#define F_CPU 1000000UL     // System Clock Frequency = 1MHz.
	#endif

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	
	// ADC Enable (adc_en)
	#define ADC_DISABLE	0
	#define ADC_ENABLE	1
	
	// Select Analog Input Channel(channel)
	//Single_Ended Input Signal
	#define ADC0_SingleEnded	0
	#define ADC1_SingleEnded	1
	#define ADC2_SingleEnded	2
	#define ADC3_SingleEnded	3
	#define ADC4_SingleEnded	4
	#define ADC5_SingleEnded	5
	#define ADC6_SingleEnded	6
	#define ADC7_SingleEnded	7
	// Differential Input Signal with gain.
	#define	ADC0_ADC0_10X	8
	#define	ADC1_ADC0_10X	9
	#define	ADC0_ADC0_200X	10
	#define	ADC1_ADC0_200X	11
	#define	ADC2_ADC2_10X	12
	#define	ADC3_ADC2_10X	13
	#define	ADC2_ADC2_200X	14
	#define	ADC3_ADC2_200X	15
	#define	ADC0_ADC1_1X	16
	#define	ADC1_ADC1_1X	17
	#define	ADC2_ADC1_1X	18
	#define	ADC3_ADC1_1X	19
	#define	ADC4_ADC1_1X	20
	#define	ADC5_ADC1_1X	21
	#define	ADC6_ADC1_1X	22
	#define	ADC7_ADC1_1X	23
	#define	ADC0_ADC2_1X	24
	#define	ADC1_ADC2_1X	25
	#define	ADC2_ADC2_1X	26
	#define	ADC3_ADC2_1X	27
	#define	ADC4_ADC2_1X	28
	#define	ADC5_ADC2_1X	29
	#define	VBG_SingleEnded	30
	#define	GND_SingleEnded	31
	
	// Reference Voltage Selection(vref).
	#define AREF			0
	#define AVCC			1
	#define INTERNAL_VREF	3
	
	// Left or Right Adjust Result(adj_res)
	#define RIGHT_ADJUST	0
	#define LEFT_ADJUST		1
	
	// ADC Start of Conversion(adc_sc)
	#define ADC_STOP_CONVERSION		0
	#define ADC_START_CONVERSION	1
	
	// ADC Interrupt Enable(adc_ien)
	#define ADC_INTERRUPT_DISABLE	0
	#define ADC_INTERRUPT_ENABLE	1
	
	// ADC Auto Trigger (adc_aten)
	#define ADC_AUTO_TRIGGER_DISABLE	0
	#define ADC_AUTO_TRIGGER_ENABLE		1
	
	// ADC Auto Trigger Source Selection(adc_ats)
	#define ADC_TRIGGER_SOURCE_DISABLE	0
	#define FREE_RUNN					0
	#define ANALOG_COMP					1
	#define EXT_INTRPT_0				2
	#define TIMER0_COMP_MATCH			3
	#define TIMER0_OVF					4
	#define TIMER1_COMP_MATCH_B			5
	#define TIMER1_OVF					6
	#define TIMER1_CAPT					7
	
	// ADC Prescaler Division Factor Select(adc_presc).
	#define  ADC_PRESC2		0
	#define  ADC_PRESC4		2
	#define  ADC_PRESC8		3
	#define  ADC_PRESC16	4
	#define  ADC_PRESC32	5
	#define  ADC_PRESC64	6
	#define  ADC_PRESC128	7
	
	// ADC Reading Registers(adc_reg).
	#define ADC_LOW		0
	#define ADC_HIGH	1
	#define ADC_BOTH	2
	


///////////////////////////////////////////////////////////////////// ADC_Functions_Prototype. ////////////////////////////////////////////////////////////////////////

void MHT_ADC_Init(unsigned char adc_en, unsigned char channel, unsigned char vref, unsigned char adj_res, unsigned char adc_sc, unsigned char adc_ien, unsigned char adc_aten, unsigned char adc_ats, unsigned char adc_presc);	// Initialize ADC.
void MHT_ADC_Start_Conversion(void);								// ADC start Conversion
void MHT_ADC_Select_Channel(unsigned char channel);					// Select ADC channel.
void MHT_ADC_Select_Reference_Voltage(unsigned char vref);			// Select ADC Reference Voltage.
void MHT_ADC_Adjust_Result(unsigned char adc_adj);					// Select ADC Left OR Right Adjust Result.
void MHT_ADC_Select_Auto_Trigger_Source(unsigned char adc_ats);		// Select ADC Auto Trigger Source.
void MHT_ADC_Select_Prescaler(unsigned char adc_presc);				// Select ADC Prescaler Division Factor.
unsigned char MHT_ADC_Check_Conversion_finished(void);				//	It will return 1 if Conversion is finished, and it will return 0 if not finished yet.
void MHT_ADC_Wait_Conversion_Finished(void);						// Wait until ADC Conversion is Finished.
void MHT_ADC_Clear_Interrupt_Flag(void);							// Clear Interrupt Flag.
void MHT_ADC_Interrupt_Conversion_Complete(unsigned char adc_ien);	// Enable of Disable ADC Interrupt Conversion Complete.
unsigned short MHT_ADC_Read_Data(unsigned char adj_res,	unsigned char adc_reg);		// Read ADC Low , High or Both Registers.




/////////////////////////////////////////////////////////////////// ADC_Functions_Macros. /////////////////////////////////////////////////////////////////////////////
#define MHT_ADC_ENABLE(void)						({ ADCSRA |= (1 << ADEN); })	// Enable ADC.
#define MHT_ADC_DISABLE(void)						({ ADCSRA &= ~(1 << ADEN); })	// Disable ADC.
	
#define MHT_ADC_START_CONVERSION(void)				({ ADCSRA |= (1 << ADSC); })	// Start of ADC Conversion.
#define MHT_ADC_STOP_CONVERSION(void)				({ ADCSRA &= ~(1 << ADSC); })	// Stop of ADC Conversion.

#define MHT_ADC_AUTO_TRIGGER_ENABLE(void)			({ ADCSRA |= (1  << ADATE); })	// Enable ADC Auto Trigger.
#define MHT_ADC_AUTO_TRIGGER_DISABLE(void)			({ ADCSRA &= ~(1 << ADATE); })	// Disable ADC Auto Trigger.

#define MHT_ADC_CHECK__CONVERSION_COMPLETED(void)	({ ADCSRA & (1 << ADIF); })		// It will be true if Conversion is finished, and will be false if not finished yet.
#define MHT_ADC_WAIT_CONVERSION_COMPLETED(void)		({ while( (ADCSRA & (1 << ADIF)) == 0 ); })	// Wait here until conversion is finished.

#define MHT_ADC_ENABLE_INTERRUPT(void)				({ ADCSRA |= (1 << ADIE); })	// Enable ADC Interrupt Conversion Complete.
#define MHT_ADC_DISABLE_INTERRUPT(void)				({ ADCSRA &= ~(1 << ADIE); })	// Disable ADC Interrupt Conversion Complete.

#define MHT_ADC_CLEAR_INTERRUPT_FLAG(void)			({ ADCSRA |= (1 << ADIF); })	// Clear ADC Complete Conversion Interrupt Flag.
	
#define MHT_ADC_READ_DATA_HIGH(void)				({ ADCH; })						// Read ADC_HIGH.
#define MHT_ADC_READ_DATA_LOW(void)					({ ADCL; })						// Read ADC_LOW.		
#define MHT_ADC_READ_DATA(void)						({ ADC;  })						// Read ADC.


#endif /* MHT_ADC_H_ */