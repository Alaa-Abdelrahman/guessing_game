/***************************************************************************************************************************/
/***************************************************************************************************************************/
/*************************************  Author : Alaa Abdelrahman         **************************************************/
/*************************************  Layer  : HAL                     **************************************************/
/*************************************  SWC    : SWITCH       		          **************************************************/
/*************************************  Version: 1.0			          **************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/

#ifndef _SW_INTERFACE_H_
#define _SW_INTERFACE_H_
/**
 * define the type of connection of the switch
 */

typedef enum {
	SW_IN_PULLUP,	/**<define the connection if switch is connected in pull up resistor */
	SW_IN_PULLDOWN  /**<define the connection if switch is connected in pull down resistor */
}SwConnection_t;

/**
 * define state of the switch
 */
typedef enum{
	SW_NOT_PRESSED,   /**< define the state of switch if it is not pressed */
	SW_PRESSED		 /**<  define the state of switch if it is  pressed*/
}SwState_t;

/**
 * define the features of switch
 */

typedef struct{
	SwConnection_t SwConectionType; /**< store the connection type of connected switch */
	DioPort_t SwPort;				  /**< store the port  of connected switch */
    DioPin_t SwPin;                 /**< store the pin of connected switch  */

}SwConfig_t;




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

ErrorState_t SW_Init(SwConfig_t * pstSW);

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


ErrorState_t SW_GetState(SwConfig_t * pstSW,volatile SwState_t *State);


#endif
