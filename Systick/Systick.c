#include "Systick.h"



volatile uint32_t g_tick_count = 0;
volatile uint32_t g_20ms = 0;
volatile uint8_t  g_1ms_Falg = 0;

void hal_systick_init(void)
{
    SysTick_Config(SystemCoreClock / TICKS_PER_SECONDS);
}

uint32_t HAL_GetTick(void)
{
  return g_tick_count;
}


void HAL_Delay(uint32_t Delay)
{
  #define HAL_MAX_DELAY      0xFFFFFFFFU

  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait++;
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}






TimeStamp datetime;
volatile uint32_t Timer_1s_Count;

/**
  * @brief Set the time variable of the calendar function
  * @param[in] Year: This parameter is year.
  * @param[in] Month: This parameter is month.
  * @param[in] Day: This parameter is day.
  * @param[in] Hour: This parameter is hour.
  * @param[in] Min: This parameter is min.
  * @param[in] Second: This parameter is second.
  * @retval Non.
  */
void Calendar_TimeVariable_Set(uint16_t Year,uint8_t Month,uint8_t Day,uint8_t Hour,uint8_t Min,uint8_t Second)
{
	datetime.year = Year;
	datetime.month = Month;
	datetime.day = Day;
	datetime.hour = Hour;
	datetime.min = Min;
	datetime.second = Second;
}

/**
  * @brief Judge whether the number of days in the month is 31
  * @param[in] month: This parameter is month.
  * @retval Yes(1) or No(0).
  */
uint8_t BigMonth(uint8_t month)
{
	if(month==1 || month==3 || month==5 || month==7 ||
		month==8 || month==10 || month==12)
		return 1;
	return 0;
}

/**
  * @brief Judge whether the parameter is leap year
  * @param[in] year: This parameter is year.
  * @retval Yes(1) or No(0).
  */
uint8_t LeapYear(uint16_t year)
{
	uint16_t y = year;
	uint16_t remainder;
	
	remainder = y%4;
	if(!remainder)
	{
		remainder = y%100;
		if(remainder) return 1;
		else 
		{
			remainder = y%400;
			if(remainder) return 0;
		}
		return 1;
	}
	return 0;
}

/**
  * @brief Calendar time variable update.
  * @param[in] Non.
  * @retval Non.
  */
void TimeVariable_Processing(void)
{
	uint8_t day;
	day = datetime.day;
	
	datetime.second += 1;
	if(datetime.second>=60) 
	{
		datetime.second -= 60;
		datetime.min++;		
		if(datetime.min>=60)
		{
			datetime.min -= 60;
			datetime.hour++;			
			if(datetime.hour>=24)
			{
				datetime.hour -= 24;
				day = (++datetime.day);				
				if(BigMonth(datetime.month))				
				{
					if(day>=32) 
					{
						datetime.day-=31;		
						day=0xff;
					}
				}
				else
				{
					if(datetime.month==2)
					{
						if(LeapYear(datetime.year))
						{
							if(day>=30) 
							{
								datetime.day-=29;
								day=0xff;
							}
						}
						else if(day>=29) 
						{
							datetime.day-=28;
							day=0xff;
						}
					}
					else if(day>=31) 
					{
						datetime.day-=30;
						day=0xff;
					}
				}
				if(day==0xff)
				{			
					datetime.month++;	
					if(datetime.month>=13)
					{
						datetime.month -= 12;
						datetime.year++;
					}									
				}
				else datetime.day=day;				
			}
		}
	}
	
}


void SysTick_Handler(void)
{
	g_tick_count++;
	g_20ms++;
	if(g_20ms == 1)
	{
		g_20ms = 0;
		g_1ms_Falg = 1;
	}
	//UDS();
}



