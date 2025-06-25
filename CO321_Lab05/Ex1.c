#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Initialize the ADC to use AVCC as reference, left adjust result, and select ADC1 (PC1)
void adc_init() {
    ADMUX = (1 << REFS0)    // Use AVCC as reference (5V)
          | (1 << ADLAR)    // Left adjust result to use ADCH for 8-bit read
          | (1 << MUX0);    // Select ADC1 (PC1 pin)

    ADCSRA = (1 << ADEN)    // Enable ADC
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128
}

// Start an ADC conversion and return the 8 most significant bits of the result
uint8_t read_adc_high_byte() {
    ADCSRA |= (1 << ADSC);              // Start ADC conversion
    while (ADCSRA & (1 << ADSC));       // Wait for conversion to complete
    return ADCH;                        // Return the top 8 bits
}

int main(void) {
    DDRC &= ~(1 << PC1);  // Set PC1 as input (ADC1)
    DDRD = 0xFF;          // Set all PORTD pins as output (PD0–PD7 for LEDs)

    adc_init();           // Initialize ADC

    while (1) {
        uint8_t value = read_adc_high_byte();    // Read 8-bit ADC result
        uint8_t led_count = value / 32;          // Map 0–255 to 0–7 LED count

        if (led_count >= 8)
            PORTD = 0xFF;                        // Turn ON all 8 LEDs (255 or near 5V)
        else if (led_count > 0)
            PORTD = (1 << led_count) - 1;        // Turn ON led_count number of LEDs
        else
            PORTD = 0x00;                        // No LEDs ON for 0V

        _delay_ms(100);                          // Short delay for stability
    }
}
