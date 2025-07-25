#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// === LCD Pins connected to PORTB ===
#define LCD_RS PB0
#define LCD_E  PB1
#define LCD_D4 PB2
#define LCD_D5 PB3
#define LCD_D6 PB4
#define LCD_D7 PB5

#define KEY_ADDR 0x00  // EEPROM address to store the encryption key

#define SET_BIT(port, bit)    ((port) |= (1 << (bit)))
#define CLEAR_BIT(port, bit)  ((port) &= ~(1 << (bit)))

// === LCD FUNCTIONS ===
void lcd_enable() {
    SET_BIT(PORTB, LCD_E);
    _delay_us(1);
    CLEAR_BIT(PORTB, LCD_E);
    _delay_us(100);
}

void lcd_send_nibble(uint8_t nibble) {
    (nibble & 0x01) ? SET_BIT(PORTB, LCD_D4) : CLEAR_BIT(PORTB, LCD_D4);
    (nibble & 0x02) ? SET_BIT(PORTB, LCD_D5) : CLEAR_BIT(PORTB, LCD_D5);
    (nibble & 0x04) ? SET_BIT(PORTB, LCD_D6) : CLEAR_BIT(PORTB, LCD_D6);
    (nibble & 0x08) ? SET_BIT(PORTB, LCD_D7) : CLEAR_BIT(PORTB, LCD_D7);
    lcd_enable();
}

void lcd_send_byte(uint8_t byte, uint8_t is_data) {
    is_data ? SET_BIT(PORTB, LCD_RS) : CLEAR_BIT(PORTB, LCD_RS);
    lcd_send_nibble(byte >> 4);
    lcd_send_nibble(byte & 0x0F);
    _delay_ms(2);
}

void LCD_cmd(uint8_t cmd) { lcd_send_byte(cmd, 0); }
void LCD_printChar(char c) { lcd_send_byte(c, 1); }
void LCD_print(const char *str) { while (*str) LCD_printChar(*str++); }
void LCD_goto(uint8_t row, uint8_t col) { LCD_cmd(0x80 + row * 0x40 + col); }
void LCD_clear() { LCD_cmd(0x01); _delay_ms(2); }

void LCD_init() {
    DDRB |= 0x3F;
    _delay_ms(50);
    lcd_send_nibble(0x03); _delay_ms(5);
    lcd_send_nibble(0x03); _delay_ms(5);
    lcd_send_nibble(0x03); _delay_ms(1);
    lcd_send_nibble(0x02);
    LCD_cmd(0x28);
    LCD_cmd(0x0C);
    LCD_cmd(0x06);
    LCD_clear();
}

// === EEPROM FUNCTIONS ===
void EEPROMwrite(uint16_t address, uint8_t data) {
    while (EECR & (1 << EEPE));
    cli();
    EEAR = address;
    EEDR = data;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
    sei();
}

uint8_t EEPROMread(uint16_t address) {
    while (EECR & (1 << EEPE));
    EEAR = address;
    EECR |= (1 << EERE);
    return EEDR;
}

// === Caesar Cipher ===
char caesarEncrypt(char ch, uint8_t key) {
    if (ch >= 'A' && ch <= 'Z')
        return ((ch - 'A' + key) % 26) + 'A';
    else if (ch >= 'a' && ch <= 'z')
        return ((ch - 'a' + key) % 26) + 'a';
    else
        return ch;
}

// === Keypad Setup ===
// Rows → PC0–PC3, Cols → PD4–PD7
const char KEYPAD[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

void keypad_init() {
    DDRC &= ~(0x0F);
    PORTC |= 0x0F;
    DDRD |= 0xF0;
    PORTD |= 0xF0;
}

char keypad_getkey() {

    uint8_t col;

    for (col = 0; col < 4; col++) {

        // PORTD = ~(1 << (col + 4));
        PORTD = (PORTD & 0x0F) | ~(1 << (col + 4));

        _delay_us(5);

        uint8_t row;

        for (row = 0; row < 4; row++) {
            if (!(PINC & (1 << row))) {
                while (!(PINC & (1 << row)));
                _delay_ms(50);
                return KEYPAD[row][col];
            }
        }
    }
    return 0;
}

// === Key Setting Mode ===
void setKey() {
    LCD_clear();
    LCD_print("Enter Key (0-9):");
    LCD_goto(1, 0);

    char keyChar = 0;

    while (1) {
        keyChar = keypad_getkey();
        if (keyChar >= '0' && keyChar <= '9') {
            LCD_printChar(keyChar);
            break;
        }
    }

    LCD_print(" # to confirm");
    while (1) {
        char confirm = keypad_getkey();
        if (confirm == '#') {
            EEPROMwrite(KEY_ADDR, keyChar - '0');
            LCD_clear();
            LCD_print("Key Saved!");
            _delay_ms(2000);
            break;
        }
    }
}

// === Text Encryption Mode ===
void encryptText() {
    char plain[11];
    char encrypted[11];

    LCD_clear();
    LCD_print("Enter Text:");
    LCD_goto(1, 0);

    int i;

    for (i = 0; i < 10; i++) {
        char k = 0;
        while (!(k = keypad_getkey()));
        plain[i] = k;
        LCD_printChar(k);
        _delay_ms(300);
    }
    plain[10] = '\0';

    uint8_t key = EEPROMread(KEY_ADDR);
    if (key > 25) key = 3;

    for (i = 0; i < 10; i++)
        encrypted[i] = caesarEncrypt(plain[i], key);
    encrypted[10] = '\0';

    LCD_clear();
    LCD_print("Encrypted:");
    LCD_goto(1, 0);
    for (i = 0; i < 10; i++)
        LCD_printChar(encrypted[i]);

    _delay_ms(3000);
}

// === Main ===
int main(void) {
    LCD_init();
    keypad_init();

    while (1) {
        LCD_clear();
        LCD_print("1:Encrypt 2:Key");
        char choice = 0;
        while (!(choice = keypad_getkey()));
        if (choice == '1') {
            encryptText();
        } 
        else if (choice == '2') {
            setKey();
        }
        _delay_ms(500);
    }
}