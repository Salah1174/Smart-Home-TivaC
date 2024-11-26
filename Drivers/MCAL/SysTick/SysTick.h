#ifndef SYSTICk_H_
#define SYSTICK_H_

#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "NVIC.h"

void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_DeInit(void);
void SysTick_Start(void);
void SysTick_Stop(void);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
extern void SysTick_Handler(void);
extern void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));

#endif
