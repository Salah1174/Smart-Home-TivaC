#ifndef BTMOD_H
#define BTMOD_H

#include <stdint.h>
#include <stdbool.h>

void BTMOD_Init(void);
void BTMOD_SendChar(uint8_t data);

void BTMOD_SendString(char *data);
void BTMOD_SendInteger(int64_t sNumber);

#endif