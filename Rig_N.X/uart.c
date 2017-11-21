#include "define.h"

void init_UART1()                 //������������� ������ 1 UART
{
   /*���������_start*/
    U1MODEbits.UARTEN = 0;        //��������� ������ UART ��� ���������� 
    U1MODE = 0;                   //��������� ��� ����� UARTU1MODEbits.BRGH = 1; 
    U1BRG = BAUDRATEREG;          //������� ��������� �������� ������ �������          
    U1MODEbits.BRGH = 1;          //����� �������� ����� ������� �������� ��������
    U1STA = 0;                    //������ �������� � ���������� 
    U1MODEbits.UARTEN = 1;        //�������� ������ UART
    U1STAbits.UTXEN = 1;          //��������� ���������� ������
    IEC0bits.U1RXIE = 0;            //��������� ���������� �� ����� ������ 
    IPC2bits.U1RXIP  =  0b001;    // interrupt receive level 1 
    IFS0bits.U1RXIF = 0;            //�������� ����(������) �����
    /*���������_end*/ 
}

char get_char_UART1()             //���� ������� �� UART 1
{
    /*���� �������_start*/
    char rv_simv;                 //����������� ������
    while(U1STAbits.URXDA == 0)
    {
    };  //��������� ������ �����, ���, ����� ����� ���� �� ���� ������
    //LATEbits.LATE9 =! LATEbits.LATE9;
    rv_simv = U1RXREG;            //������ ������, ���� ��� �� �������� ��������
    IFS0bits.U1RXIF = 0;          //�������� ����(������) �����
    //U1STAbits.OERR = 0;          //�������� ����(������) �����
    return rv_simv;               //���������� �������� ��������� �������
    /*���� �������_end*/
}

void put_char_UART1(char tr_simv) //�������� ������� �� UART 1
{
    /*�������� ����� ������_start*/
    
    while (U1STAbits.UTXBF == 1);       //���, ����� ����� �������� �����������
    U1TXREG = tr_simv;                  //���� ������ ��� �������� �� �������� ��������
    /*�������� ����� ������_end*/
}

void send_data_UART1(int data_tx)           //�������� 16 ��� ������ �� UART
{
    char data_h = (char) (data_tx >> 8);   //���������� ������  ���
    char data_l = (char) data_tx;          //���������� ������ 8 ���
    while(!U1STAbits.TRMT);                //���, ����� ������� ������������� �������� ���� ��������
    U1TXREG = data_h;                      //�������� ������� �����
    while(!U1STAbits.TRMT);                //���, ����� ������� ������������� �������� ���� ��������
    U1TXREG = data_l;                      //�������� ������� �����       
}

void send_string_UART1 (char *string)
{
    unsigned char c; 
    while( (c = *(string++)) )
        put_char_UART1(c);
}

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
