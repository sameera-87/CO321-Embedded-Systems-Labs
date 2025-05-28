#include <avr/io.h>

void delay_timer(){
    TCNT1 = 57723;

    TCCR1A = 0b0000000000000000;
    TCCR1B = 0b0000000000000101;  //Prescale is 1:1024 and normal mode
 
    while ((TIFR1 & 0x0001)==0){}

    TCCR1A = 0b0000000000000000;
    TCCR1B = 0b0000000000000000;

    TIFR1 =0x0001;  
}

int main(void){
    DDRB = DDRB|(1<<5);

    while(1){
        PORTB = PORTB ^ (1<<5);
        delay_timer();
    }
}