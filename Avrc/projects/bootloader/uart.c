#ifndef _USART_H
#define _USART_H
#ifndef F_CPU
#define F_CPU 8000000
#endif
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include<avr/io.h>
#include<util/delay.h>
 
void usart_init();
void usart_putch(unsigned char send);
unsigned int usart_getch();
 
void usart_init()
{
  UCSRB |= (1 << RXEN) | (1 << TXEN);   
  // Turn on the transmission and reception circuitry
  UCSRC |= (0 << URSEL) | (1<<USBS) | (1 << UCSZ0) | (1 << UCSZ1); 
  // Use 8-bit character sizes
 
  UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value..
  // into the low byte of the UBRR register
  UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
  // into the high byte of the UBRR register
}
 
void usart_putch(unsigned char send)
{
  while ((UCSRA & (1 << UDRE)) == 0); // Do nothing until UDR is ready..
  // for more data to be written to it
  UDR = send; // Send the byte 
}
 
unsigned int usart_getch()
{
  while ((UCSRA & (1 << RXC)) == 0);
// Do nothing until data have been received and is ready to be read from UDR
  return(UDR); // return the byte
}
 
#endif
