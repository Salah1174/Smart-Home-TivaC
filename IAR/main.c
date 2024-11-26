#include "..\Drivers\MCAL\DIO\DIO.h"
#include "..\Drivers\MCAL\UART\uart5.h"

#define SYSCTL_RCGCGPIO_REG (*((volatile uint32 *)0x400FE608))
#define SYSCTL_PRGPIO_REG   (*((volatile uint32 *)0x400FEA08))

#define GPIO_PORTF_BASE       0x40025000
#define GPIO_PORTF_DEN_REG    (*((volatile uint32 *)(GPIO_PORTF_BASE + 0x51C)))
#define GPIO_PORTF_DIR_REG    (*((volatile uint32 *)(GPIO_PORTF_BASE + 0x400)))
#define GPIO_PORTF_DATA_REG   (*((volatile uint32 *)(GPIO_PORTF_BASE + 0x3FC)))

#define LED_PIN 0x02 // PF1

void LED_Init(void)
{
    SYSCTL_RCGCGPIO_REG |= 0x20; // Enable clock for GPIO Port F
    while (!(SYSCTL_PRGPIO_REG & 0x20))
        ; // Wait until Port F is ready

    GPIO_PORTF_DEN_REG |= LED_PIN; // Enable digital functionality on PF1
    GPIO_PORTF_DIR_REG |= LED_PIN; // Set PF1 as output
}

int main(void)
{
    UART5_Init(); // Initialize UART5
    LED_Init();   // Initialize the LED on PF1

    while (1)
    {
        uint8 receivedChar = UART5_ReceiveByte(); // Receive a character

        if (receivedChar == '1') // If '1' is received
        {
            GPIO_PORTF_DATA_REG |= LED_PIN; // Turn on the LED
        }
        else if (receivedChar == '0') // If '0' is received
        {
            GPIO_PORTF_DATA_REG &= ~LED_PIN; // Turn off the LED
        }
    }
    return 0;
}
