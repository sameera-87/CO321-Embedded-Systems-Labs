#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect) {
    _delay_ms(50);

    /*
    * toggles PB0 using XOR.
    */
    PORTB ^= (1 << PB0);
}

int main(void) {
    
    // Outputs are identified by setting the corresponding bit in DDRx to 1
    // Inputs are identified by clearing the bit in DDRx to 0


    /*
    * This sets bit 0 of DDRB to 1 → PB0 is configured as OUTPUT.
    * will control this pin using PORTB
    */
    DDRB |= (1 << PB0);
    
    /*
    * This clears bit 2 of DDRD → PD2 is configured as INPUT
    */
    DDRD &= ~(1 << PD2);

    /*
    * Enables internal pull up resisitor
    */
    PORTD |= (1 << PD2);
    
    /*
    * INTx bit located in the EIMSK (External Interrupt Mask Register) register.
    * The ATmega has two external hardware interrupts: pins PD2 and PD3 designated as INT0, 
    * and INT1 respectively
    */
    EIMSK |=  (1 << INT0); 
    
    /*
    * EICRA (External Interrupt Control Register A)
    */
    EICRA |= (1 << ISC00) | (1 << ISC01); 
    

    /*
    * cli() macro clears the I bit of the SREG register while sei() sets it. 
    */
    sei();

    while (1) {
        
    }
}