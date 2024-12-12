#include "SysTick.h"
#include "buzzer.h"
#include "ADC.h"




int main(void) {

    // Initialize SysTick with interrupt mode and 1-second interval
    // Using a 16 MHz clock, 1 second corresponds to 16,000,000 cycles
    SysTick_InitInterrupt(16000000, ADC_ReadTemperature); //now each 1 second, interrupt occurs and we chekc temperature reading to act accordingly 
    
    Buzzer_Init();
    ADC_Init();              
    UART_Init();
    
    IntMasterEnable();

    // Main loop
    while (1) {
       
    }
}