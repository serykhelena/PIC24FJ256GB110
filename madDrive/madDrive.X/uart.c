#include "define.h"

// UART module 1 initialization
void init_UART1()                 
{
    U1MODEbits.UARTEN = 0;        // turn off UART (just in case) 
    U1MODE = 0;                   // turn off all ports of UARTU1MODEbits.BRGH = 1; 
    U1BRG = BAUDRATEREG;          // set exchange data speed          
    U1MODEbits.BRGH = 1;          // to get higher speed
    U1STA = 0;                    // control register (just in case) 
    U1MODEbits.UARTEN = 1;        // turn on UART
    U1STAbits.UTXEN = 1;          // data transmitting is enable 
    IEC0bits.U1RXIE = 0;          // data transmitting interrupt is disable 
    IPC2bits.U1RXIP  =  0b001;    // receive data interrupt has level 1 priority (the highest level is 7)
    IFS0bits.U1RXIF = 0;          // reset receiving flag
}

// receive 8 bits (1 byte)
char get_char_UART1()             
{
    char rv_simv;                 // receiving byte
    while(U1STAbits.URXDA == 0);  // check receving buffer, wait until even 1 bit will be received
    rv_simv = U1RXREG;            // take byte from receiving register 
    IFS0bits.U1RXIF = 0;          // reset receiving flag
    return rv_simv;               // return received byte
}

// transmit 8 bits (1 byte)
void put_char_UART1(char tr_simv) 
{
    while (U1STAbits.UTXBF == 1);  // wait until buffer of transmitting become free 
    U1TXREG = tr_simv;             // take byte from transmitting register
}

// transmit 16 bits (2 bytes)
void send_data_UART1(int data_tx)           
{
    char data_h = (char) (data_tx >> 8);   // write first 8 bits (move it to the left)
    char data_l = (char) data_tx;          // write second 8 bits
    while(!U1STAbits.TRMT);                // wait until transmitting tracking register become free 
    U1TXREG = data_h;                      // transmit higher part 
    while(!U1STAbits.TRMT);                // wait until transmitting tracking register become free 
    U1TXREG = data_l;                      // transmit lower part        
}

// transmit string
void send_string_UART1 (char *string)
{
    unsigned char c; 
    while( (c = *(string++)) )
        put_char_UART1(c);
}

// transmit number as sequence of digits
void send_number_UART1(unsigned int digit)
{
    char value[10];
    int i = 0;
    do
    {
        value[i++] = (char)(digit % 10) + '0'; //convert integer to character
        digit /= 10;
    } while(digit);
    while(i) //send data
    {
        put_char_UART1(value[--i]); 
    }
}
