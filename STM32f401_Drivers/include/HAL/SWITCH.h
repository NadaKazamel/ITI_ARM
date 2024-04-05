/*
 * SWITCH.h
 *
 *  Created on: Mar 14, 2024
 *      Author: Nada
 */

#ifndef HAL_SWITCH_H_
#define HAL_SWITCH_H_

#include "std_types.h"
#include "SWITCH_cfg.h"

/* Error Possibilities */
#define Ok				0
#define NotOk			1
#define NullPointer		2
#define WrongChoice		3

/* Switch type */
#define SWITCH_IP_PU			0b01000
#define SWITCH_IP_PD			0b10000

/* Switch Configuration */
typedef struct
{
    void* Port;
    u8 Pin;
    u32 Connection;
}SWITCH_PinConfig_t;

/* APIs */
void SWITCH_Init(void);
u8 SWITCH_getStatus(u8 Switch_Name, u8* Status);

#endif /* HAL_SWITCH_H_ */