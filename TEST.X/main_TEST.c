
#include "pragma.h"
#include "define.h"


#include "timer.h"
#include "adc.h"
#include "uart.h"

int counter = 0;
int flag = 0;

void __attribute__ ((interrupt, auto_psv)) _T1Interrupt(void) //���������� �� ������� 1 ��
{
    counter = counter + 1;
    
    if(counter == 1)
    {
        LATEbits.LATE9 = 1;
    }
    if(counter == 2)
    {
        flag = read_ADC(11);
    }
    if(counter == 3)
    {
        LATEbits.LATE9 = 0;
    }
    if(counter == 6)
    {
        counter = 0;
    }
    
     
    IFS0bits.T1IF = 0;                   //������� ���� �� ���������� ������� 1
}


int main(void) {
//    init_ADC();
//    init_timer1();
    init_UART1();
    
    TRISBbits.TRISB4 = 1;               //RB4 = ���� ��� ����� (RX)
    TRISBbits.TRISB5 = 0;               //RB5 = ����� ��� �������� (TX)     
    RPINR18bits.U1RXR = 28;             //������ae� RP24 ��� ����� ������ (RX)   
    RPOR9bits.RP18R = 3;                //��������� RP18 ��� �������� ������ (TX)
    
    
    TRISEbits.TRISE9 = 0;       // set pin as output
    
    while(1);
    
    
    return 0;
}
