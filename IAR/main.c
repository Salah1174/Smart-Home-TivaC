#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "..\Drivers\HAL\RelayMod\Relay.h"
#include "..\Drivers\HAL\BTMod\BTMod.h"
#include "..\Drivers\HAL\LM35\LM35.h"
#include "..\Drivers\HAL\Door\Door.h"
#include "..\Drivers\MCAL\GPIO\GPIO.h"
#include "..\Drivers\HAL\AlarmMod\Alarm.h"
#include "..\Drivers\HAL\PushButton\PushButton.h"
#include "driverlib\sysctl.h"
#include "driverlib\gpio.h"
volatile uint8_t tempStatus = 'C';
volatile uint32_t Temp = 15;

int main(void)
{
  BTMOD_Init();
  Relay_Init();
  LM35_Init();
  DOOR_Init();
  Alarm_Init();
  PushButton_Init();
  char buffer[7];
  bool doorStatus = true;
  bool lampStatus = true;
  while (1)
  {
    PushButton_Action();
    doorStatus = DOOR_Status();
    lampStatus = GPIO_PinRead('F',GPIO_PIN_1);
    sprintf(buffer, "%d %d %c %d\n", doorStatus, Temp, tempStatus,lampStatus);
    BTMOD_SendString(buffer);
    SysCtlDelay(1000000);
  }
}