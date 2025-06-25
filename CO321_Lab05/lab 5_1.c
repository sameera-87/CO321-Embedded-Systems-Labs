#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Initialize the ADC to use AVCC as reference, left adjust result, and select ADC1
void adc_init() {
    ADMUX = (1 << REFS0)    
          | (1 << ADLAR)    
          | (1 << MUX0);    
    
    ADCSRA = (1 << ADEN)   // Enable ADC
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128 for ADC clock Makes ADC run at 125kHz
}

// Start an ADC conversion and return the 8 most significant bits of the result
uint8_t read_adc_high_byte() {
    ADCSRA |= (1 << ADSC);              
    while (ADCSRA & (1 << ADSC));       
    return ADCH;                        // Return high 8 bits of 10-bit result
}

int main(void) {
    DDRC &= ~(1 << PC1);  // Configure PC1 as input (Analog input pin)
    DDRD = 0xFF;          // Configure PORTD (PD0-PD7) as output for LEDs
    
    adc_init();           // Initialize ADC
    
    while (1) {
        uint8_t adc_value = read_adc_high_byte();  // Read analog voltage on A1

                                                    //Store the value as adc_value (range: 0 to 255)

        uint8_t led_count = adc_value / 32;        

        if (led_count >= 8)
            PORTD = 0xFF;                          // All LEDs ON
        else if (led_count > 0)
            PORTD = (1 << led_count) - 1;          // Light up that many LEDs // (1 << 4) = 0b00010000

                                                                        
            PORTD = 0x00;                          // All OFF

        _delay_ms(100);
    }
}