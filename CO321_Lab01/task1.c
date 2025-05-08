#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void) {
    DDRB |= 0x0F;  // Set PB0–PB3 as output (0b00001111)

    while (1) {
        PORTB |= 0x0F;  // Turn ON PB0–PB3
        _delay_ms(BLINK_DELAY_MS);
        PORTB &= ~0x0F; // Turn OFF PB0–PB3
        _delay_ms(BLINK_DELAY_MS);
    }
}

