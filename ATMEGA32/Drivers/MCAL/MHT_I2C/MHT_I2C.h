/*
 * @file MHT_I2C.h
 * @brief Header File for Two Wire Interface(I2C) driver.
 *
 * It includes other needed header files and defines Macros and Function Macros, and making Functions Prototype
 * that can be used for I2C implementation and for applications that use I2c module.
 *
 * @date 03 February 2021
 * @author MH_TEALEB
 */

#ifndef MHT_I2C_H_
#define MHT_I2C_H_

/**************************************************************************************************************************************
******************************************************** Includes *********************************************************************
**************************************************************************************************************************************/
#include <avr/io.h>
#include "MHT_ATMEGA32_StdTypes.h"


/**************************************************************************************************************************************
******************************************************** Defines **********************************************************************
**************************************************************************************************************************************/
// Define Prescaler Values.
#define PRES_VAL_1	1	// For Prescaler = 1.
#define PRES_VAL_4	4	// For Prescaler = 4.
#define PRES_VAL_16	16	// For Prescaler = 16.
#define PRES_VAL_64	64	// For Prescaler = 64.

// Define General Call Recognition.
#define GENERAL_CALL_ENABLE		1	// To enable general call recognition.
#define GENERAL_CALL_DISABLE	0	// To disable general call recognition

// Define Status codes that appears on the TWSR while prescaler bits are zero.
#define START 0X08	// Status code for Start condition that has been transmitted.

#define MT_SLAW 0X18	// Status code for Master Transmit Slave Address + Write bit has been transmitted, and acknowledge is received.
#define MT_SLAR 0X40	// Status code for Master Transmit Slave Address + Read bit has been transmitted, and acknowledge is received.
#define MT_DATA 0X28	// Status code for Master Transmit DATA has been transmitted, and acknowledge is received.
#define ST_DATA 0XB8	// Status code for Slave Transmit DATA has been transmitted, and acknowledge is received.
#define ST_LA_DATA 0XC8	// Status code for Slave Transmit Last DATA has been transmitted, and acknowledge is received.

#define SR_SLAW 0X60		// Status code for Slave Receive Slave Address + Write has been Received, and acknowledge is transmitted.
#define M_LO_SR_SLAW 0X68	// Status code for Master Lost arbitration, Slave Receive mode, Slave Address + Write has been Received,
							//and acknowledge is transmitted.
#define SR_GC 0X70			// Status code for Slave Receive mode, General Call has been received, and acknowledge is transmitted.
#define M_LO_SR_GC 0X78		// Status code for Master Lost arbitration Slave Receive General Call has been Received,
							//and acknowledge is transmitted.
#define ST_SLAR 0XA8		// Status code for Slave Transmit mode, Slave Address + Read has been received, and acknowledge is transmitted.
#define M_LO_ST_SLAR 0XB0	// Status code for Master Lost arbitration, Slave Transmit mode,
							// Slave Address + Read has been received, and acknowledge is transmitted.

#define MR_DATA 0X50	// Status code for Master Receive mode, DATA has been received, and acknowledge has been transmitted.
#define P_SR_SLAW 0X80	// Status code for Slave Receive mode, Previously Addressed with own Slave address + Write has been received,
						// and ACK has been transmitted.
#define P_SR_GC	0X90	// Status code for Slave Received mode, Previously General Call has been received,
						// and ACK has been transmitted.

#define STOP 0XA0		// Status code for Slave Receive mode, Stop condition.



// Define The returned of Error, no_errors and if need action in next byte.
#define ERROR	-1
#define NO_ERROR	0
#define NEED_ACTION_NEXT	1

/**************************************************************************************************************************************
******************************************************** Function Prototypes **********************************************************
**************************************************************************************************************************************/
/**
 * @brief A function that Initialize I2C.
 *
 * It is the function that initialize I2C By Enabling I2C, taking the CPU Clock Frequency, the desired prescaler_value
 * and the clock_frequency.
 *
 * @param unsigned long int f_cpu as the CPU Clock Frequency.
 * @param unsigned char pres_value as the value of the desired prescaler.
 * @param unsigned long int scl_freq as the I2C serial Clock Frequency.
 *
 * @return signed character to represent if error happened(return -1) if not(return 0).
 */
s8 MHT_I2C_Init(u32 f_cpu, u8 pres_value, u32 scl_freq);

/**
 * @brief A function that config address for this I2C device.
 *
 * It is the function that config address that will be used for calling this I2C device as a slave by another master.
 * It takes the desired address and if needed to recognize for general call or not.
 *
 * @param unsigned char address as the I2C device address.
 * @param unsigned char general_call as if Enable or Disable the recognition for general call.
 *
 * @return Doesn't Return any Values.
 */
void MHT_I2C_Address_Device_config(u8 address, u8 general_call);

/**
 * @brief A function that start I2C.(Can be used only by Master).
 *
 * It is the function that begin the I2C operation By sending the start bit.
 * It can be used by Master Transmit and Master Receive.
 *
 * @param Doesn't take any input parameters.
 *
 * @return Doesn't return any values.
 */
void MHT_I2C_Start(void);


/**
 * @brief A function that used to transmit address and data.(Can only be used By Transmitter).
 *
 * It is the function that transmit address and data on the I2C data bus.
 * This function can be used by Master Transmitter and Slave Transmitter.
 *
 * @param unsigned char ch as the 8-bits (address + R/W) or data that will be transmitted.
 *
 * @return Doesn't return any values.
 */
void MHT_I2C_Transmit(u8 ch);


/**
 * @brief A function that used to receive the slave address.(Can only be used by Slave).
 *
 * It is the function that receive the Slave address after being called by other master by. It will transmit ACk without read any data.
 * This function can be used by Slave Transmitter and Slave Receiver.
 *
 * @param Doesn't take any input parameters.
 *
 * @return Doesn't return any values.
 */
void MHT_I2C_Receive_Slave_Address(void);


/**
 * @brief A function that read data and responding with acknowledge.(Can be used by Receiver).
 *
 * It is the function that read data from the I2C data bus and after reading it will respond with acknowledge.
 * This function can be used by Master Receiver and Slave Receiver.
 *
 * @param Doesn't send any input parameters.
 *
 * @return unsigned character as the received data or return error if there is an issue.
 */
u8 MHT_I2C_Receive_Data_with_ACK(void);


/**
 * @brief A function that read data and responding with Not Acknowledge.(Can be used by Receiver).
 *
 * It is the function that read data from the I2C data bus and after reading it will respond with Not acknowledge.
 * This function can be used by Master Receiver and Slave Receiver.
 *
 * @param Doesn't send any input parameters.
 *
 * @return unsigned character as the received data or return error if there is an issue.
 */
u8 MHT_I2C_Receive_Data_with_NACK(void);


/**
 * @brief A function that the Master stops arbitration.(Can only be used by Master).
 *
 * It is the function that the Master end the arbitration of the I2C data bus.
 * This function can be used by Master Transmitter and Master Receiver.
 *
 * @param Doesn't send any input parameters.
 *
 * @return Doesn't return any values.
 */
void MHT_I2C_Stop(void);




/**************************************************************************************************************************************
******************************************************** Function Macros **************************************************************
**************************************************************************************************************************************/
#define MHT_I2C_INTERRUPT_ENABLE()    ({ TWCR |=  (1 << TWIE); })   // Enable I2C Interrupt.
#define MHT_I2C_INTERRUPT_DISABLE()   ({ TWCR &= ~(1 << TWIE); })  // Disable I2C Interrupt.

#define MHT_I2C_MODULE_ENABLE()    ({ TWCR |=  (1 << TWEN); })   // Enable I2C Module.
#define MHT_I2C_MODULE_DISABLE()   ({ TWCR &= ~(1 << TWEN); })   // Disable I2C Module.

#define MHT_I2C_Check_COLLISION_SET() ({ ((TWCR & (1 << TWWC)) != 0); })   // Check if I2C Write Collision Flag is set.
																		   // If set, return 1. If not set, return 0.

#define MHT_I2C_STOP_SET()		 ({ TWCR |=  (1 << TWSTO); })   // SET I2C Stop bit.
#define MHT_I2C_STOP_CLEAR()	 ({ TWCR &= ~(1 << TWSTO); })   // CLEAR I2C Stop bit.

#define MHT_I2C_START_SET()    ({ TWCR |=  (1 << TWSTA); })	  // Set I2C Start bit.
#define MHT_I2C_START_CLEAR()  ({ TWCR &= ~(1 << TWSTA); })	  // Clear I2C Start bit.

#define MHT_I2C_ACK_ENABLE()   ({ TWCR |=  (1 << TWEA); })    // Enable I2C Acknowledge.
#define MHT_I2C_ACK_DIABLE()   ({ TWCR &= ~(1 << TWEA); })    // Disable I2C Acknowledge.

#define MHT_I2C_Check_INTERRUPT_FLAG_SET() ({ ((TWCR & (1 << TWINT)) != 0); })   // Check if I2C Interrupt Flag is set.
																				 // If set, return 1. If not set, return 0.
#define MHT_I2C_INTERRUPT_FLAG_CLEAR()   ({ TWCR |=  (1 << TWINT); })    // CLEAR I2C Interrupt Flag.

#define MHT_I2C_SELECT_PRESCALER_1()     ({  TWSR &= ~(3 << TWPS0);  })    // Select Prescaler Value = 1.
#define MHT_I2C_SELECT_PRESCALER_4()     ({  TWSR |=  (1 << TWPS0); \
                                             TWSR &= ~(1 << TWPS1); \
                                                                     })    // Select Prescaler Value = 4.
#define MHT_I2C_SELECT_PRESCALER_16()    ({ TWSR &= ~(1 << TWPS0); \
                                            TWSR |=  (1 << TWPS1); \
                                                                     })    // Select Prescaler Value = 16.
#define MHT_I2C_SELECT_PRESCALER_64()    ({ TWSR |=  (1 << TWPS0); \
                                            TWSR |=  (1 << TWPS1); \
                                                                     })    // Select Prescaler Value = 64.

#define MHT_I2C_GET_STATUS()	({ (TWSR & ~(3 << TWPS0)); })	// Get The status register with prescaler bits cleared.

#define MHT_I2C_GENERAL_CALL_RECOG_ENABLE()  ({ TWAR |=  (1 << TWGCE);  })    // Enable I2C General Call Recognition.
#define MHT_I2C_GENERAL_CALL_RECOG_DISABLE() ({ TWAR &= ~(1 << TWGCE);  })    // Disable I2C General Call Recognition.


#endif // END of MHT_I2C_H_
