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
#include "InputInterrupts.h"
#include "LCD.h"

#define FOSC 9830400		// Clock frequency
#define BAUD 9600              // Baud rate used by the LCD
#define MYUBRR FOSC/16/BAUD-1


int main(void)
{
    _delay_ms(4000);
    spi_init_master();
    
    int x, y;
    

    
    init_lcdd();
    while(1)
    {
        display_bitmap();
        //color_bars();
        _delay_ms(1000);
        //PORTB &= ~(1 << PB2);
        //SPDR = 0x12;
        //while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete
        //spiwrite(0x15);
        //SPCR = temp_backup;
        //PORTB |= (1 << PB2);
        //writecommand(0x00);
        //writedata(0x19);
        
        
        
        
    }
    //InputInterruptsInit();
    //while(1);
}
