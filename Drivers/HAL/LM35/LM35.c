#include <stdint.h>
#include <stdbool.h>
#include "LM35.h"
#include "..\..\MCAL\ADC\ADC.h"
#include "..\..\Drivers\MCAL\GPIO\GPIO.h"
#include "..\..\Drivers\HAL\AlarmMod\Alarm.h"
#include "..\..\Drivers\HAL\BTMod\BTMod.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

extern volatile uint8_t tempStatus;
extern volatile uint32_t Temp;
// #include "..\..\Drivers\MCAL\GPIO\GPIO.h"
// #include "tm4c123gh6pm.h"

void LM35_Init(void)
{
    ADC1_Init();
    SysTick_Delay_1Sec();
}

uint32_t LM35_Temp(void)
{
    uint32_t ADC_Value = ADC1_ReadValue();
    float Temp_f = ((ADC_Value * 3.3) / 4095.0) * 100;
    return (uint32_t)Temp_f;
}

void LM35_Handler()
{
    Temp = LM35_Temp();
    if (Temp >= 0)
    {
        Alarm_On();
        tempStatus = 'H';
        SysCtlDelay(4000000);
        // BTMOD_SendChar(tempStatus);
    }
    else
    {
        Alarm_Off();
        tempStatus = 'C';
        SysCtlDelay(4000000);
        // BTMOD_SendChar('C');
    }
    SysTickValueGet();
}