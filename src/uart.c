/*
 * =====================================================================================
 *
 *       Filename:  uart.c
 *
 *    Description:  The source for the LPC2138 UART0 library.
 *
 *        Version:  1.0
 *        Created:  03/07/2020
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gst), gasperstukelj@protonmail.com
 *   Organization:  FHTW
 *
 * =====================================================================================
 */

#include "uart.h"

static int UART_FLAG;


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_uart
 *  Description:  Init the UART pin and setup the communication channel.
 * =====================================================================================
 */

void
init_uart (void)
{

	static char done = 0;

	if (done) return; 				// ignore repeated calls

	PINSEL0 |= 0x05; 				// set the functionality of the selected pins to Tx and Rx

	install_irq(UART0_INT, UARTxHandler, UART0_PR); // install the IRQ handler for UART0 interrupt

	// set the control line register, see uart.h for values
	U0LCR    = (WLEN) | (STPB << 2) | (PARE << 3) | (1 << 7);

	// set the Baud rate
	U0DLL    = _U0DLL;
	U0DLM    = _U0DLM;

	// disable DLAB
	U0LCR   ^= (1 << 7);

	// enable and reset the Rx and Tx FIFOS and set the Rx Trigger level
	U0FCR	 = (0x07 | RXTRIG << 6);
	U0TER    = (1 << 7);

	done = 1;

}		/* -----  end of function init_uart  ----- */





/*
 * ===  FUNCTION  ======================================================================
 *         Name:  UARTxWrite
 *  Description:  Accepts pointer to a char buffer of length len. Writes XX bits every
 *  			  time the THR is empty.
 * =====================================================================================
 */

void
UARTxWrite (char *buff, unsigned int len)
{

	int i = 0;

	for (; i < len;) {

		UART_FLAG = 1;					// set the buffer flag to dirty
		U0IER |= THRE << 1;				// enable the THR interrupt

		while (UART_FLAG); 				// wait until the THR & Tx FIFO are empty

		do {						// first write, because 0 % 16 == 0 as well

			U0THR = *(buff + i++);			// write the next byte to the Tx FIFO

		} while((i < len) & (i & 0x0F));		// Tx FIFO holds 16 bytes, AND for i % 16
	}

}		/* -----  end of function UARTxWrite  ----- */




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  UARTxHandler
 *  Description:  Sets the flag when the Tx buffer is empty and ready to be written to.
 * =====================================================================================
 */

void
UARTxHandler (void)
{
	if (U0LSR & (1 << 6)) {		// check if Tx is ready for write
		UART_FLAG = 0;		// set the flag
		U0IER ^= 1 << 1;	// disable the UART0 IRQ
	}
	VICVectAddr = 0x00;
}		/* -----  end of function UARTxHandler  ----- */
