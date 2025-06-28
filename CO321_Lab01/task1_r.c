#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void){

    /*
    set PB0 to PB3 as outputs
    */
    DDRB = DDRB | 0x0F;

    while(1){

        /*
        Turn on all the leds
        */
        PORTB |= 0x0F;

        _delay_ms(BLINK_DELAY_MS);
        
        /*
        Turn off all the leds
        PORTB = 0x00; This will zero all bits in Port B
        PORTB &= ~(0X0F); This will only zero the relevent bits
        */
        PORTB &= ~(0X0F);

        _delay_ms(BLINK_DELAY_MS);
    }

}