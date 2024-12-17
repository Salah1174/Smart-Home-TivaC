//#include "..\Drivers\MCAL\DIO\DIO.h"
#include "..\Drivers\MCAL\UART\uart5.h"
//#include "..\Drivers\MCAL\UART\uart0.h"
#include "..\Drivers\MCAL\ADC\ADC.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "..\Drivers\MCAL\GPIO\GPIO.h"
//#include "..\Drivers\HAL\RelayMod\Relay.h"
#include "..\Drivers\HAL\AlarmMod\Alarm.h"



int main(void)
{
    Alarm_Init();
    ADC1_Init();
    UART5_Init(); // Initialize UART5
    DIO_Init('F',GPIO_PIN_4,GPIO_DIR_MODE_IN);
    DIO_Init('F',GPIO_PIN_0,GPIO_DIR_MODE_IN);
    DIO_Init('F',GPIO_PIN_1,GPIO_DIR_MODE_OUT);
    DIO_Init('F',GPIO_PIN_2,GPIO_DIR_MODE_OUT);
    uint32_t ADC_Value;
    float temperature;
    uint32_t Temp_int = 0;
    char buffer[5];
    DIO_Init('B',GPIO_PIN_3,GPIO_DIR_MODE_IN);
    DIO_Write('F',GPIO_PIN_2,0);    
    bool isDoorOpened = 0 ;
    bool UARTCon = 0;
    while (1)
    {        
      isDoorOpened = GPIO_PinRead('B',GPIO_INT_PIN_3);
      
      for (volatile int i = 0; i < 1000000; i++);
      ADC_Value = ADC1_ReadValue();
      float voltage = ((ADC_Value* 3.3)/4095.0);
      if (voltage < 0)
      {
        voltage = 0.0;
      }
      
      temperature = voltage *100.0;
      Temp_int = temperature;
      if (Temp_int >= 29)
      {
            Alarm_Toggle();
      }
      
      
      
//      bool on_switch = (GPIO_PinRead('F',GPIO_PIN_4)) ^ (GPIO_PinRead('F',GPIO_PIN_0)); 

      
      
      for (volatile int i = 0; i < 500000; i++);
      
//      if(on_switch){
//        DIO_Write('F',GPIO_PIN_2,1);
//      }
//      bool on_uart=0;
//      if (UART5_ReceiveByte()=='1'){
//      on_uart=1;
//      }
      
      
      
      bool on = GPIO_PinRead('F',GPIO_PIN_1);
      
//      if(UART5_ReceiveByte() == '1')
//      {
//        UARTCon^=1;
//      }
      
//      bool PinStatus = GPIO_PinRead('F',GPIO_PIN_0);
//      
//      if(on&&UARTCon&&PinStatus)
//       {
//         DIO_Write('F',GPIO_PIN_1,0);
//       }//off 
//      else if(!UARTCon && PinStatus)
//       {
//          DIO_Write('F',GPIO_PIN_1,1);
//       }//on
//      else if(UARTCon && !PinStatus)
//        {
//          DIO_Write('F',GPIO_PIN_1,1);
//        }//on
//      else if(!UARTCon && !PinStatus)
//      {
//        DIO_Write('F',GPIO_PIN_1,0);
//      }
//      
        //-> off
      
        if(UART5_ReceiveByte()=='1')
        {
          on = !on;
          DIO_Write('F',GPIO_PIN_1,on);
        }
        
         sprintf(buffer, "%d %d\n",isDoorOpened,Temp_int);
         UART5_SendString(buffer);
         for (volatile int i = 0; i < 500000; i++);
          
        
        
//      if(on)
//        {
//            on = !(on);
//          DIO_Write('F',GPIO_PIN_1,on);       
//        }
//      else
//      {
//        
//      }
//      
      
      
      for (volatile int i = 0; i < 500000; i++);

    }
    
    
    return 0;
    
    //    DIO_Init('F',GPIO_PIN_4,GPIO_DIR_MODE_IN);
//    DIO_Init('F',GPIO_PIN_0,GPIO_DIR_MODE_IN);
//    DIO_Init('F',GPIO_PIN_1,GPIO_DIR_MODE_OUT);
//    DIO_Init('F',GPIO_PIN_2,GPIO_DIR_MODE_OUT);
//    DIO_Write('F',GPIO_PIN_2,0); 
//    bool on_switch4 = GPIO_PinRead('F',GPIO_PIN_4);
//    bool on_switch0 = GPIO_PinRead('F',GPIO_PIN_0);
////    for (volatile int i = 0; i < 500000; i++);
//      if(on_switch4 | on_switch0){
////        on_switch=!on_switch;
//        DIO_Write('F',GPIO_PIN_2,1);
//      }
 
}

//    
    
    // Turn on the LED
//  else {
//        DIO_Write( 'F' , GPIO_PIN_1 , 1);
//  
//      SysCtlDelay(5000000);
//       DIO_Write('F',1,0);
//      
//      sprintf(buffer, "Temperature: %d V\n", Temp_int);
//      UART5_SendString(buffer);
//        for (volatile int i = 0; i < 2000000; i++);

//relay , alarm testing
  
//    Relay_Init();
////    DIO_Write('F', GPIO_PIN_3 | GPIO_PIN_2, 0);
////  while(1){
//    Relay_Toggle();
//    Relay_Toggle();
//
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
