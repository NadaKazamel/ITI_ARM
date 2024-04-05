/*
 * STK.h
 *
 *  Created on: Mar 14, 2024
 *      Author: Nada
 */

#ifndef MCAL_STK_H_
#define MCAL_STK_H_

#include "std_types.h"

/* Type of Callback function */
typedef void (*STK_cbf_t) (void);

/* Clock Frequency in Hz */
#define CLK_FREQUENCY				16000000

/* Error Possibilities */
#define Ok				0
#define NotOk			1
#define NullPointer		2
#define WrongChoice		3

/* Clock Source */
#define STK_AHB_8 	            0x00000000 
#define STK_PROCESSOR_CLOCK 	0x00000006
#define STK_CTRL_CLKSOURCE      STK_PROCESSOR_CLOCK

/* SysTick exception request */
#define STK_TICKINT_DIS         0x00000000
#define STK_TICKINT_EN          0x00000002
#define STK_CTRL_TICKINT        STK_TICKINT_EN

/* Number of callback functions that are going to handle the interrupt */
#define CBF_Numbers             3

/* APIs */
void STK_Start(void);
void STK_Stop(void);
void SysTick_Handler(void);
u8 STK_SetTimeMs(u32 Time);
u8 STK_SetCallBack(STK_cbf_t CBF, u8 Index);

#endif /* MCAL_STK_H_ */