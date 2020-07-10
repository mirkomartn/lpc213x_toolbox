/*
 * =====================================================================================
 *
 *       Filename:  helper.c
 *
 *    Description:  Source file for a library of helper functions.
 *
 *        Version:  1.1
 *        Created:  03/08/2020
 *       Revision:  03/15/2020
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gst), gasperstukelj@protonmail.com
 *   Organization:  FHTW
 *
 * =====================================================================================
 */


#include "helper.h"


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GSTxFTOA
 *  Description:  Stores a char representation of float x (one decimal point) in buff.
 * =====================================================================================
 */
void
GSTxFTOA (float x, char buff[3])
{

	buff[0] = ((int) x) + 0x30;				// convert integer part to ascii hex
	buff[1] = 0x2E; 					// '.'
	buff[2] = GSTxRound((x - (int) x) * 10) + 0x30;  	// convert float part to ascii hex

	if (buff[2] == 0x3A){					// if fractional part => .95 round up
		buff[0] += 1;
		buff[2]  = 0x30;
	}

}		/* -----  end of function GSTxFTOA  ----- */




/*
 * ===  FUNCTION  ======================================================================
 *         Name:  round
 *  Description:  Rounds a float and returns it as an int.
 * =====================================================================================
 */

int
GSTxRound(float x)
{
	// fractional part of x < 0.5
	if ((int) x == (int) (x + 0.5f))
		return (int) x;

	// fractional part of x => 0.5
	return (int) x + 1;

}		/* -----  end of function round  ----- */
