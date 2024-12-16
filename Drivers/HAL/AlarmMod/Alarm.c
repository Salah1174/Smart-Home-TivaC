#include <stdbool.h>
#include <stdint.h>
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "driverlib\debug.h"
#include "inc\hw_memmap.h"
#include "..\MCAL\GPIO\GPIO.h"

void Alarm_Init (){
   DIO_Init('B', GPIO_PIN_1 , GPIO_DIR_MODE_OUT);
}
void Alarm_Toggle (){
//   bool on = GPIO_PinRead('B' , GPIO_PIN_1);
    DIO_Write( 'B' , GPIO_PIN_1 , 1);
//   if( on ){
//  }
//  else {
//  }
//  
  SysCtlDelay(10000000);
    DIO_Write( 'B' , GPIO_PIN_1 , 0);
  
}