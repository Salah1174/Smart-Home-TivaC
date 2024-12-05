#include "SysTick.h"
#include "ADC.h"
#include "buzzer.h"
// Pointer to the SysTick callback function
static uint32_t (*SysTick_Callback)(void) = 0;


// Initialize SysTick Timer (interrupt mode)
void SysTick_InitInterrupt(uint32_t reloadValue, uint32_t (*callback)(void)) {
    NVIC_ST_CTRL_R = 0;               // Disable SysTick during setup
    NVIC_ST_RELOAD_R = reloadValue;   // Set reload value
    NVIC_ST_CURRENT_R = 0;            // Clear current timer value
    SysTick_Callback = callback;      // Register the callback function
    NVIC_ST_CTRL_R = 0x07;            // Enable SysTick with system clock and interrupt
}

// Enable SysTick Timer
void SysTick_Enable(void) {
    NVIC_ST_CTRL_R |= 0x05;           // Enable SysTick
}

// Disable SysTick Timer
void SysTick_Disable(void) {
    NVIC_ST_CTRL_R &= ~0x01;          // Disable SysTick
}

// Set the SysTick Timer period
void SysTick_PeriodSet(uint32_t ui32Period) {
    NVIC_ST_RELOAD_R = ui32Period - 1; // Set the reload value
}

// Get the SysTick Timer period
uint32_t SysTick_PeriodGet(void) {
    return NVIC_ST_RELOAD_R + 1;      // Return reload value
}

// Get the current value of the SysTick Timer
uint32_t SysTick_ValueGet(void) {
    return NVIC_ST_CURRENT_R;         // Return current value
}

// Check if SysTick Timer has timed out
bool SysTick_Is_Time_Out(void) {
    return (NVIC_ST_CTRL_R & 0x10000) != 0; // Check COUNT flag
}

// SysTick Interrupt Handler
void SysTick_Handler(void) {
    uint32_t temp = ADC_ReadTemperature(); // read temperature from ADC

    if (temp > 30) { 
        Buzzer_On(); 
    } else {
        Buzzer_Off(); 
    }

}
