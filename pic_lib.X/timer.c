#include "define.h"

void init_timer1()                      // initialization of timer 1
{
    T1CON = 0x00;                       // stop timer and reset registers 
    TMR1 = 0x00;                        // clear register (start value)
        
    T1CONbits.TCKPS = 0b01;             // prescaler 1:8
    T1CONbits.TCS = 0;                  // Timer1 Clock Source = Internal clock (FOSC/2)
    T1CONbits.TGATE = 0;                // Timer1 Gated Time Accumulation disable 
    T1CONbits.TSYNC = 0;                // Do not synchronize external clock input
    PR1 = TIMER1;                       // period 1 ms 
    
    IPC0bits.T1IP = 0b001;              // interrupt priority level 1
    IFS0bits.T1IF = 0;                  // clear timer interrupt sensor (flag) 
    IEC0bits.T1IE = 0;                  // turn off timer interrupt 
    
    T1CONbits.TON = 1;                  // start timer 1 
}

void init_timer3()                      // initialization of timer 3
{
    T3CON = 0x00;                       // stop timer and reset registers 
    TMR3 = 0x00;                        // clear register (start value)
    
    T3CONbits.TCKPS = 0;                // prescaler 1:1
    T3CONbits.TCS = 0;                  // Timer1 Clock Source = Internal clock (FOSC/2)
    T3CONbits.TGATE = 0;                // Timer1 Gated Time Accumulation disable                
    PR3 = TIMER3;                       // period (max value) 
    
    IFS0bits.T3IF = 0;                  // clear timer interrupt sensor (flag) 
    IEC0bits.T3IE = 0;                  // turn off timer interrupt
    
    T3CONbits.TON = 1;                  // start timer 3
}
