#include <avr/io.h>

void delay_timer500ms(){

    TCNT1 = 57725; // set initial count value (65536 + 1 - 7812)

    TCCR1A = 0x0000; // set the timer mode to normal
    TCCR1B = 0x0005; // set prescalar as 1024

    while((TIFR1 & 0x0001) == 0); // Wait until the timer overflow

    TCCR1A = 0x0000; // clear the timers
    TCCR1B = 0x0000; 

    TIFR1 = 0x0001; // clear the overflow bit (w1c). This is also a 8 bit register
}

int main(void){

    DDRB |= (1 << 5);

    while(1){
        PORTB ^= (1 << 5);
        delay_timer500ms();
    }
}