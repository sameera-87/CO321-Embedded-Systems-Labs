#include <util/delay.h>
#include <avr/io.h>

int main(void) {
    DDRD |= (1 << PD6); // OC0A as output

    // Set Fast PWM Mode
    // WGM01 and WGM00 to 1, WGM02 = 0
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

    // Non-inverting mode for OC0A
    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);

    // Set Prescaler to 64
    TCCR0B |= (1 << CS01);
    TCCR0B |= (1 << CS00);
    TCCR0B &= ~(1 << CS02);

    uint8_t duty;
    while (1) {
        // Fade up
        for (duty = 0; duty < 255; duty++) {
            OCR0A = duty;
            _delay_ms(10);
        }
        // Fade down
        for (duty = 255; duty > 0; duty--) {
            OCR0A = duty;
            _delay_ms(10);
        }
    }
}