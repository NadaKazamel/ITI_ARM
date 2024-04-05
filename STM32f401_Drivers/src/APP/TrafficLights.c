/*
 * TrafficLights.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Nada
 */

#include "LED.h"

#define PERIODICITY_SECOND      1

typedef enum
{
    RED,
    YELLOW,
    GREEN
}States_t;

#define RED_LIGHT_ON_TIME           5
#define YELLOW_LIGHT_ON_TIME        3
#define GREEN_LIGHT_ON_TIME         5

void Traffic_Runnable (void)
{
    static u32 seconds = 0;
    seconds += PERIODICITY_SECOND;
    
    static u8 curr_state = RED;
    static u8 prev_state = RED;

    switch (curr_state)
    {
    case RED:
        LED_SetStatus(RED,LED_Status_On);
        LED_SetStatus(YELLOW,LED_Status_Off);
        LED_SetStatus(GREEN,LED_Status_Off);
        if(seconds == RED_LIGHT_ON_TIME)
        {
            seconds = 0;
            curr_state = YELLOW;
            prev_state = RED;
        }
        break;
    
    case YELLOW:
        LED_SetStatus(RED,LED_Status_Off);
        LED_SetStatus(YELLOW,LED_Status_On);
        LED_SetStatus(GREEN,LED_Status_Off);
        if(prev_state == RED && seconds == YELLOW_LIGHT_ON_TIME)
        {
            seconds = 0;
            curr_state = GREEN;
            prev_state = YELLOW;
        }
        else if (prev_state == GREEN && seconds == YELLOW_LIGHT_ON_TIME)
        {
           seconds = 0;
           curr_state = RED;
           prev_state = YELLOW; 
        }
        break;

    case GREEN:
        LED_SetStatus(RED,LED_Status_Off);
        LED_SetStatus(YELLOW,LED_Status_Off);
        LED_SetStatus(GREEN,LED_Status_On);
        if (seconds == GREEN_LIGHT_ON_TIME)
        {
            seconds = 0;
            curr_state = YELLOW;
            prev_state = GREEN;
        }
    default:
        break;
    }
}