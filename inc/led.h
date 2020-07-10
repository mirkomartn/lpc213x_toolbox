/*
 * =====================================================================================
 *
 *       Filename:  led.c
 *
 *    Description:  LED library header file.
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


#ifndef __LED0

#define __LED0

#define LED 10 	// determines the pin, where the pin used for driving the led is P0.<LED>

// don't change, see PINSEL0 pin bit config in the board user guide
#define PSEL1 (LED * 2)
#define PSEL2 (PSEL1 + 1)


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_LED
 *  Description:  Initializes the pin driving the LED (macros set in led.h).
 * =====================================================================================
 */

void init_LED (void);




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  toggle_LED
 *  Description:  Toggles the LED from HIGH to LOW and vice versa.
 * =====================================================================================
 */

void toggle_LED (void);

#endif
