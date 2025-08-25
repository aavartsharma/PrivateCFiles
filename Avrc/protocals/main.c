#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Shift Register Pins
#define DATA_PIN   PB0
#define CLOCK_PIN  PB1
#define LATCH_PIN  PB2

// === UART FUNCTIONS ===
void uart_init(unsigned int baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0B = (1 << RXEN0);                    // Enable receiver
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // 8-bit data
}

uint8_t uart_receive(void) {
    while (!(UCSR0A & (1 << RXC0))); // Wait for data
    return UDR0;
}

// === SHIFT REGISTER FUNCTIONS ===
void shift_register_init() {
    DDRB |= (1 << DATA_PIN) | (1 << CLOCK_PIN) | (1 << LATCH_PIN); // Outputs
}

void shift_register_write(uint8_t data) {
    for (int i = 7; i >= 0; i--) {
        // Set data pin
        if (data & (1 << i))
            PORTB |= (1 << DATA_PIN);
        else
            PORTB &= ~(1 << DATA_PIN);

        // Clock pulse
        PORTB |= (1 << CLOCK_PIN);
        _delay_us(1);
        PORTB &= ~(1 << CLOCK_PIN);
    }

    // Latch pulse
    PORTB |= (1 << LATCH_PIN);
    _delay_us(1);
    PORTB &= ~(1 << LATCH_PIN);
}

// === MAIN ===
int main(void) {
    shift_register_init();
    uart_init(9600); // Use 9600 baud for reliability

    while (1) {
        uint8_t data = uart_receive();             // Wait for UART input
        shift_register_write(data);               // Show it on shift register
    }
}