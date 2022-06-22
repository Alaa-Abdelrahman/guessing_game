/***************************************************************************************************************************/
/***************************************************************************************************************************/
/*************************************  Author : Alaa Abdelrahman         **************************************************/
/*************************************  Layer  : HAL                     **************************************************/
/*************************************  SWC    : CLCD       		          **************************************************/
/*************************************  Version: 1.0			          **************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/

#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

#define MODE_4BIT_MASK      0b11110000

/*LCD Modes*/
 #define CLCD_4BIT_MODE   0x02
 #define CLCD_8BIT_MODE   1

/*Function set options */
#define CLCD_8Bit_FUNC_SET_2LINES_5_8_GRID     0b00111000
#define CLCD_8Bit_FUNC_SET_1LINE_5_8_GRID      0b00110000
#define CLCD_8Bit_FUNC_SET_2LINES_5_11_GRID    0b00111100
#define CLCD_8Bit_FUNC_SET_1LINES_5_11_GRID    0b00110100
#define CLCD_4Bit_FUNC_SET_2LINES_5_8_GRID     0b00101000
#define CLCD_4Bit_FUNC_SET_1LINE_5_8_GRID      0b00100000
#define CLCD_4Bit_FUNC_SET_2LINES_5_11_GRID    0b00101100
#define CLCD_4Bit_FUNC_SET_1LINES_5_11_GRID    0b00100100

/*control Cursor */
#define CLCD_DISPLAY_CTRL_ON_DISPLAY_OFF_CUR   		0b00001100
#define CLCD_DISPLAY_CTRL_OFF_DISPLAY_OFF_CUR  		0b00001000
#define CLCD_DISPLAY_CTRL_ON_DISPLAY_ON_CUR    		0b00001110
#define CLCD_DISPLAY_CTRL_ON_DISPLAY_ON_CUR_BLINK   0b00001111


/*Command to LCD*/
#define     ClEAR_LCD                                0x01
#define  	DISPLAY_OFF_CURSOR_OFF                   0X08
#define  	DISPLAY_OFF_CURSOR_ON                    0X0A
#define  	DISPLAY_ON_CURSOR_OFF                    0X0C
#define  	DISPLAY_ON_CURSOR_BLINKING               0X0E
#define  	DISPLAY_ON_CURSOR_NOT_BLINKING           0X0F
#define  	SHIFT_CURSOR_POSITION_TO_LEFT            0X10
#define  	SHIFT_CURSOR_POSITION_TO_RIGHT           0X14
#define  	SHIFT_THE_ENTIRE_DISPLAY_TO_THE_LEFT     0X18
#define  	SHIFT_THE_ENTIRE_DISPLAY_TO_THE_RIGHT    0X1C
#define  	FORCE_CURSOR_TO_BEGINNING_1ST LINE       0X80
#define  	FORCE_CURSOR_TO_BEGINNING_2ND LINE       0XC0



#endif /* CLCD_PRIVATE_H_ */
