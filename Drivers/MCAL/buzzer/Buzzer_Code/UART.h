//salah
#include <stdint.h>
#ifndef UART_H
#define UART_H

void UART_Init(void);
void UART_SendString(const char *str);
void UART_SendInt(uint32_t num);

#endif
