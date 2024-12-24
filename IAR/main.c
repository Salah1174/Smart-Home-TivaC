<<<<<<< HEAD
#include <stdint.h>
#include "..\Drivers\MCAL\ADC\tm4c123gh6pm.h"

#define red   (1 << 1)
#define blue  (1 << 2)
#define green (1 << 3)

// Function Prototypes
void UART0_Init(void);
void UART0_TransmitChar(char c);
void UART0_TransmitString(const char *str);
void GPIO_Init(void);
void UART0_Handler(void);

// Global Variables
volatile char received_char = 0;

int main(void) {
    UART0_Init();      // Initialize UART0
    GPIO_Init();       // Initialize GPIO for LEDs
    GPIO_PORTF_DATA_R = red;
    GPIO_PORTF_DATA_R = blue;
                
    UART0_TransmitString("Hello from TM4C123GH6PM with Interrupts!\r\n");
    
    while (1) {
        // Check if a new character is received
        if (received_char != 0) {
            char c = received_char;
	    UART0_TransmitChar(c);
            received_char = 0; // Clear the received character
            
            // Control the LEDs based on received character
            switch (c) {
            case 'r':
                GPIO_PORTF_DATA_R = red;
                break;
            case 'b':
                GPIO_PORTF_DATA_R = blue;
                break;
            case 'g':
                GPIO_PORTF_DATA_R = green;
                break;
            case 'x':
                GPIO_PORTF_DATA_R = 0x00;
                break;
            case 'w':
                GPIO_PORTF_DATA_R = red | blue | green;
                break;
            default:
                break;
            }
        }
        else
        {
          UART0_TransmitString("Hello from TM4C123GH6PM with Interrupts!\r\n");
        }
    }
}

void UART0_Init(void) {
    SYSCTL_RCGCUART_R |= (1 << 0); // Enable clock for UART0
    SYSCTL_RCGCGPIO_R |= (1 << 0); // Enable clock for GPIOA
    while ((SYSCTL_PRUART_R & (1 << 0)) == 0);
    while ((SYSCTL_PRGPIO_R & (1 << 0)) == 0);
    
    GPIO_PORTA_AFSEL_R |= (1 << 0) | (1 << 1);
    GPIO_PORTA_PCTL_R &= ~0xFF;
    GPIO_PORTA_PCTL_R |= (1 << 0) | (1 << 4);
    GPIO_PORTA_DEN_R |= (1 << 0) | (1 << 1);
    GPIO_PORTA_AMSEL_R &= ~((1 << 0) | (1 << 1));
    
    UART0_CTL_R &= ~(1 << 0); // Disable UART0
    UART0_IBRD_R = 104;       // Integer part for 9600 baud
    UART0_FBRD_R = 11;        // Fractional part for 9600 baud
    UART0_LCRH_R = (0x3 << 5); // 8-bit word length, no parity, 1 stop bit
    UART0_CC_R = 0x0;         // Use system clock
    UART0_IM_R |= (1 << 4);   // Enable RX interrupt
    NVIC_EN0_R |= (1 << 5);   // Enable IRQ5 for UART0 in NVIC
    UART0_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9); // Enable UART0, Tx, Rx
}

void GPIO_Init(void) {
    SYSCTL_RCGCGPIO_R |= (1 << 5); // Enable clock for GPIOF
    while ((SYSCTL_PRGPIO_R & (1 << 5)) == 0);
    
    GPIO_PORTF_DIR_R |= red | blue | green; // Set LEDs as outputs
    GPIO_PORTF_DEN_R |= red | blue | green; // Enable digital function
}

// Interrupt Service Routine for UART0
void UART0_Handler(void) {
    if (UART0_MIS_R & (1 << 4)) { // Check if RX interrupt occurred
        received_char = (char)(UART0_DR_R & 0xFF); // Read the received character
        UART0_ICR_R |= (1 << 4); // Clear RX interrupt flag
    }
}

void UART0_TransmitChar(char c) {
    while ((UART0_FR_R & (1 << 5)) != 0); // Wait until the transmit FIFO is not full
    UART0_DR_R = c; // Write the character to the data register
}

void UART0_TransmitString(const char *str) {
    while (*str) {
        UART0_TransmitChar(*str++);
    }
=======
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
>>>>>>> 78f96b5091bc4727df6e37a9bc1ea43169fbc9de
}