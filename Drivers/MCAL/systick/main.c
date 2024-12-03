#include "systick.h"
#include "DIO.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operations.h"

#define SYSTICK_BASE      (0xE000E010) 
#define SYSTICK_CTRL      *((volatile uint32_t *)(SYSTICK_BASE + 0x00))
#define SYSTICK_LOAD      *((volatile uint32_t *)(SYSTICK_BASE + 0x04))
#define SYSTICK_VAL       *((volatile uint32_t *)(SYSTICK_BASE + 0x08))
#define SYSTICK_CALIB     *((volatile uint32_t *)(SYSTICK_BASE + 0x0C))

static uint32_t period = 0;

void SysTick_Init(uint32_t reloadValue) {
    SYSTICK_CTRL = 0;                 // Disable SysTick during setup
    SYSTICK_LOAD = reloadValue - 1;   // Set reload value
    SYSTICK_VAL = 0;                  // Reset current value
    SysTick_Enable();                 // Enable SysTick
}

void SysTick_Enable(void) {
    SYSTICK_CTRL |= 0x00000007; // Enable SysTick with interrupts and processor clock
}

void SysTick_Disable(void) {
    SYSTICK_CTRL &= ~0x00000001; // Disable SysTick
}

void SysTick_PeriodSet(uint32_t ui32Period) {
    period = ui32Period;
    SysTick_Init(period);
}

uint32_t SysTick_PeriodGet(void) {
    return period;
}

uint32_t SysTick_ValueGet(void) {
    return SYSTICK_VAL; 
}

bool SysTick_Is_Time_Out(void) {
    return (SYSTICK_CTRL & 0x00010000) != 0; // Check COUNTFLAG
}

int main(void) {
    // Initialize GPIO pins for Port F (assuming `dio_init` handles this correctly)
    dio_init('F', Pin1, Output);
    dio_init('F', Pin2, Output);
    dio_init('F', Pin3, Output);
    
    // Initialize SysTick timer with 1-second interval (16 MHz clock)
    SysTick_Init(16000000 - 1); // 1-second delay at 16 MHz clock

    while (1) {
        if (!SysTick_Is_Time_Out()) {
            dio_writepin('F', Pin1, 1);   // Turn on Pin1
            SysTick_Init(16000000 - 1);  // Reset SysTick
        }
        if (!SysTick_Is_Time_Out()) {
            dio_writepin('F', Pin2, 1);   // Turn on Pin2
            SysTick_Init(16000000 - 1);  // Reset SysTick
        }
        if (!SysTick_Is_Time_Out()) {
            dio_writepin('F', Pin3, 1);   // Turn on Pin3
            SysTick_Init(16000000 - 1);  // Reset SysTick
        }
    }
}
