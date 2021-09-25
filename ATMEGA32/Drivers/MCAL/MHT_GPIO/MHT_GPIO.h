/*
 * @file MHT_GPIO.h
 * @brief Header File for General Purpose Input Output(GPIO) driver.
 *
 * It includes other needed header files and defines Macros and Function Macros, and making Functions Prototype
 * that can be used for GPIO implementation and for applications that uses GPIO module.
 *
 * @date 04 Sep. 2021
 * @author MH_TEALEB
 */

#ifndef MHT_GPIO_H_
#define MHT_GPIO_H_

/**************************************************************************************************************************************
******************************************************** Includes *********************************************************************
**************************************************************************************************************************************/
#include <avr/io.h>
#include "MHT_ATMEGA32_StdTypes.h"


/**************************************************************************************************************************************
******************************************************** Macros ***********************************************************************
**************************************************************************************************************************************/
// Define Error(-1) and No_Error(0).
#define NO_ERROR	0
#define ERROR		-1

// Define Input(0) and Output(1).
#define INPUT	0
#define OUTPUT	1

// Define Zero(0) and One(1).
#define ZERO	0
#define ONE		1

// Define Ports to use when calling macro function(to replace PORT_NAME).
#define PA	PORTA
#define PB	PORTB
#define PC	PORTC
#define PD	PORTD

// Define Direction of Ports to use when calling macro function(to replace DIR_PORT_NAME).
#define DPA	DDRA
#define DPB	DDRB
#define DPC	DDRC
#define DPD	DDRD

// Define Ports to use in Read Macro Functions(to replace READ_PORT_NAME).
#define RPA	PINA
#define RPB	PINB
#define RPC	PINC
#define RPD	PIND


/**************************************************************************************************************************************
******************************************************** Function Prototypes **********************************************************
**************************************************************************************************************************************/
/**
 * @brief A function that Defines the direction of the port.
 *
 * This function is used to define direction to all port as input or as output, 
 * so the all pins in the port will be input or the all pins in the port will be output.
 *
 * @param unsigned character port_name as the name of the port you want to define its direction,
 *  (It must be as: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 * @param unsigned character port_dir as the desired direction of the port. (It must be as: INPUT or OUTPUT).
 *
 * @return signed character to represent if there is error or no error.
 */
s8 MHT_GPIO_Port_Direction_Define(u8 port_name, u8 port_dir);


/**
 * @brief A function that Defines the direction of the pins in a specific port.
 *
 * This function is used to define each pin in the port to be input or output,
 * but you have to write all pins. There is no masking. 
 *
 * @param unsigned character port_name as the name of the port that contains the pins which needed to be chosen,
 *  (It must be from: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 * @param unsigned character pins_dir as the desired direction of the pins.
 *	(It must be between (0 and 255) or (0x00 and 0xFF) or (0b00000000 and 0bFFFFFFFF)).
 *
 * @return signed character to represent if error happened(return -1) if not(return 0).
 */
s8 MHT_GPIO_Pins_Direction_Define(u8 port_name, u8 pins_dir);


/** 
 * @brief A function that define a direction of a pin (INPUT(0) or OUTPUT(1)).
 *
 * This function is used to define direction of just one pin as input or as output at a time.
 * All other pins are masked and will not change. 
 *
 * @param unsigned character port_name as the name of the port that contains the pin which needed to be defined,
 *  (It must be from: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 * @param unsigned character pin_num as the number of the pin (It must be from 0 to 7).
 * @param unsigned char pin_dir as the desired direction of the pins of the port (It must be INPUT(0) or OUTPUT(1)).
 *
 * @return signed character to represent if error happened(return -1) if not(return 0).
 */
s8 MHT_GPIO_Pin_Direction_Define(u8 port_name, u8 pin_num, u8 pin_dir);


/**
 * @brief A function that write a value(ZERO or ONE) to the port.
 *
 * This function is used to write to the all port ones or zeros at a time,
 * so all pins in the port will be changed to one or all pins in the port will be changed to zero.
 *
 * @param unsigned character port_name as the name of the port that you want to write on it,
 *  (It must be from: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 * @param unsigned character port_value as the value wanted to be written to this port. (It must be ZERO or ONE).
 *
 * @return signed character to represent if error happened(return -1) if not(return 0).
 */
s8 MHT_GPIO_Port_Write_Value(u8 port_name, u8 port_value);

/**
 * @brief A function that write a value to the pins in a specific port.
 *
 * This function is used to write a value to the pins in the port as ones and zeros,
 * so each pin can be one or zero and you have to write to all pins at a time. There is no masking. 
 *
 * @param unsigned character port_name as the name of the port which needed to be written on it,
 *  (It must be from: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 * @param unsigned character port_value as the value wanted to be written to this port.
 *	(It must be between (0 and 255) or (0x00 and 0xFF) or (0b00000000 and 0bFFFFFFFF)).
 *
 * @return signed character to represent if error happened(return -1) if not(return 0).
 */
s8 MHT_GPIO_Pins_Write_Value(u8 port_name, u8 pins_value);

/**
 * @brief A function that write a value(0 or 1) to specific pin in a port.
 *
 * This function is used to write to just one pin at a time as one or zero,
 * The other pins are masked at each time.
 *
 * @param unsigned character port_name as the name of the port that contain the pin which needed to be written,
 *  (It must be from: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 * @param unsigned character pin_num as the number of the pin (It must be from 0 to 7).
 * @param unsigned character pin_value as the value of the pin (It must be 0 or 1).
 *
 * @return signed character to represent if error happened(return -1) if not(return 0).
 */
s8 MHT_GPIO_Pin_Write_Value(u8 port_name, u8 pin_num, u8 pin_value);

/**
 * @brief A function that read a value of the port.
 *
 * This function is used to read a value of the port.
 *
 * @param unsigned character port_name as the name of the port that you want to read the value from,
 *  (It must be from: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 *
 * @return signed character to represent if error happened(return -1) or to return the value.
 */
s8 MHT_GPIO_Port_Read_Value(u8 port_name);

/**
 * @brief A function that read a value(0 or 1) of the pin.
 *
 * This function is used to read a value(0 or 1) of the pin.
 *
 * @param unsigned character port_name as the name of the port that you want to read the value from,
 *  (It must be from: 'A' or 'a' or 'B' or 'b' or 'C' or 'c' or 'D' or 'd').
 * @param unsigned character pin_num as the number of the pin (It must be from 0 to 7).
 *
 * @return signed character to represent if error happened(return -1) or to return the value of the pin (0 or 1).
 */
s8 MHT_GPIO_Pin_Read_Value(u8 port_name, u8 pin_num);


/**************************************************************************************************************************************
******************************************************** Function Macros **************************************************************
**************************************************************************************************************************************/

/************************************** For General use(send the desired value from 0 to 255) ****************************************/
// To define direction for pins in port. (DIR_PORT_NAME can be DPA or DPB or DPC or DPD).
#define MHT_GPIO_PINS_DIRECTION_DEFINE(DIR_PORT_NAME, pins_dir)	(DIR_PORT_NAME = pins_dir)
#define MHT_GPIO_PINSA_DIRECTION_DEFINE(pins_dir)	(DDRA = pins_dir)
#define MHT_GPIO_PINSB_DIRECTION_DEFINE(pins_dir)	(DDRB = pins_dir)
#define MHT_GPIO_PINSC_DIRECTION_DEFINE(pins_dir)	(DDRC = pins_dir)
#define MHT_GPIO_PINSD_DIRECTION_DEFINE(pins_dir)	(DDRD = pins_dir)
// To Output Value to the pins in port.	(PORT_NAME can be PA or PB or PC or PD)
#define MHT_GPIO_PINS_OUTPUT_VALUE(PORT_NAME, value)	(PORT_NAME = value)
#define MHT_GPIO_PINSA_OUTPUT_VALUE(value)	(PORTA = value)
#define MHT_GPIO_PINSB_OUTPUT_VALUE(value)	(PORTB = value)
#define MHT_GPIO_PINSC_OUTPUT_VALUE(value)	(PORTC = value)
#define MHT_GPIO_PINSD_OUTPUT_VALUE(value)	(PORTD = value)
// To Read Value of Pins in port. (READ_PORT_NAME can be RPA or RPB or RPC or RPD)
#define MHT_GPIO_PINS_READ_VALUE(READ_PORT_NAME) (READ_PORT_NAME)
#define MHT_GPIO_PINSA_READ_VALUE()	(PINA)
#define MHT_GPIO_PINSB_READ_VALUE()	(PINB)
#define MHT_GPIO_PINSC_READ_VALUE()	(PINC)
#define MHT_GPIO_PINSD_READ_VALUE()	(PIND)

/***************************************************** For Input use *****************************************************************/
// Define Port Direction as Input. (DIR_PORT_NAME can be DPA or DPB or DPC or DPD).
#define MHT_GPIO_PORT_DIRECTION_INPUT(DIR_PORT_NAME)	(DIR_PORT_NAME = 0X00)
#define MHT_GPIO_PORTA_DIRECTION_INPUT()	(DDRA = 0X00)
#define MHT_GPIO_PORTB_DIRECTION_INPUT()	(DDRB = 0X00)
#define MHT_GPIO_PORTC_DIRECTION_INPUT()	(DDRC = 0X00)
#define MHT_GPIO_PORTD_DIRECTION_INPUT()	(DDRD = 0X00)
// Define pin Direction as Input. (DIR_PORT_NAME can be DPA or DPB or DPC or DPD).
#define MHT_GPIO_PIN_DIRECTION_INPUT(DIR_PORT_NAME, pin_num)	(DIR_PORT_NAME &= ~(1 << pin_num) )
// To Read Value of pin in port. (READ_PORT_NAME can be RPA or RPB or RPC or RPD).
#define MHT_GPIO_PIN_READ_VALUE(READ_PORT_NAME, pin_num)	( (READ_PORT_NAME >> pin_num) & 0X01)

/***************************************************** For Output use ****************************************************************/
// Define Port Direction as Output. (DIR_PORT_NAME can be DPA or DPB or DPC or DPD).
#define MHT_GPIO_PORT_DIRECTION_OUTPUT(DIR_PORT_NAME)	(DIR_PORT_NAME = 0XFF)
#define MHT_GPIO_PORTA_DIRECTION_OUTPUT()	(DDRA = 0XFF)
#define MHT_GPIO_PORTB_DIRECTION_OUTPUT()	(DDRB = 0XFF)
#define MHT_GPIO_PORTC_DIRECTION_OUTPUT()	(DDRC = 0XFF)
#define MHT_GPIO_PORTD_DIRECTION_OUTPUT()	(DDRD = 0XFF)
// Define pin Direction as Output. (DIR_PORT_NAME can be DPA or DPB or DPC or DPD).
#define MHT_GPIO_PIN_DIRECTION_OUTPUT(DIR_PORT_NAME, pin_num)	(DIR_PORT_NAME |= (1 << pin_num) )
// To Output Value to Port. (PORT_NAME can be PA or PB or PC or PD).
#define MHT_GPIO_PORT_OUTPUT_VALUE(PORT_NAME, value)	(PORT_NAME = value)
#define MHT_GPIO_PORTA_OUTPUT_VALUE(value)	(PORTA = value)
#define MHT_GPIO_PORTB_OUTPUT_VALUE(value)	(PORTB = value)
#define MHT_GPIO_PORTC_OUTPUT_VALUE(value)	(PORTC = value)
#define MHT_GPIO_PORTD_OUTPUT_VALUE(value)	(PORTD = value)
// To Output 1 to the port. (PORT_NAME can be PA or PB or PC or PD).
#define MHT_GPIO_PORT_OUTPUT_ONE(PORT_NAME)	(PORT_NAME = 0XFF)
#define MHT_GPIO_PORTA_OUTPUT_ONE()	(PORTA = 0XFF)
#define MHT_GPIO_PORTB_OUTPUT_ONE()	(PORTB = 0XFF)
#define MHT_GPIO_PORTC_OUTPUT_ONE()	(PORTC = 0XFF)
#define MHT_GPIO_PORTD_OUTPUT_ONE()	(PORTD = 0XFF)
// To Output 1 to pin. (PORT_NAME can be PA or PB or PC or PD).
#define MHT_GPIO_PIN_OUTPUT_ONE(PORT_NAME, pin_num)	( PORT_NAME |= (1 << pin_num) )
// To Output 0 to the port. (PORT_NAME can be PA or PB or PC or PD).
#define MHT_GPIO_PORT_OUTPUT_ZERO(PORT_NAME)	(PORT_NAME = 0X00)
#define MHT_GPIO_PORTA_OUTPUT_ZERO()	(PORTA = 0X00)
#define MHT_GPIO_PORTB_OUTPUT_ZERO()	(PORTB = 0X00)
#define MHT_GPIO_PORTC_OUTPUT_ZERO()	(PORTC = 0X00)
#define MHT_GPIO_PORTD_OUTPUT_ZERO()	(PORTD = 0X00)
// To Output 0 to pin. (PORT_NAME can be PA or PB or PC or PD).
#define MHT_GPIO_PIN_OUTPUT_ZERO(PORT_NAME, pin_num)	( PORT_NAME &= ~(1 << pin_num) )

/*************************************************************** For Toggle use ******************************************************/
// To Toggle Port Direction. (DIR_PORT_NAME can be DPA or DPB or DPC or DPD).
#define MHT_GPIO_PORT_DIRECTION_TOGGLE(DIR_PORT_NAME)	(DIR_PORT_NAME ^= 0XFF)
#define MHT_GPIO_PORTA_DIRECTION_TOGGLE()	(DDRA ^= 0XFF)
#define MHT_GPIO_PORTB_DIRECTION_TOGGLE()	(DDRB ^= 0XFF)
#define MHT_GPIO_PORTC_DIRECTION_TOGGLE()	(DDRC ^= 0XFF)
#define MHT_GPIO_PORTD_DIRECTION_TOGGLE()	(DDRD ^= 0XFF)
// To Toggle Pin Direction. (DIR_PORT_NAME can be DPA or DPB or DPC or DPD).
#define MHT_GPIO_PIN_DIRECTION_TOGGLE(DIR_PORT_NAME, pin_num)	(DIR_PORT_NAME ^= (1 << pin_num) )
// To Toggle the port. (PORT_NAME can be PA or PB or PC or PD).
#define MHT_GPIO_PORT_OUTPUT_TOGGLE(PORT_NAME)	(PORT_NAME ^= 0XFF)
#define MHT_GPIO_PORTA_OUTPUT_TOGGLE()	(PORTA ^= 0XFF)
#define MHT_GPIO_PORTB_OUTPUT_TOGGLE()	(PORTB ^= 0XFF)
#define MHT_GPIO_PORTC_OUTPUT_TOGGLE()	(PORTC ^= 0XFF)
#define MHT_GPIO_PORTD_OUTPUT_TOGGLE()	(PORTD ^= 0XFF)
// To Toggle value of pin in a port. (PORT_NAME can be PA or PB or PC or PD).
#define MHT_GPIO_PIN_OUTPUT_TOGGLE(PORT_NAME, pin_num)	( PORT_NAME ^= (1 << pin_num) )

#endif // END of MHT_GPIO_H_