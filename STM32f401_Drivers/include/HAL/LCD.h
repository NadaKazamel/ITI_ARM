/*
 * LCD.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Nada
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#include "LCD_cfg.h"

/* LCD error status */
typedef enum
{
	LCD_OK,
	LCD_NOK,
	LCD_NullPointer,
	LCD_WrongPosition,
	LCD_WrongCommand,
	LCD_WrongData
}LCD_ErrorStatus_t;

/* Operation types */
typedef enum
{
    None,
    Write,
	WriteNumber,
    Clear,
    SetPosition
}LCD_Operation_Type_t;

/* User's request state */
typedef enum
{
    ReadyForNewReq,
    Busy
}LCD_RequestState;

/* LCD Rows */
typedef enum
{
	Row1,
	Row2
}LCD_Row_t;

/* LCD Column */
typedef enum
{
	Column1,
	Column2,
	Column3,
	Column4,
	Column5,
	Column6,
	Column7,
	Column8,
	Column9,
	Column10,
	Column11,
	Column12,
	Column13,
	Column14,
	Column15,
	Column16
}LCD_Column_t;

/* APIs */

void LCD_InitAsync(void);

LCD_ErrorStatus_t LCD_getStatus (u8 *Status);

LCD_ErrorStatus_t LCD_ClearScreenAsync(void);

LCD_ErrorStatus_t LCD_enumGotoXYAsync(LCD_Row_t Row, LCD_Column_t Column);

LCD_ErrorStatus_t LCD_WriteStringAsync(const u8* String, u8 length);

LCD_ErrorStatus_t LCD_WriteNumberAsync(s32 number);

LCD_ErrorStatus_t LCD_getCurrOperation (u8 *Operation);

#endif /* HAL_LCD_H_ */