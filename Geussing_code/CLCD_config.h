/***************************************************************************************************************************/
/***************************************************************************************************************************/
/*************************************  Author : Alaa Abdelrahman         **************************************************/
/*************************************  Layer  : HAL                     **************************************************/
/*************************************  SWC    : CLCD       		          **************************************************/
/*************************************  Version: 1.0			          **************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/
#ifndef _CLCD_CONFIG_H_
#define _CLCD_CONFIG_H_

/**
 * Configure the port and pins for LCD
 */
#define CLCD_DATA_PORT    PORTC   /**<the port that connected to data pins */

#define CLCD_CTRL_PORT    PORTD   /**< the port that control pins connected to */

#define CLCD_RS_PIN       PIN0    /**<register select pin */
#define CLCD_RW_PIN       PIN1    /**<read write pin */
#define CLCD_E_PIN        PIN2    /**<enable pin */


/**
 * Mode of LCD Operation Options:
 *                  -CLCD_4BIT_MODE
 *                  -CLCD_8BIT_MODE
 */

#define CLCD_MODE    CLCD_4BIT_MODE



/* Function Set Option:
 *
 *	 			  -CLCD_4Bit_FUNC_SET_2LINES_5_8_GRID
 *				  -CLCD_4Bit_FUNC_SET_1LINE_5_8_GRID
 * 				  -CLCD_4Bit_FUNC_SET_2LINES_5_11_GRID
 * 				  -CLCD_4Bit_FUNC_SET_1LINES_5_11_GRID
 * 				  -CLCD_8Bit_FUNC_SET_2LINES_5_8_GRID
 * 				  -CLCD_8Bit_FUNC_SET_1LINE_5_8_GRID
 * 				  -CLCD_8Bit_FUNC_SET_2LINES_5_11_GRID
 * 				  -CLCD_8Bit_FUNC_SET_1LINES_5_11_GRID
 *
 *
 */


#define CLCD_FUNC_SET  CLCD_4Bit_FUNC_SET_2LINES_5_8_GRID


/* DISPLAY CONTROL OPTION:
 *               -CLCD_DISPLAY_CTRL_ON_DISPLAY_OFF_CUR
 *               -CLCD_DISPLAY_CTRL_OFF_DISPLAY_OFF_CUR
 *               -CLCD_DISPLAY_CTRL_ON_DISPLAY_ON_CUR
 *               -CLCD_DISPLAY_CTRL_ON_DISPLAY_ON_CUR_BLINK
 */




#define CLCD_DISPLAY_CTRL  CLCD_DISPLAY_CTRL_ON_DISPLAY_OFF_CUR







#endif
