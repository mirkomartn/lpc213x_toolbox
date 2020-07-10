/*
 * =====================================================================================
 *
 *       Filename:  pwm.h
 *
 *    Description:  Header file for lib implementing single edged PWM functionality.
 *
 *        Version:  1.0
 *        Created:  03/28/2020
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gs), gasperstukelj@protonmail.com
 *   Organization:  FHTW
 *
 * =====================================================================================
 */


#ifndef __PWM_H__
#define __PWM_H__

#include "lpc213x.h"
#include "irq.h"
#include "priorities.h"

// determine the MATCH channel to be used for the PWM
#define MATCHx 1

// determine the duration of the full cycle (in ms)
// default duration 1000ms = 1s
#define PWM_MSEC 1000



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_pwm
 *  Description:  Initializes the PWM module and registers the IRQ handler.
 * =====================================================================================
 */

void
init_pwm (void);



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxSetDuty
 *  Description:  Parameter: duration of ON duty cycle (in %). Sets the appropriate
 *  			  MATCHx channel. Returns nothing.
 * =====================================================================================
 */
void
PWMxSetDuty (const int duty);



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxSwitch
 *  Description:  Returns the value of the flag set by the interrupt, "public getter".
 * =====================================================================================
 */
int
PWMxSwitch (void);


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxHandler
 *  Description:  IRQ handler. Sets the flag and clears the interrupt.
 * =====================================================================================
 */
void
PWMxHandler (void);




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxRun
 *  Description:  Sets the value of initial duty cycle (passed in %) and starts the PWM module.
 * =====================================================================================
 */
void
PWMxRun (const unsigned int);





/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxStop
 *  Description:  Stops and resets the PWM timer and counter.
 * =====================================================================================
 */
void
PWMxStop (void);

#endif // __PWM_H__
