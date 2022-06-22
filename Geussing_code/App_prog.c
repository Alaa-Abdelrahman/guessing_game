/*
 * File Name  : Guessing Game
 * Version    : 1.00
 * Description: this game generate random number and the player guess what the number
 *             using switch and number of presses represent the number
 *
 * Author     : Alaa Abdelrahman
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "App_interface.h"
#include "GIE_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"




/* the random number that generate each time */
uint8_t gRandomNumber = 10 ;
static uint8_t gInputNumber = 0;
static uint8_t gTimeOutFlag = 0;


void App_GenerateRandom(){

	uint8_t LocalRandom;

	/*use timer to generate random number*/
	LocalRandom =TIMER0_ReadTimerReg();
	/*mapping the value to desired range*/

	gRandomNumber = ((sfloat32_t)LocalRandom * 14.0f)/255.0f;


}

void App_SetTimeOut(){

	static uint8_t counter= 0;
	/*increase counter*/
	counter++;

	if(counter == 220)
	{
		/*Set the flag for TimeOut*/
		gTimeOutFlag = 1;

		TIMER0_SetTimerValue(0);
	}



}

void App_GetNumber(){


	uint8_t PressedKey = 0;
	/*Enable the the interrupt*/
	TIMER0_SetInterrupt(NORMAL,ENABLED);

	/*make the Timer to count from here*/
	TIMER0_SetTimerValue(0);

	while(gTimeOutFlag == 0 ){

		/*get the state of button */
		do {


			PressedKey= KPD_u8GetPressedKey();

			if(gTimeOutFlag ==1){
				return;
			}

		}
		while(PressedKey == KPD_NO_PRESSED_KEY );



		/*check the status */
		if( PressedKey == '='){

			/*prevent the interrupt and disabled timer*/
			TIMER0_SetInterrupt(NORMAL,DISABLED);


			return;
		}

		gInputNumber =gInputNumber*10+ PressedKey;

		CLCD_voidGoToXY(1,9);

		CLCD_voidSendNumber(gInputNumber);

	}

}





void App_Display(){
	static uint8_t  LCD_flag = 0;

	if((gInputNumber == 0)&&(LCD_flag == 0)){

		CLCD_voidSendString("Please Guess ");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("number:");

		LCD_flag++;

	}
	else if((gInputNumber == 0)||(gInputNumber == 255)){
		CLCD_Clear();
		CLCD_voidSendString("you don't press ");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("any numbers");
	}

	else if((gInputNumber > 15)){
		CLCD_Clear();
		CLCD_voidSendString("invalid range");
	}
	else if(gRandomNumber == gInputNumber){
		CLCD_Clear();
		CLCD_voidSendString("YOU WIN");
	}
	else if(gRandomNumber != gInputNumber)
	{
		CLCD_Clear();
		CLCD_voidSendString("YOU LOSE");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("RIGHT GUESS: ");
		CLCD_voidSendNumber(gRandomNumber);



	}


}


void App_Init(){

	/*Initialize the components of Project*/
	PORT_voidInit();




	/*Initialize LCD*/
	CLCD_voidInit();

	App_Display();

	/*Initialize the timer0*/
	TIMER0_Init();

	/*Initialize Global interrupt*/
	GIE_voidEnable();

	/*disable timer interrupt*/
	TIMER0_SetInterrupt(NORMAL,DISABLED);

	/*ISR Callback*/
	TIMER0_u8SetCallBack(App_SetTimeOut);

}


void App_Update(){

	/*get Random Number */
	App_GenerateRandom();



	/*get the number from User*/
	App_GetNumber();

	/*display the content*/
	App_Display();


}
