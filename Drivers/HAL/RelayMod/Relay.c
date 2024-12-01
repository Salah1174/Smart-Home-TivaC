#include <stdbool.h>
#include <stdint.h>
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "driverlib\debug.h"
#include "inc\hw_memmap.h"
#include "..\MCAL\GPIO\GPIO.h"

void Relay_Init (){
  DIO_Init('B', GPIO_PIN_0 , GPIO_DIR_MODE_OUT, GPIO_STRENGTH_10MA, GPIO_PIN_TYPE_STD);
  
}
void Relay_Toggle (){
  
  bool on = GPIO_PinRead('B' , GPIO_PIN_0);
  if( on ){
    DIO_Write( 'B' , GPIO_PIN_0 , 0);
  }
  else {
    DIO_Write( 'B' , GPIO_PIN_0 , 1);
  }
  
  SysCtlDelay(5000000);
  
}