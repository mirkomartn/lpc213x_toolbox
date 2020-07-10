/*
 * =====================================================================================
 *
 *       Filename:  pwm.c
 *
 *    Description:  Source file for a lib implementing single edged PWM functionality.
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


#include "pwm.h"

static int PWM_FLAG;


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_pwm
 *  Description:  Initializes the PWM module and registers the IRQ handler.
 * =====================================================================================
 */

void
init_pwm (void)
{
	static int done = 0;

	// silently ignore repeated calls
	if (done)
		return;

	PWM_FLAG = 1;

	// prepare the GPIO P0.0 pin as the output of the PWM
	PINSEL0 &= ~(0x03);
	IO0DIR  |= (1 << 0);

	// register an IRQ handler for the PWM generated interrupts
	while(!(install_irq(PWM0_1_INT, PWMxHandler, PWM_PR)));

	// reset the timer and prescaler
	PWMTCR = 0x002;

	// set the resolution to a scale of ms
	PWMPR = 24999;

	// determine the number ms for the duration of the full cycle
	PWMMR0 = PWM_MSEC;

	// interrupt and reset PWMTC on MATCH0, interrupt on channel MATCHx
	PWMMCR = (1 << 0) | (1 << 1)  | (1 << (MATCHx * 3));

	// enable changes to MATCH0 and channel MATCH register
	PWMLER = (1 << 0) | (1 << MATCHx);

	done = 1;

}		/* -----  end of function init_pwm  ----- */





/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxRun
 *  Description:  Sets the value of initial duty cycle (passed in %) and starts the PWM module.
 * =====================================================================================
 */
void
PWMxRun (const unsigned int duty)
{

	PWMxSetDuty(duty);	// set the initial duty cycle

	PWMTCR = 0x01;		// enable the timer and prescaler

}		/* -----  end of function PWMxRun  ----- */





/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxStop
 *  Description:  Stops and resets the PWM timer and counter.
 * =====================================================================================
 */
void
PWMxStop (void)
{

	PWMTCR = 0x002;

}		/* -----  end of function PWMxStop  ----- */






/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxSetDuty
 *  Description:  Parameter: duration of ON duty cycle (in %). Sets the appropriate
 *  			  MATCHx channel. Returns nothing.
 * =====================================================================================
 */
void
PWMxSetDuty (const int duty)
{
	// 1% duty responds to 1/100th of full cycle duration
	int scale = (PWM_MSEC / 100);

	// MATCH0 interrupts every 10000 timer ticks, hence 1% -> 10 ticks in MATCHx
	switch(MATCHx)
	{
		case 1:
			PWMMR1 = duty * scale;
			break;
		case 2:
			PWMMR2 = duty * scale;
			break;
		case 3:
			PWMMR3 = duty * scale;
			break;
		case 4:
			PWMMR4 = duty * scale;
			break;
		case 5:
			PWMMR5 = duty * scale;
			break;
		case 6:
			PWMMR6 = duty * scale;
			break;
		default:
			return; 	// silently ignore illegal channel value
	}
}		/* -----  end of function PWMxSetDuty  ----- */




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxHandler
 *  Description:  IRQ handler. Sets the flag and clears the interrupt.
 * =====================================================================================
 */
void
PWMxHandler (void)
{
	if (PWMIR & (1 << MATCHx))
	{
		PWMIR = (1 << MATCHx);
		IO0CLR = 0x01;
	}
	else
	{
		PWMIR = (1 << 0);
		IO0SET = 0x01;
	}

	VICVectAddr = 0x00;

}		/* -----  end of function PWMxHandler  ----- */



/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PWMxSwitch
 *  Description:  Returns the value of the flag set by the interrupt, "public getter".
 * =====================================================================================
 */
int
PWMxSwitch (void)
{
	if (PWM_FLAG)
		return 1;

	return 0;

}		/* -----  end of function PWMxSwitch  ----- */

