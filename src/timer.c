/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  Timer library source file.
 *
 *        Version:  1.0
 *        Created:  02/28/2020
 *       Revision:  03/15/2020
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gst), gasperstukelj@protonmail.com
 *   Organization:  FHTW
 *
 * =====================================================================================
 */


#include "lpc213x.h"
#include "irq.h"
#include "timer.h"


static int TIMExFLAG;


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_timer
 *  Description:  Sets up and runs a timer, inits VIC and installs an IRQ timer handler.
 * =====================================================================================
 */

void init_timer (void)
{

	static int done = 0;

	TIMExFLAG = 0;

	if (done) {
		return; 		// silently ignore any repeated call
	}

	install_irq(TIMER0_INT, T0Handler, TIMER0_PR);  // install the IRQ handler for TIMER0 interrupt

	T0CTCR = 0x0; 		// select the timer mode
	T0TCR  = 0x2; 		// reset and disable the timer
	T0PR   = 0x61A7;	// set the PC to count in microseconds
	T0MR0  = MSEC; 		// set MR0 to trigger every MSEC ms (default 1s)
	T0MCR  = 0x03; 		// interrupt and reset TC on every MR0 trigger
	T0TCR  = 0x1; 		// enable the timer

	done = 1;		// set the flag after the first call to init_timer

}		/* -----  end of function init_timer  ----- */



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  T0Handler
 *  Description:  Sets the TIMExFLAG to 1 when a timer interrupt occurs and cleans up.
 * =====================================================================================
 */

void T0Handler (void)
{

	TIMExFLAG = 1;			// set the trigger TIMExFLAG
	T0IR = 0x1; 			// clear the MR0 interrupt flag
	VICVectAddr = 0x00;		// clear the VIC Vector Address

}		/* -----  end of function T0Handler  ----- */




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  time_flag
 *  Description:  Returns 1 if a new timer interrupt has occurred, 0 otherwise.
 * =====================================================================================
 */

int time_flag (void)
{

	if (TIMExFLAG) {
		TIMExFLAG = 0;
		return 1;
	}

	return 0;

}		/* -----  end of function time_flag  ----- */
