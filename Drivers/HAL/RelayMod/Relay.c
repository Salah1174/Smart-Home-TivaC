#include <stdbool.h>
#include <stdint.h>
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "driverlib\debug.h"
#include "inc\hw_memmap.h"
#include "..\MCAL\GPIO\GPIO.h"

void Relay_Init()
{
  DIO_Init('F', GPIO_PIN_1, GPIO_DIR_MODE_OUT);
  DIO_Init('F', GPIO_PIN_2, GPIO_DIR_MODE_OUT);
}
