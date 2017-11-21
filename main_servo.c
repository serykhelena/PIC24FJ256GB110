
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
    /* UART */  
    RPINR18bits.U1RXR = 28;             //назначaeм RP24 (RB4) для приёма данных (RX)   
    RPOR9bits.RP18R = 3;                //назначаем RP18 (RB5) для передачи данных (TX)
    /*******/
    
     /* PWM */
    TRISBbits.TRISB1 = 0;              // pin SDO set as output for PWM1 (upper servo)
    TRISBbits.TRISB2 = 0;              // pin SDI set as output for PWM2 (down serva)
    /********/
    
    init_PWM1(); 
    init_PWM2();
    init_ADC();
//    init_timer3();
    init_UART1();
    
   
    
    TRISEbits.TRISE9 = 0;       // set pin as output
    int pot = 0;
    int duty = 0;
    unsigned char a = 0;
    
    while(1)
    {
         //OC1R = 2800;
        //OC2R = 200*8.78 + 1760;;
        
        //pot = read_ADC(11);
//        send_number_UART1(pot);
//        put_char_UART1(' ');
//        __delay_ms(200);
//        send_string_UART1('hi');
       // duty = pot * 2.19 + 1760;
       // OC2R = 2800;
//        send_number_UART1(duty);
//        put_char_UART1(' ');
//        __delay_ms(300);
        
        
    }
    
    
    return 0;
}
