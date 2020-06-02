
#include "Timer.h"

void Timer_init() {
    // set mode to normal mode
    /*TCCR0A &= ~( (1 << 1) | (1 << 0) );
    TCCR0B &= ~( (1 << 3) );
    
    // set prescaler to 1
    TCCR0B &= ~( (1 << 2) | (1 << 1) );
    TCCR0B |= (1 << 0);*/
    
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCCR0B |= (1 << 0);
	
	// enable interrupt
	TIMSK0 |= (1 << 0);
}
