/************************************************************************
               Reading rotary encoder
       one, two and four step encoders supported

              Author: Peter Dannegger
      https://www.mikrocontroller.net/articles/Drehgeber

 ***********************************************************************/

#ifndef MY_ENCODER_H_
#define MY_ENCODER_H_

#define DEBUG_MY_ENCODER_

#include <avr/io.h>
#include "../timer/Timer.h"

// Debug
#ifdef DEBUG_MY_ENCODER_
#include "../uart/Uart.h"
#include <stdio.h>
#include <string.h>
#endif

void encoder_init(void);

int16_t encoder_get(void);


#endif /* MY_ENCODER_H_ */
