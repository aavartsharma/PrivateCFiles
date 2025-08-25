#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>

#define F_CPU 16000000UL
#define BAUDRATE 115200


void uart_init() {
	UCSR0A |=  (1<< U2X0);

	uint16_t ubrr = F_CPU/(BAUDRATE*8UL) - 1;
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;

	UCSR0B = (1<<RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1<< UCSZ00);
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

int main(void) {

	uart_init();
	// 
	DDRB |= (1<<PB5);
	DDRD |= (1<<PD5);
	_delay_ms(1);
	uart_puts("hello new world!!\r\n");
	PORTD |= (1<<PD5);
	char str[12];
	while (1) {
		PORTB = PORTB ^ (1<<PB5);
		PORTD ^= (1<<PD5);
		
		_delay_ms(1000);
		uart_puts("hello new world!!\r\n");
		sprintf(str, "%u", SREG);
		str[9] = '\0';
		str[10] = '\n';
		str[11] = '\r';
		uart_puts(str);
		_delay_ms(1000);
		
	}
	return 0;
}
