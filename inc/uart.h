/*
 * =====================================================================================
 *
 *       Filename:  uart.h
 *
 *    Description:  Header file for the LPC2138 UART0 library.
 *
 *        Version:  1.1
 *        Created:  03/07/2020
 *       Revision:  03/15/2020
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gst), gasperstukelj@protonmail.com
 *   Organization:  FHTW
 *
 * =====================================================================================
 */


#ifndef _UART0_H_
#define _UART0_H_


#include "lpc213x.h"
#include "priorities.h"
#include "irq.h"



#define WLEN 0x03			// word length (0x00 = 5, ... , 0x03 = 8)
#define STPB 0x0			// number of stop bits (0 = 1, 1 = 2)
#define PARE 0x00			// parity enabled ON/OFF (1/0)


// set the Baud rate to 9600
#define _U0DLL 0x9D
#define _U0DLM 0x00


#define RXTRIG 0x02			// Set the number of bits that trigger a RX interrupt
#define RBRINT 0x00			// 1 if RBR  interrupt should be enabled, 0 otherwise
#define RXINT  0x00			// 1 if RX   interrupt should be enabled, 0 otherwise
#define THRE   0x01			// 1 if THRE interrupt should be enabled, 0 otherwise


void init_uart (void);

void UARTxWrite (char *buff, unsigned int len);

void UARTxHandler(void) __attribute__ ((interrupt ("IRQ")));

#endif
