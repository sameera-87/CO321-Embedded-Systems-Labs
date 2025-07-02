#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 160000000UL;
#define BLINK_DELAY_MS 1000;

void set_prescaler(uint8_t prescale_code){
    TCCR0B = ~((1 << CS00) | (1 << CS01) | (1 << CS02));
    TCCR0B |= prescale_code;
}

int manin(void){

    DDRD |= (1 << 6);

    // Fast PWM mode, non inverting
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);

    OCR0A = 128;

    uint8_t prescalars[] = {
        (1 << CS00) | (1 < CS02),
        (1 << CS02),
        (1 << CS01) | (1 << CS00),
        (1 << CS01)
    };

    while(1){
        int i;

        for(int i = 0; i < 4; i++){
            set_prescaler(prescalars[i]);
            _delay_ms(BLINK_DELAY_MS);
        }
    }
}