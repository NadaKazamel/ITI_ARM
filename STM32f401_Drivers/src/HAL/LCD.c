/*
 * LCD.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Nada
 */

#include "../../include/HAL/LCD.h"
#include "GPIO.h"
#include "LCD_cfg.h"

/* Masks */
#define NO_OF_CTRL_PINS         3
#define MASK_ONE_BIT            1


/* LCD Pins */
extern const LCD_Config_t LCD_Pins_Cfg[LCD_Pins];

u8 FunctionSet = 0x20 | LCD_MODE | LCD_LINES | LCD_FONT;
u8 DisplayCommand = 0x08 | LCD_DISPLAY | LCD_CURSOR | LCD_CURSOR_BLINKING;
u8 ClearCommand = 0x01;
u8 EntryModeSet = 0x04 | LCD_SHIFT_CRSR | LCD_SHIFT_DSPLY;
u8 CursorDisplayShift = 0x10 ;
u8 Location00 = 128;

typedef enum
{
    LCD_Off,
    LCD_Init,
    LCD_Operation
}LCD_State_t;

typedef enum
{
    PowerOn,
    LCD_FunctionSet,
    LCD_Display,
    LCD_Clear,
    LCD_Entry,
    LCD_End,
}LCD_InitStage_t;

typedef enum
{
    EN_Low,
    EN_High
}LCD_ENpinState_t;

typedef struct
{
    u8 X;
    u8 Y;
} LCD_CurPos_t;

/* Global Variables */
static LCD_State_t LCD_State = LCD_Off;
static LCD_InitStage_t InitStage;
static LCD_ENpinState_t LCD_ENpinState = EN_Low;

struct 
{
    const u8 *buffer;                  
    u8 str_length;
    u8 index;
    LCD_RequestState ReqState;
    LCD_Operation_Type_t Op_Type;
    LCD_CurPos_t CurPosition;
}UserReq;

/* Static Functions */

static void LCD_ControlENpin (u8 EN_state)
{
    GPIO_SetPinStatus(LCD_Pins_Cfg[EN].Port,LCD_Pins_Cfg[EN].Pin,EN_state);
}

static void LCD_WriteCommand (u8 command)
{
    if (LCD_ENpinState == EN_Low)
    {
        GPIO_SetPinStatus(LCD_Pins_Cfg[RS].Port,LCD_Pins_Cfg[RS].Pin,GPIO_LOW);
        GPIO_SetPinStatus(LCD_Pins_Cfg[RW].Port,LCD_Pins_Cfg[RW].Pin,GPIO_LOW);

        u8 BitValue;

        for (u8 iterator = 0; iterator < LCD_Pins-NO_OF_CTRL_PINS; iterator++)
        {
            BitValue = (command>>iterator)&MASK_ONE_BIT;
            GPIO_SetPinStatus(LCD_Pins_Cfg[iterator].Port,LCD_Pins_Cfg[iterator].Pin,BitValue);
        }

        LCD_ENpinState = EN_High;
        LCD_ControlENpin(LCD_ENpinState);

    }

    else
    {
        LCD_ENpinState = EN_Low;
        LCD_ControlENpin(LCD_ENpinState);
    }
}

static void LCD_WriteData (u8 command)
{
    if (LCD_ENpinState == EN_Low)
    {
        GPIO_SetPinStatus(LCD_Pins_Cfg[RS].Port,LCD_Pins_Cfg[RS].Pin,GPIO_HIGH);
        GPIO_SetPinStatus(LCD_Pins_Cfg[RW].Port,LCD_Pins_Cfg[RW].Pin,GPIO_LOW);

        u8 BitValue;

        for (u8 iterator = 0; iterator < LCD_Pins-NO_OF_CTRL_PINS; iterator++)
        {
            BitValue = (command>>iterator)&MASK_ONE_BIT;
            GPIO_SetPinStatus(LCD_Pins_Cfg[iterator].Port,LCD_Pins_Cfg[iterator].Pin,BitValue);
        }

        LCD_ENpinState = EN_High;
        LCD_ControlENpin(LCD_ENpinState);
    }

    else
    {
        LCD_ENpinState = EN_Low;
        LCD_ControlENpin(LCD_ENpinState);
    }
}

static void LCD_Write_Proc(void)
{
    if (UserReq.index != UserReq.str_length)
    {
        LCD_WriteData(UserReq.buffer[UserReq.index]);
        if (LCD_ENpinState == EN_Low)
        {
            UserReq.index++;
        }
    }
    else
    {
        UserReq.ReqState = ReadyForNewReq;
        UserReq.Op_Type = None;
    }           
}

static void LCD_WriteNumber_Proc (void)
{
    u8 iterator = 0; 
    if (iterator != UserReq.str_length)
    {
        LCD_WriteData(UserReq.buffer[UserReq.index]);
        if (LCD_ENpinState == EN_Low)
        {
            UserReq.index++;
        }
    }
    else
    {
        UserReq.ReqState = ReadyForNewReq;
        UserReq.Op_Type = None;
    }
}

static void LCD_Clear_Proc (void)
{
    LCD_WriteCommand(ClearCommand);
    if (LCD_ENpinState == EN_Low)
    {
        UserReq.ReqState = ReadyForNewReq;
        UserReq.Op_Type = None;
    }
}

static void LCD_SetPosition_Proc (void)
{
    u8 LocationXY = Location00;
	
    if (UserReq.CurPosition.X == Row1)
	{
		LocationXY += UserReq.CurPosition.Y;	
	}
	else if (UserReq.CurPosition.X == Row2)
	{
		LocationXY += (UserReq.CurPosition.Y + 64);
	}

    LCD_WriteCommand(LocationXY);
    if (LCD_ENpinState == EN_Low)
    {
        UserReq.ReqState = ReadyForNewReq;
        UserReq.Op_Type = None;
    }

}


static LCD_ErrorStatus_t LCD_PowerOn (void)
{
    LCD_ErrorStatus_t ErrorStatus = LCD_OK;

    UserReq.ReqState = Busy;
    
    GPIO_PinConfig_t Pin;
    Pin.Configuration = GPO_PP;
    Pin.Speed = GPIO_HIGH_SPEED;

    for (u32 i = 0; i < LCD_Pins; i++)
    {
        Pin.Port = LCD_Pins_Cfg[i].Port;
        Pin.Pin = LCD_Pins_Cfg[i].Pin;
        ErrorStatus = GPIO_InitPinConfig(&Pin);
    }

    return ErrorStatus;
}

static void LCD_InitManager (void)
{
    switch(InitStage)
    {
        case PowerOn:
            LCD_PowerOn();
            InitStage = LCD_FunctionSet;
            break;
        case LCD_FunctionSet:
            LCD_WriteCommand(FunctionSet);
            if (LCD_ENpinState == EN_Low)
                InitStage = LCD_Display;
            break;
        case LCD_Display:
            LCD_WriteCommand(DisplayCommand);
            if (LCD_ENpinState == EN_Low)
                InitStage = LCD_Clear;
            break;
        case LCD_Clear:
            LCD_WriteCommand(ClearCommand);
            if (LCD_ENpinState == EN_Low)
                InitStage = LCD_Entry;
            break;
        case LCD_Entry:
            LCD_WriteCommand(EntryModeSet);
            if (LCD_ENpinState == EN_Low)
                InitStage = LCD_End;
            break;
        case LCD_End:
            InitStage = LCD_Operation;
            UserReq.ReqState = ReadyForNewReq;
            break;
        default:
            break;
    } 
}


/* Runnable */

void LCD_Runnable(void)
{
    switch(LCD_State)
    {
        case LCD_Off:
            /* Do Nothing */
            break;
        case LCD_Init:
            InitStage = PowerOn; 
            LCD_InitManager();
            break;
        case LCD_Operation:
            if (UserReq.ReqState==ReadyForNewReq)
            {
                switch (UserReq.Op_Type)
                {
                    case Write:
                        LCD_Write_Proc();
                        break;
                    
                    case WriteNumber:
                        LCD_WriteNumber_Proc();
                        break;

                    case Clear:
                        LCD_Clear_Proc();
                        break;

                    case SetPosition:
                        LCD_SetPosition_Proc();
                        break;

                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }   
}

/* APIs Implementations */
void LCD_InitAsync(void)
{
    LCD_State = LCD_Init;
}

LCD_ErrorStatus_t LCD_getStatus (u8 *Status)
{
    LCD_ErrorStatus_t ErrorStatus = LCD_OK;
    
    if (Status == NULL)
    {
        ErrorStatus = LCD_NullPointer;
    }
    else
    {
        *Status = LCD_State;
    }

    return ErrorStatus;
}

LCD_ErrorStatus_t LCD_ClearScreenAsync(void)
{
    LCD_ErrorStatus_t ErrorStatus = LCD_OK;
    if (LCD_State == LCD_Operation && UserReq.ReqState==ReadyForNewReq)
    {
        UserReq.ReqState = Busy;
        UserReq.Op_Type = Clear;
    }
    else
    {
        ErrorStatus = LCD_NOK;
    }

    return ErrorStatus;
}

LCD_ErrorStatus_t LCD_enumGotoXYAsync(LCD_Row_t Row, LCD_Column_t Column)
{
    LCD_ErrorStatus_t ErrorStatus = LCD_OK;
	
	if (Row < Row1 || Row > Row2 || Column < Column1 || Column > Column16)
	{
		ErrorStatus = LCD_WrongData;
	}

    else if (LCD_State == LCD_Operation && UserReq.ReqState==ReadyForNewReq)
    {
        UserReq.ReqState = Busy;
        UserReq.Op_Type = SetPosition;
        UserReq.CurPosition.X = Row;
        UserReq.CurPosition.Y = Column;
    }

    else
    {
        ErrorStatus = LCD_NOK;
    }

    return ErrorStatus;
}

LCD_ErrorStatus_t LCD_WriteStringAsync(const u8* String, u8 length)
{
    LCD_ErrorStatus_t ErrorStatus = LCD_OK;

    if (String == NULL)
    {
        ErrorStatus = LCD_NullPointer;
    }

    else if (LCD_State == LCD_Operation && UserReq.ReqState==ReadyForNewReq)
    {
        UserReq.ReqState = Busy;
        UserReq.Op_Type = Write;
        UserReq.buffer = String;
        UserReq.str_length = length;
        UserReq.index = 0;
    }

    else
    {
        ErrorStatus = LCD_NOK;
    }

    return ErrorStatus;
}

LCD_ErrorStatus_t LCD_WriteNumberAsync(s32 number)
{
    LCD_ErrorStatus_t ErrorStatus = LCD_OK;
    if (LCD_State == LCD_Operation && UserReq.ReqState==ReadyForNewReq)
    {
        u8 counter = 0;
        u8 Iterator = 0;

        if (number == 0)
        {
            counter++;
            UserReq.buffer = (const u8*)"0";
            UserReq.index = 0;
        }

        else
        {
            static u8 Local_number[11];

            for(u8 i = 0; i < 11; i++)
                Local_number[i] = 0;
            
            Iterator = 10;
                                //567893456
            while (number != 0)  //0567893456
            {
                Local_number[Iterator--] = (number%10) + '0';
                number /= 10;
                counter++;
                Iterator--;
            }
            
            if (number < 0)
            {
                Local_number[Iterator] = '-';
                counter++;
                Iterator--;
            }

            UserReq.buffer = Local_number;
            UserReq.index = Iterator+1;
        }

        UserReq.ReqState = Busy;
        UserReq.Op_Type = WriteNumber;
        UserReq.str_length = counter;
    }

    else
    {
        ErrorStatus = LCD_NOK; 
    }

    return ErrorStatus;
}

LCD_ErrorStatus_t LCD_getCurrOperation (u8 *Operation)
{
    LCD_ErrorStatus_t ErrorStatus = LCD_OK;
    
    if (Operation == NULL)
    {
        ErrorStatus = LCD_NullPointer;
    }
    else
    {
        *Operation = UserReq.Op_Type;
    }

    return ErrorStatus;
}