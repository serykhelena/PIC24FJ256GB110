 
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

//#define timer1      0b0100111000100000          //период=20000 [0,01/(1/(32 ћгц/2))/8] дл€ 10 мс
//#define timer1      0b0011111010000000          //период=16000 [0,001/(1/(32 ћгц/2))] дл€ 1 мс (????? = 8 мс))
#define timer1      0b0000011111010000          // период = 2000 = 1 мс 
#define timer3      0b1111111111111111          // период таймер 3 (65536)

#define BAUDRATEREG 34
#define BAUDRATE 115200
#define BRG 157                                 //из таблицы дл€ Fcy=16ћ√ц и такт.частота 100 к√ц

#define Period      40000                       // 50 Hz 
                                                // 27200 = 73.5 Hz -> 13.6 ms
                                                // FCY/(73.5 Hz * prescaler )
#define DutyCycle1   3030
#define DutyCycle2   3030

#endif	/* XC_HEADER_TEMPLATE_H */

