#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "Buzzer.h"

void Buzzer_Init(void) {
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // Enable clock for Port A
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0); 

    dio_init(GPIO_PORTA_BASE, Pin5, 1); 
    dio_writepin(GPIO_PORTA_BASE, Pin5, 0);       // Ensure buzzer starts off
}

void Buzzer_On(void) {
    dio_writepin(GPIO_PORTA_BASE, Pin5, 1); // Turn on the buzzer
}

void Buzzer_Off(void) {
    dio_writepin(GPIO_PORTA_BASE, Pin5, 0); // Turn off the buzzer
}
