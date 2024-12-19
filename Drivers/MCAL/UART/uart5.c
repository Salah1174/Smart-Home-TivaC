/******************************************************************************
 *
 * Module: UART5
 *
 * File Name: uart5.c
 *
 * Description: Source file for the TM4C123GH6PM UART5 driver using RX interrupt.
 *
 * Author: Edges for Training Team
 *
 ******************************************************************************/

#include "uart5.h"
#include "tm4c123gh6pm.h"
#include "../GPIO/gpio.h"
#include <stdbool.h>
/*******************************************************************************
 *                         Global Variables                                    *
 *******************************************************************************/
volatile uint8 UART5_ReceivedByte = 0; // Variable to store received byte
volatile uint8 UART5_ReceivedFlag = 0; // Flag to indicate a new byte was received

/*******************************************************************************
 *                         Private Functions Definitions                       *
 *******************************************************************************/

/**
 * @brief Initializes UART5 with the default configuration: 9600 baud, 8 data bits, 1 stop bit.
 *        Enables RX interrupt for UART5.
 */
void UART5_Init(void)
{
    // Step 1: Enable clock for UART5 and GPIO Port E
    SYSCTL_RCGCUART_R |= 0x20; // Enable clock for UART5 (bit 5 = 0x20)
    SYSCTL_RCGCGPIO_R |= 0x10; // Enable clock for GPIO Port E (bit 4 = 0x10)

    // Wait until UART5 and GPIO Port E are ready
    while (!(SYSCTL_PRUART_R & 0x20))
        ; // Wait until UART5 is ready
    while (!(SYSCTL_PRGPIO_R & 0x10))
        ; // Wait until GPIO Port E is ready

    // Step 2: Configure GPIO pins PE4 (RX) and PE5 (TX) for UART5
    GPIO_PORTE_AMSEL_R &= ~0x30;                                       // Disable analog functionality on PE4 (RX) and PE5 (TX)
    GPIO_PORTE_DIR_R |= 0x20;                                          // Set PE5 (TX) as output
    GPIO_PORTE_DIR_R &= ~0x10;                                         // Set PE4 (RX) as input
    GPIO_PORTE_AFSEL_R |= 0x30;                                        // Enable alternate function on PE4 and PE5
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | 0x00110000; // Set PE4 as RX and PE5 as TX
    GPIO_PORTE_DEN_R |= 0x30;                                          // Enable digital I/O on PE4 and PE5

    // Step 3: Disable UART5 for configuration
    UART5_CTL_R &= ~UART_CTL_UARTEN_MASK; // Disable UART5

    // Step 4: Configure the baud rate for UART5 (9600 bps)
    UART5_IBRD_R = 104; // Integer part of the divisor (for 9600 bps, with 16 MHz system clock)
    UART5_FBRD_R = 11;  // Fractional part of the divisor

    // Step 5: Configure UART5 line control settings
    UART5_LCRH_R = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS) // 8 bits data
        ;                                                       // Enable FIFOs

    // Step 6: Enable RX interrupt
    UART5_IM_R |= UART_IM_RXIM;            // Enable RX interrupt
    NVIC_EN1_R |= (1 << (INT_UART5 - 48)); // Enable UART5 interrupt in NVIC (interrupt number 61)

    // Step 7: Enable UART5, TX, and RX
    UART5_CTL_R = UART_CTL_UARTEN_MASK | UART_CTL_RXE_MASK | UART_CTL_TXE_MASK;
}

/**
 * @brief Sends a single byte over UART5.
 *
 * @param data Byte to send.
 */
void UART5_SendByte(uint8 data)
{
    while (UART5_FR_R & UART_FR_TXFF)
        ;              // Wait until the TX FIFO is not full
    UART5_DR_R = data; // Write the byte to the UART Data Rister
}

/**
 * @brief Receives a single byte from UART5 (blocking).
 *
 * @return Received byte.
 */
uint8 UART5_ReceiveByte(void)
{
    //    while (!(UART5_ReceivedFlag))
    //        ; // Wait until a new byte is received

    UART5_ReceivedFlag = 0; // Clear the flag
    return UART5_ReceivedByte;
}

/**
 * @brief Sends a null-terminated string via UART5.
 *
 * @param pData Pointer to the string to send.
 */
void UART5_SendString(const uint8 *pData)
{
    while (*pData != '\0')
    {
        UART5_SendByte(*pData); // Send each byte of the string
        pData++;
    }
}

/**
 * @brief Sends an integer via UART5 (converts it to a string before sending).
 *
 * @param sNumber Integer to send.
 */
void UART5_SendInteger(sint64 sNumber)
{
    uint8 uDigits[20];
    sint8 uCounter = 0;

    // Send the negative sign in case of negative numbers
    if (sNumber < 0)
    {
        UART5_SendByte('-');
        sNumber *= -1;
    }

    // Convert the number to an array of characters
    do
    {
        uDigits[uCounter++] = sNumber % 10 + '0'; // Convert each digit to its corresponding ASCII character
        sNumber /= 10;                            // Remove the already converted digit
    } while (sNumber != 0);

    // Send the array of characters in reverse order
    for (uCounter--; uCounter >= 0; uCounter--)
    {
        UART5_SendByte(uDigits[uCounter]);
    }
}

/**
 * @brief UART5 interrupt handler.
 */
void UART5_Handler(void)
{
    if (UART5_MIS_R & UART_MIS_RXMIS) // Check if RX interrupt occurred
    {
        UART5_ReceivedByte = (uint8)UART5_DR_R; // Read the received byte
        switch (UART5_ReceivedByte)
        {
        case '1' :
            char lampStatus = GPIO_PinRead('F', 0x000000002);
            DIO_Write('F', 0x000000002, !lampStatus);
            break;
        case '2':
          char plugStatus = GPIO_PinRead('F',0x0000004);
          DIO_Write('F', 0x000000004, !plugStatus);
        }
//        UART5_SendByte(UART5_ReceivedByte);
//        UART5_ReceivedByte = 0;
        UART5_ICR_R |= UART_ICR_RXIC; // Clear the RX interrupt flag
    }
}
