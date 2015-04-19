/*************************************************************
*       at328-0.c - Demonstrate simple I/O functions of ATmega328
*
*       Program loops turning PC0 on and off as fast as possible.
*
* The program should generate code in the loop consisting of
*   LOOP:   SBI  PORTC,0        (2 cycles)
*           CBI  PORTC,0        (2 cycles)
*           RJMP LOOP           (2 cycles)
*
* PC0 will be low for 4 / XTAL freq
* PC0 will be high for 2 / XTAL freq
* A 9.8304MHz clock gives a loop period of about 600 nanoseconds.
*
* Revision History
* Date     Author      Description
* 09/14/12 A. Weber    Initial Release
* 11/18/13 A. Weber    Renamed for ATmega328P
*************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#define ClearBit(x,y) x &= ~_BV(y)
#define SetBit(x,y) x |= _BV(y)

#define SWRESET 0x01
#define SLPOUT  0x11
#define DISPOFF 0x28
#define DISPON  0x29
#define CASET 0x2A
#define RASET 0x2B
#define RAMWR 0x2C
#define MADCTL  0x36
#define COLMOD  0x3A

#define FOSC 9830400		// Clock frequency
#define BAUD 9600              // Baud rate used by the LCD
#define MYUBRR FOSC/16/BAUD-1

//serial port functions 
void sci_num(uint8_t num)
{
    char first = (num>>4)&0x0f;
    char second = num&0x0f;
    
    
    
    
    first += '0';
    second +='0';
    
    if(first > '9')
    {
        first -= '9';
        first -= 1;
        first += 'A';
    }
    if(second > '9')
    {
        second -= '9';
        second -= 1;
        second += 'A';
    }
    sci_out(first);
    sci_out(second);
    sci_out(' ');
}

void sci_init(void) {
    UBRR0 = MYUBRR;          // Set baud rate
    UCSR0B |= (1 << TXEN0);  // Turn on transmitter
    UCSR0C = (3 << UCSZ00);  // Set for asynchronous operation, no parity,
    // one stop bit, 8 data bits
}

void sci_out(unsigned char ch)
{
    while ( (UCSR0A & (1<<UDRE0)) == 0);
    UDR0 = ch;
}

unsigned char sci_in()
{
    while(!(UCSR0A & (1<<RXC0)) == 0);
    return UDR0;
}

void sci_outs(unsigned char *s)
{
    unsigned char ch;
    
    while ((ch = *s++) != (unsigned char) '\0')
    sci_out(ch);
}

void checkA2D()
{
    
}

int main(void)
{
    
    sci_init();
    uint8_t x;
    int time = 0;
    int flag = 0;
    //DDRD |=(1<<DDD7);
    ADMUX |= (1<<REFS0);
    ADMUX &=~(1<<REFS1);
    ADMUX |= (1<<ADLAR);
    //ADMUX |= (3<<MUX0);
    //ADMUX &= (0xf0 | (3<<MUX0));
    ADCSRA |= (7<<ADPS0);
    ADCSRA |= (1<<ADEN);
    while (1) {
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));
        x = ADCH;
        _delay_ms(1);
        UDR0 = 0;
        if(x < 0xFF && flag == 0)
        {
            flag = 1;
            time = 0;
            sci_num(x);
        }
        if(x < 0xFF && flag == 1)
        {
            time++;
        }
        if(x == 0xFF && flag == 1)
        {
            flag = 0;
        }
    }
}
