#ifndef TIMER_H_
#define TIMER_H_

#define COMPA_VAL 250
#define COMPA_VAL_8MHZ 125

#define T2_COMPA_VAL 125
#define T2_COMPA_VAL_8MHZ 125

#include <avr/io.h>
#include <avr/interrupt.h>

void Timer_init(uint8_t clockFreqMhz);

void Timer2_init(uint8_t clockFreqMhz, void (*f)(void));

uint16_t Timer_getTick(void);


#endif /* TIMER_H_ */
