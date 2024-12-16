#include <stdbool.h>
#include <stdint.h>
// #include "types.h"
#include "driverlib\gpio.h"
#include "driverlib\sysctl.h"
#include "driverlib\debug.h"
#include "inc\hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"

uint32_t GetPortBaseAddress(char ui8Port)
{
    switch (ui8Port)
    {
    case 'A':
        return GPIO_PORTA_BASE;
    case 'B':
        return GPIO_PORTB_BASE;
    case 'C':
        return GPIO_PORTC_BASE;
    case 'D':
        return GPIO_PORTD_BASE;
    case 'E':
        return GPIO_PORTE_BASE;
    case 'F':
        return GPIO_PORTF_BASE;
    default:
        return 0;
    }
}

void GetPeripheralAndBaseAddress(char ui8Port, uint32_t *pui32Peripheral, uint32_t *pui32PortBase)
{
    switch (ui8Port)
    {
    case 'A':
        *pui32Peripheral = SYSCTL_PERIPH_GPIOA;
        *pui32PortBase = GPIO_PORTA_BASE;
        break;
    case 'B':
        *pui32Peripheral = SYSCTL_PERIPH_GPIOB;
        *pui32PortBase = GPIO_PORTB_BASE;
        break;
    case 'C':
        *pui32Peripheral = SYSCTL_PERIPH_GPIOC;
        *pui32PortBase = GPIO_PORTC_BASE;
        break;
    case 'D':
        *pui32Peripheral = SYSCTL_PERIPH_GPIOD;
        *pui32PortBase = GPIO_PORTD_BASE;
        break;
    case 'E':
        *pui32Peripheral = SYSCTL_PERIPH_GPIOE;
        *pui32PortBase = GPIO_PORTE_BASE;
        break;
    case 'F':
        *pui32Peripheral = SYSCTL_PERIPH_GPIOF;
        *pui32PortBase = GPIO_PORTF_BASE;
        break;
    default:
        *pui32Peripheral = 0;
        *pui32PortBase = 0;
        break;
    }
}

void DIO_Init(uint8_t ui8Port, uint8_t ui8Pins, uint32_t ui32Direction)
{
    // Enable clock
    uint32_t ui32Peripheral;
    uint32_t ui32Port;
    GetPeripheralAndBaseAddress(ui8Port, &ui32Peripheral, &ui32Port);
    SysCtlPeripheralEnable(ui32Peripheral);
    while (!SysCtlPeripheralReady(ui32Peripheral))
    {
    }

    // unlock ( more ports' special/locked pins needed ? )                                                      //needs to be tested
    if (ui8Port == 'F' && ui8Pins == GPIO_PIN_0)
    {

        // unlock & change into gpio input
        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
        HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;
        // lock again
        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
        HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x00;
        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 );
    }

    //    GPIOUnlockPin(ui32Port, ui8Pins);

    // dir
    GPIODirModeSet(ui32Port, ui8Pins, ui32Direction);

    //    // drive strength and pad type (  GPIO_STRENGTH_2MA and GPIO_PIN_TYPE_STD push-pull for ex
    //    GPIOPadConfigSet(ui32Port, ui8Pins, ui32Strength, ui32PadType);

    // den
    if (ui32Direction == GPIO_DIR_MODE_OUT)
    {
        GPIOPinTypeGPIOOutput(ui32Port, ui8Pins);
    }
    else if (ui32Direction == GPIO_DIR_MODE_IN)
    {
        GPIOPinTypeGPIOInput(ui32Port, ui8Pins);
    }
}

uint32_t GPIO_PortRead(uint8_t ui8Port)
{
    uint32_t ui32Port = GetPortBaseAddress(ui8Port);
    return GPIOPinRead(ui32Port, 0xFF);
}

void DIO_Write(uint8_t ui8Port, uint8_t ui8Pin, uint8_t ui8Value)
{
    uint32_t ui32Port = GetPortBaseAddress(ui8Port);
    if (ui8Value)
    {
        GPIOPinWrite(ui32Port, ui8Pin, ui8Pin); // set
    }
    else
    {
        GPIOPinWrite(ui32Port, ui8Pin, 0); // clear
    }
}

uint8_t GPIO_PinRead(uint8_t ui8Port, uint8_t ui8Pin)
{
    uint32_t ui32Port = GetPortBaseAddress(ui8Port);
    return (GPIOPinRead(ui32Port, ui8Pin) ) ? 1 : 0;  //& ui8Pin
}

void GPIO_WritePort(uint32_t ui32Port, uint8_t ui8Value)
{
    GPIOPinWrite(ui32Port, 0xFF, ui8Value);
//    return 0;
}

uint8_t GPIO_ReadPort(uint32_t ui32Port)
{
    return GPIOPinRead(ui32Port, 0xFF);
}
