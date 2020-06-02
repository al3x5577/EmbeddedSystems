/*
 * Projekt1.c
 *
 * Created: 26.05.2020 00:20:09
 * Author : MSR
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

#include "gpio/Taster.h"
#include "gpio/Led.h"
#include "playground/Playground.h"
#include "timer/Timer.h"
#include <avr/interrupt.h>


volatile uint16_t x = 0;


ISR(TIMER0_OVF_vect){
    x++;
}


int main(void) {
	
    Led_init();
	Taster_init();
    Timer_init();
	sei();
	
    while (1) {
        playground();
        if ( x > 1000) {
            x = 0;
        }
    }
}

