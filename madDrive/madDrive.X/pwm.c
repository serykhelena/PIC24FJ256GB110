#include "define.h"

// PWM module 1 initialization (for steering wheels)
void init_PWM1 ()                 
{
    TMR2 = 0;                     // start value of timer
    PR2 =  Period;                // final value of timer
    T2CONbits.TCKPS = 0b01;       // prescaler 1:8  
    T2CONbits.TON = 1;            // timer 2 turn on
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (делим на 1 частоту "кварца")
    RPOR0bits.RP1R = 18;          // set pin for PWM1 RB1 - RP1
    OC1R = DutyCycle1;            // pulse width 
    OC1RS = PR2;                  // period 
    OC1CON2bits.SYNCSEL = 0b01100;// sync source
    OC1CON2bits.OCTRIG = 0;       
    OC1CON1bits.OCTSEL = 0;       // choose timer 2 <=> 000 
    IEC0bits.T2IE = 0;            // timer interrupt is disable 
    IEC0bits.OC1IE = 0;           // OC interrupt is disable 
    IEC0bits.U1RXIE = 0;          // U1RX interrupt is disable   
    OC1CON1bits.OCM = 0b110;      // Edge-aligned PWM Mode on OCx 
}

// PWM module 2 initialization (for driving wheels)
void init_PWM2 ()                 
{
    TMR2 = 0;                     // start value of timer
    PR2 =  Period;                // final value of timer
    T2CONbits.TCKPS = 0b01;       // prescaler 1:8 
    T2CONbits.TON = 1;            // timer 2 turn on
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (делим на 1 частоту "кварца")
    RPOR6bits.RP13R = 19;         // set pin for PWM2 RB2 - RP13 Choose number of function carefully! 
    OC2RS = PR2;                  // period 
    OC2R = DutyCycle2;            // pulse width             
    OC2CON2bits.SYNCSEL = 0b01100;// sync source
    OC2CON2bits.OCTRIG = 0;       
    OC2CON1bits.OCTSEL = 0;       // choose timer 2 <=> 000  
    IEC0bits.T2IE = 0;            // timer interrupt is disable
    IEC0bits.OC1IE = 0;           // OC interrupt is disable 
    IEC0bits.U1RXIE = 0;          // U1RX interrupt is disable
    OC2CON1bits.OCM = 0b110;      // Edge-aligned PWM Mode on OCx 
}
