
#include "Timer.h"

volatile uint16_t timer_count = 0;

void Timer_init() { // datasheet page 97
    // set mode to clear timer on compare (CTC)
    TCCR0B &= ~(1 << WGM02);
    TCCR0A |= (1 << WGM01);
    TCCR0A &= ~(1 << WGM00);
    
    // set OCR0A-reg (top value of timer)
    OCR0A = 0x7C;   // dez 124; range 0 - 124 -> 125 cycles till interrupt
    
    // set prescaler to 1/8
    TCCR0B &= ~(1 << CS02);
    TCCR0B |= (1 << CS01);
    TCCR0B &= ~(1 << CS00);
	
	
	TIMSK0 &= ~(1 << OCIE0B);   // disable Output Compare Match B Interrupt
    TIMSK0 |= (1 << OCIE0A);    // enable Output Compare Match A Interrupt
    TIMSK0 &= ~(1 << TOIE0);    // disable timer overflow interrupt
}

uint16_t Timer_getTick() {
    // disable global interrupt
    cli();
    
    // store timer_count in a temp int that can't get changed by ISR
    uint16_t temp_timer_count = timer_count;
    
    // enable global interrupt
    sei();

    return temp_timer_count;
}

/**
 ( not used atm)
 Timer compare A interrput:
 - increase timer_count
 - if timer_count is at max of uint16, set it to 0
 */
ISR(TIMER0_COMPA_vect){
    timer_count++;
}

/**
 ( not used atm)
 Timer overflow interrput:
 - increase timer_count
 - if timer_count is at max of uint16, set it to 0
 */
/*
ISR(TIMER0_OVF_vect){
    timer_count++;
}*/


/* Timer_init() aus Aufgabe 1
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
 */
