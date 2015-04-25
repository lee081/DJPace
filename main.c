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
    //sequence();
    
    
    init_audio();
    
    /*
     audio_data = 0xffff;
     send_audio_data();*/
    send_audio_data(0x0001);
    send_audio_data(0xfffe);
    _delay_ms(5000);
    send_audio_data(0x0002);
    send_audio_data(0xfffe);
    
    while(1);
    
    return 0;
    
    //return 0;
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




