#include <avr/io.h>
#include <util/delay.h>

#define DELAY_MS 200

int main(void) {
    DDRB |= 0x0F;  // Set PB0–PB3 as output
    int i;         // Declare outside the loops for C90 compatibility

    while (1) {
        // ABCD
        for (i = 0; i < 4; i++) {
            PORTB = (1 << i);
            _delay_ms(DELAY_MS);
        }
        // CBA
        for (i = 2; i > 0; i--) {
            PORTB = (1 << i);
            _delay_ms(DELAY_MS);
        }
    }
}
