 
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#define FOSC        (32000000ULL)
#define FCY         (FOSC/2)

#include <xc.h>
#include <libpic30.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>


/*
 * TIMER PERIOD = T_MS * FCY) * (1 / PRESCALER)
 * 2000 = 0.001 * 16 000 000 / 8)
 */
#define TIMER1          2000                        // timer 1 period = 1 ms 
#define TIMER3          65536                       // timer 3 period (max) 

#define BAUDRATEREG     34
#define BAUDRATE        115200                      // requered speed for UART 
#define BRG             157                         // from table for Fcy = 16 ÌÃö and system clock 100 kHz

/* 
 * PERIOD_PWM = TS_PWM * FCY * (1 / PRESCALER_PWM)
 * 20000 = 0.01 * 16 000 000 * (1 / 8)      <=> 100 Hz 
 */

#define PERIOD_PWM      20000
                                                
/*===========================================================================*/
/* PWM (Timer 2) for Wheels Control                                          */
/*===========================================================================*/
/*  RB1 (RP1) => Steering wheels (Channel 1)
 *
 *        |  Clockwise  |  Center  | Counterclockwise
 * -------------------------------------------------
 * t, ms  |     1.27    |   1.52   |      1.79
 * ------------------------------------------------- 
 * width  |     2540    |   3040   |      3580
 * -------------------------------------------------
 *        |     right   |  Center  |      left
 *
 * RB2 (RP13) => Driving wheels (Channel 2)
 *
 *        |  Backward   |  Center  | Forward
 *-------------------------------------------
 * t, ms  |     1.05    |   1.51   |   1.92
 * ------------------------------------------
 * width  |     2100    |   3020   |   3840
 *
 */

#define DUTYCYCLE1      3580
#define DUTYCYCLE2      3020

#endif	/* XC_HEADER_TEMPLATE_H */

