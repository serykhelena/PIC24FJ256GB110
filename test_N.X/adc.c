#include "define.h"

void init_ADC()                   // инициализация АЦП
{
    // настройка портов
    AD1PCFGL = 0xFFFF;            // все цифровые 
    AD1PCFGLbits.PCFG11 = 0;      // аналоговый сигнал RB11 (AN11)
    AD1PCFGLbits.PCFG12 = 0;      // set pin as analog RB12 (AN12)
    //AD1PCFGLbits.PCFG13 = 0;      // set pin as analog RB13 (AN13)
      
    AD1CON2bits.VCFG = 0b000;     //опорное напряжение AVdd AVss
    AD1CON3bits.ADCS = 0;         //выбор тактовой частоты 
                                  //(максимальная частота <-> минимальный период)
    AD1CSSL = 0;                  //не сканировать порты
    AD1CON3bits.SAMC = 0b11111;   //время заряда конденсатора
    AD1CON1bits.SSRC = 0b111;     // (auto-convert) Internal counter ends sampling 
                                  // and starts conversion 
    AD1CON1bits.FORM = 0b00;      //формат вывода 
    AD1CON1bits.ADON = 1;         //модуль АЦП старт
}

int read_ADC(int channel)         //чтение значения с АЦП-модуля
{
    AD1CHS = channel;             //выбор канала
    AD1CON1bits.SAMP = 1;         //начать преобразование
    while(!AD1CON1bits.DONE);     //дождаться пока окончится преобразование
    return ADC1BUF0;              //вернуть результат
}
