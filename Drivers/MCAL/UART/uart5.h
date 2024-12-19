/******************************************************************************
 *
 * Module: UART5
 *
 * File Name: uart5.h
 *
 * Description: Header file for the TM4C123GH6PM UART5 driver
 *
 * Author: Edges for Training Team
 *
 *******************************************************************************/

#ifndef UART5_H_
#define UART5_H_

#include "std_types.h"

/*******************************************************************************
 *                             Preprocessor Macros                             *
 *******************************************************************************/

#define UART_DATA_5BITS 0x0
#define UART_DATA_6BITS 0x1
#define UART_DATA_7BITS 0x2
#define UART_DATA_8BITS 0x3
#define UART_LCRH_WLEN_BITS_POS 5

/* UART5 Control Register Masks */
#define UART_CTL_UARTEN_MASK 0x00000001 // UART Enable
#define UART_CTL_TXE_MASK 0x00000100    // UART Transmit Enable
#define UART_CTL_RXE_MASK 0x00000200    // UART Receive Enable

/* UART5 Flag Register Masks */
#define UART_FR_TXFE_MASK 0x00000080 // UART Transmit FIFO Empty
#define UART_FR_RXFE_MASK 0x00000010 // UART Receive FIFO Empty

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

extern volatile uint8 UART5_ReceivedByte; // Variable to store received byte

extern void UART5_Init(void);

extern void UART5_SendByte(uint8 data);

extern uint8 UART5_ReceiveByte(void);

extern void UART5_SendString(const uint8 *pData);

extern void UART5_SendInteger(sint64 sNumber);

#endif /* UART5_H_ */
