#include "define.h"

void init_ADC()                   // ������������� ���
{
    // ��������� ������
    AD1PCFGL = 0xFFFF;            // ��� �������� 
    AD1PCFGLbits.PCFG11 = 0;      // ���������� ������ RB11 (AN11)
    AD1PCFGLbits.PCFG12 = 0;      // set pin as analog RB12 (AN12)
    //AD1PCFGLbits.PCFG13 = 0;      // set pin as analog RB13 (AN13)
      
    AD1CON2bits.VCFG = 0b000;     //������� ���������� AVdd AVss
    AD1CON3bits.ADCS = 0;         //����� �������� ������� 
                                  //(������������ ������� <-> ����������� ������)
    AD1CSSL = 0;                  //�� ����������� �����
    AD1CON3bits.SAMC = 0b11111;   //����� ������ ������������
    AD1CON1bits.SSRC = 0b111;     // (auto-convert) Internal counter ends sampling 
                                  // and starts conversion 
    AD1CON1bits.FORM = 0b00;      //������ ������ 
    AD1CON1bits.ADON = 1;         //������ ��� �����
}

int read_ADC(int channel)         //������ �������� � ���-������
{
    AD1CHS = channel;             //����� ������
    AD1CON1bits.SAMP = 1;         //������ ��������������
    while(!AD1CON1bits.DONE);     //��������� ���� ��������� ��������������
    return ADC1BUF0;              //������� ���������
}
