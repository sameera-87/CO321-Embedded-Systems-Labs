#include <avr/io.h>

int main(void) {
    // Set OC0A as output
    DDRD |= (1 << PD6);

    // Set Fast PWM Mode to do that WGM01 and WGM00 to 1, WGM02 = 0
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    // Clear WGM02 to set Fast PWM mode
    TCCR0B &= ~(1 << WGM02);

    // Non-inverting mode for OC0A: COM0A1 = 1, COM0A0 = 0
    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);

    // Set Prescaler to 64: CS01 and CS00 to 1
    TCCR0B |= (1 << CS01);   //Clock Select bits in TCCR0B
    TCCR0B |= (1 << CS00);
    // Clear CS02 to set prescaler to 64
    TCCR0B &= ~(1 << CS02);

    OCR0A = 128;

    while (1) {
        
    }
}