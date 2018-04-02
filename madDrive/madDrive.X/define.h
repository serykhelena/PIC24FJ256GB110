 
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#define FOSC        (32000000ULL)
#define FCY         16000000

#include <xc.h>
#include <libpic30.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

//#define timer1        0b0100111000100000          //������=20000 [0,01/(1/(32 ���/2))/8] ��� 10 ��
//#define timer1        0b0011111010000000          //������=16000 [0,001/(1/(32 ���/2))] ��� 1 �� (????? = 8 ��))
//#define timer1        0b0000011111010000          // ������ = 2000 = 1 �� 
#define timer1        50000
#define timer3        0b1111111111111111          // ������ ������ 3 (65536)
#define timer5        40000                         // ������ 20 �� 

#define BAUDRATEREG     34
#define BAUDRATE        115200
#define BRG             157                         // (not used, just for info) from table Fcy=16���, clock frequency = 100 kHz

#define Period          27200
#define DutyCycle1      3040

/*
 * Steering wheels (PWM 1 => Channel 1)
 *    Clockwise    |    Center    |    Counterclockwise
 * ----------------|--------------|---------------------
 *     1.27 ms     |    1.52 ms   |         1.79 ms
 * ----------------|--------------|---------------------
 *      2540       |     3040     |          3580
 * ----------------|--------------|---------------------
 *   on the right  |    center    |       on the left 
 */

#define DutyCycle2      3020
/*
 * Driving wheels (PWM 2 => Channel 2)
 *    Backward     |    Center    |        Forward
 * ----------------|--------------|---------------------
 *     1.05 ms     |    1.51 ms   |         1.92 ms
 * ----------------|--------------|---------------------
 *      2100       |     3020     |          3840
 */


#endif	/* XC_HEADER_TEMPLATE_H */

