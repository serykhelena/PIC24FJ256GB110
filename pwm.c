#include "define.h"

void init_PWM1 ()                 // ������������� ���1 - steering wheels
{
    TMR2 = 0;                     // ��������� �������� �������
    PR2 =  Period;                // �������� �������� �������
    T2CONbits.TCKPS = 0b01;       // ������������ 1:8  
    T2CONbits.TON = 1;            // ����� ������ 2 
    
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (����� �� 1 ������� "������")
    RPOR0bits.RP1R = 18;          // ����� ���� ��� ��� RB1 - RP1
    OC1R = DutyCycle1;             // ����������
    OC1RS = PR2;                  // ������ 
    OC1CON2bits.SYNCSEL = 0b01100;// sync source
    OC1CON2bits.OCTRIG = 0;       
    OC1CON1bits.OCTSEL = 0;       // ����� ������ 2 <=> 000 
    IEC0bits.T2IE = 0;            // ���������� ���������� �� �������
    IEC0bits.OC1IE = 0;           // ���������� ���������� �� ��
    IEC0bits.U1RXIE = 0; 
    OC1CON1bits.OCM = 0b110;      // ����� ������ ��� Edge-aligned PWM Mode on OCx 
}

void init_PWM2 ()                  // ������������� ��� - driving wheels
{
    TMR2 = 0;                     // ��������� �������� �������
    PR2 =  Period;                // �������� �������� �������
    T2CONbits.TCKPS = 0b01;       // ������������ 1:8  
    T2CONbits.TON = 1;            // ����� ������ 2 
    
    CLKDIVbits.RCDIV = 0b000;     // FRC Postscaler bits (����� �� 1 ������� "������")
    RPOR6bits.RP13R = 19;        // ����� ���� ��� ��� RB3 - RP13 Choose number of function carefully! 
    OC2RS = PR2;                  //������ 
    OC2R = DutyCycle2;             // ����������
                   
    OC2CON2bits.SYNCSEL = 0b01100;// sync source
    OC2CON2bits.OCTRIG = 0;       
    OC2CON1bits.OCTSEL = 0;       // ����� ������ 2 <=> 000 
    IEC0bits.T2IE = 0;            // ���������� ���������� �� �������
    IEC0bits.OC1IE = 0;           // ���������� ���������� �� ��
    IEC0bits.U1RXIE = 0; 
    OC2CON1bits.OCM = 0b110;      // ����� ������ ��� Edge-aligned PWM Mode on OCx 
}
