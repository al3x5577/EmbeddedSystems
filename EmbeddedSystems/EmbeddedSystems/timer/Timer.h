#ifndef TIMER_H_
#define TIMER_H_

#define COMPA_VAL 250
#define COMPB_VAL 135

#define COMPA_VAL_8MHZ 125
#define COMPB_VAL_8MHZ 63

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../gpio/Led.h"
#include "../uart/Uart.h"

void Timer_init(uint8_t clockFreqMhz);

uint16_t Timer_getTick(void);


#endif /* TIMER_H_ */
