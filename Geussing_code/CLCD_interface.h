/***************************************************************************************************************************/
/***************************************************************************************************************************/
/*************************************  Author : Alaa Abdelrahman         **************************************************/
/*************************************  Layer  : HAL                     **************************************************/
/*************************************  SWC    : CLCD       		          **************************************************/
/*************************************  Version: 1.0			          **************************************************/
/***************************************************************************************************************************/
/***************************************************************************************************************************/

#ifndef _CLCD_INTERFACE_H_
#define _CLCD_INTERFACE_H_



/*********************************************************************
* Function : CLCD_voidSend8BitCommand(uint8_t Copy_u8Command)
*//**
* \b Description: it is helper function used to send command when LCD in 8 bit mode
*
* @param : command that sent to LCD
* @return void
*
****************************************************************************************/

static void CLCD_voidSend8BitCommand(uint8_t Copy_u8Command);

/*********************************************************************
* Function : CLCD_voidSend8BitData(uint8_t Copy_u8Data)
*//**
* \b Description: it is helper function used to send Data when LCD in 8 bit mode
*
* @param : data that sent to LCD
* @return void
*
****************************************************************************************/
static void CLCD_voidSend8BitData(uint8_t Copy_u8Data);

/**************************************************************************************
* Function : CLCD_voidSend4BitCommand(uint8_t Copy_u8Command)
*//**
* \b Description: it is helper function used to send Command  when LCD in 4 bit mode
*
* @param : command that sent to LCD
* @return void
*
****************************************************************************************/

static void CLCD_voidSend4BitCommand(uint8_t Copy_u8Command);

/**************************************************************************************
* Function : CLCD_voidSend4BitData(uint8_t Copy_u8Data)
*//**
* \b Description: it is helper function used to send Data  when LCD in 4 bit mode
*
* @param : data that sent to LCD
* @return void
*
****************************************************************************************/

static void CLCD_voidSend4BitData(uint8_t Copy_u8Data);

/**************************************************************************************
* Function : CLCD_voidSendData(uint8_t Copy_u8Data);
*//**
* \b Description:  used to send data to LCD in both mode 4bit and 8bit
*
* @param : Data that sent to LCD
* @return void
*
****************************************************************************************/

void CLCD_voidSendData(uint8_t Copy_u8Data);

/**************************************************************************************
* Function : CLCD_voidSendCmd(uint8_t Copy_u8Data);
*//**
* \b Description:  used to send data to LCD in both mode 4bit and 8bit
*
* @param : command that sent to LCD
* @return void
*
****************************************************************************************/
void CLCD_voidSendCmd(uint8_t Copy_u8Data);

/*********************************************************************
* Function : CLCD_voidInit()
*//**
* \b Description:
*
* This function is used to initialize LCD based on the configuration in config.h
* initialize mode 4bit or 8bit and lines and grids for LCD
*
*
*PRE-CONDITION: Configuration must set and be suitable for each mode  <br>
*
*
* POST-CONDITION: LCD was configured
*
* @param :  void
*
* @return void
**************************************************************************************************************************/
void CLCD_voidInit(void);

/*********************************************************************
* Function : CLCD_voidSendString(const char* Copy_pcString)
*//**
* \b Description: write string on LCD
*
*PRE-CONDITION: Pointer to string must initialize nit null  <br>
*
* POST-CONDITION: String was written
*
* @param :  pointer to string
*
* @return void
**************************************************************************************************************************/

void CLCD_voidSendString(const char* Copy_pcString);

/*********************************************************************
* Function : CLCD_voidGoToXY(uint8_t Copy_u8XPos,uint8_t Copy_u8YPos)
*//**
* \b Description: move the cursor in LCD to write
*
*PRE-CONDITION: x , y are in range of LCD   <br>
*
* POST-CONDITION: cursor was move to desire position
*
* @param :  x position and y position
*
* @return void
**************************************************************************************************************************/

void CLCD_voidGoToXY(uint8_t Copy_u8XPos,uint8_t Copy_u8YPos);

/*********************************************************************
* Function : CLCD_voidSendNumber(uint32 Copy_u8Data);
*//**
* \b Description: write numbers on LCD
*
* @param :  number
*
* @return void
**************************************************************************************************************************/

void CLCD_voidSendNumber(uint32 Copy_u8Data);

/*********************************************************************
* Function : ClCD_voidWriteSpecialCharacter
*//**
* \b Description: write special character on lcd and use in draw shapes in it
*

*
* @param :  pattern array ,number of pattern and  position
*
* @return void
**************************************************************************************************************************/

void ClCD_voidWriteSpecialCharacter(uint8_t * Copy_pu8Pattern,uint8_t Copy_u8PatternNumber, uint8_t Copy_u8Xpos, uint8_t Copy_u8Ypos);



void CLCD_Clear();
#endif
