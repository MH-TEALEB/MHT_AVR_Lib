/*
 * @Description Measure Positive and Negative Temperature, and display the measured temperature value on LCD.
 *
 * @Date 25-Nov-18 1:59:43 PM
 * @Author MH_TEALEB
 */ 

#include "MHT_LCD.h"
#include "MHT_ADC.h"

#define Vref 2.56
#define Num_of_Steps 1024
#define V_PER_C 0.01		// 10mV for each Degree.

int main(void)
{
	unsigned short Data1, Data2; 
	signed short Temp;
	float Vout1, Vout2;
	
	DDRA &= ~(1 << PA0) & ~(1 << PA1) ;	// make direction of ADC0(PA0) and ADC1(PA1) pins as input 
	
	// Initialize LCD
    MHT_LCD_Init();
	
	// Enable ADC module, Channel = ADC0 single-Ended Input, Vref = 2.56V internal, Right Adjusted, Using Polling, Single Conversion Mode without Auto Trigger, Division Factor = 8.
	MHT_ADC_Init(ADC_ENABLE, ADC0_SingleEnded, INTERNAL_VREF, RIGHT_ADJUST, ADC_START_CONVERSION, ADC_INTERRUPT_DISABLE, ADC_AUTO_TRIGGER_DISABLE, ADC_TRIGGER_SOURCE_DISABLE, ADC_PRESC8);
	
	while (1) 
    {
		//***************************************************** Read Data from channel 0 ( ADC0 ) ******************************************************************.
		MHT_ADC_Select_Channel(ADC0_SingleEnded);	// Select channel ADC0 Single Ended Input.
		MHT_ADC_START_CONVERSION();					// Start of Conversion
		MHT_ADC_WAIT_CONVERSION_COMPLETED();		// Wait here until conversion completed.
		MHT_ADC_CLEAR_INTERRUPT_FLAG();				// Clear Interrupt Flag.
		
		Data1 = MHT_ADC_READ_DATA();				// Read The data from this channel.
		Vout1 = (Data1 * Vref) / (Num_of_Steps);	// Calculate the corresponds Volt for the Read data from this channel.
		//***************************************************** Read data from channel 1 ( ADC1 ) *******************************************************************.
		MHT_ADC_Select_Channel(ADC1_SingleEnded);	// Select channel ADC1 Single Ended Input.
		MHT_ADC_START_CONVERSION();					// Start of Conversion
		MHT_ADC_WAIT_CONVERSION_COMPLETED();		// Wait here until conversion completed.
		MHT_ADC_CLEAR_INTERRUPT_FLAG();				// Clear Interrupt Flag.
		
		Data2 = MHT_ADC_READ_DATA();				// Read The data from this channel.
		Vout2 = (Data2 * Vref) / (Num_of_Steps);	// Calculate the corresponds Volt for the Read data from this channel.
		
		//***************************************************** Display Temperature on LCD *******************************************.
		MHT_LCD_Send_Command(0x01);			// Clear LCD
		MHT_LCD_Goto_Location(1,1);			// Go to the First position on LCD.
		MHT_LCD_Send_String("Temp = ");		// Write (Temp = ) on LCD.
						
		Temp = (Vout1 - Vout2) / V_PER_C;	// Calculate The Temperature Value.
		                                    // using Formula: (Volt = Temp * step_volt_degree"Volt_for_each_degree").
											
		MHT_LCD_Send_IntegerNumber(Temp,3);	// Display the Temperature on LCD
		MHT_LCD_Send_String(" C");			// Put degree sign after the temperature value.
		
		_delay_ms(500);						// make delay to make the displayed data in LCD not blinking because of speed 
    }
	return 0;
}

