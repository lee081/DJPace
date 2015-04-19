//
//  Serial.h
//  final
//
//  Created by Sam Vercauteren on 4/14/15.
//
//

#include <avr/io.h>
#include <util/delay.h>

#define FOSC 9830400		// Clock frequency
#define BAUD 9600              // Baud rate used by the LCD
#define MYUBRR FOSC/16/BAUD-1

#ifndef final_Serial_h
#define final_Serial_h


void sci_num(uint8_t);
void sci_init(void);
void sci_out(unsigned char);
unsigned char sci_in();
void sci_outs(unsigned char *s);


#endif
