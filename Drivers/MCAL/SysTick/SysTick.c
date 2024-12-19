#include "SysTick.h"
#include "tm4c123gh6pm.h"
static volatile void (*CallBackNotificationPtr)(void) = NULL_PTR;

/*********************************************************************
*   Service Name: SysTick_Init
*   Sync/Async: Synchronous
*   Reentrancy: reentrant
*   Parameters (in): a_TimeInMilliSeconds - time in ms to generate interrupt
*   Parameters (inout): None
*   Parameters (out): None
*   Return value: None
*   Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts
 **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG &= ~(1<<0);                                    //Disableing the systick timer
    SYSTICK_CURRENT_REG = 0;                                        //Clearing the Current Reg
    SYSTICK_RELOAD_REG = ((a_TimeInMilliSeconds * 16000) - 1);      //Setting the time value for interrupt in Reload Reg
    SYSTICK_CTRL_REG |= 0x7;                                        //Enable = 1 SysTick Enable, INTEN = 1 Interrupt enable
                                                                    //CLK_SRC = 1 System clock 16Mhz
                                                                    //priority bit left as Zeros as 0 priority
    Enable_Exceptions();                                            //Enabling IRQ
}

/*********************************************************************
*   Service Name: SysTick_DeInit
*   Sync/Async: Synchronous
*   Reentrancy: reentrant
*   Parameters (in): None
*   Parameters (inout): None
*   Parameters (out): None
*   Return value: None
*   Description: Function to De-initialize the SysTick Timer
 **********************************************************************/
void SysTick_DeInit(void){
    SYSTICK_CTRL_REG = 0;                                           //Clearing SysTick Registers
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_RELOAD_REG = 0;
}

/*********************************************************************
*   Service Name: SysTick_Start
*   Sync/Async: Synchronous
*   Reentrancy: reentrant
*   Parameters (in): a_TimeInMilliSeconds - time in ms to generate interrupt
*   Parameters (inout): None
*   Parameters (out): None
*   Return value: None
*   Description: Start/Resume the SysTick timer
 **********************************************************************/
void SysTick_Start(void){
    SYSTICK_CTRL_REG |= (1<<0);                                     //Enable bit = 1
}

/*********************************************************************
*   Service Name: SysTick_Stop
*   Sync/Async: Synchronous
*   Reentrancy: reentrant
*   Parameters (in): a_TimeInMilliSeconds - time in ms to generate interrupt
*   Parameters (inout): None
*   Parameters (out): None
*   Return value: None
*   Description: Stops the SysTick timer
 **********************************************************************/
void SysTick_Stop(void){
    SYSTICK_CTRL_REG &= ~(1<<0);                                    //Enable bit = 0
}

/*********************************************************************
*   Service Name: SysTick_StartBusyWait
*   Sync/Async: Synchronous
*   Reentrancy: reentrant
*   Parameters (in): a_TimeInMilliSeconds - time in ms to busy wait (polling)
*   Parameters (inout): None
*   Parameters (out): None
*   Return value: None
*   Description: Initialize the SysTick timer with the specified time in milliseconds using polling and stops the timer at the end
 **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG &= ~(1<<0);                                    //Disableing the systick timer
    SYSTICK_CURRENT_REG = 0;                                        //Clearing the Current Reg
    SYSTICK_RELOAD_REG = ((a_TimeInMilliSeconds * 16000) - 1);      //Setting the time value for interrupt in Reload Reg
    SYSTICK_CTRL_REG |= 0x5;                                        //CLk_SRC = 1 sys clock, Enable = 1 timer enabled
    while(!(SYSTICK_CTRL_REG & (1<<16)));                           //wait until the count flag is set
    SysTick_DeInit();                                               //DeInitliazing the Systick timer
}

/*********************************************************************
*   Service Name: SysTick_Handler
*   Sync/Async: Synchronous
*   Reentrancy: reentrant
*   Parameters (in): None
*   Parameters (inout): None
*   Parameters (out): None
*   Return value: None
*   Description: Handler for SysTick interrupt use to call the call-back function
 **********************************************************************/
extern void SysTick_Handler(void){
    if(CallBackNotificationPtr != NULL_PTR){
        (*CallBackNotificationPtr)();
    }
}

/*********************************************************************
*   Service Name: SysTick_SetCallBack
*   Sync/Async: Synchronous
*   Reentrancy: reentrant
*   Parameters (in): pointer to function address to be executed
*   Parameters (inout): None
*   Parameters (out): None
*   Return value: None
*   Description: Start/Resume the SysTick timer
 **********************************************************************/
extern void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
    CallBackNotificationPtr = Ptr2Func;
}
