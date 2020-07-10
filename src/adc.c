/*
 * =====================================================================================
 *
 *       Filename:  adc.c
 *
 *    Description:  Source for the LPC2138 ADC0 library (software conversion).
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


#include "adc.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_adc
 *  Description:  Inits the ADC pin and prepares for ADC0 conversion.
 * =====================================================================================
 */

void
init_adc (void)
{

	static char done = 0;

	if (done) return; 		// silently ignore repeated calls

	PINSEL1 |= (1 << _PINSEL); 	// set the function of the selected pin to ADC

	AD0CR    = 0x00;
	AD0CR 	 = (1 << ADCPIN) | 	(CLKDIV << 8) | (BURST << 16);

	done = 1;

}		/* -----  end of function init_adc  ----- */




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ADCxConvert
 *  Description:  Gets the value from selected ADC pin and returns a float.
 * =====================================================================================
 */

float
ADCxConvert (void)
{

	float retval;

	AD0CR |= (1 << 21) | (START << 24); 		// start the conversion

	while(!(AD0DR >> 31));				// wait for the completion

	retval = GETVAL(AD0DR);				// get the fractional result

	AD0CR ^= (1 << 21) | (START << 24);		// turn off the ADC

	return retval * CONVERT; 			// compute the converted value

}		/* -----  end of function ADCxConvert  ----- */
