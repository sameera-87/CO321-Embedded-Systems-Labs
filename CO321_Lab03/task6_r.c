#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count = 0;

int main(void){

    DDRB |= (1 << PB0);
    DDRB |= (1 << PB5);

    TCNT0 = 0; // setting initial value to 0
    TCCR0A = 0x00; // setting to the normal mode
    TCCR0B = 0x05; // prescalar 1024

    TCNT1 = 57723; // setting initial value
    TCCR1A = 0x00;
    TCCR1B = 0x05;

    TIMSK0 |= (1 << TOIE0);
    TIMSK1 |= (1 << TOIE1);

    sei();

    while(1){

    }
}


ISR(TIMER0_OVF_vect){
    overflow_count++;
    if(overflow_count >= 3){
        PORTB ^= (1 << PB0);
        overflow_count = 0;
    }
}

ISR(TIMER1_OVF_vect){
    PORTB ^= (1 << PB5);
    TCNT1 = 57723;
}