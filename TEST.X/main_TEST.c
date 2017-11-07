
#include "pragma.h"

#define FOSC        (32000000ULL)
#define FCY         16000000

#include "xc.h"
#include <libpic30.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>




int main(void) {
    
    TRISEbits.TRISE9 = 0;       // set pin as output
    
    while(1) 
    {
        LATEbits.LATE9 = 1;
        __delay_ms(1000); 
        LATEbits.LATE9 = 0;
        __delay_ms(1000);
        
    }
    return 0;
}
