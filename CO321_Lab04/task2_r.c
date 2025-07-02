#include <avr/io.h>
#include <util/delay.h>

int main(void){

    // OC0A as the output
    DDRD |= (1 << PD6);

    // set fast PWM mode WGM00 = 1, WGM01 = 1, WGM02 = 0
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

    // set non - inverting mode for OC0A
    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);

    // set prescalar to 64
    TCCR0B |= (1 << CS00);
    TCCR0B |= (1 << CS01);
    TCCR0B &= ~(1 << CS02);

    uint8_t duty;

    while(1){

        // fade up
        for(duty = 0; duty < 255; duty++){
            OCR0A = duty;
            _delay_ms(10);
        }

        // fade down
        for(duty = 255; duty > 0; duty--){
            OC0A = duty;
            _delay_ms(10);
        }
    }
}