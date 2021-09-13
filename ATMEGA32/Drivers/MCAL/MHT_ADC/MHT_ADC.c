/*
 * MHT_ADC.c
 *
 * Created: 29-Feb-20 2:15:53 PM
 *  Author: MH_TEALEB
 */ 

// Include ADC Header File.
#include "MHT_ADC.h"


// Function Definition to Initialize ADC.

void MHT_ADC_Init(unsigned char adc_en, unsigned char channel, unsigned char vref, unsigned char adj_res, unsigned char adc_sc, unsigned char adc_ien, unsigned char adc_aten, unsigned char adc_ats, unsigned char adc_presc)
{
	// Select Analog Input Channel & Adjust Result and The Reference Voltage.
	ADMUX = 0x00;	// Clear any initialization before.
	ADMUX |= (channel << MUX0) | (adj_res << ADLAR) | (vref << REFS0);
	 
	// Enable or Disable ADC & Interrupt & Auto Trigger and Select ADC Prescaler.
	ADCSRA = 0x00;	// Clear nay initialization before.
	ADCSRA |= (adc_en << ADEN) | (adc_aten << ADATE) | (adc_presc << ADPS0) | (adc_ien << ADIE);
	SREG |= (adc_ien << 7);		// if ADC_Interrupt is Enabled, Global Interrupt will be Enable, if ADC_Interrupt Disabled, Global Interrupt will be the same as it was before.
	
	// Select Auto Trigger Source if Enabled before.
	SFIOR &= 0x1F;	// Clear any Initialization before for Trigger Source.
	SFIOR |= (adc_ats << ADTS0);
	
	// Start or Stop Conversion.
	ADCSRA |= (adc_sc << ADSC);
}

// Function Definition to Start Conversion of ADC.
void MHT_ADC_Start_Conversion(void)
{
	ADCSRA |= (1 << ADSC);
}

// Function Definition to Select ADC Channel.
void MHT_ADC_Select_Channel(unsigned char channel)
{
	ADMUX &= ~ 0X1F;	// Clear Selected channel bits.
	ADMUX |= (channel << MUX0);	// Select the desired ADC Channel.
}

// Function Definition to select ADC Reference Voltage.
void MHT_ADC_Select_Reference_Voltage(unsigned char vref)
{
	ADMUX &= ~( (1 << REFS0) | (1 << REFS1));	// Clear Reference Voltage Selection bits.
	ADMUX |= (vref << REFS0);	// Select The Desired Reference Voltage. 
}

// Function Definition to Select Left OR Right ADC Adjust Result.
void MHT_ADC_Adjust_Result(unsigned char adc_adj)
{
	ADMUX &= ~(1 << ADLAR);	// Clear ADC Adjust Result bit.
	ADMUX |= (adc_adj << ADLAR);	// Select The Desired ADC Adjust Result (Left OR Right).
}

// Function Definition to Select ADC Auto Trigger Source.
void MHT_ADC_Select_Auto_Trigger_Source(unsigned char adc_ats)
{
	SFIOR &= ~( (1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2) );	// Clear ADC Auto Trigger Source bits.
	SFIOR |= (adc_ats << ADTS0);	// Select The Desired ADC Auto Trigger Source.
}

// Function Definition to Select ADC Prescaler Division Factor
void MHT_ADC_Select_Prescaler(unsigned char adc_presc)
{
	ADCSRA &= ~( (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) );	// Clear ADC Prescaler bits.
	ADCSRA |= (adc_presc << ADPS0);	// Select The Desired ADC Prescaler.
}

// Function Definition to return 1 if Conversion is finished, and return 0 if not finished yet. 
unsigned char MHT_ADC_Check_Conversion_finished(void)
{
	if ( (ADCSRA & (1 << ADIF)) == 0)
	{
		return 0;
	}
	else
	{
		return 1;	
		
	}
}

// Function Definition to Wait until ADC Conversion is Finished.
void MHT_ADC_Wait_Conversion_Finished(void)
{
	while ( (ADCSRA & (1 << ADIF)) == 0);
}	

// Function Definition to Clear ADC Complete Conversion Interrupt Flag.
void MHT_ADC_Clear_Interrupt_Flag(void)
{
	ADCSRA |= (1 << ADIF);
}	

// Function Definition to Enable or Disable ADC Interrupt Conversion Complete.
void MHT_ADC_Interrupt_Conversion_Complete(unsigned char adc_ien)
{
	ADCSRA &= ~(1 << ADIE);	// Clear ADC Interrupt Enable bit.
	ADCSRA |= (adc_ien << ADIE);	// Enable or Disable ADC Interrupt Conversion Complete.
	SREG |= (adc_ien << 7);		// Enable or not Global Interrupt.
}

// Function Definition to Read ADC Low, High or Both Registers.
unsigned short MHT_ADC_Read_Data(unsigned char adj_res,	unsigned char adc_reg)
{
	ADCSRA &= ~(1 << ADLAR);	// Clear Adjust Result bit.
	ADCSRA |= (adj_res << ADLAR);	// Select The Desire Adjusted Result.
	
	switch (adc_reg)
	{
		case 0:
			return ADCL;
			break;
		case 1:
			return ADCH;
			break;
		case 2:		// If Both" The ALL data" is Selected, arrange the data then return it.
			if (adj_res == RIGHT_ADJUST)	// If Selected Right Adjust.
			{  
				return ( ADCL | (ADCH << 8) );	// Arranging data in the right way and return it.
			}
			else	// If Selected Left Adjust.
			{
				return ( (ADCL << 6) | (ADCH << 2) ) ;	// Arranging data in the right way and return it.
			}		 
			break;
		default:
			return ADC;
			break;	
	}
}



/*
// Interrupt Service Routine for ADC Conversion Complete.
ISR(ADC_vect)
{
	
}
*/