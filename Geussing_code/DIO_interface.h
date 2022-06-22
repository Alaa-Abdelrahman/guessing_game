/****************************************************************************/
/****************************************************************************/
/*****************		Author  : Alaa Abdelrahman    ***********************/
/*****************		Layer	:	MCAL			  ***********************/
/*****************		SWC		:	DIO				  ***********************/
/*****************		Version :   2.00			  ***********************/
/*****************		Date    :   12/9			  ***********************/
/****************************************************************************/
/****************************************************************************/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/**
 * define the number of pins in each MCU
 */

#define NUMBER_OF_PINS    8

/**
 * define the number of ports in each MCU
 */

#define NUMBER_OF_PORTS    4





/**
 * This enum is used to define the mode of the
 * pin or port; each pin has three states:
 *                            -DIO_OUTPUT
 *                            -DIO_INPUT
 *                            -DIO_INPUT_PULLUP
 */

typedef enum{
	DIO_OUTPUT,                 /**< set the mode to pin output */
	DIO_INPUT,					/**< set the mode to pin input floating */
	DIO_INPUT_PULLUP		    /**< set the mode to pin and enable the internal pull up resistor */

}DioMode_t;


/**
 * This enum is used to define the state of the
 * pin or port; each pin has two states:
 *                            -DIO_HIGH
 *                            -DIO_LOW
 */
typedef enum{
	DIO_LOW,	/**< set the output pin to low voltage (GND) */
	DIO_HIGH    /**< set the output pin to high voltage (vcc) */

}DioState_t;

/**
 * This enum is used to define Ports of the MCU
 * Ports available are :
 *                       -PORTA
 *                       -PORTB
 *                       -PORTC
 *                       -PORTD
 */

typedef enum{
	        PORTA,
	        PORTB,
	        PORTC,
	        PORTD
}DioPort_t;

/**
 * This enum is used to define pins of each Port of the MCU
 */

typedef enum{
	      PIN0,
	      PIN1,
	      PIN2,
	      PIN3,
	      PIN4,
	      PIN5,
	      PIN6,
	      PIN7
}DioPin_t;


/**
* Defines the digital input/output configuration table’s elements that are
* used
* by Dio_Init to configure the Dio peripheral.
*/

typedef struct
{
DioPort_t  Port;	/**< Define Port  */
DioPin_t   Pin; 	/**< The I/O pin */
DioMode_t  Mode; 	/**< OUTPUT or INPUT */
DioState_t State;	/**<HIGH or LOW */

}DioConfig_t;


/*********************************************************************
* Function : Dio_Init()
*//**
* \b Description:
*
* This function is used to initialize the Dio based on the configuration
 * table that is just array of 2d dimensional each row as port and columns are pins
 *
 *
* PRE-CONDITION: Configuration must set <br>
*
*
* POST-CONDITION: The DIO peripheral is set up with the configuration
* settings.
*
* @param : Config is a pointer to the configuration table that
* contains the initialization for the peripheral.
*
* @return error state that defined in enum error state
*
* \b Example:
*
* @code
* Dio_Init(DioConfig);
*
* @endcode
*
**************************************************************************************************************************/


ErrorState_t DIO_Init(const DioConfig_t * const Config) ;

/**********************************************************************
* Function : DIO_SetPinDirection()
*//**
* \b Description:
*
* This function is used to set the mode of DIO (pin)
*
* PRE-CONDITION: Pin is defined  in DioPin_t enum <br>
* PRE-CONDITION: Port is defined in DioPort_t enum <br>
*
* POST-CONDITION: The channel is set in the one of three modes
*                                                             -output
*                                                             -input_floating
*                                                             -input_pull_up
* @param port which pin is part from
* @param pin  needed to set
* @param mode
*
* @return error state that in definition
*
* \b Example:
* @code
*
* uint8_t state = DIO_u8SetPinDirection(PORTA,PIN0,DIO_INPUT);
*
* @endcode
***************************************************************/

ErrorState_t DIO_SetPinDirection(DioPort_t Port,DioPin_t Pin, DioMode_t Mode);

/**************************************************************************
* Function : DIO_SetPortDirection()
*//**
* \b Description:
* *
*This function is used to directly set the desired port with desired value.
* The value control the modes of all port pins  at once
*
* POST-CONDITION: The port with set with desired values that control pin modes
*
* @param  Port to set the vlaue for
* @param  Value is the value to set the Dio register to
*
* @return Error state
*
* \b Example:
* @code
* DIO_SetPortDirection(PORTA,15);
* @endcode
***************************************************************************/


ErrorState_t DIO_SetPortDirection(DioPort_t Port, uint8_t u8Value);

/**********************************************************************
* Function : DIO_SetPinValue()
*//**
* \b Description:
* *
* This function is used to write the state of a channel (pin) as either
* logic high or low
*
* PRE-CONDITION: The pin is configured as OUTPUT <br>
* PRE-CONDITION: The pin is configured as GPIO <br>
* PRE-CONDITION: The pin is within the maximum DioChannel_t definition
*
* POST-CONDITION: The pin state will be State
*
* @param pin is the pin to write using the Diopin_t enum definition
* @param State is DIO_HIGH or DIO_LOW  or as defined in the DioState_t enum
*
* @return Error state
*
* \b Example:
* @code
* DIO_SetPinValue(PORTA, PIN0 , LOW);
* DIO_SetPinValue(PORTB, PIN1 , HIGH);
* @endcode
**********************************************************************/

ErrorState_t DIO_SetPinValue(DioPort_t Port,DioPin_t Pin, DioState_t State);


/**************************************************************************
* Function : DIO_TogglePinValue()
*//**
* \b Description:
* *
This function is used to toggle the current state of pin
*
* PRE-CONDITION: The pin is configured as OUTPUT <br>
* PRE-CONDITION: The pin is configured as GPIO <br>
* PRE-CONDITION: The pin is within the maximum Diopin_t definition
*
* POST-CONDITION:
*
* @param port is the port from the DioPort_t that is to be modified.
* @param pin is the pin from the DioPin_t that is to be modified.
*
*
* @return error state
*
* \b Example:
* @code
* DIO_TogglePinValue(PORTA,PIN1);
* @endcode
***************************************************/


ErrorState_t DIO_TogglePinValue(DioPort_t Port,DioPin_t Pin);

/**********************************************************************
* Function : DIO_GetPinValue()
*//**
* \b Description:
** This function is used to read the state of a dio channel (pin)
*
* PRE-CONDITION: The pin is configured as INPUT <br>
* PRE-CONDITION: The pin is configured as GPIO <br>
* PRE-CONDITION: The pin is within the maximum Diopin_t definition
* * PRE-CONDITION: the pointer mustn't  be null
*
*
* POST-CONDITION: The channel state is stored in pointer
*
* @param port is the DioPort_t that represents a port
* @param pin is the DioPin_t that represents a pin
* @param pointer to store state
*
* @return error state
*
* \b Example:
* @code
* uint8_t value;
* uint8_t pinstate = DIO_GetPinValue(PORTA,PIN0,&value);
* @endcode
******************************************************************************/
ErrorState_t DIO_GetPinValue(DioPort_t Port,DioPin_t Pin, uint8_t* pu8Value);


/**************************************************************************
* Function : DIO_SetPortValue()
*//**
* \b Description:
* *
*This function is used to directly set the desired port with desired value.
* The value control the state of all port pins  at once
*
* POST-CONDITION: The port with set with desired values that control pin modes
*
* @param  Port to set the vlaue for
* @param  Value is the value to set the Dio register to
*
* @return Error state
*
* \b Example:
* @code
* DIO_SetPortDirection(PORTA,ox15);
* @endcode
***************************************************************************/

ErrorState_t DIO_SetPortValue(DioPort_t Port, uint8_t u8Value);



#endif
