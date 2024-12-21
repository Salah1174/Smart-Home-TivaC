#include "Door.h"
#include "..\..\MCAL\GPIO\GPIO.h"
#include "driverlib\gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
// #include "tm4c123gh6pm.h"

extern volatile bool doorStatus;

void DOOR_Init(void)
{
    DIO_Init('B', GPIO_PIN_3, GPIO_DIR_MODE_IN);

    GPIOIntDisable(GPIO_PORTB_BASE, GPIO_PIN_3);                  // Disable interrupt for PB3
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_3);                    // Clear any prior interrupt
                                                                  //    GPIOIntRegister(GPIO_PORTB_BASE, DoorIntHandler);             // Register the interrupt handler
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_BOTH_EDGES); // Interrupt on both edges
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_3);                   // Enable interrupt for PB3

    // Enable the interrupt in the NVIC
    IntEnable(17);
}

bool DOOR_Status(void)
{
    // bool doorPreviousStatus = false;
    bool doorCurrentStatus = GPIO_PinRead('B', GPIO_PIN_3);
    return doorCurrentStatus;
}

void DoorIntHandler(void)
{

    // Handle the door status change
    bool doorStatus_Pin = GPIO_PinRead('B', GPIO_PIN_3);
    if (!doorStatus_Pin)
    {
        doorStatus = false;
        SysCtlDelay(1000000);
        // Door is open
    }
    else
    {
        doorStatus = true;
        SysCtlDelay(1000000);
    }

    GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_3); // Clear the interrupt flag
}