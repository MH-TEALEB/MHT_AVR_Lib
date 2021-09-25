/*
 * @file MHT_GPIO.c
 * @brief Implementation File for General Purpose Input Output(GPIO) driver.
 *
 * It includes MHT_GPIO.h header file and defines Functions that can be used by GPIO module.
 *
 * @date 04 Sep. 2021
 * @author MH_TEALEB
 */

#include "MHT_GPIO.h"	// Include MHT_GPIO Header file

// A function that Defines the direction of the port.
s8 MHT_GPIO_Port_Direction_Define(u8 port_name, u8 port_dir){
	// Define the Desired PORT Direction.
	if ( (port_dir == INPUT) ){		// Check if the desired port direction is Input. 
		port_dir = 0X00;	// Put zeros on port_dir argument to make direction as Input. 
	}else if ( (port_dir == OUTPUT) ){	// Check if the desired port direction is Output.
		port_dir = 0XFF;	// Put ones on port_dir argument to make direction as Output.
	}else{	// If anything else is send in port_dir argument.
		return ERROR;	// Return Error.
	}
	
	// Select the defined port and define its direction.
	switch(port_name){
		case 'A':	// If Port A is defined.
		case 'a':
			DDRA = port_dir; // Put the port A as the defined port direction
		break;
		
		case 'B':	// If port B is defined.
		case 'b':
			DDRB = port_dir;	// Put the port B as the defined port direction.
		break;
		
		case 'C':	// If port C is defined.
		case 'c':
			DDRC = port_dir;	// Put the port C as the defined port direction.
		break;
		
		case 'D':	// If port D is defined.
		case 'd':
			DDRD = port_dir;	// Put the port D as the defined port direction.
		break;
		
		default:	// If anything else is send.
			return ERROR;	// Return Error.
	}
	return NO_ERROR;	// Return no error.
}


// A function that Defines the direction of the pins in a specific port.
s8 MHT_GPIO_Pins_Direction_Define(u8 port_name, u8 pins_dir){
	// Select the defined port and define its pins direction.
	switch(port_name){
		case 'A':	// If Port A is defined.
		case 'a':
			DDRA = pins_dir; // Put the port A as the defined pins direction.
		break;
		
		case 'B':	// If port B is defined.
		case 'b':
			DDRB = pins_dir;	// Put the port B as the defined pins direction.
		break;
		
		case 'C':	// If port C is defined.
		case 'c':
			DDRC = pins_dir;	// Put the port C as the defined pins direction.
		break;
		
		case 'D':	// If port D is defined.
		case 'd':
			DDRD = pins_dir;	// Put the port D as the defined pins direction.
		break;
		
		default:	// If anything else is send.
			return ERROR;	// Return Error.
	}
	return NO_ERROR;	// Return no error.	
}


// A function that define a direction of a pin (INPUT(0) or OUTPUT(1)).
s8 MHT_GPIO_Pin_Direction_Define(u8 port_name, u8 pin_num, u8 pin_dir){
	// check if pin_num is not from 0 to 7, return error.
	if ( (pin_num < 0) || (pin_num > 7) ){
		return ERROR;	// Return Error.
	}
	
	// check if pin_dir is not INPUT(0) or OUTPUT(1), return error.
	if ( (pin_dir != 0) && (pin_dir != 1) ){
		return ERROR;	// Return Error.
	}
	
	// Select the port and write the value to it.
	switch(port_name){
		case 'A':	// If Port A is selected.
		case 'a':
			DDRA &= ~(1 << pin_num);			 // Clear the selected pin on port A.
			DDRA |=  (pin_dir << pin_num);		// Write the direction of the selected pin on port A.
		break;
		
		case 'B':	// If port B is selected.
		case 'b':
			DDRB &= ~(1 << pin_num);	         // Clear the selected pin on port B.
			DDRB |=  (pin_dir << pin_num) ;		// Write the direction of the selected pin on port B.
		break;
		
		case 'C':	// If port C is selected.
		case 'c':
			DDRC &= ~(1 << pin_num);			 // Clear the selected pin on port C.
			DDRC |=  (pin_dir << pin_num);		// Write the direction of the selected pin on port C.
		break;
		
		case 'D':	// If port D is selected.
		case 'd':
			DDRD &= ~(1 << pin_num);			 // Clear the selected pin on port D.
			DDRD |=  (pin_dir << pin_num);		// Write the direction of the selected pin on port D.
		break;
		
		default:	// If anything else is send.
		return ERROR;	// Return Error.
	}
	return NO_ERROR;
}


//A function that write a value(ZERO or ONE) to the port.
s8 MHT_GPIO_Port_Write_Value(u8 port_name, u8 port_value){
	// Generalize the port value.
	if ( (port_value == ZERO) ){		// Check if the desired port value is ZERO.
		port_value = 0X00;				// Put zeros on port_value.
	}else if ( (port_value == ONE) ){	// Check if the desired port value is ONE.
		port_value = 0XFF;				// Put ones on port_value.
	}else{								// If anything else is send in port_value argument.
		return ERROR;					// Return Error.
	}
	
	// Select the defined port and define its direction.
	switch(port_name){
		case 'A':				// If Port A is selected.
		case 'a':
			PORTA = port_value; // Put the desired value on port A.
		break;
		
		case 'B':				// If port B is selected.
		case 'b':
			PORTB = port_value;	// Put the desired value on port B.
		break;
		
		case 'C':				// If port C is selected.
		case 'c':
			PORTC = port_value;	// Put the desired value on port C.
		break;
		
		case 'D':				// If port D is selected.
		case 'd':
			PORTD = port_value;	// Put the desired value on port D.
		break;
		
		default:				// If anything else is send.
			return ERROR;		// Return Error.
	}

	return NO_ERROR;	// Return No Error.
}


//A function that write a value to the pins in a specific port.
s8 MHT_GPIO_Pins_Write_Value(u8 port_name, u8 pins_value){
	// Select the port and write the value to it.
	switch(port_name){
		case 'A':	// If Port A is selected.
		case 'a':
			PORTA = pins_value;	// Write the value of the pins in port A.
		break;
		
		case 'B':	// If port B is selected.
		case 'b':
			PORTB = pins_value;	// Write the value of the pins in port B.
		break;
		
		case 'C':	// If port C is selected.
		case 'c':
			PORTC = pins_value;	// Write the value of the pins in port C.
		break;
		
		case 'D':	// If port D is selected.
		case 'd':
			PORTD = pins_value;	// Write the value of the pins in port D.
		break;
		
		default:	// If anything else is send.
		return ERROR;	// Return Error.
	}
	return NO_ERROR;	// Return no error.
}


//A function that write a value(0 or 1) to specific pin in a port.
s8 MHT_GPIO_Pin_Write_Value(u8 port_name, u8 pin_num, u8 pin_value){
	// check if pin_num is not from 0 to 7, return error.
	if ( (pin_num < 0) || (pin_num > 7) ){
		return ERROR;	// Return Error.
	}
	
	// check if pin_value is not 0 or 1, return error.
	if ( (pin_value != 0) && (pin_value != 1) ){
		return ERROR;	// Return Error.
	}
	
	// Select the port and write the value to it.
	switch(port_name){
		case 'A':	// If Port A is selected.
		case 'a':
			PORTA &= ~(1 << pin_num);			 // Clear the selected pin on port A.
			PORTA |=  (pin_value << pin_num);	 // Write the value on the selected pin on port A.
		break;
		
		case 'B':	// If port B is selected.
		case 'b':
			PORTB &= ~(1 << pin_num);	         // Clear the selected pin on port B.
			PORTB |=  (pin_value << pin_num) ;	 // Write the value on the selected pin on port B. 
		break;
		
		case 'C':	// If port C is selected.
		case 'c':
			PORTC &= ~(1 << pin_num);			 // Clear the selected pin on port C.
			PORTC |=  (pin_value << pin_num);	 // Write the value on the selected pin on port C.
		break;
		
		case 'D':	// If port D is selected.
		case 'd':
			PORTD &= ~(1 << pin_num);			 // Clear the selected pin on port D.
			PORTD |=  (pin_value << pin_num);	 // Write the value on the selected pin on port D.
		break;
		
		default:	// If anything else is send.
		return ERROR;	// Return Error.
	} 
	return NO_ERROR;	//  Return No Error.
 }


//A function that read a value of the port. 
 s8 MHT_GPIO_Port_Read_Value(u8 port_name){
	 // Select the port name and return the read value.
	 switch(port_name){
		 case 'A':		// If Port A is Selected.
		 case 'a':
			return PINA;	// Return The Value of Port A.
		break;
		case 'B':		// If PORT B is Selected.		
		case 'b':
			return PINB;	// Return The Value of Port B.
		break;
		case 'C':		// If Port C is Selected.
		case 'c':
			return PINC;	// Return The Value of Port C.
		break;
		case 'D':		// If Port C is Selected.
		case 'd':
			return PIND;	// Return The VAlue of Port D.
		break;
		default:
			return ERROR;	// Return Error.
	 }
 }


// A function that read a value(0 or 1) of the pin.
s8 MHT_GPIO_Pin_Read_Value(u8 port_name, u8 pin_num){
	// Select the port name and return the read value.
	switch(port_name){
		case 'A':		// If Port A is Selected.
		case 'a':
			return ( (PINA >> pin_num) & 0X01 );	// Return The Value of The Selected Pin in Port A.
		break;
		case 'B':		// If PORT B is Selected.
		case 'b':
			return ( (PINB >> pin_num) & 0X01 );	// Return The Value of The Selected Pin in Port B.
		break;
		case 'C':		// If Port C is Selected.
		case 'c':
			return ( (PINC >> pin_num) & 0X01 );	// Return The Value of The Selected Pin in Port C.
		break;
		case 'D':		// If Port C is Selected.
		case 'd':
			return ( (PIND >> pin_num) & 0X01 );	// Return The VAlue of The Selected Pin in Port D.
		break;
		default:
			return ERROR;	// Return Error.
	}
}