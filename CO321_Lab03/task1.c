#include <avr/io.h>

void delay_timer2ms(){
    TCNT0 = 131;  // initial counter value for prescaler 1:256 and for 2ms delay

    TCCR0A = 0b00000000;
    TCCR0B = 0b00000100;  //Prescale is 1:256 and normal mode

    while ((TIFR0 & 0x01)==0){}

    TCCR0A = 0b00000000;
    TCCR0B = 0b00000000;  // clear the timer otherwise it will keep counting

    /*
    * clears the TOV0 bit bit from this
    * This is called W1c (write 1 to clear)
    * Since TOV0 is already set 1 in the above while loop
    * The below line clears it
    */
    TIFR0 = 0x01; 
}

int main(void){
    DDRB = DDRB|(1<<5);

    while(1){
        PORTB = PORTB ^ (1<<5);
        delay_timer2ms();
    }
}