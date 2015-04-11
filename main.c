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

void OpenSPI()
{
    SPCR = 0x50;
}

void HardwareReset()
{
    DDRB &= ~_BV(DDB0);
    _delay_ms(1);
    DDRB |= _BV(DDB0);
    _delay_ms(200);
    // pull PB0 (digital 8) briefly low
    // 1 mS is enough
    // return PB0 high
    // wait 200 mS for reset to finish
}

void CloseSPI()
{
    SPCR = 0x00;
}

uint8_t Xfer(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & 0x80));
    return SPDR;
}
// you can use uint8_t for byte
// initiate transfer
// wait for transfer to complete

void WriteData (uint8_t b)
{
    Xfer(b);
}

void WriteCmd (uint8_t cmd)
{
    ClearBit(PORTB,1);
    Xfer(cmd);
    SetBit(PORTB,1);
}

void InitDisplay()
{
    HardwareReset();
    WriteCmd(SLPOUT);
    _delay_ms(150);
    WriteCmd(COLMOD);
    WriteData(0x05);
    WriteCmd(DISPON);
    // initialize display controller
    // take display out of sleep mode
    // wait 150mS for TFT driver circuits
    // select color mode:
    // mode 5 = 16bit pixels (RGB565)
    // turn display on!
}

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

/*
 sci_out - Output a byte to SCI port
 */
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

/*
 sci_outs - Print the contents of the character string "s" out the SCI
 port. The string must be terminated by a zero byte.
 */
void sci_outs(unsigned char *s)
{
    unsigned char ch;
    
    while ((ch = *s++) != (unsigned char) '\0')
    sci_out(ch);
}

int main(void)
{
    
    sci_init();                 // Initialize the SCI port
    uint8_t x;
    DDRD |=(1<<DDD7);
    ADMUX |= (1<<REFS0);
    ADMUX &=~(1<<REFS1);
    ADMUX |= (1<<ADLAR);
    //ADMUX |= (3<<MUX0);
    //ADMUX &= (0xf0 | (3<<MUX0));
    ADCSRA |= (7<<ADPS0);
    ADCSRA |= (1<<ADEN);
    while (1) {
        ADCSRA |= (1 << ADSC); // Start a conversion
        while (ADCSRA & (1 << ADSC)); // wait for conversion complete
        x = ADCH; // Get converted value
        sci_num(x);
        _delay_ms(10);
        UDR0 = 0;
        if(x > 82)
            PORTD |= (1<<PD7);
        else
            PORTD &= ~(1<<PD7);
    }
}
