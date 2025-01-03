#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

// Function prototypes for polling mode
void SysTick_Enable(void);
void SysTick_Disable(void);
void SysTick_PeriodSet(uint32_t ui32Period);
uint32_t SysTick_PeriodGet(void);
uint32_t SysTick_ValueGet(void);
bool SysTick_Is_Time_Out(void);

// Function prototypes for interrupt mode
void SysTick_InitInterrupt(uint32_t reloadValue, uint32_t (*callback)(void)); // pointer to fn that has void return type and takes no arguments

void SysTickEnable(void);
void SysTickIntEnable(void);
void SysTickPeriodSet(uint32_t ui32Period);
void SysTickIntRegister(void (*pfnHandler)(void));
void SysTickIntDisable(void);
void SysTickDisable(void);
#endif
