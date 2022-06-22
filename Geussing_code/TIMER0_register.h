/**********************************************************************/
/**********************************************************************/
/*****************		Author: Alaa		    ***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	TIMER			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/


#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_
  
#define TCNT0    		  *((volatile uint8_t*)0x52)    /* timer Register */
#define TCCR0             *((volatile uint8_t*)0x53)    /* TIMER0 control register */
#define TCCR0_WGM00        6						    /* Waveform generation mode bit0 */
#define TCCR0_WGM01        3						    /* Waveform generation mode bit1 */
#define TCCR0_CS02         2						    /* prescaler bit2  */
#define TCCR0_CS01         1						    /* prescaler bit1  */
#define TCCR0_CS00         0						    /* prescaler bit0  */
#define TCCR0_COM00        4                            /*PIN for capture on compare match*/
#define TCCR0_COM01        5                            /*PIN for capture on compare match*/

#define OCR0              *((volatile uint8_t*)0x5C)    /* Output compare Register 0  */

#define TIFR              *((volatile uint8_t*)0x58)    /* TIMER INTERRUPT FLAG REGSITER */
#define TIFR_TOV0         0                             /* TIMER OVERFLOW FLAG */
#define TIFR_OCF0         1                              /* OUTPUT COMPARE  FLAG */
#define TIMSK             *((volatile uint8_t*)0x59)    /* timer mask  */
#define TIMSK_TOIE0       0                             /* Timer overflow 0 interrupt enable  */
#define TIMSK_OCIE0       1                             /* Output compare 0 interrupt enable  */

#endif 
