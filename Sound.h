//
//  Sound.h
//  final
//
//  Created by Sam Vercauteren on 4/23/15.
//
//

#include <avr/io.h>
#include <util/delay.h>


#define SEND          0x80
#define PLAY_PAUSE    0x01
#define STOP          0x02
#define NEXT          0x04
#define VOLUME_UP     0x08
#define VOLUME_DOWN   0x08
#define ADDRESS       0x10


void init_audio(void);

void send_audio_data(uint16_t);