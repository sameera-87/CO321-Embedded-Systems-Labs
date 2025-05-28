#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count = 0;

int main(void) {
    // Set PB5 as output
    DDRB |= (1 << PB5);


    TCNT0 = 0;
    TCCR0A = 0b00000000;  // Normal mode
    TCCR0B = 0b00000101;  // Prescaler = 1024

    // Enable Timer0 overflow interrupt
    TIMSK0 |= (1 << TOIE0);

    // Enable global interrupts
    sei();

    while(1) {
        // main loop does nothing, LED toggle handled in ISR
    }
}

// Timer0 overflow interrupt service routine
ISR(TIMER0_OVF_vect) {
    overflow_count++;
    if (overflow_count >= 6) {  // ~100 ms
        PORTB ^= (1 << PB5);
        overflow_count = 0;
    }
}