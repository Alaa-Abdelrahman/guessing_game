/**********************************************************************/
/**********************************************************************/
/*****************		Author: Alaa		    ***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TIMER			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/

#ifndef TIMER_CONFIIG_H_
#define TIMER_CONFIIG_H_

/**
 * Define the clock source options
 *
 *                      - TIM_NO_CLK
 *                      - TIM_CLK_PRESC_0
 *                      - TIM_CLK_PRESC_8
 *                      - TIM_CLK_PRESC_64
 *                      - TIM_CLK_PRESC_256
 *                      - TIM_CLK_PRESC_1024
 *                      - TIM_CLK_EXT_FALLING_EDGE_T0
 *                      - TIM_CLK_EXT_RISING_EDGE_T0
 *
 */


#define  CLOCK_SELECT    TIM_CLK_PRESC_1024



#endif
