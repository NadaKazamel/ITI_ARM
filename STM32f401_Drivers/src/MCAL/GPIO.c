/*
 * GPIO.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Nada
 */

#include <GPIO.h>

/* GPIO Registers */
typedef struct{
	volatile u32 GPIO_MODER;
	volatile u32 GPIO_OTYPER;
	volatile u32 GPIO_OSPEEDER;
	volatile u32 GPIO_PUPDR;
	volatile u32 GPIO_IDR;
	volatile u32 GPIO_ODR;
	volatile u32 GPIO_BSRR;
	volatile u32 GPIO_LCKR;
	volatile u32 GPIO_AFRL;
	volatile u32 GPIO_AFRH;
}GPIO_Regs_t;

/*Shifting*/
#define SHIFT_FOR_OTYPE		2
#define SHIFT_FOR_PUPDR		3

/*Masks to get bits*/
#define MASK_ONE_BIT		0x00000001
#define MASK_TWO_BITS		0x00000003
#define ONE_BIT				1
#define TWO_BITS			2
#define SET					1


u8 GPIO_InitPinConfig(GPIO_PinConfig_t *PinCfgr)
{
	u8 ErrorStatus = Ok;

	u32 Local_CopyReg = 0;

	if(PinCfgr->Port == NULL||(PinCfgr->Pin < GPIO_Pin0)||(PinCfgr->Pin > GPIO_Pin15))
	{
		ErrorStatus = NotOk;
	}

	else
	{
		Local_CopyReg = ((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_MODER;
		Local_CopyReg &= ~(MASK_TWO_BITS<<((PinCfgr->Pin)*TWO_BITS));
		Local_CopyReg |= (((PinCfgr->Configuration)&MASK_TWO_BITS)<<((PinCfgr->Pin)*TWO_BITS));
		((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_MODER = Local_CopyReg;

		Local_CopyReg = ((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_OTYPER;
		Local_CopyReg &= ~(MASK_ONE_BIT<<(PinCfgr->Pin));
		Local_CopyReg |= ((((PinCfgr->Configuration)>>SHIFT_FOR_OTYPE)&MASK_ONE_BIT)<<(PinCfgr->Pin));
		((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_OTYPER = Local_CopyReg;

		Local_CopyReg = ((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_PUPDR;
		Local_CopyReg &= ~(MASK_TWO_BITS<<((PinCfgr->Pin)*TWO_BITS));
		Local_CopyReg |= ((((PinCfgr->Configuration)>>SHIFT_FOR_PUPDR)&MASK_TWO_BITS)<<((PinCfgr->Pin)*TWO_BITS));
		((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_PUPDR = Local_CopyReg;

		Local_CopyReg = ((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_OSPEEDER;
		Local_CopyReg &= ~(MASK_TWO_BITS<<((PinCfgr->Pin)*TWO_BITS));
		Local_CopyReg |= ((PinCfgr->Speed)<<((PinCfgr->Pin)*TWO_BITS));
		((GPIO_Regs_t*)(PinCfgr->Port))->GPIO_OSPEEDER = Local_CopyReg;

	}

	return ErrorStatus;
}

u8 GPIO_SetPinStatus(void* Port, GPIO_Pins_t Pin, u8 Status)
{
	u8 ErrorStatus = Ok;

	if(Port == NULL||(Pin < GPIO_Pin0)||(Pin > GPIO_Pin15))
	{
		ErrorStatus = NotOk;
	}

	else
	{
		switch (Status)
		{
			case GPIO_LOW:
				((GPIO_Regs_t*)Port)->GPIO_BSRR |= (SET<<(Pin+GPIO_NumberOfPins));
				break;
			case GPIO_HIGH:
				((GPIO_Regs_t*)Port)->GPIO_BSRR |= (SET<<Pin);
				break;
			default:
				ErrorStatus = NotOk;
				break;
		}
	}

	return ErrorStatus;
}

u8 GPIO_GetPinStatus(void* Port, GPIO_Pins_t Pin, u8 * Status)
{
	u8 ErrorStatus = Ok;

	if(Port == NULL||(Pin < GPIO_Pin0)||(Pin > GPIO_Pin15)||Status == NULL)
	{
		ErrorStatus = NotOk;
	}

	else
	{
		*Status = (((((GPIO_Regs_t*)Port)->GPIO_IDR)>>Pin) & MASK_ONE_BIT);
	}

	return ErrorStatus;
}