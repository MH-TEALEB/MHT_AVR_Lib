/*
* MHT_ATMEGA32_DataTypes.h
*
* This is Data Types for ATMEGA32 8-bit Micro-Controller.
*
* Created: 27-Oct-18 11:42:32 AM
* Author : MH_TEALEB
*/

#ifndef MHT_ATMEGA32_DataTypes_H_
#define MHT_ATMEGA32_DataTypes_H_

    typedef unsigned char uint8;
    typedef signed char   sint8;
	typedef char          int8;
	
    typedef unsigned short int	uint16;
    typedef signed short int	sint16;
	typedef short int			int16;

    typedef unsigned long int uint32;
    typedef signed long int   sint32;
	typedef long int		  int32;
	
    typedef unsigned long long int uint64;
    typedef signed long long int   sint64;
	typedef long long int		   int64;
    typedef float float32;  // Float, Double & Long Double are all 4-Bytes in 8-bit Micro-Controller.

#endif // MHT_ATMEGA32_DATATYPES_H_
