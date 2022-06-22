/****************************************************************************/
/****************************************************************************/
/*****************		Author  : Alaa Abdelrahman    ***********************/
/*****************		Layer	:	MCAL			  ***********************/
/*****************		SWC		:	DIO				  ***********************/
/*****************		Version :   2.00			  ***********************/
/*****************		Date    :   12/9			  ***********************/
/****************************************************************************/
/****************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_register.h"
#include "DIO_private.h"
#include "DIO_config.h"







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


ErrorState_t DIO_SetPinDirection(DioPort_t Port,DioPin_t Pin, DioMode_t Mode)
{
	ErrorState_t Local_u8ErrorState = DONE;

	if(Pin<= PIN7)
	{
		if(Mode==DIO_INPUT)
		{
			switch(Port)
			{
			case PORTA: CLR_BIT( PORTA_BASE_PTR->DDR,Pin); break;
			case PORTB: CLR_BIT( PORTB_BASE_PTR->DDR,Pin); break;
			case PORTC: CLR_BIT( PORTC_BASE_PTR->DDR,Pin); break;
			case PORTD: CLR_BIT( PORTD_BASE_PTR->DDR,Pin); break;
			default: Local_u8ErrorState = PORT_NOT_FOUND ; break;
			}
		}

		if(Mode==DIO_INPUT_PULLUP)
		{
			switch(Port)
			{
			case PORTA: CLR_BIT( PORTA_BASE_PTR->DDR,Pin);SET_BIT( PORTA_BASE_PTR->PORT,Pin); break;
			case PORTB: CLR_BIT( PORTB_BASE_PTR->DDR,Pin);SET_BIT( PORTB_BASE_PTR->PORT,Pin); break;
			case PORTC: CLR_BIT( PORTC_BASE_PTR->DDR,Pin);SET_BIT( PORTC_BASE_PTR->PORT,Pin); break;
			case PORTD: CLR_BIT( PORTD_BASE_PTR->DDR,Pin);SET_BIT( PORTD_BASE_PTR->PORT,Pin); break;
			default: Local_u8ErrorState = PORT_NOT_FOUND ; break;
			}
		}
		else if (Mode==DIO_OUTPUT)
		{
			switch(Port)
			{
			case PORTA: SET_BIT( PORTA_BASE_PTR->DDR,Pin); break;
			case PORTB: SET_BIT( PORTB_BASE_PTR->DDR,Pin); break;
			case PORTC: SET_BIT( PORTC_BASE_PTR->DDR,Pin); break;
			case PORTD: SET_BIT( PORTD_BASE_PTR->DDR,Pin); break;
			default: Local_u8ErrorState = PORT_NOT_FOUND ; break;
			}
		}
		else
		{
			Local_u8ErrorState = MODE_NOT_AVALIABLE;
		}
	}
	else
	{
		Local_u8ErrorState = PIN_NOT_FOUND;
	}

	return Local_u8ErrorState;
}

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

ErrorState_t DIO_SetPortDirection(DioPort_t Port, uint8_t u8Value)
{
	ErrorState_t Local_u8ErrorState = DONE;

	switch(Port)
	{
	case PORTA : PORTA_BASE_PTR->DDR = u8Value; break;
	case PORTB : PORTB_BASE_PTR->DDR = u8Value; break;
	case PORTC : PORTC_BASE_PTR->DDR = u8Value; break;
	case PORTD : PORTD_BASE_PTR->DDR = u8Value; break;
	default: Local_u8ErrorState = PORT_NOT_FOUND;
	}

	return Local_u8ErrorState;
}

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


ErrorState_t DIO_SetPortValue(DioPort_t Port, uint8_t u8Value)
{
	ErrorState_t Local_u8ErrorState = DONE;

	switch(Port)
	{
	case PORTA : PORTA_BASE_PTR->PORT = u8Value; break;
	case PORTB : PORTB_BASE_PTR->PORT = u8Value; break;
	case PORTC : PORTC_BASE_PTR->PORT = u8Value; break;
	case PORTD : PORTD_BASE_PTR->PORT = u8Value; break;
	default: Local_u8ErrorState= PORT_NOT_FOUND;
	}

	return Local_u8ErrorState;
}


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

ErrorState_t DIO_SetPinValue(DioPort_t Port,DioPin_t Pin, DioState_t State)
{
	ErrorState_t Local_u8ErrorState = DONE;

	if(Pin<= PIN7)
	{
		if(State==DIO_LOW)
		{
			switch(Port)
			{
			case PORTA: CLR_BIT(PORTA_BASE_PTR->PORT,Pin); break;
			case PORTB: CLR_BIT(PORTB_BASE_PTR->PORT,Pin); break;
			case PORTC: CLR_BIT(PORTC_BASE_PTR->PORT,Pin); break;
			case PORTD: CLR_BIT(PORTD_BASE_PTR->PORT,Pin); break;
			default: Local_u8ErrorState = PORT_NOT_FOUND ; break;
			}
		}
		else if (State==DIO_HIGH)
		{
			switch(Port)
			{
			case PORTA: SET_BIT(PORTA_BASE_PTR->PORT,Pin); break;
			case PORTB: SET_BIT(PORTB_BASE_PTR->PORT,Pin); break;
			case PORTC: SET_BIT(PORTC_BASE_PTR->PORT,Pin); break;
			case PORTD: SET_BIT(PORTD_BASE_PTR->PORT,Pin); break;
			default: Local_u8ErrorState = PORT_NOT_FOUND; break;
			}
		}
		else
		{
			Local_u8ErrorState = STATE_NOT_AVALIABLE;
		}
	}
	else
	{
		Local_u8ErrorState = PIN_NOT_FOUND;
	}

	return Local_u8ErrorState;
}

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


ErrorState_t DIO_TogglePinValue(DioPort_t Port,DioPin_t Pin)
{
	ErrorState_t Local_u8ErrorState= DONE ;
	if(Pin<= PIN7)
	{
		switch(Port)
		{
		case PORTA: TOG_BIT(PORTA_BASE_PTR->PORT,Pin); break;
		case PORTB: TOG_BIT(PORTB_BASE_PTR->PORT,Pin); break;
		case PORTC: TOG_BIT(PORTC_BASE_PTR->PORT,Pin); break;
		case PORTD: TOG_BIT(PORTD_BASE_PTR->PORT,Pin); break;
		default: Local_u8ErrorState = PORT_NOT_FOUND ; break;
		}
	}
	else
	{
		Local_u8ErrorState = PIN_NOT_FOUND;
	}

	return Local_u8ErrorState;

}




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
ErrorState_t DIO_GetPinValue(DioPort_t Port,DioPin_t Pin, uint8_t* pu8Value)
{
	ErrorState_t Local_u8ErrorState = DONE ;

	if(pu8Value!=NULL)
	{
		if( (Pin<=PIN7))
		{
			switch(Port)
			{
			case PORTA : *pu8Value= GET_BIT(PORTA_BASE_PTR->PIN ,Pin); break;
			case PORTB : *pu8Value= GET_BIT(PORTB_BASE_PTR->PIN ,Pin); break;
			case PORTC : *pu8Value= GET_BIT(PORTC_BASE_PTR->PIN ,Pin); break;
			case PORTD : *pu8Value= GET_BIT(PORTD_BASE_PTR->PIN ,Pin); break;
			default: Local_u8ErrorState = PORT_NOT_FOUND ;
			}
		}
		else
		{
			Local_u8ErrorState = PIN_NOT_FOUND ;
		}
	}
	else
	{
		Local_u8ErrorState = NULLPTR;

	}
	return Local_u8ErrorState;
}


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

ErrorState_t DIO_Init(const DioConfig_t * const  Config)
{
	ErrorState_t Local_u8ErrorState = 4;


	if(Config != NULL)
	{

		DIO_SetPinDirection(Config->Port,Config->Pin,Config->Mode);


	}
	else
	{
		Local_u8ErrorState = NULLPTR;
	}

	return Local_u8ErrorState ;

}
