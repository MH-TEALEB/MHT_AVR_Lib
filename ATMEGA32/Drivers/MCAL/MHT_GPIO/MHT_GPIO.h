/*
 * @file MHT_GPIO.h
 * @brief Header File for General Purpose Input Output(GPIO) driver.
 *
 * It includes other needed header files and defines Macros and Function Macros, and making Functions Prototype
 * that can be used for GPIO implementation and for applications that uses GPIO module.
 *
 * @date 22 February 2020
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

// Define The returned of Error, no_errors and if need action in next byte.
#define ERROR	-1
#define NO_ERROR	0
#define NEED_ACTION_NEXT	1

/**************************************************************************************************************************************
******************************************************** Function Prototypes **********************************************************
**************************************************************************************************************************************/
/**
 * @brief A function that.......
 *
 * It is the function that..........
 *
 * @param unsigned long int f_cpu as the CPU Clock Frequency.
 * @param unsigned char pres_value as the value of the desired prescaler.
 *
 * @return signed character to represent if error happened(return -1) if not(return 0).
 */
s8 MHT_GPIO(u32 f_cpu, u8 pres_value);


/**************************************************************************************************************************************
******************************************************** Function Macros **************************************************************
**************************************************************************************************************************************/





#endif // END of MHT_GPIO_H_