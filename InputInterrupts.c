//
//  InputInterrupts.c
//  final
//
//  Created by Sam Vercauteren on 4/19/15.
//
//

#include "InputInterrupts.h"

int times[10];

int currentI;
int high;
int count;

void InputInterruptsInit()
{
    sci_init();
    
    ADMUX |= (1<<REFS0);
    ADMUX &=~(1<<REFS1);
    ADMUX |= (1<<ADLAR);
    ADCSRA |= (7<<ADPS0);
    ADCSRA |= (1<<ADEN);
    
    currentI = 0;
    high = 0;
    
    //set up interrupts
    TCCR1B |= (1 << WGM12);     // Set for CTC mode.  OCR1A = modulus
    TIMSK1 |= (1 << OCIE1A);    // Enable CTC interrupt
    sei();                      // Enable global interrupts
    OCR1A = 1920;              // Set the counter modulus
    TCCR1B |= (1 << CS12);      // Set prescaler for divide by 256,
}

ISR(TIMER1_COMPA_vect)
{
    if(HeartMonitorReadValue())
    {
        if(!high)
        {
            high = 1;
            count = 0;
            sci_num(0x11);
        }
        else
            count++;
    }
    else
    {
        high = 0;
    }
}