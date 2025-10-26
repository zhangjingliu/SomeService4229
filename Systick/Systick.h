#ifndef SYSTICK_H
#define SYSTICK_H

#include "hal_data.h"



#define TICKS_PER_SECONDS 1000


typedef struct
{
	volatile uint16_t	year;
	volatile uint8_t	month;
	volatile uint8_t	day;
	volatile uint8_t	hour;
	volatile uint8_t	min;
	volatile uint8_t	second;
} TimeStamp;

extern TimeStamp datetime;
extern volatile uint32_t Timer_1s_Count;

extern volatile uint32_t g_20ms;
extern volatile uint8_t  g_1ms_Falg;

void hal_systick_init(void);

void HAL_Delay(uint32_t Delay);

uint32_t HAL_GetTick(void);


void Calendar_TimeVariable_Set(uint16_t Year,uint8_t Month,uint8_t Day,uint8_t Hour,uint8_t Min,uint8_t Second);
uint8_t BigMonth(uint8_t month);
uint8_t LeapYear(uint16_t year);
void TimeVariable_Processing(void);


#endif

