#include <avr/io.h>
#include <util/delay.h>


void delay_timer(){
    TCNT1 = 49910;

    TCCR1A = 0b0000000000000000;
    TCCR1B = 0b0000000000000101;  //Prescale is 1:1024

    while ((TIFR1 & 0x0001)==0){}

    TCCR1A = 0b0000000000000000;
    TCCR1B = 0b0000000000000000;

    TIFR1 =0x0001;  
}

int main(void) {
    // Set PB0–PB3 as output
    DDRB |= 0x0F;

    // Define LED sequence: A B C D C B A B C D C ...
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

    DDRB = DDRB|(1<<5);

    while (1) {
        PORTB = (PORTB & 0xF0) | sequence[i]; // Keep upper bits, modify lower bits
        delay_timer();
        i = (i + 1) % seq_length;
        PORTB = PORTB ^ (1<<5);
    }
}