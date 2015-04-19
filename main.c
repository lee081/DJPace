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

#define FOSC 9830400		// Clock frequency
#define BAUD 9600              // Baud rate used by the LCD
#define MYUBRR FOSC/16/BAUD-1

//serial port functions 


int main(void)
{
    /*
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
    }*/
    InputInterruptsInit();
    while(1);
}
