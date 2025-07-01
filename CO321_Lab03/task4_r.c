#include <avr/io.h>

void delay_timer_1s(void){

    TCNT1 = 49912;

    TCCR1A = 0x0000;
    TCCR1B = 0x0005;

    while((TIFR1 & 0x0001) == 0);

    TCCR1A = 0x0000;
    TCCR1B = 0x0000;

    TIFR1 = 0x0001;
}


int main(void){

    DDRB |= 0x0F;
    DDRB |= (1 << PB5);

    // sequence A B C D C B 
    uint8_t sequence[] = {
        (1 << PB0),
        (1 << PB1),
        (1 << PB2),
        (1 << PB3),
        (1 << PB2),
        (1 << PB1)
    };

    uint8_t seq_length = sizeof(sequence) / sizeof(sequence[0]);
    uint8_t i = 0;

    while(1){
        PORTB = (PORTB & 0xF0) | sequence[i];
        delay_timer_1s();
        i = (i + 1) % seq_length;
        PORTB ^= (1 << PB5);
    }
}