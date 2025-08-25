#include <avr/io.h>
#include <util/delay.h>

#define DIN PB3
#define CLK PB5
#define CS PB2

void spi_init(void){
    DDRB |= (1<<DIN) | (1<<CLK) | (1<<CS);
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);

    PORTB |= (1<<CS); // set cs pin to high
}

void spi_transfer(char data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

void spi_send(uint8_t address, uint8_t data)
{
    PORTB &= ~(1<<CS);
    spi_transfer(address);
    spi_transfer(data);
    PORTB |= (1<<CS);
}

int main(void) {
    spi_init();
    spi_send(0x0C,0x01); // for normal mode 
    spi_send(0x0A, 0x03); // for brightness
    spi_send(0x0B, 0x07); // scan limit
    spi_send(0x09, 0x00); // dont' decode the data

    DDRB |= (1<<PB0);
    _delay_ms(1);
    PORTB ^= (1<<PB0);
    for (uint8_t i = 1; i <= 8; i++) {
        spi_send(i, 0x00);  // Write all zeros to each row
    }
    while(1){
        PORTB ^= (1<<PB0);
        for (uint8_t i =1; i <= 8; i++){
            spi_send(i,(1<<(i-1)));
            _delay_ms(1000);
        }
        _delay_ms(9);
        for (uint8_t i = 1; i <= 8; i++) {
            spi_send(i, 0x00);  // Write all zeros to each row
            _delay_ms(1000);
        }

    }
    return 0;
}