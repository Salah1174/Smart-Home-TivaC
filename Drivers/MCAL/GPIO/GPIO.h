#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

void DIO_Init(uint32_t ui32Port, uint8_t ui8Pins, uint32_t ui32Direction, uint32_t ui32Strength, uint32_t ui32PadType );
uint32_t GPIO_PortRead(uint32_t ui32Port) ;
void DIO_Write(uint32_t ui32Port, uint8_t ui8Pin, uint8_t ui8Value);
uint8_t GPIO_PinRead(uint32_t ui32Port, uint8_t ui8Pin);

#endif