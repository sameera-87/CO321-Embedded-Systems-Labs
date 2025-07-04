#include <avr/io.h>
#include <util/delay.h>

int main(void) {

    /*
    * 0x3F in binary is 00111111
    */
    DDRB = 0x3F;
    
    /*
    * 1 << PD7 shifts 1 to bit 7 → 10000000
    * ~(1 << PD7) inverts that → 01111111
    * DDRD &= ... clears bit 7 of DDRD, setting PD7 as an input.
    */
    DDRD &= ~(1 << PD7);
    
    /*
    * PORTD bit to 1 activates its internal pull-up resistor.
    * Without a pull-up resistor, the input pin would float (be unstable), picking up noise and giving unpredictable results.
    */
    PORTD |= (1 << PD7);

    uint8_t count = 0;
    uint8_t prev = 1;

    while (1) {

        /*
        * PIND is a special register in AVR microcontrollers that holds the current logic level 
        * (input state) of all 8 pins on Port D.
        */
        uint8_t current = (PIND & (1 << PD7)) >> PD7;

        if (prev == 1 && current == 0) {
            _delay_ms(50);
            count++;
            PORTB = count & 0x3F; 
        }

        prev = current;
    }
}