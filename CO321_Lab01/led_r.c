#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void){

    /*
    1<<5 = 0b00100000 = bitmask for PB5
    set PB5 as the output
    */
    DDRB = DDRB | (1<<5);

    while(1){
        PORTB = PORTB | (1<<5);

        _delay_ms(BLINK_DELAY_MS);
        
        
        /*
        The & operation should be applied here, to forcefully off the led
        */
        PORTB = PORTB & ~(1<<5);

        _delay_ms(BLINK_DELAY_MS);
    }

}