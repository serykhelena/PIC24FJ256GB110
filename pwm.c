#include "define.h"

void init_PWM1 ()                 // инициализация ШИМ1 - steering wheels
{
    TMR2 = 0;                     // начальное значение таймера
    PR2 =  Period;                // конечное значение таймера
    T2CONbits.TCKPS = 0b01;       // предделитель 1:8  
    T2CONbits.TON = 1;            // старт таймер 2 
    
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (делим на 1 частоту "кварца")
    RPOR0bits.RP1R = 18;          // выбор пина для ШИМ RB1 - RP1
    OC1R = DutyCycle1;             // скважность
    OC1RS = PR2;                  // период 
    OC1CON2bits.SYNCSEL = 0b01100;// sync source
    OC1CON2bits.OCTRIG = 0;       
    OC1CON1bits.OCTSEL = 0;       // выбор таймер 2 <=> 000 
    IEC0bits.T2IE = 0;            // выключение прерываний по таймеру
    IEC0bits.OC1IE = 0;           // выключение прерываний по ОС
    IEC0bits.U1RXIE = 0; 
    OC1CON1bits.OCM = 0b110;      // выбор режима ШИМ Edge-aligned PWM Mode on OCx 
}

void init_PWM2 ()                  // инициализация ШИМ - driving wheels
{
    TMR2 = 0;                     // начальное значение таймера
    PR2 =  Period;                // конечное значение таймера
    T2CONbits.TCKPS = 0b01;       // предделитель 1:8  
    T2CONbits.TON = 1;            // старт таймер 2 
    
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (делим на 1 частоту "кварца")
    RPOR6bits.RP13R = 19;        // выбор пина для ШИМ RB3 - RP13 Choose number of function carefully! 
    OC2RS = PR2;                  //период 
    OC2R = DutyCycle2;             // скважность
                   
    OC2CON2bits.SYNCSEL = 0b01100;// sync source
    OC2CON2bits.OCTRIG = 0;       
    OC2CON1bits.OCTSEL = 0;       // выбор таймер 2 <=> 000 
    IEC0bits.T2IE = 0;            // выключение прерываний по таймеру
    IEC0bits.OC1IE = 0;           // выключение прерываний по ОС
    IEC0bits.U1RXIE = 0; 
    OC2CON1bits.OCM = 0b110;      // выбор режима ШИМ Edge-aligned PWM Mode on OCx 
}
