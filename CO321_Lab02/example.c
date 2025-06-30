#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void){
    DDRD &= ~(1 << PD2);     // Set PD2 (INT0) as input
    PORTD |= (1 << PD2);     // Enable internal pull-up resistor

    DDRB |= (1 << PB0);      // Set PB0 as output
    PORTB &= ~(1 << PB0);    // Turn LED OFF initially

    // Configure INT0 for rising edge detection
    EICRA |= (1 << ISC01) | (1 << ISC00);

    EIMSK |= (1 << INT0);    // Enable external interrupt INT0
    sei();                   // Enable global interrupts

    while (1) {
        // Do nothing here; interrupt handles the LED
    }

    return 0;
}

ISR(INT0_vect){
    PORTB |= (1 << PB0);     // Turn LED ON when button is pressed
    _delay_ms(BLINK_DELAY_MS);
    PORTB &= ~(1 << PB0);    // Optional: Turn LED OFF again after delay
}
