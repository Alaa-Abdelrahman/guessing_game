#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_



typedef  unsigned char            uint8_t;
typedef  signed char              sint8_t;
typedef  unsigned short  int      uint16;
typedef  signed short int         sint16_t;
typedef  unsigned  int            uint32;
typedef  unsigned long long int   uint64_t;
typedef  float                    sfloat32_t;
typedef  double                   sfloat64_t;

/**
 * indicate the error that may happen in the driver
 */
typedef enum {
	PIN_NOT_FOUND,   		/**<the pin that passed to function not defined in DioPin_t enumeration*/
	PORT_NOT_FOUND,			/**<the port that passed to function not defined in DioPort_t enumeration*/
	WRONG_CONNECTION,		/**<the connection that passed to function not defined in SwConnection_t enumeration*/
	MODE_NOT_AVALIABLE,     /**<error due to pass mode  not defined to function */
    STATE_NOT_AVALIABLE,    /**<error due to pass state  defined toin function */
	NULLPTR,                /**<Passed a pointer to function which is null */
	INT_REQ_LINE_NOT_FOUND, /**<interrupt request line is wrong */
	INT_SENSE_CONTROL,      /**<sense control is not found */
	WRONG_MODE,             /**< Mode that you choose is wrong */
	ERROR_STATE,
	DONE                    /**<If everything is ok */

}ErrorState_t;

#define NULL    0

#endif
