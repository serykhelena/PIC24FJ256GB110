#include "define.h"
#include "uart.h"

void init_UART1()                       // initialization of UART 1
{
    /* UART */  
    RPINR18bits.U1RXR = 28;             // set RP28 -> RB4 for receiving data  (RX) 
                                        // (green = TX)    
    RPOR9bits.RP18R = 3;                // set RP18->RB5 for transmitting data (TX)
                                        // (white = RX) 
    /*******/    
    U1MODEbits.UARTEN = 0;              // turn off UART (just in case)  
    U1MODE = 0;                         // reset all pins (just in case)  
    U1BRG = BAUDRATEREG;                // data rate           
    U1MODEbits.BRGH = 1;                // to get HIGHER date rate 
    U1STA = 0;                          // reset all pins in control register  
    U1MODEbits.UARTEN = 1;              // start UART
    U1STAbits.UTXEN = 1;                // data transmittion is allowed 
    IEC0bits.U1RXIE = 0;                // turn off UART receive interrupt  
    IPC2bits.U1RXIP  =  0b001;          // interrupt receive level 1 
    IFS0bits.U1RXIF = 0;                // reset receive sensor (flag) 
}

char get_char_UART1()                   // receive 8 bits (1 byte) UART 1
{
    char rv_simv;                       // receiving symbol 
    while(U1STAbits.URXDA == 0);        // check RX buffer, wait until even 1 bit will be received 
    rv_simv = U1RXREG;                  // get symbol from RX register 
    IFS0bits.U1RXIF = 0;                // reset RX sensor (flag) 
    return rv_simv;                     // return value of receving symbol 
}

void put_char_UART1(char tr_simv)       // transmit 8 bits (1 byte) UART 1
{
    while (U1STAbits.UTXBF == 1);       // wait until TX buffer will be empty 
    U1TXREG = tr_simv;                  // get symbol from transmitting register 
}

void send_data_UART1(int data_tx)       // transmit 16 bits (2 bytes) UART1
{
    char data_h = (char) (data_tx >> 8);// get first (high) 8 bits 
    char data_l = (char) data_tx;       // get next (low) 8 bits 
    while(!U1STAbits.TRMT);             // wait until U1STA will be empty 
    U1TXREG = data_h;                   // transmit high 8 bits 
    while(!U1STAbits.TRMT);             // wait until U1STA will be empty
    U1TXREG = data_l;                   // transmit next (low) 8 bits       
}

void send_string_UART1(char string[])
{
    uint16_t i = 0;
    for( i = 0; i <= (strlen(string) - 1); i++)
    {
        put_char_UART1(string[i]);   
    }
}

void send_number_UART1(uint16_t digit)
{
    char value[10];
    int i = 0;
    do
    {
        value[i++] = (char)(digit % 10) + '0';  //convert integer to character
        digit /= 10;
    } while(digit);
    while(i)                                    //send data
    {
        put_char_UART1(value[--i]); 
    }
    
}

void test_UART1(char send_byte, char send_str[], uint16_t send_number)
{
    put_char_UART1(send_byte);
    send_string_UART1( send_str );
    send_number_UART1(send_number);  
}

void easy_test_UART1( )
{
    put_char_UART1('I');
    send_string_UART1(" am working! ");
    send_number_UART1(1000); 
    put_char_UART1(' ');
}

void init_UART2()                 // initialization of UART 2
{
    /* UART */  
    RPINR19bits.U2RXR = 8;       // set RP8 -> RB8 for receiving data  (RX) 
                                 // (green = TX)    
    RPOR4bits.RP9R = 3;          // set RP9->RB9 for transmitting data (TX)
                                 // (white = RX) 
    /*******/   
       
    U2MODEbits.UARTEN = 0;        // turn off UART (just in case)  
    U2MODE = 0;                   // reset all pins (just in case)  
    U2BRG = BAUDRATEREG;          // data rate           
    U2MODEbits.BRGH = 1;          // to get HIGHER date rate 
    U2STA = 0;                    // reset all pins in control register 
    U2MODEbits.UARTEN = 1;        // start UART
    U2STAbits.UTXEN = 1;          // data transmittion is allowed
    IEC1bits.U2RXIE = 0;          // turn off UART receive interrupt 
    IPC7bits.U2RXIP  =  0b001;    // interrupt receive level 1 
    IFS1bits.U2RXIF = 0;          // reset receive sensor (flag) 
}

char get_char_UART2()             // receive 8 bits (1 byte) UART 2
{
    char rv_simv;                 // receiving symbol 
    while(U2STAbits.URXDA == 0);  // check RX buffer, wait until even 1 bit will be received 
    rv_simv = U2RXREG;            // get symbol from RX register 
    IFS1bits.U2RXIF = 0;          // reset RX sensor (flag) 
    return rv_simv;               // return value of receving symbol 
}

void put_char_UART2(char tr_simv) // transmit 8 bits (1 byte) UART 2
{
    while (U2STAbits.UTXBF == 1); // wait until TX buffer will be empty 
    U2TXREG = tr_simv;            // get symbol from transmitting register 
}

