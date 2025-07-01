#include <avr/io.h>

void delay_timer0(){

    TCNT0 = 0x00; // Load the counter register with 0

    TCCR0A = 0x00; // set the timer to normal mode
    TCCR0B = 0x01; // No prescaling

    while((TIFR0 & 0x01) == 0); // wait until the timer overflow TOV0

    TCCR0A = 0x00; // clear the timer settings
    TCCR0B = 0x00; 

    TIFR0 =  0x01; // clear the timer overflow bit - W1c (write 1 to clear)
}

int main(void){

    DDRB = DDRB | (1 << 5);

    while(1){

        PORTB = PORTB | (1 << 5);
        delay_timer0();

        PORTB = PORTB & ~(1 << 5);
        delay_timer0();
    }
}