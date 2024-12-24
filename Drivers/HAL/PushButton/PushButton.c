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
    static bool lastState = false; // Stores the last stable state of the rocker switch
    bool currentState = GPIO_PinRead('A', GPIO_PIN_3); // Read the current state of the rocker switch

    if (currentState != lastState) // If the state has changed
    {
//        SysCtlDelay(50000); // Debounce delay (adjust this as per your system clock speed)
        currentState = GPIO_PinRead('A', GPIO_PIN_3); // Read the state again to confirm it's stable

        if (currentState != lastState) // Confirm the state change
        {
            lastState = currentState; // Update the last state

            if (!currentState) // If the rocker switch is pressed
            {
                if (GPIO_PinRead('F', GPIO_PIN_1)) // If the LED is ON
                {
                    DIO_Write('F', GPIO_PIN_1, 0); // Turn OFF the LED
                }
                else // If the LED is OFF
                {
                    DIO_Write('F', GPIO_PIN_1, 1); // Turn ON the LED
                }
            }
        }
    }
}
