#include "define.h"

void init_PWM1 ()                 // steering wheels
{
    TMR2 = 0;                     // start value for timer 2
    PR2 =  PERIOD_PWM;            // end value for timer 2 (period)
    T2CONbits.TCKPS = 0b01;       // prescaler 1:8  
    T2CONbits.TON = 1;            // start timer 2 
    
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (crystal clock divide by 1)
    RPOR0bits.RP1R = 18;          // choose pin for PWM (RB1 - RP1) Choose number of function carefully!! 
    OC1R = DUTYCYCLE1;            // dutycycle for PWM1
    OC1RS = PR2;                  // period 
    OC1CON2bits.SYNCSEL = 0b01100;// sync source with timer 2
    OC1CON2bits.OCTRIG = 0;       
    OC1CON1bits.OCTSEL = 0;       // choose timer 2 for PWM <=> 000 
    IEC0bits.T2IE = 0;            // turn off timer interrupt
    IEC0bits.OC1IE = 0;           // turn off OC interrupt 
    IEC0bits.U1RXIE = 0;          // turn off UART Receive interrupt
    OC1CON1bits.OCM = 0b110;      // choose Edge-aligned PWM Mode on OCx 
}

void init_PWM2 ()                 // driving wheels
{
    TMR2 = 0;                     // start value for timer 2
    PR2 =  PERIOD_PWM;            // end value for timer 2 (period) 
    T2CONbits.TCKPS = 0b01;       // prescaler 1:8   
    T2CONbits.TON = 1;            // start timer 2 
    
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (crystal clock divide by 1)
    RPOR6bits.RP13R = 19;         // choose pin for PWM RB2 - RP13 Choose number of function carefully!!  
    OC2RS = PR2;                  // period  
    OC2R = DUTYCYCLE2;            // dutycycle for PWM2              
    OC2CON2bits.SYNCSEL = 0b01100;// sync source with timer 2
    OC2CON2bits.OCTRIG = 0;       
    OC2CON1bits.OCTSEL = 0;       // choose timer 2 for PWM <=> 000  
    IEC0bits.T2IE = 0;            // turn off timer interrupt
    IEC0bits.OC1IE = 0;           // turn off OC interrupt
    IEC0bits.U1RXIE = 0;          // turn off UART Receive interrupt  
    OC2CON1bits.OCM = 0b110;      // choose Edge-aligned PWM Mode on OCx
}
