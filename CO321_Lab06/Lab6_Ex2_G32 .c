#define F_CPU 16000000UL
#include <avr/io.h>

void usart_init(void) {
    unsigned int ubrr = F_CPU / 16 / 9600 - 1;  // Calculate UBRR for 9600 baud (speed at which data is transmitted bits per second)
    UBRR0H = (ubrr >> 8); // Set high byte of baud rate register

    UBRR0L = ubrr; // Set low byte of baud rate register

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Enable Receiver and Transmitter Without these, no data will be sent or received.
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, no parity, 1 stop bit (8 data bits per character, No parity bit (no error check bit), 1 stop bit to signal end of byte)
}

void usart_send(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));  // waits until the UDRE0 bit becomes 1, which means the transmit buffer (UDR0) is empty and ready to receive new data.
    UDR0 = data;  // Once the buffer is empty, Send data
}

unsigned char usart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));  // Wait in a loop until the RXC0 bit is set, meaning new data has arrived and is ready to be read.
    return UDR0;  // Return the received data from the USART Data Register 0.
}

void usart_send_string(const char* str) {
    while (*str) {          // Loop until the end of the string (takes a string (a pointer to a sequence of characters ending with '\0')) 
        usart_send(*str++);  //Send the current character using usart_send(), then move the pointer to the next character.
    }
}

int main(void) {
    usart_init();

    while (1) {
        usart_send_string("Janith. - E/20/231\r\n");
        usart_send_string("Sameera - E/20/212\r\n");
        for (volatile long i = 0; i < 200000; i++);  // Delay
    }

    return 0;
}