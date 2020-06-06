#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void Timer_init(void);

uint16_t Timer_getTick(void);

void loop_blink_with_interrupt(void);

#endif /* TIMER_H_ */
