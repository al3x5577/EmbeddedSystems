/************************************************************************
               Reading rotary encoder
       one, two and four step encoders supported

              Author: Peter Dannegger
      https://www.mikrocontroller.net/articles/Drehgeber

 ***********************************************************************/

#ifndef MY_ENCODER_H_
#define MY_ENCODER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../timer/Timer.h"
#include "../uart/Uart.h"
#include <string.h>

#define PHASE_A     (PINC & 1<<PC6)
#define PHASE_B     (PINC & 1<<PC7)

void encode_init(void);

int loop(void);

#endif /* MY_ENCODER_H_ */
