#include <avr/io.h>

void delay_timer2ms(void){

    TCNT0 = 131; // set initial count value

    TCCR0A = 0b00000000; // Set the timer mode to normal mode
    TCCR0B = 0b00000100; // prescalar in binary 1 : 256

    while((TIFR0 & 0x01) == 0);

    TCCR0A = 0b00000000; // clear the timers
    TCCR0B = 0b00000000;

    TIFR0 = 0x01; // W1C - Write 1 to clear
}

int main(void){
    DDRB = DDRB | (1 << 5);
    
    while(1){
        PORTB ^= (1 << 5);
        delay_timer2ms; 
    }
}