#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BLINK_DELAY_MS 1000

// Helper function to set prescaler bits in TCCR0B
void set_prescaler(uint8_t prescale_code) {
    // Clear prescaler bits (CS02, CS01, CS00)
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
    // Set new prescaler bits
    TCCR0B |= prescale_code;
}

int main(void) {
    // Set PD6 (OC0A) as output
    DDRD |= (1 << 6);

    // Set Fast PWM 8-bit, non-inverting mode
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
    // WGM02=0 in TCCR0B for Fast PWM 8-bit

    // Duty cycle (volume) fixed to 128 (50%)
    OCR0A = 128;

    // Prescaler codes for Timer0:
    // CS02 CS01 CS00 | Prescaler
    // 0    0    1    | 1
    // 0    1    0    | 8
    // 0    1    1    | 64
    // 1    0    0    | 256
    // 1    0    1    | 1024

    // We will generate frequencies in increasing order by changing prescaler

    // Array of prescaler codes in increasing frequency order:
    uint8_t prescalers[] = {
        (1 << CS02) | (1 << CS00),  // 1024 -> ~61 Hz
        (1 << CS02),                // 256  -> ~244 Hz
        (1 << CS01) | (1 << CS00),  // 64   -> ~976 Hz
        (1 << CS01),                // 8    -> ~7,812 Hz
        // skipping 1 (62kHz) as it's too high to hear or useful
    };

    while (1) {

        int i;
        
        for (i = 0; i < 4; i++) {
            set_prescaler(prescalers[i]);
            _delay_ms(BLINK_DELAY_MS);
        }
    }
}

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t value = 0;

ISR(INT0_vect) {
    _delay_ms(500);
    value = (value << 1);
    PORTB = value & 0x3F;
}

ISR(INT1_vect) {
    _delay_ms(500);
    value = (value << 1) | 0x01;
    PORTB = value & 0x3F;
}

int main(void) {
    DDRB = 0x3F;
    DDRD &= ~((1 << PD2) | (1 << PD3));

    PORTD |= (1 << PD2) | (1 << PD3);

    EIMSK |= (1 << INT0) | (1 << INT1);

    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);

    sei();
    
    while (1) {
    };
}




// #include <avr/io.h>
// #include <util/delay.h>

// #define BLINK_DELAY_MS 1000

// // Fast PWM mode ==> WGM00 =1, WGM01=1, WGM02=0
// // Non inverting mode ==> COM0A0 =0, COM0A1=1
// // Prescales ==> 8,64,256,1024 
// // Prescale values: 2 = 8, 3 = 64, 4 = 256, 5 = 1024  <-- frequency chnges with prescale

// int main()
// {

//     DDRD = DDRD | (1 << 6);
    

//     TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);

//     int prescale;
//     // int value = 50;
//     int value = 1000;

//     while (1)
//     {
//         for (prescale = 2; prescale <= 5; prescale++)
//         {   
//             OCR0A = value; 
//             TCCR0B = prescale; // Increase Prescale
//             value -= 10; // Decrease duty cycle
//             _delay_ms(BLINK_DELAY_MS);
//         }
//     }

//     return 0;
// }