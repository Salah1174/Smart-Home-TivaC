#include "Door.h"
#include "..\..\MCAL\GPIO\GPIO.h"
#include "driverlib\gpio.h"

void DOOR_Init(void)
{
    DIO_Init('B', GPIO_PIN_3, GPIO_DIR_MODE_IN);
}

bool DOOR_Status(void)
{
    bool doorPreviousStatus = false;
    bool doorCurrentStatus = GPIO_PinRead('B', GPIO_PIN_3);
    // SysCtlDelay(1000000);
    if (doorCurrentStatus != doorPreviousStatus)
    {
        doorPreviousStatus = doorCurrentStatus;
        return doorCurrentStatus;
    }
     return doorPreviousStatus;
}
