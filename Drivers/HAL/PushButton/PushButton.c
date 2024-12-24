#include <stdint.h>
#include <stdbool.h>
#include "..\..\MCAL\GPIO\GPIO.h" 
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "PushButton.h"

#define DEBOUNCE_DELAY_MS 50

void PushButton_Init()
{
    DIO_Init('A', GPIO_PIN_3, GPIO_DIR_MODE_IN);
}

void PushButton_Action(void)
{
if (!GPIO_PinRead('A', GPIO_PIN_3) && GPIO_PinRead('F', GPIO_PIN_1))
    {
      DIO_Write('F', GPIO_PIN_1, 0);
    }
    else if (!GPIO_PinRead('A', GPIO_PIN_3) && !GPIO_PinRead('F', GPIO_PIN_1))
    {
      DIO_Write('F', GPIO_PIN_1, 1);
    }
    SysCtlDelay(50000);
}