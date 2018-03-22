
#include "pragma.h"
#include "define.h"

#include "timer.h"
#include "adc.h"
#include "uart.h"
#include "pwm.h"
#include "ic.h"

/* UART 1 Receive Interrupt */
void __attribute__ ((interrupt, auto_psv)) _U1RXInterrupt(void)
{
    
    IFS0bits.U1RXIF = 0;                    // clear RX Interrupt sensor (flag) 
}

/* UART 2 Receive Interrupt */
void __attribute__ ((interrupt, auto_psv)) _U2RXInterrupt(void)
{
    
    IFS1bits.U2RXIF = 0;                    // clear RX Interrupt sensor (flag) 
}

/* IC1 Interrupt */
void __attribute__ ((interrupt, auto_psv)) _IC1Interrupt(void)  
{
   // is IC2BUF and IC4BUF EMPTY?
   if ((IC2CON1bits.ICBNE)&&(IC4CON1bits.ICBNE)) 
   {

   }   
   IFS0bits.IC1IF  =  0;                   // clear IC1 Interrupt sensor (flag) 
}

/* CN Interrupt */
void __attribute__((__interrupt__, no_auto_psv)) _CNInterrupt(void) 
{   
    
    IFS1bits.CNIF = 0;                      // clear CN Interrupt sensor (flag)   
}

/* Timer 1 Interrupt */
void __attribute__ ((interrupt, auto_psv)) _T1Interrupt(void) 
{        
    
    IFS0bits.T1IF = 0;                     // clear Timer 1 Interrupt sensor (flag) 
}

int main(void)
{
    AD1PCFGL = 0xFFFF;                      // set all pins as digital (just in case) 
    
    /*  IC  */
    TRISBbits.TRISB8 = 1;              // RB8 input IC1 & IC2 - steering wheels
    TRISBbits.TRISB9 = 1;              // RB9 input IC3 & IC4 - driving wheels
    
    RPINR7bits.IC1R = 8;               // set pin RP8 (RB8) for IC1 
    RPINR7bits.IC2R = 8;               // set pin RP8 (RB8) for IC2 
    
    RPINR8bits.IC3R = 9;               // set pin RP9 (RB9) for IC3 
    RPINR8bits.IC4R = 9;               // set pin RP9 (RB9) for IC4 
    /*--------------------------------------------------*/
    
    /* ICN */   
    TRISGbits.TRISG8 = 1;              // pin RG8 (CN10) set as input - Hall sensor #1
    CNPU1bits.CN10PUE = 0;             // internal Pull-up resistor is disEnable for pin RG8
    CNPD1bits.CN10PDE = 1;             // internal Pull-down resistor is Enable for pin RG8
    CNEN1bits.CN10IE = 1;              // Change Notofication on CN10 pin RG8 is Enable
    
    TRISGbits.TRISG7 = 1;              // pin RG7 (CN9) set as input - Hall sensor #2
    CNPU1bits.CN9PUE = 0;              // internal Pull-up resistor is disEnable for pin RG7
    CNPD1bits.CN9PDE = 1;              // internal Pull-down resistor is Enable for pin RG7
    CNEN1bits.CN9IE = 1;               // Change Notofication on CN9 pin RG7 is Enable
    
    TRISGbits.TRISG6 = 1;              // pin RG6 (CN8) set as input - Hall sensor #3
    CNPU1bits.CN8PUE = 0;              // internal Pull-up resistor is disEnable for pin RG6
    CNPD1bits.CN8PDE = 1;              // internal Pull-down resistor is Enable for pin RG6
    CNEN1bits.CN8IE = 1;               // Change Notofication on CN8 pin RG8 is Enable
    
    IEC1bits.CNIE = 1;                  // Interrupt for ICN is Enable
    IFS1bits.CNIF = 0;                  // Clear Flag for CN
    /*-------------------------------------------------*/
    
    
    init_PWM1(); 
    init_PWM2();
    init_ADC();
    init_timer3();
    init_timer1();
    init_UART1();
    init_UART2();
    init_IC1();
    init_IC2();
    init_IC3();
    init_IC4();

    while(1)
    {

    }
    return 0;
}
