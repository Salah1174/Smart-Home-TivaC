#include "BTMod.h"
#include "..\..\MCAL\UART\uart5.h"

void BTMOD_Init(void)
{
    UART5_Init();
}
void BTMOD_SendChar(uint8_t data)
{
    UART5_SendChar(data);
}

void BTMOD_SendString(char *data)
{
    UART5_SendString(data);
}
