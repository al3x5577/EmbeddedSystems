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





int main(void) {
	
    Led_init();
	Taster_init();
    Timer_init();
	sei();
	
    uint8_t state_testBoard = 0;
    uint16_t last_time = 0;
    
    /**
    Toggle PORTB every 500ms -> LEDs blink with 1 Hz, accuracy: +- 70 us
    (There could be a lag if timer_count was cleared, approximately every 65,5 seconds)
    */
    while (1) {
        // Check if time difference is more than 500 ms
        if ( (Timer_getTick() - last_time) >= 500 ) {
            last_time = Timer_getTick();
            
            // toggle leds
            if (state_testBoard) {
                state_testBoard = 0;
                PORTB = 0x00;
            }else {
                state_testBoard = 1;
                PORTB = 0xFF;
            }
        }
        
        
        //playground();
    }
}


