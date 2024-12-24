#include <stdbool.h>
#include <stdint.h>
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "driverlib\debug.h"
#include "inc\hw_memmap.h"
#include "..\MCAL\GPIO\GPIO.h"

void Alarm_Init()
{
  DIO_Init('F', GPIO_PIN_3, GPIO_DIR_MODE_OUT);
}
void Alarm_On()
{
  DIO_Write('F', GPIO_PIN_3, 1);
}

void Alarm_Off()
{
  DIO_Write('F', GPIO_PIN_3, 0);
}
