#include "SysTick.h"
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "..\..\Drivers\MCAL\GPIO\GPIO.h"


void SysTick_Delay_1Sec(void)
{
    SysTickDisable();
    SysTickIntDisable();
//    SysTickIntRegister(SysTick_Handler);
    SysTickPeriodSet(16000000);
    SysTickIntEnable();
    SysTickEnable();
}

