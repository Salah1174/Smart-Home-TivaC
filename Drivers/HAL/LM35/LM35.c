#include "LM35.h"
#include "..\..\MCAL\ADC\ADC.h"
#include "..\..\Drivers\MCAL\GPIO\GPIO.h"
#include <stdint.h>
#include <stdbool.h>
//#include "tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
// #include "..\..\Drivers\MCAL\GPIO\GPIO.h"

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
    uint32_t Temp = LM35_Temp();
    if (Temp > 18)
    {
        DIO_Write('F', 0x00000008, 1);
    }
    else
    {
        DIO_Write('F', 0x00000008, 0);
    }
    // bool isOn = GPIO_PinRead('F', 0x00000008);
    // DIO_Write('F', 0x00000008, !isOn);
    SysTickValueGet();
}