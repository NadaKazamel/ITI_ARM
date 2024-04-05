/*
 * LED.h
 *
 *  Created on: Mar 5, 2024
 *      Author: Nada
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_

#include "std_types.h"
#include "LED_cfg.h"

/*Led Connection*/
#define LED_Conn_FW         0
#define LED_Conn_RV         1

/*Led Status*/
#define LED_Status_Off      0
#define LED_Status_On       1

/* Error Possibilities */
#define Ok			    0
#define NotOk		    1
#define NullPointer		2
#define WrongChoice     3

typedef struct
{
    void * Port;
    u32 Pin;
    u8 Connection;
    u8 Default_Status;
}LED_cfg_t;

u8 LED_Init(void);

u8 LED_SetStatus(u8 Led, u8 status);


#endif /* HAL_LED_H_ */