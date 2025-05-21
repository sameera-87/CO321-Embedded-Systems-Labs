#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t value = 0; 


ISR(INT0_vect) {
    _delay_ms(500);
    value = (value << 1); 
    PORTB = value & 0x3F; 
}


ISR(INT1_vect) {
    _delay_ms(500);
    value = (value << 1) | 0x01; 
    PORTB = value & 0x3F;        
}

int main(void) {
    
    DDRB = 0x3F; 

    DDRD &= ~((1 << PD2) | (1 << PD3));

    PORTD |= (1 << PD2) | (1 << PD3);

    EIMSK |= (1 << INT0) | (1 << INT1);

    EICRA |= (1 << ISC01);   // Set ISC01 = 1
    EICRA &= ~(1 << ISC00);  // Set ISC00 = 0

    EICRA |= (1 << ISC11);   
    EICRA &= ~(1 << ISC10);

    // EICRA |= (1 << ISC01) | (1 << ISC11);  
    // EICRA &= ~((1 << ISC00) | (1 << ISC10)); 

    sei();

    while (1){

    };
}