/*
 * =====================================================================================
 *
 *       Filename:  helper.h
 *
 *    Description:  Header file for a library of helper functions.
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

// converts a float to a char representation rounded to 1 decimal point
void GSTxFTOA (float x, char buff[3]);

// rounds a float to the nearest int
int GSTxRound (float x);
