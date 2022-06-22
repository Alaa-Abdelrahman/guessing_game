/***************************************************************************************************************************/
/***************************************************************************************************************************/
/*************************************  Author : Alaa Abdelrahman         **************************************************/
/*************************************  Layer  : HAL                     **************************************************/
/*************************************  SWC    : SWITCH       		          **************************************************/
/*************************************  Version: 1.0			          **************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SW_interface.h"

/**********************************************************************
* Function : SW_Init()
*//**
* \b Description:
** This function is used to configure the switch with
** the port and pin the switch connect to  and the status
*
* PRE-CONDITION: Pointer that passed to function  not null , point to configure structure<br>
* PRE-CONDITION: SwConfig_t structure must be initilized with right valuess <br>
*
* POST-CONDITION: switch is configured
*
* @param pointer to SwConfig_t structure
*
* @return error state
*
* \b Example:
* @code
*
* SwConfig SW1 = {SW_IN_PULLUP,,PORTA,PIN0}
* uint8_t state = SW_Init(&SW1);
*
* @endcode
******************************************************************************/
ErrorState_t SW_Init(SwConfig_t * pstSW)
{

	ErrorState_t Local_u8SwErrorState = DONE;
	if(pstSW != NULL)
	{
		DIO_SetPinDirection(pstSW->SwPort ,pstSW->SwPin , DIO_INPUT);

		if(pstSW->SwConectionType == SW_IN_PULLUP)
		{
			DIO_SetPinValue(pstSW->SwPort ,pstSW->SwPin , DIO_HIGH);
		}
	}
	else
	{
		Local_u8SwErrorState = NULLPTR ;
	}
	return Local_u8SwErrorState ;
}



/**********************************************************************
* Function : SW_GetState()
*//**
* \b Description:
* This function is used to get state of switch after configured
*
* PRE-CONDITION: Pointer that passed to function  not null , point to configure structure<br>
* PRE-CONDITION: the switch must be configured with function SW_Init() <br>
* PRE-CONDITION: state pointer musn't be null
*
* POST-CONDITION: get the state of the switch
*
* @param pointer to SwConfig_t structure
* @param pointer to state of switch
*
*
* @return error state
*
* \b Example:
* @code
*
* SwConfig SW1 = {SW_IN_PULLUP,,PORTA,PIN0}
* ErrorState_t state = SW_Init(&SW1);
* SwState_t state ;
* ErrorState_t SwState = SW_GetState(&SW1, *State)
*
* if(state == SW_PRESSED)
* {
*   //CODE
* }
*
* @endcode
******************************************************************************/



ErrorState_t  SW_GetState(SwConfig_t * pstSW,volatile SwState_t * State){

	ErrorState_t Local_u8SwErrorState = DONE;
	SwState_t Local_u8SwState;

	if((pstSW != NULL) && (State != NULL))

	{
		DIO_GetPinValue(pstSW->SwPort ,pstSW->SwPin, &Local_u8SwState);

		if(pstSW->SwConectionType == SW_IN_PULLUP)
		{

			if(Local_u8SwState == 0)
			{
				*State = SW_PRESSED;
			}

			else if(Local_u8SwState == 1)
			{
				*State = SW_NOT_PRESSED;
			}
		}

		else if(pstSW->SwConectionType == SW_IN_PULLDOWN)
		{

			if(Local_u8SwState == 1)
			{
				*State = SW_PRESSED;
			}

			else if(Local_u8SwState == 0)
			{
				*State = SW_NOT_PRESSED;
			}
		}
	}
	else
	{
		Local_u8SwErrorState = NULLPTR ;
	}
	return Local_u8SwErrorState;
}
