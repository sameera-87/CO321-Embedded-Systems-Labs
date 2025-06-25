#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Initialize ADC with external AREF and left-adjusted result
void adc_init() {
    ADMUX = (1 << ADLAR)        // Left-adjust result for 8-bit (read from ADCH)
          | (1 << MUX0);        // Use ADC1 (PC1)
    // REFS1=0, REFS0=0 → Use External AREF (pin 21)

    ADCSRA = (1 << ADEN)        // Enable ADC
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler = 128
}

// Read 8-bit ADC result
uint8_t read_adc_high_byte() {
    ADCSRA |= (1 << ADSC);              // Start conversion
    while (ADCSRA & (1 << ADSC));       // Wait until done
    return ADCH;                        // Read high 8 bits
}

int main(void) {
    DDRC &= ~(1 << PC1);   // PC1 (ADC1) as input
    DDRD |= (1 << PD0);    // PD0 as output (for LED)

    adc_init();            // Initialize ADC

    while (1) {
        uint8_t value = read_adc_high_byte();  // Read light level

        // Simple threshold: adjust depending on AREF and lighting
        if (value > 100) {
            PORTD |= (1 << PD0);  // Dark → LED ON
        } else {
            PORTD &= ~(1 << PD0); // Bright → LED OFF
        }

        _delay_ms(100); // Debounce / delay
    }
}