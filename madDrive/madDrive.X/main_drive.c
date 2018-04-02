
#include "pragma.h"
#include "define.h"
#include "timer.h"
#include "adc.h"
#include "uart.h"
#include "pwm.h"

#define DESIRE_DISTANCE_CM 20
#define RADIUS_WHEEL_CM 4
#define GEAR_RATIO 0.0344

int Hall, prevHall = 0; 
unsigned int HallCounter = 0, prevHallCounter = 0, RotCounter = 0;
int direction_rot = 0;
int start_flag = 0;

int counter = 0;
int angle = 2540;
int servo_OC = 0; 
float S = 0, preS = 0, d_S = 0;
int counter_speed = 0;
float speed = 0;

void __attribute__ ((interrupt, auto_psv)) _T1Interrupt(void) //прерывание по таймеру 1 мс
{
    counter += 1;
        if(counter == 40)
        {
            angle = angle + 104;
            if(angle == 3580)
            {
                angle = 2540;
                send_string_UART1("          ");
            }
            OC1R = angle;
            servo_OC = read_ADC(11);
            send_number_UART1(servo_OC);
            put_char_UART1(' ');
            counter = 0;
        }
    IFS0bits.T1IF = 0;                   //Очищаем флаг по прерыванию таймера 1
}



void __attribute__ ((interrupt, auto_psv)) _T5Interrupt(void) //прерывание по таймеру 20 мс
{
    
    counter_speed += 1;
        if(counter_speed == 5)                                // каждые 100 мс
        {
            preS = S;
            S = 2 * 3.14 * RADIUS_WHEEL_CM * GEAR_RATIO * (HallCounter);
            d_S = S - preS; 
            
//            preS = S;
//            d_S = S - preS; 
            speed = 10 * d_S; 
//            send_number_UART1((int)(speed));
            send_number_UART1(speed);
            put_char_UART1(' ');
            
            counter_speed = 0;
        }
    IFS1bits.T5IF = 0;                   //Очищаем флаг по прерыванию таймера 5
}




void __attribute__((__interrupt__, no_auto_psv)) _CNInterrupt(void) // interrupt for Hall sensors
{   
    
    int dig;                    // variable for decimal combination from binary
    start_flag += 1;
    dig = (PORTG >> 6)&7;
    
//    send_number_UART1(Hall);
//    put_char_UART1(' ');
//    send_number_UART1(prevHall);
////    put_char_UART1('0'+dig);
//    put_char_UART1(' ');
//   
    switch (dig)                // recoding Hall combination into ordered combination
    {               
        case 3:
            Hall = 1;
            break;
        case 2:
            Hall = 2; 
            break;
        case 6:
            Hall = 3;
            break;
        case 4:
            Hall = 4;
            break;
        case 5:
            Hall = 5;
            break;
        case 1:
            Hall = 6;
            break;
        default:
            send_string_UART1("Error or Start/Stop point");
            put_char_UART1(' ');
            Hall = 0;
            break;
    }
    

    // rotation direction detection
    if ((Hall == 1 && prevHall == 6) || (Hall == 6 && prevHall == 1))
    {
        if (Hall > prevHall)
        {
            HallCounter += 1; 
//            put_char_UART1('F');
        }
        if (Hall < prevHall)
        {
            if(start_flag > 2)
            {
                HallCounter -= 1;
            }
//            put_char_UART1('B');
        }
    }
    else
    {                           
        if (Hall > prevHall)
        {
            if(start_flag > 2)
            {
                HallCounter -= 1;
            }
//            put_char_UART1('N');
        }
        if (Hall < prevHall)
        {
            
                HallCounter += 1; 
//            put_char_UART1('V');
        }
    }
//    send_number_UART1(HallCounter);
    
    IFS1bits.CNIF = 0;   
}


 int rot = 0;

void car_go_on_dist(int dist, int duty2)
{
    
    rot = (dist)/(2 * 3.14 * RADIUS_WHEEL_CM * GEAR_RATIO);
    S = 2 * 3.14 * RADIUS_WHEEL_CM * GEAR_RATIO * (HallCounter);
    if((HallCounter) <= rot)
    {
        OC2R = duty2;
    }
    else
    {
        OC2R = 3020;
    }
    
}

int main(void) {
    
    AD1PCFGL = 0xFFFF;                 // set all ports as digital
     
     /* UART */  
    RPINR18bits.U1RXR = 28;             // set RP28 (RB4) for data receiving (RX)   
    RPOR9bits.RP18R = 3;                // set RP18 (RB5) for data transmitting (TX)
    /*******/
    
    /*CN settings*/
    TRISGbits.TRISG8 = 1;               // pin RG8 (CN10) set as input - Hall sensor #1
    CNPU1bits.CN10PUE = 0;              // internal Pull-up resistor is disEnable for pin RG8
    CNPD1bits.CN10PDE = 1;              // internal Pull-down resistor is Enable for pin RG8
    CNEN1bits.CN10IE = 1;               // Change Notofication on CN10 pin RG8 is Enable
    
    TRISGbits.TRISG7 = 1;              // pin RG7 (CN9) set as input - Hall sensor #2
    CNPU1bits.CN9PUE = 0;              // internal Pull-up resistor is disEnable for pin RG7
    CNPD1bits.CN9PDE = 1;              // internal Pull-down resistor is Enable for pin RG7
    CNEN1bits.CN9IE = 1;               // Change Notofication on CN9 pin RG7 is Enable
    
    TRISGbits.TRISG6 = 1;              // pin RG6 (CN8) set as input - Hall sensor #3
    CNPU1bits.CN8PUE = 0;              // internal Pull-up resistor is disEnable for pin RG6
    CNPD1bits.CN8PDE = 1;              // internal Pull-down resistor is Enable for pin RG6
    CNEN1bits.CN8IE = 1;               // Change Notofication on CN8 pin RG8 is Enable
    
    IEC1bits.CNIE = 1;                  // Interrupt for ICN is Enable
    IFS1bits.CNIF = 0;                  // Clear Flag for CN
    /***************/
    
    
    TRISGbits.TRISG9 = 0;
    
    init_UART1();
    init_PWM1();
    init_PWM2();
    init_ADC();
//    init_timer5();
//    init_timer1();
    
    int right_s = 0, left_s = 0;
    int right_s_n = 0, left_s_n = 0;
    
//   signed int def = 0;
    
    int i=0,  fin=100;
    long sum=0;
    
    while(1)
    {
        for(i=0;i<fin;i++)
        {
            right_s = read_ADC(11);
            
            sum = right_s + sum;
            
        }
        
        sum = sum/fin;
        send_number_UART1(sum);
        
//        left_s = read_ADC(12);
//        
//        right_s_n = (10283/(right_s-5))-4;  
//        left_s_n = (10283/(left_s-5))-4;  
//        
//        send_number_UART1(right_s);
        put_char_UART1(' ');
        
//        send_number_UART1(left_s_n);
//        put_char_UART1(' ');
//        
        
        __delay_ms(300);
        i=0;

//        OC2R = 3060;
//        
//        prevHall = Hall;
//        
        
       
        
 

    }
    
    
    return 0;
}
