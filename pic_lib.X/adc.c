#include "define.h"

void init_ADC()                   // ADC initialization 
{
    AD1PCFGL = 0xFFFF;            // all pins are set as digital  
    AD1PCFGLbits.PCFG11 = 0;      // set RB11 (AN11) as analog 
    //AD1PCFGLbits.PCFG12 = 0;      // set pin as analog RB12 (AN12)
    //AD1PCFGLbits.PCFG13 = 0;      // set pin as analog RB13 (AN13)   
    AD1CON2bits.VCFG = 0b000;     // Voltage Reference AVdd AVss
    AD1CON3bits.ADCS = 0;         // A/D Conversion Clock (max frequency <=> min period)                      
    AD1CSSL = 0;                  // do not scan ports 
    AD1CON3bits.SAMC = 0b11111;   // time of conductor charging 
    AD1CON1bits.SSRC = 0b111;     // (auto-convert) Internal counter ends sampling 
                                  // and starts conversion 
    AD1CON1bits.FORM = 0b00;      // Data Output Format 
    AD1CON1bits.ADON = 1;         // ADC start 
}

int read_ADC(int channel)         
{
    AD1CHS = channel;             // choose channel 
    AD1CON1bits.SAMP = 1;         // start conversion 
    while(!AD1CON1bits.DONE);     // wait until conversion ends 
    return ADC1BUF0;              // return result 
}
