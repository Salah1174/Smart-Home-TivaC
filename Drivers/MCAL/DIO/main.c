#include "DIO.h"
#include "bitwise_operations.h"
#include "tm4c123gh6pm.h"

#define LED_PORT 'F'
#define LED_PIN  2

void delay_ms(int milliseconds);

int main(void) {
    DIO_Init(LED_PORT, LED_PIN, DIO_PIN_OUTPUT);

    while (1) {
        DIO_WritePin(LED_PORT, LED_PIN, 1);
        delay_ms(500);

        DIO_WritePin(LED_PORT, LED_PIN, 0);
        delay_ms(500);
    }
}

void delay_ms(int milliseconds) {
    int i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 3180; j++) { }
    }
}
