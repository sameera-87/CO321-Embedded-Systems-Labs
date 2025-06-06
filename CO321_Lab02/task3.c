#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t count = 0;

ISR(INT0_vect) {
    _delay_ms(50);
    count++;
    PORTB = count & 0x3F; 
}

int main(void) {
    
    DDRB = 0x3F;

    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    /*
    * Enables interrupt 0
    */
    EIMSK |= (1 << INT0);

    /*
    * EICRA = External Interrupt Control Register A
    * ISC01 = 2
    * ISC00 = 1
    * That is why the bitwise or operation is used here
    */
    EICRA |= (1 << ISC01) | (1 << ISC00); 

    sei();

    while (1); 
}