/*
 * GPIO.h
 *
 *  Created on: Feb 18, 2024
 *      Author: Nada
 */

#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_

#include "std_types.h"

/* Port options */
#define GPIO_A			(void*)0x40020000
#define GPIO_B			(void*)0x40020400
#define GPIO_C			(void*)0x40020800
#define GPIO_D			(void*)0x40020C00
#define GPIO_E			(void*)0x40021000
#define GPIO_H			(void*)0x40021C00

/* Pin options */
typedef enum
{
	GPIO_WrongPin = -1,
	GPIO_Pin0,
	GPIO_Pin1,
	GPIO_Pin2,
	GPIO_Pin3,
	GPIO_Pin4,
	GPIO_Pin5,
	GPIO_Pin6,
	GPIO_Pin7,
	GPIO_Pin8,
	GPIO_Pin9,
	GPIO_Pin10,
	GPIO_Pin11,
	GPIO_Pin12,
	GPIO_Pin13,
	GPIO_Pin14,
	GPIO_Pin15,
	GPIO_NumberOfPins
}GPIO_Pins_t;

/* Configuration Options */
#define GPO_PP			0b00001
#define GPO_PP_PU		0b01001
#define GPO_PP_PD		0b10001

#define GPO_OD			0b00101
#define GPO_OD_PU		0b01101
#define GPO_OD_PD		0b10101

#define AF_PP			0b00010
#define AF_PP_PU		0b01010
#define AF_PP_PD		0b10010

#define AF_OD			0b00110
#define AF_OD_PU		0b01110
#define AF_OD_PD		0b10110

#define IP_F			0b00000
#define IP_PU			0b01000
#define IP_PD			0b10000

/* Speed */
#define GPIO_LOW_SPEED			0
#define GPIO_MED_SPEED			1
#define GPIO_HIGH_SPEED			2
#define GPIO_VERY_HIGH_SPEED	3

/*Output States*/
#define GPIO_LOW	0
#define GPIO_HIGH	1

/* Struct for pin configuration info */
typedef struct
{
    void* Port;
    GPIO_Pins_t Pin;
    u32 Configuration;
    u32 Speed;
}GPIO_PinConfig_t;


/* Error Possibilities */
#define Ok				0
#define NotOk			1
#define NullPointer		2
#define WrongChoice		3

/* APIs */

u8 GPIO_InitPinConfig(GPIO_PinConfig_t *PinCfgr);

u8 GPIO_SetPinStatus(void* Port, GPIO_Pins_t Pin, u8 Status);

u8 GPIO_GetPinStatus(void* Port, GPIO_Pins_t Pin, u8 * Status);

#endif /* MCAL_GPIO_H_ */