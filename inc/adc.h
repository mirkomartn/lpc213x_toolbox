/*
 * =====================================================================================
 *
 *       Filename:  adc.h
 *
 *    Description:  Header file for the LPC2138 ADC0 library (software conversion).
 *
 *        Version:  1.1
 *        Created:  03/08/2020
 *       Revision:  03/29/2020
 *       Compiler:  gcc
 *
 *         Author:  Gasper Stukelj (gst), gasperstukelj@protonmail.com
 *   Organization:  FHTW
 *
 * =====================================================================================
 */

#ifndef ADC0_H_
#define ADC0_H_

#include "irq.h"
#include "lpc213x.h"

// select the adc pin that can be configured through selected PINSEL1
#define _PINSEL 22

// Define 'x' in A0.x pin selected above
#define ADCPIN 0

// Must be such that PCLK / (CLKDIV + 1) <= 4.5 MHz
#define CLKDIV 0x05

// 0 if software conversion (11 cycles), see user guide for 1
#define BURST 0x00

// Time to start the conversion, 0x001 == NOW
#define START 0x001

// 10 bit conversion -> 2^10 - 1 = 0x3FF
#define ADCFRAC 0x3FF

// max possible value on the ADC0 pin, application dependent(!)
//#define ADCMAX 3.3f

// define ADCMAX to be 100, to get
#define ADCMAX 100.0f


// constant factor to get a float from the 10 bits from ADC
#define CONVERT (ADCMAX / ADCFRAC)


// helper function, extracts the bits 15:6 from x
#define GETVAL(x) ((x & 0xFFC0) >> 6)


// call this once at the start of the program
void init_adc (void);

// call this to start the ADC conversion, returns a float after it's done
float ADCxConvert (void);

#endif
