/*
 * =====================================================================================
 *
 *       Filename:  led.c
 *
 *    Description:  Source for the LED library.
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


#include "lpc213x.h"
#include "led.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_LED
 *  Description:  Initializes the pin driving the LED (macros set in led.h).
 * =====================================================================================
 */

void init_LED (void)
{
	PINSEL0 ^= ((1 << PSEL1) & (1 << PSEL2));	// set the LED pin  as a GPIO port
	IO0DIR = (1 << LED);				// set the LED pin  as an OUT pin
	IO0CLR = (1 << LED); 				// set the LED pin to LOW

}		/* -----  end of function init_LED  ----- */




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  toggle_LED
 *  Description:  Toggles the LED from HIGH to LOW and vice versa.
 * =====================================================================================
 */

void toggle_LED (void)
{
	static int on = 0;
	if (on) {
		IO0CLR = (1 << LED);			// set P0.10 to LOW
		on = 0;
	}
	else{
		IO0SET = (1 << LED);			// set P0.10 to HIGH
		on = 1;
	}
}		/* -----  end of function toggle_LED  ----- */
