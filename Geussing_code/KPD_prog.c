/**********************************************************************/
/**********************************************************************/
/*****************		Author: Alaa		    ***********************/
/*****************		Layer:	HAL			    ***********************/
/*****************		SWC:	KEYPAD		    ***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
/**********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include  "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"


uint8_t  KPD_u8GetPressedKey(void)
{
	/*Initialize the state of keys that not pressed */
	uint8_t Local_u8PressedKey = KPD_NO_PRESSED_KEY ,Local_u8PinState,Local_u8ColumnId,Local_u8RowId;

	/*the value that I want to access the any pressed switch*/
	static uint8_t Local_u8KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARR_VALS;

	/*store the physical connection pins for a columns in array */
	static uint8_t Local_u8KPDColumnArr[COLUMN_NUM] = {KPD_COLUMN0_PIN,
			                                           KPD_COLUMN1_PIN,
			                                           KPD_COLUMN2_PIN,
			                                           KPD_COLUMN3_PIN };

	/*store the physical connection pins for a ROWS in array */
	static uint8_t Local_u8KPDRowArr[ROW_NUM] = {KPD_ROW0_PIN,
			                                     KPD_ROW1_PIN,
			                                     KPD_ROW2_PIN,
			                                     KPD_ROW3_PIN};


	/*Scanning the keypad */
	for( Local_u8ColumnId = 0 ; Local_u8ColumnId < COLUMN_NUM ; Local_u8ColumnId++)
	{
		/* Activate current column */
		DIO_SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnId],DIO_LOW);

		for( Local_u8RowId = 0 ; Local_u8RowId < ROW_NUM ; Local_u8RowId++)
		{
			/* Read the current row */
			DIO_GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowId],&Local_u8PinState);

			/* check if switch is pressed */
			if(DIO_LOW == Local_u8PinState)
			{
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowId][ Local_u8ColumnId] ;

				/* polling (busy waiting ) until the key is released */
				while(DIO_LOW == Local_u8PinState)
				{
					DIO_GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowId],&Local_u8PinState);
				}
				return Local_u8PressedKey;
			}

		}

		/* Deactivate current column */
		DIO_SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnId],DIO_HIGH);

	}


	return Local_u8PressedKey;


}
