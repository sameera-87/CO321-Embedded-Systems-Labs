#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect) {
    _delay_ms(50);
    PORTB ^= (1 << PB0);
}

int main(void) {
    
    DDRB |= (1 << PB0);
    
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);
 
    EIMSK |=  (1 << INT0);
 
    EICRA |= (1 << ISC00) | (1 << ISC01);
    
    sei();

    while (1) {
        
    }
}