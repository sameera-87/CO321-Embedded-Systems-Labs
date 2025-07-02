#include <avr/io.h>

int main(void){

    // set OC0A as the output
    DDRD |= (1 << PD6);

    // set fast PWM mode WGM00 = 1, WGM01 = 1, WGM02 = 0
    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << WGM01);

    TCCR0B &= ~(1 << WGM02);

    // Set non inerting mode for OC0A
    // COM0A1 = 1, COM0A2 = 0
    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A2);

    // set prescalar for 64
    TCCR0B |= (1 << CS00);
    TCCR0B |= (1 << CS01);

    TCCR0B &= ~(1 << CS02);

    OC0A = 128;

    while(1){
        
    }

}