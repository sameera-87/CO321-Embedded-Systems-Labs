#include <avr/io.h>
#include <util/delay.h>


int main(void){

    DDRB = 0x3F; // output

    DDRD &= ~(1 << PD7); // input

    PORTD |= (1 << PD7);

    uint8_t count = 0;
    uint8_t prev = 1;

    while(1){

        uint8_t current = (PIND & (1 << PD7)) >> PD7;

        if(prev == 1 && current == 0){
            _delay_ms(100);
            count++;
            PORTB = count & 0x3F;
        }

        prev = current;
    }

}