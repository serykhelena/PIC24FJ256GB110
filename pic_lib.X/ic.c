#include "define.h"

void init_IC1()                           // Steering wheels - rising
{
    IFS0bits.IC1IF  =  0;                 // clear interrupt sensor (flag) IC1
    IEC0bits.IC1IE  =  0;                 // IC1 interrupt enable    
    IPC0bits.IC1IP  =  0b111;             // interrupt priority level 7 
   
    IC1CON1 = 0x00;                       // clear IC1 CON1
    IC1CON2 = 0x00;                       // clear IC1 CON2
    IC1CON1bits.ICTSEL = 0b000;           // choose timer 3
    IC1CON1bits.ICI = 0b00;               // interuupt each event 
    IC1CON1bits.ICM = 0b011;              // working mode - every rising 
    IC1CON2bits.TRIGSTAT = 1;             // trigger + running
}

void init_IC2()                           // Steering wheels - falling
{
    IFS0bits.IC2IF  =  0;                 // clear interrupt sensor (flag) IC2
    IEC0bits.IC2IE  =  0;                 // interrupt disable IC2   
    IPC1bits.IC2IP  =  0b000;             // interrupt priority level 0
            
    IC2CON1 = 0x00;                       // clear IC2 CON1
    IC2CON2 = 0x00;                       // clear IC2 CON2
    IC2CON1bits.ICTSEL = 0b000;           // choose timer 3
//    IC2CON1bits.ICI = 0b10;               // no interrupts  
    IC2CON1bits.ICM = 0b010;              // working mode - every falling
    IC2CON2bits.TRIGSTAT = 1;             // trigger + running
}

void init_IC3()                           // Driving wheels - rising
{
    IFS2bits.IC3IF  =  0;                 // clear interrupt sensor (flag) IC3
    IEC2bits.IC3IE  =  0;                 // interrupt IC3 disable   
    IPC9bits.IC3IP  =  0b001;             // interrupt priority level 0
                              
    IC3CON1 = 0x00;                       // clear IC3 CON1
    IC3CON2 = 0x00;                       // clear IC3 CON2
    IC3CON1bits.ICTSEL = 0b000;           // choose timer 3
//    IC3CON1bits.ICI = 0b10;               // no interrups
    IC3CON1bits.ICM = 0b011;              // working mode - every rising
    IC3CON2bits.TRIGSTAT = 1;             // trigger + running
}

void init_IC4()                           // Driving wheels - falling
{
    IFS2bits.IC4IF  =  0;                 // clear interrupt sensor (flag) IC4
    IEC2bits.IC4IE  =  0;                 // interrupt IC4 disable  
    IPC9bits.IC4IP  =  0b000;             // interrupt priority level 0
    
    IC4CON1 = 0x00;                        // clear IC4 CON1
    IC4CON2 = 0x00;                        // clear IC4 CON2
    IC4CON1bits.ICTSEL = 0b000;            // choose timer 3
//    IC2CON1bits.ICI = 0b10;                // no interrups 
    IC4CON1bits.ICM = 0b010;               // working mode - every falling   
    IC4CON2bits.TRIGSTAT = 1;              // trigger + running
}
