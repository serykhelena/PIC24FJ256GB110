#include "define.h"

void init_UART1()                 //инициализация модуля 1 UART
{
   /*Настройка_start*/
    U1MODEbits.UARTEN = 0;        //выключить модуль UART для надежности 
    U1MODE = 0;                   //выключить все порты UARTU1MODEbits.BRGH = 1; 
    U1BRG = BAUDRATEREG;          //регистр установки скорости обмена данными          
    U1MODEbits.BRGH = 1;          //чтобы получить более высокую скорость передачи
    U1STA = 0;                    //регист контроля и управления 
    U1MODEbits.UARTEN = 1;        //включить модуль UART
    U1STAbits.UTXEN = 1;          //разрешаем передавать данные
    IEC0bits.U1RXIE = 0;            //разрешаем прерывания по приёму данных 
    IPC2bits.U1RXIP  =  0b001;    // interrupt receive level 1 
    IFS0bits.U1RXIF = 0;            //обнуляем флаг(датчик) приёма
    /*Настройка_end*/ 
}

char get_char_UART1()             //приём символа по UART 1
{
    /*Приём символа_start*/
    char rv_simv;                 //принимаемый символ
    while(U1STAbits.URXDA == 0)
    {
    };  //проверяем буффер приёма, ждём, когда придёт хотя бы один символ
    //LATEbits.LATE9 =! LATEbits.LATE9;
    rv_simv = U1RXREG;            //символ пришёл, берём его из регистра приёмника
    IFS0bits.U1RXIF = 0;          //обнуляем флаг(датчик) приёма
    //U1STAbits.OERR = 0;          //обнуляем флаг(датчик) приёма
    return rv_simv;               //возвращает значение принятого символа
    /*Приём символа_end*/
}

void put_char_UART1(char tr_simv) //передача символа по UART 1
{
    /*Передача байта данных_start*/
    
    while (U1STAbits.UTXBF == 1);       //ждём, чтобы буфер передачи освободился
    U1TXREG = tr_simv;                  //берём символ для передачи из регистра передачи
    /*Передача байта данных_end*/
}

void send_data_UART1(int data_tx)           //отправка 16 бит данных по UART
{
    char data_h = (char) (data_tx >> 8);   //записываем первые  бит
    char data_l = (char) data_tx;          //записываем вторые 8 бит
    while(!U1STAbits.TRMT);                //ждём, чтобы регистр отслеживающий передачу стал свободен
    U1TXREG = data_h;                      //посылаем старшую часть
    while(!U1STAbits.TRMT);                //ждём, чтобы регистр отслеживающий передачу стал свободен
    U1TXREG = data_l;                      //посылаем младшую часть       
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
