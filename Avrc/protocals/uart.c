#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>

// === UART FUNCTIONS ===
void uart_init(unsigned int baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0B = (1 << RXEN0);                    // Enable receiver
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // 8-bit data
}

void uart_init_x2(unsigned int baud){
    UCSR0A |= (1<<U2X0);

    uint16_t ubrr = (F_CPU/(baud*16)) -1;
    UBRR0H = (ubrr>>8);
    UBRR0L = ubrr;

    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
    
}

uint8_t uart_receive(void) {
    while (!(UCSR0A & (1 << RXC0))); // Wait for data
    return UDR0;
}

void uart_send(uint8_t data){
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

void uart_putchar(char c){
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void uart_puts(const char* str){
	while(*str){
		uart_putchar(*str++);
	}
}
