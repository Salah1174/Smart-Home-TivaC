#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "..\Drivers\HAL\RelayMod\Relay.h"
#include "..\Drivers\HAL\BTMod\BTMod.h"
#include "..\Drivers\HAL\LM35\LM35.h"
#include "..\Drivers\HAL\Door\Door.h"
#include "..\Drivers\MCAL\GPIO\GPIO.h"
#include "..\Drivers\HAL\AlarmMod\Alarm.h"
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"

// #include "tm4c123gh6pm.h"

volatile uint8_t tempStatus = 'C';
volatile uint32_t Temp = 0;

int main(void)
{
  BTMOD_Init();
  DIO_Init('F', GPIO_PIN_3, GPIO_DIR_MODE_OUT);
  //  DIO_Write('F',GPIO_PIN_1,1);
  Relay_Init();
  LM35_Init();
  DOOR_Init();
  Alarm_Init();
  char buffer[5];
  bool doorStatus;
  // uint8_t tempStatus = 'C';
  // uint32_t Temp_int;

  while (1)
  {
    doorStatus = DOOR_Status();
    // Temp = LM35_Temp();
    sprintf(buffer, "%d %d %c\n", doorStatus, Temp, tempStatus);
    BTMOD_SendString(buffer);
    SysCtlDelay(1000000);
  }
}