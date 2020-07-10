/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  Timer library header file.
 *
 *        Version:  1.0
 *        Created:  02/28/2020
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gst), gasperstukelj@protonmail.com
 *   Organization:  FHTW
 *
 * =====================================================================================
 */


#ifndef __TIMER0
#define __TIMER0

#define MSEC 0x03E8		// set the number of ms at which MR0 triggers

#include "lpc213x.h"
#include "irq.h"
#include "priorities.h"


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_timer
 *  Description:  Sets up and runs a timer, inits VIC and installs an IRQ timer handler.
 * =====================================================================================
 */

void init_timer (void);



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  T0Handler
 *  Description:  Sets the FLAG to 1 when a timer interrupt occurs and cleans up.
 * =====================================================================================
 */

void T0Handler (void) __attribute__ ((interrupt ("IRQ")));



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  time_flag
 *  Description:  Returns 1 if a new timer interrupt has occurred, 0 otherwise.
 * =====================================================================================
 */

int time_flag (void);



#endif

