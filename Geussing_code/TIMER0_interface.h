/**********************************************************************/
/**********************************************************************/
/*****************		Author: Alaa		    ***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TIMER			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


#define STAT1 5
#define STAT2 6
#define STAT3 7


/**
 * define the Timer clk source value
 */

#define TIMER_CLK_SRC   8


/**
 * define number of ticks that cause timer to overflow
 * depend on 2 exponent resolution of Timer
 */

#define TIMER_TICKS   256
/**
 * define the System Clock in value in mega
 * if 8000000   write 8
 */

#define SYS_CLK        8


/**
 * TimerMode_t contains modes of timer that normal mode or overflow mode
 * clear on compare match  mode
 */
typedef enum{
	NORMAL,     /**< normal mode or overflow mode */
	CTC = 2     /**< clear on compare match value mode */
}TimerMode_t;

/**
 * Compare output mode : control  the behavior of
 * output compare pin OC0 behavior
 */

typedef enum {
	DISCONNECTED_OC0,
	TOGGLE_OC0      ,
	CLEAR_OC0       ,
	SET_OC0
}CompareOutputMode_t;




/**
 * ClockSelect contain clock source for timer0 counter
 */

typedef enum{
	   TIM_NO_CLK                 ,
	   TIM_CLK_PRESC_0            ,
	   TIM_CLK_PRESC_8            ,
	   TIM_CLK_PRESC_64           ,
	   TIM_CLK_PRESC_256          ,
	   TIM_CLK_PRESC_1024         ,
	   TIM_CLK_EXT_FALLING_EDGE_T0,
	   TIM_CLK_EXT_RISING_EDGE_T0
}ClockSelect_t;

/**
 * Interrupt status that set interrupt enable or disabled for each mode
 */

typedef enum{
	DISABLED,
	ENABLED

}InterruptStatus_t;

/**
 * FlagStatus contains the status of flag of each mode
 */

typedef enum {
	CLEAR,
	SET

}FlagStatus_t;


/*****************************************************************************
 * Function: TIMER0_Init()
 */
 /**
  * Description :  is used to select the source of clock for timer0
  *
  * PRECONDTION : must choose the clock source in TIMER0_config.h
  *
  * POSTCONDTION: The clock source of Timer is configured
  *
  * @param none
  *
  * @return void
 ******************************************************************************/
void TIMER0_Init(void);


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
ErrorState_t TIMER0_SetMode(TimerMode_t Mode);

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

ErrorState_t TIMER0_SetInterrupt(TimerMode_t Mode,InterruptStatus_t State);

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
ErrorState_t TIMER0_ReadFlag(TimerMode_t Mode,FlagStatus_t *Result );

/****************************************************************************
 * Function: TIMER0_SetBusyWait()
 /**
  * Description: used for delay to wait and make processor busy
  *				 the maximum period depend on prescaler that used
  *				            -prescaler 8    -----> max time 256        micro second
  *				            -prescaler 64   -----> max time 2_048       micro second
  *				            -prescaler 256  -----> max time 8_192       micro second
  *                         -prescaler 1024 -----> max time 32_768     micro second
  *
  * PRECONDTION: TIMER CLK SOURCE IS CLOCK
  *
  * @param[IN]  period
  *
  * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetBusyWait(uint64_t Period);
/****************************************************************************
 * Function: TIMER0_Disabled()
 /**
  * Description: used to disable the TIMER0
  *
  * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_Disabled(void);

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
ErrorState_t TIMER0_SetModeOfOutputComparePin(CompareOutputMode_t Mode);

/****************************************************************************
 * Function: TIMER0_ReadTimerReg()
 /**
  * Description: Read the value of Timer Register
  *
  * @param[OUT]  none
  *
  * @return timer register
 ******************************************************************************/
uint8_t TIMER0_ReadTimerReg();

/****************************************************************************
 * Function: TIMER0_SetTimerValue()
 /**
  * Description: write value directly in timer register value
  *
  * @param[IN]  value
  *
  * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetTimerValue(uint8_t Value);
/****************************************************************************
 * Function: TIMER0_SetOutputCompareValue()
 /**
  * Description: set value of output compare register value OCR0
  * 				Value = number of ticks
  * @param[IN]  value
  *
  * @return Error state
 ******************************************************************************/

ErrorState_t TIMER0_SetOutputCompareValue(uint8_t Value);

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

ErrorState_t TIMER0_u8SetCallBack(void (*Copy_pvCallBack)(void));



#endif
