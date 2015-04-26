#include <avr/io.h>
#include <util/delay.h>
#include "InputInterrupts.h"
#include "LCD.h"
#include "Sound.h"
#include "Serial.h"

#define FOSC 9830400		// Clock frequency
#define BAUD 9600              // Baud rate used by the LCD
#define MYUBRR FOSC/16/BAUD-1



int main(void)
{
    _delay_ms(4000);
    spi_init_master();
    init_lcdd();
    
    while(1)
    {
    display_bitmap(0);
    _delay_ms(5000);
    display_bitmap(1);
    _delay_ms(5000);
    display_bitmap(2);
    _delay_ms(5000);
    }
    
    /*init_audio();

    send_audio_data(0x0001);
    send_audio_data(0xfffe);
    _delay_ms(5000);
    send_audio_data(0x0002);
    send_audio_data(0xfffe);*/
    
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
    //}
    //InputInterruptsInit();
    //while(1);
}




