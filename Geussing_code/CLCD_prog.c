/***************************************************************************************************************************/
/***************************************************************************************************************************/
/*************************************  Author : Alaa Abdelrahman         **************************************************/
/*************************************  Layer  : HAL                     **************************************************/
/*************************************  SWC    : CLCD       		          **************************************************/
/*************************************  Version: 1.0			          **************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"




void CLCD_voidSend4BitCommand(uint8_t Copy_u8Command){

	/* store the 4 MSB to send first */
	uint8_t Local_Cmd = Copy_u8Command & MODE_4BIT_MASK;

	/* Set RS pin to low for command */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_LOW);

	/* Set RW pin to LOW for Write */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

	/* send command to data pins */
	(void)DIO_SetPortValue(CLCD_DATA_PORT,Local_Cmd);

	/*send enable pulse */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_LOW);

	/* store the 4 LSB to send second */
	Local_Cmd = Copy_u8Command << 4 ;
	/* send command to data pins */
	(void)DIO_SetPortValue(CLCD_DATA_PORT,Local_Cmd);

	/*send enable pulse */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_LOW);



}

void CLCD_voidSend4BitData(uint8_t Copy_u8Data){

	uint8_t Local_Data = Copy_u8Data & MODE_4BIT_MASK;

	/* Set RS pin to HIGH for DATA */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_HIGH);

	/* Set RW pin to LOW for Write */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

	/* send data to data pins */
	(void)DIO_SetPortValue(CLCD_DATA_PORT,Local_Data);

	/*send enable pulse */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_LOW);

	/* store the 4 LSB to send second */
	Local_Data = Copy_u8Data << 4 ;

	/* send data to data pins */
	(void)DIO_SetPortValue(CLCD_DATA_PORT,Local_Data);

	/*send enable pulse */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_LOW);



}


void CLCD_voidSend8BitCommand(uint8_t Copy_u8Command){

	/* Set RS pin to low for command */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_LOW);

	/* Set RW pin to LOW for Write */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

	/* send command to data pins */
	(void)DIO_SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/*send enable pulse */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_LOW);

}

void CLCD_voidSend8BitData(uint8_t Copy_u8Data){

	/* Set RS pin to HIGH for DATA */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_HIGH);

	/* Set RW pin to LOW for Write */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

	/* send command to data pins */
	(void)DIO_SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/*send enable pulse */
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	(void)DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_LOW);

}

void CLCD_voidSendData(uint8_t Copy_u8Data){

#if CLCD_MODE == CLCD_8BIT_MODE

	CLCD_voidSend8BitData(Copy_u8Data);

#elif CLCD_MODE == CLCD_4BIT_MODE

	CLCD_voidSend4BitData(Copy_u8Data);

#endif
}

void CLCD_voidSendCmd(uint8_t Copy_u8Data){

#if CLCD_MODE == CLCD_8BIT_MODE

	CLCD_voidSend8BitCommand(Copy_u8Data);

#elif CLCD_MODE == CLCD_4BIT_MODE

	CLCD_voidSend4BitCommand(Copy_u8Data);

#endif
}

void CLCD_Clear(){

	/* Clear Display  */
	CLCD_voidSendCmd(ClEAR_LCD);
}

void CLCD_DispOff(){

	CLCD_voidSendCmd(DISPLAY_OFF_CURSOR_OFF);
}

void CLCD_DispOn(){

	CLCD_voidSendCmd(DISPLAY_OFF_CURSOR_ON);
}

void CLCD_ShL()
{
	CLCD_voidSendCmd(SHIFT_CURSOR_POSITION_TO_LEFT);

}

void CLCD_ShR()
{
	CLCD_voidSendCmd(SHIFT_CURSOR_POSITION_TO_RIGHT);

}
void CLCD_voidInit(void){


	/* wait for more than 30 ms */
	_delay_ms(40);

#if CLCD_MODE == CLCD_8BIT_MODE

	/* Function set command : 2 lines , 5*8 font size */
	CLCD_voidSend8BitCommand(CLCD_FUNC_SET);

	/* Display on oFF control */
	CLCD_voidSend8BitCommand(CLCD_DISPLAY_CTRL);

	/* Clear Display  */
	CLCD_voidSend8BitCommand(ClEAR_LCD);

#elif CLCD_MODE == CLCD_4BIT_MODE

	/*Send command to set for 4 bit mode */
	CLCD_voidSend4BitCommand(CLCD_4BIT_MODE );

	/* Function set command control lines and font size */
	CLCD_voidSend4BitCommand(CLCD_FUNC_SET);

	/* Display on oFF control */
	CLCD_voidSend4BitCommand(CLCD_DISPLAY_CTRL);

	/* Clear Display  */
	CLCD_voidSend4BitCommand(ClEAR_LCD);

#endif
}


void CLCD_voidSendString(const char* Copy_pcString){

	uint8_t Local_u8Iterator = 0;

	while(Copy_pcString[Local_u8Iterator] != '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Iterator]);

		Local_u8Iterator++;
	}

}

void CLCD_voidSendNumber(uint32  Copy_u8Data)
{
	 sint8_t Local_Index ;
	 uint8_t Local_Iterator = 0;
	char arru8Digit [32];



	while (Copy_u8Data > 0) {

		// storing remainder in digit array
		arru8Digit[Local_Iterator] = Copy_u8Data % 10;
		Copy_u8Data =  Copy_u8Data / 10;
		Local_Iterator++;
	}
	for(Local_Index = Local_Iterator-1 ; Local_Index >= 0 ; Local_Index--)
	{
		CLCD_voidSendData(arru8Digit[Local_Index]+ '0') ;
	}


}

void CLCD_voidGoToXY(uint8_t Copy_u8XPos,uint8_t Copy_u8YPos){

	uint8_t Local_u8Address;
	if(Copy_u8XPos == 0)
	{
		Local_u8Address = Copy_u8YPos;
	}
	else if(Copy_u8XPos == 1)
	{
		Local_u8Address = Copy_u8YPos + 0x40;
	}

	/* set DDRAM address command
	 * 7 *6				    0     *******************
	 ************************************************
	 * 1 * adresss               ********************
	 ************************************************
	 */

	CLCD_voidSendCmd(Local_u8Address+128);
}


