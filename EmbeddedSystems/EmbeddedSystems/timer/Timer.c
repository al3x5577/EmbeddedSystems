
#include "Timer.h"

void Timer_init() {
    // set mode to normal mode
    TCCR0A &= ~( (1 << WGM01) | (1 << WGM00) );
    TCCR0B &= ~( (1 << WGM02) );
    
    // set prescaler to 1
    TCCR0B &= ~( (1 << CS02) | (1 << CS01) );
    TCCR0B |= (1 << CS00);
	
	// enable interrupt
	TIMSK0 |= (1 << TOIE0);
}
