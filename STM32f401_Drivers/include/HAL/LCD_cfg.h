/*
 * LCD_cfg.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Nada
 */

#ifndef HAL_LCD_CFG_H_
#define HAL_LCD_CFG_H_

#include "std_types.h"

/* LCD mode */
#define	LCD_FOUR_BIT_MODE	0x00
#define LCD_EIGHT_BIT_MODE	0x10
#define LCD_MODE			LCD_EIGHT_BIT_MODE

/* LCD number of lines */
#define LCD_ONE_LINE	0x00
#define LCD_TWO_LINES	0x08
#define LCD_LINES		LCD_TWO_LINES

/* LCD font size */
#define LCD_NORMAL_FONT	0x00
#define LCD_LARGE_FONT	0x04
#define LCD_FONT		LCD_NORMAL_FONT

/* LCD display mode */
#define LCD_DISPLAY_OFF	0x00
#define LCD_DISPLAY_ON	0x04
#define LCD_DISPLAY		LCD_DISPLAY_ON

/* LCD Display shift */
#define SHIFT_DSPLY_OFF	0x00
#define	SHIFT_DSPLY_ON	0x01	
#define LCD_SHIFT_DSPLY	SHIFT_DSPLY_OFF

/* LCD cursor shift */
#define	LCD_SHIFT_LEFT	0x00
#define	LCD_SHIFT_RIGHT	0x02
#define LCD_SHIFT_CRSR	LCD_SHIFT_RIGHT

/* LCD cursor display */
#define	LCD_CURSOR_OFF	0x00
#define LCD_CURSOR_ON	0x02
#define LCD_CURSOR		LCD_CURSOR_ON

/* LCD cursor blinking */
#define	LCD_CURSOR_BLINKING_OFF	0x00
#define LCD_CURSOR_BLINKING_ON	0x01
#define LCD_CURSOR_BLINKING		LCD_CURSOR_BLINKING_OFF

/* LCD shifting both display and cursor */
#define CURSOR_LEFT				0x10
#define CURSOR_RIGHT			0x14
#define CURSOR_DSPLY_LEFT		0x18
#define CURSOR_DSPLY_RIGHT		0x1C

/* LCD return cursor home */
#define RETURN_CRSR_HOME		0x02

/* LCD Pins */
typedef enum 
{
	RS,
	RW,
	EN,
    D0,
	D1,
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
    LCD_Pins 
}LCD_Pins_t;

/* LCD Pins details */
typedef struct
{
	void* Port;
	u32 Pin;
}LCD_Config_t;

#endif /* HAL_LCD_CFG_H_ */