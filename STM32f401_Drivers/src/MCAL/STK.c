/*
 * STK.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Nada
 */

#include "STK.h"

/* STK base address */
#define STK_BASEADD         0xE000E010

/* Numbers */
#define ZERO                0
#define ONE                 1
#define TWO                 2
#define EIGHT               8

/* to convert seconds to milliseconds */
#define sec_to_ms           1000

/* Min and Max reload value */
#define Min_Reload_Val      0x00000001
#define Max_Reload_Val      0x00FFFFFF


/* Masks */
#define MASK_ONE_BIT        0x00000001
#define MASK_THREE_BITS     0x00000007

/* STK registers */
typedef struct
{
    volatile u32 STK_CTRL;
    volatile u32 STK_LOAD;
    volatile u32 STK_VAL;
    volatile u32 STK_CALIB;
}STK_Regs_t;

STK_Regs_t *STK_Regs = (STK_Regs_t*)STK_BASEADD;

static STK_cbf_t STK_CBFs[CBF_Numbers];

/* APIs Implementation */

void STK_Start(void)
{
    u32 Copy_Reg = STK_Regs->STK_CTRL;
    Copy_Reg &= ~(MASK_THREE_BITS);
    Copy_Reg |= STK_CTRL_CLKSOURCE|STK_CTRL_TICKINT|MASK_ONE_BIT;
    STK_Regs->STK_CTRL = Copy_Reg;
}

void STK_Stop(void)
{
    STK_Regs->STK_CTRL &= ~(MASK_ONE_BIT);
}

void SysTick_Handler(void)
{
    for (u8 iterator = 0; iterator < CBF_Numbers; iterator++)
    {
        if(STK_CBFs[iterator])
        {
            STK_CBFs[iterator]();
        }
    }
}

u8 STK_SetTimeMs(u32 TimeinMs)
{
    u8 ErrorStatus = Ok;
    u32 Frequency = CLK_FREQUENCY;

    if (((STK_Regs->STK_CTRL)>>TWO)&MASK_ONE_BIT)
    {
        Frequency /= EIGHT;
    }

    u32 Reload = (Frequency*TimeinMs)/sec_to_ms - ONE;

    if (Reload < Min_Reload_Val || Reload > Max_Reload_Val)
    {
        ErrorStatus = NotOk;
    }
    else
    {
        STK_Regs->STK_LOAD = Reload;
        STK_Regs->STK_VAL = ZERO;
    }

    return ErrorStatus;
}

u8 STK_SetCallBack(STK_cbf_t CBF, u8 Index)
{
    u8 ErrorStatus = Ok;

    if (Index < ZERO || Index >= CBF_Numbers)
    {
        ErrorStatus = WrongChoice;
    }
    else if (!CBF)
    {
        ErrorStatus = NullPointer;
    }
    else
    {
        STK_CBFs[Index] = CBF;
    }

    return ErrorStatus;
}