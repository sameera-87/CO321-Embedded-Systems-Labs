#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t count = 0;

ISR(INT0_vect){
    _delay_ms(50);
    count++;
    PORTB = count & 0x3F;
    
}

int main(void){

    DDRB |= 0x3F;

    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC00) | (1 << ISC01);

    sei();

    while(1){

    }
}