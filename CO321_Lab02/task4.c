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

    /*
    * Set 1 to the end by 0x01
    */
    value = (value << 1) | 0x01; 
    PORTB = value & 0x3F;        
}

int main(void) {
    
    /*
    * Set outputs
    */
    DDRB = 0x3F; 

    /*
    * Set input for PD2 and PD3
    * Where the interrupts connects
    * pins PD2 and PD3 designated as INT0, and INT1 respectively
    */
    DDRD &= ~((1 << PD2) | (1 << PD3));
    
    /*
    * Enables internal pull up resistors
    */
    PORTD |= (1 << PD2) | (1 << PD3);

    /*
    * INTx bit located in the EIMSK (External Interrupt Mask Register) register.
    */
    EIMSK |= (1 << INT0) | (1 << INT1);

    /*
    * EICRA = External Interrupt Control Register A.
    */
    EICRA |= (1 << ISC01);   // Set ISC01 = 1
    EICRA &= ~(1 << ISC00);  // Set ISC00 = 0

    EICRA |= (1 << ISC11);  // Set ISC11 = 1
    EICRA &= ~(1 << ISC10); // Clear ISC10 = 0

    // EICRA |= (1 << ISC01) | (1 << ISC11);  
    // EICRA &= ~((1 << ISC00) | (1 << ISC10)); 


    /*
    * Enables global interrupts
    */
    sei();

    while (1){

    };
}