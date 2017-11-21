
#include <p24FJ256GB110.h>

#include "pragma.h"
#include "define.h"


#include "timer.h"
#include "adc.h"
#include "uart.h"
#include "pwm.h"

int counter = 0;
int flag = 0;
int moment = 0;

//void __attribute__ ((interrupt, auto_psv)) _T1Interrupt(void) //прерывание по таймеру 1 мс
//{
//    counter = counter + 1;
//    
//    if(counter == 1)
//    {
//        LATEbits.LATE9 = 1;
//        
//    }
//    if(counter == 2)
//    {
//        flag = read_ADC(11);
//        send_data_UART1(flag);
//        moment = read_ADC(12);
//////        send_data_UART1(flag);
//        send_data_UART1(moment);
//    }
//    if(counter == 3)
//    {
//        LATEbits.LATE9 = 0;
//    }
//    if(counter == 4)
//    {
//        counter = 0;
//    }
//     
//    IFS0bits.T1IF = 0;                   //Очищаем флаг по прерыванию таймера 1
//}

int count_duty = 0;
unsigned int duty1 = 0;
unsigned int duty2 = 0;
int duty = 0;

void __attribute__ ((interrupt, auto_psv)) _U1RXInterrupt(void)//прерывание по приходу данных по UART
{
   
//    put_char_UART1('a');
    LATEbits.LATE9 =! PORTEbits.RE9;
    
//    count_duty += 1;
//    if(count_duty == 2)
//    {
//        duty1 = get_char_UART1();
//        duty2 = get_char_UART1();
//        duty = (duty1 << 8)|(duty2);
//        send_data_UART1(duty);
        count_duty = 0;
//    }
    
   
     IFS0bits.U1RXIF = 0;                //обнуляем флаг(датчик) приёма
}



int main(void) 
{
    CLKDIVbits.CPDIV = 00;
//    init_PWM1();
//    init_ADC();
//    init_timer1();
    init_UART1();
    
//    TRISBbits.TRISB4 = 1;               //RB4 = вход для приёма (RX)
//    TRISBbits.TRISB5 = 0;               //RB5 = выход для передачи (TX)     
    RPINR18bits.U1RXR = 31;             //назначaeм RP31 (RF13) для приёма данных (RX)   
    RPOR9bits.RP18R = 3;                //назначаем RP18 (RB5) для передачи данных (TX)
    
    /* PWM */
    TRISBbits.TRISB1 = 0;              // pin SDO set as output for PWM1 (upper servo)
    /*-----*/
    
    TRISEbits.TRISE9 = 0;       // set pin as output
    //TRISEbits.TRISE8 = 0;
    
//    LATEbits.LATE9 = 0;
//    __delay_ms(500);
//    
    char a = 'f';
    put_char_UART1(a);
    
    while(1)
    {
 
        a = get_char_UART1();
        LATEbits.LATE9 =! LATEbits.LATE9;
        put_char_UART1(a);
     
//     __delay_ms(400);
    }
   
        
    return 0;
}
