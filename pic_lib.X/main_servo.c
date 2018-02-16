
#include "pragma.h"
#include "define.h"


#include "timer.h"
#include "adc.h"
#include "uart.h"
#include "pwm.h"

int counter = 0;
int flag = 0;

/* Servo parameters
 *  0.88 ms  |  1.44 ms  |  2 ms  |
 *  ---------|-----------|--------|
 *    1760   |   2880    |  4000  |  
 *    down   |           |   up
 *    right  |           |   left
 */

unsigned char com = 128;
void __attribute__ ((interrupt, auto_psv)) _U1RXInterrupt(void)//прерывание по приходу данных по UART
{
    com = get_char_UART1();
    
    OC2R = com*8.78 + 1760;
    
    // x = 8.78   b = 1760
     IFS0bits.U1RXIF = 0;                //обнуляем флаг(датчик) приёма
}


int main(void)
{
    AD1PCFGL = 0xFFFF; 
    /* UART */  
    RPINR18bits.U1RXR = 1; //RP13 -> RB2            //назначaeм RP24 (RB4) для приёма данных (RX)   
    RPOR6bits.RP13R = 3;          //RP1->RB1      //назначаем RP18 (RB5) для передачи данных (TX)
    /*******/
    
     /* PWM */
    //TRISBbits.TRISB1 = 0;              // pin SDO set as output for PWM1 (upper servo)
    //TRISBbits.TRISB2 = 0;              // pin SDI set as output for PWM2 (down serva)
    /********/
    
    //init_PWM1(); 
    //init_PWM2();
    //init_ADC();
//    init_timer3();
    init_UART1();
    TRISAbits.TRISA5 = 0;       // Blue
    TRISAbits.TRISA4 = 0;       // Pink
    TRISAbits.TRISA15 = 0;       // Blue
    TRISAbits.TRISA14 = 0;       // Pink
    TRISAbits.TRISA3 = 0;       // Yellow
    TRISAbits.TRISA2 = 0;       // Orange
    
    uint16_t counter = 0;
    
    while(1)
    {
        //put_char_UART1('o');
        //LATAbits.LATA15 = 0;     // blue off
        LATAbits.LATA5 = 0;     // blue off
        LATAbits.LATA2 = 1;     // orange
        __delay_ms(5);
        LATAbits.LATA2 = 1;     // orange
        LATAbits.LATA3 = 1;     // yellow 
        __delay_ms(5);
        LATAbits.LATA2 = 0;     // orange off
        LATAbits.LATA3 = 1;     // yellow 
        __delay_ms(5);
        LATAbits.LATA3 = 1;     // yellow
        LATAbits.LATA4 = 1;     // pink
        //LATAbits.LATA14 = 1;     // pink
        __delay_ms(5);
        LATAbits.LATA3 = 0;     // yellow off
        //LATAbits.LATA14 = 1;     // pink
        LATAbits.LATA4 = 1;     // pink
        __delay_ms(5);
        LATAbits.LATA4 = 1;     // pink
        LATAbits.LATA5 = 1;     // blue
        //LATAbits.LATA14 = 1;     // pink
        //LATAbits.LATA15 = 1;     // blue
        __delay_ms(5);
        LATAbits.LATA4 = 0;     // pink off
        LATAbits.LATA5 = 1;     // blue
//        LATAbits.LATA14 = 0;     // pink off
//        LATAbits.LATA15 = 1;     // blue
         __delay_ms(5);
         LATAbits.LATA5 = 1;     // blue
         //LATAbits.LATA15 = 1;     // blue
         LATAbits.LATA2 = 1;     // orange
         __delay_ms(5);
    }
    
    
    return 0;
}
