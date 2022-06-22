/**********************************************************************/
/**********************************************************************/
/*****************		Author: Alaa	     	***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	DIO				***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/
#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_


/**
 * define the registers related to each port
 */

typedef struct{
	uint8_t PIN;    /**<Data register           (data)    */
	uint8_t DDR;  /**<Data Direction Register (control) */
	uint8_t PORT;  /**<Pin Out pin register    (status)*/

}volatile * const Dio_MapPtr;


/**
 *  The pointer to base address of registers of PortA
 */
#define PORTA_BASE_PTR		((Dio_MapPtr)0x39)
/**
 *  The pointer to base address of registers of PortB
 */
#define PORTB_BASE_PTR		((Dio_MapPtr)0x36)
/**
 *  The pointer to base address of registers of PortC
 */
#define PORTC_BASE_PTR		((Dio_MapPtr)0x33)
/**
 *  The pointer to base address of registers of PortD
 */
#define PORTD_BASE_PTR		((Dio_MapPtr)0x30)


#endif
