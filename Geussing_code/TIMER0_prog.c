/**********************************************************************/
/**********************************************************************/
/*****************		Author: Alaa		    ***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TIMER			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "TIMER0_interface.h"
#include "TIMER0_register.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h"

/*GLOBAL POINTER TO FUNCTION */
static void (*Timer0Callback)(void)=NULL;


/*
 * Function: TIMER0_Init()
 /**
 * Description:  is used to select the source of clock for timer0
 *
 *
 * PRECONDTION: must choose the clock source in TIMER0_config.h
 *
 * POSTCONDTION: The clock source of Timer is configured
 *
 * @param none
 *
 * @return void
 */
void TIMER0_Init(void){

	/**
	 * clear the bits that control clock source
	 */
	TCCR0 &= CLK_MASK;

	/**
	 * Set the clock source
	 */
	TCCR0 |= CLOCK_SELECT;

}

/****************************************************************************
 * Function: TIMER0_SetMode()
 /**
 * Description:  is used to set mode of timer0 Normal mode or CTC mode
 *
 * PRECONDTION: choose one of mode that defined in TimerMode_t enum
 *
 * POSTCONDTION: The mode of Timer is configured
 *
 * @param[IN]  Mode is type of TimerMode_t
 *
 * @return Error state
 ******************************************************************************/
ErrorState_t TIMER0_SetMode(TimerMode_t Mode){
	ErrorState_t state = DONE ;
	switch(Mode){
	case NORMAL:
	{
		CLR_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
	}break;
	case CTC:
	{
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
	}break;
	default:
		state = WRONG_MODE;

	}
	return state;
}

/****************************************************************************
 * Function: TIMER0_SetInterrupt()
 /**
 * Description:  is used to control interrupt enable or disabled for each mode
 *
 * PRECONDTION: choose one of mode that defined in TimerMode_t enum
 * PRECONDTION: choose one of status that defined in InterruptStatus_t enum
 *
 * POSTCONDTION: interrupt state is configured
 *
 * @param[IN]  Mode is type of TimerMode_t
 * @param[IN]  state is type of InterruptStatus_t
 *
 * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetInterrupt(TimerMode_t Mode,InterruptStatus_t State){
	ErrorState_t state = DONE;

	switch(Mode){
	case NORMAL:
	{
		switch(State){
		case ENABLED:
		{
			SET_BIT(TIMSK,TIMSK_TOIE0);break;
		}
		case DISABLED:
		{
			CLR_BIT(TIMSK,TIMSK_TOIE0);break;
		}
		default:
			state = ERROR_STATE;
		}
		break;
	}
	case CTC:
	{
		switch(State){
		case ENABLED:
		{
			SET_BIT(TIMSK,TIMSK_OCIE0);break;
		}
		case DISABLED:
		{
			CLR_BIT(TIMSK,TIMSK_OCIE0);break;
		}
		default:
			state = ERROR_STATE;
		}
		break;
	}
	default:
		state = WRONG_MODE;
	}

	return state;
}

/****************************************************************************
 * Function: TIMER0_ReadFlag()
 /**
 * Description:  is used to read the flag for each mode
 *
 * PRECONDTION: choose one of mode that defined in TimerMode_t enum
 *
 * POSTCONDTION: the flag is read
 *
 * @param[IN]  Mode is type of TimerMode_t
 * @param[OUT] Result
 *
 * @return Error state
 ******************************************************************************/
ErrorState_t TIMER0_ReadFlag(TimerMode_t Mode,FlagStatus_t *Result ){
	ErrorState_t state = DONE;
	if(Result != NULL){
		switch(Mode){
		case NORMAL: *Result = GET_BIT(TIFR,TIFR_TOV0); break;
		case CTC   : *Result = GET_BIT(TIFR,TIFR_OCF0); break;
		default : state = WRONG_MODE;
		}
	}
	return state;
}

/****************************************************************************
 * Function: TIMER0_SetBusyWait()
 /**
 * Description: used for delay to wait and make processor busy
 *				 the maximum period depend on prescaler that used
 *				            -prescaler 8    -----> max time 256        micro second
 *				            -prescaler 64   -----> max time 2_048       micro second
 *				            -prescaler 256  -----> max time 8_192       micro second
 *                         -prescaler 1024 -----> max time 32_768     micro second
 *                         desired period calculation depend on that
 *
 * PRECONDTION: TIMER CLK SOURCE IS CLOCK
 *
 * @param[IN]  period
 *
 * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetBusyWait(uint64_t Period){

	ErrorState_t state = DONE;
	uint32 TickTime,OverFlowTicks,Freq,Prescaler,DesiredTicks;
	uint8_t Flag,Preload;
	sfloat32_t NO_ofOverflow;

	/*
	 * define the freq ,presacler, OverFlowTicks parameters
	 */
	Freq =SYS_CLK;
	Prescaler = TIMER_CLK_SRC ;
	OverFlowTicks= TIMER_TICKS;
	/*
	 * calculate the Tick time of counter in microsecond
	 */
	TickTime = ( sfloat32_t)Prescaler / Freq;

	/*
	 * calculate the desired ticks
	 */

	DesiredTicks = ( sfloat32_t)Period / TickTime;

	/**
	 * Check the relation between overflow ticks and desired ticks
	 */
	if(DesiredTicks > OverFlowTicks){

		NO_ofOverflow = (sfloat32_t)DesiredTicks /OverFlowTicks;
		/*to get integer part */
		Flag = (uint32)NO_ofOverflow;
		/*to get fraction part and calculate the preload value*/
		Preload = ((1-(NO_ofOverflow -Flag))*( sfloat32_t)OverFlowTicks);
		if(Preload >0 ){
			Flag ++;
		}
		TCNT0 = Preload;

		/*Stuck until during is elapsed */

		while(Flag > 0)
		{
			/*Decrement flag each time */
			Flag --;
			/*stay polling until flag is raised */
			while(GET_BIT(TIFR,TIFR_TOV0) != 1);
			/*CLEAR FLAG BY ST WITH LOGIC ONE*/
			SET_BIT(TIFR,TIFR_TOV0);
			/*Set the timer register = 0*/

			TCNT0= 0;

		}


		state = STAT1;


	}
	else if(DesiredTicks < OverFlowTicks){
		/*
		 * we calculate the preload value and set to timer register
		 */
		Preload = OverFlowTicks -DesiredTicks;
		TCNT0 = Preload;
		/*stay polling until flag is raised */
		while(GET_BIT(TIFR,TIFR_TOV0) != 1);
		/*CLEAR FLAG BY ST WITH LOGIC ONE*/
		SET_BIT(TIFR,TIFR_TOV0);
		state = STAT2;
	}
	else if(DesiredTicks == OverFlowTicks){
		TCNT0 = 0;

		/*stay polling until flag is raised */
		while(GET_BIT(TIFR,TIFR_TOV0) != 1);
		/*CLEAR FLAG BY ST WITH LOGIC ONE*/
		SET_BIT(TIFR,TIFR_TOV0);
		state = STAT3;
	}

	else
	{
		state = NULLPTR;
	}

	return state;



}
/****************************************************************************
 * Function: TIMER0_Disabled()
 /**
 * Description: used to disable the TIMER0
 *
 * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_Disabled(void){
	ErrorState_t state = DONE;

	TCCR0 |=TIM_NO_CLK;

	return state;
}

/****************************************************************************
 * Function: TIMER0_SetModeOfOutputComparePin()
 /**
 * Description: select the mode of output compare pin OC0 when timer0 in
 * 			clear on compare match CTC
 *
 * PRECONDTION: TIMER 	mode be CTC
 *
 * @param[IN]  mode in CompareOutputMode_t enum
 *
 * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetModeOfOutputComparePin(CompareOutputMode_t Mode){
	ErrorState_t state = DONE;

	switch(Mode){
	case DISCONNECTED_OC0:
	{
		CLR_BIT(TCCR0,TCCR0_COM00);
		CLR_BIT(TCCR0,TCCR0_COM01);
		break;
	}
	case TOGGLE_OC0      :
	{
		SET_BIT(TCCR0,TCCR0_COM00);
		CLR_BIT(TCCR0,TCCR0_COM01);
		break;
	}
	case CLEAR_OC0       :
	{
		CLR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	}
	case SET_OC0         :
	{
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	}
	default:
	{
		state = WRONG_MODE;
	}

	}

	return state;
}

/****************************************************************************
 * Function: TIMER0_ReadTimerReg()
 /**
 * Description: Read the value of Timer Register
 *
 * @param[OUT]  none
 *
 * @return value of timer register
 ******************************************************************************/
uint8_t  TIMER0_ReadTimerReg(void){
	return TCNT0;

}

/****************************************************************************
 * Function: TIMER0_SetTimerValue()
 /**
 * Description: write value directly in timer register value
 *					value = number of ticks
 * @param[IN]  value
 *
 * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetTimerValue(uint8_t Value){
	ErrorState_t state = DONE;

	TCNT0 = Value;

	return state;
}

/****************************************************************************
 * Function: TIMER0_SetOutputCompareValue()
 /**
 * Description: set value of output compare register value OCR0
 * 				Value = number of ticks
 * @param[IN]  value
 *
 * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetOutputCompareValue(uint8_t Value){
	ErrorState_t state = DONE;
	OCR0 = Value;

	return state;
}

/****************************************************************************
 * Function: TIMER0_u8SetCallBack()
 /**
 * Description: allow the user odf driver to excute the event
 * 			throw pass the function that need to implement when interrupt
 * 			occur
 *
 * @param[IN]  Copy_pvCallBack
 *
 * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_u8SetCallBack(void (*Copy_pvCallBack)(void)){
	ErrorState_t state = DONE;
	if(Copy_pvCallBack != NULL){
		Timer0Callback = Copy_pvCallBack;
	}
	else
	{
		state = NULLPTR;
	}
	return state;
}

/**
 * ISR for CLear On Compare Match Event
 */
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(Timer0Callback  != NULL)
	{
		Timer0Callback();
	}
}


/**
 * ISR for CLear On overflow Event
 */
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(Timer0Callback  != NULL)
	{
		Timer0Callback();
	}
}



