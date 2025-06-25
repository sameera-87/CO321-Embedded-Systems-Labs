#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


void ADC_init() {
    ADMUX = (1 << ADLAR); // Use External AREF, left-adjusted result, ADC0
    ADCSRA = (1 << ADEN) 
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler = 128
}

uint8_t ADC_read() {
    ADCSRA |= (1 << ADSC);              // Start conversion
    while (ADCSRA & (1 << ADSC));       
    return ADCH;                        // Return 8-bit result (left-adjusted)
}

int main(void) {
    DDRD |= (1 << PD0);   // Set PD0 as output (LED)
    DDRC &= ~(1 << PC0);  // Set PC0 (ADC0) as input

    ADC_init();

    while (1) {
        uint8_t light = ADC_read();     // Read ADC value

        if (light < 200) {
            PORTD |= (1 << PD0);        //LED ON
        } else {
            PORTD &= ~(1 << PD0);       //LED OFF
        }

        _delay_ms(100);                 // Wait before next reading
    }
}
