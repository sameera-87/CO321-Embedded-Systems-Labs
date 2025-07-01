#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count = 0;

int main(void){

    DDRB |= (1 << PB5);

    TCNT0 = 0;

    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x05; // prescalar 1024

    TIMSK0 |= (1 << TOIE0); // enable the interrupt that triggers when Timer0 overflows

    sei(); // enable global interrupts

    while(1){

    }
}

ISR(TIMER0_OVF_vect){
    overflow_count++;
    if(overflow_count >= 6){
        PORTB ^= (1 << 5);
        overflow_count = 0;
    }
}