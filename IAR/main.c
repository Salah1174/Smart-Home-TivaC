//#include "..\Drivers\MCAL\DIO\DIO.h"
//#include "..\Drivers\MCAL\UART\uart5.h"
#include "..\Drivers\MCAL\UART\uart0.h"
#include "..\Drivers\MCAL\ADC\ADC.h"


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "..\Drivers\MCAL\GPIO\GPIO.h"
//#include "..\Drivers\HAL\RelayMod\Relay.h"
//#include "..\Drivers\HAL\AlarmMod\Alarm.h"

int main(void)
{
  float temperature;
  char buffer[50];
  int Temp_int;
  UART0_Init();
  ADC1_Init();
//    UART5_Init(); // Initialize UART5
//    LED_Init();   // Initialize the LED on PF1
//    unsigned char temp = 0 ;
//    UART5_SendByte(temp);
    //UART5_SendInteger(50);
    uint32_t ADC_Value;
    while (1)
    {
        
      ADC_Value = ADC1_ReadValue();
      float voltage = ((ADC_Value* 3.3)/4095.0);
      if (voltage < 0)
      {
        voltage = 0.0;
      }
//      temperature = voltage *100.0;
//      Temp_int = temperature;
//      voltage = voltage - 0.20;
      sprintf(buffer, "Voltage: %d V\n", voltage);
      UART0_SendString(buffer);
//      UART0_SendInteger(ADC_Value);
//      UART0_SendByte('\n');
//      SysCtlDelay(10000000);
        for (volatile int i = 0; i < 2000000; i++);
    }
    return 0;
}
  //relay , alarm testing
  
//    Relay_Init();
////    DIO_Write('F', GPIO_PIN_3 | GPIO_PIN_2, 0);
////    Alarm_Init();
//    while(1){
//    Relay_Toggle();
//    Relay_Toggle();
//
////      Alarm_Toggle();
////      Alarm_Toggle();
//    }
  
  //gpio testing
  
////  DIO_Init('F', GPIO_PIN_0, GPIO_DIR_MODE_IN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//  DIO_Init('F', GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_DIR_MODE_OUT, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
//   DIO_Write('F', GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_2, 0);
//  while (1){
//    
//      DIO_Write('F', GPIO_PIN_3 | GPIO_PIN_2, 1);
//    SysCtlDelay(5000000);
//    DIO_Write('F', GPIO_PIN_3 | GPIO_PIN_2, 0);
//    SysCtlDelay(5000000);
//  }
    
  //UART testing
      //UART5_SendInteger(50);
//    UART5_SendByte(temp);
//      temp++;
//      UART5_SendByte(temp);
      
//        uint8 receivedChar = UART5_ReceiveByte(); // Receive a character
//
//        if (receivedChar == '1') // If '1' is received
//        {
//            GPIO_PORTF_DATA_REG ^= LED_PIN; // Turn on the LED
//        }
//        else if (receivedChar == '0') // If '0' is received
//        {
//            GPIO_PORTF_DATA_REG &= ~LED_PIN; // Turn off the LED
//        }
