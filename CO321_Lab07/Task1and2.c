#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// USART Setup
void usart_init(void) {
    unsigned int ubrr = F_CPU / 16 / 9600 - 1;
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);      // Enable RX and TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // 8-bit data
}

void usart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));          // Wait until buffer is empty
    UDR0 = data;
    _delay_ms(5);
}

char usart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));           // Wait until data is received
    return UDR0;
}

// EEPROM Handling
void EEPROMwrite(unsigned int address, char data) {
    while (EECR & (1 << EEPE));
    EEAR = address;
    EEDR = data;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
}

char EEPROMread(unsigned int address) {
    while (EECR & (1 << EEPE));
    EEAR = address;
    EECR |= (1 << EERE);
    return EEDR;
}

void EEPROM_clear(void) {
    unsigned int i;
    for (i = 0; i < 1024; i++) {
        EEPROMwrite(i, 0xFF);
    }
}

int main(void) {
    usart_init();
    _delay_ms(1000);
    EEPROM_clear();

    unsigned int addr = 0;
    unsigned int i;
    char ch;
    while ((ch = usart_receive()) != '\r' && addr < 1024) {
        EEPROMwrite(addr++, ch);
        _delay_ms(20);
    }

    // Echo stored sentence via USART
    for (i = 0; i < addr; i++) {
        char echo = EEPROMread(i);
        if (echo == 0x00 || echo == 0xFF) break;
        usart_transmit('[');
        usart_transmit(echo);
        usart_transmit(']');
        _delay_ms(10);
    }
    while (1);
}
