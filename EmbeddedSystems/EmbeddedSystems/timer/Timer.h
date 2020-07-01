#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void Timer_init(uint8_t clockFreqMhz);

uint16_t Timer_getTick(void);


#endif /* TIMER_H_ */
