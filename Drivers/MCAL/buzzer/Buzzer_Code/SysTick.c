#include "SysTick.h"
#include "ADC.h"
#include "buzzer.h"
// Pointer to the SysTick callback function
static uint32_t (*SysTick_Callback)(void) = 0;

// Initialize SysTick Timer (interrupt mode)
void SysTick_InitInterrupt(uint32_t reloadValue, uint32_t (*callback)(void))
{
    NVIC_ST_CTRL_R = 0;             // Disable SysTick during setup
    NVIC_ST_RELOAD_R = reloadValue; // Set reload value
    NVIC_ST_CURRENT_R = 0;          // Clear current timer value
    SysTick_Callback = callback;    // Register the callback function
    NVIC_ST_CTRL_R = 0x07;          // Enable SysTick with system clock and interrupt
}

// Enable SysTick Timer
void SysTick_Enable(void)
{
    NVIC_ST_CTRL_R |= 0x05; // Enable SysTick
}

// Disable SysTick Timer
void SysTick_Disable(void)
{
    NVIC_ST_CTRL_R &= ~0x01; // Disable SysTick
}

// Set the SysTick Timer period
void SysTick_PeriodSet(uint32_t ui32Period)
{
    NVIC_ST_RELOAD_R = ui32Period - 1; // Set the reload value
}

// Get the SysTick Timer period
uint32_t SysTick_PeriodGet(void)
{
    return NVIC_ST_RELOAD_R + 1; // Return reload value
}

// Get the current value of the SysTick Timer
uint32_t SysTick_ValueGet(void)
{
    return NVIC_ST_CURRENT_R; // Return current value
}

// Check if SysTick Timer has timed out
bool SysTick_Is_Time_Out(void)
{
    return (NVIC_ST_CTRL_R & 0x10000) != 0; // Check COUNT flag
}

// SysTick Interrupt Handler
void SysTick_Handler(void)
{
    // uint32_t temp = ADC_ReadTemperature(); // read temperature from ADC

    // if (temp > 30)
    // {
    //     Buzzer_On();
    // }
    // else
    // {
    //     Buzzer_Off();
    // }
}

//*****************************************************************************
//
//! Disables the SysTick counter.
//!
//! This function stops the SysTick counter.  If an interrupt handler has been
//! registered, it is not called until SysTick is restarted.
//!
//! \return None.
//
//*****************************************************************************
void SysTickDisable(void)
{
    //
    // Disable SysTick.
    //
    HWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_ENABLE);
}

//*****************************************************************************
//
//! Disables the SysTick interrupt.
//!
//! This function disables the SysTick interrupt, preventing it from being
//! reflected to the processor.
//!
//! \return None.
//
//*****************************************************************************
void SysTickIntDisable(void)
{
    //
    // Disable the SysTick interrupt.
    //
    HWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_INTEN);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the SysTick interrupt.
//!
//! \param pfnHandler is a pointer to the function to be called when the
//! SysTick interrupt occurs.
//!
//! This function registers the handler to be called when a SysTick interrupt
//! occurs.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void SysTickIntRegister(void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    IntRegister(FAULT_SYSTICK, pfnHandler);

    //
    // Enable the SysTick interrupt.
    //
    HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
}

//*****************************************************************************
//
//! Sets the period of the SysTick counter.
//!
//! \param ui32Period is the number of clock ticks in each period of the
//! SysTick counter and must be between 1 and 16,777,216, inclusive.
//!
//! This function sets the rate at which the SysTick counter wraps, which
//! equates to the number of processor clocks between interrupts.
//!
//! \note Calling this function does not cause the SysTick counter to reload
//! immediately.  If an immediate reload is required, the \b NVIC_ST_CURRENT
//! register must be written.  Any write to this register clears the SysTick
//! counter to 0 and causes a reload with the \e ui32Period supplied here on
//! the next clock after SysTick is enabled.
//!
//! \return None.
//
//*****************************************************************************
void SysTickPeriodSet(uint32_t ui32Period)
{
    //
    // Check the arguments.
    //
    ASSERT((ui32Period > 0) && (ui32Period <= 16777216));

    //
    // Set the period of the SysTick counter.
    //
    HWREG(NVIC_ST_RELOAD) = ui32Period - 1;
}

//*****************************************************************************
//
//! Enables the SysTick interrupt.
//!
//! This function enables the SysTick interrupt, allowing it to be
//! reflected to the processor.
//!
//! \note The SysTick interrupt handler is not required to clear the SysTick
//! interrupt source because it is cleared automatically by the NVIC when the
//! interrupt handler is called.
//!
//! \return None.
//
//*****************************************************************************
void SysTickIntEnable(void)
{
    //
    // Enable the SysTick interrupt.
    //
    HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
}

//*****************************************************************************
//
//! Enables the SysTick counter.
//!
//! This function starts the SysTick counter.  If an interrupt handler has been
//! registered, it is called when the SysTick counter rolls over.
//!
//! \note Calling this function causes the SysTick counter to (re)commence
//! counting from its current value.  The counter is not automatically reloaded
//! with the period as specified in a previous call to SysTickPeriodSet().  If
//! an immediate reload is required, the \b NVIC_ST_CURRENT register must be
//! written to force the reload.  Any write to this register clears the SysTick
//! counter to 0 and causes a reload with the supplied period on the next
//! clock.
//!
//! \return None.
//
//*****************************************************************************
void SysTickEnable(void)
{
    //
    // Enable SysTick.
    //
    HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}