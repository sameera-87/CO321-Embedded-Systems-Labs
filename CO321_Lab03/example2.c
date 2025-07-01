#include <avr/io.h>

void delay_timer0(){

    TCNT0 = 116; // Load timer counter register

    TCCR0A = 0x00; // Set the normal mode
    TCCR0B = 0x02; // Set prescalar 1:8 in hexadecimal

    while((TIFR0 & 0x01) == 0); // Wait until the timer overflow (TOV0 becomes 1)

    TCCR0A = 0x00; // clear the timer settings to stop the timer
    TCCR0B = 0x00;

    TIFRO = 0x01; // clear the overflow bit TOV0 (W1c - Write 1 to clear)
}

int main(void){

    DDRB = DDRB | (1 << 5); // ser port 5 as the output

    while(1){
        PORTB = PORTB ^ (1 << 5); // toggle the value using XOR operation
        delay_timer0();
    }
}