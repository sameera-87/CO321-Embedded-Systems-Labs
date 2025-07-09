#define F_CPU 16000000UL
#include <avr/io.h>

void usart_init(void) {
    unsigned int ubrr = F_CPU / 16 / 9600 - 1;  // Calculate UBRR for 9600 baud
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Enable Receiver and Transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, no parity, 1 stop bit
}

void usart_send(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));  // Wait for buffer to be empty
    UDR0 = data;  // Send data
}

unsigned char usart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));  // Wait for data to be received
    return UDR0;  // Get received data
}

void usart_send_string(const char* str) {
    while (*str) {
        usart_send(*str++);
    }
}

int main(void) {
    usart_init();

    while (1) {
        usart_send_string("Janith. - E/20/231\r\n");
        usart_send_string("Sameera - E/20/212\r\n");

        volatile long i;

        for (i = 0; i < 200000; i++);  // Delay
    }

    return 0;
}