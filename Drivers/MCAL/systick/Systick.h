#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stdbool.h>

void SysTick_init(unsigned int reloadvalue);
void SysTick_Enable(void);
void SysTick_Disable(void);
void SysTci_Periodset(uint32_t ui32period);
uint32_t SysTick_PeriodGet(void);
uint32_t SysTick_ValueGet(void);
bool SysTick_Is_time_out(void);





#endif