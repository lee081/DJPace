#include <avr/io.h>
#include <util/delay.h>
#include "InputInterrupts.h"
#include "LCD.h"
#include "Sound.h"

#define FOSC 9830400		// Clock frequency
#define BAUD 9600              // Baud rate used by the LCD
#define MYUBRR FOSC/16/BAUD-1



int main(void)
{
    sequence();
    
    return 0;
    //spi_init_master();
    
    //int x, y;
    

    
    //init_lcdd();
    //while(1)
    //{
        //display_bitmap();
        //color_bars();
        //PORTB &= ~(1 << PB2);
        //SPDR = 0x12;
        //while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete
        //spiwrite(0x15);
        //SPCR = temp_backup;
        //PORTB |= (1 << PB2);
        //writecommand(0x00);
        //writedata(0x19);
        
        
        
        
    //}
    //InputInterruptsInit();
    //while(1);
}




