#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count = 0;



int main(void){
    DDRB |= (1 << PB5);
    DDRB |= (1 << PB0);

    TCNT0 = 0;
    TCCR0A = 0x00;
    TCCR0B = 0b00000101;  // Prescaler 1:1024
    

    TCNT1 = 57723;

    TCCR1A = 0b0000000000000000;
    TCCR1B = 0b0000000000000101;  // Prescaler = 1024

    // Enable Timer0 overflow interrupt
    TIMSK0 |= (1 << TOIE0);
    // Enable Timer0 overflow interrupt
    TIMSK1 |= (1 << TOIE1);

    // Enable global interrupts
    sei();

    while(1) {
        // main loop does nothing, LED toggle handled in ISR
    }
}

ISR(TIMER0_OVF_vect) {
    overflow_count++;
    if (overflow_count >= 3) {  // ~50 ms
        PORTB ^= (1 << PB5);    // Toggle LED
        overflow_count = 0;
    }
}

ISR(TIMER1_OVF_vect) {
    PORTB = PORTB ^ (1<< PB0);
    TCNT1 = 57723;
}