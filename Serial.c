//
//  Serial.c
//  final
//
//  Created by Sam Vercauteren on 4/14/15.
//
//

#include "Serial.h"

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