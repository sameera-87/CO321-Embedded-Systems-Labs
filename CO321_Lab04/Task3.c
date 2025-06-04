#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

void playFrequency(uint16_t freq) {
    // Prescaler 64
    uint32_t top = (F_CPU / (freq * 64UL)) - 1;

    ICR1 = top;           // TOP value for Fast PWM mode 14
    OCR1B = top / 2;      // 50% duty cycle

    // Fast PWM mode 14, TOP = ICR1
    TCCR1A = (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
}

int main(void) {
    DDRD |= (1 << PD4);  // OC1B pin output

    uint16_t notes[] = {262, 330, 392, 523};
    uint8_t i;

    while (1) {
        for (i = 0; i < 4; i++) {
            playFrequency(notes[i]);
            _delay_ms(700);
        }
    }
}