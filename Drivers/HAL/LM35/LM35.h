#ifndef LM35_H
#define LM35_H

#include <stdint.h>
#include <stdbool.h>

void LM35_Init(void);
uint32_t LM35_Temp(void);

#endif